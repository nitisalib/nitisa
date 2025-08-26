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
		CPrimitiveCone::CPrimitiveCone(IControl *control) :
			CModel(false, false),
			m_fRadius1{ 5 },
			m_fRadius2{ 0 },
			m_fHeight{ 10 },
			m_iSides{ 32 },
			m_iCapSegments{ 1 },
			m_iHeightSegments{ 1 },
			m_pControl{ control },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		void CPrimitiveCone::FreeResources()
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
		bool CPrimitiveCone::setRadius1(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRadius1))
			{
				m_fRadius1 = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCone::setRadius2(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRadius2))
			{
				m_fRadius2 = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCone::setHeight(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fHeight))
			{
				m_fHeight = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCone::setSides(const int value)
		{
			if (value >= 3 && value != m_iSides)
			{
				m_iSides = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCone::setSize(const float radius1, const float radius2, const float height, const int sides)
		{
			if (ntl::IsGreater<float>(radius1, 0) && ntl::IsGreaterOrEqual<float>(radius2, 0) && ntl::IsGreater<float>(height, 0) && sides >= 3)
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

		bool CPrimitiveCone::setCapSegments(const int value)
		{
			if (value >= 1 && value != m_iCapSegments)
			{
				m_iCapSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCone::setHeightSegments(const int value)
		{
			if (value >= 1 && value != m_iHeightSegments)
			{
				m_iHeightSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveCone::setSegments(const int cap, const int height)
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
		void CPrimitiveCone::UpdateGeometry()
		{
			m_pVertexArray->Clear();
			IPolygon *top{ m_pVertexArray->AddPolygon() }, *bottom{ m_pVertexArray->AddPolygon() }, *p;
			top->AddVertex()
				->putPosition3D(Vec3f{ 0, m_fHeight / 2, 0 })
				->putNormal(Vec3f{ 0, 1, 0 })
				->putTextureCoords(Vec2f{ 0.5f, 0.5f });
			bottom->AddVertex()
				->putPosition3D(Vec3f{ 0, -m_fHeight / 2, 0 })
				->putNormal(Vec3f{ 0, -1, 0 })
				->putTextureCoords(Vec2f{ 0.5f, 0.5f });
			float ny{ (m_fRadius1 - m_fRadius2) * m_fHeight / (m_fHeight * m_fHeight + (m_fRadius1 - m_fRadius2) * (m_fRadius1 - m_fRadius2)) }, rs, rb;
			Vec3f n1, n2, n3, n4;
			for (int i = 0; i < m_iSides; i++)
			{
				float a1{ i * 2 * ntl::Pi<float> / m_iSides }, b1{ 2 * ntl::Pi<float> - a1 };
				float a2{ (i + 1) * 2 * ntl::Pi<float> / m_iSides }, b2{ 2 * ntl::Pi<float> - a2 };
				for (int y = 0; y < m_iHeightSegments - 1; y++)
				{
					rs = m_fRadius1 - (y + 1) * (m_fRadius1 - m_fRadius2) / m_iHeightSegments;
					rb = m_fRadius1 - y * (m_fRadius1 - m_fRadius2) / m_iHeightSegments;
					n1 = Vec3f{ rb * std::cos(a2), ny, rb * std::sin(a2) };
					ntl::Normalize<float>(n1);
					n2 = Vec3f{ rs * std::cos(a2), ny, rs * std::sin(a2) };
					ntl::Normalize<float>(n2);
					n3 = Vec3f{ rs * std::cos(a1), ny, rs * std::sin(a1) };
					ntl::Normalize<float>(n3);
					n4 = Vec3f{ rb * std::cos(a1), ny, rb * std::sin(a1) };
					ntl::Normalize<float>(n4);
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a2), -m_fHeight / 2 + y * m_fHeight / m_iHeightSegments, rb * std::sin(a2) })
						->putNormal(n1)
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, y / (float)m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a2), -m_fHeight / 2 + (y + 1) * m_fHeight / m_iHeightSegments, rs * std::sin(a2) })
						->putNormal(n2)
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, (y + 1) / (float)m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a1), -m_fHeight / 2 + (y + 1) * m_fHeight / m_iHeightSegments, rs * std::sin(a1) })
						->putNormal(n3)
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, (y + 1) / (float)m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a1), -m_fHeight / 2 + y * m_fHeight / m_iHeightSegments, rb * std::sin(a1) })
						->putNormal(n4)
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, y / (float)m_iHeightSegments });
				}
				if (m_fRadius2 > 0)
				{
					float t{ float(m_iHeightSegments - 1) };
					float y{ t * m_fHeight / m_iHeightSegments };
					rs = m_fRadius2;
					rb = m_fRadius1 - (m_iHeightSegments - 1) * (m_fRadius1 - m_fRadius2) / m_iHeightSegments;
					n1 = Vec3f{ rb * std::cos(a2), ny, rb * std::sin(a2) };
					ntl::Normalize<float>(n1);
					n2 = Vec3f{ rs * std::cos(a2), ny, rs * std::sin(a2) };
					ntl::Normalize<float>(n2);
					n3 = Vec3f{ rs * std::cos(a1), ny, rs * std::sin(a1) };
					ntl::Normalize<float>(n3);
					n4 = Vec3f{ rb * std::cos(a1), ny, rb * std::sin(a1) };
					ntl::Normalize<float>(n4);
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a2), -m_fHeight / 2 + y, rb * std::sin(a2) })
						->putNormal(n1)
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, t / m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a2), m_fHeight / 2, rs * std::sin(a2) })
						->putNormal(n2)
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, 1 });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a1), m_fHeight / 2, rs * std::sin(a1) })
						->putNormal(n3)
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, 1 });
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(a1), -m_fHeight / 2 + y, rb * std::sin(a1) })
						->putNormal(n4)
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, t / m_iHeightSegments });
				}
				else
				{
					rs = m_fRadius1 - (m_iHeightSegments - 1) * (m_fRadius1 - m_fRadius2) / m_iHeightSegments;
					n1 = Vec3f{ rs * std::cos(a2), ny, rs * std::sin(a2) };
					ntl::Normalize<float>(n1);
					n3 = Vec3f{ rs * std::cos(a1), ny, rs * std::sin(a1) };
					ntl::Normalize<float>(n3);
					n2 = (n1 + n3) / 2.0f;
					ntl::Normalize<float>(n2);
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a2), -m_fHeight / 2 + (m_iHeightSegments - 1) * m_fHeight / m_iHeightSegments, rs * std::sin(a2) })
						->putNormal(n1)
						->putTextureCoords(Vec2f{ 1 - (i + 1) / (float)m_iSides, (m_iHeightSegments - 1) / (float)m_iHeightSegments });
					p->AddVertex()
						->putPosition3D(Vec3f{ 0, m_fHeight / 2, 0 })
						->putNormal(n2)
						->putTextureCoords(Vec2f{ 1 - (i + 0.5f) / (float)m_iSides, 1 });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a1), -m_fHeight / 2 + (m_iHeightSegments - 1) * m_fHeight / m_iHeightSegments, rs * std::sin(a1) })
						->putNormal(n3)
						->putTextureCoords(Vec2f{ 1 - i / (float)m_iSides, (m_iHeightSegments - 1) / (float)m_iHeightSegments });
				}
				for (int t = 0; t < m_iCapSegments - 1; t++)
				{
					if (m_fRadius2 > 0)
					{
						rb = m_fRadius2 - t * m_fRadius2 / m_iCapSegments;
						rs = m_fRadius2 - (t + 1) * m_fRadius2 / m_iCapSegments;
						p = m_pVertexArray->AddPolygon();
						p->AddVertex()
							->putPosition3D(Vec3f{ rb * std::cos(a2), m_fHeight / 2, rb * std::sin(a2) })
							->putNormal(Vec3f{ 0, 1, 0 })
							->putTextureCoords(Vec2f{ (rb * std::cos(a2) + m_fRadius2) / (2 * m_fRadius2), 1 - (rb * std::sin(a2) + m_fRadius2) / (2 * m_fRadius2) });
						p->AddVertex()
							->putPosition3D(Vec3f{ rs * std::cos(a2), m_fHeight / 2, rs * std::sin(a2) })
							->putNormal(Vec3f{ 0, 1, 0 })
							->putTextureCoords(Vec2f{ (rs * std::cos(a2) + m_fRadius2) / (2 * m_fRadius2), 1 - (rs * std::sin(a2) + m_fRadius2) / (2 * m_fRadius2) });
						p->AddVertex()
							->putPosition3D(Vec3f{ rs * std::cos(a1), m_fHeight / 2, rs * std::sin(a1) })
							->putNormal(Vec3f{ 0, 1, 0 })
							->putTextureCoords(Vec2f{ (rs * std::cos(a1) + m_fRadius2) / (2 * m_fRadius2), 1 - (rs * std::sin(a1) + m_fRadius2) / (2 * m_fRadius2) });
						p->AddVertex()
							->putPosition3D(Vec3f{ rb * std::cos(a1), m_fHeight / 2, rb * std::sin(a1) })
							->putNormal(Vec3f{ 0, 1, 0 })
							->putTextureCoords(Vec2f{ (rb * std::cos(a1) + m_fRadius2) / (2 * m_fRadius2), 1 - (rb * std::sin(a1) + m_fRadius2) / (2 * m_fRadius2) });
					}
					rb = m_fRadius1 - t * m_fRadius1 / m_iCapSegments;
					rs = m_fRadius1 - (t + 1) * m_fRadius1 / m_iCapSegments;
					p = m_pVertexArray->AddPolygon();
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(b2), -m_fHeight / 2, rb * std::sin(b2) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(b2) + m_fRadius1) / (2 * m_fRadius1), (rb * std::sin(b2) + m_fRadius1) / (2 * m_fRadius1) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(b2), -m_fHeight / 2, rs * std::sin(b2) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(b2) + m_fRadius1) / (2 * m_fRadius1), (rs * std::sin(b2) + m_fRadius1) / (2 * m_fRadius1) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(b1), -m_fHeight / 2, rs * std::sin(b1) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(b1) + m_fRadius1) / (2 * m_fRadius1), (rs * std::sin(b1) + m_fRadius1) / (2 * m_fRadius1) });
					p->AddVertex()
						->putPosition3D(Vec3f{ rb * std::cos(b1), -m_fHeight / 2, rb * std::sin(b1) })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (rb * std::cos(b1) + m_fRadius1) / (2 * m_fRadius1), (rb * std::sin(b1) + m_fRadius1) / (2 * m_fRadius1) });
				}
				if (m_fRadius2 > 0)
				{
					rs = m_fRadius2 - (m_iCapSegments - 1) * m_fRadius2 / m_iCapSegments;
					top->AddVertex()
						->putPosition3D(Vec3f{ rs * std::cos(a1), m_fHeight / 2, rs * std::sin(a1) })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (rs * std::cos(a1) + m_fRadius2) / (2 * m_fRadius2), 1 - (rs * std::sin(a1) + m_fRadius2) / (2 * m_fRadius2) });
				}
				rs = m_fRadius1 - (m_iCapSegments - 1) * m_fRadius1 / m_iCapSegments;
				bottom->AddVertex()
					->putPosition3D(Vec3f{ rs * std::cos(b1), -m_fHeight / 2, rs * std::sin(b1) })
					->putNormal(Vec3f{ 0, -1, 0 })
					->putTextureCoords(Vec2f{ (rs * std::cos(b1) + m_fRadius1) / (2 * m_fRadius1), (rs * std::sin(b1) + m_fRadius1) / (2 * m_fRadius1) });
			}
			if (m_fRadius2 > 0)
			{
				rs = m_fRadius2 - (m_iCapSegments - 1) * m_fRadius2 / m_iCapSegments;
				top->AddVertex()
					->putPosition3D(Vec3f{ rs, m_fHeight / 2, 0 })
					->putNormal(Vec3f{ 0, 1, 0 })
					->putTextureCoords(Vec2f{ (rs + m_fRadius2) / (2 * m_fRadius1), 0.5f });
			}
			rs = m_fRadius1 - (m_iCapSegments - 1) * m_fRadius1 / m_iCapSegments;
			bottom->AddVertex()
				->putPosition3D(Vec3f{ rs, -m_fHeight / 2, 0 })
				->putNormal(Vec3f{ 0, -1, 0 })
				->putTextureCoords(Vec2f{ (rs + m_fRadius1) / (2 * m_fRadius1), 0.5f });
		}
	#pragma endregion

	#pragma region Render
		bool CPrimitiveCone::Render()
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