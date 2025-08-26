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
	String TransformOrderToString(const TransformOrder value)
	{
		switch (value)
		{
		case TransformOrder::SRT:
			return L"TransformOrder::SRT";
		case TransformOrder::STR:
			return L"TransformOrder::STR";
		case TransformOrder::RST:
			return L"TransformOrder::RST";
		case TransformOrder::RTS:
			return L"TransformOrder::RTS";
		case TransformOrder::TSR:
			return L"TransformOrder::TSR";
		case TransformOrder::TRS:
			return L"TransformOrder::TRS";
		}
		return L"";
	}

	TransformOrder StringToTransformOrder(const String &value)
	{
		if (value == L"TransformOrder::STR")
			return TransformOrder::STR;
		if (value == L"TransformOrder::RST")
			return TransformOrder::RST;
		if (value == L"TransformOrder::RTS")
			return TransformOrder::RTS;
		if (value == L"TransformOrder::TSR")
			return TransformOrder::TSR;
		if (value == L"TransformOrder::TRS")
			return TransformOrder::TRS;
		return TransformOrder::SRT;
	}

	StringArray TransformOrderItems()
	{
		return StringArray{
			L"TransformOrder::SRT",
			L"TransformOrder::STR",
			L"TransformOrder::RST",
			L"TransformOrder::RTS",
			L"TransformOrder::TSR",
			L"TransformOrder::TRS" };
	}
}