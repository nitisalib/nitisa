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
	String ToString(const DbValueType value)
	{
		switch (value)
		{
		case DbValueType::Bool: return L"Bool";
		case DbValueType::Char: return L"Char";
		case DbValueType::Byte: return L"Byte";
		case DbValueType::Short: return L"Short";
		case DbValueType::UShort: return L"UShort";
		case DbValueType::Int: return L"Int";
		case DbValueType::UInt: return L"UInt";
		case DbValueType::Int64: return L"Int64";
		case DbValueType::UInt64: return L"UInt64";
		case DbValueType::Float: return L"Float";
		case DbValueType::Double: return L"Double";
		case DbValueType::String: return L"String";
		case DbValueType::AnsiString: return L"AnsiString";
		case DbValueType::Buffer: return L"Buffer";
		case DbValueType::Date: return L"Date";
		case DbValueType::Time: return L"Time";
		case DbValueType::DateTime: return L"DateTime";
		default: return L"Null";
		}
	}
}