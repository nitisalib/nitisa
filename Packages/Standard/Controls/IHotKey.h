// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Hotkey.h"
#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IHotKey :public virtual IControl
		{
		protected:
			IHotKey() = default;
			~IHotKey() = default;
			IHotKey(const IHotKey &other) = delete;
			IHotKey(IHotKey &&other) = delete;
			IHotKey &operator=(const IHotKey &other) = delete;
			IHotKey &operator=(IHotKey &&other) = delete;
		public:
			virtual Hotkey getHotKey() = 0; // Return hotkey

			virtual bool setHotKey(const Hotkey &value) = 0; // Set hotkey. Hotkey.Down isn't used
		};
	}
}