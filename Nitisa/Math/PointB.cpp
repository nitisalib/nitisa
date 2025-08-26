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
#pragma region PointB
	bool PointB::operator[](const int index) const
	{
		return Data[index];
	}

	bool &PointB::operator[](const int index)
	{
		return Data[index];
	}
#pragma endregion

#pragma region Operators
	bool operator==(const PointB &a, const PointB &b)
	{
		return a.X == b.X && a.Y == b.Y;
	}

	bool operator!=(const PointB &a, const PointB &b)
	{
		return a.X != b.X || a.Y != b.Y;
	}

	std::wostream &operator<<(std::wostream &stream, const PointB &a)
	{
		stream << L"{ " << (a.X ? L"true" : L"false") << L", " << (a.Y ? L"true" : L"false") << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	String AsSourceCode(const PointB &a)
	{
		return L"PointB{ " + ToString(a.X) + L", " + ToString(a.Y) + L" }";
	}

	String ToString(const PointB &value)
	{
		return String(value.X ? L"true" : L"false") + L", " + String(value.Y ? L"true" : L"false");
	}

	Variant ToVariant(const PointB &value)
	{
		Variant result;
		result.push_back((Variant)value.X);
		result.push_back((Variant)value.Y);
		return result;
	}

	void FromVariant(const Variant &value, PointB &dest)
	{
		dest = PointB{ (bool)value.get(0), (bool)value.get(1) };
	}
#pragma endregion
}