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
	String ToString(const DbStatus value)
	{
		switch (value)
		{
		case DbStatus::Initialized: return L"Initialized";
		case DbStatus::Unsupported: return L"Unsupported";
		case DbStatus::Error: return L"Error";
		default: return L"Uninitialized";
		}
	}
}