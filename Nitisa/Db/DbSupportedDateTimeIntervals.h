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
	struct DbSupportedDateTimeIntervals
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool SecondFracture;
		bool Second;
		bool Minute;
		bool Hour;
		bool Day;
		bool Week;
		bool Month;
		bool Quarter;
		bool Year;

		explicit operator String() const;
	};
}