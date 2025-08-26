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
		CBox::CBox() :
			C3DControl(L"Box"),
			m_cPrimitive{ this }
		{
			
		}

		CBox::CBox(IControl *parent) :CBox()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IBox getters
		float CBox::getBoxWidth()
		{
			return m_cPrimitive.Width;
		}

		float CBox::getBoxHeight()
		{
			return m_cPrimitive.Height;
		}

		float CBox::getBoxDepth()
		{
			return m_cPrimitive.Depth;
		}

		int CBox::getWidthSegments()
		{
			return m_cPrimitive.WidthSegments;
		}

		int CBox::getHeightSegments()
		{
			return m_cPrimitive.HeightSegments;
		}

		int CBox::getDepthSegments()
		{
			return m_cPrimitive.DepthSegments;
		}
	#pragma endregion

	#pragma region IBox setters
		bool CBox::setBoxWidth(const float value)
		{
			if (m_cPrimitive.setWidth(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CBox::setBoxHeight(const float value)
		{
			if (m_cPrimitive.setHeight(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CBox::setBoxDepth(const float value)
		{
			if (m_cPrimitive.setDepth(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CBox::setBoxSize(const float width, const float height, const float depth)
		{
			if (m_cPrimitive.setSize(width, height, depth))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CBox::setWidthSegments(const int value)
		{
			if (m_cPrimitive.setWidthSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CBox::setHeightSegments(const int value)
		{
			if (m_cPrimitive.setHeightSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CBox::setDepthSegments(const int value)
		{
			if (m_cPrimitive.setDepthSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CBox::setSegments(const int width, const int height, const int depth)
		{
			if (m_cPrimitive.setSegments(width, height, depth))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CBox::FreeResources(COpenGL *graphics)
		{
			m_cPrimitive.FreeResources();
		}
	#pragma endregion

	#pragma region Render
		void CBox::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			m_cPrimitive.Render();
		}
	#pragma endregion
	}
}