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
	String AsSourceCode(const BoolArray &a)
	{
		String result{ L"BoolArray{ " };
		for (size_t i = 0; i < a.size(); i++)
			if (i > 0)
				result += L", " + ToString(a[i]);
			else
				result += ToString(a[i]);
		if (a.size() > 0)
			return result + L" }";
		return result + L"}";
	}

	String ToString(const BoolArray &value)
	{
		if (value.size() == 0)
			return L"{}";
		if (value.size() == 1)
			return L"{ " + ToString(value[0]) + L" }";
		return L"{ " + ToString(value[0]) + L", ... }";
	}

	Variant ToVariant(const BoolArray &value)
	{
		Variant result;
		for (auto v : value)
			result.push_back(ToVariant(v));
		return result;
	}

	void FromVariant(const Variant &value, BoolArray &dest)
	{
		dest.clear();
		if (value.getType() == Variant::VariantType::Array)
			for (auto v : value)
			{
				bool r;
				FromVariant(v.second, r);
				dest.push_back(r);
			}
	}
}