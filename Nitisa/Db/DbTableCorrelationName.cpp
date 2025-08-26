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
	String ToString(const DbTableCorrelationName value)
	{
		switch (value)
		{
		case DbTableCorrelationName::None: return L"None";
		case DbTableCorrelationName::Different: return L"Different";
		case DbTableCorrelationName::Any: return L"Any";
		default: return L"Unknown";
		}
	}
}