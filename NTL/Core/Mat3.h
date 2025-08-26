// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Mat2.h"

namespace ntl
{
	// Row-major order
	template<class TYPE>
	union TMat3
	{
		struct
		{
			TYPE _11, _12, _13; // First row
			TYPE _21, _22, _23; // Second row
			TYPE _31, _32, _33; // Third row
		};
		TVec3<TYPE> Rows[3]; // Rows as vectors
		TYPE Data[9]; // Elements as array
		TMatrix<TYPE, 3, 3> M; // As TMatrix

		TMat3() = default;
		TMat3(const TMat3 &other) = default;
		TMat3(TMat3 &&other) = default;

		// Create with specified elements
		TMat3(
			const TYPE m11, const TYPE m12, const TYPE m13,
			const TYPE m21, const TYPE m22, const TYPE m23,
			const TYPE m31, const TYPE m32, const TYPE m33) :
			_11{ m11 }, _12{ m12 }, _13{ m13 },
			_21{ m21 }, _22{ m22 }, _23{ m23 },
			_31{ m31 }, _32{ m32 }, _33{ m33 }
		{

		}

		// Create with specified rows
		TMat3(const TVec3<TYPE> &row1, const TVec3<TYPE> &row2, const TVec3<TYPE> &row3) :
			Rows{ row1, row2, row3 }
		{

		}

		// Create diagonal matrix
		TMat3(const TYPE diagonal, const TYPE other) :
			_11{ diagonal }, _12{ other }, _13{ other },
			_21{ other }, _22{ diagonal }, _23{ other },
			_31{ other }, _32{ other }, _33{ diagonal }
		{

		}

		// Create from TMatrix
		TMat3(const TMatrix<TYPE, 3, 3> &m) :
			M{ m }
		{

		}

		TMat3 &operator=(const TMat3 &other) = default;
		TMat3 &operator=(TMat3 &&other) = default;

		TVec3<TYPE> operator[](const size_t row) const // Return specified row. Used when matrix is a constant
		{
			return Rows[row];
		}

