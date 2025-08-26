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
	TextAlign StringToTextAlign(const String &value)
	{
		if (value == L"TextAlign::Center")
			return TextAlign::Center;
		if (value == L"TextAlign::Right")
			return TextAlign::Right;
		return TextAlign::Left;
	}

	String TextAlignToString(const TextAlign value)
	{
		switch (value)
		{
		case TextAlign::Center:		return L"TextAlign::Center";
		case TextAlign::Right:		return L"TextAlign::Right";
		default:					return L"TextAlign::Left";
		}
	}

	StringArray TextAlignItems()
	{
		return StringArray{
			L"TextAlign::Left",
			L"TextAlign::Center",
			L"TextAlign::Right" };
	}
}