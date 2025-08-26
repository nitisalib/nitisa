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
		CHeightmap::CHeightmap() :
			C3DControl(L"Heightmap"),
			m_fCellWidth{ 5 },
			m_fCellHeight{ 0.1f },
			m_fCellDepth{ 5 },
			m_sHeightmapSize{ 0, 0 },
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		CHeightmap::CHeightmap(IControl *parent) :CHeightmap()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IHeightmap getters
		float CHeightmap::getCellWidth()
		{
			return m_fCellWidth;
		}

		float CHeightmap::getCellHeight()
		{
			return m_fCellHeight;
		}

		float CHeightmap::getCellDepth()
		{
			return m_fCellDepth;
		}

		String CHeightmap::getFilename()
		{
			return m_sFilename;
		}

		Point CHeightmap::getHeightmapSize()
		{
			return m_sHeightmapSize;
		}
	#pragma endregion

	#pragma region IHeightmap setters
		bool CHeightmap::setCellWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCellWidth))
			{
				m_fCellWidth = value;
				m_bValid = false;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CHeightmap::setCellHeight(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCellHeight))
			{
				m_fCellHeight = value;
				m_bValid = false;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CHeightmap::setCellDepth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCellDepth))
			{
				m_fCellDepth = value;
				m_bValid = false;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CHeightmap::setCellSize(const float width, const float height, const float depth)
		{
			if (ntl::IsGreater<float>(width, 0) && ntl::IsGreater<float>(height, 0) && ntl::IsGreater<float>(depth, 0))
			{
				bool changed{ false };
				if (ntl::IsNotEqual<float>(width, m_fCellWidth))
				{
					m_fCellWidth = width;
					changed = true;
				}
				if (ntl::IsNotEqual<float>(height, m_fCellHeight))
				{
					m_fCellHeight = height;
					changed = true;
				}
				if (ntl::IsNotEqual<float>(depth, m_fCellDepth))
				{
					m_fCellDepth = depth;
					changed = true;
				}
				if (changed)
				{
					m_bValid = false;
					QueryService()->SendChangeNotification();
					return true;
				}
			}
			return false;
		}

		bool CHeightmap::setFilename(const String &value)
		{
			if (value != m_sFilename)
			{
				m_sFilename = value;
				m_bValid = false;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CHeightmap::FreeResources(COpenGL *graphics)
		{
			if (m_pVertexArray)
			{
				m_pVertexArray->Release();
				m_pVertexArray = nullptr;
				m_bValid = false;
			}
		}
	#pragma endregion

	#pragma region Render
		void CHeightmap::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			if (!m_sFilename.empty())
			{
				if (!m_pVertexArray)
				{
					if (!(m_pVertexArray = renderer->CreateVertexArray(VertexFormat)))
						return;
				}
				if (!m_bValid)
				{
					Image bmp{ Application->Picture->Load(m_sFilename) };
					if (bmp.Width < 2 || bmp.Height < 2)
					{
						m_sFilename.clear();
						return;
					}
					m_sHeightmapSize = Point{ bmp.Width, bmp.Height };
					float x1{ -bmp.Width * m_fCellWidth * 0.5f }, z1{ -bmp.Height * m_fCellDepth * 0.5f };
					m_pVertexArray->setPolygonCount((bmp.Width - 1) * (bmp.Height - 1), 4);
					size_t polygon_index{ 0 };
					for (int z = 0; z < bmp.Height - 1; z++)
						for (int x = 0; x < bmp.Width - 1; x++, polygon_index++)
						{
							Vec3f p1{ x1 + x * m_fCellWidth, bmp[x][z + 1].average() * m_fCellHeight, z1 + (z + 1) * m_fCellDepth };
							Vec3f p2{ x1 + x * m_fCellWidth, bmp[x][z].average() * m_fCellHeight, z1 + z * m_fCellDepth };
							Vec3f p3{ x1 + (x + 1) * m_fCellWidth, bmp[x + 1][z].average() * m_fCellHeight, z1 + z * m_fCellDepth };
							Vec3f p4{ x1 + (x + 1) * m_fCellWidth, bmp[x + 1][z + 1].average() * m_fCellHeight, z1 + (z + 1) * m_fCellDepth };
							m_pVertexArray->getPolygon(polygon_index)->getVertex(0)
								->putPosition3D(p1)
								->putTextureCoords(Vec2f{ x / (float)bmp.Width, (z + 1) / (float)bmp.Height });
							m_pVertexArray->getPolygon(polygon_index)->getVertex(1)
								->putPosition3D(p2)
								->putTextureCoords(Vec2f{ x / (float)bmp.Width, z / (float)bmp.Height });
							m_pVertexArray->getPolygon(polygon_index)->getVertex(2)
								->putPosition3D(p3)
								->putTextureCoords(Vec2f{ (x + 1) / (float)bmp.Width, z / (float)bmp.Height });
							m_pVertexArray->getPolygon(polygon_index)->getVertex(3)
								->putPosition3D(p4)
								->putTextureCoords(Vec2f{ (x + 1) / (float)bmp.Width, (z + 1) / (float)bmp.Height });
						}
					Vec3f n;
					int normal_count;
					for (int z = 0; z < bmp.Height - 1; z++)
						for (int x = 0; x < bmp.Width - 1; x++)
						{
							// Vertex1
							n = Vec3f{ 0, 0, 0 };
							normal_count = 0;
							n += m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x)->getPlane().N;
							normal_count++;
							if (x > 0)
							{
								n += m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x - 1)->getPlane().N;
								normal_count++;
								if (z < bmp.Height - 2)
								{
									n += m_pVertexArray->getPolygon((z + 1) * (bmp.Width - 1) + x - 1)->getPlane().N;
									normal_count++;
								}
							}
							if (z < bmp.Height - 2)
							{
								n += m_pVertexArray->getPolygon((z + 1) * (bmp.Width - 1) + x)->getPlane().N;
								normal_count++;
							}
							n /= (float)normal_count;
							m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x)->getVertex(0)->putNormal(n);
							// Vertex2
							n = Vec3f{ 0, 0, 0 };
							normal_count = 0;
							n += m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x)->getPlane().N;
							normal_count++;
							if (x > 0)
							{
								n += m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x - 1)->getPlane().N;
								normal_count++;
								if (z > 0)
								{
									n += m_pVertexArray->getPolygon((z - 1) * (bmp.Width - 1) + x - 1)->getPlane().N;
									normal_count++;
								}
							}
							if (z > 0)
							{
								n += m_pVertexArray->getPolygon((z - 1) * (bmp.Width - 1) + x)->getPlane().N;
								normal_count++;
							}
							n /= (float)normal_count;
							m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x)->getVertex(1)->putNormal(n);
							// Vertex3
							n = Vec3f{ 0, 0, 0 };
							normal_count = 0;
							n += m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x)->getPlane().N;
							normal_count++;
							if (x < bmp.Width - 2)
							{
								n += m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x + 1)->getPlane().N;
								normal_count++;
								if (z > 0)
								{
									n += m_pVertexArray->getPolygon((z - 1) * (bmp.Width - 1) + x + 1)->getPlane().N;
									normal_count++;
								}
							}
							if (z > 0)
							{
								n += m_pVertexArray->getPolygon((z - 1) * (bmp.Width - 1) + x)->getPlane().N;
								normal_count++;
							}
							n /= (float)normal_count;
							m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x)->getVertex(2)->putNormal(n);
							// Vertex4
							n = Vec3f{ 0, 0, 0 };
							normal_count = 0;
							n += m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x)->getPlane().N;
							normal_count++;
							if (x < bmp.Width - 2)
							{
								n += m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x + 1)->getPlane().N;
								normal_count++;
								if (z < bmp.Height - 2)
								{
									n += m_pVertexArray->getPolygon((z + 1) * (bmp.Width - 1) + x + 1)->getPlane().N;
									normal_count++;
								}
							}
							if (z < bmp.Height - 2)
							{
								n += m_pVertexArray->getPolygon((z + 1) * (bmp.Width - 1) + x)->getPlane().N;
								normal_count++;
							}
							n /= (float)normal_count;
							m_pVertexArray->getPolygon(z * (bmp.Width - 1) + x)->getVertex(3)->putNormal(n);
						}
					m_bValid = true;
				}
				IVertexArray *old{ renderer->ActiveVertexArray };
				renderer->ActivateVertexArray(m_pVertexArray);
				m_pVertexArray->RenderPolygons();
				renderer->ActivateVertexArray(old);
			}
		}
	#pragma endregion
	}
}