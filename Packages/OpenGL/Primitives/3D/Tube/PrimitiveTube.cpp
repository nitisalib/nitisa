// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace opengl
	{
	#pragma region Constructor & destructor
		CPrimitiveTube::CPrimitiveTube(IControl *control) :
			CModel(false, false),
			m_fOuterRadius{ 5 },
			m_fInnerRadius{ 3 },
			m_fHeight{ 10 },
			m_iSides{ 32 },
			m_iCapSegments{ 1 },
			m_iHeightSegments{ 1 },
			m_pControl{ control },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		void CPrimitiveTube::FreeResources()
		{
			if (m_pVertexArray)
			{
				m_pVertexArray->Release();
				m_pVertexArray = nullptr;
				m_bValid = false;
			}
		}
	#pragma endregion

	#pragma region Setters
		bool CPrimitiveTube::setOuterRadius(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsGreater<float>(value, m_fInnerRadius) && ntl::IsNotEqual<float>(value, m_fOuterRadius))
			{
				m_fOuterRadius = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveTube::setInnerRadius(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsLess<float>(value, m_fOuterRadius) && ntl::IsNotEqual<float>(value, m_fInnerRadius))
			{
				m_fInnerRadius = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveTube::setHeight(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fHeight))
			{
				m_fHeight = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveTube::setSides(const int value)
		{
			if (value >= 3 && value != m_iSides)
			{
				m_iSides = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveTube::setSize(const float outer_radius, const float inner_radius, const float height, const int sides)
		{
			if (ntl::IsGreater<float>(outer_radius, 0) && ntl::IsGreater<float>(inner_radius, 0) && ntl::IsGreater<float>(outer_radius, inner_radius) && ntl::IsGreater<float>(height, 0) && sides >= 3)
			{
				bool changed{ false };
				if (ntl::IsNotEqual<float>(outer_radius, m_fOuterRadius))
				{
					m_fOuterRadius = outer_radius;
					changed = true;
				}
				if (ntl::IsNotEqual<float>(inner_radius, m_fInnerRadius))
				{
					m_fInnerRadius = inner_radius;
					changed = true;
				}
				if (ntl::IsNotEqual<float>(height, m_fHeight))
				{
					m_fHeight = height;
					changed = true;
				}
				if (sides != m_iSides)
				{
					m_iSides = sides;
					changed = true;
				}
				if (changed)
				{
					m_bValid = false;
					return true;
				}
			}
			return false;
		}

		bool CPrimitiveTube::setCapSegments(const int value)
		{
			if (value >= 1 && value != m_iCapSegments)
			{
				m_iCapSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveTube::setHeightSegments(const int value)
		{
			if (value >= 1 && value != m_iHeightSegments)
			{
				m_iHeightSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveTube::setSegments(const int cap, const int height)
		{
			if (cap >= 1 && height >= 1)
			{
				bool changed{ false };
				if (cap != m_iCapSegments)
				{
					m_iCapSegments = cap;
					changed = true;
				}
				if (height != m_iHeightSegments)
				{
					m_iHeightSegments = height;
					changed = true;
				}
				if (changed)
				{
					m_bValid = false;
					return true;
				}
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CPrimitiveTube::UpdateGeometry()
		{
			m_pVertexArray->Clear();
			float d{ m_fInnerRadius / m_fOuterRadius };
			IPolygon *p;
			for (int i = 0; i < m_iSides; i++)
			{
				float a1{ i * 2 * ntl::Pi<float> / m_iSides }, b1{ 2 * ntl::Pi<float> - a1 };
				float a2{ (i + 1) * 2 * ntl::Pi<float> / m_iSides }, b2{ 2 * ntl::Pi<float> - a2 };
				for (int y = 0; y < m_iHeightSegments; y++)
				{
					// Outer
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fOuterRadius * std::cos(a2), -m_fHeight / 2 + y * m_fHeight / m_iHeightSegments, m_fOuterRadius * std::sin(a2) })
						->putNormal(Vec3f{ std::cos(a2), 0, std::sin(a2) })
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, y / (float)m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fOuterRadius * std::cos(a2), -m_fHeight / 2 + (y + 1) * m_fHeight / m_iHeightSegments, m_fOuterRadius * std::sin(a2) })
						->putNormal(Vec3f{ std::cos(a2), 0, std::sin(a2) })
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, (y + 1) / (float)m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fOuterRadius * std::cos(a1), -m_fHeight / 2 + (y + 1) * m_fHeight / m_iHeightSegments, m_fOuterRadius * std::sin(a1) })
						->putNormal(Vec3f{ std::cos(a1), 0, std::sin(a1) })
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, (y + 1) / (float)m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fOuterRadius * std::cos(a1), -m_fHeight / 2 + y * m_fHeight / m_iHeightSegments, m_fOuterRadius * std::sin(a1) })
						->putNormal(Vec3f{ std::cos(a1), 0, std::sin(a1) })
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, y / (float)m_iHeightSegments });
					// Inner
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fInnerRadius * std::cos(b2), -m_fHeight / 2 + y * m_fHeight / m_iHeightSegments, m_fInnerRadius * std::sin(b2) })
						->putNormal(Vec3f{ -std::cos(b2), 0, -std::sin(b2) })
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, y / (float)m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fInnerRadius * std::cos(b2), -m_fHeight / 2 + (y + 1) * m_fHeight / m_iHeightSegments, m_fInnerRadius * std::sin(b2) })
						->putNormal(Vec3f{ -std::cos(b2), 0, -std::sin(b2) })
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, (y + 1) / (float)m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fInnerRadius * std::cos(b1), -m_fHeight / 2 + (y + 1) * m_fHeight / m_iHeightSegments, m_fInnerRadius * std::sin(b1) })
						->putNormal(Vec3f{ -std::cos(b1), 0, -std::sin(b1) })
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, (y + 1) / (float)m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fInnerRadius * std::cos(b1), -m_fHeight / 2 + y * m_fHeight / m_iHeightSegments, m_fInnerRadius * std::sin(b1) })
						->putNormal(Vec3f{ -std::cos(b1), 0, -std::sin(b1) })
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, y / (float)m_iHeightSegments });
				}
				for (int t = 0; t < m_iCapSegments; t++)
				{
					float rb{ m_fOuterRadius - t * (m_fOuterRadius - m_fInnerRadius) / m_iCapSegments };
					float rs{ m_fOuterRadius - (t + 1) * (m_fOuterRadius - m_fInnerRadius) / m_iCapSegments };
					// Top
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a2), m_fHeight / 2, rb * std::sin(a2) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(a2) + m_fOuterRadius) / (2 * m_fOuterRadius), 1 - (rb * std::sin(a2) + m_fOuterRadius) / (2 * m_fOuterRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a2), m_fHeight / 2, rs * std::sin(a2) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(a2) + m_fOuterRadius) / (2 * m_fOuterRadius), 1 - (rs * std::sin(a2) + m_fOuterRadius) / (2 * m_fOuterRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a1), m_fHeight / 2, rs * std::sin(a1) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(a1) + m_fOuterRadius) / (2 * m_fOuterRadius), 1 - (rs * std::sin(a1) + m_fOuterRadius) / (2 * m_fOuterRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a1), m_fHeight / 2, rb * std::sin(a1) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(a1) + m_fOuterRadius) / (2 * m_fOuterRadius), 1 - (rb * std::sin(a1) + m_fOuterRadius) / (2 * m_fOuterRadius) });
					// Bottom
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(b2), -m_fHeight / 2, rb * std::sin(b2) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(b2) + m_fOuterRadius) / (2 * m_fOuterRadius), (rb * std::sin(b2) + m_fOuterRadius) / (2 * m_fOuterRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(b2), -m_fHeight / 2, rs * std::sin(b2) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(b2) + m_fOuterRadius) / (2 * m_fOuterRadius), (rs * std::sin(b2) + m_fOuterRadius) / (2 * m_fOuterRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(b1), -m_fHeight / 2, rs * std::sin(b1) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(b1) + m_fOuterRadius) / (2 * m_fOuterRadius), (rs * std::sin(b1) + m_fOuterRadius) / (2 * m_fOuterRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(b1), -m_fHeight / 2, rb * std::sin(b1) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(b1) + m_fOuterRadius) / (2 * m_fOuterRadius), (rb * std::sin(b1) + m_fOuterRadius) / (2 * m_fOuterRadius) });
				}
			}
		}
	#pragma endregion

	#pragma region Render
		bool CPrimitiveTube::Render()
		{
			IRenderer *renderer{ m_pControl->getForm()->getRenderer() };
			if (!m_pVertexArray)
			{
				if (!(m_pVertexArray = renderer->CreateVertexArray(VertexFormat)))
					return false;
			}
			if (!m_bValid)
			{
				UpdateGeometry();
				m_bValid = true;
			}
			IVertexArray *old{ renderer->ActiveVertexArray };
			renderer->ActivateVertexArray(m_pVertexArray);
			m_pVertexArray->RenderPolygons();
			renderer->ActivateVertexArray(old);
			return true;
		}
	#pragma endregion
	}
}