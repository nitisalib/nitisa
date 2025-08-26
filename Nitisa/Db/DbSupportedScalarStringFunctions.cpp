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
	DbSupportedScalarStringFunctions::operator String() const
	{
		StringArray list;
		if (ASCII) list.push_back(L"ASCII");
		if (BitLength) list.push_back(L"BitLength");
		if (Char) list.push_back(L"Char");
		if (CharLength) list.push_back(L"CharLength");
		if (CharacterLength) list.push_back(L"CharacterLength");
		if (Concat) list.push_back(L"Concat");
		if (Difference) list.push_back(L"Difference");
		if (Insert) list.push_back(L"Insert");
		if (LCase) list.push_back(L"LCase");
		if (Left) list.push_back(L"Left");
		if (Length) list.push_back(L"Length");
		if (Locate) list.push_back(L"Locate");
		if (Locate2) list.push_back(L"Locate2");
		if (LTrim) list.push_back(L"LTrim");
		if (OctetLength) list.push_back(L"OctetLength");
		if (Position) list.push_back(L"Position");
		if (Repeat) list.push_back(L"Repeat");
		if (Replace) list.push_back(L"Replace");
		if (Right) list.push_back(L"Right");
		if (RTrim) list.push_back(L"RTrim");
		if (SoundEx) list.push_back(L"SoundEx");
		if (Space) list.push_back(L"Space");
		if (SubString) list.push_back(L"SubString");
		if (UCase) list.push_back(L"UCase");
		return Implode(L", ", list);
	}
}