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
	static wchar_t WCharBuffer64[64];
	static char CharBuffer64[64];

#pragma region String type conversion functions
	String AnsiToString(const AnsiString &str)
	{
		std::vector<wchar_t> buffer(str.size());
		std::use_facet<std::ctype<wchar_t>>(std::locale()).widen(str.data(), str.data() + str.size(), buffer.data());
		return String(buffer.data(), buffer.size());
	}

	UTF8String AnsiToUTF8(const AnsiString &str)
	{
		return StringToUTF8(AnsiToString(str));
	}

	AnsiString UTF8ToAnsi(const UTF8String &str, const char replacer)
	{
		return StringToAnsi(UTF8ToString(str), replacer);
	}

	String UTF8ToString(const UTF8String &str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(str);
	}

	AnsiString StringToAnsi(const String &str, const char replacer)
	{
		std::vector<char> buffer(str.size());
		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(str.data(), str.data() + str.size(), replacer, buffer.data());
		return AnsiString(buffer.data(), buffer.size());
	}

	UTF8String StringToUTF8(const String &str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(str);
	}
#pragma endregion

#pragma region Convert strings to numerical values
	int StringToInt(const String &str)
	{
		String s{ Trim(str) };
		size_t idx;
		int result{ std::stoi(s, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		return result;
	}

	int StringToInt(const AnsiString &str)
	{
		AnsiString s{ Trim(str) };
		size_t idx;
		int result{ std::stoi(s, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		return result;
	}

	unsigned int StringToUInt(const String &str)
	{
		String s{ Trim(str) };
		size_t idx;
		long long result{ std::stoll(s, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		if (result < (long long)std::numeric_limits<unsigned int>::min() || result >(long long)std::numeric_limits<unsigned int>::max())
			throw std::out_of_range("Number is out of range");
		return (unsigned int)result;
	}

	unsigned int StringToUInt(const AnsiString &str)
	{
		AnsiString s{ Trim(str) };
		size_t idx;
		long long result{ std::stoll(s, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		if (result < (long long)std::numeric_limits<unsigned int>::min() || result >(long long)std::numeric_limits<unsigned int>::max())
			throw std::out_of_range("Number is out of range");
		return (unsigned int)result;
	}

	long long StringToInt64(const String &str)
	{
		String s{ Trim(str) };
		size_t idx;
		long long result{ std::stoll(s, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		return result;
	}

	long long StringToInt64(const AnsiString &str)
	{
		AnsiString s{ Trim(str) };
		size_t idx;
		long long result{ std::stoll(s, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		return result;
	}

	unsigned long long StringToUInt64(const String &str)
	{
		String s{ Trim(str) };
		if (s.length() > 0 && s[0] == L'-')
			throw std::out_of_range("Number is out of range");
		size_t idx;
		unsigned long long result{ std::stoull(s, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		return result;
	}

	unsigned long long StringToUInt64(const AnsiString &str)
	{
		AnsiString s{ Trim(str) };
		if (s.length() > 0 && s[0] == '-')
			throw std::out_of_range("Number is out of range");
		size_t idx;
		unsigned long long result{ std::stoull(s, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		return result;
	}

	float StringToFloat(const String &str)
	{
		size_t idx;
		float result{ std::stof(str, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		return result;
	}

	float StringToFloat(const AnsiString &str)
	{
		size_t idx;
		float result{ std::stof(str, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		return result;
	}

	double StringToDouble(const String &str)
	{
		size_t idx;
		double result{ std::stod(str, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		return result;
	}

	double StringToDouble(const AnsiString &str)
	{
		size_t idx;
		double result{ std::stod(str, &idx) };
		if (idx < str.length())
			throw std::invalid_argument("Invalid argument");
		return result;
	}
#pragma endregion

#pragma region Convert numerical values to strings
	String ToString(const int value)
	{
		return std::to_wstring(value);
	}

	String ToString(const unsigned int value)
	{
		return std::to_wstring(value);
	}

	String ToString(const long long value)
	{
		return std::to_wstring(value);
	}

	String ToString(const unsigned long long value)
	{
		return std::to_wstring(value);
	}

	String ToString(const float value)
	{
		return std::to_wstring(value);
	}

	String ToStringCompact(const float value)
	{
		std::wstringstream ss;
		ss << value;
		return ss.str();
	}

	String ToString(const double value)
	{
		return std::to_wstring(value);
	}

	String ToStringCompact(const double value)
	{
		std::wstringstream ss;
		ss << value;
		return ss.str();
	}

	AnsiString ToAnsi(const int value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsi(const unsigned int value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsi(const long long value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsi(const unsigned long long value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsi(const float value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsiCompact(const float value)
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	}

	AnsiString ToAnsi(const double value)
	{
		return std::to_string(value);
	}

	AnsiString ToAnsiCompact(const double value)
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	}
#pragma endregion

#pragma region Try convert strings to numerical values
	bool TryStringToInt(const String &str, int &out)
	{
		try
		{
			int r{ StringToInt(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToUInt(const String &str, unsigned int &out)
	{
		try
		{
			unsigned int r{ StringToUInt(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToInt64(const String &str, long long &out)
	{
		try
		{
			long long r{ StringToInt64(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToUInt64(const String &str, unsigned long long &out)
	{
		try
		{
			unsigned long long r{ StringToUInt64(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToFloat(const String &str, float &out)
	{
		try
		{
			float r{ StringToFloat(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToDouble(const String &str, double &out)
	{
		try
		{
			double r{ StringToDouble(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToInt(const AnsiString &str, int &out)
	{
		try
		{
			int r{ StringToInt(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToUInt(const AnsiString &str, unsigned int &out)
	{
		try
		{
			unsigned int r{ StringToUInt(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToInt64(const AnsiString &str, long long &out)
	{
		try
		{
			long long r{ StringToInt64(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToUInt64(const AnsiString &str, unsigned long long &out)
	{
		try
		{
			unsigned long long r{ StringToUInt64(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToFloat(const AnsiString &str, float &out)
	{
		try
		{
			float r{ StringToFloat(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryStringToDouble(const AnsiString &str, double &out)
	{
		try
		{
			double r{ StringToDouble(str) };
			out = r;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	long long BinToInt64(const String &str)
	{
		if (str.length() == 0 || str.length() > 64)
			return -1;
		long long result{ 0 };
		unsigned char t;
		for (auto c : str)
		{
			if ((t = BinToByte(c)) == 255)
				return -1;
			result = (result << 1) + t;
		}
		return result;
	}

	long long BinToInt64(const AnsiString &str)
	{
		if (str.length() == 0 || str.length() > 64)
			return -1;
		long long result{ 0 };
		unsigned char t;
		for (auto c : str)
		{
			if ((t = BinToByte(c)) == 255)
				return -1;
			result = (result << 1) + (long long)t;
		}
		return result;
	}

	long long OctToInt64(const String &str)
	{
		if (str.length() == 0 || str.length() > 21)
			return -1;
		long long result{ 0 };
		unsigned char t;
		for (auto c : str)
		{
			if ((t = OctToByte(c)) == 255)
				return -1;
			result = (result << 3) + (long long)t;
		}
		return result;
	}

	long long OctToInt64(const AnsiString &str)
	{
		if (str.length() == 0 || str.length() > 21)
			return -1;
		long long result{ 0 };
		unsigned char t;
		for (auto c : str)
		{
			if ((t = OctToByte(c)) == 255)
				return -1;
			result = (result << 3) + (long long)t;
		}
		return result;
	}

	long long HexToInt64(const String &str)
	{
		if (str.length() == 0 || str.length() > 16)
			return -1;
		long long result{ 0 };
		unsigned char t;
		for (auto c : str)
		{
			if ((t = HexToByte(c)) == 255)
				return -1;
			result = (result << 4) + t;
		}
		return result;
	}

	long long HexToInt64(const AnsiString &str)
	{
		if (str.length() == 0 || str.length() > 16)
			return -1;
		long long result{ 0 };
		unsigned char t;
		for (auto c : str)
		{
			if ((t = HexToByte(c)) == 255)
				return -1;
			result = (result << 4) + t;
		}
		return result;
	}

	bool TryOctToUInt64(const String &str, unsigned long long &result)
	{
		if (str.length() == 0 || str.length() > 21)
			return false;
		result = 0;
		unsigned char t;
		for (auto c : str)
		{
			if ((t = OctToByte(c)) == 255)
				return false;
			result = (result << 3) + t;
		}
		return true;
	}

	bool TryOctToUInt64(const AnsiString &str, unsigned long long &result)
	{
		if (str.length() == 0 || str.length() > 21)
			return false;
		result = 0;
		unsigned char t;
		for (auto c : str)
		{
			if ((t = OctToByte(c)) == 255)
				return false;
			result = (result << 3) + t;
		}
		return true;
	}

	bool TryBinToUInt64(const String &str, unsigned long long &result)
	{
		if (str.length() == 0 || str.length() > 64)
			return false;
		result = 0;
		unsigned char t;
		for (auto c : str)
		{
			if ((t = BinToByte(c)) == 255)
				return false;
			result = (result << 1) + t;
		}
		return true;
	}

	bool TryBinToUInt64(const AnsiString &str, unsigned long long &result)
	{
		if (str.length() == 0 || str.length() > 64)
			return false;
		result = 0;
		unsigned char t;
		for (auto c : str)
		{
			if ((t = BinToByte(c)) == 255)
				return false;
			result = (result << 1) + t;
		}
		return true;
	}

	bool TryHexToUInt64(const String &str, unsigned long long &result)
	{
		if (str.length() == 0 || str.length() > 16)
			return false;
		result = 0;
		unsigned char t;
		for (auto c : str)
		{
			if ((t = HexToByte(c)) == 255)
				return false;
			result = (result << 4) + t;
		}
		return true;
	}

	bool TryHexToUInt64(const AnsiString &str, unsigned long long &result)
	{
		if (str.length() == 0 || str.length() > 16)
			return false;
		result = 0;
		unsigned char t;
		for (auto c : str)
		{
			if ((t = HexToByte(c)) == 255)
				return false;
			result = (result << 4) + t;
		}
		return true;
	}

	char ByteLoToHexAnsi(const unsigned char value)
	{
		switch (value % 16)
		{
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		case 10: return 'A';
		case 11: return 'B';
		case 12: return 'C';
		case 13: return 'D';
		case 14: return 'E';
		case 15: return 'F';
		}
		return '0';
	}

	char ByteHiToHexAnsi(const unsigned char value)
	{
	#ifdef __GNUC__
		return ByteLoToHexAnsi((unsigned char)((int)value >> 4));
	#else
		return ByteLoToHexAnsi(value >> 4);
	#endif
	}

	wchar_t ByteLoToHex(const unsigned char value)
	{
		switch (value % 16)
		{
		case 1: return L'1';
		case 2: return L'2';
		case 3: return L'3';
		case 4: return L'4';
		case 5: return L'5';
		case 6: return L'6';
		case 7: return L'7';
		case 8: return L'8';
		case 9: return L'9';
		case 10: return L'A';
		case 11: return L'B';
		case 12: return L'C';
		case 13: return L'D';
		case 14: return L'E';
		case 15: return L'F';
		}
		return L'0';
	}

	wchar_t ByteHiToHex(const unsigned char value)
	{
	#ifdef __GNUC__
		return ByteLoToHex((unsigned char)((int)value >> 4));
	#else
		return ByteLoToHex(value >> 4);
	#endif
	}

	String Hex(const unsigned int value)
	{
		String result;
		result.resize(sizeof(unsigned int) * 2);
		for (size_t i = 0; i < sizeof(unsigned int); i++)
		{
			result[i * 2 + 0] = ByteHiToHex(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned int) - 1 - i]);
			result[i * 2 + 1] = ByteLoToHex(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned int) - 1 - i]);
		}
		return result;
	}

	String Hex(const unsigned long long value)
	{
		String result;
		result.resize(sizeof(unsigned long long) * 2);
		for (size_t i = 0; i < sizeof(unsigned long long); i++)
		{
			result[i * 2 + 0] = ByteHiToHex(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned long long) - 1 - i]);
			result[i * 2 + 1] = ByteLoToHex(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned long long) - 1 - i]);
		}
		return result;
	}

	AnsiString HexAnsi(const unsigned int value)
	{
		AnsiString result;
		result.resize(sizeof(unsigned int) * 2);
		for (size_t i = 0; i < sizeof(unsigned int); i++)
		{
			result[i * 2 + 0] = ByteHiToHexAnsi(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned int) - 1 - i]);
			result[i * 2 + 1] = ByteLoToHexAnsi(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned int) - 1 - i]);
		}
		return result;
	}

	AnsiString HexAnsi(const unsigned long long value)
	{
		AnsiString result;
		result.resize(sizeof(unsigned long long) * 2);
		for (size_t i = 0; i < sizeof(unsigned long long); i++)
		{
			result[i * 2 + 0] = ByteHiToHexAnsi(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned long long) - 1 - i]);
			result[i * 2 + 1] = ByteLoToHexAnsi(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned long long) - 1 - i]);
		}
		return result;
	}

	String HexCompact(const unsigned int value)
	{
		String result;
		bool skip{ true };
		for (size_t i = 0; i < sizeof(unsigned int); i++)
		{
			if (skip && reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned int) - 1 - i] == 0 && i < sizeof(unsigned int) - 1)
				continue;
			skip = false;
			result += ByteHiToHex(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned int) - 1 - i]);
			result += ByteLoToHex(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned int) - 1 - i]);
		}
		return result;
	}

	String HexCompact(const unsigned long long value)
	{
		String result;
		bool skip{ true };
		for (size_t i = 0; i < sizeof(unsigned long long); i++)
		{
			if (skip && reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned long long) - 1 - i] == 0 && i < sizeof(unsigned long long) - 1)
				continue;
			skip = false;
			result += ByteHiToHex(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned long long) - 1 - i]);
			result += ByteLoToHex(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned long long) - 1 - i]);
		}
		return result;
	}

	AnsiString HexAnsiCompact(const unsigned int value)
	{
		AnsiString result;
		bool skip{ true };
		for (size_t i = 0; i < sizeof(unsigned int); i++)
		{
			if (skip && reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned int) - 1 - i] == 0 && i < sizeof(unsigned int) - 1)
				continue;
			skip = false;
			result += ByteHiToHexAnsi(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned int) - 1 - i]);
			result += ByteLoToHexAnsi(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned int) - 1 - i]);
		}
		return result;
	}

	AnsiString HexAnsiCompact(const unsigned long long value)
	{
		AnsiString result;
		bool skip{ true };
		for (size_t i = 0; i < sizeof(unsigned long long); i++)
		{
			if (skip && reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned long long) - 1 - i] == 0 && i < sizeof(unsigned long long) - 1)
				continue;
			skip = false;
			result += ByteHiToHexAnsi(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned long long) - 1 - i]);
			result += ByteLoToHexAnsi(reinterpret_cast<const unsigned char*>(&value)[sizeof(unsigned long long) - 1 - i]);
		}
		return result;
	}

	String ToFixed(const float value, const int signs)
	{
		int s{ signs };
		if (s < 0)
			s = 0;
		else if (s > 9)
			s = 9;
		String format;
		format = L"%." + ToString(s) + L"f";
	#ifdef __GNUC__
		swprintf(WCharBuffer64, 64, format.c_str(), value);
	#else
		swprintf_s(WCharBuffer64, 64, format.c_str(), value);
	#endif
		return WCharBuffer64;
	}

	String ToFixed(const double value, const int signs)
	{
		int s{ signs };
		if (s < 0)
			s = 0;
		else if (s > 9)
			s = 9;
		String format;
		format = L"%." + ToString(s) + L"f";
	#ifdef __GNUC__
		swprintf(WCharBuffer64, 64, format.c_str(), value);
	#else
		swprintf_s(WCharBuffer64, 64, format.c_str(), value);
	#endif
		return WCharBuffer64;
	}

	AnsiString ToFixedAnsi(const float value, const int signs)
	{
		int s{ signs };
		if (s < 0)
			s = 0;
		else if (s > 9)
			s = 9;
		AnsiString format;
		format = "%." + ToAnsi(s) + "f";
	#ifdef __GNUC__
		sprintf(CharBuffer64, format.c_str(), value);
	#else
		sprintf_s(CharBuffer64, 64, format.c_str(), value);
	#endif
		return CharBuffer64;
	}

	AnsiString ToFixedAnsi(const double value, const int signs)
	{
		int s{ signs };
		if (s < 0)
			s = 0;
		else if (s > 9)
			s = 9;
		AnsiString format;
		format = "%." + ToAnsi(s) + "f";
	#ifdef __GNUC__
		sprintf(CharBuffer64, format.c_str(), value);
	#else
		sprintf_s(CharBuffer64, 64, format.c_str(), value);
	#endif
		return CharBuffer64;
	}

	String PadLeft(const String &str, const wchar_t c, const size_t length)
	{
		if (str.length() >= length)
			return str;
		String t;
		t.resize(length - str.length(), c);
		return t + str;
	}

	AnsiString PadLeft(const AnsiString &str, const char c, const size_t length)
	{
		if (str.length() >= length)
			return str;
		AnsiString t;
		t.resize(length - str.length(), c);
		return t + str;
	}

	void PadLeftDirect(String &str, const wchar_t c, const size_t length)
	{
		if (str.length() >= length)
			return;
		String t;
		t.resize(length - str.length(), c);
		str = t + str;
	}

	void PadLeftDirect(AnsiString &str, const char c, const size_t length)
	{
		if (str.length() >= length)
			return;
		AnsiString t;
		t.resize(length - str.length(), c);
		str = t + str;
	}

	String PadRight(const String &str, const wchar_t c, const size_t length)
	{
		if (str.length() >= length)
			return str;
		String t{ str };
		t.resize(length, c);
		return t;
	}

	AnsiString PadRight(const AnsiString &str, const char c, const size_t length)
	{
		if (str.length() >= length)
			return str;
		AnsiString t{ str };
		t.resize(length, c);
		return t;
	}

	void PadRightDirect(String &str, const wchar_t c, const size_t length)
	{
		if (str.length() >= length)
			return;
		str.resize(length, c);
	}

	void PadRightDirect(AnsiString &str, const char c, const size_t length)
	{
		if (str.length() >= length)
			return;
		str.resize(length, c);
	}
#pragma endregion

#pragma region Formatting
	wchar_t ToUpper(const wchar_t chr, const std::locale &locale)
	{
		return std::use_facet<std::ctype<wchar_t>>(locale).toupper(chr);
	}

	char ToUpper(const char chr, const std::locale &locale)
	{
		return std::use_facet<std::ctype<char>>(locale).toupper(chr);
	}

	wchar_t ToLower(const wchar_t chr, const std::locale &locale)
	{
		return std::use_facet<std::ctype<wchar_t>>(locale).tolower(chr);
	}

	char ToLower(const char chr, const std::locale &locale)
	{
		return std::use_facet<std::ctype<char>>(locale).tolower(chr);
	}

	String Replace(const String &str, const String &search, const String &replace)
	{
		if (search.length() == 0)
			return str;
		size_t pos{ str.find(search, 0) };
		if (pos == String::npos)
			return str;
		String result(str);
		result.replace(pos, search.length(), replace);
		return result;
	}

	String Replace(const String &str, const StringKeyValue &pair)
	{
		if (pair.first.length() == 0)
			return str;
		size_t pos{ str.find(pair.first, 0) };
		if (pos == String::npos)
			return str;
		String result(str);
		result.replace(pos, pair.first.length(), pair.second);
		return result;
	}

	AnsiString Replace(const AnsiString &str, const AnsiString &search, const AnsiString &replace)
	{
		if (search.length() == 0)
			return str;
		size_t pos{ str.find(search, 0) };
		if (pos == AnsiString::npos)
			return str;
		AnsiString result(str);
		result.replace(pos, search.length(), replace);
		return result;
	}

	AnsiString Replace(const AnsiString &str, const AnsiStringKeyValue &pair)
	{
		if (pair.first.length() == 0)
			return str;
		size_t pos{ str.find(pair.first, 0) };
		if (pos == AnsiString::npos)
			return str;
		AnsiString result(str);
		result.replace(pos, pair.first.length(), pair.second);
		return result;
	}

	void ReplaceDirect(String &str, const String &search, const String &replace)
	{
		if (search.length() == 0)
			return;
		size_t pos{ str.find(search, 0) };
		if (pos == String::npos)
			return;
		str.replace(pos, search.length(), replace);
	}

	void ReplaceDirect(String &str, const StringKeyValue &pair)
	{
		if (pair.first.length() == 0)
			return;
		size_t pos{ str.find(pair.first, 0) };
		if (pos == String::npos)
			return;
		str.replace(pos, pair.first.length(), pair.second);
	}

	void ReplaceDirect(AnsiString &str, const AnsiString &search, const AnsiString &replace)
	{
		if (search.length() == 0)
			return;
		size_t pos{ str.find(search, 0) };
		if (pos == String::npos)
			return;
		str.replace(pos, search.length(), replace);
	}

	void ReplaceDirect(AnsiString &str, const AnsiStringKeyValue &pair)
	{
		if (pair.first.length() == 0)
			return;
		size_t pos{ str.find(pair.first, 0) };
		if (pos == String::npos)
			return;
		str.replace(pos, pair.first.length(), pair.second);
	}

	String ReplaceAll(const String &str, const String &search, const String &replace)
	{
		if (search.length() == 0)
			return str;
		size_t pos{ str.find(search, 0) };
		if (pos == String::npos)
			return str;
		String result(str);
		do
		{
			result.replace(pos, search.length(), replace);
			pos = result.find(search, pos + replace.length());
		} while (pos != String::npos);
		return result;
	}

	String ReplaceAll(const String &str, const StringKeyValue &pair)
	{
		if (pair.first.length() == 0)
			return str;
		size_t pos{ str.find(pair.first, 0) };
		if (pos == String::npos)
			return str;
		String result(str);
		do
		{
			result.replace(pos, pair.first.length(), pair.second);
			pos = result.find(pair.first, pos + pair.second.length());
		} while (pos != String::npos);
		return result;
	}

	String ReplaceAll(const String &str, const StringArray &search, const StringArray &replace)
	{
		if (str.empty() || search.empty() || replace.size() != search.size())
			return str;
		String result{ str };
		for (size_t index = 0; index < search.size(); index++)
			ReplaceAllDirect(result, search[index], replace[index]);
		return result;
	}

	String ReplaceAll(const String &str, const StringKeyValueArray &pairs)
	{
		if (str.empty() || pairs.empty())
			return str;
		String result{ str };
		for (size_t index = 0; index < pairs.size(); index++)
			ReplaceAllDirect(result, pairs[index]);
		return result;
	}

	AnsiString ReplaceAll(const AnsiString &str, const AnsiString &search, const AnsiString &replace)
	{
		if (search.length() == 0)
			return str;
		size_t pos{ str.find(search, 0) };
		if (pos == AnsiString::npos)
			return str;
		AnsiString result(str);
		do
		{
			result.replace(pos, search.length(), replace);
			pos = result.find(search, pos + replace.length());
		} while (pos != AnsiString::npos);
		return result;
	}

	AnsiString ReplaceAll(const AnsiString &str, const AnsiStringKeyValue &pair)
	{
		if (pair.first.length() == 0)
			return str;
		size_t pos{ str.find(pair.first, 0) };
		if (pos == AnsiString::npos)
			return str;
		AnsiString result(str);
		do
		{
			result.replace(pos, pair.first.length(), pair.second);
			pos = result.find(pair.first, pos + pair.second.length());
		} while (pos != AnsiString::npos);
		return result;
	}

	AnsiString ReplaceAll(const AnsiString &str, const AnsiStringArray &search, const AnsiStringArray &replace)
	{
		if (str.empty() || search.empty() || replace.size() != search.size())
			return str;
		AnsiString result{ str };
		for (size_t index = 0; index < search.size(); index++)
			ReplaceAllDirect(result, search[index], replace[index]);
		return result;
	}

	AnsiString ReplaceAll(const AnsiString &str, const AnsiStringKeyValueArray &pairs)
	{
		if (str.empty() || pairs.empty())
			return str;
		AnsiString result{ str };
		for (size_t index = 0; index < pairs.size(); index++)
			ReplaceAllDirect(result, pairs[index]);
		return result;
	}

	void ReplaceAllDirect(String &str, const String &search, const String &replace)
	{
		if (search.length() == 0)
			return;
		size_t pos{ str.find(search, 0) };
		if (pos == String::npos)
			return;
		do
		{
			str.replace(pos, search.length(), replace);
			pos = str.find(search, pos + replace.length());
		} while (pos != String::npos);
	}

	void ReplaceAllDirect(String &str, const StringKeyValue &pair)
	{
		if (pair.first.length() == 0)
			return;
		size_t pos{ str.find(pair.first, 0) };
		if (pos == String::npos)
			return;
		do
		{
			str.replace(pos, pair.first.length(), pair.second);
			pos = str.find(pair.first, pos + pair.second.length());
		} while (pos != String::npos);
	}

	void ReplaceAllDirect(String &str, const StringArray &search, const StringArray &replace)
	{
		if (str.empty() || search.empty() || replace.size() != search.size())
			return;
		for (size_t index = 0; index < search.size(); index++)
			ReplaceAllDirect(str, search[index], replace[index]);
	}

	void ReplaceAllDirect(String &str, const StringKeyValueArray &pairs)
	{
		if (str.empty() || pairs.empty())
			return;
		for (size_t index = 0; index < pairs.size(); index++)
			ReplaceAllDirect(str, pairs[index]);
	}

	void ReplaceAllDirect(AnsiString &str, const AnsiString &search, const AnsiString &replace)
	{
		if (search.length() == 0)
			return;
		size_t pos{ str.find(search, 0) };
		if (pos == AnsiString::npos)
			return;
		do
		{
			str.replace(pos, search.length(), replace);
			pos = str.find(search, pos + replace.length());
		} while (pos != AnsiString::npos);
	}

	void ReplaceAllDirect(AnsiString &str, const AnsiStringKeyValue &pair)
	{
		if (pair.first.length() == 0)
			return;
		size_t pos{ str.find(pair.first, 0) };
		if (pos == AnsiString::npos)
			return;
		do
		{
			str.replace(pos, pair.first.length(), pair.second);
			pos = str.find(pair.first, pos + pair.second.length());
		} while (pos != AnsiString::npos);
	}

	void ReplaceAllDirect(AnsiString &str, const AnsiStringArray &search, const AnsiStringArray &replace)
	{
		if (str.empty() || search.empty() || replace.size() != search.size())
			return;
		for (size_t index = 0; index < search.size(); index++)
			ReplaceAllDirect(str, search[index], replace[index]);
	}

	void ReplaceAllDirect(AnsiString &str, const AnsiStringKeyValueArray &pairs)
	{
		if (str.empty() || pairs.empty())
			return;
		for (size_t index = 0; index < pairs.size(); index++)
			ReplaceAllDirect(str, pairs[index]);
	}

	String TrimRight(const String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t last{ str.length() - 1 };
		while (last > 0)
		{
			if (!std::isspace(str[last], locale))
				break;
			last--;
		}
		if (last == 0 && std::isspace(str[last], locale))
			return L"";
		if (last == str.length() - 1)
			return str;
		return str.substr(0, last + 1);
	}

	AnsiString TrimRight(const AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t last{ str.length() - 1 };
		while (last > 0)
		{
			if (!std::isspace(str[last], locale))
				break;
			last--;
		}
		if (last == 0 && std::isspace(str[last], locale))
			return "";
		if (last == str.length() - 1)
			return str;
		return str.substr(0, last + 1);
	}

	void TrimRightDirect(String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t last{ str.length() - 1 };
		while (last > 0)
		{
			if (!std::isspace(str[last], locale))
				break;
			last--;
		}
		if (last == 0 && std::isspace(str[last], locale))
		{
			str.clear();
			return;
		}
		if (last == str.length() - 1)
			return;
		str.erase(last + 1, str.length() - last + 1);
	}

	void TrimRightDirect(AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t last{ str.length() - 1 };
		while (last > 0)
		{
			if (!std::isspace(str[last], locale))
				break;
			last--;
		}
		if (last == 0 && std::isspace(str[last], locale))
		{
			str.clear();
			return;
		}
		if (last == str.length() - 1)
			return;
		str.erase(last + 1, str.length() - last + 1);
	}

	String TrimLeft(const String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		if (first == 0)
			return str;
		return str.substr(first);
	}

	AnsiString TrimLeft(const AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		if (first == 0)
			return str;
		return str.substr(first);
	}

	void TrimLeftDirect(String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		if (first == 0)
			return;
		str.erase(0, first);
	}

	void TrimLeftDirect(AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		if (first == 0)
			return;
		str.erase(0, first);
	}

	String Trim(const String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		size_t last{ str.length() - 1 };
		while (last > 0)
		{
			if (!std::isspace(str[last], locale))
				break;
			last--;
		}
		if (last < first || (last == 0 && std::isspace(str[last], locale)))
			return L"";
		return str.substr(first, last - first + 1);
	}

	AnsiString Trim(const AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return str;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		size_t last{ str.length() - 1 };
		while (last > 0)
		{
			if (!std::isspace(str[last], locale))
				break;
			last--;
		}
		if (last < first || (last == 0 && std::isspace(str[last], locale)))
			return "";
		return str.substr(first, last - first + 1);
	}

	void TrimDirect(String &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		size_t last{ str.length() - 1 };
		while (last > 0)
		{
			if (!std::isspace(str[last], locale))
				break;
			last--;
		}
		if (last < first || (last == 0 && std::isspace(str[last], locale)))
		{
			str.clear();
			return;
		}
		str = str.substr(first, last - first + 1);
	}

	void TrimDirect(AnsiString &str, const std::locale &locale)
	{
		if (str.length() == 0)
			return;
		size_t first;
		for (first = 0; first < str.length(); first++)
			if (!std::isspace(str[first], locale))
				break;
		size_t last{ str.length() - 1 };
		while (last > 0)
		{
			if (!std::isspace(str[last], locale))
				break;
			last--;
		}
		if (last < first || (last == 0 && std::isspace(str[last], locale)))
		{
			str.clear();
			return;
		}
		str = str.substr(first, last - first + 1);
	}

#ifndef __GNUC__
	String FormatDateTime(const String &format, const tm datetime, const std::locale &locale)
	{
		std::basic_stringstream<wchar_t> stream;
		std::use_facet<std::time_put<wchar_t>>(locale).put(std::basic_ostream<wchar_t>::_Iter(stream.rdbuf()), stream, L' ', &datetime, format.data(), format.data() + format.length());
		return stream.rdbuf()->str();
	}

	AnsiString FormatDateTime(const AnsiString &format, const tm datetime, const std::locale &locale)
	{
		std::basic_stringstream<char> stream;
		std::use_facet<std::time_put<char>>(locale).put(std::basic_ostream<char>::_Iter(stream.rdbuf()), stream, ' ', &datetime, format.data(), format.data() + format.length());
		return stream.rdbuf()->str();
	}

	bool ParseDateTime(const String &str, tm &out, const String &format, const std::locale &locale)
	{
		std::basic_stringstream<wchar_t> stream(str);
		std::ios_base::iostate state = std::ios_base::goodbit;
		std::use_facet<std::time_get<wchar_t>>(locale).get(std::basic_istream<wchar_t>::_Iter(stream.rdbuf()), std::istreambuf_iterator<wchar_t>(), stream, state, &out, format.data(), format.data() + format.length());
		return state == std::ios_base::goodbit || state == std::ios_base::eofbit;
	}

	bool ParseDateTime(const AnsiString &str, tm &out, const AnsiString &format, const std::locale &locale)
	{
		std::basic_stringstream<char> stream(str);
		std::ios_base::iostate state = std::ios_base::goodbit;
		std::use_facet<std::time_get<char>>(locale).get(std::basic_istream<char>::_Iter(stream.rdbuf()), std::istreambuf_iterator<char>(), stream, state, &out, format.data(), format.data() + format.length());
		return state == std::ios_base::goodbit || state == std::ios_base::eofbit;
	}
#endif

	void Explode(const String &str, const String &delimiter, StringArray &out, const bool remove_empty)
	{
		out.clear();
		if (str.empty())
		{
			if (!remove_empty)
				out.push_back(str);
			return;
		}
		if (delimiter.empty())
		{
			out.push_back(str);
			return;
		}
		String::size_type start{ 0 }, index;
		while (true)
		{
			index = str.find(delimiter, start);
			if (index == String::npos)
			{
				if (start < str.length() || !remove_empty)
					out.push_back(str.substr(start, str.length() - start));
				break;
			}
			if (index > start || (index == start && !remove_empty))
				out.push_back(str.substr(start, index - start));
			start = index + delimiter.length();
		}
	}

	void Explode(const AnsiString &str, const AnsiString &delimiter, AnsiStringArray &out, const bool remove_empty)
	{
		out.clear();
		if (str.empty())
		{
			if (!remove_empty)
				out.push_back(str);
			return;
		}
		if (delimiter.empty())
		{
			out.push_back(str);
			return;
		}
		AnsiString::size_type start{ 0 }, index;
		while (true)
		{
			index = str.find(delimiter, start);
			if (index == AnsiString::npos)
			{
				if (start < str.length() || !remove_empty)
					out.push_back(str.substr(start, str.length() - start));
				break;
			}
			if (index > start || (index == start && !remove_empty))
				out.push_back(str.substr(start, index - start));
			start = index + delimiter.length();
		}
	}

	String ToUpper(const String &str, const std::locale &locale)
	{
		String result{ str };
		for (wchar_t &c : result)
			c = std::use_facet<std::ctype<wchar_t>>(locale).toupper(c);
		return result;
	}

	AnsiString ToUpper(const AnsiString &str, const std::locale &locale)
	{
		AnsiString result{ str };
		for (char &c : result)
			c = std::use_facet<std::ctype<char>>(locale).toupper(c);
		return result;
	}

	void ToUpperDirect(String &str, const std::locale &locale)
	{
		for (wchar_t &c : str)
			c = std::use_facet<std::ctype<wchar_t>>(locale).toupper(c);
	}

	void ToUpperDirect(AnsiString &str, const std::locale &locale)
	{
		for (char &c : str)
			c = std::use_facet<std::ctype<char>>(locale).toupper(c);
	}

	String ToLower(const String &str, const std::locale &locale)
	{
		String result{ str };
		for (wchar_t &c : result)
			c = std::use_facet<std::ctype<wchar_t>>(locale).tolower(c);
		return result;
	}

	AnsiString ToLower(const AnsiString &str, const std::locale &locale)
	{
		AnsiString result{ str };
		for (char &c : result)
			c = std::use_facet<std::ctype<char>>(locale).tolower(c);
		return result;
	}

	void ToLowerDirect(String &str, const std::locale &locale)
	{
		for (wchar_t &c : str)
			c = std::use_facet<std::ctype<wchar_t>>(locale).tolower(c);
	}

	void ToLowerDirect(AnsiString &str, const std::locale &locale)
	{
		for (char &c : str)
			c = std::use_facet<std::ctype<char>>(locale).tolower(c);
	}

	StringArray Explode(const String &str, const String &delimiter, const bool remove_empty)
	{
		StringArray result;
		Explode(str, delimiter, result, remove_empty);
		return result;
	}

	AnsiStringArray Explode(const AnsiString &str, const AnsiString &delimiter, const bool remove_empty)
	{
		AnsiStringArray result;
		Explode(str, delimiter, result, remove_empty);
		return result;
	}

	AnsiString Implode(const AnsiString &glue, const AnsiStringArray &lines)
	{
		AnsiString result;
		size_t size{ 0 };
		for (auto &line : lines)
			size += line.length();
		if (lines.size() > 1)
			size += glue.length() * (lines.size() - 1);
		if (size > 0)
		{
			result.resize(size);
			size_t index{ 0 };
			for (auto &line : lines)
			{
				if (index > 0 && glue.length() > 0)
				{
					for (size_t i = 0; i < glue.length(); i++)
						result[index++] = glue[i];
				}
				for (size_t i = 0; i < line.length(); i++)
					result[index++] = line[i];
			}
		}
		return result;
	}

	String Implode(const String &glue, const StringArray &lines)
	{
		String result;
		size_t size{ 0 };
		for (auto &line : lines)
			size += line.length();
		if (lines.size() > 1)
			size += glue.length() * (lines.size() - 1);
		if (size > 0)
		{
			result.resize(size);
			size_t index{ 0 };
			for (auto &line : lines)
			{
				if (index > 0 && glue.length() > 0)
				{
					for (size_t i = 0; i < glue.length(); i++)
						result[index++] = glue[i];
				}
				for (size_t i = 0; i < line.length(); i++)
					result[index++] = line[i];
			}
		}
		return result;
	}
#pragma endregion

#pragma region Searching
	size_t SearchNextWord(const String &str, const size_t start, const bool with_punct, const std::locale &locale)
	{
		if (start >= str.length())
			return str.length();
		auto test{ with_punct ? static_cast<bool(*)(wchar_t ch, const std::locale & loc)>(std::isgraph<wchar_t>) : static_cast<bool(*)(wchar_t ch, const std::locale & loc)>(std::isalnum<wchar_t>) };
		size_t result{ start + 1 };
		if (test(str[result], locale)) // If current position is inside word, find first position outside word
			while (result < str.length() && test(str[result], locale))
				result++;
		while (result < str.length() && (!test(str[result], locale) || std::isspace(str[result], locale))) // Find first word char
			result++;
		return result;
	}

	size_t SearchPrevWord(const String &str, const size_t start, const bool with_punct, const std::locale &locale)
	{
		if (str.length() == 0)
			return 0;
		size_t result{ start };
		if (start > str.length())
			result = str.length();
		if (result > 0)
			result--;
		auto test{ with_punct ? static_cast<bool(*)(wchar_t ch, const std::locale & loc)>(std::isgraph<wchar_t>) : static_cast<bool(*)(wchar_t ch, const std::locale & loc)>(std::isalnum<wchar_t>) };
		if (!test(str[result], locale)) // If current position is outside word, find first position inside word
			while (result > 0 && (!test(str[result], locale) || std::isspace(str[result], locale)))
				result--;
		while (result > 0 && test(str[result - 1], locale)) // Find first word char
			result--;
		return result;
	}

	size_t SearchWordStartForward(const String &str, const size_t start, const std::locale &locale)
	{
		if (start >= str.length() || str.length() == 0)
			return String::npos;
		size_t result{ start }, len{ str.length() };
		while (result < len && !std::isspace(str[result], locale))
			result++;
		while (result < len && std::isspace(str[result], locale))
			result++;
		return result;
	}

	size_t SearchWordEndForward(const String &str, const size_t start, const std::locale &locale)
	{
		if (start >= str.length() || str.length() == 0)
			return String::npos;
		size_t result{ start }, len{ str.length() };
		while (result < len && std::isspace(str[result], locale))
			result++;
		while (result < len && !std::isspace(str[result], locale))
			result++;
		return result - 1;
	}

	size_t SearchWordStartBackward(const String &str, const size_t start, const std::locale &locale)
	{
		if (start >= str.length() || str.length() == 0)
			return String::npos;
		size_t result{ start };
		while (result > 0 && std::isspace(str[result], locale))
			result--;
		while (result > 0 && !std::isspace(str[result], locale))
			result--;
		if (result == 0 && !std::isspace(str[result], locale))
			return result;
		return result + 1;
	}

	size_t SearchWordEndBackward(const String &str, const size_t start, const std::locale &locale)
	{
		if (start >= str.length() || str.length() == 0)
			return String::npos;
		size_t result{ start };
		while (result > 0 && !std::isspace(str[result], locale))
			result--;
		while (result > 0 && std::isspace(str[result], locale))
			result--;
		return result;
	}
#pragma endregion

#pragma region Checking
	bool isCppIdentifier(const AnsiString &str)
	{
		// Should not be empty
		if (str.length() == 0)
			return false;
		// Should not start with digit
		if (isDigit(str[0]))
			return false;
		bool has_az{ false }, has_digit{ false };
		for (auto c : str)
		{
			if (isUnderscore(c))
				continue;
			if (isAz(c))
			{
				has_az = true;
				continue;
			}
			if (isDigit(c))
			{
				has_digit = true;
				continue;
			}
			// Unacceptable symbol
			return false;
		}
		// Should not has only underscores
		if (!has_az && !has_digit)
			return false;
		// Valid
		return true;
	}

	bool isCppIdentifier(const String &str)
	{
		// Should not be empty
		if (str.length() == 0)
			return false;
		// Should not start with digit
		if (isDigit(str[0]))
			return false;
		bool has_az{ false }, has_digit{ false };
		for (auto c : str)
		{
			if (isUnderscore(c))
				continue;
			if (isAz(c))
			{
				has_az = true;
				continue;
			}
			if (isDigit(c))
			{
				has_digit = true;
				continue;
			}
			// Unacceptable symbol
			return false;
		}
		// Should not has only underscores
		if (!has_az && !has_digit)
			return false;
		// Valid
		return true;
	}
#pragma endregion
}