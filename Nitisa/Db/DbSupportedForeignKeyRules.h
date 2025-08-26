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
	struct DbSupportedForeignKeyRules
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool Cascade;
		bool NoAction;
		bool SetDefault;
		bool SetNull;

		explicit operator String() const;
	};
}