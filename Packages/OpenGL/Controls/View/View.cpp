// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#include "Platform/OpenGL/OpenGL.h"

#ifdef DrawText
#undef DrawText
#endif

namespace nitisa
{
	namespace opengl
	{
		const AnsiString CView::m_sProgramVertex{
			"#version 140\n"

			"in vec3 in_Position;\n"
			"in vec3 in_Normal;\n"

			"uniform mat4 app_MatrixModel;\n"
			"uniform mat3 app_MatrixNormal;\n"
			"uniform mat4 app_MatrixCamera;\n"
			"uniform vec3 app_CameraPosition;\n"

			"out vec3 var_N;\n"
			"out vec3 var_L;\n"
			"out vec3 var_V;\n"

			"void main()\n"
			"{\n"
			"	vec4 P = app_MatrixModel * vec4(in_Position, 1);\n"
			"	var_N = app_MatrixNormal * in_Normal;\n"
			"	var_L = vec3(1000, 1000, 1000) - P.xyz;\n"
			"	var_V = app_CameraPosition - P.xyz;\n"
			"	gl_Position = app_MatrixCamera * P;\n"
			"}\n"
		};

		const AnsiString CView::m_sProgramFragment{
			"#version 140\n"

			"in vec3 var_N;\n"
			"in vec3 var_L;\n"
			"in vec3 var_V;\n"

			"out vec4 FragColor;\n"

			"void main()\n"
			"{\n"
			"	vec3 n = normalize(var_N), l = normalize(var_L), v = normalize(var_V), r = reflect(-l, n);\n"
			"	vec4 diffuse = max(dot(n, l), 0.0) * vec4(0.5, 0.5, 0.5, 1.0);\n"
			"	vec4 specular = pow(max(dot(r, v), 0.0), 100) * vec4(1, 1, 1, 1);\n"
			"	FragColor = vec4(0.1, 0.1, 0.1, 1.0) + diffuse + specular;\n"
			"}\n"
		};

	#pragma region Constructor & destructor
		CView::CView() :
			CControl(L"View", true, true, true, true, false, false),
			m_sBackgroundColor{ 0, 0, 0, 255 },
			m_fTurnSpeed{ ntl::DegToRad<float>(1) },
			m_fMoveSpeed{ 1 },
			m_fMoveSlowMultiplier{ 0.01f },
			m_fMoveFastMultiplier{ 100 },
			m_fFOVStep{ ntl::DegToRad<float>(1) },
			m_cAxes{ this },
			m_cGrid{ this },
			m_pCamera{ new CCamera() },
			m_pCanvas{ nullptr },
			m_pDepthTexture{ nullptr },
			m_pFramebuffer{ nullptr },
			m_iLockCount{ 0 },
			m_bUpdateRequired{ false },
			m_bProgramValid{ false },
			m_pProgram{ nullptr }
		{
			OnRender = nullptr;
			setService(new CViewService(this), true);
			setSize(PointF{ 300, 200 });
		}
		
		CView::CView(IForm *parent) :CView()
		{
			setForm(parent);
		}

		CView::CView(IControl *parent) : CView()
		{
			setParent(parent);
		}

		CView::~CView()
		{
			m_pCamera->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		bool CView::isAcceptChild(IControl *control)
		{
			return cast<I3DControl*>(control) != nullptr || cast<IMaterialControl*>(control) != nullptr;
		}
	#pragma endregion

	#pragma region IControl methods
		void CView::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			CControl::Refresh(refresh_children);
		}
	#pragma endregion

	#pragma region IView getters
		ICamera *CView::getCamera()
		{
			return m_pCamera;
		}
	#pragma endregion

	#pragma region IView setters
		bool CView::setCamera(ICamera *value)
		{
			if (value && value != m_pCamera)
			{
				LockUpdate();
				m_pCamera->Release();
				m_pCamera = value;
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		Color CView::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		float CView::getTurnSpeed() const
		{
			return m_fTurnSpeed;
		}

		float CView::getMoveSpeed() const
		{
			return m_fMoveSpeed;
		}

		float CView::getMoveSlowMultiplier() const
		{
			return m_fMoveSlowMultiplier;
		}

		float CView::getMoveFastMultiplier() const
		{
			return m_fMoveFastMultiplier;
		}

		float CView::getFOVStep() const
		{
			return m_fFOVStep;
		}
	#pragma endregion

	#pragma region Setters
		bool CView::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				ForceUpdate();
				return true;
			}
			return false;
		}

