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
	String RotateOrderToString(const RotateOrder value)
	{
		switch (value)
		{
		case RotateOrder::XYZ:
			return L"RotateOrder::XYZ";
		case RotateOrder::XZY:
			return L"RotateOrder::XZY";
		case RotateOrder::YXZ:
			return L"RotateOrder::YXZ";
		case RotateOrder::YZX:
			return L"RotateOrder::YZX";
		case RotateOrder::ZXY:
			return L"RotateOrder::ZXY";
		case RotateOrder::ZYX:
			return L"RotateOrder::ZYX";
		}
		return L"";
	}

	RotateOrder StringToRotateOrder(const String &value)
	{
		if (value == L"RotateOrder::XZY") 
			return RotateOrder::XZY;
		if (value == L"RotateOrder::YXZ")
			return RotateOrder::YXZ;
		if (value == L"RotateOrder::YZX")
			return RotateOrder::YZX;
		if (value == L"RotateOrder::ZXY")
			return RotateOrder::ZXY;
		if (value == L"RotateOrder::ZYX")
			return RotateOrder::ZYX;
		return RotateOrder::XYZ;
	}

	StringArray RotateOrderItems()
	{
		return StringArray{
			L"RotateOrder::XYZ",
			L"RotateOrder::XZY",
			L"RotateOrder::YXZ",
			L"RotateOrder::YZX",
			L"RotateOrder::ZXY",
			L"RotateOrder::ZYX" };
	}
}