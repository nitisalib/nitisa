// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructors
	DbValue::DbValue() :
		m_eType{ DbValueType::Null }
	{

	}

	DbValue::DbValue(const bool value) :
		m_eType{ DbValueType::Bool }
	{
		m_bBool = value;
	}

	DbValue::DbValue(const char value) :
		m_eType{ DbValueType::Char }
	{
		m_iChar = value;
	}

	DbValue::DbValue(const byte value) :
		m_eType{ DbValueType::Byte }
	{
		m_iByte = value;
	}

	DbValue::DbValue(const short value) :
		m_eType{ DbValueType::Short }
	{
		m_iShort = value;
	}

	DbValue::DbValue(const unsigned short value) :
		m_eType{ DbValueType::UShort }
	{
		m_iUShort = value;
	}

	DbValue::DbValue(const int value) :
		m_eType{ DbValueType::Int }
	{
		m_iInt = value;
	}

	DbValue::DbValue(const uint value) :
		m_eType{ DbValueType::UInt }
	{
		m_iUInt = value;
	}

	DbValue::DbValue(const int64 value) :
		m_eType{ DbValueType::Int64 }
	{
		m_iInt64 = value;
	}

	DbValue::DbValue(const uint64 value) :
		m_eType{ DbValueType::UInt64 }
	{
		m_iUInt64 = value;
	}

	DbValue::DbValue(const float value) :
		m_eType{ DbValueType::Float }
	{
		m_fFloat = value;
	}

	DbValue::DbValue(const double value) :
		m_eType{ DbValueType::Double }
	{
		m_fDouble = value;
	}

	DbValue::DbValue(const String &value) :
		m_eType{ DbValueType::String }
	{
		m_sString = value;
	}

	DbValue::DbValue(const wchar_t *value) :
		m_eType{ DbValueType::String }
	{
		m_sString = value;
	}

	DbValue::DbValue(const AnsiString &value) :
		m_eType{ DbValueType::AnsiString }
	{
		m_sAnsiString = value;
	}

	DbValue::DbValue(const char *value) :
		m_eType{ DbValueType::AnsiString }
	{
		m_sAnsiString = value;
	}

	DbValue::DbValue(const ByteArray &value) :
		m_eType{ DbValueType::Buffer }
	{
		m_aBuffer = value;
	}

	DbValue::DbValue(const DbDate &value) :
		m_eType{ DbValueType::Date }
	{
		m_sDate = value;
	}

	DbValue::DbValue(const DbTime &value) :
		m_eType{ DbValueType::Time }
	{
		m_sTime = value;
	}

	DbValue::DbValue(const DbDateTime &value) :
		m_eType{ DbValueType::DateTime }
	{
		m_sDateTime = value;
	}

	DbValue::DbValue(const DbValue &other) :
		m_eType{ other.m_eType }
	{
		switch (other.m_eType)
		{
		case DbValueType::Bool:
			m_bBool = other.m_bBool;
			break;
		case DbValueType::Char:
			m_iChar = other.m_iChar;
			break;
		case DbValueType::Byte:
			m_iByte = other.m_iByte;
			break;
		case DbValueType::Short:
			m_iShort = other.m_iShort;
			break;
		case DbValueType::UShort:
			m_iUShort = other.m_iUShort;
			break;
		case DbValueType::Int:
			m_iInt = other.m_iInt;
			break;
		case DbValueType::UInt:
			m_iUInt = other.m_iUInt;
			break;
		case DbValueType::Int64:
			m_iInt64 = other.m_iInt64;
			break;
		case DbValueType::UInt64:
			m_iUInt64 = other.m_iUInt64;
			break;
		case DbValueType::Float:
			m_fFloat = other.m_fFloat;
			break;
		case DbValueType::Double:
			m_fDouble = other.m_fDouble;
			break;
		case DbValueType::String:
			m_sString = other.m_sString;
			break;
		case DbValueType::AnsiString:
			m_sAnsiString = other.m_sAnsiString;
			break;
		case DbValueType::Buffer:
			m_aBuffer = other.m_aBuffer;
			break;
		case DbValueType::Date:
			m_sDate = other.m_sDate;
			break;
		case DbValueType::Time:
			m_sTime = other.m_sTime;
			break;
		case DbValueType::DateTime:
			m_sDateTime = other.m_sDateTime;
			break;
		default:
			break;
		}
	}

	DbValue::DbValue(DbValue &&other) :
		m_eType{ other.m_eType }
	{
		switch (other.m_eType)
		{
		case DbValueType::Bool:
			m_bBool = other.m_bBool;
			break;
		case DbValueType::Char:
			m_iChar = other.m_iChar;
			break;
		case DbValueType::Byte:
			m_iByte = other.m_iByte;
			break;
		case DbValueType::Short:
			m_iShort = other.m_iShort;
			break;
		case DbValueType::UShort:
			m_iUShort = other.m_iUShort;
			break;
		case DbValueType::Int:
			m_iInt = other.m_iInt;
			break;
		case DbValueType::UInt:
			m_iUInt = other.m_iUInt;
			break;
		case DbValueType::Int64:
			m_iInt64 = other.m_iInt64;
			break;
		case DbValueType::UInt64:
			m_iUInt64 = other.m_iUInt64;
			break;
		case DbValueType::Float:
			m_fFloat = other.m_fFloat;
			break;
		case DbValueType::Double:
			m_fDouble = other.m_fDouble;
			break;
		case DbValueType::String:
			m_sString = std::move(other.m_sString);
			break;
		case DbValueType::AnsiString:
			m_sAnsiString = std::move(other.m_sAnsiString);
			break;
		case DbValueType::Buffer:
			m_aBuffer = std::move(other.m_aBuffer);
			break;
		case DbValueType::Date:
			m_sDate = other.m_sDate;
			break;
		case DbValueType::Time:
			m_sTime = other.m_sTime;
			break;
		case DbValueType::DateTime:
			m_sDateTime = other.m_sDateTime;
			break;
		default:
			break;
		}
	}
