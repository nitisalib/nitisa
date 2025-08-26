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
	String ToString(const DbConcatenateNullBehaviour value)
	{
		switch (value)
		{
		case DbConcatenateNullBehaviour::Null: return L"Null";
		case DbConcatenateNullBehaviour::NotNull: return L"NotNull";
		default: return L"Unknown";
		}
	}
}