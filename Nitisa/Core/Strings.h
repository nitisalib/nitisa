// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include <ctime>
#include <locale>
#include <string>
#include <utility>
#include <vector>

namespace nitisa
{
#pragma region String declarations
	using String = std::wstring;
	using AnsiString = std::string;
	using UTF8String = std::string;
	using StringArray = std::vector<String>;
	using AnsiStringArray = std::vector<AnsiString>;
	using UTF8StringArray = std::vector<UTF8String>;
	using StringKeyValue = std::pair<String, String>;
	using AnsiStringKeyValue = std::pair<AnsiString, AnsiString>;
	using UTF8StringKeyValue = std::pair<UTF8String, UTF8String>;
	using StringKeyValueArray = std::vector<StringKeyValue>;
	using AnsiStringKeyValueArray = std::vector<AnsiStringKeyValue>;
	using UTF8StringKeyValueArray = std::vector<UTF8StringKeyValue>;
#pragma endregion

#pragma region String type convertion functions
	/**
	Convert ansi string to wide chcracter string
	@param str Ansi string
	@return Wide character string
	*/
	String AnsiToString(const AnsiString &str);

	/**
	Convert ansi string to utf-8 encoded string
	@param str Ansi string
	@return UTF8 encoded string
	*/
	UTF8String AnsiToUTF8(const AnsiString &str);

	/**
	Convert utf-8 encoded string to ansi string
	@param str UTF-8 encoded string
	@param replacer When unsupported by ansi string char is found, it will be replaced with this one. Default '?'
	@return Ansi string
	*/
	AnsiString UTF8ToAnsi(const UTF8String &str, const char replacer = '?');

	/**
	Convert utf-8 encoded string to wide character string
	@param str UTF-8 encoded string
	@return Wide character string
	*/
	String UTF8ToString(const UTF8String &str);

	/**
	Convert wide character string to ansi string
	@param str Wide character string
	@param replacer When unsupported by ansi string char is found, it will be replaced with this one. Default '?'
	@return Ansi string
	*/
	AnsiString StringToAnsi(const String &str, const char replacer = '?');

	/**
	Convert wide character string to utf-8 encoded string
	@param str Wide character string
	@return UTF-8 encoded string
	*/
	UTF8String StringToUTF8(const String &str);
#pragma endregion

#pragma region Conversions between strings and numerical values
	/**
	Convert string to int
	@param str Wide character string
	@return integer value or throw exception if convertion failed
	*/
	int StringToInt(const String &str);

	/**
	Convert ansi string to int
	@param str Ansi string
	@return integer value or throw exception if conversion failed
	*/
	int StringToInt(const AnsiString &str);

	/**
	Convert string to unsigned int
	@param str Wide character string
	@return unsigned int or throw exception if conversion failed
	*/
	unsigned int StringToUInt(const String &str);

	/**
	Convert ansi string to unsigned int
	@param str Ansi string
	@return unsigned int or throw exception if conversion failed
	*/
	unsigned int StringToUInt(const AnsiString &str);

	/**
	Convert string to Int64
	@param str Wide character string
	@returns 64-bit integer or throw exception if conversion failed
	*/
	long long StringToInt64(const String &str);

	/**
	Convert ansi string to Int64
	@param str Ansi string
	@return 64-bit integer or throw exception if conversion failed
	*/
	long long StringToInt64(const AnsiString &str);

	/**
	Convert string to unsigned Int64
	@param str Wide character string
	@return unsigned 64-bit integer or throw exception if conversion failed
	*/
	unsigned long long StringToUInt64(const String &str);

	/**
	Convert ansi string to unsigned Int64
	@param str Ansi string
	@return unsigned 64-bit integer or throw exception if conversion failed
	*/
	unsigned long long StringToUInt64(const AnsiString &str);

	/**
	Convert string to float
	@param str Wide character string
	@return float value or throw exception if conversion failed
	*/
	float StringToFloat(const String &str);

	/**
	Convert ansi string to float
	@param str Ansi string
	@return float value or throw exception if conversion failed
	*/
	float StringToFloat(const AnsiString &str);

	/**
	Convert string to double
	@param str Wide character string
	@return double value or throw exception if conversion failed
	*/
	double StringToDouble(const String &str);

	/**
	Convert ansi string to double
	@param str Ansi string
	@return double value or throw exception if conversion failed
	*/
	double StringToDouble(const AnsiString &str);

	/**
	Convert int to string
	@param value int value
	@return Wide character string
	*/
	String ToString(const int value);

