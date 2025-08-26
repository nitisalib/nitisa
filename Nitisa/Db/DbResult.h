// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "DbColumns.h"
#include "DbRows.h"

namespace nitisa
{
	struct DbResult
	{
		bool Successful; // Indicates whether query was executed successfully or not
		int64 AffectedRowCount; // Row count affected by the query (for UPDATE and DELETE-like queries)
		DbColumns Columns; // Column descriptions
		DbRows Rows; // Result rows

		DbResult();
		DbResult(const DbResult &other) = default;
		DbResult(DbResult &&other) = default;

		DbResult &operator=(const DbResult &other) = default;
		DbResult &operator=(DbResult &&other) = default;
	};
}