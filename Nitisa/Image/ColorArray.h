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
#include "Color.h"
#include <vector>

namespace nitisa
{
	using ColorArray = std::vector<Color>;

	String AsSourceCode(const ColorArray &a);
	String ToString(const ColorArray &value);
	Variant ToVariant(const ColorArray &value);
	void FromVariant(const Variant &value, ColorArray &dest);
}