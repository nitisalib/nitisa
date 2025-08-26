// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Core/Variant.h"
#include <vector>

namespace nitisa
{
	using IntegerArray = std::vector<int>;

	String AsSourceCode(const IntegerArray &a);
	String ToString(const IntegerArray &value);
	Variant ToVariant(const IntegerArray &value);
	void FromVariant(const Variant &value, IntegerArray &dest);
}