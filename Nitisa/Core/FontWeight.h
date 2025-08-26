// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Strings.h"

namespace nitisa
{
	enum class FontWeight // Font weight(each one is bolder then prev one)
	{
		Thin,
		ExtraLight,
		Light,
		Normal,
		Medium,
		SemiBold,
		Bold,
		ExtraBold,
		Heavy
	};

	String FontWeightToString(const FontWeight value);
}