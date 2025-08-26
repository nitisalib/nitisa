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
		CCircle::CCircle() :
			C3DControl(L"Circle"),
			m_cPrimitive{ this }
		{

		}

		CCircle::CCircle(IControl *parent) :CCircle()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region ICircle getters
		float CCircle::getCircleRadius()
		{
			return m_cPrimitive.Radius;
		}

		int CCircle::getCircleSides()
		{
			return m_cPrimitive.Sides;
		}

		int CCircle::getCapSegments()
		{
			return m_cPrimitive.Segments;
		}
	#pragma endregion

	#pragma region ICircle setters
		bool CCircle::setCircleRadius(const float value)
		{
			if (m_cPrimitive.setRadius(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCircle::setCircleSides(const int value)
		{
			if (m_cPrimitive.setSides(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCircle::setCircleSize(const float radius, const int sides)
		{
			if (m_cPrimitive.setSize(radius, sides))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCircle::setCapSegments(const int value)
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
		void CCircle::FreeResources(COpenGL *graphics)
		{
			m_cPrimitive.FreeResources();
		}
	#pragma endregion

	#pragma region Render
		void CCircle::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			m_cPrimitive.Render();
		}
	#pragma endregion
	}
}