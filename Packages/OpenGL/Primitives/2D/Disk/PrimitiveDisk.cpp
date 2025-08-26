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
		CPrimitiveDisk::CPrimitiveDisk(IControl *control) :
			CModel(false, false),
			m_fOuterRadius{ 5 },
			m_fInnerRadius{ 3 },
			m_iSides{ 32 },
			m_iSegments{ 1 },
			m_pControl{ control },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		void CPrimitiveDisk::FreeResources()
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
		bool CPrimitiveDisk::setOuterRadius(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fOuterRadius))
			{
				m_fOuterRadius = value;
				m_bValid = false;
				return true;
			}
			return false;
		}
		bool CPrimitiveDisk::setInnerRadius(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fInnerRadius))
			{
				m_fInnerRadius = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveDisk::setSides(const int value)
		{
			if (value >= 3 && value != m_iSides)
			{
				m_iSides = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveDisk::setSegments(const int value)
		{
			if (value >= 1 && value != m_iSegments)
			{
				m_iSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveDisk::setSize(const float outer_radius, const float inner_radius, const int sides)
		{
			if (ntl::IsGreater<float>(outer_radius, 0) && ntl::IsGreater<float>(inner_radius, 0) && ntl::IsGreater<float>(outer_radius, inner_radius) && sides >= 3)
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
		void CPrimitiveDisk::UpdateGeometry()
		{
			m_pVertexArray->Clear();
			float d{ m_fInnerRadius / m_fOuterRadius };
			IPolygon *p;
			for (int i = 0; i < m_iSides; i++)
			{
				float a1{ i * 2 * ntl::Pi<float> / m_iSides }, b1{ 2 * ntl::Pi<float> - a1 };
				float a2{ (i + 1) * 2 * ntl::Pi<float> / m_iSides }, b2{ 2 * ntl::Pi<float> - a2 };
				for (int t = 0; t < m_iSegments; t++)
				{
					float rb{ m_fOuterRadius - t * (m_fOuterRadius - m_fInnerRadius) / m_iSegments };
					float rs{ m_fOuterRadius - (t + 1) * (m_fOuterRadius - m_fInnerRadius) / m_iSegments };
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a2), 0, rb * std::sin(a2) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(a2) + m_fOuterRadius) / (2 * m_fOuterRadius), 1 - (rb * std::sin(a2) + m_fOuterRadius) / (2 * m_fOuterRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a2), 0, rs * std::sin(a2) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(a2) + m_fOuterRadius) / (2 * m_fOuterRadius), 1 - (rs * std::sin(a2) + m_fOuterRadius) / (2 * m_fOuterRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a1), 0, rs * std::sin(a1) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(a1) + m_fOuterRadius) / (2 * m_fOuterRadius), 1 - (rs * std::sin(a1) + m_fOuterRadius) / (2 * m_fOuterRadius) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a1), 0, rb * std::sin(a1) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(a1) + m_fOuterRadius) / (2 * m_fOuterRadius), 1 - (rb * std::sin(a1) + m_fOuterRadius) / (2 * m_fOuterRadius) });
				}
			}
		}
	#pragma endregion

	#pragma region Render
		bool CPrimitiveDisk::Render()
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