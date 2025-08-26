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
	String ScrollVisibilityToString(const ScrollVisibility value)
	{
		switch (value)
		{
		case ScrollVisibility::Auto:		return L"ScrollVisibility::Auto";
		case ScrollVisibility::Visible:		return L"ScrollVisibility::Visible";
		default:							return L"ScrollVisibility::None";
		}
	}

	ScrollVisibility StringToScrollVisibility(const String &value)
	{
		if (value == L"ScrollVisibility::Visible")
			return ScrollVisibility::Visible;
		if (value == L"ScrollVisibility::None")
			return ScrollVisibility::None;
		return ScrollVisibility::Auto;
	}

	StringArray ScrollVisibilityItems()
	{
		return StringArray{
			L"ScrollVisibility::Auto",
			L"ScrollVisibility::Visible",
			L"ScrollVisibility::None" };
	}
}