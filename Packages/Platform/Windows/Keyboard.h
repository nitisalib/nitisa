// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Core/Key.h"
#include "Nitisa/Interfaces/IKeyboard.h"

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			class CKeyboard :public virtual IKeyboard
			{
			public:
				bool isDown(const Key key) override;
				bool isToggled(const Key key) override;
				void getControlKeys(bool &ctrl, bool &alt, bool &shift) override;
			};
		}
	}
}
#endif