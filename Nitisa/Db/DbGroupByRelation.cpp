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
	String ToString(const DbGroupByRelation value)
	{
		switch (value)
		{
		case DbGroupByRelation::NotSupported: return L"NotSupported";
		case DbGroupByRelation::Collate: return L"Collate";
		case DbGroupByRelation::EqualsSelect: return L"EqualsSelect";
		case DbGroupByRelation::ContainsSelect: return L"ContainsSelect";
		case DbGroupByRelation::NoRelation: return L"NoRelation";
		default: return L"Unknown";
		}
	}
}