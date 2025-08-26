// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Operators
	std::wostream &operator<<(std::wostream &stream, const BorderColor &a)
	{
		stream << L"{ " << a.Left << L", " << a.Top << L", " << a.Right << L", " << a.Bottom << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	String AsSourceCode(const BorderColor &a)
	{
		return L"BorderColor{ " + AsSourceCode(a.Left) + L", " + AsSourceCode(a.Top) + L", " + AsSourceCode(a.Right) + L", " + AsSourceCode(a.Bottom) + L" }";
	}

	String ToString(const BorderColor &value)
	{
		return L"{ " + ToString(value.Left) + L" }, " + L"{ " + ToString(value.Top) + L" }, " + L"{ " + ToString(value.Right) + L" }, " + L"{ " + ToString(value.Bottom) + L" }";
	}

	Variant ToVariant(const BorderColor &value)
	{
		Variant result;
		result.push_back(ToVariant(value.Left));
		result.push_back(ToVariant(value.Top));
		result.push_back(ToVariant(value.Right));
		result.push_back(ToVariant(value.Bottom));
		return result;
	}

	void FromVariant(const Variant &value, BorderColor &dest)
	{
		FromVariant(value.get(0), dest.Left);
		FromVariant(value.get(1), dest.Top);
		FromVariant(value.get(2), dest.Right);
		FromVariant(value.get(3), dest.Bottom);
	}
#pragma endregion
}