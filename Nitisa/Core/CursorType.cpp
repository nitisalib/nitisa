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
	CursorType StringToCursorType(const String &value)
	{
		if (value == L"CursorType::AppStarting")
			return CursorType::AppStarting;
		if (value == L"CursorType::Arrow")
			return CursorType::Arrow;
		if (value == L"CursorType::Cross")
			return CursorType::Cross;
		if (value == L"CursorType::Hand")
			return CursorType::Hand;
		if (value == L"CursorType::Help")
			return CursorType::Help;
		if (value == L"CursorType::IBeam")
			return CursorType::IBeam;
		if (value == L"CursorType::No")
			return CursorType::No;
		if (value == L"CursorType::SizeAll")
			return CursorType::SizeAll;
		if (value == L"CursorType::SizeNortheastSouthwest")
			return CursorType::SizeNortheastSouthwest;
		if (value == L"CursorType::SizeNorthSouth")
			return CursorType::SizeNorthSouth;
		if (value == L"CursorType::SizeNorthwestSoutheast")
			return CursorType::SizeNorthwestSoutheast;
		if (value == L"CursorType::SizeWestEast")
			return CursorType::SizeWestEast;
		if (value == L"CursorType::UpArrow")
			return CursorType::UpArrow;
		if (value == L"CursorType::Wait")
			return CursorType::Wait;
		return CursorType::None;
	}

	String CursorTypeToString(const CursorType value)
	{
		switch (value)
		{
		case CursorType::AppStarting:				return L"CursorType::AppStarting";
		case CursorType::Arrow:						return L"CursorType::Arrow";
		case CursorType::Cross:						return L"CursorType::Cross";
		case CursorType::Hand:						return L"CursorType::Hand";
		case CursorType::Help:						return L"CursorType::Help";
		case CursorType::IBeam:						return L"CursorType::IBeam";
		case CursorType::No:						return L"CursorType::No";
		case CursorType::SizeAll:					return L"CursorType::SizeAll";
		case CursorType::SizeNortheastSouthwest:	return L"CursorType::SizeNortheastSouthwest";
		case CursorType::SizeNorthSouth:			return L"CursorType::SizeNorthSouth";
		case CursorType::SizeNorthwestSoutheast:	return L"CursorType::SizeNorthwestSoutheast";
		case CursorType::SizeWestEast:				return L"CursorType::SizeWestEast";
		case CursorType::UpArrow:					return L"CursorType::UpArrow";
		case CursorType::Wait:						return L"CursorType::Wait";
		default:									return L"CursorType::None";
		}
	}

	StringArray CursorTypeItems()
	{
		return StringArray{
			L"CursorType::None",
			L"CursorType::AppStarting",
			L"CursorType::Arrow",
			L"CursorType::Cross",
			L"CursorType::Hand",
			L"CursorType::Help",
			L"CursorType::IBeam",
			L"CursorType::No",
			L"CursorType::SizeAll",
			L"CursorType::SizeNortheastSouthwest",
			L"CursorType::SizeNorthSouth",
			L"CursorType::SizeNorthwestSoutheast",
			L"CursorType::SizeWestEast",
			L"CursorType::UpArrow",
			L"CursorType::Wait" };
	}
}