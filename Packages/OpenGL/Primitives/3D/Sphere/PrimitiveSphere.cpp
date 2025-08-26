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
		CPrimitiveSphere::CPrimitiveSphere(IControl *control) :
			CModel(false, false),
			m_fRadius{ 5 },
			m_iSides{ 32 },
			m_iYSides{ 32 },
			m_pControl{ control },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		void CPrimitiveSphere::FreeResources()
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
		bool CPrimitiveSphere::setRadius(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRadius))
			{
				m_fRadius = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveSphere::setSides(const int value)
		{
			if (value >= 3 && value != m_iSides)
			{
				m_iSides = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveSphere::setYSides(const int value)
		{
			if (value >= 2 && value != m_iYSides)
			{
				m_iYSides = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveSphere::setSize(const float radius, const int sides, const int y_sides)
		{
			if (ntl::IsGreater<float>(radius, 0) && sides >= 3 && y_sides >= 2)
			{
				bool changed{ false };
				if (ntl::IsNotEqual<float>(radius, m_fRadius))
				{
					m_fRadius = radius;
					changed = true;
				}
				if (sides != m_iSides)
				{
					m_iSides = sides;
					changed = true;
				}
				if (sides != m_iYSides)
				{
					m_iYSides = sides;
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
		void CPrimitiveSphere::UpdateGeometry()
		{
			m_pVertexArray->Clear();
			Vec3f n1, n2, n3, n4;
			float a1, a2, a3, a4, b1, b2, b3, b4;
			IPolygon *p;
			for (int i = 0; i < m_iSides; i++)
			{
				a1 = i * 2 * ntl::Pi<float> / m_iSides;
				a2 = (i + 1) * 2 * ntl::Pi<float> / m_iSides;
				b1 = 2 * ntl::Pi<float> - a1;
				b2 = 2 * ntl::Pi<float> - a2;
				for (int j = 0; j < m_iYSides - 2; j++)
				{
					a3 = (j + 1) * ntl::Pi<float> / m_iYSides;
					a4 = (j + 2) * ntl::Pi<float> / m_iYSides;
					b3 = ntl::Pi<float> - a3;
					b4 = ntl::Pi<float> - a4;
					n1 = Vec3f{ std::cos(a2) * std::sin(a4), std::cos(a4), std::sin(a2) * std::sin(a4) };
					ntl::Normalize<float>(n1);
					n2 = Vec3f{ std::cos(a2) * std::sin(a3), std::cos(a3), std::sin(a2) * std::sin(a3) };
					ntl::Normalize<float>(n2);
					n3 = Vec3f{ std::cos(a1) * std::sin(a3), std::cos(a3), std::sin(a1) * std::sin(a3) };
					ntl::Normalize<float>(n3);
					n4 = Vec3f{ std::cos(a1) * std::sin(a4), std::cos(a4), std::sin(a1) * std::sin(a4) };
					ntl::Normalize<float>(n4);
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(n1 * m_fRadius)
						->putNormal(n1)
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, 0.5f + std::cos(a4) / 2 });
					p->AddVertex()
						->putPosition3D(n2 * m_fRadius)
						->putNormal(n2)
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, 0.5f + std::cos(a3) / 2 });
					p->AddVertex()
						->putPosition3D(n3 * m_fRadius)
						->putNormal(n3)
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, 0.5f + std::cos(a3) / 2 });
					p->AddVertex()
						->putPosition3D(n4 * m_fRadius)
						->putNormal(n4)
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, 0.5f + std::cos(a4) / 2 });
				}
				a3 = ntl::Pi<float> / m_iYSides;
				b3 = ntl::Pi<float> - a3;
				n1 = Vec3f{ std::cos(a2) * std::sin(a3), std::cos(a3), std::sin(a2) * std::sin(a3) };
				n3 = Vec3f{ std::cos(a1) * std::sin(a3), std::cos(a3), std::sin(a1) * std::sin(a3) };
				// Top
				p = m_pVertexArray->AddPolygon();
				p->AddVertex()
					->putPosition3D(n1 * m_fRadius)
					->putNormal(n1)
					->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, 0.5f + std::cos(a3) / 2 });
				p->AddVertex()
					->putPosition3D(Vec3f{ 0, m_fRadius, 0 })
					->putNormal(Vec3f{ 0, 1, 0 })
					->putTextureCoords(Vec2f{ 1 - (i + 0.5f) / (float)m_iSides, 1 });
				p->AddVertex()
					->putPosition3D(n3 * m_fRadius)
					->putNormal(n3)
					->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, 0.5f + std::cos(a3) / 2 });
				a3 = (m_iYSides - 1) * ntl::Pi<float> / m_iYSides;
				n1 = Vec3f{ std::cos(a1) * std::sin(a3), std::cos(a3), std::sin(a1) * std::sin(a3) };
				n3 = Vec3f{ std::cos(a2) * std::sin(a3), std::cos(a3), std::sin(a2) * std::sin(a3) };
				// Bottom
				p = m_pVertexArray->AddPolygon();
				p->AddVertex()
					->putPosition3D(n1 * m_fRadius)
					->putNormal(n1)
					->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, 0.5f + std::cos(a3) / 2 });
				p->AddVertex()
					->putPosition3D(Vec3f{ 0, -m_fRadius, 0 })
					->putNormal(Vec3f{ 0, -1, 0 })
					->putTextureCoords(Vec2f{ 1 - (i + 0.5f) / (float)m_iSides, 0 });
				p->AddVertex()
					->putPosition3D(n3 * m_fRadius)
					->putNormal(n3)
					->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, 0.5f + std::cos(a3) / 2 });
			}
		}
	#pragma endregion

	#pragma region Render
		bool CPrimitiveSphere::Render()
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