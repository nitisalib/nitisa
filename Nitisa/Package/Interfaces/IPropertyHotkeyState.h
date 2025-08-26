// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Core/Hotkey.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyHotkeyState :public virtual IPropertyState
	{
	protected:
		IPropertyHotkeyState() = default;
		~IPropertyHotkeyState() = default;
		IPropertyHotkeyState(const IPropertyHotkeyState &other) = delete;
		IPropertyHotkeyState(IPropertyHotkeyState &&other) = delete;
		IPropertyHotkeyState &operator=(const IPropertyHotkeyState &other) = delete;
		IPropertyHotkeyState &operator=(IPropertyHotkeyState &&other) = delete;
	public:
		virtual Hotkey getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const Hotkey value) = 0; // Set value of state
	};
}