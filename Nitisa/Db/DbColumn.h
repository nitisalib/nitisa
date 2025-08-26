// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/Strings.h"
#include "DbDataType.h"
#include "DbNullabilityType.h"
#include "DbSearchableType.h"
#include "DbUpdatableType.h"

namespace nitisa
{
	struct DbColumn
	{
		bool AutoIncrementing;
		String Name;
		String BaseTableName;
		bool CaseSensitive;
		String CatalogName;
		DbDataType ConciseType;
		int64 MaximumDisplayLength;
		bool FixedPrecisionScale;
		String Label;
		int64 MaximumLength;
		String LiteralPrefix;
		String LiteralSuffix;
		String LocalTypeName;
		String Alias;
		DbNullabilityType Nullability;
		int PrecisionRadix;
		int64 OctetLength;
		int Precision;
		int Scale;
		String SchemaName;
		DbSearchableType Searchable;
		String TableName;
		DbDataType DataType;
		String DataTypeName;
		bool Unnamed;
		bool Unsigned;
		DbUpdatableType Updatable;

		DbColumn();
		DbColumn(const DbColumn &other) = default;
		DbColumn(DbColumn &&other) = default;

		explicit operator String() const;
		DbColumn &operator=(const DbColumn &other) = default;
		DbColumn &operator=(DbColumn &&other) = default;
	};
}