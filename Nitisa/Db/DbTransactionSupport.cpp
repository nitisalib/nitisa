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
	String ToString(const DbTransactionSupport value)
	{
		switch (value)
		{
		case DbTransactionSupport::None: return L"None";
		case DbTransactionSupport::DataManipulation: return L"DataManipulation";
		case DbTransactionSupport::DataDefinitionCommit: return L"DataDefinitionCommit";
		case DbTransactionSupport::DataDefinitionIgnore: return L"DataDefinitionIgnore";
		case DbTransactionSupport::All: return L"All";
		default: return L"Unknown";
		}
	}
}