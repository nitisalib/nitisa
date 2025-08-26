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
		CCone::CCone() :
			C3DControl(L"Cone"),
			m_cPrimitive{ this }
		{

		}

		CCone::CCone(IControl *parent) :CCone()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region ICone getters
		float CCone::getConeRadius1()
		{
			return m_cPrimitive.Radius1;
		}

		float CCone::getConeRadius2()
		{
			return m_cPrimitive.Radius2;
		}

		float CCone::getConeHeight()
		{
			return m_cPrimitive.Height;
		}

		int CCone::getConeSides()
		{
			return m_cPrimitive.Sides;
		}

		int CCone::getCapSegments()
		{
			return m_cPrimitive.CapSegments;
		}

		int CCone::getHeightSegments()
		{
			return m_cPrimitive.HeightSegments;
		}
	#pragma endregion

	#pragma region ICone setters
		bool CCone::setConeRadius1(const float value)
		{
			if (m_cPrimitive.setRadius1(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCone::setConeRadius2(const float value)
		{
			if (m_cPrimitive.setRadius2(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCone::setConeHeight(const float value)
		{
			if (m_cPrimitive.setHeight(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCone::setConeSides(const int value)
		{
			if (m_cPrimitive.setSides(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCone::setConeSize(const float radius1, const float radius2, const float height, const int sides)
		{
			if (m_cPrimitive.setSize(radius1, radius2, height, sides))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCone::setCapSegments(const int value)
		{
			if (m_cPrimitive.setCapSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCone::setHeightSegments(const int value)
		{
			if (m_cPrimitive.setHeightSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCone::setSegments(const int cap, const int height)
		{
			if (m_cPrimitive.setSegments(cap, height))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CCone::FreeResources(COpenGL *graphics)
		{
			m_cPrimitive.FreeResources();
		}
	#pragma endregion

	#pragma region Render
		void CCone::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			m_cPrimitive.Render();
		}
	#pragma endregion
	}
}