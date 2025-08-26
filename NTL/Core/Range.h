// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Utils.h"

namespace ntl
{
	template<class TYPE>
	union TRange
	{
		struct // As interval
		{
			TYPE From;
			TYPE Till;
		};
		struct // As limits
		{
			TYPE Minimum;
			TYPE Maximum;
		};
		struct // As segment
		{
			TYPE A;
			TYPE B;
		};
	};

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, bool> operator==(const TRange<TYPE> &a, const TRange<TYPE> &b) // Check whether ranges are equal. Can be used for non-float data types only
	{
		return a.From == b.From && a.Till == b.Till;
	}

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, bool> operator!=(const TRange<TYPE> &a, const TRange<TYPE> &b) // Check whether ranges aren't equal. Can be used for non-float data types only
	{
		return a.From != b.From || a.Till != b.Till;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TRange<TYPE> &a, const TRange<TYPE> &b) // Compare whether ranges are equal
	{
		return a.From == b.From && a.Till == b.Till;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TRange<TYPE> &a, const TRange<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether ranges are equal
	{
		return IsEqual<TYPE>(a.From, b.From, tolerance) && IsEqual<TYPE>(a.Till, b.Till, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TRange<TYPE> &a, const TRange<TYPE> &b) // Compare whether ranges aren't equal
	{
		return a.From != b.From || a.Till != b.Till;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TRange<TYPE> &a, const TRange<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether ranges aren't equal
	{
		return IsNotEqual<TYPE>(a.From, b.From, tolerance) || IsNotEqual<TYPE>(a.Till, b.Till, tolerance);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TRange<TYPE> &a, const TRange<TYPE> &b, const FLOAT relative_tolerance) // Check whether ranges are equal using relative comparison
	{
		return Equals<TYPE, FLOAT>(a.From, b.From, relative_tolerance) && Equals<TYPE, FLOAT>(a.Till, b.Till, relative_tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TRange<TYPE> &a, const TRange<TYPE> &b, const TYPE relative_tolerance) // Check whether ranges are equal using relative comparison
	{
		return Equals<TYPE>(a.From, b.From, relative_tolerance) && Equals<TYPE>(a.Till, b.Till, relative_tolerance);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TRange<TYPE> &a, const TRange<TYPE> &b, const FLOAT relative_tolerance) // Check whether ranges aren't equal using relative comparison
	{
		return NotEquals<TYPE, FLOAT>(a.From, b.From, relative_tolerance) || NotEquals<TYPE, FLOAT>(a.Till, b.Till, relative_tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TRange<TYPE> &a, const TRange<TYPE> &b, const TYPE relative_tolerance) // Check whether ranges aren't equal using relative comparison
	{
		return NotEquals<TYPE>(a.From, b.From, relative_tolerance) || NotEquals<TYPE>(a.Till, b.Till, relative_tolerance);
	}

	template<class INT, class TYPE>
	std::enable_if_t<std::is_integral_v<INT> && std::is_arithmetic_v<TYPE>, TRange<INT>> Round(const TRange<TYPE> &v) // Return range with rounded elements
	{
		return TRange<INT>{ Round<INT, TYPE>(v.From), Round<INT, TYPE>(v.Till) };
	}

	template<class TO, class FROM>
	TRange<TO> Convert(const TRange<FROM> &v) // Convert to range with another data type
	{
		return TRange<TO>{ (TO)v.From, (TO)v.Till };
	}

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, TRange<TYPE>> Extend(const TRange<TYPE> &a, const TRange<TYPE> &b, const TYPE nval) // Return range which accomodates both ranges. nval defines a value used to specify "no limit" special value
	{
		return TRange<TYPE>{
			(a.From == nval) ? b.From : ((b.From == nval) ? a.From : Min<TYPE>(a.From, b.From)),
			(a.Till == nval) ? b.Till : ((b.Till == nval) ? a.Till : Max<TYPE>(a.Till, b.Till)) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, TRange<TYPE>> Extend(const TRange<TYPE> &a, const TRange<TYPE> &b, const TYPE nval, const TYPE relative_tolerance) // Return range which accomodates both ranges. nval defines a value used to specify "no limit" special value
	{
		return TRange<TYPE>{
			Equals<TYPE>(a.From, nval, relative_tolerance) ? b.From : (Equals<TYPE>(b.From, nval, relative_tolerance) ? a.From : Min<TYPE>(a.From, b.From)),
			Equals<TYPE>(a.Till, nval, relative_tolerance) ? b.Till : (Equals<TYPE>(b.Till, nval, relative_tolerance) ? a.Till : Max<TYPE>(a.Till, b.Till)) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, TRange<TYPE>> Intersection(const TRange<TYPE> &a, const TRange<TYPE> &b, const TYPE nval) // Return range which equals to intersection of two ranges. nval defines a value used to specify "no limit" special value. If ranges are not intersected, returns TRange{ nval, nval }
	{
		if (a.From == nval && a.Till == nval)
			return TRange<TYPE>{ nval, nval };
		if (b.From == nval && b.Till == nval)
			return TRange<TYPE>{ nval, nval };
		TRange<TYPE> a1{ (a.From == nval) ? a.Till : a.From, (a.Till == nval) ? a.From : a.Till };
		TRange<TYPE> b1{ (b.From == nval) ? b.Till : b.From, (b.Till == nval) ? b.From : b.Till };
		if (b1.From > a1.Till || b1.Till < a1.From)
			return TRange<TYPE>{ nval, nval };
		return TRange<TYPE>{ Max<TYPE>(a1.From, b1.From), Min<TYPE>(a1.Till, b1.Till) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, TRange<TYPE>> Intersection(const TRange<TYPE> &a, const TRange<TYPE> &b, const TYPE nval, const TYPE relative_tolerance) // Return range which equals to intersection of two ranges. nval defines a value used to specify "no limit" special value. If ranges are not intersected, returns TRange{ nval, nval }
	{
		if (Equals<TYPE>(a.From, nval, relative_tolerance) && Equals<TYPE>(a.Till, nval, relative_tolerance))
			return TRange<TYPE>{ nval, nval };
		if (Equals<TYPE>(b.From, nval, relative_tolerance) && Equals<TYPE>(b.Till, nval, relative_tolerance))
			return TRange<TYPE>{ nval, nval };
		TRange<TYPE> a1{ Equals<TYPE>(a.From, nval, relative_tolerance) ? a.Till : a.From, Equals<TYPE>(a.Till, nval, relative_tolerance) ? a.From : a.Till };
		TRange<TYPE> b1{ Equals<TYPE>(b.From, nval, relative_tolerance) ? b.Till : b.From, Equals<TYPE>(b.Till, nval, relative_tolerance) ? b.From : b.Till };
		if (b1.From > a1.Till || b1.Till < a1.From)
			return TRange<TYPE>{ nval, nval };
		return TRange<TYPE>{ Max<TYPE>(a1.From, b1.From), Min<TYPE>(a1.Till, b1.Till) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, bool> Intersect(const TRange<TYPE> &a, const TRange<TYPE> &b, const TYPE nval) // Return whether ranges have intersection or not. nval defines a value used to specify "no limit" special value
	{
		if (a.From == nval && a.Till == nval)
			return false;
		if (b.From == nval && b.Till == nval)
			return false;
		TRange<TYPE> a1{ (a.From == nval) ? a.Till : a.From, (a.Till == nval) ? a.From : a.Till };
		TRange<TYPE> b1{ (b.From == nval) ? b.Till : b.From, (b.Till == nval) ? b.From : b.Till };
		if (b1.From > a1.Till || b1.Till < a1.From)
			return false;
		return true;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Intersect(const TRange<TYPE> &a, const TRange<TYPE> &b, const TYPE nval, const TYPE relative_tolerance) // Return whether ranges have intersection or not. nval defines a value used to specify "no limit" special value
	{
		if (Equals<TYPE>(a.From, nval, relative_tolerance) && Equals<TYPE>(a.Till, nval, relative_tolerance))
			return false;
		if (Equals<TYPE>(b.From, nval, relative_tolerance) && Equals<TYPE>(b.Till, nval, relative_tolerance))
			return false;
		TRange<TYPE> a1{ Equals<TYPE>(a.From, nval, relative_tolerance) ? a.Till : a.From, Equals<TYPE>(a.Till, nval, relative_tolerance) ? a.From : a.Till };
		TRange<TYPE> b1{ Equals<TYPE>(b.From, nval, relative_tolerance) ? b.Till : b.From, Equals<TYPE>(b.Till, nval, relative_tolerance) ? b.From : b.Till };
		if (b1.From > a1.Till || b1.Till < a1.From)
			return false;
		return true;
	}
}