		bool CView::setTurnSpeed(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fTurnSpeed))
			{
				m_fTurnSpeed = value;
				return true;
			}
			return false;
		}

		bool CView::setMoveSpeed(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fMoveSpeed))
			{
				m_fMoveSpeed = value;
				return true;
			}
			return false;
		}

		bool CView::setMoveSlowMultiplier(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsLess<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fMoveSlowMultiplier))
			{
				m_fMoveSlowMultiplier = value;
				return true;
			}
			return false;
		}

		bool CView::setMoveFastMultiplier(const float value)
		{
			if (ntl::IsGreater<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fMoveFastMultiplier))
			{
				m_fMoveFastMultiplier = value;
				return true;
			}
			return false;
		}

		bool CView::setFOVStep(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fFOVStep))
			{
				m_fFOVStep = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Axes getters
		bool CView::isShowXAxis() const
		{
			return m_cAxes.isShowX();
		}

		bool CView::isShowYAxis() const
		{
			return m_cAxes.isShowY();
		}

		bool CView::isShowZAxis() const
		{
			return m_cAxes.isShowZ();
		}

		PointF CView::getXAxisRange() const
		{
			return m_cAxes.getXRange();
		}

		PointF CView::getYAxisRange() const
		{
			return m_cAxes.getYRange();
		}

		PointF CView::getZAxisRange() const
		{
			return m_cAxes.getZRange();
		}

		Color CView::getXAxisColor() const
		{
			return m_cAxes.getXColor();
		}

		Color CView::getYAxisColor() const
		{
			return m_cAxes.getYColor();
		}

		Color CView::getZAxisColor() const
		{
			return m_cAxes.getZColor();
		}
	#pragma endregion

	#pragma region Axes setters
		bool CView::setShowXAxis(const bool value)
		{
			return m_cAxes.setShowX(value);
		}

		bool CView::setShowYAxis(const bool value)
		{
			return m_cAxes.setShowY(value);
		}

		bool CView::setShowZAxis(const bool value)
		{
			return m_cAxes.setShowZ(value);
		}

		bool CView::setXAxisRange(const PointF &value)
		{
			return m_cAxes.setXRange(value);
		}

		bool CView::setYAxisRange(const PointF &value)
		{
			return m_cAxes.setYRange(value);
		}

		bool CView::setZAxisRange(const PointF &value)
		{
			return m_cAxes.setZRange(value);
		}

		bool CView::setXAxisColor(const Color &value)
		{
			return m_cAxes.setXColor(value);
		}

		bool CView::setYAxisColor(const Color &value)
		{
			return m_cAxes.setYColor(value);
		}

		bool CView::setZAxisColor(const Color &value)
		{
			return m_cAxes.setZColor(value);
		}
	#pragma endregion

	#pragma region Grid getters
		bool CView::isShowGrid() const
		{
			return m_cGrid.isVisible();
		}

		float CView::getGridXRange() const
		{
			return m_cGrid.getXRange();
		}

		float CView::getGridZRange() const
		{
			return m_cGrid.getZRange();
		}

		float CView::getGridStep() const
		{
			return m_cGrid.getStep();
		}

		Color CView::getGridColor() const
		{
			return m_cGrid.getColor();
		}
	#pragma endregion

	#pragma region Grid setters
		bool CView::setShowGrid(const bool value)
		{
			return m_cGrid.setVisible(value);
		}

		bool CView::setGridXRange(const float value)
		{
			return m_cGrid.setXRange(value);
		}

		bool CView::setGridZRange(const float value)
		{
			return m_cGrid.setZRange(value);
		}

		bool CView::setGridStep(const float value)
		{
			return m_cGrid.setStep(value);
		}

		bool CView::setGridColor(const Color &value)
		{
			return m_cGrid.setColor(value);
		}
	#pragma endregion

	#pragma region Helpers
		void CView::ForceUpdate()
		{
			LockUpdate();
			m_bUpdateRequired = true;
			UnlockUpdate();
		}

		void CView::LockUpdate()
		{
			if (m_iLockCount++ == 0)
				m_bUpdateRequired = false;
		}

		void CView::UnlockUpdate()
		{
			if (m_iLockCount > 0 && --m_iLockCount == 0 && m_bUpdateRequired)
			{
				PointF size{ getSize() };
				m_pCamera->setViewport(RectF{ -size.X / 2, size.Y / 2, size.X / 2, -size.Y / 2 });
				m_pCamera->setAspect(size.X / size.Y);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
		}

		void CView::ActivateProgram(COpenGL *graphics, IModel *model, ICamera *camera)
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (!m_pProgram)
			{
				if (!(m_pProgram = renderer->CreateProgram(m_sProgramVertex, m_sProgramFragment, IRenderer::Bindings{ { 1, "in_Position" }, { 2, "in_Normal" } })))
					return;
				m_bProgramValid = true;
				if ((*reinterpret_cast<GLint*>(&m_hUniformMatrixModel) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_MatrixModel")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformMatrixNormal) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_MatrixNormal")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformMatrixCamera) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_MatrixCamera")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformCameraPosition) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_CameraPosition")) < 0)
					m_bProgramValid = false;
			}
			if (m_bProgramValid)
			{
				renderer->ActivateProgram(m_pProgram);
				graphics->UniformMatrix4fv(*reinterpret_cast<GLint*>(&m_hUniformMatrixModel), 1, GL_TRUE, model->getMatrix().Data);
				graphics->UniformMatrix3fv(*reinterpret_cast<GLint*>(&m_hUniformMatrixNormal), 1, GL_TRUE, model->getNormalMatrix().Data);
				graphics->UniformMatrix4fv(*reinterpret_cast<GLint*>(&m_hUniformMatrixCamera), 1, GL_TRUE, camera->getMatrix().Data);
				graphics->Uniform3f(*reinterpret_cast<GLint*>(&m_hUniformCameraPosition), camera->Position.X, camera->Position.Y, camera->Position.Z);
			}
		}
	#pragma endregion

	#pragma region Paint
		void CView::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			COpenGL *graphics{ cast<COpenGL*>(renderer->NativeGraphics) };
			if (!graphics)
				return;
			if (!m_pCanvas || !m_pCanvas->isValid())
			{
				if (!m_pCanvas)
					m_pCanvas = renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true);
				else if (m_pCanvas->Width != ntl::Round<int>(getWidth()) || m_pCanvas->Height != ntl::Round<int>(getHeight()))
				{
					m_pCanvas->setSize(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()));
					if (m_pFramebuffer)
						m_pFramebuffer->setDepthAttachment(nullptr);
					if (m_pDepthTexture)
						m_pDepthTexture->setSize(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()));
				}
				if (m_pCanvas)
				{
					CStoreTarget s_target{ renderer };
					renderer->ActivateTarget(m_pCanvas);
					if (renderer->Technology != RendererTechnology::OpenGL)
					{
						renderer->Clear(m_sBackgroundColor);
						RenderError(renderer, L"ERROR: OpenGL renderer is required");
					}
					else
					{
					#ifdef _WIN32
						if (!m_pFramebuffer)
							m_pFramebuffer = renderer->CreateFramebuffer();
						if (m_pFramebuffer)
						{
							CStoreFramebuffer s_fb{ renderer };
							renderer->ActivateFramebuffer(m_pFramebuffer);
							if (!m_pDepthTexture)
								m_pDepthTexture = renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::Depth, false);
							if (m_pDepthTexture)
							{
								m_pFramebuffer->setDepthAttachment(m_pDepthTexture);
								CStoreProgram s_program{ renderer };
								graphics->Enable(GL_DEPTH_TEST);
								graphics->ClearColor(m_sBackgroundColor.R / 255.0f, m_sBackgroundColor.G / 255.0f, m_sBackgroundColor.B / 255.0f, m_sBackgroundColor.A / 255.0f);
								graphics->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
								m_cGrid.Render(graphics, m_pCamera);
								m_cAxes.Render(graphics, m_pCamera);
								RenderChildren(this, graphics, renderer);
								if (OnRender)
									OnRender(this);
								graphics->Disable(GL_DEPTH_TEST);
							}
						}
					#else
						renderer->Clear(m_sBackgroundColor);
						RenderError(renderer, L"ERROR: Windows target platform is required");
					#endif
					}
					m_pCanvas->setValid(true);
				}
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CView::RenderError(IRenderer *renderer, const String &error)
		{
			IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
			if (pf)
			{
				CStorePrimitiveMatrix s_matrix{ renderer };
				PointF size{ pf->getStringSize(error, getFont()->Distance) };
				renderer
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>((getWidth() - size.X) * 0.5f, (getHeight() - size.Y) * 0.5f, 0))
					->DrawText(error, pf, getFont()->Distance, Color{ 255, 255, 255, 255 });
			}
		}

		void CView::RenderChildren(IControl *parent, COpenGL *graphics, IRenderer *renderer)
		{
			for (int i = 0; i < parent->getControlCount(); i++)
			{
				I3DControl *control{ cast<I3DControl*>(parent->getControl(i)) };
				if (control)
				{
					I3DControlService *service{ cast<I3DControlService*>(control->QueryService()) };
					if (service)
					{
						if (!control->getMaterial() || !control->getMaterial()->Activate(graphics, control->getModel(), m_pCamera))
							ActivateProgram(graphics, control->getModel(), m_pCamera);
						service->NotifyOnRender(graphics, renderer, m_pCamera);
					}
					RenderChildren(control, graphics, renderer);
				}
			}
		}
	#pragma endregion
	}
}