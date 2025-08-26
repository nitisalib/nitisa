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
		const AnsiString CView::CAxes::m_sVertexShader{
			"#version 140\n"

			"in vec3 in_Position;\n"
			"in vec4 in_Color;\n"

			"uniform mat4 app_Matrix;\n"

			"out vec4 var_Color;\n"

			"void main()\n"
			"{\n"
			"	gl_Position = app_Matrix * vec4(in_Position, 1);\n"
			"	var_Color = in_Color;\n"
			"}\n"
		};

		const AnsiString CView::CAxes::m_sFragmentShader{
			"#version 140\n"

			"in vec4 var_Color;\n"

			"out vec4 FragColor;\n"

			"void main()\n"
			"{\n"
			"	FragColor = var_Color;\n"
			"}\n"
		};
	#pragma endregion

		const nitisa::VertexFormat CView::CAxes::m_sVertexFormat{
			0, 0, 1, 1,
			0, 0, 0, 0,
			nitisa::VertexFormat::npos, nitisa::VertexFormat::npos, nitisa::VertexFormat::npos, nitisa::VertexFormat::npos, nitisa::VertexFormat::npos, 0, nitisa::VertexFormat::npos, 0 };

	#pragma region Constructor & destructor
		CView::CAxes::CAxes(CView *control):
			m_pControl{ control },
			m_bShowX{ true },
			m_bShowY{ true },
			m_bShowZ{ true },
			m_sXRange{ 0, 50 },
			m_sYRange{ 0, 10 },
			m_sZRange{ 0, 50 },
			m_sXColor{ 255, 0, 0, 255 },
			m_sYColor{ 0, 255, 0, 255 },
			m_sZColor{ 0, 0, 255, 255 },
			m_pVertexArray{ nullptr },
			m_pProgram{ nullptr },
			m_bGeometryValid{ false },
			m_bProgramValid{ false }
		{

		}
	#pragma endregion

	#pragma region Getters
		bool CView::CAxes::isShowX() const
		{
			return m_bShowX;
		}

		bool CView::CAxes::isShowY() const
		{
			return m_bShowY;
		}

		bool CView::CAxes::isShowZ() const
		{
			return m_bShowZ;
		}

		PointF CView::CAxes::getXRange() const
		{
			return m_sXRange;
		}

		PointF CView::CAxes::getYRange() const
		{
			return m_sYRange;
		}

		PointF CView::CAxes::getZRange() const
		{
			return m_sZRange;
		}

		Color CView::CAxes::getXColor() const
		{
			return m_sXColor;
		}

		Color CView::CAxes::getYColor() const
		{
			return m_sYColor;
		}

		Color CView::CAxes::getZColor() const
		{
			return m_sZColor;
		}
	#pragma endregion

	#pragma region Setters
		bool CView::CAxes::setShowX(const bool value)
		{
			if (value != m_bShowX)
			{
				m_bShowX = value;
				m_bGeometryValid = false;
				m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}

		bool CView::CAxes::setShowY(const bool value)
		{
			if (value != m_bShowY)
			{
				m_bShowY = value;
				m_bGeometryValid = false;
				m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}

		bool CView::CAxes::setShowZ(const bool value)
		{
			if (value != m_bShowZ)
			{
				m_bShowZ = value;
				m_bGeometryValid = false;
				m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}

		bool CView::CAxes::setXRange(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.Y, value.X) && IsNotEqual(value, m_sXRange))
			{
				m_sXRange = value;
				if (m_bShowX)
				{
					m_bGeometryValid = false;
					m_pControl->ForceUpdate();
				}
				return true;
			}
			return false;
		}

		bool CView::CAxes::setYRange(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.Y, value.X) && IsNotEqual(value, m_sYRange))
			{
				m_sYRange = value;
				if (m_bShowY)
				{
					m_bGeometryValid = false;
					m_pControl->ForceUpdate();
				}
				return true;
			}
			return false;
		}

		bool CView::CAxes::setZRange(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.Y, value.X) && IsNotEqual(value, m_sZRange))
			{
				m_sZRange = value;
				if (m_bShowZ)
				{
					m_bGeometryValid = false;
					m_pControl->ForceUpdate();
				}
				return true;
			}
			return false;
		}

		bool CView::CAxes::setXColor(const Color &value)
		{
			if (value != m_sXColor)
			{
				m_sXColor = value;
				if (m_bShowX)
					m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}

		bool CView::CAxes::setYColor(const Color &value)
		{
			if (value != m_sYColor)
			{
				m_sYColor = value;
				if (m_bShowY)
					m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}

		bool CView::CAxes::setZColor(const Color &value)
		{
			if (value != m_sZColor)
			{
				m_sZColor = value;
				if (m_bShowZ)
					m_pControl->ForceUpdate();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CView::CAxes::FreeResources(COpenGL *graphics)
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
		void CView::CAxes::Render(COpenGL *graphics, ICamera *camera)
		{
			if (m_bShowX || m_bShowY || m_bShowZ)
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
					size_t index{ 0 };
					m_pVertexArray->setPolygonCount((m_bShowX ? 1 : 0) + (m_bShowY ? 1 : 0) + (m_bShowZ ? 1 : 0), 2);
					if (m_bShowX)
					{
						m_pVertexArray
							->getPolygon(index)
							->getVertex(0)
							->putPosition3D(Vec3f{ m_sXRange.X, 0, 0 })
							->putColor(Vec4f{ m_sXColor.R / 255.0f, m_sXColor.G / 255.0f, m_sXColor.B / 255.0f, m_sXColor.A / 255.0f });
						m_pVertexArray
							->getPolygon(index)
							->getVertex(1)
							->putPosition3D(Vec3f{ m_sXRange.Y, 0, 0 })
							->putColor(Vec4f{ m_sXColor.R / 255.0f, m_sXColor.G / 255.0f, m_sXColor.B / 255.0f, m_sXColor.A / 255.0f });
						index++;
					}
					if (m_bShowY)
					{
						m_pVertexArray
							->getPolygon(index)
							->getVertex(0)
							->putPosition3D(Vec3f{ 0, m_sYRange.X, 0 })
							->putColor(Vec4f{ m_sYColor.R / 255.0f, m_sYColor.G / 255.0f, m_sYColor.B / 255.0f, m_sYColor.A / 255.0f });
						m_pVertexArray
							->getPolygon(index)
							->getVertex(1)
							->putPosition3D(Vec3f{ 0, m_sYRange.Y, 0 })
							->putColor(Vec4f{ m_sYColor.R / 255.0f, m_sYColor.G / 255.0f, m_sYColor.B / 255.0f, m_sYColor.A / 255.0f });
						index++;
					}
					if (m_bShowZ)
					{
						m_pVertexArray
							->getPolygon(index)
							->getVertex(0)
							->putPosition3D(Vec3f{ 0, 0, m_sZRange.X })
							->putColor(Vec4f{ m_sZColor.R / 255.0f, m_sZColor.G / 255.0f, m_sZColor.B / 255.0f, m_sZColor.A / 255.0f });
						m_pVertexArray
							->getPolygon(index)
							->getVertex(1)
							->putPosition3D(Vec3f{ 0, 0, m_sZRange.Y })
							->putColor(Vec4f{ m_sZColor.R / 255.0f, m_sZColor.G / 255.0f, m_sZColor.B / 255.0f, m_sZColor.A / 255.0f });
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
				}
				if (m_bProgramValid)
				{
					renderer->ActivateProgram(m_pProgram);
					graphics->UniformMatrix4fv(*reinterpret_cast<GLint*>(&m_hUniformMatrix), 1, GL_TRUE, camera->getMatrix().Data);
					CStoreVertexArray s_va{ renderer };
					renderer->ActivateVertexArray(m_pVertexArray);
					graphics->DepthFunc(GL_ALWAYS);
					m_pVertexArray->RenderLines();
					graphics->DepthFunc(GL_LESS);
				}
			}
		}
	#pragma endregion
	}
}