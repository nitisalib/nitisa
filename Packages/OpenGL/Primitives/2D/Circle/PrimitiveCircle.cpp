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
		CPrimitiveCircle::CPrimitiveCircle(IControl *control) :
			CModel(false, false),
			m_fRadius{ 5 },
			m_iSides{ 32 },
			m_iSegments{ 1 },
			m_pControl{ control },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		void CPrimitiveCircle::FreeResources()
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
		bool CPrimitiveCircle::setRadius(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRadius))
			{
				m_fRadius = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCircle::setSides(const int value)
		{
			if (value >= 3 && value != m_iSides)
			{
				m_iSides = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCircle::setSegments(const int value)
		{
			if (value >= 1 && value != m_iSegments)
			{
				m_iSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCircle::setSize(const float radius, const int sides)
		{
			if (ntl::IsGreater<float>(radius, 0) && sides >= 3)
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
		void CPrimitiveCircle::UpdateGeometry()
		{
			m_pVertexArray->Clear();
			float rb, rs;
			IPolygon *top{ m_pVertexArray->AddPolygon() }, *p;
			top->AddVertex()
				->putPosition3D(Vec3f{ 0, 0, 0 })
				->putNormal(Vec3f{ 0, 1, 0 })
				->putTextureCoords(Vec2f{ 0.5f, 0.5f });
			for (int i = 0; i < m_iSides; i++)
			{
				float a1{ i * 2 * ntl::Pi<float> / m_iSides }, b1{ 2 * ntl::Pi<float> - a1 };
				float a2{ (i + 1) * 2 * ntl::Pi<float> / m_iSides }, b2{ 2 * ntl::Pi<float> - a2 };
				for (int t = 0; t < m_iSegments - 1; t++)
				{
					rb = m_fRadius - t * m_fRadius / m_iSegments;
					rs = m_fRadius - (t + 1) * m_fRadius / m_iSegments;
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a2), 0, rb * std::sin(a2) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(a2) + m_fRadius) / (2 * m_fRadius), 1 - (rb * std::sin(a2) + m_fRadius) / (2 * m_fRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a2), 0, rs * std::sin(a2) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(a2) + m_fRadius) / (2 * m_fRadius), 1 - (rs * std::sin(a2) + m_fRadius) / (2 * m_fRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a1), 0, rs * std::sin(a1) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(a1) + m_fRadius) / (2 * m_fRadius), 1 - (rs * std::sin(a1) + m_fRadius) / (2 * m_fRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a1), 0, rb * std::sin(a1) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(a1) + m_fRadius) / (2 * m_fRadius), 1 - (rb * std::sin(a1) + m_fRadius) / (2 * m_fRadius) });
				}
				rs = m_fRadius - (m_iSegments - 1) * m_fRadius / m_iSegments;
				top->AddVertex()
					->putPosition3D(Vec3f{ rs * std::cos(a1), 0, rs * std::sin(a1) })
					->putNormal(Vec3f{ 0, 1, 0 })
					->putTextureCoords(Vec2f{ (rs * std::cos(a1) + m_fRadius) / (2 * m_fRadius), 1 - (rs * std::sin(a1) + m_fRadius) / (2 * m_fRadius) });
			}
			rs = m_fRadius - (m_iSegments - 1) * m_fRadius / m_iSegments;
			top->AddVertex()
				->putPosition3D(Vec3f{ rs, 0, 0 })
				->putNormal(Vec3f{ 0, 1, 0 })
				->putTextureCoords(Vec2f{ (rs + m_fRadius) / (2 * m_fRadius), 0.5f });
		}
	#pragma endregion

	#pragma region Render
		bool CPrimitiveCircle::Render()
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