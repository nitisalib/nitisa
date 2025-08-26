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
		CPrimitivePlane::CPrimitivePlane(IControl *control) :
			CModel(false, false),
			m_fWidth{ 10 },
			m_fDepth{ 10 },
			m_iWidthSegments{ 1 },
			m_iDepthSegments{ 1 },
			m_pControl{ control },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		void CPrimitivePlane::FreeResources()
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
		bool CPrimitivePlane::setWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fWidth))
			{
				m_fWidth = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitivePlane::setDepth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDepth))
			{
				m_fDepth = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitivePlane::setSize(const float width, const float depth)
		{
			if (ntl::IsGreater<float>(width, 0) && ntl::IsGreater<float>(depth, 0))
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
				if (changed)
				{
					m_bValid = false;
					return true;
				}
			}
			return false;
		}

		bool CPrimitivePlane::setWidthSegments(const int value)
		{
			if (value >= 1 && value != m_iWidthSegments)
			{
				m_iWidthSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitivePlane::setDepthSegments(const int value)
		{
			if (value >= 1 && value != m_iDepthSegments)
			{
				m_iDepthSegments = value;
				m_bValid = false;
				return true;
			}
			return false;
		}

		bool CPrimitivePlane::setSegments(const int width, const int depth)
		{
			if (width >= 1 && depth >= 1)
			{
				bool changed{ false };
				if (width != m_iWidthSegments)
				{
					m_iWidthSegments = width;
					changed = true;
				}
				if (depth != m_iDepthSegments)
				{
					m_iDepthSegments = depth;
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
		void CPrimitivePlane::UpdateGeometry()
		{
			m_pVertexArray->Clear();
			m_pVertexArray->setPolygonCount(m_iWidthSegments * m_iDepthSegments, 4);
			size_t index{ 0 };
			for (int x = 0; x < m_iWidthSegments; x++)
				for (int z = 0; z < m_iDepthSegments; z++, index++)
				{
					m_pVertexArray->getPolygon(index)->getVertex(0)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + x * m_fWidth / m_iWidthSegments, 0, m_fDepth / 2 - z * m_fDepth / m_iDepthSegments })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ x / (float)m_iWidthSegments, z / (float)m_iDepthSegments });
					m_pVertexArray->getPolygon(index)->getVertex(1)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + x * m_fWidth / m_iWidthSegments, 0, m_fDepth / 2 - (z + 1) * m_fDepth / m_iDepthSegments })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ x / (float)m_iWidthSegments, (z + 1) / (float)m_iDepthSegments });
					m_pVertexArray->getPolygon(index)->getVertex(2)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + (x + 1) * m_fWidth / m_iWidthSegments, 0, m_fDepth / 2 - (z + 1) * m_fDepth / m_iDepthSegments })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (x + 1) / (float)m_iWidthSegments, (z + 1) / (float)m_iDepthSegments });
					m_pVertexArray->getPolygon(index)->getVertex(3)
						->putPosition3D(Vec3f{ -m_fWidth / 2 + (x + 1) * m_fWidth / m_iWidthSegments, 0, m_fDepth / 2 - z * m_fDepth / m_iDepthSegments })
						->putNormal(Vec3f{ 0, 1, 0 })
						->putTextureCoords(Vec2f{ (x + 1) / (float)m_iWidthSegments, z / (float)m_iDepthSegments });
				}
		}
	#pragma endregion

	#pragma region Render
		bool CPrimitivePlane::Render()
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