	/**
	Convert unsigned int to string
	@param value Unsigned integer value
	@return Wide character string
	*/
	String ToString(const unsigned int value);

	/**
	Convert Int64 to string
	@param value 64-bit integer
	@return Wide character string
	*/
	String ToString(const long long value);

	/**
	Convert unsigned Int64 to string
	@param value Unsigned 64-bit integer
	@return Wide character string
	*/
	String ToString(const unsigned long long value);

	/**
	Convert float to string
	@param value double value
	@return Wide character string
	*/
	String ToString(const float value);

	/**
	Convert float to string without zeroes at the end
	@param value double value
	@return Wide character string
	*/
	String ToStringCompact(const float value);

	/**
	Convert double to string
	@param value Double value
	@return Wide character string
	*/
	String ToString(const double value);

	/**
	Convert double to string without zeroes at the end
	@param value Double value
	@return Wide character string
	*/
	String ToStringCompact(const double value);

	/**
	Convert int to ansi string
	@param value int value
	@return Ansi string
	*/
	AnsiString ToAnsi(const int value);

	/**
	Convert unsigned int to ansi string
	@param value Unsigned integer value
	@return Ansi string
	*/
	AnsiString ToAnsi(const unsigned int value);

	/**
	Convert Int64 to ansi string
	@param value 64-bit integer value
	@return Ansi string
	*/
	AnsiString ToAnsi(const long long value);

	/**
	Convert unsigned Int64 to ansi string
	@param value Unsigned 64-bit value
	@return Ansi string
	*/
	AnsiString ToAnsi(const unsigned long long value);

	/**
	Convert float to ansi string
	@param value double value
	@return Ansi string
	*/
	AnsiString ToAnsi(const float value);

	/**
	Convert float to ansi string without zeros at the end
	@param value double value
	@return Ansi string
	*/
	AnsiString ToAnsiCompact(const float value);

	/**
	Convert double to ansi string
	@param value Double value
	@return Ansi string
	*/
	AnsiString ToAnsi(const double value);

	/**
	Convert double to ansi string without zeroes at the end
	@param value Double value
	@return Ansi string
	*/
	AnsiString ToAnsiCompact(const double value);

	/**
	Try convert string to int
	@param str Wide character string
	@param[out] out Reference to integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToInt(const String &str, int &out);

	/**
	Try convert string to unsigned int
	@param str Wide character string
	@param[out] out Reference to unsigned integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToUInt(const String &str, unsigned int &out);

	/**
	Try convert string to Int64
	@param str Wide character string
	@param[out] out Reference to 64-bit integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToInt64(const String &str, long long &out);

	/**
	Try convert string to unsigned Int64
	@param str Wide character string
	@param[out] out Reference to unsigned 64-bit integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToUInt64(const String &str, unsigned long long &out);

	/**
	Try convert string to float
	@param str Wide character string
	@param[out] out Reference to float where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToFloat(const String &str, float &out);

	/**
	Try convert string to double
	@param str Wide character string
	@param[out] out Reference to double where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToDouble(const String &str, double &out);

	/**
	Try convert ansi string to int
	@param str Ansi string
	@param[out] out Reference to integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToInt(const AnsiString &str, int &out);

	/**
	Try convert ansi string to unsigned int
	@param str Ansi string
	@param[out] out Reference to unsigned integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToUInt(const AnsiString &str, unsigned int &out);

	/**
	Try convert ansi string to Int64
	@param str Ansi string
	@param[out] out Reference to 64-bit integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToInt64(const AnsiString &str, long long &out);

	/**
	Try convert ansi string to unsigned Int64
	@param str Ansi string
	@param[out] out Reference to unsigned 64-bit integer where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToUInt64(const AnsiString &str, unsigned long long &out);

	/**
	Try convert ansi string to float
	@param str Ansi string
	@param[out] out Reference to float where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToFloat(const AnsiString &str, float &out);

	/**
	Try convert ansi string to double
	@param str Ansi string
	@param[out] out Reference to double where to store result of conversion
	@return True if conversion succeeded, otherwise - false
	*/
	bool TryStringToDouble(const AnsiString &str, double &out);

