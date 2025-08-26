// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#include "Platform/OpenGL/OpenGL.h"

namespace nitisa
{
	namespace opengl
	{
	#pragma region Constructor & destructor
		C3DObject::C3DObject() :
			C3DControl(L"3DObject"),
			m_pVertexArray{ nullptr },
			m_ePrimitiveType{ PrimitiveType::Polygon }
		{

		}

		C3DObject::C3DObject(IControl *parent) :C3DObject()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region I3DObject getters
		IVertexArray *C3DObject::getVertexArray()
		{
			if (!m_pVertexArray && getForm() && getForm()->getRenderer())
				m_pVertexArray = getForm()->getRenderer()->CreateVertexArray(VertexFormat);
			return m_pVertexArray;
		}

		I3DObject::PrimitiveType C3DObject::getPrimitiveType() const
		{
			return m_ePrimitiveType;
		}
	#pragma endregion

	#pragma region I3DObject setters
		bool C3DObject::setPrimitiveType(const PrimitiveType &value)
		{
			if (value != m_ePrimitiveType)
			{
				m_ePrimitiveType = value;
				if (m_pVertexArray)
					QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void C3DObject::FreeResources(COpenGL *graphics)
		{
			if (m_pVertexArray)
			{
				m_pVertexArray->Release();
				m_pVertexArray = nullptr;
			}
		}
	#pragma endregion

	#pragma region Render
		void C3DObject::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			if (m_pVertexArray)
			{
				CStoreVertexArray s_va{ renderer };
				renderer->ActivateVertexArray(m_pVertexArray);
				switch (m_ePrimitiveType)
				{
				case PrimitiveType::Point:
					m_pVertexArray->RenderPoints();
					break;
				case PrimitiveType::Line:
					m_pVertexArray->RenderLines();
					break;
				case PrimitiveType::Wire:
					m_pVertexArray->RenderWires();
					break;
				default:
					m_pVertexArray->RenderPolygons();
				}
			}
		}
	#pragma endregion
	}
}