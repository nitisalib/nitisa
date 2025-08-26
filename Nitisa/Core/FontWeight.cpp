// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	String FontWeightToString(const FontWeight value)
	{
		switch (value)
		{
		case FontWeight::Thin: return L"FontWeight::Thin";
		case FontWeight::ExtraLight: return L"FontWeight::ExtraLight";
		case FontWeight::Light: return L"FontWeight::Light";
		case FontWeight::Medium: return L"FontWeight::Medium";
		case FontWeight::SemiBold: return L"FontWeight::SemiBold";
		case FontWeight::Bold: return L"FontWeight::Bold";
		case FontWeight::ExtraBold: return L"FontWeight::ExtraBold";
		case FontWeight::Heavy: return L"FontWeight::Heavy";
		default: return L"FontWeight::Normal";
		}
	}
}