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
		CCylinder::CCylinder() :
			C3DControl(L"Cylinder"),
			m_cPrimitive{ this }
		{
			
		}

		CCylinder::CCylinder(IControl *parent) :CCylinder()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region ICylinder getters
		float CCylinder::getCylinderRadius()
		{
			return m_cPrimitive.Radius;
		}

		float CCylinder::getCylinderHeight()
		{
			return m_cPrimitive.Height;
		}

		int CCylinder::getCylinderSides()
		{
			return m_cPrimitive.Sides;
		}

		int CCylinder::getCapSegments()
		{
			return m_cPrimitive.CapSegments;
		}

		int CCylinder::getHeightSegments()
		{
			return m_cPrimitive.HeightSegments;
		}
	#pragma endregion

	#pragma region ICylinder setters
		bool CCylinder::setCylinderRadius(const float value)
		{
			if (m_cPrimitive.setRadius(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCylinder::setCylinderHeight(const float value)
		{
			if (m_cPrimitive.setHeight(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCylinder::setCylinderSides(const int value)
		{
			if (m_cPrimitive.setSides(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCylinder::setCylinderSize(const float radius, const float height, const int sides)
		{
			if (m_cPrimitive.setSize(radius, height, sides))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCylinder::setCapSegments(const int value)
		{
			if (m_cPrimitive.setCapSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCylinder::setHeightSegments(const int value)
		{
			if (m_cPrimitive.setHeightSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCylinder::setSegments(const int cap, const int height)
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
		void CCylinder::FreeResources(COpenGL *graphics)
		{
			m_cPrimitive.FreeResources();
		}
	#pragma endregion

	#pragma region Render
		void CCylinder::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			m_cPrimitive.Render();
		}
	#pragma endregion
	}
}