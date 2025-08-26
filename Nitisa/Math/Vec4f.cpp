// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	String AsSourceCode(const Vec4f &a)
	{
		return L"Vec4f{ " + AsSourceCode(a.X) + L", " + AsSourceCode(a.Y) + L", " + AsSourceCode(a.Z) + L", " + AsSourceCode(a.W) + L" }";
	}
}