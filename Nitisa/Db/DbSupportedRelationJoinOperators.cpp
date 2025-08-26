// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	DbSupportedRelationJoinOperators::operator String() const
	{
		StringArray list;
		if (CorrespondingClause) list.push_back(L"CorrespondingClause");
		if (CrossJoin) list.push_back(L"CrossJoin");
		if (ExceptJoin) list.push_back(L"ExceptJoin");
		if (FullOuterJoin) list.push_back(L"FullOuterJoin");
		if (InnerJoin) list.push_back(L"InnerJoin");
		if (IntersectJoin) list.push_back(L"IntersectJoin");
		if (LeftOuterJoin) list.push_back(L"LeftOuterJoin");
		if (NaturalJoin) list.push_back(L"NaturalJoin");
		if (RightOuterJoin) list.push_back(L"RightOuterJoin");
		if (UnionJoin) list.push_back(L"UnionJoin");
		return Implode(L", ", list);
	}
}