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
	DbColumn::DbColumn() :
		AutoIncrementing{ false },
		CaseSensitive{ false },
		ConciseType{ DbDataType::Unknown },
		MaximumDisplayLength{ 0 },
		FixedPrecisionScale{ false },
		MaximumLength{ 0 },
		Nullability{ DbNullabilityType::Unknown },
		PrecisionRadix{ 0 },
		OctetLength{ 0 },
		Precision{ 0 },
		Scale{ 0 },
		Searchable{ DbSearchableType::Unknown },
		DataType{ DbDataType::Unknown },
		Unnamed{ false },
		Unsigned{ false },
		Updatable{ DbUpdatableType::Unknown }
	{

	}

	DbColumn::operator String() const
	{
		return
			(String)L"\tAutoIncrementing = " + ToString(AutoIncrementing) + L"\n" +
			L"\tName = " + Name + L"\n" +
			L"\tBaseTableName = " + BaseTableName + L"\n" +
			L"\tCaseSensitive = " + ToString(CaseSensitive) + L"\n" +
			L"\tCatalogName = " + CatalogName + L"\n" +
			L"\tConciseType = " + ToString(ConciseType) + L"\n" +
			L"\tMaximumDisplayLength = " + ToString(MaximumDisplayLength) + L"\n" +
			L"\tFixedPrecisionScale = " + ToString(FixedPrecisionScale) + L"\n" +
			L"\tLabel = " + Label + L"\n" +
			L"\tMaximumLength = " + ToString(MaximumLength) + L"\n" +
			L"\tLiteralPrefix = " + LiteralPrefix + L"\n" +
			L"\tLiteralSuffix = " + LiteralSuffix + L"\n" +
			L"\tLocalTypeName = " + LocalTypeName + L"\n" +
			L"\tAlias = " + Alias + L"\n" +
			L"\tNullability = " + ToString(Nullability) + L"\n" +
			L"\tPrecisionRadix = " + ToString(PrecisionRadix) + L"\n" +
			L"\tOctetLength = " + ToString(OctetLength) + L"\n" +
			L"\tPrecision = " + ToString(Precision) + L"\n" +
			L"\tScale = " + ToString(Scale) + L"\n" +
			L"\tSchemaName = " + SchemaName + L"\n" +
			L"\tSearchable = " + ToString(Searchable) + L"\n" +
			L"\tTableName = " + TableName + L"\n" +
			L"\tDataType = " + ToString(DataType) + L"\n" +
			L"\tDataTypeName = " + DataTypeName + L"\n" +
			L"\tUnnamed = " + ToString(Unnamed) + L"\n" +
			L"\tUnsigned = " + ToString(Unsigned) + L"\n" +
			L"\tUpdatable = " + ToString(Updatable);
	}
}