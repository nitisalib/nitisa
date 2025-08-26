// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "DbDate.h"
#include "DbDateTime.h"
#include "DbTime.h"
#include "DbValueType.h"
#include "../Core/Aliases.h"
#include "../Core/ByteArray.h"
#include "../Core/Strings.h"

namespace nitisa
{
	class DbValue
	{
	private:
		union
		{
			bool m_bBool;
			char m_iChar;
			byte m_iByte;
			short m_iShort;
			unsigned short m_iUShort;
			int m_iInt;
			uint m_iUInt;
			int64 m_iInt64;
			uint64 m_iUInt64;
			float m_fFloat;
			double m_fDouble;
			DbDate m_sDate;
			DbTime m_sTime;
			DbDateTime m_sDateTime;
		};
		String m_sString;
		AnsiString m_sAnsiString;
		ByteArray m_aBuffer;
	protected:
		DbValueType m_eType;
	public:
		DbValueType const &Type{ m_eType };

		// Constructors
		DbValue();
		DbValue(const bool value);
		DbValue(const char value);
		DbValue(const byte value);
		DbValue(const short value);
		DbValue(const unsigned short value);
		DbValue(const int value);
		DbValue(const uint value);
		DbValue(const int64 value);
		DbValue(const uint64 value);
		DbValue(const float value);
		DbValue(const double value);
		DbValue(const String &value);
		DbValue(const wchar_t *value);
		DbValue(const AnsiString &value);
		DbValue(const char *value);
		DbValue(const ByteArray &value);
		DbValue(const DbDate &value);
		DbValue(const DbTime &value);
		DbValue(const DbDateTime &value);
		DbValue(const DbValue &other);
		DbValue(DbValue &&other);
		template<class Type> DbValue(Type) = delete;

		// Assignment operators
		DbValue &operator=(void *value); // Sets type to Null
		DbValue &operator=(const bool value);
		DbValue &operator=(const char value);
		DbValue &operator=(const byte value);
		DbValue &operator=(const short value);
		DbValue &operator=(const unsigned short value);
		DbValue &operator=(const int value);
		DbValue &operator=(const uint value);
		DbValue &operator=(const int64 value);
		DbValue &operator=(const uint64 value);
		DbValue &operator=(const float value);
		DbValue &operator=(const double value);
		DbValue &operator=(const String &value);
		DbValue &operator=(const wchar_t *value);
		DbValue &operator=(const AnsiString &value);
		DbValue &operator=(const char *value);
		DbValue &operator=(const ByteArray &value);
		DbValue &operator=(const DbDate &value);
		DbValue &operator=(const DbTime &value);
		DbValue &operator=(const DbDateTime &value);
		DbValue &operator=(const DbValue &other);
		DbValue &operator=(DbValue &&other);
		template<class Type> DbValue &operator=(Type) = delete;

		// Converting operators
		explicit operator const Pointer() const; // Return nullptr if type is Null, or pointer to value if type is not null
		explicit operator bool() const;
		explicit operator char() const;
		explicit operator byte() const;
		explicit operator short() const;
		explicit operator unsigned short() const;
		explicit operator int() const;
		explicit operator uint() const;
		explicit operator int64() const;
		explicit operator uint64() const;
		explicit operator float() const;
		explicit operator double() const;
		explicit operator String() const;
		explicit operator AnsiString() const;
		explicit operator ByteArray() const;
		explicit operator DbDate() const;
		explicit operator DbTime() const;
		explicit operator DbDateTime() const;

		// Comparison operators
		bool operator==(const DbValue &other) const;
		bool operator!=(const DbValue &other) const;

		size_t Length() const; // Return length of string/buffer or 0
		DbValue Convert(const DbValueType type) const; // Return value converted to specified type
	};
}