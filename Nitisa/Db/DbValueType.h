// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	enum class DbValueType
	{
		Null, // NULL value
		Bool, // Boolean value (bool)
		Char, // 1-byte signed integer or character (char)
		Byte, // 1-byte unsigned integer (unsigned char, byte)
		Short, // 2-byte signed integer (short)
		UShort, // 2-byte unsigned integer (unsigned short)
		Int, // 4-byte signed integer (int)
		UInt, // 4-byte unsigned integer (unsigned int, uint)
		Int64, // 8-byte signed integer (long long, int64)
		UInt64, // 8-byte unsigned integer (unsigned long long, uint64)
		Float, // 4-byte float (float)
		Double, // 8-byte float (double)
		String, // Unicode string (String)
		AnsiString, // ANSI string (AnsiString)
		Buffer, // Array of unsigned characters (std::vector<unsigned char>)
		Date, // DbDate structure
		Time, // DbTime structure
		DateTime // DbDateTime structure
	};

	String ToString(const DbValueType value);
}