#pragma endregion

#pragma region Assignment operators
	DbValue &DbValue::operator=(void *value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Null;
		return *this;
	}

	DbValue &DbValue::operator=(const bool value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Bool;
		m_bBool = value;
		return *this;
	}

	DbValue &DbValue::operator=(const char value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Char;
		m_iChar = value;
		return *this;
	}

	DbValue &DbValue::operator=(const byte value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Byte;
		m_iByte = value;
		return *this;
	}

	DbValue &DbValue::operator=(const short value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Short;
		m_iShort = value;
		return *this;
	}

	DbValue &DbValue::operator=(const unsigned short value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::UShort;
		m_iUShort = value;
		return *this;
	}

	DbValue &DbValue::operator=(const int value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Int;
		m_iInt = value;
		return *this;
	}

	DbValue &DbValue::operator=(const uint value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::UInt;
		m_iUInt = value;
		return *this;
	}

	DbValue &DbValue::operator=(const int64 value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Int64;
		m_iInt64 = value;
		return *this;
	}

	DbValue &DbValue::operator=(const uint64 value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::UInt64;
		m_iUInt64 = value;
		return *this;
	}

	DbValue &DbValue::operator=(const float value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Float;
		m_fFloat = value;
		return *this;
	}

	DbValue &DbValue::operator=(const double value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Double;
		m_fDouble = value;
		return *this;
	}

	DbValue &DbValue::operator=(const String &value)
	{
		switch (m_eType)
		{
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::String;
		m_sString = value;
		return *this;
	}

	DbValue &DbValue::operator=(const wchar_t *value)
	{
		switch (m_eType)
		{
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::String;
		m_sString = value;
		return *this;
	}

	DbValue &DbValue::operator=(const AnsiString &value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::AnsiString;
		m_sAnsiString = value;
		return *this;
	}

	DbValue &DbValue::operator=(const char *value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::AnsiString;
		m_sAnsiString = value;
		return *this;
	}

	DbValue &DbValue::operator=(const ByteArray &value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Buffer;
		m_aBuffer = value;
		return *this;
	}

	DbValue &DbValue::operator=(const DbDate &value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Date;
		m_sDate = value;
		return *this;
	}

	DbValue &DbValue::operator=(const DbTime &value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::Time;
		m_sTime = value;
		return *this;
	}

	DbValue &DbValue::operator=(const DbDateTime &value)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			m_sString.clear();
			break;
		case DbValueType::AnsiString:
			m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			m_aBuffer.clear();
			break;
		default:
			break;
		}
		m_eType = DbValueType::DateTime;
		m_sDateTime = value;
		return *this;
	}

	DbValue &DbValue::operator=(const DbValue &other)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			if (other.m_eType != DbValueType::String)
				m_sString.clear();
			break;
		case DbValueType::AnsiString:
			if (other.m_eType != DbValueType::AnsiString)
				m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			if (other.m_eType != DbValueType::Buffer)
				m_aBuffer.clear();
			break;
		default:
			break;
		}
		switch (other.m_eType)
		{
		case DbValueType::Bool:
			m_bBool = other.m_bBool;
			break;
		case DbValueType::Char:
			m_iChar = other.m_iChar;
			break;
		case DbValueType::Byte:
			m_iByte = other.m_iByte;
			break;
		case DbValueType::Short:
			m_iShort = other.m_iShort;
			break;
		case DbValueType::UShort:
			m_iUShort = other.m_iUShort;
			break;
		case DbValueType::Int:
			m_iInt = other.m_iInt;
			break;
		case DbValueType::UInt:
			m_iUInt = other.m_iUInt;
			break;
		case DbValueType::Int64:
			m_iInt64 = other.m_iInt64;
			break;
		case DbValueType::UInt64:
			m_iUInt64 = other.m_iUInt64;
			break;
		case DbValueType::Float:
			m_fFloat = other.m_fFloat;
			break;
		case DbValueType::Double:
			m_fDouble = other.m_fDouble;
			break;
		case DbValueType::String:
			m_sString = other.m_sString;
			break;
		case DbValueType::AnsiString:
			m_sAnsiString = other.m_sAnsiString;
			break;
		case DbValueType::Buffer:
			m_aBuffer = other.m_aBuffer;
			break;
		case DbValueType::Date:
			m_sDate = other.m_sDate;
			break;
		case DbValueType::Time:
			m_sTime = other.m_sTime;
			break;
		case DbValueType::DateTime:
			m_sDateTime = other.m_sDateTime;
			break;
		default:
			break;
		}
		m_eType = other.m_eType;
		return *this;
	}

	DbValue &DbValue::operator=(DbValue &&other)
	{
		switch (m_eType)
		{
		case DbValueType::String:
			if (other.m_eType != DbValueType::String)
				m_sString.clear();
			break;
		case DbValueType::AnsiString:
			if (other.m_eType != DbValueType::AnsiString)
				m_sAnsiString.clear();
			break;
		case DbValueType::Buffer:
			if (other.m_eType != DbValueType::Buffer)
				m_aBuffer.clear();
			break;
		default:
			break;
		}
		switch (other.m_eType)
		{
		case DbValueType::Bool:
			m_bBool = other.m_bBool;
			break;
		case DbValueType::Char:
			m_iChar = other.m_iChar;
			break;
		case DbValueType::Byte:
			m_iByte = other.m_iByte;
			break;
		case DbValueType::Short:
			m_iShort = other.m_iShort;
			break;
		case DbValueType::UShort:
			m_iUShort = other.m_iUShort;
			break;
		case DbValueType::Int:
			m_iInt = other.m_iInt;
			break;
		case DbValueType::UInt:
			m_iUInt = other.m_iUInt;
			break;
		case DbValueType::Int64:
			m_iInt64 = other.m_iInt64;
			break;
		case DbValueType::UInt64:
			m_iUInt64 = other.m_iUInt64;
			break;
		case DbValueType::Float:
			m_fFloat = other.m_fFloat;
			break;
		case DbValueType::Double:
			m_fDouble = other.m_fDouble;
			break;
		case DbValueType::String:
			m_sString = std::move(other.m_sString);
			break;
		case DbValueType::AnsiString:
			m_sAnsiString = std::move(other.m_sAnsiString);
			break;
		case DbValueType::Buffer:
			m_aBuffer = std::move(other.m_aBuffer);
			break;
		case DbValueType::Date:
			m_sDate = other.m_sDate;
			break;
		case DbValueType::Time:
			m_sTime = other.m_sTime;
			break;
		case DbValueType::DateTime:
			m_sDateTime = other.m_sDateTime;
			break;
		default:
			break;
		}
		m_eType = other.m_eType;
		return *this;
	}
