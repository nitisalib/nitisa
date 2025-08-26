// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Interfaces/IScreen.h"
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

			class CScreen :public virtual IScreen
			{
			private:
				CApplication *m_pApplication;
			public:
				int getWidth() override;
				int getHeight() override;
				Point getDPI() override;

				CScreen(CApplication *application);
			};
		}
	}
}
#endif