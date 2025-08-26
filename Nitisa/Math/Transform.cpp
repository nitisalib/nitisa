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
	std::wostream &operator<<(std::wostream &stream, const Transform &a)
	{
		stream << L"{ "
			<< AsSourceCode(a.Tx) << L", " << AsSourceCode(a.Ty) << L", " << AsSourceCode(a.Tz) << L", "
			<< AsSourceCode(a.Sx) << L", " << AsSourceCode(a.Sy) << L", " << AsSourceCode(a.Sz) << L", "
			<< AsSourceCode(a.Rx) << L", " << AsSourceCode(a.Ry) << L", " << AsSourceCode(a.Rz) << L", "
			<< RotateOrderToString(a.RotateOrder) << L", " << TransformOrderToString(a.TransformOrder) << L" }";
		return stream;
	}

	bool IsEqual(const Transform &a, const Transform &b, const float tolerance)
	{
		return
			ntl::IsEqual<float>(a.Translation, b.Translation, tolerance) &&
			ntl::IsEqual<float>(a.Scaling, b.Scaling, tolerance) &&
			ntl::IsEqual<float>(a.Rotation, b.Rotation, tolerance) &&
			a.RotateOrder == b.RotateOrder && a.TransformOrder == b.TransformOrder;
	}

	bool IsNotEqual(const Transform &a, const Transform &b, const float tolerance)
	{
		return
			ntl::IsNotEqual<float>(a.Translation, b.Translation, tolerance) ||
			ntl::IsNotEqual<float>(a.Scaling, b.Scaling, tolerance) ||
			ntl::IsNotEqual<float>(a.Rotation, b.Rotation, tolerance) ||
			a.RotateOrder != b.RotateOrder || a.TransformOrder != b.TransformOrder;
	}

	bool Equals(const Transform &a, const Transform &b, const float relative_tolerance)
	{
		return
			ntl::Equals<float>(a.Translation, b.Translation, relative_tolerance) &&
			ntl::Equals<float>(a.Scaling, b.Scaling, relative_tolerance) &&
			ntl::Equals<float>(a.Rotation, b.Rotation, relative_tolerance) &&
			a.RotateOrder == b.RotateOrder && a.TransformOrder == b.TransformOrder;
	}

	bool NotEquals(const Transform &a, const Transform &b, const float relative_tolerance)
	{
		return
			ntl::NotEquals<float>(a.Translation, b.Translation, relative_tolerance) ||
			ntl::NotEquals<float>(a.Scaling, b.Scaling, relative_tolerance) ||
			ntl::NotEquals<float>(a.Rotation, b.Rotation, relative_tolerance) ||
			a.RotateOrder != b.RotateOrder || a.TransformOrder != b.TransformOrder;
	}

	String ToString(const Transform &value)
	{
		return L"Tx: " + ToStringCompact(value.Tx) + L", Ty: " + ToStringCompact(value.Ty) + L", Rz: " + ToStringCompact(value.Rz);
	}

	Variant ToVariant(const Transform &value)
	{
		Variant result;
		result[L"Tx"] = value.Tx;
		result[L"Ty"] = value.Ty;
		result[L"Tz"] = value.Tz;
		result[L"Sx"] = value.Sx;
		result[L"Sy"] = value.Sy;
		result[L"Sz"] = value.Sz;
		result[L"Rx"] = value.Rx;
		result[L"Ry"] = value.Ry;
		result[L"Rz"] = value.Rz;
		result[L"RO"] = RotateOrderToString(value.RotateOrder);
		result[L"TO"] = TransformOrderToString(value.TransformOrder);
		return result;
	}

	void FromVariant(const Variant &value, Transform &dest)
	{
		dest.Tx = (float)value.get(L"Tx");
		dest.Ty = (float)value.get(L"Ty");
		dest.Tz = (float)value.get(L"Tz");
		dest.Sx = (float)value.get(L"Sx");
		dest.Sy = (float)value.get(L"Sy");
		dest.Sz = (float)value.get(L"Sz");
		dest.Rx = (float)value.get(L"Rx");
		dest.Ry = (float)value.get(L"Ry");
		dest.Rz = (float)value.get(L"Rz");
		dest.RotateOrder = StringToRotateOrder((String)value.get(L"RO"));
		dest.TransformOrder = StringToTransformOrder((String)value.get(L"TO"));
	}

	String AsSourceCode(const Transform &a)
	{
		return L"Transform{ "
			+ AsSourceCode(a.Tx) + L", " + AsSourceCode(a.Ty) + L", " + AsSourceCode(a.Tz) + L", "
			+ AsSourceCode(a.Sx) + L", " + AsSourceCode(a.Sy) + L", " + AsSourceCode(a.Sz) + L", "
			+ AsSourceCode(a.Rx) + L", " + AsSourceCode(a.Ry) + L", " + AsSourceCode(a.Rz) + L", "
			+ RotateOrderToString(a.RotateOrder) + L", " + TransformOrderToString(a.TransformOrder) + L" }";
	}
}