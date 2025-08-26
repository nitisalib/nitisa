// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Interfaces/IScreen.h"
#include "Nitisa/Math/Point.h"

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			class CScreen :public virtual IScreen
			{
			public:
				int getWidth() override;
				int getHeight() override;
				Point getDPI() override; // Return { 96, 96 }
			};
		}
	}
}
#endif