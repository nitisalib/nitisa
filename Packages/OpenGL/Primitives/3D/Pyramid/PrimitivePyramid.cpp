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
		CPrimitivePyramid::CPrimitivePyramid(IControl *control) :
			CModel(false, false),
			m_fWidth{ 10 },
			m_fDepth{ 10 },
			m_fHeight{ 10 },
			m_iSegments{ 1 },
			m_pControl{ control },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		void CPrimitivePyramid::FreeResources()
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
		bool CPrimitivePyramid::setWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fWidth))
			{
				m_fWidth = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitivePyramid::setDepth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDepth))
			{
				m_fDepth = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitivePyramid::setHeight(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fHeight))
			{
				m_fHeight = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitivePyramid::setSize(const float width, const float depth, const float height)
		{
			if (ntl::IsGreater<float>(width, 0) && ntl::IsGreater<float>(depth, 0) && ntl::IsGreater<float>(height, 0))
			{
				bool changed{ false };
				if (ntl::IsNotEqual<float>(width, m_fWidth))
				{
					m_fWidth = width;
					changed = true;
				}
				if (ntl::IsNotEqual<float>(depth, m_fDepth))
				{
					m_fDepth = depth;
					changed = true;
				}
				if (ntl::IsNotEqual<float>(height, m_fHeight))
				{
					m_fHeight = height;
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

		bool CPrimitivePyramid::setSegments(const int value)
		{
			if (value >= 1 && value != m_iSegments)
			{
				m_iSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CPrimitivePyramid::UpdateGeometry()
		{
			m_pVertexArray->Clear();
			float ny{ m_fDepth * m_fDepth * m_fHeight / 2 / (m_fHeight * m_fHeight + m_fDepth * m_fDepth) };
			float nz{ m_fDepth * m_fDepth * m_fDepth / 2 / (m_fHeight * m_fHeight + m_fDepth * m_fDepth) };
			float nx{ m_fWidth * m_fWidth * m_fWidth / 2 / (m_fHeight * m_fHeight + m_fWidth * m_fWidth) };
			Vec3f n1{ 0, ny, nz };
			ntl::Normalize<float>(n1);
			Vec3f n2{ 0, ny, -nz };
			ntl::Normalize<float>(n2);
			Vec3f n3{ -nx, ny, 0 };
			ntl::Normalize<float>(n3);
			Vec3f n4{ nx, ny, 0 };
			ntl::Normalize<float>(n4);
			float w{ m_fWidth / (2 * m_iSegments) }, h{ m_fHeight / m_iSegments }, d{ m_fDepth / (2 * m_iSegments) }, k{ 1 / (float)m_iSegments }, p{ (float)m_iSegments - 1 };
			// Bottom
			IPolygon *t{ m_pVertexArray->AddPolygon() };
			t->AddVertex()
				->putPosition3D(Vec3f{ -m_fWidth / 2, -m_fHeight / 2, -m_fDepth / 2 })
				->putNormal(Vec3f{ 0, -1, 0 })
				->putTextureCoords(Vec2f{ 0, 0 });
			t->AddVertex()
				->putPosition3D(Vec3f{ -m_fWidth / 2, -m_fHeight / 2, +m_fDepth / 2 })
				->putNormal(Vec3f{ 0, -1, 0 })
				->putTextureCoords(Vec2f{ 0, 1 });
			t->AddVertex()
				->putPosition3D(Vec3f{ +m_fWidth / 2, -m_fHeight / 2, +m_fDepth / 2 })
				->putNormal(Vec3f{ 0, -1, 0 })
				->putTextureCoords(Vec2f{ 1, 1 });
			t->AddVertex()
				->putPosition3D(Vec3f{ +m_fWidth / 2, -m_fHeight / 2, -m_fDepth / 2 })
				->putNormal(Vec3f{ 0, -1, 0 })
				->putTextureCoords(Vec2f{ 1, 0 });
			// Front
			for (int y = 0; y < m_iSegments - 1; y++)
			{
				t = m_pVertexArray->AddPolygon();
				t->AddVertex()
					->putPosition3D(Vec3f{ -m_fWidth / 2 + y * w, -m_fHeight / 2 + y * h, m_fDepth / 2 - y * d })
					->putNormal(n1)
					->putTextureCoords(Vec2f{ y * k / 2, y * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ -m_fWidth / 2 + (y + 1) * w, -m_fHeight / 2 + (y + 1) * h, m_fDepth / 2 - (y + 1) * d })
					->putNormal(n1)
					->putTextureCoords(Vec2f{ (y + 1) * k / 2, (y + 1) * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ m_fWidth / 2 - (y + 1) * w, -m_fHeight / 2 + (y + 1) * h, m_fDepth / 2 - (y + 1) * d })
					->putNormal(n1)
					->putTextureCoords(Vec2f{ 1 - (y + 1) * k / 2, (y + 1) * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ m_fWidth / 2 - y * w, -m_fHeight / 2 + y * h, m_fDepth / 2 - y * d })
					->putNormal(n1)
					->putTextureCoords(Vec2f{ 1 - y * k / 2, y * k });
			}
			t = m_pVertexArray->AddPolygon();
			t->AddVertex()
				->putPosition3D(Vec3f{ -m_fWidth / 2 + p * w, -m_fHeight / 2 + p * h, m_fDepth / 2 - p * d })
				->putNormal(n1)
				->putTextureCoords(Vec2f{ p * k / 2, p * k });
			t->AddVertex()
				->putPosition3D(Vec3f{ 0, m_fHeight / 2, 0 })
				->putNormal(n1)
				->putTextureCoords(Vec2f{ 0.5f, 1 });
			t->AddVertex()
				->putPosition3D(Vec3f{ m_fWidth / 2 - p * w, -m_fHeight / 2 + p * h, m_fDepth / 2 - p * d })
				->putNormal(n1)
				->putTextureCoords(Vec2f{ 1 - p * k / 2, p * k });
			// Back
			for (int y = 0; y < m_iSegments - 1; y++)
			{
				t = m_pVertexArray->AddPolygon();
				t->AddVertex()
					->putPosition3D(Vec3f{ m_fWidth / 2 - y * w, -m_fHeight / 2 + y * h, -m_fDepth / 2 + y * d })
					->putNormal(n2)
					->putTextureCoords(Vec2f{ y * k / 2, y * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ m_fWidth / 2 - (y + 1) * w, -m_fHeight / 2 + (y + 1) * h, -m_fDepth / 2 + (y + 1) * d })
					->putNormal(n2)
					->putTextureCoords(Vec2f{ (y + 1) * k / 2, (y + 1) * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ -m_fWidth / 2 + (y + 1) * w, -m_fHeight / 2 + (y + 1) * h, -m_fDepth / 2 + (y + 1) * d })
					->putNormal(n2)
					->putTextureCoords(Vec2f{ 1 - (y + 1) * k / 2, (y + 1) * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ -m_fWidth / 2 + y * w, -m_fHeight / 2 + y * h, -m_fDepth / 2 + y * d })
					->putNormal(n2)
					->putTextureCoords(Vec2f{ 1 - y * k / 2, y * k });
			}
			t = m_pVertexArray->AddPolygon();
			t->AddVertex()
				->putPosition3D(Vec3f{ m_fWidth / 2 - p * w, -m_fHeight / 2 + p * h, -m_fDepth / 2 + p * d })
				->putNormal(n2)
				->putTextureCoords(Vec2f{ p * k / 2, p * k });
			t->AddVertex()
				->putPosition3D(Vec3f{ 0, m_fHeight / 2, 0 })
				->putNormal(n2)
				->putTextureCoords(Vec2f{ 0.5f, 1 });
			t->AddVertex()
				->putPosition3D(Vec3f{ -m_fWidth / 2 + p * w, -m_fHeight / 2 + p * h, -m_fDepth / 2 + p * d })
				->putNormal(n2)
				->putTextureCoords(Vec2f{ 1 - p * k / 2, p * k });
			// Left
			for (int y = 0; y < m_iSegments - 1; y++)
			{
				t = m_pVertexArray->AddPolygon();
				t->AddVertex()
					->putPosition3D(Vec3f{ -m_fWidth / 2 + y * w, -m_fHeight / 2 + y * h, -m_fDepth / 2 + y * d })
					->putNormal(n3)
					->putTextureCoords(Vec2f{ y * k / 2, y * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ -m_fWidth / 2 + (y + 1) * w, -m_fHeight / 2 + (y + 1) * h, -m_fDepth / 2 + (y + 1) * d })
					->putNormal(n3)
					->putTextureCoords(Vec2f{ (y + 1) * k / 2, (y + 1) * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ -m_fWidth / 2 + (y + 1) * w, -m_fHeight / 2 + (y + 1) * h, m_fDepth / 2 - (y + 1) * d })
					->putNormal(n3)
					->putTextureCoords(Vec2f{ 1 - (y + 1) * k / 2, (y + 1) * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ -m_fWidth / 2 + y * w, -m_fHeight / 2 + y * h, m_fDepth / 2 - y * d })
					->putNormal(n3)
					->putTextureCoords(Vec2f{ 1 - y * k / 2, y * k });
			}
			t = m_pVertexArray->AddPolygon();
			t->AddVertex()
				->putPosition3D(Vec3f{ -m_fWidth / 2 + p * w, -m_fHeight / 2 + p * h, -m_fDepth / 2 + p * d })
				->putNormal(n3)
				->putTextureCoords(Vec2f{ p * k / 2, p * k });
			t->AddVertex()
				->putPosition3D(Vec3f{ 0, m_fHeight / 2, 0 })
				->putNormal(n3)
				->putTextureCoords(Vec2f{ 0.5f, 1 });
			t->AddVertex()
				->putPosition3D(Vec3f{ -m_fWidth / 2 + p * w, -m_fHeight / 2 + p * h, m_fDepth / 2 - p * d })
				->putNormal(n3)
				->putTextureCoords(Vec2f{ 1 - p * k / 2, p * k });
			// Right
			for (int y = 0; y < m_iSegments - 1; y++)
			{
				t = m_pVertexArray->AddPolygon();
				t->AddVertex()
					->putPosition3D(Vec3f{ m_fWidth / 2 - y * w, -m_fHeight / 2 + y * h, m_fDepth / 2 - y * d })
					->putNormal(n4)
					->putTextureCoords(Vec2f{ y * k / 2, y * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ m_fWidth / 2 - (y + 1) * w, -m_fHeight / 2 + (y + 1) * h, m_fDepth / 2 - (y + 1) * d })
					->putNormal(n4)
					->putTextureCoords(Vec2f{ (y + 1) * k / 2, (y + 1) * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ m_fWidth / 2 - (y + 1) * w, -m_fHeight / 2 + (y + 1) * h, -m_fDepth / 2 + (y + 1) * d })
					->putNormal(n4)
					->putTextureCoords(Vec2f{ 1 - (y + 1) * k / 2, (y + 1) * k });
				t->AddVertex()
					->putPosition3D(Vec3f{ m_fWidth / 2 - y * w, -m_fHeight / 2 + y * h, -m_fDepth / 2 + y * d })
					->putNormal(n4)
					->putTextureCoords(Vec2f{ 1 - y * k / 2, y * k });
			}
			t = m_pVertexArray->AddPolygon();
			t->AddVertex()
				->putPosition3D(Vec3f{ m_fWidth / 2 - p * w, -m_fHeight / 2 + p * h, m_fDepth / 2 - p * d })
				->putNormal(n4)
				->putTextureCoords(Vec2f{ p * k / 2, p * k });
			t->AddVertex()
				->putPosition3D(Vec3f{ 0, m_fHeight / 2, 0 })
				->putNormal(n4)
				->putTextureCoords(Vec2f{ 0.5f, 1 });
			t->AddVertex()
				->putPosition3D(Vec3f{ m_fWidth / 2 - p * w, -m_fHeight / 2 + p * h, -m_fDepth / 2 + p * d })
				->putNormal(n4)
				->putTextureCoords(Vec2f{ 1 - p * k / 2, p * k });
		}
	#pragma endregion

	#pragma region Render
		bool CPrimitivePyramid::Render()
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