// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Releasable.h"
#include "../Core/Strings.h"
#include "../Interfaces/IDbMigrationColumn.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class CDbMigrationColumn :public virtual IDbMigrationColumn, public CReleasable
	{
	public:
		// Set column type
		IDbMigrationColumn* Boolean() override;
		IDbMigrationColumn* Integer(const int& width = -1) override;
		IDbMigrationColumn* TinyInt(const int& width = -1) override;
		IDbMigrationColumn* SmallInt(const int& width = -1) override;
		IDbMigrationColumn* MediumInt(const int& width = -1) override;
		IDbMigrationColumn* BigInt(const int& width = -1) override;
		IDbMigrationColumn* Decimal(const int& width = -1, const int& digits = -1) override;
		IDbMigrationColumn* Numeric(const int& width = -1, const int& digits = -1) override;
		IDbMigrationColumn* Float(const int& width = -1, const int& digits = -1) override;
		IDbMigrationColumn* Double(const int& width = -1, const int& digits = -1) override;
		IDbMigrationColumn* Date() override;
		IDbMigrationColumn* Time(const int& fsp = -1) override;
		IDbMigrationColumn* DateTime(const int& fsp = -1) override;
		IDbMigrationColumn* TimeStamp(const int& fsp = -1) override;
		IDbMigrationColumn* Char(const int& width) override;
		IDbMigrationColumn* VarChar(const int& width) override;
		IDbMigrationColumn* Text(const int& width = -1) override;
		IDbMigrationColumn* TinyText() override;
		IDbMigrationColumn* MediumText() override;
		IDbMigrationColumn* LongText() override;
		IDbMigrationColumn* Enum(const StringArray& options) override;
		IDbMigrationColumn* Set(const StringArray& options) override;
		IDbMigrationColumn* Json() override;

		// Set modifiers
		IDbMigrationColumn* Unsigned(const bool value = true) override;
		IDbMigrationColumn* NotNull(const bool value = true) override;
		IDbMigrationColumn* Comment(const String& comment) override;
		IDbMigrationColumn* Charset(const String& charset) override;
		IDbMigrationColumn* Collation(const String& collation) override;
		IDbMigrationColumn* AutoIncrement(const bool value = true) override;
		IDbMigrationColumn* Unique(const bool value = true) override;
		IDbMigrationColumn* PrimaryKey(const bool value = true) override;

		// Set default value
		IDbMigrationColumn* Default(const bool& value) override;
		IDbMigrationColumn* Default(const int64& value) override;
		IDbMigrationColumn* Default(const uint64& value) override;
		IDbMigrationColumn* Default(const double& value) override;
		IDbMigrationColumn* Default(const String& value) override;
		IDbMigrationColumn* Default(const wchar_t *value) override;
		IDbMigrationColumn *ClearDefault() override;

		CDbMigrationColumn(const String& name);
	};
}