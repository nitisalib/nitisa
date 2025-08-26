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
		CPrimitiveBox::CPrimitiveBox(IControl *control):
			CModel(false, false),
			m_fWidth{ 10 },
			m_fHeight{ 10 },
			m_fDepth{ 10 },
			m_iWidthSegments{ 1 },
			m_iHeightSegments{ 1 },
			m_iDepthSegments{ 1 },
			m_pControl{ control },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		void CPrimitiveBox::FreeResources()
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
		bool CPrimitiveBox::setWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fWidth))
			{
				m_fWidth=value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveBox::setHeight(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fHeight))
			{
				m_fHeight = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveBox::setDepth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDepth))
			{
				m_fDepth = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveBox::setSize(const float width, const float height, const float depth)
		{
			if (ntl::IsGreater<float>(width, 0) && ntl::IsGreater<float>(height, 0) && ntl::IsGreater<float>(depth, 0) &&
				(ntl::IsNotEqual<float>(width, m_fWidth) || ntl::IsNotEqual<float>(height, m_fHeight) || ntl::IsNotEqual<float>(depth, m_fDepth)))
			{
				m_fWidth = width;
				m_fHeight = height;
				m_fDepth = depth;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveBox::setWidthSegments(const int value)
		{
			if (value > 0 && value != m_iWidthSegments)
			{
				m_iWidthSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveBox::setHeightSegments(const int value)
		{
			if (value > 0 && value != m_iHeightSegments)
			{
				m_iHeightSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveBox::setDepthSegments(const int value)
		{
			if (value > 0 && value != m_iDepthSegments)
			{
				m_iDepthSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitiveBox::setSegments(const int width, const int height, const int depth)
		{
			if (width > 0 && height > 0 && depth > 0 && (width != m_iWidthSegments || height != m_iHeightSegments || depth != m_iDepthSegments))
			{
				m_iWidthSegments = width;
				m_iHeightSegments = height;
				m_iDepthSegments = depth;
				m_bValid = false;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CPrimitiveBox::UpdateGeometry()
		{
			m_pVertexArray->setPolygonCount((m_iWidthSegments * m_iHeightSegments + m_iWidthSegments * m_iDepthSegments + m_iHeightSegments * m_iDepthSegments) * 2, 4);
			size_t polygon_index{ 0 };

			float w{ m_fWidth / m_iWidthSegments }, h{ m_fHeight / m_iHeightSegments }, d{ m_fDepth / m_iDepthSegments };
			float ws{ (float)m_iWidthSegments }, hs{ (float)m_iHeightSegments }, ds{ (float)m_iDepthSegments };
			// Front
			for (int x = 0; x < m_iWidthSegments; x++)
				for (int y = 0; y < m_iHeightSegments; y++, polygon_index++)
				{
					m_pVertexArray->getPolygon(polygon_index)->getVertex(0)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + x * w, -m_fHeight / 2 + y * h, m_fDepth / 2 })
						->putNormal(Vec3f{ 0, 0, 1 })
						->putTextureCoords(Vec2f{ x / ws, y / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(1)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + x * w, -m_fHeight / 2 + (y + 1) * h, m_fDepth / 2 })
						->putNormal(Vec3f{ 0, 0, 1 })
						->putTextureCoords(Vec2f{ x / ws, (y + 1) / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(2)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + (x + 1) * w, -m_fHeight / 2 + (y + 1) * h, m_fDepth / 2 })
						->putNormal(Vec3f{ 0, 0, 1 })
						->putTextureCoords(Vec2f{ (x + 1) / ws, (y + 1) / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(3)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + (x + 1) * w, -m_fHeight / 2 + y * h, m_fDepth / 2 })
						->putNormal(Vec3f{ 0, 0, 1 })
						->putTextureCoords(Vec2f{ (x + 1) / ws, y / hs });
				}
			// Back
			for (int x = 0; x < m_iWidthSegments; x++)
				for (int y = 0; y < m_iHeightSegments; y++, polygon_index++)
				{
					m_pVertexArray->getPolygon(polygon_index)->getVertex(0)
						->putPosition3D(Vec3f{ m_fWidth / 2 - x * w, -m_fHeight / 2 + y * h, -m_fDepth / 2 })
						->putNormal(Vec3f{ 0, 0, -1 })
						->putTextureCoords(Vec2f{ x / ws, y / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(1)
						->putPosition3D(Vec3f{ m_fWidth / 2 - x * w, -m_fHeight / 2 + (y + 1) * h, -m_fDepth / 2 })
						->putNormal(Vec3f{ 0, 0, -1 })
						->putTextureCoords(Vec2f{ x / ws, (y + 1) / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(2)
						->putPosition3D(Vec3f{ m_fWidth / 2 - (x + 1) * w, -m_fHeight / 2 + (y + 1) * h, -m_fDepth / 2 })
						->putNormal(Vec3f{ 0, 0, -1 })
						->putTextureCoords(Vec2f{ (x + 1) / ws, (y + 1) / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(3)
						->putPosition3D(Vec3f{ m_fWidth / 2 - (x + 1) * w, -m_fHeight / 2 + y * h, -m_fDepth / 2 })
						->putNormal(Vec3f{ 0, 0, -1 })
						->putTextureCoords(Vec2f{ (x + 1) / ws, y / hs });
				}
			// Top
			for (int x = 0; x < m_iWidthSegments; x++)
				for (int z = 0; z < m_iDepthSegments; z++, polygon_index++)
				{
					m_pVertexArray->getPolygon(polygon_index)->getVertex(0)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + x * w, m_fHeight / 2, m_fDepth / 2 - z * d })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ x / ws, z / ds });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(1)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + x * w, m_fHeight / 2, m_fDepth / 2 - (z + 1) * d })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ x / ws, (z + 1) / ds });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(2)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + (x + 1) * w, m_fHeight / 2, m_fDepth / 2 - (z + 1) * d })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (x + 1) / ws, (z + 1) / ds });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(3)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + (x + 1) * w, m_fHeight / 2, m_fDepth / 2 - z * d })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (x + 1) / ws, z / ds });
				}
			// Bottom
			for (int x = 0; x < m_iWidthSegments; x++)
				for (int z = 0; z < m_iDepthSegments; z++, polygon_index++)
				{
					m_pVertexArray->getPolygon(polygon_index)->getVertex(0)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + x * w, -m_fHeight / 2, -m_fDepth / 2 + z * d })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ x / ws, z / ds });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(1)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + x * w, -m_fHeight / 2, -m_fDepth / 2 + (z + 1) * d })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ x / ws, (z + 1) / ds });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(2)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + (x + 1) * w, -m_fHeight / 2, -m_fDepth / 2 + (z + 1) * d })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (x + 1) / ws, (z + 1) / ds });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(3)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + (x + 1) * w, -m_fHeight / 2, -m_fDepth / 2 + z * d })
						->putNormal(Vec3f{ 0, -1, 0 })
						->putTextureCoords(Vec2f{ (x + 1) / ws, z / ds });
				}
			// Left
			for (int z = 0; z < m_iDepthSegments; z++)
				for (int y = 0; y < m_iHeightSegments; y++, polygon_index++)
				{
					m_pVertexArray->getPolygon(polygon_index)->getVertex(0)
						->putPosition3D(Vec3f{ -m_fWidth / 2, -m_fHeight / 2 + y * h, -m_fDepth / 2 + z * d })
						->putNormal(Vec3f{ -1, 0, 0 })
						->putTextureCoords(Vec2f{ z / ds, y / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(1)
						->putPosition3D(Vec3f{ -m_fWidth / 2, -m_fHeight / 2 + (y + 1) * h, -m_fDepth / 2 + z * d })
						->putNormal(Vec3f{ -1, 0, 0 })
						->putTextureCoords(Vec2f{ z / ds, (y + 1) / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(2)
						->putPosition3D(Vec3f{ -m_fWidth / 2, -m_fHeight / 2 + (y + 1) * h, -m_fDepth / 2 + (z + 1) * d })
						->putNormal(Vec3f{ -1, 0, 0 })
						->putTextureCoords(Vec2f{ (z + 1) / ds, (y + 1) / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(3)
						->putPosition3D(Vec3f{ -m_fWidth / 2, -m_fHeight / 2 + y * h, -m_fDepth / 2 + (z + 1) * d })
						->putNormal(Vec3f{ -1, 0, 0 })
						->putTextureCoords(Vec2f{ (z + 1) / ds, y / hs });
				}
			// Right
			for (int z = 0; z < m_iDepthSegments; z++)
				for (int y = 0; y < m_iHeightSegments; y++, polygon_index++)
				{
					m_pVertexArray->getPolygon(polygon_index)->getVertex(0)
						->putPosition3D(Vec3f{ m_fWidth / 2, -m_fHeight / 2 + y * h, m_fDepth / 2 - z * d })
						->putNormal(Vec3f{ 1, 0, 0 })
						->putTextureCoords(Vec2f{ z / ds, y / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(1)
						->putPosition3D(Vec3f{ m_fWidth / 2, -m_fHeight / 2 + (y + 1) * h, m_fDepth / 2 - z * d })
						->putNormal(Vec3f{ 1, 0, 0 })
						->putTextureCoords(Vec2f{ z / ds, (y + 1) / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(2)
						->putPosition3D(Vec3f{ m_fWidth / 2, -m_fHeight / 2 + (y + 1) * h, m_fDepth / 2 - (z + 1) * d })
						->putNormal(Vec3f{ 1, 0, 0 })
						->putTextureCoords(Vec2f{ (z + 1) / ds, (y + 1) / hs });
					m_pVertexArray->getPolygon(polygon_index)->getVertex(3)
						->putPosition3D(Vec3f{ m_fWidth / 2, -m_fHeight / 2 + y * h, m_fDepth / 2 - (z + 1) * d })
						->putNormal(Vec3f{ 1, 0, 0 })
						->putTextureCoords(Vec2f{ (z + 1) / ds, y / hs });
				}
		}
	#pragma endregion

	#pragma region Render
		bool CPrimitiveBox::Render()
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