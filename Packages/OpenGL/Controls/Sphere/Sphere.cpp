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
		CSphere::CSphere() :
			C3DControl(L"Sphere"),
			m_cPrimitive{ this }
		{

		}

		CSphere::CSphere(IControl *parent) :CSphere()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region ISphere getters
		float CSphere::getSphereRadius()
		{
			return m_cPrimitive.Radius;
		}

		int CSphere::getSphereSides()
		{
			return m_cPrimitive.Sides;
		}

		int CSphere::getSphereYSides()
		{
			return m_cPrimitive.YSides;
		}
	#pragma endregion

	#pragma region ISphere setters
		bool CSphere::setSphereRadius(const float value)
		{
			if (m_cPrimitive.setRadius(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CSphere::setSphereSides(const int value)
		{
			if (m_cPrimitive.setSides(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CSphere::setSphereYSides(const int value)
		{
			if (m_cPrimitive.setYSides(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CSphere::setSphereSize(const float radius, const int sides, const int y_sides)
		{
			if (m_cPrimitive.setSize(radius, sides, y_sides))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CSphere::FreeResources(COpenGL *graphics)
		{
			m_cPrimitive.FreeResources();
		}
	#pragma endregion

	#pragma region Render
		void CSphere::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			m_cPrimitive.Render();
		}
	#pragma endregion
	}
}