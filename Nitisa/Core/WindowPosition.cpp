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
	String WindowPositionToString(const WindowPosition value)
	{
		switch (value)
		{
		case WindowPosition::ScreenLeftTop:			return L"WindowPosition::ScreenLeftTop";
		case WindowPosition::ScreenRightTop:		return L"WindowPosition::ScreenRightTop";
		case WindowPosition::ScreenLeftBottom:		return L"WindowPosition::ScreenLeftBottom";
		case WindowPosition::ScreenRightBottom:		return L"WindowPosition::ScreenRightBottom";
		case WindowPosition::ScreenCenter:			return L"WindowPosition::ScreenCenter";
		case WindowPosition::MainFormLeftTop:		return L"WindowPosition::MainFormLeftTop";
		case WindowPosition::MainFormRightTop:		return L"WindowPosition::MainFormRightTop";
		case WindowPosition::MainFormLeftBottom:	return L"WindowPosition::MainFormLeftBottom";
		case WindowPosition::MainFormRightBottom:	return L"WindowPosition::MainFormRightBottom";
		case WindowPosition::MainFormCenter:		return L"WindowPosition::MainFormCenter";
		default:									return L"WindowPosition::Custom";
		}
	}

	WindowPosition StringToWindowPosition(const String &value)
	{
		if (value == L"WindowPosition::ScreenLeftTop")
			return WindowPosition::ScreenLeftTop;
		if (value == L"WindowPosition::ScreenRightTop")
			return WindowPosition::ScreenRightTop;
		if (value == L"WindowPosition::ScreenLeftBottom")
			return WindowPosition::ScreenLeftBottom;
		if (value == L"WindowPosition::ScreenRightBottom")
			return WindowPosition::ScreenRightBottom;
		if (value == L"WindowPosition::ScreenCenter")
			return WindowPosition::ScreenCenter;
		if (value == L"WindowPosition::MainFormLeftTop")
			return WindowPosition::MainFormLeftTop;
		if (value == L"WindowPosition::MainFormRightTop")
			return WindowPosition::MainFormRightTop;
		if (value == L"WindowPosition::MainFormLeftBottom")
			return WindowPosition::MainFormLeftBottom;
		if (value == L"WindowPosition::MainFormRightBottom")
			return WindowPosition::MainFormRightBottom;
		if (value == L"WindowPosition::MainFormCenter")
			return WindowPosition::MainFormCenter;
		return WindowPosition::Custom;
	}

	StringArray WindowPositionItems()
	{
		return StringArray{
			L"WindowPosition::ScreenLeftTop",
			L"WindowPosition::ScreenRightTop",
			L"WindowPosition::ScreenLeftBottom",
			L"WindowPosition::ScreenRightBottom",
			L"WindowPosition::ScreenCenter",
			L"WindowPosition::MainFormLeftTop",
			L"WindowPosition::MainFormRightTop",
			L"WindowPosition::MainFormLeftBottom",
			L"WindowPosition::MainFormRightBottom",
			L"WindowPosition::MainFormCenter",
			L"WindowPosition::Custom" };
	}
}