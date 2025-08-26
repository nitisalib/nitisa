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
	String AsSourceCode(const Mat4f &a)
	{
		return L"Mat4f{ " + AsSourceCode(a.Rows[0]) + L", " + AsSourceCode(a.Rows[1]) + L", " + AsSourceCode(a.Rows[2]) + L", " + AsSourceCode(a.Rows[3]) + L" }";
	}

	String ToString(const Mat4f &value)
	{
		return L"[Matrix]";
	}

	Variant ToVariant(const Mat4f &value)
	{
		Variant result;
		for (unsigned char y = 0; y < 4; y++)
		{
			Variant row;
			row.push_back((Variant)value.Rows[y].X);
			row.push_back((Variant)value.Rows[y].Y);
			row.push_back((Variant)value.Rows[y].Z);
			row.push_back((Variant)value.Rows[y].W);
			result.push_back(row);
		}
		return result;
	}

	void FromVariant(const Variant &value, Mat4f &dest)
	{
		for (unsigned char y = 0; y < 4; y++)
		{
			dest.Rows[y].X = (float)value.get(y).get(0);
			dest.Rows[y].Y = (float)value.get(y).get(1);
			dest.Rows[y].Z = (float)value.get(y).get(2);
			dest.Rows[y].W = (float)value.get(y).get(3);
		}
	}
}