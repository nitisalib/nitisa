// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Interfaces/IMouse.h"
#include "Nitisa/Math/Point.h"

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			class CMouse :public virtual IMouse
			{
			public:
				Point getPosition() override;
				bool setPosition(const Point &value) override;
			};
		}
	}
}
#endif