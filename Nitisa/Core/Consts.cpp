// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	// Default settings
	const Mat4f Identity{ 1, 0 };
	const Point DesignDPI{ 96, 96 };

	// Empty constants
	const String EmptyString;
	const AnsiString EmptyAnsiString;
	const UTF8String EmptyUTF8String;
	const StringArray EmptyStringArray;
	const AnsiStringArray EmptyAnsiStringArray;
	const UTF8StringArray EmptyUTF8StringArray;
	const StringKeyValue EmptyStringKeyValue;
	const AnsiStringKeyValue EmptyAnsiStringKeyValue;
	const UTF8StringKeyValue EmptyUTF8StringKeyValue;
	const StringKeyValueArray EmptyStringKeyValueArray;
	const AnsiStringKeyValueArray EmptyAnsiStringKeyValueArray;
	const UTF8StringKeyValueArray EmptyUTF8StringKeyValueArray;

	// Translate categories
	const String TranslateCategoryColors{ L"Colors" };
	const String TranslateCategoryKeys{ L"Keys" };
	const String TranslateCategoryCalendar{ L"Calendar" };

	// Escape sequences
	const StringKeyValueArray EncodeEscape{
		StringKeyValue{ L"\\", L"\\\\" },
		StringKeyValue{ L"\n", L"\\n" },
		StringKeyValue{ L"\t", L"\\t" },
		StringKeyValue{ L"\a", L"\\a" },
		StringKeyValue{ L"\b", L"\\b" },
		StringKeyValue{ L"\f", L"\\f" },
		StringKeyValue{ L"\r", L"\\n" },
		StringKeyValue{ L"\v", L"\\v" } };
	const StringKeyValueArray DecodeEscape{
		StringKeyValue{ L"\\", L"\\" },
		StringKeyValue{ L"n", L"\n" },
		StringKeyValue{ L"t", L"\t" },
		StringKeyValue{ L"a", L"\a" },
		StringKeyValue{ L"b", L"\b" },
		StringKeyValue{ L"f", L"\f" },
		StringKeyValue{ L"r", L"\n" },
		StringKeyValue{ L"v", L"\v" } };

	// Months
	namespace months
	{
		const String January{ L"January" };
		const String February{ L"February" };
		const String March{ L"March" };
		const String April{ L"April" };
		const String May{ L"May" };
		const String June{ L"June" };
		const String July{ L"July" };
		const String August{ L"August" };
		const String September{ L"September" };
		const String October{ L"October" };
		const String November{ L"November" };
		const String December{ L"December" };
		const StringArray Names{ January, February, March, April, May, June, July, August, September, October, November, December };
		const String Jan{ L"Jan" };
		const String Feb{ L"Feb" };
		const String Mar{ L"Mar" };
		const String Apr{ L"Apr" };
		const String Jun{ L"Jun" };
		const String Jul{ L"Jul" };
		const String Aug{ L"Aug" };
		const String Sep{ L"Sep" };
		const String Oct{ L"Oct" };
		const String Nov{ L"Nov" };
		const String Dec{ L"Dec" };
		const StringArray ShortNames{ Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
	}

	// Days of week
	namespace days
	{
		const String Monday{ L"Monday" };
		const String Tuesday{ L"Tuesday" };
		const String Wednesday{ L"Wednesday" };
		const String Thursday{ L"Thursday" };
		const String Friday{ L"Friday" };
		const String Saturday{ L"Saturday" };
		const String Sunday{ L"Sunday" };
		const StringArray Names{ Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
		const String Mo{ L"Mo" };
		const String Tu{ L"Tu" };
		const String We{ L"We" };
		const String Th{ L"Th" };
		const String Fr{ L"Fr" };
		const String Sa{ L"Sa" };
		const String Su{ L"Su" };
		const StringArray ShortNames{ Mo, Tu, We, Th, Fr, Sa, Su };
		const String Today{ L"Today" };
	}
}