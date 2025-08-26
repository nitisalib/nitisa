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
	VerticalAlign StringToVerticalAlign(const String &value)
	{
		if (value == L"VerticalAlign::Middle")
			return VerticalAlign::Middle;
		if (value == L"VerticalAlign::Bottom")
			return VerticalAlign::Bottom;
		return VerticalAlign::Top;
	}

	String VerticalAlignToString(const VerticalAlign value)
	{
		switch (value)
		{
		case VerticalAlign::Middle: return L"VerticalAlign::Middle";
		case VerticalAlign::Bottom: return L"VerticalAlign::Bottom";
		default:					return L"VerticalAlign::Top";
		}
	}

	StringArray VerticalAlignItems()
	{
		return StringArray{
			L"VerticalAlign::Top",
			L"VerticalAlign::Middle",
			L"VerticalAlign::Bottom" };
	}
}