#pragma endregion

#pragma region Converting operators
	DbValue::operator const Pointer() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (Pointer)&m_bBool;
		case DbValueType::Char:
			return (Pointer)&m_iChar;
		case DbValueType::Byte:
			return (Pointer)&m_iByte;
		case DbValueType::Short:
			return (Pointer)&m_iShort;
		case DbValueType::UShort:
			return (Pointer)&m_iUShort;
		case DbValueType::Int:
			return (Pointer)&m_iInt;
		case DbValueType::UInt:
			return (Pointer)&m_iUInt;
		case DbValueType::Int64:
			return (Pointer)&m_iInt64;
		case DbValueType::UInt64:
			return (Pointer)&m_iUInt64;
		case DbValueType::Float:
			return (Pointer)&m_fFloat;
		case DbValueType::Double:
			return (Pointer)&m_fDouble;
		case DbValueType::String:
			return (Pointer)m_sString.c_str();
		case DbValueType::AnsiString:
			return (Pointer)m_sAnsiString.c_str();
		case DbValueType::Buffer:
			return (Pointer)m_aBuffer.data();
		case DbValueType::Date:
			return (Pointer)&m_sDate;
		case DbValueType::Time:
			return (Pointer)&m_sTime;
		case DbValueType::DateTime:
			return (Pointer)&m_sDateTime;
		default:
			return nullptr;
		}
	}

	DbValue::operator bool() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return m_bBool;
		case DbValueType::Char:
			return m_iChar ? true : false;
		case DbValueType::Byte:
			return m_iByte ? true : false;
		case DbValueType::Short:
			return m_iShort ? true : false;
		case DbValueType::UShort:
			return m_iUShort ? true : false;
		case DbValueType::Int:
			return m_iInt ? true : false;
		case DbValueType::UInt:
			return m_iUInt ? true : false;
		case DbValueType::Int64:
			return m_iInt64 ? true : false;
		case DbValueType::UInt64:
			return m_iUInt64 ? true : false;
		case DbValueType::Float:
			return ntl::IsZero<float>(m_fFloat);
		case DbValueType::Double:
			return ntl::IsZero<double>(m_fDouble);
		case DbValueType::String:
			return m_sString.length() > 0;
		case DbValueType::AnsiString:
			return m_sAnsiString.length() > 0;
		case DbValueType::Buffer:
			return m_aBuffer.size() > 0;
		case DbValueType::Date:
			return m_sDate.Year || m_sDate.Month || m_sDate.Day;
		case DbValueType::Time:
			return m_sTime.Hour || m_sTime.Minute || m_sTime.Second;
		case DbValueType::DateTime:
			return m_sDateTime.Date.Year || m_sDateTime.Date.Month || m_sDateTime.Date.Day || m_sDateTime.Time.Hour || m_sDateTime.Time.Minute || m_sDateTime.Time.Second || m_sDateTime.NanoSecond;
		default:
			return false;
		}
	}

	DbValue::operator char() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (char)m_bBool;
		case DbValueType::Char:
			return m_iChar;
		case DbValueType::Byte:
			return (char)m_iByte;
		case DbValueType::Short:
			return (char)m_iShort;
		case DbValueType::UShort:
			return (char)m_iUShort;
		case DbValueType::Int:
			return (char)m_iInt;
		case DbValueType::UInt:
			return (char)m_iUInt;
		case DbValueType::Int64:
			return (char)m_iInt64;
		case DbValueType::UInt64:
			return (char)m_iUInt64;
		case DbValueType::Float:
			return (char)m_fFloat;
		case DbValueType::Double:
			return (char)m_fDouble;
		default:
			return 0;
		}
	}

	DbValue::operator byte() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (byte)m_bBool;
		case DbValueType::Char:
			return (byte)m_iChar;
		case DbValueType::Byte:
			return m_iByte;
		case DbValueType::Short:
			return (byte)m_iShort;
		case DbValueType::UShort:
			return (byte)m_iUShort;
		case DbValueType::Int:
			return (byte)m_iInt;
		case DbValueType::UInt:
			return (byte)m_iUInt;
		case DbValueType::Int64:
			return (byte)m_iInt64;
		case DbValueType::UInt64:
			return (byte)m_iUInt64;
		case DbValueType::Float:
			return (byte)m_fFloat;
		case DbValueType::Double:
			return (byte)m_fDouble;
		default:
			return 0;
		}
	}

	DbValue::operator short() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (short)m_bBool;
		case DbValueType::Char:
			return (short)m_iChar;
		case DbValueType::Byte:
			return (short)m_iByte;
		case DbValueType::Short:
			return m_iShort;
		case DbValueType::UShort:
			return (short)m_iUShort;
		case DbValueType::Int:
			return (short)m_iInt;
		case DbValueType::UInt:
			return (short)m_iUInt;
		case DbValueType::Int64:
			return (short)m_iInt64;
		case DbValueType::UInt64:
			return (short)m_iUInt64;
		case DbValueType::Float:
			return (short)m_fFloat;
		case DbValueType::Double:
			return (short)m_fDouble;
		default:
			return 0;
		}
	}

	DbValue::operator unsigned short() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (unsigned short)m_bBool;
		case DbValueType::Char:
			return (unsigned short)m_iChar;
		case DbValueType::Byte:
			return (unsigned short)m_iByte;
		case DbValueType::Short:
			return (unsigned short)m_iShort;
		case DbValueType::UShort:
			return m_iUShort;
		case DbValueType::Int:
			return (unsigned short)m_iInt;
		case DbValueType::UInt:
			return (unsigned short)m_iUInt;
		case DbValueType::Int64:
			return (unsigned short)m_iInt64;
		case DbValueType::UInt64:
			return (unsigned short)m_iUInt64;
		case DbValueType::Float:
			return (unsigned short)m_fFloat;
		case DbValueType::Double:
			return (unsigned short)m_fDouble;
		default:
			return 0;
		}
	}

	DbValue::operator int() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (int)m_bBool;
		case DbValueType::Char:
			return (int)m_iChar;
		case DbValueType::Byte:
			return (int)m_iByte;
		case DbValueType::Short:
			return (int)m_iShort;
		case DbValueType::UShort:
			return (int)m_iUShort;
		case DbValueType::Int:
			return m_iInt;
		case DbValueType::UInt:
			return (int)m_iUInt;
		case DbValueType::Int64:
			return (int)m_iInt64;
		case DbValueType::UInt64:
			return (int)m_iUInt64;
		case DbValueType::Float:
			return (int)m_fFloat;
		case DbValueType::Double:
			return (int)m_fDouble;
		case DbValueType::String:
		{
			int v;
			if (TryStringToInt(m_sString, v))
				return v;
		}
		case DbValueType::AnsiString:
		{
			int v;
			if (TryStringToInt(m_sAnsiString, v))
				return v;
		}
		default:
			return 0;
		}
	}

	DbValue::operator uint() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (uint)m_bBool;
		case DbValueType::Char:
			return (uint)m_iChar;
		case DbValueType::Byte:
			return (uint)m_iByte;
		case DbValueType::Short:
			return (uint)m_iShort;
		case DbValueType::UShort:
			return (uint)m_iUShort;
		case DbValueType::Int:
			return (uint)m_iInt;
		case DbValueType::UInt:
			return m_iUInt;
		case DbValueType::Int64:
			return (uint)m_iInt64;
		case DbValueType::UInt64:
			return (uint)m_iUInt64;
		case DbValueType::Float:
			return (uint)m_fFloat;
		case DbValueType::Double:
			return (uint)m_fDouble;
		case DbValueType::String:
		{
			unsigned int v;
			if (TryStringToUInt(m_sString, v))
				return v;
		}
		case DbValueType::AnsiString:
		{
			unsigned int v;
			if (TryStringToUInt(m_sAnsiString, v))
				return v;
		}
		default:
			return 0;
		}
	}

	DbValue::operator int64() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (int64)m_bBool;
		case DbValueType::Char:
			return (int64)m_iChar;
		case DbValueType::Byte:
			return (int64)m_iByte;
		case DbValueType::Short:
			return (int64)m_iShort;
		case DbValueType::UShort:
			return (int64)m_iUShort;
		case DbValueType::Int:
			return (int64)m_iInt;
		case DbValueType::UInt:
			return (int64)m_iUInt;
		case DbValueType::Int64:
			return m_iInt64;
		case DbValueType::UInt64:
			return (int64)m_iUInt64;
		case DbValueType::Float:
			return (int64)m_fFloat;
		case DbValueType::Double:
			return (int64)m_fDouble;
		case DbValueType::String:
		{
			long long v;
			if (TryStringToInt64(m_sString, v))
				return v;
		}
		case DbValueType::AnsiString:
		{
			long long v;
			if (TryStringToInt64(m_sAnsiString, v))
				return v;
		}
		default:
			return 0;
		}
	}

	DbValue::operator uint64() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (uint64)m_bBool;
		case DbValueType::Char:
			return (uint64)m_iChar;
		case DbValueType::Byte:
			return (uint64)m_iByte;
		case DbValueType::Short:
			return (uint64)m_iShort;
		case DbValueType::UShort:
			return (uint64)m_iUShort;
		case DbValueType::Int:
			return (uint64)m_iInt;
		case DbValueType::UInt:
			return (uint64)m_iUInt;
		case DbValueType::Int64:
			return (uint64)m_iInt64;
		case DbValueType::UInt64:
			return m_iUInt64;
		case DbValueType::Float:
			return (uint64)m_fFloat;
		case DbValueType::Double:
			return (uint64)m_fDouble;
		case DbValueType::String:
		{
			unsigned long long v;
			if (TryStringToUInt64(m_sString, v))
				return v;
		}
		case DbValueType::AnsiString:
		{
			unsigned long long v;
			if (TryStringToUInt64(m_sAnsiString, v))
				return v;
		}
		default:
			return 0;
		}
	}

	DbValue::operator float() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (float)m_bBool;
		case DbValueType::Char:
			return (float)m_iChar;
		case DbValueType::Byte:
			return (float)m_iByte;
		case DbValueType::Short:
			return (float)m_iShort;
		case DbValueType::UShort:
			return (float)m_iUShort;
		case DbValueType::Int:
			return (float)m_iInt;
		case DbValueType::UInt:
			return (float)m_iUInt;
		case DbValueType::Int64:
			return (float)m_iInt64;
		case DbValueType::UInt64:
			return (float)m_iUInt64;
		case DbValueType::Float:
			return m_fFloat;
		case DbValueType::Double:
			return (float)m_fDouble;
		case DbValueType::String:
		{
			float v;
			if (TryStringToFloat(m_sString, v))
				return v;
		}
		case DbValueType::AnsiString:
		{
			float v;
			if (TryStringToFloat(m_sAnsiString, v))
				return v;
		}
		default:
			return 0;
		}
	}

	DbValue::operator double() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return (double)m_bBool;
		case DbValueType::Char:
			return (double)m_iChar;
		case DbValueType::Byte:
			return (double)m_iByte;
		case DbValueType::Short:
			return (double)m_iShort;
		case DbValueType::UShort:
			return (double)m_iUShort;
		case DbValueType::Int:
			return (double)m_iInt;
		case DbValueType::UInt:
			return (double)m_iUInt;
		case DbValueType::Int64:
			return (double)m_iInt64;
		case DbValueType::UInt64:
			return (double)m_iUInt64;
		case DbValueType::Float:
			return (double)m_fFloat;
		case DbValueType::Double:
			return m_fDouble;
		case DbValueType::String:
		{
			double v;
			if (TryStringToDouble(m_sString, v))
				return v;
		}
		case DbValueType::AnsiString:
		{
			double v;
			if (TryStringToDouble(m_sAnsiString, v))
				return v;
		}
		default:
			return 0;
		}
	}

	DbValue::operator String() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return m_bBool ? L"true" : L"false";
		case DbValueType::Char:
		{
			AnsiString v{ m_iChar };
			return AnsiToString(v);
		}
		case DbValueType::Byte:
			return ToString(m_iByte);
		case DbValueType::Short:
			return ToString(m_iShort);
		case DbValueType::UShort:
			return ToString(m_iUShort);
		case DbValueType::Int:
			return ToString(m_iInt);
		case DbValueType::UInt:
			return ToString(m_iUInt);
		case DbValueType::Int64:
			return ToString(m_iInt64);
		case DbValueType::UInt64:
			return ToString(m_iUInt64);
		case DbValueType::Float:
			return ToString(m_fFloat);
		case DbValueType::Double:
			return ToString(m_fDouble);
		case DbValueType::String:
			return m_sString;
		case DbValueType::AnsiString:
			return AnsiToString(m_sAnsiString);
		case DbValueType::Date:
			return (String)m_sDate;
		case DbValueType::Time:
			return (String)m_sTime;
		case DbValueType::DateTime:
			return (String)m_sDateTime;
		default:
			return L"";
		}
	}

	DbValue::operator AnsiString() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return m_bBool ? "true" : "false";
		case DbValueType::Char:
		{
			AnsiString v{ m_iChar };
			return v;
		}
		case DbValueType::Byte:
			return ToAnsi(m_iByte);
		case DbValueType::Short:
			return ToAnsi(m_iShort);
		case DbValueType::UShort:
			return ToAnsi(m_iUShort);
		case DbValueType::Int:
			return ToAnsi(m_iInt);
		case DbValueType::UInt:
			return ToAnsi(m_iUInt);
		case DbValueType::Int64:
			return ToAnsi(m_iInt64);
		case DbValueType::UInt64:
			return ToAnsi(m_iUInt64);
		case DbValueType::Float:
			return ToAnsi(m_fFloat);
		case DbValueType::Double:
			return ToAnsi(m_fDouble);
		case DbValueType::String:
			return StringToAnsi(m_sString);
		case DbValueType::AnsiString:
			return m_sAnsiString;
		case DbValueType::Date:
			return (AnsiString)m_sDate;
		case DbValueType::Time:
			return (AnsiString)m_sTime;
		case DbValueType::DateTime:
			return (AnsiString)m_sDateTime;
		default:
			return "";
		}
	}

	DbValue::operator ByteArray() const
	{
		switch (m_eType)
		{
		case DbValueType::Bool:
			return ByteArray{ (byte)m_bBool };
		case DbValueType::Char:
			return ByteArray{ (byte)m_iChar };
		case DbValueType::Byte:
			return ByteArray{ m_iByte };
		case DbValueType::AnsiString:
			if (m_sAnsiString.length() > 0)
			{
				ByteArray v;
				v.resize(m_sAnsiString.length());
				for (size_t i = 0; i < m_sAnsiString.length(); i++)
					v[i] = (byte)m_sAnsiString[0];
				return v;
			}
			return ByteArray{};
		case DbValueType::Buffer:
			return m_aBuffer;
		default:
			return ByteArray{};
		}
	}

	DbValue::operator DbDate() const
	{
		switch (m_eType)
		{
		case DbValueType::Date:
			return m_sDate;
		case DbValueType::DateTime:
			return m_sDateTime.Date;
		default:
			return DbDate{ 0, 0, 0 };
		}
	}

	DbValue::operator DbTime() const
	{
		switch (m_eType)
		{
		case DbValueType::Time:
			return m_sTime;
		case DbValueType::DateTime:
			return m_sDateTime.Time;
		default:
			return DbTime{ 0, 0, 0 };
		}
	}

	DbValue::operator DbDateTime() const
	{
		switch (m_eType)
		{
		case DbValueType::Date:
			return DbDateTime{ DbDate{ m_sDate.Year, m_sDate.Month, m_sDate.Day }, DbTime{ 0, 0, 0 }, 0 };
		case DbValueType::Time:
			return DbDateTime{ DbDate{ 0, 0, 0 }, DbTime{ m_sTime.Hour, m_sTime.Minute, m_sTime.Second }, 0 };
		case DbValueType::DateTime:
			return m_sDateTime;
		default:
			return DbDateTime{ DbDate{ 0, 0, 0 }, DbTime{ 0, 0, 0 }, 0 };
		}
	}
