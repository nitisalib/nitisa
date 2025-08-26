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
	struct DbSupportedRelationJoinOperators
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool CorrespondingClause;
		bool CrossJoin;
		bool ExceptJoin;
		bool FullOuterJoin;
		bool InnerJoin;
		bool IntersectJoin;
		bool LeftOuterJoin;
		bool NaturalJoin;
		bool RightOuterJoin;
		bool UnionJoin;

		explicit operator String() const;
	};
}