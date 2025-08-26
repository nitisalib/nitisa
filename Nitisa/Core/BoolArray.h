// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Strings.h"
#include "Variant.h"
#include <vector>

namespace nitisa
{
	using BoolArray = std::vector<bool>;

	String AsSourceCode(const BoolArray &a);
	String ToString(const BoolArray &value);
	Variant ToVariant(const BoolArray &value);
	void FromVariant(const Variant &value, BoolArray &dest);
}