// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Interfaces/IMouse.h"
#include "Nitisa/Math/Point.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			class CApplication;

			class CMouse :public virtual IMouse
			{
			private:
				CApplication *m_pApplication;
			public:
				Point getPosition() override;
				bool setPosition(const Point &value) override;

				CMouse(CApplication *application);
			};
		}
	}
}
#endif