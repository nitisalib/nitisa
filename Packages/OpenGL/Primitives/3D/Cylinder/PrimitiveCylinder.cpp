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
		CPrimitiveCylinder::CPrimitiveCylinder(IControl *control) :
			CModel(false, false),
			m_fRadius{ 5 },
			m_fHeight{ 10 },
			m_iSides{ 32 },
			m_iCapSegments{ 1 },
			m_iHeightSegments{ 1 },
			m_pControl{ control },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		void CPrimitiveCylinder::FreeResources()
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
		bool CPrimitiveCylinder::setRadius(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRadius))
			{
				m_fRadius = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCylinder::setHeight(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fHeight))
			{
				m_fHeight = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCylinder::setSides(const int value)
		{
			if (value >= 3 && value != m_iSides)
			{
				m_iSides = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCylinder::setSize(const float radius, const float height, const int sides)
		{
			if (ntl::IsGreater<float>(radius, 0) && ntl::IsGreater<float>(height, 0) && sides >= 3)
			{
				bool changed{ false };
				if (ntl::IsNotEqual<float>(radius, m_fRadius))
				{
					m_fRadius = radius;
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

		bool CPrimitiveCylinder::setCapSegments(const int value)
		{
			if (value >= 1 && value != m_iCapSegments)
			{
				m_iCapSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCylinder::setHeightSegments(const int value)
		{
			if (value >= 1 && value != m_iHeightSegments)
			{
				m_iHeightSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCylinder::setSegments(const int cap, const int height)
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
		void CPrimitiveCylinder::UpdateGeometry()
		{
			m_pVertexArray->Clear();
			float h{ m_fHeight / m_iHeightSegments }, hs{ 1 / (float)m_iHeightSegments }, rb, rs;
			IPolygon *top{ m_pVertexArray->AddPolygon() }, *bottom{ m_pVertexArray->AddPolygon() }, *p;
			top->AddVertex()
				->putPosition3D(Vec3f{ 0, m_fHeight / 2, 0 })
				->putNormal(Vec3f{ 0, 1, 0 })
				->putTextureCoords(Vec2f{ 0.5f, 0.5f });
			bottom->AddVertex()
				->putPosition3D(Vec3f{ 0, -m_fHeight / 2, 0 })
				->putNormal(Vec3f{ 0, -1, 0 })
				->putTextureCoords(Vec2f{ 0.5f, 0.5f });
			for (int i = 0; i < m_iSides; i++)
			{
				float a1{ i * 2 * ntl::Pi<float> / m_iSides }, b1{ 2 * ntl::Pi<float> -a1 };
				float a2{ (i + 1) * 2 * ntl::Pi<float> / m_iSides }, b2{ 2 * ntl::Pi<float> -a2 };
				for (int y = 0; y < m_iHeightSegments; y++)
				{
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fRadius * std::cos(a2), -m_fHeight / 2 + y * h, m_fRadius * std::sin(a2) })
						->putNormal(Vec3f{ std::cos(a2), 0, std::sin(a2) })
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, y * hs });
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fRadius * std::cos(a2), -m_fHeight / 2 + (y + 1) * h, m_fRadius * std::sin(a2) })
						->putNormal(Vec3f{ std::cos(a2), 0, std::sin(a2) })
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, (y + 1) * hs });
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fRadius * std::cos(a1), -m_fHeight / 2 + (y + 1) * h, m_fRadius * std::sin(a1) })
						->putNormal(Vec3f{ std::cos(a1), 0, std::sin(a1) })
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, (y + 1) * hs });
					p->AddVertex()
						->putPosition3D(Vec3f{ m_fRadius * std::cos(a1), -m_fHeight / 2 + y * h, m_fRadius * std::sin(a1) })
						->putNormal(Vec3f{ std::cos(a1), 0, std::sin(a1) })
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, y * hs });
				}
				for (int t = 0; t < m_iCapSegments - 1; t++)
				{
					rb = m_fRadius - t * m_fRadius / m_iCapSegments;
					rs = m_fRadius - (t + 1) * m_fRadius / m_iCapSegments;
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a2), m_fHeight / 2, rb * std::sin(a2) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(a2) + m_fRadius) / (2 * m_fRadius), 1 - (rb * std::sin(a2) + m_fRadius) / (2 * m_fRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a2), m_fHeight / 2, rs * std::sin(a2) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(a2) + m_fRadius) / (2 * m_fRadius), 1 - (rs * std::sin(a2) + m_fRadius) / (2 * m_fRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a1), m_fHeight / 2, rs * std::sin(a1) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(a1) + m_fRadius) / (2 * m_fRadius), 1 - (rs * std::sin(a1) + m_fRadius) / (2 * m_fRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a1), m_fHeight / 2, rb * std::sin(a1) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(a1) + m_fRadius) / (2 * m_fRadius), 1 - (rb * std::sin(a1) + m_fRadius) / (2 * m_fRadius) });
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(b2), -m_fHeight / 2, rb * std::sin(b2) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(b2) + m_fRadius) / (2 * m_fRadius), (rb * std::sin(b2) + m_fRadius) / (2 * m_fRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(b2), -m_fHeight / 2, rs * std::sin(b2) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(b2) + m_fRadius) / (2 * m_fRadius), (rs * std::sin(b2) + m_fRadius) / (2 * m_fRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(b1), -m_fHeight / 2, rs * std::sin(b1) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(b1) + m_fRadius) / (2 * m_fRadius), (rs * std::sin(b1) + m_fRadius) / (2 * m_fRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(b1), -m_fHeight / 2, rb * std::sin(b1) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(b1) + m_fRadius) / (2 * m_fRadius), (rb * std::sin(b1) + m_fRadius) / (2 * m_fRadius) });
				}
				rs = m_fRadius - (m_iCapSegments - 1) * m_fRadius / m_iCapSegments;
				top->AddVertex()
					->putPosition3D(Vec3f{ rs * std::cos(a1), m_fHeight / 2, rs * std::sin(a1) })
					->putNormal(Vec3f{ 0, 1, 0 })
					->putTextureCoords(Vec2f{ (rs * std::cos(a1) + m_fRadius) / (2 * m_fRadius), 1 - (rs * std::sin(a1) + m_fRadius) / (2 * m_fRadius) });
				bottom->AddVertex()
					->putPosition3D(Vec3f{ rs * std::cos(b1), -m_fHeight / 2, rs * std::sin(b1) })
					->putNormal(Vec3f{ 0, -1, 0 })
					->putTextureCoords(Vec2f{ (rs * std::cos(b1) + m_fRadius) / (2 * m_fRadius), (rs * std::sin(b1) + m_fRadius) / (2 * m_fRadius) });
			}
			rs = m_fRadius - (m_iCapSegments - 1) * m_fRadius / m_iCapSegments;
			top->AddVertex()
				->putPosition3D(Vec3f{ rs, m_fHeight / 2, 0 })
				->putNormal(Vec3f{ 0, 1, 0 })
				->putTextureCoords(Vec2f{ (rs + m_fRadius) / (2 * m_fRadius), 0.5f });
			bottom->AddVertex()
				->putPosition3D(Vec3f{ rs, -m_fHeight / 2, 0 })
				->putNormal(Vec3f{ 0, -1, 0 })
				->putTextureCoords(Vec2f{ (rs + m_fRadius) / (2 * m_fRadius), 0.5f });
		}
	#pragma endregion

	#pragma region Render
		bool CPrimitiveCylinder::Render()
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