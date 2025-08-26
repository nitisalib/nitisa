// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	std::wostream &operator<<(std::wostream &stream, const Hotkey &a)
	{
		stream << L"{ " << KeyToString(a.Key) << L", " << ToString(a.Ctrl) << L", " << ToString(a.Alt) << L", " << ToString(a.Shift) << L", " << ToString(a.Down) << L" }";
		return stream;
	}

	String AsSourceCode(const Hotkey &a)
	{
		return L"Hotkey{ " + KeyToString(a.Key) + L", " + ToString(a.Ctrl) + L", " + ToString(a.Alt) + L", " + ToString(a.Shift) + L", " + ToString(a.Down) + L" }";
	}

	String ToString(const Hotkey &value)
	{
		String result;
		if (value.Key != Key::Unknown)
		{
			if (value.Ctrl)
			{
				if (!result.empty())
					result += L"+";
				result += L"Ctrl";
			}
			if (value.Alt)
			{
				if (!result.empty())
					result += L"+";
				result += L"Alt";
			}
			if (value.Shift)
			{
				if (!result.empty())
					result += L"+";
				result += L"Shift";
			}
			if (!result.empty())
				result += L"+";
			result += KeyToString(value.Key);
		}
		return result;
	}

	Variant ToVariant(const Hotkey &value)
	{
		Variant result;
		result[L"Key"] = KeyToString(value.Key);
		result[L"Ctrl"] = value.Ctrl;
		result[L"Alt"] = value.Alt;
		result[L"Shift"] = value.Shift;
		result[L"Down"] = value.Down;
		return result;
	}

	void FromVariant(const Variant &value, Hotkey &dest)
	{
		dest.Key = StringToKey(String(value.get(L"Key")));
		dest.Ctrl = bool(value.get(L"Ctrl"));
		dest.Alt = bool(value.get(L"Alt"));
		dest.Shift = bool(value.get(L"Shift"));
		dest.Down = bool(value.get(L"Down"));
	}
}