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
	String GradientTypeToString(const GradientType value)
	{
		switch (value)
		{
		case GradientType::Horizontal:		return L"GradientType::Horizontal";
		case GradientType::Vertical:		return L"GradientType::Vertical";
		case GradientType::Radial:			return L"GradientType::Radial";
		case GradientType::DiagonalDown:	return L"GradientType::DiagonalDown";
		case GradientType::DiagonalUp:		return L"GradientType::DiagonalUp";
		case GradientType::Circle:			return L"GradientType::Circle";
		}
		return L"";
	}
}