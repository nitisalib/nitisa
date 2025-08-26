// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/Strings.h"
#include "IReleasable.h"

namespace nitisa
{
	class IDbMigrationColumn :public virtual IReleasable
	{
	public:
		enum class DataType // Column data type
		{
			None,
			Bool,
			Int,
			TinyInt,
			SmallInt,
			MediumInt,
			BigInt,
			Decimal,
			Numeric,
			Float,
			Double,
			Date,
			Time,
			DateTime,
			TimeStamp,
			Char,
			VarChar,
			Text,
			TinyText,
			MediumText,
			LongText,
			Enum,
			Set,
			Json
		};
	protected:
		IDbMigrationColumn() = default;
		~IDbMigrationColumn() = default;
		IDbMigrationColumn(const IDbMigrationColumn &other) = delete;
		IDbMigrationColumn(IDbMigrationColumn &&other) = delete;
		IDbMigrationColumn &operator=(const IDbMigrationColumn &other) = delete;
		IDbMigrationColumn &operator=(IDbMigrationColumn &&other) = delete;
	protected:
		String m_sName;
		DataType m_eDataType;
		bool m_bUnsigned;
		bool m_bNotNull;
		int m_iWidth;
		int m_iDigits;
		String m_sComment;
		String m_sCharset;
		String m_sCollation;
		StringArray m_aOptions;
		bool m_bAutoIncrement;
		bool m_bUnique;
		bool m_bPrimaryKey;
		bool m_bDefaultBoolSet;
		bool m_bDefaultIntSet;
		bool m_bDefaultUIntSet;
		bool m_bDefaultFloatSet;
		bool m_bDefaultStringSet;
		bool m_bDefaultBoolValue;
		int64 m_iDefaultIntValue;
		uint64 m_iDefaultUIntValue;
		double m_fDefaultFloatValue;
		String m_sDefaultStringValue;
	public:
		// Read-only references to the protected members
		String const &sName{ m_sName };
		DataType const &eDataType{ m_eDataType };
		bool const &bUnsigned{ m_bUnsigned };
		bool const &bNotNull{ m_bNotNull };
		int const &iWidth{ m_iWidth };
		int const &iDigits{ m_iDigits };
		String const &sComment{ m_sComment };
		String const &sCharset{ m_sCharset };
		String const &sCollation{ m_sCollation };
		StringArray const &aOptions{ m_aOptions };
		bool const &bAutoIncrement{ m_bAutoIncrement };
		bool const &bUnique{ m_bUnique };
		bool const &bPrimaryKey{ m_bPrimaryKey };
		bool const &bDefaultBoolSet{ m_bDefaultBoolSet };
		bool const &bDefaultIntSet{ m_bDefaultIntSet };
		bool const &bDefaultUIntSet{ m_bDefaultUIntSet };
		bool const &bDefaultFloatSet{ m_bDefaultFloatSet };
		bool const &bDefaultStringSet{ m_bDefaultStringSet };
		bool const &bDefaultBoolValue{ m_bDefaultBoolValue };
		int64 const &iDefaultIntValue{ m_iDefaultIntValue };
		uint64 const &iDefaultUIntValue{ m_iDefaultUIntValue };
		double const &fDefaultFloatValue{ m_fDefaultFloatValue };
		String const &sDefaultStringValue{ m_sDefaultStringValue };

		// Set column type
		virtual IDbMigrationColumn *Boolean() = 0;
		virtual IDbMigrationColumn *Integer(const int &width = -1) = 0;
		virtual IDbMigrationColumn *TinyInt(const int &width = -1) = 0;
		virtual IDbMigrationColumn *SmallInt(const int &width = -1) = 0;
		virtual IDbMigrationColumn *MediumInt(const int &width = -1) = 0;
		virtual IDbMigrationColumn *BigInt(const int &width = -1) = 0;
		virtual IDbMigrationColumn *Decimal(const int &width = -1, const int &digits = -1) = 0;
		virtual IDbMigrationColumn *Numeric(const int &width = -1, const int &digits = -1) = 0;
		virtual IDbMigrationColumn *Float(const int &width = -1, const int &digits = -1) = 0;
		virtual IDbMigrationColumn *Double(const int &width = -1, const int &digits = -1) = 0;
		virtual IDbMigrationColumn *Date() = 0;
		virtual IDbMigrationColumn *Time(const int &fsp = -1) = 0;
		virtual IDbMigrationColumn *DateTime(const int &fsp = -1) = 0;
		virtual IDbMigrationColumn *TimeStamp(const int &fsp = -1) = 0;
		virtual IDbMigrationColumn *Char(const int &width) = 0;
		virtual IDbMigrationColumn *VarChar(const int &width) = 0;
		virtual IDbMigrationColumn *Text(const int &width = -1) = 0;
		virtual IDbMigrationColumn *TinyText() = 0;
		virtual IDbMigrationColumn *MediumText() = 0;
		virtual IDbMigrationColumn *LongText() = 0;
		virtual IDbMigrationColumn *Enum(const StringArray &options) = 0;
		virtual IDbMigrationColumn *Set(const StringArray &options) = 0;
		virtual IDbMigrationColumn *Json() = 0;

		// Set modifiers
		virtual IDbMigrationColumn *Unsigned(const bool value = true) = 0;
		virtual IDbMigrationColumn *NotNull(const bool value = true) = 0;
		virtual IDbMigrationColumn *Comment(const String &comment) = 0;
		virtual IDbMigrationColumn *Charset(const String &charset) = 0;
		virtual IDbMigrationColumn *Collation(const String &collation) = 0;
		virtual IDbMigrationColumn *AutoIncrement(const bool value = true) = 0;
		virtual IDbMigrationColumn *Unique(const bool value = true) = 0;
		virtual IDbMigrationColumn *PrimaryKey(const bool value = true) = 0;

		// Set default value
		virtual IDbMigrationColumn *Default(const bool &value) = 0;
		virtual IDbMigrationColumn *Default(const int64 &value) = 0;
		virtual IDbMigrationColumn *Default(const uint64 &value) = 0;
		virtual IDbMigrationColumn *Default(const double &value) = 0;
		virtual IDbMigrationColumn *Default(const String &value) = 0;
		virtual IDbMigrationColumn *Default(const wchar_t *value) = 0;
		virtual IDbMigrationColumn *ClearDefault() = 0;
	};
}