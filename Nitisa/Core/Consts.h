// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/Mat4f.h"
#include "../Math/Point.h"
#include "Strings.h"

namespace nitisa
{
	// Default settings
	extern const Mat4f Identity; // Identity matrix
	extern const Point DesignDPI; // Default DPI being used to design widgets
	constexpr const float ScrollInterval{ 0.1f }; // Default scroll interval
	constexpr const int MaxPolygonPoints{ 3000 }; // Maximum number of points in polygon which renderers will draw(some renderers may use greater limits).
	constexpr const unsigned int OutlineMask{ 0b00110011001100110011001100110011 }; // Default mask used to outline some widgets in Form Builder initially invisible(there is no content to draw)
	constexpr const size_t npos{ (size_t)-1 }; // No-index value

	// Empty constants
	extern const String EmptyString;
	extern const AnsiString EmptyAnsiString;
	extern const UTF8String EmptyUTF8String;
	extern const StringArray EmptyStringArray;
	extern const AnsiStringArray EmptyAnsiStringArray;
	extern const UTF8StringArray EmptyUTF8StringArray;
	extern const StringKeyValue EmptyStringKeyValue;
	extern const AnsiStringKeyValue EmptyAnsiStringKeyValue;
	extern const UTF8StringKeyValue EmptyUTF8StringKeyValue;
	extern const StringKeyValueArray EmptyStringKeyValueArray;
	extern const AnsiStringKeyValueArray EmptyAnsiStringKeyValueArray;
	extern const UTF8StringKeyValueArray EmptyUTF8StringKeyValueArray;

	// Translate categories
	extern const String TranslateCategoryColors; // Defined as L"Colors"
	extern const String TranslateCategoryKeys; // Defined as L"Keys"
	extern const String TranslateCategoryCalendar; // Defined as L"Calendar"

	// Escape sequences
	extern const StringKeyValueArray EncodeEscape;
	extern const StringKeyValueArray DecodeEscape;

	// Months
	namespace months
	{
		extern const String January; // Defined as L"January"
		extern const String February; // Defined as L"February"
		extern const String March; // Defined as L"March"
		extern const String April; // Defined as L"April"
		extern const String May; // Defined as L"May"
		extern const String June; // Defined as L"June"
		extern const String July; // Defined as L"July"
		extern const String August; // Defined as L"August"
		extern const String September; // Defined as L"September"
		extern const String October; // Defined as L"October"
		extern const String November; // Defined as L"November"
		extern const String December; // Defined as L"December"
		extern const StringArray Names; // List of month names
		extern const String Jan; // Defined as L"Jan"
		extern const String Feb; // Defined as L"Feb"
		extern const String Mar; // Defined as L"Mar"
		extern const String Apr; // Defined as L"Apr"
		extern const String Jun; // Defined as L"Jun"
		extern const String Jul; // Defined as L"Jul"
		extern const String Aug; // Defined as L"Aug"
		extern const String Sep; // Defined as L"Sep"
		extern const String Oct; // Defined as L"Oct"
		extern const String Nov; // Defined as L"Nov"
		extern const String Dec; // Defined as L"Dec"
		extern const StringArray ShortNames; // List of month short names
	}

	// Days of week
	namespace days
	{
		extern const String Monday; // Defined as L"Monday"
		extern const String Tuesday; // Defined as L"Tuesday"
		extern const String Wednesday; // Defined as L"Wednesday"
		extern const String Thursday; // Defined as L"Thursday"
		extern const String Friday; // Defined as L"Friday"
		extern const String Saturday; // Defined as L"Saturday"
		extern const String Sunday; // Defined as L"Sunday"
		extern const StringArray Names; // List of day names
		extern const String Mo; // Defined as L"Mo"
		extern const String Tu; // Defined as L"Tu"
		extern const String We; // Defined as L"We"
		extern const String Th; // Defined as L"Th"
		extern const String Fr; // Defined as L"Fr"
		extern const String Sa; // Defined as L"Sa"
		extern const String Su; // Defined as L"Su"
		extern const StringArray ShortNames; // List of day short names
		extern const String Today; // Defined as L"Today"
	}
}