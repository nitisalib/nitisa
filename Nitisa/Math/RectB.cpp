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
#pragma region RectB
	bool RectB::operator[](const int index) const
	{
		return Data[index];
	}

	bool &RectB::operator[](const int index)
	{
		return Data[index];
	}
#pragma endregion

#pragma region Operators
	bool operator==(const RectB &a, const RectB &b)
	{
		return a.Left == b.Left && a.Top == b.Top && a.Right == b.Right && a.Bottom == b.Bottom;
	}

	bool operator!=(const RectB &a, const RectB &b)
	{
		return a.Left != b.Left || a.Top != b.Top || a.Right != b.Right || a.Bottom != b.Bottom;
	}

	std::wostream &operator<<(std::wostream &stream, const RectB &a)
	{
		stream << L"{ " << (a.Left ? L"true" : L"false") << L", " << (a.Top ? L"true" : L"false") << L", " << (a.Right ? L"true" : L"false") << L", " << (a.Bottom ? L"true" : L"false") << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	String AsSourceCode(const RectB &a)
	{
		return L"RectB{ " + ToString(a.Left) + L", " + ToString(a.Top) + L", " + ToString(a.Right) + L", " + ToString(a.Bottom) + L" }";
	}

	String ToString(const RectB &value)
	{
		return String(value.Left ? L"true" : L"false") + L", " + String(value.Top ? L"true" : L"false") + L", " + String(value.Right ? L"true" : L"false") + L", " + String(value.Bottom ? L"true" : L"false");
	}

	Variant ToVariant(const RectB &value)
	{
		Variant result;
		result.push_back((Variant)value.Left);
		result.push_back((Variant)value.Top);
		result.push_back((Variant)value.Right);
		result.push_back((Variant)value.Bottom);
		return result;
	}

	void FromVariant(const Variant &value, RectB &dest)
	{
		dest = RectB{ (bool)value.get(0), (bool)value.get(1), (bool)value.get(2), (bool)value.get(3) };
	}
#pragma endregion
}