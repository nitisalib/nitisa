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
		CTube::CTube() :
			C3DControl(L"Tube"),
			m_cPrimitive{ this }
		{

		}

		CTube::CTube(IControl *parent) :CTube()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region ITube getters
		float CTube::getTubeOuterRadius()
		{
			return m_cPrimitive.OuterRadius;
		}

		float CTube::getTubeInnerRadius()
		{
			return m_cPrimitive.InnerRadius;
		}

		float CTube::getTubeHeight()
		{
			return m_cPrimitive.Height;
		}

		int CTube::getTubeSides()
		{
			return m_cPrimitive.Sides;
		}

		int CTube::getCapSegments()
		{
			return m_cPrimitive.CapSegments;
		}

		int CTube::getHeightSegments()
		{
			return m_cPrimitive.HeightSegments;
		}
	#pragma endregion

	#pragma region ITube setters
		bool CTube::setTubeOuterRadius(const float value)
		{
			if (m_cPrimitive.setOuterRadius(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTube::setTubeInnerRadius(const float value)
		{
			if (m_cPrimitive.setInnerRadius(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTube::setTubeHeight(const float value)
		{
			if (m_cPrimitive.setHeight(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTube::setTubeSides(const int value)
		{
			if (m_cPrimitive.setSides(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTube::setTubeSize(const float outer_radius, const float inner_radius, const float height, const int sides)
		{
			if (m_cPrimitive.setSize(outer_radius, inner_radius, height, sides))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTube::setCapSegments(const int value)
		{
			if (m_cPrimitive.setCapSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTube::setHeightSegments(const int value)
		{
			if (m_cPrimitive.setHeightSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTube::setSegments(const int cap, const int height)
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
		void CTube::FreeResources(COpenGL *graphics)
		{
			m_cPrimitive.FreeResources();
		}
	#pragma endregion

	#pragma region Render
		void CTube::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			m_cPrimitive.Render();
		}
	#pragma endregion
	}
}