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
		CPrimitiveTorus::CPrimitiveTorus(IControl *control) :
			CModel(false, false),
			m_fRadius1{ 5 },
			m_fRadius2{ 2 },
			m_iSides1{ 32 },
			m_iSides2{ 16 },
			m_pControl{ control },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		void CPrimitiveTorus::FreeResources()
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
		bool CPrimitiveTorus::setRadius1(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRadius1) && ntl::IsGreater<float>(value, m_fRadius2))
			{
				m_fRadius1 = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveTorus::setRadius2(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRadius2) && ntl::IsLess<float>(value, m_fRadius1))
			{
				m_fRadius2 = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveTorus::setSides1(const int value)
		{
			if (value >= 3 && value != m_iSides1)
			{
				m_iSides1 = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveTorus::setSides2(const int value)
		{
			if (value >= 3 && value != m_iSides2)
			{
				m_iSides2 = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveTorus::setSize(const float radius1, const float radius2, const int sides1, const int sides2)
		{
			if (ntl::IsGreater<float>(radius1, 0) && ntl::IsGreater<float>(radius2, 0) && ntl::IsGreater<float>(radius1, radius2) && sides1 >= 3 && sides2 >= 3)
			{
				bool changed{ false };
				if (ntl::IsNotEqual<float>(radius1, m_fRadius1))
				{
					m_fRadius1 = radius1;
					changed = true;
				}
				if (ntl::IsNotEqual<float>(radius2, m_fRadius2))
				{
					m_fRadius2 = radius2;
					changed = true;
				}
				if (sides1 != m_iSides1)
				{
					m_iSides1 = sides1;
					changed = true;
				}
				if (sides2 != m_iSides2)
				{
					m_iSides2 = sides2;
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
		void CPrimitiveTorus::UpdateGeometry()
		{
			m_pVertexArray->Clear();
			IPolygon *p;
			for (int a = 0; a < m_iSides1; a++)
			{
				float a1{ a * 2 * ntl::Pi<float> / m_iSides1 };
				float a2{ (a + 1) * 2 * ntl::Pi<float> / m_iSides1 };
				for (int b = 0; b < m_iSides2; b++)
				{
					float b1{ b * 2 * ntl::Pi<float> / m_iSides2 };
					float b2{ (b + 1) * 2 * ntl::Pi<float> / m_iSides2 };
					Vec3f p1{ (m_fRadius1 + m_fRadius2 * std::cos(b1)) * std::cos(a2), m_fRadius2 * std::sin(b1), (m_fRadius1 + m_fRadius2 * std::cos(b1)) * std::sin(a2) };
					Vec3f p2{ (m_fRadius1 + m_fRadius2 * std::cos(b2)) * std::cos(a2), m_fRadius2 * std::sin(b2), (m_fRadius1 + m_fRadius2 * std::cos(b2)) * std::sin(a2) };
					Vec3f p3{ (m_fRadius1 + m_fRadius2 * std::cos(b2)) * std::cos(a1), m_fRadius2 * std::sin(b2), (m_fRadius1 + m_fRadius2 * std::cos(b2)) * std::sin(a1) };
					Vec3f p4{ (m_fRadius1 + m_fRadius2 * std::cos(b1)) * std::cos(a1), m_fRadius2 * std::sin(b1), (m_fRadius1 + m_fRadius2 * std::cos(b1)) * std::sin(a1) };
					Vec3f v1{ m_fRadius1 * std::cos(a2), 0, m_fRadius1 * std::sin(a2) };
					Vec3f v2{ m_fRadius1 * std::cos(a1), 0, m_fRadius1 * std::sin(a1) };
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(p1)
						->putNormal(ntl::Normalized<float>(p1 - v1))
						->putTextureCoords(Vec2f{ 1 - (a + 1) / (float)m_iSides1, b / (float)m_iSides2 });
					p->AddVertex()
						->putPosition3D(p2)
						->putNormal(ntl::Normalized<float>(p2 - v1))
						->putTextureCoords(Vec2f{ 1 - (a + 1) / (float)m_iSides1, (b + 1) / (float)m_iSides2 });
					p->AddVertex()
						->putPosition3D(p3)
						->putNormal(ntl::Normalized<float>(p3 - v2))
						->putTextureCoords(Vec2f{ 1 - a / (float)m_iSides1, (b + 1) / (float)m_iSides2 });
					p->AddVertex()
						->putPosition3D(p4)
						->putNormal(ntl::Normalized<float>(p4 - v2))
						->putTextureCoords(Vec2f{ 1 - a / (float)m_iSides1, b / (float)m_iSides2 });
				}
			}
		}
	#pragma endregion

	#pragma region Render
		bool CPrimitiveTorus::Render()
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