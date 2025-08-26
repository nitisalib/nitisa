// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Interfaces/IMouse.h"
#include "Nitisa/Math/Point.h"

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			class CApplication;

			class CMouse :public virtual IMouse
			{
				friend CApplication;
			private:
				Point m_sPosition;
			public:
				Point getPosition() override; // Return last known primary pointer position
				bool setPosition(const Point &value) override; // Only stores the value. Doesn't update mouse pointer because there is no one on Android

				CMouse();
			};
		}
	}
}
#endif