		TVec3<TYPE> &operator[](const size_t row) // Return specified row
		{
			return Rows[row];
		}
	};

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TMat3<TYPE> &a, const TMat3<TYPE> &b) // Check whether matrices are equal. Can be used for non-float data types only
	{
		return
			a._11 == b._11 && a._12 == b._12 && a._13 == b._13 &&
			a._21 == b._21 && a._22 == b._22 && a._23 == b._23 &&
			a._31 == b._31 && a._32 == b._32 && a._33 == b._33;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TMat3<TYPE> &a, const TMat3<TYPE> &b) // Check whether matrices aren't equal. Can be used for non-float data types only
	{
		return
			a._11 != b._11 || a._12 != b._12 || a._13 != b._13 ||
			a._21 != b._21 || a._22 != b._22 || a._23 != b._23 ||
			a._31 != b._31 || a._32 != b._32 || a._33 != b._33;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator+(const TMat3<TYPE> &m, const TYPE val) // Add matrix and scalar
	{
		return TMat3<TYPE>{
			m._11 + val, m._12 + val, m._13 + val,
			m._21 + val, m._22 + val, m._23 + val,
			m._31 + val, m._32 + val, m._33 + val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator-(const TMat3<TYPE> &m, const TYPE val) // Subtract matrix and scalar
	{
		return TMat3<TYPE>{
			m._11 - val, m._12 - val, m._13 - val,
			m._21 - val, m._22 - val, m._23 - val,
			m._31 - val, m._32 - val, m._33 - val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator*(const TMat3<TYPE> &m, const TYPE val) // Multiply matrix and scalar
	{
		return TMat3<TYPE>{
			m._11 * val, m._12 * val, m._13 * val,
			m._21 * val, m._22 * val, m._23 * val,
			m._31 * val, m._32 * val, m._33 * val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator/(const TMat3<TYPE> &m, const TYPE val) // Divide matrix and scalar
	{
		return TMat3<TYPE>{
			m._11 / val, m._12 / val, m._13 / val,
			m._21 / val, m._22 / val, m._23 / val,
			m._31 / val, m._32 / val, m._33 / val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator+(const TYPE val, const TMat3<TYPE> &m) // Add scalar and matrix
	{
		return TMat3<TYPE>{
			val + m._11, val + m._12, val + m._13,
			val + m._21, val + m._22, val + m._23,
			val + m._31, val + m._32, val + m._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator-(const TYPE val, const TMat3<TYPE> &m) // Subtract scalar and matrix
	{
		return TMat3<TYPE>{
			val - m._11, val - m._12, val - m._13,
			val - m._21, val - m._22, val - m._23,
			val - m._31, val - m._32, val - m._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator*(const TYPE val, const TMat3<TYPE> &m) // Multiply scalar and matrix
	{
		return TMat3<TYPE>{
			val * m._11, val * m._12, val * m._13,
			val * m._21, val * m._22, val * m._23,
			val * m._31, val * m._32, val * m._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator/(const TYPE val, const TMat3<TYPE> &m) // Divide scalar and matrix
	{
		return TMat3<TYPE>{
			val / m._11, val / m._12, val / m._13,
			val / m._21, val / m._22, val / m._23,
			val / m._31, val / m._32, val / m._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> &operator+=(TMat3<TYPE> &m, const TYPE val) // Add scalar to matrix
	{
		m._11 += val; m._12 += val; m._13 += val;
		m._21 += val; m._22 += val; m._23 += val;
		m._31 += val; m._32 += val; m._33 += val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> &operator-=(TMat3<TYPE> &m, const TYPE val) // Subtract scalar from matrix
	{
		m._11 -= val; m._12 -= val; m._13 -= val;
		m._21 -= val; m._22 -= val; m._23 -= val;
		m._31 -= val; m._32 -= val; m._33 -= val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> &operator*=(TMat3<TYPE> &m, const TYPE val) // Multiply matrix by scalar
	{
		m._11 *= val; m._12 *= val; m._13 *= val;
		m._21 *= val; m._22 *= val; m._23 *= val;
		m._31 *= val; m._32 *= val; m._33 *= val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> &operator/=(TMat3<TYPE> &m, const TYPE val) // Divide matrix by scalar
	{
		m._11 /= val; m._12 /= val; m._13 /= val;
		m._21 /= val; m._22 /= val; m._23 /= val;
		m._31 /= val; m._32 /= val; m._33 /= val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec3<TYPE>> operator*(const TVec3<TYPE> &v, const TMat3<TYPE> &m) // Multiply vector and matrix
	{
		return TVec3<TYPE>{
			v.X * m._11 + v.Y * m._21 + v.Z * m._31,
			v.X * m._12 + v.Y * m._22 + v.Z * m._32,
			v.X * m._13 + v.Y * m._23 + v.Z * m._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec3<TYPE>> &operator*=(TVec3<TYPE> &v, const TMat3<TYPE> &m) // Multiply vector by matrix
	{
		TYPE x{ v.X * m._11 + v.Y * m._21 + v.Z * m._31 };
		TYPE y{ v.X * m._12 + v.Y * m._22 + v.Z * m._32 };
		TYPE z{ v.X * m._13 + v.Y * m._23 + v.Z * m._33 };
		v.X = x;
		v.Y = y;
		v.Z = z;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec3<TYPE>> operator*(const TMat3<TYPE> &m, const TVec3<TYPE> &v) // Multiply matrix and vector
	{
		return TVec3<TYPE>{
			v.X * m._11 + v.Y * m._12 + v.Z * m._13,
			v.X * m._21 + v.Y * m._22 + v.Z * m._23,
			v.X * m._31 + v.Y * m._32 + v.Z * m._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator*(const TVec4<TYPE> &v, const TMat3<TYPE> &m) // Multiply vector and matrix
	{
		return TVec4<TYPE>{
			v.X * m._11 + v.Y * m._21 + v.Z * m._31,
			v.X * m._12 + v.Y * m._22 + v.Z * m._32,
			v.X * m._13 + v.Y * m._23 + v.Z * m._33,
			1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> &operator*=(TVec4<TYPE> &v, const TMat3<TYPE> &m) // Multiply vector by matrix
	{
		TYPE x{ v.X * m._11 + v.Y * m._21 + v.Z * m._31 };
		TYPE y{ v.X * m._12 + v.Y * m._22 + v.Z * m._32 };
		TYPE z{ v.X * m._13 + v.Y * m._23 + v.Z * m._33 };
		v.X = x;
		v.Y = y;
		v.Z = z;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator*(const TMat3<TYPE> &m, const TVec4<TYPE> &v) // Multiply matrix and vector
	{
		return TVec4<TYPE>{
			v.X * m._11 + v.Y * m._12 + v.Z * m._13,
			v.X * m._21 + v.Y * m._22 + v.Z * m._23,
			v.X * m._31 + v.Y * m._32 + v.Z * m._33,
			1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator*(const TQuaternion<TYPE> &q, const TMat3<TYPE> &m) // Multiply quaternion and matrix
	{
		return TQuaternion<TYPE>{
			q.X * m._11 + q.Y * m._21 + q.Z * m._31,
			q.X * m._12 + q.Y * m._22 + q.Z * m._32,
			q.X * m._13 + q.Y * m._23 + q.Z * m._33,
			q.W
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> &operator*=(TQuaternion<TYPE> &q, const TMat3<TYPE> &m) // Multiply quaternion by matrix
	{
		TYPE x{ q.X * m._11 + q.Y * m._21 + q.Z * m._31 };
		TYPE y{ q.X * m._12 + q.Y * m._22 + q.Z * m._32 };
		TYPE z{ q.X * m._13 + q.Y * m._23 + q.Z * m._33 };
		q.X = x;
		q.Y = y;
		q.Z = z;
		return q;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator*(const TMat3<TYPE> &m, const TQuaternion<TYPE> &q) // Multiply matrix and quaternion
	{
		return TQuaternion<TYPE>{
			q.X * m._11 + q.Y * m._12 + q.Z * m._13,
			q.X * m._21 + q.Y * m._22 + q.Z * m._23,
			q.X * m._31 + q.Y * m._32 + q.Z * m._33,
			q.W
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator+(const TMat3<TYPE> &a, const TMat3<TYPE> &b) // Add matrices
	{
		return TMat3<TYPE>{
			a._11 + b._11, a._12 + b._12, a._13 + b._13,
			a._21 + b._21, a._22 + b._22, a._23 + b._23,
			a._31 + b._31, a._32 + b._32, a._33 + b._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator-(const TMat3<TYPE> &a, const TMat3<TYPE> &b) // Subtract matrices
	{
		return TMat3<TYPE>{
			a._11 - b._11, a._12 - b._12, a._13 - b._13,
			a._21 - b._21, a._22 - b._22, a._23 - b._23,
			a._31 - b._31, a._32 - b._32, a._33 - b._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator*(const TMat3<TYPE> &a, const TMat3<TYPE> &b) // Multiply matrices
	{
		return TMat3<TYPE>{
			a._11 * b._11 + a._12 * b._21 + a._13 * b._31,
			a._11 * b._12 + a._12 * b._22 + a._13 * b._32,
			a._11 * b._13 + a._12 * b._23 + a._13 * b._33,

			a._21 * b._11 + a._22 * b._21 + a._23 * b._31,
			a._21 * b._12 + a._22 * b._22 + a._23 * b._32,
			a._21 * b._13 + a._22 * b._23 + a._23 * b._33,

			a._31 * b._11 + a._32 * b._21 + a._33 * b._31,
			a._31 * b._12 + a._32 * b._22 + a._33 * b._32,
			a._31 * b._13 + a._32 * b._23 + a._33 * b._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator+=(TMat3<TYPE> &a, const TMat3<TYPE> &b) // Add matrix to matrix
	{
		a._11 += b._11; a._12 += b._12; a._13 += b._13;
		a._21 += b._21; a._22 += b._22; a._23 += b._23;
		a._31 += b._31; a._32 += b._32; a._33 += b._33;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> operator-=(TMat3<TYPE> &a, const TMat3<TYPE> &b) // Subtract matrix from matrix
	{
		a._11 -= b._11; a._12 -= b._12; a._13 -= b._13;
		a._21 -= b._21; a._22 -= b._22; a._23 -= b._23;
		a._31 -= b._31; a._32 -= b._32; a._33 -= b._33;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> &operator*=(TMat3<TYPE> &a, const TMat3<TYPE> &b) // Multiply matrix by matrix
	{
		TYPE m11{ a._11 * b._11 + a._12 * b._21 + a._13 * b._31 };
		TYPE m12{ a._11 * b._12 + a._12 * b._22 + a._13 * b._32 };
		TYPE m13{ a._11 * b._13 + a._12 * b._23 + a._13 * b._33 };

		TYPE m21{ a._21 * b._11 + a._22 * b._21 + a._23 * b._31 };
		TYPE m22{ a._21 * b._12 + a._22 * b._22 + a._23 * b._32 };
		TYPE m23{ a._21 * b._13 + a._22 * b._23 + a._23 * b._33 };

		TYPE m31{ a._31 * b._11 + a._32 * b._21 + a._33 * b._31 };
		TYPE m32{ a._31 * b._12 + a._32 * b._22 + a._33 * b._32 };
		TYPE m33{ a._31 * b._13 + a._32 * b._23 + a._33 * b._33 };

		a._11 = m11; a._12 = m12; a._13 = m13;
		a._21 = m21; a._22 = m22; a._23 = m23;
		a._31 = m31; a._32 = m32; a._33 = m33;
		return a;
	}

	template<class TYPE>
	TMat2<TYPE> Minor(const TMat3<TYPE> &m, const size_t row, const size_t col) // Return matrix minor of specified row and column
	{
		return Minor<TYPE, 3, 3>(m.M, row, col);
	}

	template<class TYPE>
	void Transpose(TMat3<TYPE> &m) // Transpose matrix
	{
		Swap<TYPE>(m._21, m._12);
		Swap<TYPE>(m._31, m._13);
		Swap<TYPE>(m._32, m._23);
	}

	template<class TYPE>
	TMat3<TYPE> Transposed(const TMat3<TYPE> &m) // Return transposed matrix
	{
		return TMat3<TYPE>{
			m._11, m._21, m._31,
			m._12, m._22, m._32,
			m._13, m._23, m._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Determinant(const TMat3<TYPE> &m) // Return matrix determinant. Can be used with arithmetic data types only
	{
		return
			m._11 * m._22 * m._33 -
			m._11 * m._23 * m._32 -
			m._12 * m._21 * m._33 +
			m._12 * m._23 * m._31 +
			m._13 * m._21 * m._32 -
			m._13 * m._22 * m._31;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Inverse(TMat3<TYPE> &m) // Inverse matrix. Can be used with arithmetic data types only
	{
		Inverse<TYPE, 3>(m.M);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> Inversed(const TMat3<TYPE> &m) // Return inversed matrix. Can be used with arithmetic data types only
	{
		return TMat3<TYPE>{Inversed<TYPE, 3>(m.M) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Identity(TMat3<TYPE> &m) // Makes matrix identity. Can be used with arithmetic data types only
	{
		m._11 = 1; m._12 = 0; m._13 = 0;
		m._21 = 0; m._22 = 1; m._23 = 0;
		m._31 = 0; m._32 = 0; m._33 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Diagonal(TMat3<TYPE> &m, const TYPE v) // Makes matrix diagonal. Can be used with arithmetic data types only
	{
		m._11 = v; m._12 = 0; m._13 = 0;
		m._21 = 0; m._22 = v; m._23 = 0;
		m._31 = 0; m._32 = 0; m._33 = v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Rotate(TMat3<TYPE> &m, const TYPE a) // Makes rotation around X-axis matrix. Can be used with arithmetic data types only
	{
		TYPE C{ std::cos(a) }, S{ std::sin(a) }, s{ -S };
		m._11 = C; m._12 = s; m._13 = 0;
		m._21 = S; m._22 = C; m._23 = 0;
		m._31 = 0; m._32 = 0; m._33 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Scale(TMat3<TYPE> &m, const TYPE x, const TYPE y, const TYPE z) // Makes scaling matrix. Can be used with arithmetic data types only
	{
		m._11 = x; m._12 = 0; m._13 = 0;
		m._21 = 0; m._22 = y; m._23 = 0;
		m._31 = 0; m._32 = 0; m._33 = z;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TMat3<TYPE> &a, const TMat3<TYPE> &b) // Compare whether matrices are equal
	{
		for (size_t r = 0; r < 3; r++)
			for (size_t c = 0; c < 3; c++)
				if (a.Rows[r].Data[c] != b.Rows[r].Data[c])
					return false;
		return true;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TMat3<TYPE> &a, const TMat3<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether matrices are equal
	{
		for (size_t r = 0; r < 3; r++)
			for (size_t c = 0; c < 3; c++)
				if (IsNotEqual<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return false;
		return true;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TMat3<TYPE> &a, const TMat3<TYPE> &b) // Compare whether matrices aren't equal
	{
		for (size_t r = 0; r < 3; r++)
			for (size_t c = 0; c < 3; c++)
				if (a.Rows[r].Data[c] != b.Rows[r].Data[c])
					return true;
		return false;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TMat3<TYPE> &a, const TMat3<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether matrices aren't equal
	{
		for (size_t r = 0; r < 3; r++)
			for (size_t c = 0; c < 3; c++)
				if (IsNotEqual<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return true;
		return false;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TMat3<TYPE> &a, const TMat3<TYPE> &b, const FLOAT tolerance) // Check whether matrices are equal using relative comparison
	{
		for (size_t r = 0; r < 3; r++)
			for (size_t c = 0; c < 3; c++)
				if (NotEquals<TYPE, FLOAT>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return false;
		return true;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TMat3<TYPE> &a, const TMat3<TYPE> &b, const TYPE tolerance) // Check whether matrices are equal using relative comparison
	{
		for (size_t r = 0; r < 3; r++)
			for (size_t c = 0; c < 3; c++)
				if (NotEquals<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return false;
		return true;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TMat3<TYPE> &a, const TMat3<TYPE> &b, const FLOAT tolerance) // Check whether matrices aren't equal using relative comparison
	{
		for (size_t r = 0; r < 3; r++)
			for (size_t c = 0; c < 3; c++)
				if (NotEquals<TYPE, FLOAT>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return true;
		return false;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TMat3<TYPE> &a, const TMat3<TYPE> &b, const TYPE tolerance) // Check whether matrices aren't equal using relative comparison
	{
		for (size_t r = 0; r < 3; r++)
			for (size_t c = 0; c < 3; c++)
				if (NotEquals<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return true;
		return false;
	}

	template<class TO, class FROM>
	TMat3<TO> Convert(const TMat3<FROM> &m) // Convert to matrix with another data type
	{
		return TMat3<TO>{
			(TO)m._11, (TO)m._12, (TO)m._13,
			(TO)m._21, (TO)m._22, (TO)m._23,
			(TO)m._31, (TO)m._32, (TO)m._33
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> Mat3Identity() // Return identity matrix
	{
		return TMat3<TYPE>{
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> Mat3Diagonal(const TYPE v) // Return diagonal matrix
	{
		return TMat3<TYPE>{
			v, 0, 0,
			0, v, 0,
			0, 0, v
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> Mat3Rotate(const TYPE a) // Return rotation matrix
	{
		TYPE C{ std::cos(a) }, S{ std::sin(a) }, s{ -S };
		return TMat3<TYPE>{
			C, s, 0,
			S, C, 0,
			0, 0, 1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat3<TYPE>> Mat3Scale(const TYPE x, const TYPE y, const TYPE z) // Return scaling matrix
	{
		return TMat3<TYPE>{
			x, 0, 0,
			0, y, 0,
			0, 0, z
		};
	}
}