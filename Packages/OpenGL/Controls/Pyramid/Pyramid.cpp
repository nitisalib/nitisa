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
		CPyramid::CPyramid() :
			C3DControl(L"Pyramid"),
			m_cPrimitive{ this }
		{
			
		}

		CPyramid::CPyramid(IControl *parent) :CPyramid()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IPyramid getters
		float CPyramid::getPyramidWidth()
		{
			return m_cPrimitive.Width;
		}

		float CPyramid::getPyramidDepth()
		{
			return m_cPrimitive.Depth;
		}

		float CPyramid::getPyramidHeight()
		{
			return m_cPrimitive.Height;
		}

		int CPyramid::getHeightSegments()
		{
			return m_cPrimitive.Segments;
		}
	#pragma endregion

	#pragma region IPyramid setters
		bool CPyramid::setPyramidWidth(const float value)
		{
			if (m_cPrimitive.setWidth(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CPyramid::setPyramidDepth(const float value)
		{
			if (m_cPrimitive.setDepth(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CPyramid::setPyramidHeight(const float value)
		{
			if (m_cPrimitive.setHeight(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CPyramid::setPyramidSize(const float width, const float depth, const float height)
		{
			if (m_cPrimitive.setSize(width, depth, height))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CPyramid::setHeightSegments(const int value)
		{
			if (m_cPrimitive.setSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CPyramid::FreeResources(COpenGL *graphics)
		{
			m_cPrimitive.FreeResources();
		}
	#pragma endregion

	#pragma region Render
		void CPyramid::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			m_cPrimitive.Render();
		}
	#pragma endregion
	}
}