#pragma endregion

#pragma region Comparison operators
	bool DbValue::operator==(const DbValue &other) const
	{
		if (m_eType == other.m_eType)
		{
			switch (m_eType)
			{
			case DbValueType::Null:
				return true;
			case DbValueType::Bool:
				return m_bBool == other.m_bBool;
			case DbValueType::Char:
				return m_iChar == other.m_iChar;
			case DbValueType::Byte:
				return m_iByte == other.m_iByte;
			case DbValueType::Short:
				return m_iShort == other.m_iShort;
			case DbValueType::UShort:
				return m_iUShort == other.m_iUShort;
			case DbValueType::Int:
				return m_iInt == other.m_iInt;
			case DbValueType::UInt:
				return m_iUInt == other.m_iUInt;
			case DbValueType::Int64:
				return m_iInt64 == other.m_iInt64;
			case DbValueType::UInt64:
				return m_iUInt64 == other.m_iUInt64;
			case DbValueType::Float:
				return ntl::IsEqual<float>(m_fFloat, other.m_fFloat);
			case DbValueType::Double:
				return ntl::IsEqual<double>(m_fDouble, other.m_fDouble);
			case DbValueType::String:
				return m_sString == other.m_sString;
			case DbValueType::AnsiString:
				return m_sAnsiString == other.m_sAnsiString;
			case DbValueType::Buffer:
				return m_aBuffer == other.m_aBuffer;
			case DbValueType::Date:
				return m_sDate == other.m_sDate;
			case DbValueType::Time:
				return m_sTime == other.m_sTime;
			case DbValueType::DateTime:
				return m_sDateTime == other.m_sDateTime;
			}
		}
		return false;
	}

	bool DbValue::operator!=(const DbValue &other) const
	{
		if (m_eType == other.m_eType)
		{
			switch (m_eType)
			{
			case DbValueType::Null:
				return false;
			case DbValueType::Bool:
				return m_bBool != other.m_bBool;
			case DbValueType::Char:
				return m_iChar != other.m_iChar;
			case DbValueType::Byte:
				return m_iByte != other.m_iByte;
			case DbValueType::Short:
				return m_iShort != other.m_iShort;
			case DbValueType::UShort:
				return m_iUShort != other.m_iUShort;
			case DbValueType::Int:
				return m_iInt != other.m_iInt;
			case DbValueType::UInt:
				return m_iUInt != other.m_iUInt;
			case DbValueType::Int64:
				return m_iInt64 != other.m_iInt64;
			case DbValueType::UInt64:
				return m_iUInt64 != other.m_iUInt64;
			case DbValueType::Float:
				return ntl::IsNotEqual<float>(m_fFloat, other.m_fFloat);
			case DbValueType::Double:
				return ntl::IsNotEqual<double>(m_fDouble, other.m_fDouble);
			case DbValueType::String:
				return m_sString != other.m_sString;
			case DbValueType::AnsiString:
				return m_sAnsiString != other.m_sAnsiString;
			case DbValueType::Buffer:
				return m_aBuffer != other.m_aBuffer;
			case DbValueType::Date:
				return m_sDate != other.m_sDate;
			case DbValueType::Time:
				return m_sTime != other.m_sTime;
			case DbValueType::DateTime:
				return m_sDateTime != other.m_sDateTime;
			}
		}
		return true;
	}
