// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Hotkey.h"
#include "Nitisa/Package/Interfaces/IProperty.h"

namespace nitisa
{
	namespace standard
	{
		class IPropertyHotkeyList :public virtual IProperty
		{
		protected:
			IPropertyHotkeyList() = default;
			~IPropertyHotkeyList() = default;
			IPropertyHotkeyList(const IPropertyHotkeyList &other) = delete;
			IPropertyHotkeyList(IPropertyHotkeyList &&other) = delete;
			IPropertyHotkeyList &operator=(const IPropertyHotkeyList &other) = delete;
			IPropertyHotkeyList &operator=(IPropertyHotkeyList &&other) = delete;
		public:
			virtual int getCount() = 0; // Return hotkey count
			virtual Hotkey getHotkey(const int index) = 0; // Return hotkey by index

			virtual int Add(Hotkey data) = 0; // Add hotkey
			virtual bool Delete(const int index) = 0; // Delete hotkey by index
			virtual bool Clear() = 0; // Delete all hotkeys
		};
	}
}