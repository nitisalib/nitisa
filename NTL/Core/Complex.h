// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
	union TComplex
	{
		struct
		{
			TYPE Re; // Real part
			TYPE Im; // Imaginary part
		};
		TYPE Data[2]; // Real and imaginary parts

		const TYPE &operator[](const int index) const // Return const reference to the part specified by index. 0 and 1 can be used only
		{
			return Data[index];
		}

		TYPE &operator[](const int index) // Return reference to the part specified by index. 0 and 1 can be used only
		{
			return Data[index];
		}
	};

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TComplex<TYPE> &a, const TComplex<TYPE> &b) // Strict comparison with another complex number for equality
	{
		return a.Re == b.Re && a.Im == b.Im;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TComplex<TYPE> &a, const TComplex<TYPE> &b) // Strict comparison with another complex number for inequality
	{
		return a.Re != b.Re || a.Im != b.Im;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator+(const TComplex<TYPE> &a, const TYPE &value) // Add complex and real values
	{
		return TComplex<TYPE>{ a.Re + value, a.Im };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator-(const TComplex<TYPE> &a, const TYPE &value) // Subtract real value from complex
	{
		return TComplex<TYPE>{ a.Re - value, a.Im };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator*(const TComplex<TYPE> &a, const TYPE &value) // Multiply complex and real values
	{
		return TComplex<TYPE>{ a.Re * value, a.Im * value };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator/(const TComplex<TYPE> &a, const TYPE &value) // Divide complex value by real one
	{
		return TComplex<TYPE>{ a.Re / value, a.Im / value  };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> &operator+=(TComplex<TYPE> &a, const TYPE &value) // Add real value to complex one
	{
		a.Re += value;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> &operator-=(TComplex<TYPE> &a, const TYPE &value) // Subtract real value from complex one
	{
		a.Re -= value;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> &operator*=(TComplex<TYPE> &a, const TYPE &value) // Multiply complex value by real one
	{
		a.Re *= value;
		a.Im *= value;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> &operator/=(TComplex<TYPE> &a, const TYPE &value) // Divide complex value by real one
	{
		a.Re /= value;
		a.Im /= value;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator+(const TYPE &value, const TComplex<TYPE> &a) // Add real and complex values
	{
		return TComplex<TYPE>{ value + a.Re, a.Im };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator-(const TYPE &value, const TComplex<TYPE> &a) // Subtract complex value from real one
	{
		return TComplex<TYPE>{ value - a.Re, -a.Im };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator*(const TYPE &value, const TComplex<TYPE> &a) // Multiply real and complex values
	{
		return TComplex<TYPE>{ value * a.Re, value * a.Im };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator/(const TYPE &value, const TComplex<TYPE> &a) // Divide real value by complex one
	{
		TYPE d{ a.Re * a.Re + a.Im * a.Im };
		return TComplex<TYPE>{ value * a.Re / d, -value * a.Im / d };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator+(const TComplex<TYPE> &a, const TComplex<TYPE> &b) // Add complex numbers
	{
		return TComplex<TYPE>{ a.Re + b.Re, a.Im + b.Im };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator-(const TComplex<TYPE> &a, const TComplex<TYPE> &b) // Subtract complex numbers
	{
		return TComplex<TYPE>{ a.Re - b.Re, a.Im - b.Im };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator*(const TComplex<TYPE> &a, const TComplex<TYPE> &b) // Multiply complex numbers
	{
		return TComplex<TYPE>{ a.Re * b.Re - a.Im * b.Im, a.Re * b.Im + b.Re * a.Im };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator/(const TComplex<TYPE> &a, const TComplex<TYPE> &b) // Divide complex numbers
	{
		TYPE d{ b.Re * b.Re + b.Im * b.Im };
		return TComplex<TYPE>{ (a.Re * b.Re + a.Im * b.Im) / d, (b.Re * a.Im - a.Re * b.Im) / d };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> &operator+=(TComplex<TYPE> &a, const TComplex<TYPE> &b) // Add second complex number to first one
	{
		a.Re += b.Re;
		a.Im += b.Im;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> &operator-=(TComplex<TYPE> &a, const TComplex<TYPE> &b) // Subtract second complex number from first one
	{
		a.Re -= b.Re;
		a.Im -= b.Im;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> &operator*=(TComplex<TYPE> &a, const TComplex<TYPE> &b) // Multiply first complex number by second one
	{
		a = TComplex<TYPE>{ a.Re * b.Re - a.Im * b.Im, a.Re * b.Im + b.Re * a.Im };
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> &operator/=(TComplex<TYPE> &a, const TComplex<TYPE> &b) // Divide first complex number by second one
	{
		TYPE d{ b.Re * b.Re + b.Im * b.Im };
		a = TComplex<TYPE>{ (a.Re * b.Re + a.Im * b.Im) / d, (b.Re * a.Im - a.Re * b.Im) / d };
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TComplex<TYPE>> operator-(const TComplex<TYPE> &a) // Inverse complex value
	{
		return TComplex<TYPE>{ -a.Re, -a.Im };
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TComplex<TYPE> &a, const TComplex<TYPE> &b) // Compare whether complex values are equal
	{
		return a.Re == b.Re && a.Im == b.Im;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TComplex<TYPE> &a, const TComplex<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether complex values are equal. For float data type
	{
		return IsEqual<TYPE>(a.Re, b.Re, tolerance) && IsEqual<TYPE>(a.Im, b.Im, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TComplex<TYPE> &a, const TComplex<TYPE> &b) // Compare whether complex values aren't equal
	{
		return a.Re != b.Re || a.Im != b.Im;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TComplex<TYPE> &a, const TComplex<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether complex values aren't equal. For float data types
	{
		return IsNotEqual<TYPE>(a.Re, b.Re, tolerance) || IsNotEqual<TYPE>(a.Im, b.Im, tolerance);
	}

	template<class TO, class FROM>
	TComplex<TO> Convert(const TComplex<FROM> &v) // Convert to complex with another data type
	{
		return TComplex<TO>{ (TO)v.Re, (TO)v.Im };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Modulus(const TComplex<TYPE> &v) // Return modulus
	{
		return (TYPE)std::sqrt(v.Re * v.Re + v.Im * v.Im);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Argument(const TComplex<TYPE> &v) // Return argument
	{
		return (TYPE)std::atan2(v.Im, v.Re);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TComplex<TYPE> &a, const TComplex<TYPE> &b, const FLOAT tolerance) // Check whether complex values are equal using relative comparison
	{
		return Equals<TYPE, FLOAT>(a.Re, b.Re, tolerance) && Equals<TYPE, FLOAT>(a.Im, b.Im, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TComplex<TYPE> &a, const TComplex<TYPE> &b, const TYPE tolerance) // Check whether complex values are equal using relative comparison
	{
		return Equals<TYPE>(a.Re, b.Re, tolerance) && Equals<TYPE>(a.Im, b.Im, tolerance);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TComplex<TYPE> &a, const TComplex<TYPE> &b, const FLOAT tolerance) // Check whether complex values aren't equal using relative comparison
	{
		return NotEquals<TYPE, FLOAT>(a.Re, b.Re, tolerance) || NotEquals<TYPE, FLOAT>(a.Im, b.Im, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TComplex<TYPE> &a, const TComplex<TYPE> &b, const TYPE tolerance) // Check whether complex values aren't equal using relative comparison
	{
		return NotEquals<TYPE>(a.Re, b.Re, tolerance) || NotEquals<TYPE>(a.Im, b.Im, tolerance);
	}

	// Find solution of x + a = 0 equation and store it in x1. Return number of found solutions(always 1)
	template<class TYPE>
	typename std::enable_if_t<std::is_floating_point_v<TYPE>, int> SolveEquation1n(const TYPE a, TComplex<TYPE> &x1)
	{
		x1.Re = -a;
		x1.Im = 0;
		return 1;
	}

	// Find solution of ax + b = 0 equation and store it in x1. Return number of found solutions(either 1 or 0 if a = 0). Tolerance is used for comparison of a with zero
	template<class TYPE>
	typename std::enable_if_t<std::is_floating_point_v<TYPE>, int> SolveEquation1n(const TYPE a, const TYPE b, TComplex<TYPE> &x1, const TYPE tolerance)
	{
		if (IsNotZero<TYPE>(a, tolerance))
			return SolveEquation1n<TYPE>(b / a, x1);
		return 0;
	}

	// Find solutions of x * x + ax + b = 0 equation and store them in x1 and x2. Return number of found solutions including complex ones. Return either 1 or 2
	template<class TYPE>
	typename std::enable_if_t<std::is_floating_point_v<TYPE>, int> SolveEquation2n(const TYPE a, const TYPE b, TComplex<TYPE> &x1, TComplex<TYPE> &x2)
	{
		TYPE d{ a * a - 4 * b };
		if (d > 0)
		{
			TYPE ds{ std::sqrt(d) };
			x1.Re = (-a + ds) / 2;
			x1.Im = 0;
			x2.Re = (-a - ds) / 2;
			x2.Im = 0;
			return 2;
		}
		if (d == 0)
		{
			x1.Re = -a / 2;
			x1.Im = 0;
			return 1;
		}
		TYPE ds{ std::sqrt(Abs<TYPE>(d)) };
		x1.Re = -a / 2;
		x1.Im = ds / 2;
		x2.Re = x1.Re;
		x2.Im = -x1.Im;
		return 2;
	}

	// Find solutions of a * x * x + bx + c = 0 equation and store them in x1 and x2. Return number of found solutions including complex ones. Return 0(if both a and b are zero), 1 or 2. Tolerance is used to compare a and b with zero
	template<class TYPE>
	typename std::enable_if_t<std::is_floating_point_v<TYPE>, int> SolveEquation2n(const TYPE a, const TYPE b, const TYPE c, TComplex<TYPE> &x1, TComplex<TYPE> &x2, const TYPE tolerance)
	{
		if (IsNotZero(a, tolerance))
			return SolveEquation2n<TYPE>(b / a, c / a, x1, x2);
		return SolveEquation1n<TYPE>(b, c, x1, tolerance);
	}

	// Find solutions of x * x * x + a * x * x + b * x + c = 0 equation and store them in x1, x2, and x3. Return number of found solutions including complex ones. Return either 2 or 3
	template<class TYPE>
	typename std::enable_if_t<std::is_floating_point_v<TYPE>, int> SolveEquation3n(const TYPE a, const TYPE b, const TYPE c, TComplex<TYPE> &x1, TComplex<TYPE> &x2, TComplex<TYPE> &x3)
	{
		TYPE q{ (a * a - 3 * b) / 9 }, r{ (2 * a * a * a - 9 * a * b + 27 * c) / 54 };
		TYPE q3{ q * q * q }, r2{ r * r };
		if (r2 < q3)
		{
			TYPE t{ std::acos(r / std::sqrt(q3)) };
			q = -2 * std::sqrt(q);
			x1.Re = q * std::cos(t / 3) - a / 3;
			x1.Im = 0;
			x2.Re = q * std::cos((t + 2 * Pi<TYPE>) / 3) - a / 3;
			x2.Im = 0;
			x3.Re = q * std::cos((t - 2 * Pi<TYPE>) / 3) - a / 3;
			x3.Im = 0;
			return 3;
		}
		TYPE A{ -Sign<TYPE>(r) * std::pow(Abs<TYPE>(r) + std::sqrt(r2 - q3), 1 / (TYPE)3) };
		TYPE B{ (A == 0) ? 0 : (q / A) };
		x1.Re = A + B - a / 3;
		x1.Im = 0;
		if (A == B)
		{
			x2.Re = -A - a / 3;
			x2.Im = 0;
			return 2;
		}
		x2.Re = -(A + B) / 2 - a / 3;
		x2.Im = std::sqrt((TYPE)3) * (A - B) / 2;
		x3.Re = x2.Re;
		x3.Im = -x2.Im;
		return 3;
	}

	// Find solutions of a * x * x * x + b * x * x + c * x + d = 0 equation and store them in x1, x2, and x3. Return number of found solutions including complex ones. Return 0(if a, b, and c are zero), 2 or 3. Tolerance is used to compare a, b, and c with zero
	template<class TYPE>
	typename std::enable_if_t<std::is_floating_point_v<TYPE>, int> SolveEquation3n(const TYPE a, const TYPE b, const TYPE c, const TYPE d, TComplex<TYPE> &x1, TComplex<TYPE> &x2, TComplex<TYPE> &x3, const TYPE tolerance)
	{
		if (IsNotZero(a, tolerance))
			return SolveEquation3n<TYPE>(b / a, c / a, d / a, x1, x2, x3);
		return SolveEquation2n<TYPE>(b, c, d, x1, x2, tolerance);
	}
}