#pragma endregion

#pragma region Methods
	size_t DbValue::Length() const
	{
		switch (m_eType)
		{
		case DbValueType::String:
			return m_sString.length();
		case DbValueType::AnsiString:
			return m_sAnsiString.length();
		case DbValueType::Buffer:
			return m_aBuffer.size();
		default:
			return 0;
		}
	}

	DbValue DbValue::Convert(const DbValueType type) const
	{
		switch (type)
		{
		case DbValueType::Bool: return DbValue{ this->operator bool() };
		case DbValueType::Char: return DbValue{ this->operator char() };
		case DbValueType::Byte: return DbValue{ this->operator byte() };
		case DbValueType::Short: return DbValue{ this->operator short() };
		case DbValueType::UShort: return DbValue{ this->operator unsigned short() };
		case DbValueType::Int: return DbValue{ this->operator int() };
		case DbValueType::UInt: return DbValue{ this->operator uint() };
		case DbValueType::Int64: return DbValue{ this->operator int64() };
		case DbValueType::UInt64: return DbValue{ this->operator uint64() };
		case DbValueType::Float: return DbValue{ this->operator float() };
		case DbValueType::Double: return DbValue{ this->operator double() };
		case DbValueType::String: return DbValue{ this->operator String() };
		case DbValueType::AnsiString: return DbValue{ this->operator AnsiString() };
		case DbValueType::Buffer: return DbValue{ this->operator ByteArray() };
		case DbValueType::Date: return DbValue{ this->operator DbDate() };
		case DbValueType::Time: return DbValue{ this->operator DbTime() };
		case DbValueType::DateTime: return DbValue{ this->operator DbDateTime() };
		default: return DbValue{ };
		}
	}
#pragma endregion
}