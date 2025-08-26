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
		CTorus::CTorus() :
			C3DControl(L"Torus"),
			m_cPrimitive{ this }
		{

		}

		CTorus::CTorus(IControl *parent) :CTorus()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region ITorus getters
		float CTorus::getTorusRadius1()
		{
			return m_cPrimitive.Radius1;
		}

		float CTorus::getTorusRadius2()
		{
			return m_cPrimitive.Radius2;
		}

		int CTorus::getTorusSides1()
		{
			return m_cPrimitive.Sides1;
		}

		int CTorus::getTorusSides2()
		{
			return m_cPrimitive.Sides2;
		}
	#pragma endregion

	#pragma region ITorus setters
		bool CTorus::setTorusRadius1(const float value)
		{
			if (m_cPrimitive.setRadius1(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTorus::setTorusRadius2(const float value)
		{
			if (m_cPrimitive.setRadius2(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTorus::setTorusSides1(const int value)
		{
			if (m_cPrimitive.setSides1(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTorus::setTorusSides2(const int value)
		{
			if (m_cPrimitive.setSides2(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CTorus::setTorusSize(const float radius1, const float radius2, const int sides1, const int sides2)
		{
			if (m_cPrimitive.setSize(radius1, radius2, sides1, sides2))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CTorus::FreeResources(COpenGL *graphics)
		{
			m_cPrimitive.FreeResources();
		}
	#pragma endregion

	#pragma region Render
		void CTorus::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			m_cPrimitive.Render();
		}
	#pragma endregion
	}
}