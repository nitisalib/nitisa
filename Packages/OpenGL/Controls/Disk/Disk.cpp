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
		CDisk::CDisk() :
			C3DControl(L"Disk"),
			m_cPrimitive{ this }
		{

		}

		CDisk::CDisk(IControl *parent) :CDisk()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IDisk getters
		float CDisk::getDiskOuterRadius()
		{
			return m_cPrimitive.OuterRadius;
		}

		float CDisk::getDiskInnerRadius()
		{
			return m_cPrimitive.InnerRadius;
		}

		int CDisk::getDiskSides()
		{
			return m_cPrimitive.Sides;
		}

		int CDisk::getCapSegments()
		{
			return m_cPrimitive.Segments;
		}
	#pragma endregion

	#pragma region IDisk setters
		bool CDisk::setDiskOuterRadius(const float value)
		{
			if (m_cPrimitive.setOuterRadius(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CDisk::setDiskInnerRadius(const float value)
		{
			if (m_cPrimitive.setInnerRadius(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CDisk::setDiskSides(const int value)
		{
			if (m_cPrimitive.setSides(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CDisk::setDiskSize(const float outer_radius, const float inner_radius, const int sides)
		{
			if (m_cPrimitive.setSize(outer_radius, inner_radius, sides))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CDisk::setCapSegments(const int value)
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
		void CDisk::FreeResources(COpenGL *graphics)
		{
			m_cPrimitive.FreeResources();
		}
	#pragma endregion

	#pragma region Render
		void CDisk::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			m_cPrimitive.Render();
		}
	#pragma endregion
	}
}