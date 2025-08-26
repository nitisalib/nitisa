// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Interfaces/ISystem.h"

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			class CSystem :public virtual ISystem
			{
			public:
				CSystem();
			};
		}
	}
}
#endif