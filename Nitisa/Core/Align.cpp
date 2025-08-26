// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	Align StringToAlign(const String &value)
	{
		if (value == L"Align::Left")
			return Align::Left;
		if (value == L"Align::Top")
			return Align::Top;
		if (value == L"Align::Right")
			return Align::Right;
		if (value == L"Align::Bottom")
			return Align::Bottom;
		if (value == L"Align::Client")
			return Align::Client;
		return Align::None;
	}

	String AlignToString(const Align value)
	{
		switch (value)
		{
		case Align::Left:		return L"Align::Left";
		case Align::Top:		return L"Align::Top";
		case Align::Right:		return L"Align::Right";
		case Align::Bottom:		return L"Align::Bottom";
		case Align::Client:		return L"Align::Client";
		default:				return L"Align::None";
		}
	}

	StringArray AlignItems()
	{
		return StringArray{
			L"Align::None",
			L"Align::Left",
			L"Align::Top",
			L"Align::Right",
			L"Align::Bottom",
			L"Align::Client" };
	}
}