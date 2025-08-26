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
	struct DbSupportedPredicates
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool Between;
		bool Comparison;
		bool Exists;
		bool In;
		bool IsNotNull;
		bool IsNull;
		bool Like;
		bool MatchFull;
		bool MatchPartial;
		bool MatchUniqueFull;
		bool MatchUniquePartial;
		bool Overlaps;
		bool QuantifierComparison;
		bool Unique;

		explicit operator String() const;
	};
}