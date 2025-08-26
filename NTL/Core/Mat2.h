// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Matrix.h"

namespace ntl
{
	// Row-major order
	template<class TYPE>
	union TMat2
	{
		struct
		{
			TYPE _11, _12; // First row
			TYPE _21, _22; // Second row
		};
		TVec2<TYPE> Rows[2]; // Rows as vectors
		TYPE Data[4]; // Elements as array
		TMatrix<TYPE, 2, 2> M; // As TMatrix

		TMat2() = default;
		TMat2(const TMat2 &other) = default;
		TMat2(TMat2 &&other) = default;

		// Create with specified elements
		TMat2(
			const TYPE m11, const TYPE m12,
			const TYPE m21, const TYPE m22):
			_11{ m11 }, _12{ m12 },
			_21{ m21 }, _22{ m22 }
		{

		}

		// Create with specified rows
		TMat2(const TVec2<TYPE> &row1, const TVec2<TYPE> &row2):
			Rows{ row1, row2 }
		{

		}

		// Create diagonal matrix
		TMat2(const TYPE diagonal, const TYPE other) :
			_11{ diagonal }, _12{ other },
			_21{ other }, _22{ diagonal }
		{

		}

		// Create from TMatrix
		TMat2(const TMatrix<TYPE, 2, 2> &m) :
			M{ m }
		{

		}

		TMat2 &operator=(const TMat2 &other) = default;
		TMat2 &operator=(TMat2 &&other) = default;

		TVec2<TYPE> operator[](const size_t row) const // Return specified row. Used when matrix is a constant
		{
			return Rows[row];
		}

