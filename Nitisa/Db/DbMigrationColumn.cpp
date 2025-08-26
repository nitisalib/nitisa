// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CDbMigrationColumn::CDbMigrationColumn(const String& name) :
		CReleasable()
	{
		m_sName = name;
		m_eDataType = DataType::None;
		m_bUnsigned = false;
		m_bNotNull = false;
		m_iWidth = -1;
		m_iDigits = -1;
		m_bAutoIncrement = false;
		m_bUnique = false;
		m_bPrimaryKey = false;
		m_bDefaultBoolSet = false;
		m_bDefaultIntSet = false;
		m_bDefaultUIntSet = false;
		m_bDefaultFloatSet = false;
		m_bDefaultStringSet = false;
	}
#pragma endregion

#pragma region Set column type
	IDbMigrationColumn* CDbMigrationColumn::Boolean()
	{
		m_eDataType = DataType::Bool;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Integer(const int& width)
	{
		m_eDataType = DataType::Int;
		m_iWidth = width;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::TinyInt(const int& width)
	{
		m_eDataType = DataType::TinyInt;
		m_iWidth = width;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::SmallInt(const int& width)
	{
		m_eDataType = DataType::SmallInt;
		m_iWidth = width;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::MediumInt(const int& width)
	{
		m_eDataType = DataType::MediumInt;
		m_iWidth = width;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::BigInt(const int& width)
	{
		m_eDataType = DataType::BigInt;
		m_iWidth = width;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Decimal(const int& width, const int& digits)
	{
		m_eDataType = DataType::Decimal;
		m_iWidth = width;
		m_iDigits = digits;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Numeric(const int& width, const int& digits)
	{
		m_eDataType = DataType::Numeric;
		m_iWidth = width;
		m_iDigits = digits;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Float(const int& width, const int& digits)
	{
		m_eDataType = DataType::Float;
		m_iWidth = width;
		m_iDigits = digits;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Double(const int& width, const int& digits)
	{
		m_eDataType = DataType::Double;
		m_iWidth = width;
		m_iDigits = digits;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Date()
	{
		m_eDataType = DataType::Date;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Time(const int& fsp)
	{
		m_eDataType = DataType::Time;
		m_iWidth = fsp;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::DateTime(const int& fsp)
	{
		m_eDataType = DataType::DateTime;
		m_iWidth = fsp;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::TimeStamp(const int& fsp)
	{
		m_eDataType = DataType::TimeStamp;
		m_iWidth = fsp;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Char(const int& width)
	{
		m_eDataType = DataType::Char;
		m_iWidth = width;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::VarChar(const int& width)
	{
		m_eDataType = DataType::VarChar;
		m_iWidth = width;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Text(const int& width)
	{
		m_eDataType = DataType::Text;
		m_iWidth = width;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::TinyText()
	{
		m_eDataType = DataType::TinyText;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::MediumText()
	{
		m_eDataType = DataType::MediumText;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::LongText()
	{
		m_eDataType = DataType::LongText;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Enum(const StringArray& options)
	{
		m_eDataType = DataType::Enum;
		m_aOptions = options;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Set(const StringArray& options)
	{
		m_eDataType = DataType::Set;
		m_aOptions = options;
		return this;
	}

	IDbMigrationColumn *CDbMigrationColumn::Json()
	{
		m_eDataType = DataType::Json;
		return this;
	}
#pragma endregion

#pragma region Set modifiers
	IDbMigrationColumn* CDbMigrationColumn::Unsigned(const bool value)
	{
		m_bUnsigned = value;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::NotNull(const bool value)
	{
		m_bNotNull = value;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Comment(const String& comment)
	{
		m_sComment = comment;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Charset(const String& charset)
	{
		m_sCharset = charset;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Collation(const String& collation)
	{
		m_sCollation = collation;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::AutoIncrement(const bool value)
	{
		m_bAutoIncrement = value;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Unique(const bool value)
	{
		m_bUnique = value;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::PrimaryKey(const bool value)
	{
		m_bPrimaryKey = value;
		return this;
	}
#pragma endregion

#pragma region Set default value
	IDbMigrationColumn* CDbMigrationColumn::Default(const bool& value)
	{
		m_bDefaultBoolSet = true;
		m_bDefaultBoolValue = value;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Default(const int64& value)
	{
		m_bDefaultIntSet = true;
		m_iDefaultIntValue = value;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Default(const uint64& value)
	{
		m_bDefaultUIntSet = true;
		m_iDefaultUIntValue = value;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Default(const double& value)
	{
		m_bDefaultFloatSet = true;
		m_fDefaultFloatValue = value;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Default(const String& value)
	{
		m_bDefaultStringSet = true;
		m_sDefaultStringValue = value;
		return this;
	}

	IDbMigrationColumn* CDbMigrationColumn::Default(const wchar_t *value)
	{
		m_bDefaultStringSet = true;
		m_sDefaultStringValue = value;
		return this;
	}

	IDbMigrationColumn *CDbMigrationColumn::ClearDefault()
	{
		m_bDefaultBoolSet = false;
		m_bDefaultIntSet = false;
		m_bDefaultUIntSet = false;
		m_bDefaultFloatSet = false;
		m_bDefaultStringSet = false;
		return this;
	}
#pragma endregion
}