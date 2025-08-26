// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Hotkey.h"

namespace nitisa
{
	namespace standard
	{
		class IFormHotkeyList
		{
		protected:
			IFormHotkeyList() = default;
			~IFormHotkeyList() = default;
			IFormHotkeyList(const IFormHotkeyList &other) = delete;
			IFormHotkeyList(IFormHotkeyList &&other) = delete;
			IFormHotkeyList &operator=(const IFormHotkeyList &other) = delete;
			IFormHotkeyList &operator=(IFormHotkeyList &&other) = delete;
		public:
			virtual int getHotkeyCount() = 0; // Return hotkey count
			virtual Hotkey getHotkey(const int index) = 0; // Return hotkey by index

			virtual bool AddHotkey(const Hotkey &value) = 0; // Add hotkey
			virtual bool DeleteHotkey(const int index) = 0; // Delete hotkey by index
			virtual bool DeleteHotkeys() = 0; // Delete all hotkeys

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}