// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Key.h"
#include "Strings.h"
#include "Variant.h"
#include <iostream>

namespace nitisa
{
	struct Hotkey
	{
		nitisa::Key Key; // Key
		bool Ctrl; // Ctrl key down state
		bool Alt; // Alt/Menu key down state
		bool Shift; // Shift key down state
		bool Down; // Down or release event

		bool operator==(const Hotkey &other) const // Check if hotkeys are equal
		{
			return Key == other.Key && Ctrl == other.Ctrl && Alt == other.Alt && Shift == other.Shift && Down == other.Down;
		}

		bool operator!=(const Hotkey &other) const // Check if hotkeys are not equal
		{
			return Key != other.Key || Ctrl != other.Ctrl || Alt != other.Alt || Shift != other.Shift || Down != other.Down;
		}
	};

	std::wostream &operator<<(std::wostream &stream, const Hotkey &a); // Output as source code

	String AsSourceCode(const Hotkey &a);
	String ToString(const Hotkey &value);
	Variant ToVariant(const Hotkey &value);
	void FromVariant(const Variant &value, Hotkey &dest);
}