	long long BinToInt64(const String &str); // Return -1 if failed
	long long BinToInt64(const AnsiString &str); // Return -1 if failed
	long long OctToInt64(const String &str); // Return -1 if failed
	long long OctToInt64(const AnsiString &str); // Return -1 if failed
	long long HexToInt64(const String &str); // Return -1 if failed
	long long HexToInt64(const AnsiString &str); // Return -1 if failed
	bool TryBinToUInt64(const String &str, unsigned long long &result); // Return false if failed (result may be changed). Otherwise return true and result is populated with correct value
	bool TryBinToUInt64(const AnsiString &str, unsigned long long &result); // Return false if failed (result may be changed). Otherwise return true and result is populated with correct value
	bool TryOctToUInt64(const String &str, unsigned long long &result); // Return false if failed (result may be changed). Otherwise return true and result is populated with correct value
	bool TryOctToUInt64(const AnsiString &str, unsigned long long &result); // Return false if failed (result may be changed). Otherwise return true and result is populated with correct value
	bool TryHexToUInt64(const String &str, unsigned long long &result); // Return false if failed (result may be changed). Otherwise return true and result is populated with correct value
	bool TryHexToUInt64(const AnsiString &str, unsigned long long &result); // Return false if failed (result may be changed). Otherwise return true and result is populated with correct value
	char ByteLoToHexAnsi(const unsigned char value);
	char ByteHiToHexAnsi(const unsigned char value);
	wchar_t ByteLoToHex(const unsigned char value);
	wchar_t ByteHiToHex(const unsigned char value);
	String Hex(const unsigned int value);
	String Hex(const unsigned long long value);
	AnsiString HexAnsi(const unsigned int value);
	AnsiString HexAnsi(const unsigned long long value);
	String HexCompact(const unsigned int value);
	String HexCompact(const unsigned long long value);
	AnsiString HexAnsiCompact(const unsigned int value);
	AnsiString HexAnsiCompact(const unsigned long long value);

	String ToFixed(const float value, const int signs = 6);
	String ToFixed(const double value, const int signs = 6);
	AnsiString ToFixedAnsi(const float value, const int signs = 6);
	AnsiString ToFixedAnsi(const double value, const int signs = 6);

	String PadLeft(const String &str, const wchar_t c, const size_t length);
	AnsiString PadLeft(const AnsiString &str, const char c, const size_t length);
	void PadLeftDirect(String &str, const wchar_t c, const size_t length);
	void PadLeftDirect(AnsiString &str, const char c, const size_t length);
	String PadRight(const String &str, const wchar_t c, const size_t length);
	AnsiString PadRight(const AnsiString &str, const char c, const size_t length);
	void PadRightDirect(String &str, const wchar_t c, const size_t length);
	void PadRightDirect(AnsiString &str, const char c, const size_t length);

#pragma region Inline functions
	inline unsigned char BinToByte(const wchar_t c) // Return 255 if character is not in 0..1 range
	{
		return (c == L'0') ? 0 : ((c == L'1') ? 1 : 255);
	}

	inline unsigned char BinToByte(const char c) // Return 255 if character is not in 0..1 range
	{
		return (c == '0') ? 0 : ((c == '1') ? 1 : 255);
	}

	inline unsigned char OctToByte(const wchar_t c) // Return 255 if character is not in 0..7 range
	{
		return (c >= L'0' && c <= L'7') ? (unsigned char)(c - L'0') : 255;
	}

	inline unsigned char OctToByte(const char c) // Return 255 if character is not in 0..7 range
	{
		return (c >= '0' && c <= '7') ? (unsigned char)(c - '0') : 255;
	}

	inline unsigned char HexToByte(const wchar_t c) // Return 255 if character is not in 0..F range
	{
		return (c >= L'0' && c <= L'9') ? (unsigned char)(c - L'0') : ((c >= L'A' && c <= L'F') ? (unsigned char)(c - L'A' + 10) : ((c >= L'a' && c <= L'f') ? (unsigned char)(c - L'a' + 10) : 255));
	}

	inline unsigned char HexToByte(const char c) // Return 255 if character is not in 0..F range
	{
		return (c >= '0' && c <= '9') ? (unsigned char)(c - '0') : ((c >= 'A' && c <= 'F') ? (unsigned char)(c - 'A' + 10) : ((c >= 'a' && c <= 'f') ? (unsigned char)(c - 'a' + 10) : 255));
	}

	inline bool isUnderscore(const char c)
	{
		return c == L'_';
	}

	inline bool isUnderscore(const wchar_t c)
	{
		return c == L'_';
	}

	inline bool isAz(const char c)
	{
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}

