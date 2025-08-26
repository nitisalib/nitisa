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
		CJsonMesh::CJsonMesh() :
			C3DControl(L"JsonMesh"),
			m_pVertexArray{ nullptr },
			m_bValid{ false }
		{

		}

		CJsonMesh::CJsonMesh(IControl *parent) :CJsonMesh()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IJsonMesh getters
		String CJsonMesh::getFilename()
		{
			return m_sFilename;
		}
	#pragma endregion

	#pragma region IJsonMesh setters
		bool CJsonMesh::setFilename(const String &value)
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
		void CJsonMesh::FreeResources(COpenGL *graphics)
		{
			if (m_pVertexArray)
			{
				m_pVertexArray->Release();
				m_pVertexArray = nullptr;
				m_bValid = false;
			}
		}

		void CJsonMesh::VariantToVertexArray(IVertexArray *va, const Variant &content)
		{
			if (content.isSet(L"Polygons") && content.get(L"Polygons").getType() == Variant::VariantType::Array)
				for (auto &polygon : content.get(L"Polygons"))
					if (polygon.second.isSet(L"Vertices") && polygon.second.get(L"Vertices").getType() == Variant::VariantType::Array)
					{
						IPolygon *p{ va->AddPolygon() };
						bool has_n{ true };
						for (auto &vertex : polygon.second.get(L"Vertices"))
							if (vertex.second.isSet(L"Position") && vertex.second.get(L"Position").isSet(L"X") && vertex.second.get(L"Position").isSet(L"Y") && vertex.second.get(L"Position").isSet(L"Z"))
							{
								Vec3f v, n;
								Vec2f t;
								v.X = float(vertex.second.get(L"Position").get(L"X"));
								v.Y = float(vertex.second.get(L"Position").get(L"Y"));
								v.Z = float(vertex.second.get(L"Position").get(L"Z"));
								if (vertex.second.isSet(L"Normal") && vertex.second.get(L"Normal").isSet(L"Nx") && vertex.second.get(L"Normal").isSet(L"Ny") && vertex.second.get(L"Normal").isSet(L"Nz"))
								{
									n.X = float(vertex.second.get(L"Normal").get(L"Nx"));
									n.Y = float(vertex.second.get(L"Normal").get(L"Ny"));
									n.Z = float(vertex.second.get(L"Normal").get(L"Nz"));
								}
								else
									has_n = false;
								if (vertex.second.isSet(L"Texture") && vertex.second.get(L"Texture").isSet(L"Tx") && vertex.second.get(L"Texture").isSet(L"Ty"))
								{
									t.X = float(vertex.second.get(L"Texture").get(L"Tx"));
									t.Y = float(vertex.second.get(L"Texture").get(L"Yy"));
								}
								else
									t = Vec2f{ 0, 0 };
								p->AddVertex()->putPosition3D(v)->putNormal(n)->putTextureCoords(t);
							}
						if (p->getVertexCount() >= 3 && !has_n)
							for (size_t i = 0; i < p->getVertexCount(); i++)
								p->getVertex(i)->putNormal(p->getPlane().N);
					}
		}
	#pragma endregion

	#pragma region Render
		void CJsonMesh::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
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
					Variant content;
					json_decode(GetUTF8FileContent(m_sFilename), content);
					VariantToVertexArray(m_pVertexArray, content);
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