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
	String ToString(const DbSpecialColumnScope value)
	{
		switch (value)
		{
		case DbSpecialColumnScope::Transaction: return L"Transaction";
		case DbSpecialColumnScope::Session: return L"Session";
		default: return L"CurrentRow";
		}
	}
}