	inline bool isAz(const wchar_t c)
	{
		return (c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z');
	}

	inline bool isDigit(const char c)
	{
		return c >= '0' && c <= '9';
	}

	inline bool isDigit(const wchar_t c)
	{
		return c >= L'0' && c <= L'9';
	}
#pragma endregion
#pragma endregion

#pragma region Formatting
	/**
	Replace first occurrence of substring "search" in string "str" on substring "replace" and return new string
	@param str String where to search
	@param search Searching string
	@param replace String to replace with
	@return String where first occurrence of "search" is replaced with "replace"
	*/
	String Replace(const String &str, const String &search, const String &replace);

	/**
	Replace first occurrence of substring "pair.first" in string "str" on substring "pair.second" and return new string
	@param str String where to search
	@param pair Search and replace parts
	@return String where first occurrence of "pair.first" is replaced with "pair.second"
	*/
	String Replace(const String &str, const StringKeyValue &pair);

	/**
	Replace first occurrence of substring "search" in ANSI string "str" on substring "replace" and return new ANSI string
	@param str String where to search
	@param search Searching string
	@param replace String to replace with
	@return String where first occurrence of "search" is replaced with "replace"
	*/
	AnsiString Replace(const AnsiString &str, const AnsiString &search, const AnsiString &replace);

	/**
	Replace first occurrence of substring "pair.first" in ANSI string "str" on substring "pair.second" and return new ANSI string
	@param str String where to search
	@param pair Search and replace parts
	@return String where first occurrence of "pair.first" is replaced with "pair.second"
	*/
	AnsiString Replace(const AnsiString &str, const AnsiStringKeyValue &pair);

	/**
	Replace first occurrence of substring "search" in string "str" on substring "replace"
	@param[in, out] str String where to search and replace
	@param search Searching string
	@param replace String to replace with
	*/
	void ReplaceDirect(String &str, const String &search, const String &replace);

	/**
	Replace first occurrence of substring "pair.first" in string "str" on substring "pair.second"
	@param[in, out] str String where to search and replace
	@param pair Search and replace parts
	*/
	void ReplaceDirect(String &str, const StringKeyValue &pair);

	/**
	Replace first occurrence of substring "search" in ANSI string "str" on substring "replace"
	@param[in, out] str String where to search and replace
	@param search Searching string
	@param replace String to replace with
	*/
	void ReplaceDirect(AnsiString &str, const AnsiString &search, const AnsiString &replace);

	/**
	Replace first occurrence of substring "pair.first" in ANSI string "str" on substring "pair.second"
	@param[in, out] str String where to search and replace
	@param pair Search and replace parts
	*/
	void ReplaceDirect(AnsiString &str, const AnsiStringKeyValue &pair);

	/**
	Replace all occurrences of substring "search" in string "str" on substring "replace" and return new string
	@param str String where to search
	@param search Searching string
	@param replace String to replace with
	@return String where all occurrences of "search" is replaced with "replace"
	*/
	String ReplaceAll(const String &str, const String &search, const String &replace);

	/**
	Replace all occurrences of substring "pair.first" in string "str" on substring "pair.second" and return new string
	@param str String where to search
	@param pair Search and replace parts
	@return String where all occurrences of "pair.first" is replaced with "pair.second"
	*/
	String ReplaceAll(const String &str, const StringKeyValue &pair);

	/**
	Replace all occurrences of substrings "search" in string "str" on substrings "replace" and return new string
	@param str String where to search
	@param search Searching strings
	@param replace Strings to replace with. The size should be equal to the size of "search"
	@return String where all occurrences of "search" is replaced with "replace"
	*/
	String ReplaceAll(const String &str, const StringArray &search, const StringArray &replace);

	/**
	Replace all occurrences of substrings "pairs[].first" in string "str" on substrings "pairs[].second" and return new string
	@param str String where to search
	@param pairs Search and replace pairs
	@return String where all occurrences of "pairs[].first" is replaced with "pairs[].second"
	*/
	String ReplaceAll(const String &str, const StringKeyValueArray &pairs);

	/**
	Replace all occurrences of substring "search" in ANSI string "str" on substring "replace" and return new ANSI string
	@param str String where to search
	@param search Searching string
	@param replace String to replace with
	@return String where all occurrences of "search" is replaced with "replace"
	*/
	AnsiString ReplaceAll(const AnsiString &str, const AnsiString &search, const AnsiString &replace);

	/**
	Replace all occurrences of substring "pair.first" in ANSI string "str" on substring "pair.second" and return new ANSI string
	@param str String where to search
	@param pair Search and replace pair
	@return String where all occurrences of "pair.first" is replaced with "pair.second"
	*/
	AnsiString ReplaceAll(const AnsiString &str, const AnsiStringKeyValue &pair);

	/**
	Replace all occurrences of substrings "search" in ANSI string "str" on substrings "replace" and return new ANSI string
	@param str String where to search
	@param search Searching strings
	@param replace Strings to replace with. The size should be equal to the size of "search"
	@return String where all occurrences of "search" is replaced with "replace"
	*/
	AnsiString ReplaceAll(const AnsiString &str, const AnsiStringArray &search, const AnsiStringArray &replace);

	/**
	Replace all occurrences of substrings "pairs[].first" in ANSI string "str" on substrings "pairs[].second" and return new ANSI string
	@param str String where to search
	@param pairs Search and replace pairs
	@return String where all occurrences of "pairs[].first" is replaced with "pairs[].second"
	*/
	AnsiString ReplaceAll(const AnsiString &str, const AnsiStringKeyValueArray &pairs);

	/**
	Replace all occurrences of substring "search" in string "str" on substring "replace"
	@param[in, out] str String where to search and replace
	@param search Searching string
	@param replace String to replace with
	*/
	void ReplaceAllDirect(String &str, const String &search, const String &replace);

	/**
	Replace all occurrences of substring "pair.first" in string "str" on substring "pair.second"
	@param[in, out] str String where to search and replace
	@param pair Search and replace pair
	*/
	void ReplaceAllDirect(String &str, const StringKeyValue &pair);

	/**
	Replace all occurrences of substrings "search" in string "str" on substrings "replace"
	@param[in, out] str String where to search and replace
	@param search Searching strings
	@param replace Strings to replace with. The size should be equal to the size of "search"
	*/
	void ReplaceAllDirect(String &str, const StringArray &search, const StringArray &replace);

	/**
	Replace all occurrences of substrings "pairs[].first" in string "str" on substrings "pairs[].second"
	@param[in, out] str String where to search and replace
	@param pairs Search and replace pairs
	*/
	void ReplaceAllDirect(String &str, const StringKeyValueArray &pairs);

	/**
	Replace all occurrences of substring "search" in ANSI string "str" on substring "replace"
	@param[in, out] str String where to search and replace
	@param search Searching string
	@param replace String to replace with
	*/
	void ReplaceAllDirect(AnsiString &str, const AnsiString &search, const AnsiString &replace);

	/**
	Replace all occurrences of substring "pair.first" in ANSI string "str" on substring "pair.second"
	@param[in, out] str String where to search and replace
	@param pair Search and replace pair
	*/
	void ReplaceAllDirect(AnsiString &str, const AnsiStringKeyValue &pair);

	/**
	Replace all occurrences of substrings "search" in ANSI string "str" on substrings "replace"
	@param[in, out] str String where to search and replace
	@param search Searching strings
	@param replace Strings to replace with. The size should be equal to the size of "search"
	*/
	void ReplaceAllDirect(AnsiString &str, const AnsiStringArray &search, const AnsiStringArray &replace);

	/**
	Replace all occurrences of substrings "pairs[].first" in ANSI string "str" on substrings "pairs[].second"
	@param[in, out] str String where to search and replace
	@param pairs Search and replace pairs
	*/
	void ReplaceAllDirect(AnsiString &str, const AnsiStringKeyValueArray &pairs);

	/**
	Remove spaces at the end of string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from end
	*/
	String TrimRight(const String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the end of ANSI string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from end
	*/
	AnsiString TrimRight(const AnsiString &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the end of string
	@param[in, out] str String where to search and remove spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimRightDirect(String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the end of ANSI string
	@param[in, out] str String where to and remove search spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimRightDirect(AnsiString &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the beginning of string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from beginning
	*/
	String TrimLeft(const String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the beginning of ANSI string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from beginning
	*/
	AnsiString TrimLeft(const AnsiString &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the beginning of string
	@param[in, out] str String where to search and remove spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimLeftDirect(String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces at the beginning of ANSI string
	@param[in, out] str String where to search and remove spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimLeftDirect(AnsiString &str, const std::locale &locale = std::locale());

	/**
	Remove spaces both at the beginning and at the end of string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from beginning and end
	*/
	String Trim(const String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces both at the beginning and at the end of ANSI string and return new one
	@param str String where to search spaces
	@param local Locale used for search. Default is current locale
	@return String with removed spaces from beginning and end
	*/
	AnsiString Trim(const AnsiString &str, const std::locale &locale = std::locale());

	/**
	Remove spaces both at the beginning and at the end of string
	@param[in, out] str String where to search and remove spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimDirect(String &str, const std::locale &locale = std::locale());

	/**
	Remove spaces both at the beginning and at the end of ANSI string
	@param[in, out] str String where to search and remove spaces
	@param local Locale used for search. Default is current locale
	*/
	void TrimDirect(AnsiString &str, const std::locale &locale = std::locale());

#ifndef __GNUC__
	/**
	Format datetime to specified format and return as string
	@param format Format in which datetime should be output
	@param  datetime Datetime structure
	@param locale Locale used for formatting. Default is current one
	@return Formatted string datetime representation

	@para Possible formats:
		- \%a Abbreviated weekday name
		- \%A Full weekday name
		- \%b Abbreviated month name
		- \%B Full month name
		- \%c Date and time representation appropriate for locale
		- \%d Day of month as decimal number (01 - 31)
		- \%H Hour in 24-hour format (00 - 23)
		- \%I Hour in 12-hour format (01 - 12)
		- \%j Day of year as decimal number (001 - 366)
		- \%m Month as decimal number (01 - 12)
		- \%M Minute as decimal number (00 - 59)
		- \%p Current locale's A.M./P.M. indicator for 12-hour clock
		- \%S Second as decimal number (00 - 59)
		- \%U Week of year as decimal number, with Sunday as first day of week (00 - 53)
		- \%w Weekday as decimal number (0 - 6; Sunday is 0)
		- \%W Week of year as decimal number, with Monday as first day of week (00 - 53)
		- \%x Date representation for current locale
		- \%X Time representation for current locale
		- \%y Year without century, as decimal number (00 - 99)
		- \%Y Year with century, as decimal number
		- \%z, %Z Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown
		- \%\% Percent sign
	*/
	String FormatDateTime(const String &format, const tm datetime, const std::locale &locale = std::locale());

	/**
	Format datetime to specified format and return as ansi string
	@param format Format in which datetime should be output
	@param  datetime Datetime structure
	@param locale Locale used for formatting. Default is current one
	@return Formatted string datetime representation

	@para Possible formats:
	- \%a Abbreviated weekday name
	- \%A Full weekday name
	- \%b Abbreviated month name
	- \%B Full month name
	- \%c Date and time representation appropriate for locale
	- \%d Day of month as decimal number (01 - 31)
	- \%H Hour in 24-hour format (00 - 23)
	- \%I Hour in 12-hour format (01 - 12)
	- \%j Day of year as decimal number (001 - 366)
	- \%m Month as decimal number (01 - 12)
	- \%M Minute as decimal number (00 - 59)
	- \%p Current locale's A.M./P.M. indicator for 12-hour clock
	- \%S Second as decimal number (00 - 59)
	- \%U Week of year as decimal number, with Sunday as first day of week (00 - 53)
	- \%w Weekday as decimal number (0 - 6; Sunday is 0)
	- \%W Week of year as decimal number, with Monday as first day of week (00 - 53)
	- \%x Date representation for current locale
	- \%X Time representation for current locale
	- \%y Year without century, as decimal number (00 - 99)
	- \%Y Year with century, as decimal number
	- \%z, %Z Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown
	- \%\% Percent sign
	*/
	AnsiString FormatDateTime(const AnsiString &format, const tm datetime, const std::locale &locale = std::locale());

	/**
	Parse string for specified datetime format and return true if successfully parsed or false otherwise
	@param str String for parsing
	@param[out] out Datetime structure where to store result
	@param format Expected format. Default is "%Y-%m-%d %H:%M:%S"
	@param locale Locale used for parsing. Default is current one
	@return True is successfully parsed, otherwise - false

	@para Possible formats:
	- \%a Abbreviated weekday name
	- \%A Full weekday name
	- \%b Abbreviated month name
	- \%B Full month name
	- \%c Date and time representation appropriate for locale
	- \%d Day of month as decimal number (01 - 31)
	- \%H Hour in 24-hour format (00 - 23)
	- \%I Hour in 12-hour format (01 - 12)
	- \%j Day of year as decimal number (001 - 366)
	- \%m Month as decimal number (01 - 12)
	- \%M Minute as decimal number (00 - 59)
	- \%p Current locale's A.M./P.M. indicator for 12-hour clock
	- \%S Second as decimal number (00 - 59)
	- \%U Week of year as decimal number, with Sunday as first day of week (00 - 53)
	- \%w Weekday as decimal number (0 - 6; Sunday is 0)
	- \%W Week of year as decimal number, with Monday as first day of week (00 - 53)
	- \%x Date representation for current locale
	- \%X Time representation for current locale
	- \%y Year without century, as decimal number (00 - 99)
	- \%Y Year with century, as decimal number
	- \%z, %Z Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown
	- \%\% Percent sign
	*/
	bool ParseDateTime(const String &str, tm &out, const String &format = L"%Y-%m-%d %H:%M:%S", const std::locale &locale = std::locale());

	/**
	Parse ansi string for specified datetime format and return true if successfully parsed or false otherwise
	@param str String for parsing
	@param[out] out Datetime structure where to store result
	@param format Expected format. Default is "%Y-%m-%d %H:%M:%S"
	@param locale Locale used for parsing. Default is current one
	@return True is successfully parsed, otherwise - false

	@para Possible formats:
	- \%a Abbreviated weekday name
	- \%A Full weekday name
	- \%b Abbreviated month name
	- \%B Full month name
	- \%c Date and time representation appropriate for locale
	- \%d Day of month as decimal number (01 - 31)
	- \%H Hour in 24-hour format (00 - 23)
	- \%I Hour in 12-hour format (01 - 12)
	- \%j Day of year as decimal number (001 - 366)
	- \%m Month as decimal number (01 - 12)
	- \%M Minute as decimal number (00 - 59)
	- \%p Current locale's A.M./P.M. indicator for 12-hour clock
	- \%S Second as decimal number (00 - 59)
	- \%U Week of year as decimal number, with Sunday as first day of week (00 - 53)
	- \%w Weekday as decimal number (0 - 6; Sunday is 0)
	- \%W Week of year as decimal number, with Monday as first day of week (00 - 53)
	- \%x Date representation for current locale
	- \%X Time representation for current locale
	- \%y Year without century, as decimal number (00 - 99)
	- \%Y Year with century, as decimal number
	- \%z, %Z Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown
	- \%\% Percent sign
	*/
	bool ParseDateTime(const AnsiString &str, tm &out, const AnsiString &format = "%Y-%m-%d %H:%M:%S", const std::locale &locale = std::locale());
#endif

	/**
	Explode string by specified delimiter and put parts into specified output
	@param str String to exploding
	@param delimiter Exploding delimiter
	@param[out] out Vector of string parts
	@param remove_empty Indicates if empty parts should be removed. Default is true
	*/
	void Explode(const String &str, const String &delimiter, StringArray &out, const bool remove_empty = true);

	/**
	Explode ansi string by specified delimiter and put parts into specified output
	@param str String to exploding
	@param delimiter Exploding delimiter
	@param[out] out Vector of string parts
	@param remove_empty Indicates if empty parts should be removed. Default is true
	*/
	void Explode(const AnsiString &str, const AnsiString &delimiter, AnsiStringArray &out, const bool remove_empty = true);

	/**
	Explode string by specified delimiter and return result(less efficient than version without result due to twice copying)
	@param str String to exploding
	@param delimiter Exploding delimiter
	@param remove_empty Indicates if empty parts should be removed. Default is true
	@return Vector of string parts
	*/
	StringArray Explode(const String &str, const String &delimiter, const bool remove_empty = true);

	/**
	Explode ansi string by specified delimiter and return result(less efficient than version without result due to twice copying)
	@param str String to exploding
	@param delimiter Exploding delimiter
	@param remove_empty Indicates if empty parts should be removed. Default is true
	@return Vector of string parts
	*/
	AnsiStringArray Explode(const AnsiString &str, const AnsiString &delimiter, const bool remove_empty = true);

	/**
	Convert string to upper case and return result
	@param str Source string
	@param locale Locale used for conversion. Default is current one
	@return Uppercase representation of source string
	*/
	String ToUpper(const String &str, const std::locale &locale = std::locale());

	/**
	Convert character to upper case and return result
	@param chr Source character
	@param locale Locale used for conversion. Default is current one
	@return Uppercase representation of source character
	*/
	wchar_t ToUpper(const wchar_t chr, const std::locale &locale = std::locale());

	/**
	Convert ansi string to upper case and return result
	@param str Source string
	@param locale Locale used for conversion. Default is current one
	@return Uppercase representation of source string
	*/
	AnsiString ToUpper(const AnsiString &str, const std::locale &locale = std::locale());

	/**
	Convert ansi character to upper case and return result
	@param chr Source character
	@param locale Locale used for conversion. Default is current one
	@return Uppercase representation of source character
	*/
	char ToUpper(const char chr, const std::locale &locale = std::locale());

	/**
	Direct convert string to upper case
	@param[in, out] str String to be converted
	@param locale Locale used for conversion. Default is current one
	*/
	void ToUpperDirect(String &str, const std::locale &locale = std::locale());

	/**
	Direct convert ansi string to upper case
	@param[in, out] str String to be converted
	@param locale Locale used for conversion. Default is current one
	*/
	void ToUpperDirect(AnsiString &str, const std::locale &locale = std::locale());

	/**
	Convert string to lower case and return result
	@param str Source string
	@param locale Locale used for conversion. Default is current one
	@return Lowercase representation of source string
	*/
	String ToLower(const String &str, const std::locale &locale = std::locale());

	/**
	Convert character to lower case and return result
	@param chr Source character
	@param locale Locale used for conversion. Default is current one
	@return Lowercase representation of source character
	*/
	wchar_t ToLower(const wchar_t chr, const std::locale &locale = std::locale());

	/**
	Convert ansi string to lower case and return result
	@param str Source string
	@param locale Locale used for conversion. Default is current one
	@return Lowercase representation of source string
	*/
	AnsiString ToLower(const AnsiString &str, const std::locale &locale = std::locale());

	/**
	Convert ansi character to lower case and return result
	@param chr Source character
	@param locale Locale used for conversion. Default is current one
	@return Lowercase representation of source character
	*/
	char ToLower(const char chr, const std::locale &locale = std::locale());

	/**
	Direct convert string to lower case
	@param[in, out] str String to be converted
	@param locale Locale used for conversion. Default is current one
	*/
	void ToLowerDirect(String &str, const std::locale &locale = std::locale());

	/**
	Direct convert ansi string to lower case
	@param[in, out] str String to be converted
	@param locale Locale used for conversion. Default is current one
	*/
	void ToLowerDirect(AnsiString &str, const std::locale &locale = std::locale());

	/**
	Concatenate array of ANSI string into a single ANSI string with each line separated by specified 'glue' string
	@param glue String to be inserted between lines
	@param lines Array of strings to be concatenated
	*/
	AnsiString Implode(const AnsiString &glue, const AnsiStringArray &lines);

	/**
	Concatenate array of unicode string into a single unicode string with each line separated by specified 'glue' string
	@param glue String to be inserted between lines
	@param lines Array of strings to be concatenated
	*/
	String Implode(const String &glue, const StringArray &lines);
#pragma endregion

#pragma region Searching
	/**
	Return index of starting word characted next after start position
	@param str String where to search
	@param start Index from where start to search
	@param with_punch If true, punctuation characters are interpreted as words as well
	@param locale Used locale
	@return Word start position or str length
	*/
	size_t SearchNextWord(const String &str, const size_t start, const bool with_punct = false, const std::locale &locale = std::locale());

	/**
	Return index of starting word characted prev to start position
	@param str String where to search
	@param start Index from where start to search
	@param with_punch If true, punctuation characters are interpreted as words as well
	@param locale Used locale
	@return Word start position or 0
	*/
	size_t SearchPrevWord(const String &str, const size_t start, const bool with_punct = false, const std::locale &locale = std::locale());

	/**
	Return index of next word beginning after the specified position
	@param str String where to search
	@param start Index from where to search
	@param locale Used locale
	@return Word start position if found
	@return String length if no word start found till the string end
	@return String::npos in case of invalid parameters
	*/
	size_t SearchWordStartForward(const String &str, const size_t start, const std::locale &locale = std::locale());

	/**
	Return index of next word ending after the specified position
	@param str String where to search
	@param start Index from where to search
	@param locale Used locale
	@return Word end position if found
	@return String length if no word end found till the string end
	@return String::npos in case of invalid parameters
	*/
	size_t SearchWordEndForward(const String &str, const size_t start, const std::locale &locale = std::locale());

	/**
	Return index of previous word beginning before the specified position
	@param str String where to search
	@param start Index from where to search
	@param locale Used locale
	@return Word start position if found
	@return Zero if no word start found till the string start
	@return String::npos in case of invalid parameters
	*/
	size_t SearchWordStartBackward(const String &str, const size_t start, const std::locale &locale = std::locale());

	/**
	Return index of previous word ending before the specified position
	@param str String where to search
	@param start Index from where to search
	@param locale Used locale
	@return Word end position if found
	@return Zero if no word end found till the string start
	@return String::npos in case of invalid parameters
	*/
	size_t SearchWordEndBackward(const String &str, const size_t start, const std::locale &locale = std::locale());
#pragma endregion

#pragma region Checking
	bool isCppIdentifier(const AnsiString &str);
	bool isCppIdentifier(const String &str);
#pragma endregion
}