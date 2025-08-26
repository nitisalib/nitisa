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
	bool IsEqual(const FloatArray &a, const FloatArray &b, const float tolerance)
	{
		if (a.size() == b.size())
		{
			for (size_t i = 0; i < a.size(); i++)
				if (ntl::IsNotEqual<float>(a[i], b[i], tolerance))
					return false;
			return true;
		}
		return false;
	}

	bool IsNotEqual(const FloatArray &a, const FloatArray &b, const float tolerance)
	{
		if (a.size() == b.size())
		{
			for (size_t i = 0; i < a.size(); i++)
				if (ntl::IsNotEqual<float>(a[i], b[i], tolerance))
					return true;
			return false;
		}
		return true;
	}

	String AsSourceCode(const FloatArray &a)
	{
		String result{ L"FloatArray{ " };
		for (size_t i = 0; i < a.size(); i++)
			if (i > 0)
				result += L", " + AsSourceCode(a[i]);
			else
				result += AsSourceCode(a[i]);
		if (a.size() > 0)
			return result + L" }";
		return result + L"}";
	}

	String ToString(const FloatArray &value)
	{
		if (value.size() == 0)
			return L"{}";
		if (value.size() == 1)
			return L"{ " + ToString(value[0]) + L" }";
		return L"{ " + ToString(value[0]) + L", ... }";
	}

	Variant ToVariant(const FloatArray &value)
	{
		Variant result;
		for (auto v : value)
			result.push_back(ToVariant(v));
		return result;
	}

	void FromVariant(const Variant &value, FloatArray &dest)
	{
		dest.clear();
		if (value.getType() == Variant::VariantType::Array)
			for (auto v : value)
			{
				float r;
				FromVariant(v.second, r);
				dest.push_back(r);
			}
	}
}