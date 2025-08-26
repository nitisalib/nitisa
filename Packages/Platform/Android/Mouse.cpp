// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

#ifdef __ANDROID__
namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			CMouse::CMouse() :
				m_sPosition{ -1, -1 }
			{

			}

			Point CMouse::getPosition()
			{
				return m_sPosition;
			}

			bool CMouse::setPosition(const Point &value)
			{
				if (value != m_sPosition)
				{
					m_sPosition = value;
					return true;
				}
				return false;
			}
		}
	}
}
#endif