		TVec2<TYPE> &operator[](const size_t row) // Return specified row
		{
			return Rows[row];
		}
	};

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TMat2<TYPE> &a, const TMat2<TYPE> &b) // Check whether matrices are equal. Can be used for non-float data types only
	{
		return
			a._11 == b._11 && a._12 == b._12 &&
			a._21 == b._21 && a._22 == b._22;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TMat2<TYPE> &a, const TMat2<TYPE> &b) // Check whether matrices aren't equal. Can be used for non-float data types only
	{
		return
			a._11 != b._11 || a._12 != b._12 ||
			a._21 != b._21 || a._22 != b._22;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator+(const TMat2<TYPE> &m, const TYPE val) // Add matrix and scalar
	{
		return TMat2<TYPE>{
			m._11 + val, m._12 + val,
			m._21 + val, m._22 + val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator-(const TMat2<TYPE> &m, const TYPE val) // Subtract matrix and scalar
	{
		return TMat2<TYPE>{
			m._11 - val, m._12 - val,
			m._21 - val, m._22 - val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator*(const TMat2<TYPE> &m, const TYPE val) // Multiply matrix and scalar
	{
		return TMat2<TYPE>{
			m._11 * val, m._12 * val,
			m._21 * val, m._22 * val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator/(const TMat2<TYPE> &m, const TYPE val) // Divide matrix and scalar
	{
		return TMat2<TYPE>{
			m._11 / val, m._12 / val,
			m._21 / val, m._22 / val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator+(const TYPE val, const TMat2<TYPE> &m) // Add scalar and matrix
	{
		return TMat2<TYPE>{
			val + m._11, val + m._12,
			val + m._21, val + m._22
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator-(const TYPE val, const TMat2<TYPE> &m) // Subtract scalar and matrix
	{
		return TMat2<TYPE>{
			val - m._11, val - m._12,
			val - m._21, val - m._22
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator*(const TYPE val, const TMat2<TYPE> &m) // Multiply scalar and matrix
	{
		return TMat2<TYPE>{
			val * m._11, val * m._12,
			val * m._21, val * m._22
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator/(const TYPE val, const TMat2<TYPE> &m) // Divide scalar and matrix
	{
		return TMat2<TYPE>{
			val / m._11, val / m._12,
			val / m._21, val / m._22 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> &operator+=(TMat2<TYPE> &m, const TYPE val) // Add scalar to matrix
	{
		m._11 += val; m._12 += val;
		m._21 += val; m._22 += val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> &operator-=(TMat2<TYPE> &m, const TYPE val) // Subtract scalar from matrix
	{
		m._11 -= val; m._12 -= val;
		m._21 -= val; m._22 -= val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> &operator*=(TMat2<TYPE> &m, const TYPE val) // Multiply matrix by scalar
	{
		m._11 *= val; m._12 *= val;
		m._21 *= val; m._22 *= val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> &operator/=(TMat2<TYPE> &m, const TYPE val) // Divide matrix by scalar
	{
		m._11 /= val; m._12 /= val;
		m._21 /= val; m._22 /= val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec2<TYPE>> operator*(const TVec2<TYPE> &v, const TMat2<TYPE> &m) // Multiply vector and matrix
	{
		return TVec2<TYPE>{
			v.X * m._11 + v.Y * m._21,
			v.X * m._12 + v.Y * m._22
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec2<TYPE>> operator*(const TMat2<TYPE> &m, const TVec2<TYPE> &v) // Multiply matrix and vector
	{
		return TVec2<TYPE>{
			v.X * m._11 + v.Y * m._12,
			v.X * m._21 + v.Y * m._22
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec2<TYPE>> &operator*=(TVec2<TYPE> &v, const TMat2<TYPE> &m) // Multiply vector by matrix
	{
		TYPE x{ v.X * m._11 + v.Y * m._21 };
		TYPE y{ v.X * m._12 + v.Y * m._22 };
		v.X = x;
		v.Y = y;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator+(const TMat2<TYPE> &a, const TMat2<TYPE> &b) // Add matrices
	{
		return TMat2<TYPE>{
			a._11 + b._11, a._12 + b._12,
			a._21 + b._21, a._22 + b._22
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator-(const TMat2<TYPE> &a, const TMat2<TYPE> &b) // Subtract matrices
	{
		return TMat2<TYPE>{
			a._11 - b._11, a._12 - b._12,
			a._21 - b._21, a._22 - b._22
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator*(const TMat2<TYPE> &a, const TMat2<TYPE> &b) // Multiply matrices
	{
		return TMat2<TYPE>{
			a._11 * b._11 + a._12 * b._21, a._11 * b._12 + a._12 * b._22,
			a._21 * b._11 + a._22 * b._21, a._21 * b._12 + a._22 * b._22
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator+=(TMat2<TYPE> &a, const TMat2<TYPE> &b) // Add matrix to matrix
	{
		a._11 += b._11; a._12 += b._12;
		a._21 += b._21; a._22 += b._22;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> operator-=(TMat2<TYPE> &a, const TMat2<TYPE> &b) // Subtract matrix from matrix
	{
		a._11 -= b._11; a._12 -= b._12;
		a._21 -= b._21; a._22 -= b._22;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> &operator*=(TMat2<TYPE> &a, const TMat2<TYPE> &b) // Multiply matrix by matrix
	{
		TYPE m11{ a._11 * b._11 + a._12 * b._21 }, m12{ a._11 * b._12 + a._12 * b._22 };
		TYPE m21{ a._21 * b._11 + a._22 * b._21 }, m22{ a._21 * b._12 + a._22 * b._22 };
		a._11 = m11; a._12 = m12;
		a._21 = m21; a._22 = m22;
		return a;
	}

	template<class TYPE>
	TYPE Minor(const TMat2<TYPE> &m, const size_t row, const size_t col) // Return matrix minor of specified row and column
	{
		return Minor<TYPE, 2, 2>(m.M, row, col);
	}

	template<class TYPE>
	void Transpose(TMat2<TYPE> &m) // Transpose matrix
	{
		Swap<TYPE>(m._21, m._12);
	}

	template<class TYPE>
	TMat2<TYPE> Transposed(const TMat2<TYPE> &m) // Return transposed matrix
	{
		return TMat2<TYPE>{
			m._11, m._21,
			m._12, m._22
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Determinant(const TMat2<TYPE> &m) // Return matrix determinant. Can be used with arithmetic data types only
	{
		return m._11 * m._22 - m._12 * m._21;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Inverse(TMat2<TYPE> &m) // Inverse matrix. Can be used with arithmetic data types only
	{
		Inverse<TYPE, 2>(m.M);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> Inversed(const TMat2<TYPE> &m) // Return inversed matrix. Can be used with arithmetic data types only
	{
		return TMat2<TYPE>{ Inversed<TYPE, 2>(m.M) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Identity(TMat2<TYPE> &m) // Makes matrix identity. Can be used with arithmetic data types only
	{
		m._11 = 1; m._12 = 0;
		m._21 = 0; m._22 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Diagonal(TMat2<TYPE> &m, const TYPE v) // Makes matrix diagonal. Can be used with arithmetic data types only
	{
		m._11 = v; m._12 = 0;
		m._21 = 0; m._22 = v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Scale(TMat2<TYPE> &m, const TYPE x, const TYPE y) // Makes scaling matrix. Can be used with arithmetic data types only
	{
		m._11 = x; m._12 = 0;
		m._21 = 0; m._22 = y;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TMat2<TYPE> &a, const TMat2<TYPE> &b) // Compare whether matrices are equal
	{
		for (size_t r = 0; r < 2; r++)
			for (size_t c = 0; c < 2; c++)
				if (a.Rows[r].Data[c] != b.Rows[r].Data[c])
					return false;
		return true;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TMat2<TYPE> &a, const TMat2<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether matrices are equal
	{
		for (size_t r = 0; r < 2; r++)
			for (size_t c = 0; c < 2; c++)
				if (IsNotEqual<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return false;
		return true;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TMat2<TYPE> &a, const TMat2<TYPE> &b) // Compare whether matrices aren't equal
	{
		for (size_t r = 0; r < 2; r++)
			for (size_t c = 0; c < 2; c++)
				if (a.Rows[r].Data[c] != b.Rows[r].Data[c])
					return true;
		return false;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TMat2<TYPE> &a, const TMat2<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether matrices aren't equal
	{
		for (size_t r = 0; r < 2; r++)
			for (size_t c = 0; c < 2; c++)
				if (IsNotEqual<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return true;
		return false;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TMat2<TYPE> &a, const TMat2<TYPE> &b, const FLOAT tolerance) // Check whether matrices are equal using relative comparison
	{
		for (size_t r = 0; r < 2; r++)
			for (size_t c = 0; c < 2; c++)
				if (NotEquals<TYPE, FLOAT>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return false;
		return true;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TMat2<TYPE> &a, const TMat2<TYPE> &b, const TYPE tolerance) // Check whether matrices are equal using relative comparison
	{
		for (size_t r = 0; r < 2; r++)
			for (size_t c = 0; c < 2; c++)
				if (NotEquals<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return false;
		return true;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TMat2<TYPE> &a, const TMat2<TYPE> &b, const FLOAT tolerance) // Check whether matrices aren't equal using relative comparison
	{
		for (size_t r = 0; r < 2; r++)
			for (size_t c = 0; c < 2; c++)
				if (NotEquals<TYPE, FLOAT>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return true;
		return false;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TMat2<TYPE> &a, const TMat2<TYPE> &b, const TYPE tolerance) // Check whether matrices aren't equal using relative comparison
	{
		for (size_t r = 0; r < 2; r++)
			for (size_t c = 0; c < 2; c++)
				if (NotEquals<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return true;
		return false;
	}

	template<class TO, class FROM>
	TMat2<TO> Convert(const TMat2<FROM> &m) // Convert to matrix with another data type
	{
		return TMat2<TO>{
			(TO)m._11, (TO)m._12,
			(TO)m._21, (TO)m._22
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> Mat2Identity() // Return identity matrix
	{
		return TMat2<TYPE>{
			1, 0,
			0, 1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> Mat2Diagonal(const TYPE v) // Return diagonal matrix
	{
		return TMat2<TYPE>{
			v, 0,
			0, v
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat2<TYPE>> Mat2Scale(const TYPE x, const TYPE y) // Return scaling matrix
	{
		return TMat2<TYPE>{
			x, 0,
			0, y
		};
	}
}