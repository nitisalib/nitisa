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
		CMesh::CMesh() :
			C3DControl(L"Mesh"),
			m_pVertexArray{ nullptr }
		{

		}

		CMesh::CMesh(IControl *parent) :CMesh()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IMesh getters
		IVertexArray *CMesh::getVertexArray()
		{
			if (!m_pVertexArray && getForm() && getForm()->getRenderer())
				m_pVertexArray = getForm()->getRenderer()->CreateVertexArray(VertexFormat);
			return m_pVertexArray;
		}
	#pragma endregion

	#pragma region Helpers
		void CMesh::FreeResources(COpenGL *graphics)
		{
			if (m_pVertexArray)
			{
				m_pVertexArray->Release();
				m_pVertexArray = nullptr;
			}
		}
	#pragma endregion

	#pragma region Render
		void CMesh::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			if (m_pVertexArray)
			{
				IVertexArray *old{ renderer->ActiveVertexArray };
				renderer->ActivateVertexArray(m_pVertexArray);
				m_pVertexArray->RenderPolygons();
				renderer->ActivateVertexArray(old);
			}
		}
	#pragma endregion
	}
}