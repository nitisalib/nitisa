// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#include "Platform/OpenGL/OpenGL.h"

namespace nitisa
{
	namespace opengl
	{
	#pragma region Shaders
		const AnsiString CView::CGrid::m_sVertexShader{
			"#version 140\n"

			"in vec3 in_Position;\n"

			"uniform mat4 app_Matrix;\n"

			"void main()\n"
			"{\n"
			"	gl_Position = app_Matrix * vec4(in_Position, 1);\n"
			"}\n"
		};

		const AnsiString CView::CGrid::m_sFragmentShader{
			"#version 140\n"

			"uniform vec4 app_Color;\n"

			"out vec4 FragColor;\n"

			"void main()\n"
			"{\n"
			"	FragColor = app_Color;\n"
			"}\n"
		};
	#pragma endregion

		const nitisa::VertexFormat CView::CGrid::m_sVertexFormat{
			0, 0, 1, 0,
			0, 0, 0, 0,
			nitisa::VertexFormat::npos, nitisa::VertexFormat::npos, nitisa::VertexFormat::npos, nitisa::VertexFormat::npos, nitisa::VertexFormat::npos, 0, nitisa::VertexFormat::npos, nitisa::VertexFormat::npos };

	#pragma region Constructor & destructor
		CView::CGrid::CGrid(CView *control):
			m_pControl{ control },
			m_bVisible{ true },
			m_fXRange{ 100 },
			m_fZRange{ 100 },
			m_fStep{ 10 },
			m_sColor{ 64, 64, 64, 255 },
			m_pVertexArray{ nullptr },
			m_pProgram{ nullptr },
			m_bGeometryValid{ false },
			m_bProgramValid{ false }
		{

		}
	#pragma endregion

	#pragma region Getters
		bool CView::CGrid::isVisible() const
		{
			return m_bVisible;
		}

		float CView::CGrid::getXRange() const
		{
			return m_fXRange;
		}

		float CView::CGrid::getZRange() const
		{
			return m_fZRange;
		}

		float CView::CGrid::getStep() const
		{
			return m_fStep;
		}

		Color CView::CGrid::getColor() const
		{
			return m_sColor;
		}
	#pragma endregion

	#pragma region Setters
		bool CView::CGrid::setVisible(const bool value)
		{
			if (value != m_bVisible)
			{
				m_bVisible = value;
				m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}

		bool CView::CGrid::setXRange(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fXRange))
			{
				m_fXRange = value;
				m_bGeometryValid = false;
				if (m_bVisible)
					m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}

		bool CView::CGrid::setZRange(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fZRange))
			{
				m_fZRange = value;
				m_bGeometryValid = false;
				if (m_bVisible)
					m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}

		bool CView::CGrid::setStep(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fStep))
			{
				m_fStep = value;
				m_bGeometryValid = false;
				if (m_bVisible)
					m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}

		bool CView::CGrid::setColor(const Color &value)
		{
			if (value != m_sColor)
			{
				m_sColor = value;
				m_bGeometryValid = false;
				if (m_bVisible)
					m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CView::CGrid::FreeResources(COpenGL *graphics)
		{
			if (m_pVertexArray)
			{
				m_pVertexArray->Release();
				m_pVertexArray = nullptr;
				m_bGeometryValid = false;
			}
			if (m_pProgram)
			{
				m_pProgram->Release();
				m_pProgram = nullptr;
				m_bProgramValid = false;
			}
		}
	#pragma endregion

	#pragma region Render
		void CView::CGrid::Render(COpenGL *graphics, ICamera *camera)
		{
			if (m_bVisible)
			{
				// Create OpenGL objects if not exist and activate them
				IRenderer *renderer{ m_pControl->getForm()->getRenderer() };
				if (!m_pVertexArray)
				{
					if (!(m_pVertexArray = renderer->CreateVertexArray(m_sVertexFormat)))
						return;
				}
				if (!m_bGeometryValid)
				{
					size_t xsize{ size_t(m_fXRange / m_fStep) }, zsize{ size_t(m_fZRange / m_fStep) }, index{ 0 };
					float x{ m_fStep }, z{ m_fStep };
					m_pVertexArray->setPolygonCount(2 * (1 + xsize + zsize), 2);
					m_pVertexArray->getPolygon(index)->getVertex(0)->setPosition3D(Vec3f{ 0, 0, m_fZRange });
					m_pVertexArray->getPolygon(index)->getVertex(1)->setPosition3D(Vec3f{ 0, 0, -m_fZRange });
					index++;
					for (size_t i = 1; i <= xsize; i++, x += m_fStep)
					{
						m_pVertexArray->getPolygon(index)->getVertex(0)->setPosition3D(Vec3f{ x, 0, m_fZRange });
						m_pVertexArray->getPolygon(index)->getVertex(1)->setPosition3D(Vec3f{ x, 0, -m_fZRange });
						index++;
						m_pVertexArray->getPolygon(index)->getVertex(0)->setPosition3D(Vec3f{ -x, 0, m_fZRange });
						m_pVertexArray->getPolygon(index)->getVertex(1)->setPosition3D(Vec3f{ -x, 0, -m_fZRange });
						index++;
					}
					m_pVertexArray->getPolygon(index)->getVertex(0)->setPosition3D(Vec3f{ m_fXRange, 0, 0 });
					m_pVertexArray->getPolygon(index)->getVertex(1)->setPosition3D(Vec3f{ -m_fXRange, 0, 0 });
					index++;
					for (size_t i = 1; i <= zsize; i++, z += m_fStep)
					{
						m_pVertexArray->getPolygon(index)->getVertex(0)->setPosition3D(Vec3f{ m_fXRange, 0, z });
						m_pVertexArray->getPolygon(index)->getVertex(1)->setPosition3D(Vec3f{ -m_fXRange, 0, z });
						index++;
						m_pVertexArray->getPolygon(index)->getVertex(0)->setPosition3D(Vec3f{ m_fXRange, 0, -z });
						m_pVertexArray->getPolygon(index)->getVertex(1)->setPosition3D(Vec3f{ -m_fXRange, 0, -z });
						index++;
					}

					m_bGeometryValid = true;
				}
				
				CStoreProgram s_program{ renderer };
				if (!m_pProgram)
				{
					if (!(m_pProgram = renderer->CreateProgram(m_sVertexShader, m_sFragmentShader)))
						return;
					m_bProgramValid = true;
					renderer->ActivateProgram(m_pProgram);
					if ((*reinterpret_cast<GLint*>(&m_hUniformMatrix) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Matrix")) < 0)
						m_bProgramValid = false;
					if ((*reinterpret_cast<GLint*>(&m_hUniformColor) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Color")) < 0)
						m_bProgramValid = false;
				}
				if (m_bProgramValid)
				{
					renderer->ActivateProgram(m_pProgram);
					graphics->Uniform4f(*reinterpret_cast<GLint*>(&m_hUniformColor), m_sColor.R / 255.0f, m_sColor.G / 255.0f, m_sColor.B / 255.0f, m_sColor.A / 255.0f);
					graphics->UniformMatrix4fv(*reinterpret_cast<GLint*>(&m_hUniformMatrix), 1, GL_TRUE, camera->getMatrix().Data);
					CStoreVertexArray s_va{ renderer };
					renderer->ActivateVertexArray(m_pVertexArray);
					m_pVertexArray->RenderLines();
				}
			}
		}
	#pragma endregion
	}
}