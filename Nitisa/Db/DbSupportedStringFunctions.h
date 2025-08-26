// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	struct DbSupportedStringFunctions
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool Convert;
		bool Lower;
		bool Upper;
		bool SubString;
		bool Translate;
		bool TrimBoth;
		bool TrimLeading;
		bool TrimTrailing;

		explicit operator String() const;
	};
}