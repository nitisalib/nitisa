// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Mat3.h"
#include "Vec3.h"
#include "Vec4.h"

namespace ntl
{
	// Row-major order
	template<class TYPE>
	union TMat4
	{
		struct
		{
			TYPE _11, _12, _13, _14; // First row
			TYPE _21, _22, _23, _24; // Second row
			TYPE _31, _32, _33, _34; // Third row
			TYPE _41, _42, _43, _44; // Fourth row
		};
		TVec4<TYPE> Rows[4]; // Rows as vectors
		TYPE Data[16]; // Elements as array
		TMatrix<TYPE, 4, 4> M; // As TMatrix

		TMat4() = default;
		TMat4(const TMat4 &other) = default;
		TMat4(TMat4 &&other) = default;

		// Create with specified elements
		TMat4(
			const TYPE m11, const TYPE m12, const TYPE m13, const TYPE m14,
			const TYPE m21, const TYPE m22, const TYPE m23, const TYPE m24,
			const TYPE m31, const TYPE m32, const TYPE m33, const TYPE m34,
			const TYPE m41, const TYPE m42, const TYPE m43, const TYPE m44) :
			_11{ m11 }, _12{ m12 }, _13{ m13 }, _14{ m14 },
			_21{ m21 }, _22{ m22 }, _23{ m23 }, _24{ m24 },
			_31{ m31 }, _32{ m32 }, _33{ m33 }, _34{ m34 },
			_41{ m41 }, _42{ m42 }, _43{ m43 }, _44{ m44 }
		{

		}

		// Create with specified rows
		TMat4(const TVec4<TYPE> &row1, const TVec4<TYPE> &row2, const TVec4<TYPE> &row3, const TVec4<TYPE> &row4) :
			Rows{ row1, row2, row3, row4 }
		{

		}

		// Create diagonal matrix
		TMat4(const TYPE diagonal, const TYPE other) :
			_11{ diagonal }, _12{ other }, _13{ other }, _14{ other },
			_21{ other }, _22{ diagonal }, _23{ other }, _24{ other },
			_31{ other }, _32{ other }, _33{ diagonal }, _34{ other },
			_41{ other }, _42{ other }, _43{ other }, _44{ diagonal }
		{

		}

		// Create from TMatrix
		TMat4(const TMatrix<TYPE, 4, 4> &m) :
			M{ m }
		{

		}

		// Create from rotation quaternion
		TMat4(const TQuaternion<TYPE> &q):
			_11{ 1 - 2 * (q.Y * q.Y + q.Z * q.Z) },	_12{ 2 * (q.X * q.Y - q.W * q.Z) },		_13{ 2 * (q.X * q.Z + q.W * q.Y) },		_14{ 0 },
			_21{ 2 * (q.X * q.Y + q.W * q.Z) },		_22{ 1 - 2 * (q.X * q.X + q.Z * q.Z) },	_23{ 2 * (q.Y * q.Z - q.W * q.X) },		_24{ 0 },
			_31{ 2 * (q.X * q.Z - q.W * q.Y) },		_32{ 2 * (q.Y * q.Z + q.W * q.X) },		_33{ 1 - 2 * (q.X * q.X + q.Y * q.Y) },	_34{ 0 },
			_41{ 0 },								_42{ 0 },								_43{ 0 },								_44{ 1 }
		{

		}

		TMat4 &operator=(const TMat4 &other) = default;
		TMat4 &operator=(TMat4 &&other) = default;

		TVec4<TYPE> operator[](const size_t row) const // Return specified row. Used when matrix is a constant
		{
			return Rows[row];
		}

		TVec4<TYPE> &operator[](const size_t row) // Return specified row
		{
			return Rows[row];
		}
	};

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TMat4<TYPE> &a, const TMat4<TYPE> &b) // Check whether matrices are equal. Can be used for non-float data types only
	{
		return
			a._11 == b._11 && a._12 == b._12 && a._13 == b._13 && a._14 == b._14 &&
			a._21 == b._21 && a._22 == b._22 && a._23 == b._23 && a._24 == b._24 &&
			a._31 == b._31 && a._32 == b._32 && a._33 == b._33 && a._34 == b._34 &&
			a._41 == b._41 && a._42 == b._42 && a._43 == b._43 && a._44 == b._44;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TMat4<TYPE> &a, const TMat4<TYPE> &b) // Check whether matrices aren't equal. Can be used for non-float data types only
	{
		return
			a._11 != b._11 || a._12 != b._12 || a._13 != b._13 || a._14 != b._14 ||
			a._21 != b._21 || a._22 != b._22 || a._23 != b._23 || a._24 != b._24 ||
			a._31 != b._31 || a._32 != b._32 || a._33 != b._33 || a._34 != b._34 ||
			a._41 != b._41 || a._42 != b._42 || a._43 != b._43 || a._44 != b._44;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator+(const TMat4<TYPE> &m, const TYPE val) // Add matrix and scalar
	{
		return TMat4<TYPE>{
			m._11 + val, m._12 + val, m._13 + val, m._14 + val,
			m._21 + val, m._22 + val, m._23 + val, m._24 + val,
			m._31 + val, m._32 + val, m._33 + val, m._34 + val,
			m._41 + val, m._42 + val, m._43 + val, m._44 + val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator-(const TMat4<TYPE> &m, const TYPE val) // Subtract matrix and scalar
	{
		return TMat4<TYPE>{
			m._11 - val, m._12 - val, m._13 - val, m._14 - val,
			m._21 - val, m._22 - val, m._23 - val, m._24 - val,
			m._31 - val, m._32 - val, m._33 - val, m._34 - val,
			m._41 - val, m._42 - val, m._43 - val, m._44 - val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator*(const TMat4<TYPE> &m, const TYPE val) // Multiply matrix and scalar
	{
		return TMat4<TYPE>{
			m._11 * val, m._12 * val, m._13 * val, m._14 * val,
			m._21 * val, m._22 * val, m._23 * val, m._24 * val,
			m._31 * val, m._32 * val, m._33 * val, m._34 * val,
			m._41 * val, m._42 * val, m._43 * val, m._44 * val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator/(const TMat4<TYPE> &m, const TYPE val) // Divide matrix and scalar
	{
		return TMat4<TYPE>{
			m._11 / val, m._12 / val, m._13 / val, m._14 / val,
			m._21 / val, m._22 / val, m._23 / val, m._24 / val,
			m._31 / val, m._32 / val, m._33 / val, m._34 / val,
			m._41 / val, m._42 / val, m._43 / val, m._44 / val
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator+(const TYPE val, const TMat4<TYPE> &m) // Add scalar and matrix
	{
		return TMat4<TYPE>{
			val + m._11, val + m._12, val + m._13, val + m._14,
			val + m._21, val + m._22, val + m._23, val + m._24,
			val + m._31, val + m._32, val + m._33, val + m._34,
			val + m._41, val + m._42, val + m._43, val + m._44
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator-(const TYPE val, const TMat4<TYPE> &m) // Subtract scalar and matrix
	{
		return TMat4<TYPE>{
			val - m._11, val - m._12, val - m._13, val - m._14,
			val - m._21, val - m._22, val - m._23, val - m._24,
			val - m._31, val - m._32, val - m._33, val - m._34,
			val - m._41, val - m._42, val - m._43, val - m._44
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator*(const TYPE val, const TMat4<TYPE> &m) // Multiply scalar and matrix
	{
		return TMat4<TYPE>{
			val * m._11, val * m._12, val * m._13, val * m._14,
			val * m._21, val * m._22, val * m._23, val * m._24,
			val * m._31, val * m._32, val * m._33, val * m._34,
			val * m._41, val * m._42, val * m._43, val * m._44
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator/(const TYPE val, const TMat4<TYPE> &m) // Divide scalar and matrix
	{
		return TMat4<TYPE>{
			val / m._11, val / m._12, val / m._13, val / m._14,
			val / m._21, val / m._22, val / m._23, val / m._24,
			val / m._31, val / m._32, val / m._33, val / m._34,
			val / m._41, val / m._42, val / m._43, val / m._44
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> &operator+=(TMat4<TYPE> &m, const TYPE val) // Add scalar to matrix
	{
		m._11 += val; m._12 += val; m._13 += val; m._14 += val;
		m._21 += val; m._22 += val; m._23 += val; m._24 += val;
		m._31 += val; m._32 += val; m._33 += val; m._34 += val;
		m._41 += val; m._42 += val; m._43 += val; m._44 += val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> &operator-=(TMat4<TYPE> &m, const TYPE val) // Subtract scalar from matrix
	{
		m._11 -= val; m._12 -= val; m._13 -= val; m._14 -= val;
		m._21 -= val; m._22 -= val; m._23 -= val; m._24 -= val;
		m._31 -= val; m._32 -= val; m._33 -= val; m._34 -= val;
		m._41 -= val; m._42 -= val; m._43 -= val; m._44 -= val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> &operator*=(TMat4<TYPE> &m, const TYPE val) // Multiply matrix by scalar
	{
		m._11 *= val; m._12 *= val; m._13 *= val; m._14 *= val;
		m._21 *= val; m._22 *= val; m._23 *= val; m._24 *= val;
		m._31 *= val; m._32 *= val; m._33 *= val; m._34 *= val;
		m._41 *= val; m._42 *= val; m._43 *= val; m._44 *= val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> &operator/=(TMat4<TYPE> &m, const TYPE val) // Divide matrix by scalar
	{
		m._11 /= val; m._12 /= val; m._13 /= val; m._14 /= val;
		m._21 /= val; m._22 /= val; m._23 /= val; m._24 /= val;
		m._31 /= val; m._32 /= val; m._33 /= val; m._34 /= val;
		m._41 /= val; m._42 /= val; m._43 /= val; m._44 /= val;
		return m;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec3<TYPE>> operator*(const TVec3<TYPE> &v, const TMat4<TYPE> &m) // Multiply vector and matrix
	{
		return TVec3<TYPE>{
			v.X * m._11 + v.Y * m._21 + v.Z * m._31 + m._41,
			v.X * m._12 + v.Y * m._22 + v.Z * m._32 + m._42,
			v.X * m._13 + v.Y * m._23 + v.Z * m._33 + m._43,
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec3<TYPE>> &operator*=(TVec3<TYPE> &v, const TMat4<TYPE> &m) // Multiply vector by matrix
	{
		TYPE x{ v.X * m._11 + v.Y * m._21 + v.Z * m._31 + m._41 };
		TYPE y{ v.X * m._12 + v.Y * m._22 + v.Z * m._32 + m._42 };
		TYPE z{ v.X * m._13 + v.Y * m._23 + v.Z * m._33 + m._43 };
		v.X = x;
		v.Y = y;
		v.Z = z;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec3<TYPE>> operator*(const TMat4<TYPE> &m, const TVec3<TYPE> &v) // Multiply matrix and vector
	{
		return TVec3<TYPE>{
			v.X * m._11 + v.Y * m._12 + v.Z * m._13 + m._14,
			v.X * m._21 + v.Y * m._22 + v.Z * m._23 + m._24,
			v.X * m._31 + v.Y * m._32 + v.Z * m._33 + m._34,
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator*(const TVec4<TYPE> &v, const TMat4<TYPE> &m) // Multiply vector and matrix
	{
		return TVec4<TYPE>{
			v.X * m._11 + v.Y * m._21 + v.Z * m._31 + m._41,
			v.X * m._12 + v.Y * m._22 + v.Z * m._32 + m._42,
			v.X * m._13 + v.Y * m._23 + v.Z * m._33 + m._43,
			1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> &operator*=(TVec4<TYPE> &v, const TMat4<TYPE> &m) // Multiply vector by matrix
	{
		TYPE x{ v.X * m._11 + v.Y * m._21 + v.Z * m._31 + m._41 };
		TYPE y{ v.X * m._12 + v.Y * m._22 + v.Z * m._32 + m._42 };
		TYPE z{ v.X * m._13 + v.Y * m._23 + v.Z * m._33 + m._43 };
		v.X = x;
		v.Y = y;
		v.Z = z;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator*(const TMat4<TYPE> &m, const TVec4<TYPE> &v) // Multiply matrix and vector
	{
		return TVec4<TYPE>{
			v.X * m._11 + v.Y * m._12 + v.Z * m._13 + m._14,
			v.X * m._21 + v.Y * m._22 + v.Z * m._23 + m._24,
			v.X * m._31 + v.Y * m._32 + v.Z * m._33 + m._34,
			1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator*(const TQuaternion<TYPE> &q, const TMat4<TYPE> &m) // Multiply quaternion and matrix
	{
		return TQuaternion<TYPE>{
			q.X * m._11 + q.Y * m._21 + q.Z * m._31 + q.W * m._41,
			q.X * m._12 + q.Y * m._22 + q.Z * m._32 + q.W * m._42,
			q.X * m._13 + q.Y * m._23 + q.Z * m._33 + q.W * m._43,
			q.X * m._14 + q.Y * m._24 + q.Z * m._34 + q.W * m._44,
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> &operator*=(TQuaternion<TYPE> &q, const TMat4<TYPE> &m) // Multiply quaternion by matrix
	{
		TYPE x{ q.X * m._11 + q.Y * m._21 + q.Z * m._31 + q.W * m._41 };
		TYPE y{ q.X * m._12 + q.Y * m._22 + q.Z * m._32 + q.W * m._42 };
		TYPE z{ q.X * m._13 + q.Y * m._23 + q.Z * m._33 + q.W * m._43 };
		TYPE w{ q.X * m._14 + q.Y * m._24 + q.Z * m._34 + q.W * m._44 };
		q.X = x;
		q.Y = y;
		q.Z = z;
		q.W = w;
		return q;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator*(const TMat4<TYPE> &m, const TQuaternion<TYPE> &q) // Multiply matrix and quaternion
	{
		return TQuaternion<TYPE>{
			q.X * m._11 + q.Y * m._12 + q.Z * m._13 + q.W * m._14,
			q.X * m._21 + q.Y * m._22 + q.Z * m._23 + q.W * m._24,
			q.X * m._31 + q.Y * m._32 + q.Z * m._33 + q.W * m._34,
			q.X * m._41 + q.Y * m._42 + q.Z * m._43 + q.W * m._44,
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator+(const TMat4<TYPE> &a, const TMat4<TYPE> &b) // Add matrices
	{
		return TMat4<TYPE>{
			a._11 + b._11, a._12 + b._12, a._13 + b._13, a._14 + b._14,
			a._21 + b._21, a._22 + b._22, a._23 + b._23, a._24 + b._24,
			a._31 + b._31, a._32 + b._32, a._33 + b._33, a._34 + b._34,
			a._41 + b._41, a._42 + b._42, a._43 + b._43, a._44 + b._44
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator-(const TMat4<TYPE> &a, const TMat4<TYPE> &b) // Subtract matrices
	{
		return TMat4<TYPE>{
			a._11 - b._11, a._12 - b._12, a._13 - b._13, a._14 - b._14,
			a._21 - b._21, a._22 - b._22, a._23 - b._23, a._24 - b._24,
			a._31 - b._31, a._32 - b._32, a._33 - b._33, a._34 - b._34,
			a._41 - b._41, a._42 - b._42, a._43 - b._43, a._44 - b._44
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator*(const TMat4<TYPE> &a, const TMat4<TYPE> &b) // Multiply matrices
	{
		return TMat4<TYPE>{
			a._11 * b._11 + a._12 * b._21 + a._13 * b._31 + a._14 * b._41,
			a._11 * b._12 + a._12 * b._22 + a._13 * b._32 + a._14 * b._42,
			a._11 * b._13 + a._12 * b._23 + a._13 * b._33 + a._14 * b._43,
			a._11 * b._14 + a._12 * b._24 + a._13 * b._34 + a._14 * b._44,

			a._21 * b._11 + a._22 * b._21 + a._23 * b._31 + a._24 * b._41,
			a._21 * b._12 + a._22 * b._22 + a._23 * b._32 + a._24 * b._42,
			a._21 * b._13 + a._22 * b._23 + a._23 * b._33 + a._24 * b._43,
			a._21 * b._14 + a._22 * b._24 + a._23 * b._34 + a._24 * b._44,

			a._31 * b._11 + a._32 * b._21 + a._33 * b._31 + a._34 * b._41,
			a._31 * b._12 + a._32 * b._22 + a._33 * b._32 + a._34 * b._42,
			a._31 * b._13 + a._32 * b._23 + a._33 * b._33 + a._34 * b._43,
			a._31 * b._14 + a._32 * b._24 + a._33 * b._34 + a._34 * b._44,

			a._41 * b._11 + a._42 * b._21 + a._43 * b._31 + a._44 * b._41,
			a._41 * b._12 + a._42 * b._22 + a._43 * b._32 + a._44 * b._42,
			a._41 * b._13 + a._42 * b._23 + a._43 * b._33 + a._44 * b._43,
			a._41 * b._14 + a._42 * b._24 + a._43 * b._34 + a._44 * b._44
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator+=(TMat4<TYPE> &a, const TMat4<TYPE> &b) // Add matrix to matrix
	{
		a._11 += b._11; a._12 += b._12; a._13 += b._13; a._14 += b._14;
		a._21 += b._21; a._22 += b._22; a._23 += b._23; a._24 += b._24;
		a._31 += b._31; a._32 += b._32; a._33 += b._33; a._34 += b._34;
		a._41 += b._41; a._42 += b._42; a._43 += b._43; a._44 += b._44;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> operator-=(TMat4<TYPE> &a, const TMat4<TYPE> &b) // Subtract matrix from matrix
	{
		a._11 -= b._11; a._12 -= b._12; a._13 -= b._13; a._14 -= b._14;
		a._21 -= b._21; a._22 -= b._22; a._23 -= b._23; a._24 -= b._24;
		a._31 -= b._31; a._32 -= b._32; a._33 -= b._33; a._34 -= b._34;
		a._41 -= b._41; a._42 -= b._42; a._43 -= b._43; a._44 -= b._44;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> &operator*=(TMat4<TYPE> &a, const TMat4<TYPE> &b) // Multiply matrix by matrix
	{
		TYPE m11{ a._11 * b._11 + a._12 * b._21 + a._13 * b._31 + a._14 * b._41 };
		TYPE m12{ a._11 * b._12 + a._12 * b._22 + a._13 * b._32 + a._14 * b._42 };
		TYPE m13{ a._11 * b._13 + a._12 * b._23 + a._13 * b._33 + a._14 * b._43 };
		TYPE m14{ a._11 * b._14 + a._12 * b._24 + a._13 * b._34 + a._14 * b._44 };

		TYPE m21{ a._21 * b._11 + a._22 * b._21 + a._23 * b._31 + a._24 * b._41 };
		TYPE m22{ a._21 * b._12 + a._22 * b._22 + a._23 * b._32 + a._24 * b._42 };
		TYPE m23{ a._21 * b._13 + a._22 * b._23 + a._23 * b._33 + a._24 * b._43 };
		TYPE m24{ a._21 * b._14 + a._22 * b._24 + a._23 * b._34 + a._24 * b._44 };

		TYPE m31{ a._31 * b._11 + a._32 * b._21 + a._33 * b._31 + a._34 * b._41 };
		TYPE m32{ a._31 * b._12 + a._32 * b._22 + a._33 * b._32 + a._34 * b._42 };
		TYPE m33{ a._31 * b._13 + a._32 * b._23 + a._33 * b._33 + a._34 * b._43 };
		TYPE m34{ a._31 * b._14 + a._32 * b._24 + a._33 * b._34 + a._34 * b._44 };

		TYPE m41{ a._41 * b._11 + a._42 * b._21 + a._43 * b._31 + a._44 * b._41 };
		TYPE m42{ a._41 * b._12 + a._42 * b._22 + a._43 * b._32 + a._44 * b._42 };
		TYPE m43{ a._41 * b._13 + a._42 * b._23 + a._43 * b._33 + a._44 * b._43 };
		TYPE m44{ a._41 * b._14 + a._42 * b._24 + a._43 * b._34 + a._44 * b._44 };

		a._11 = m11; a._12 = m12; a._13 = m13; a._14 = m14;
		a._21 = m21; a._22 = m22; a._23 = m23; a._24 = m24;
		a._31 = m31; a._32 = m32; a._33 = m33; a._34 = m34;
		a._41 = m41; a._42 = m42; a._43 = m43; a._44 = m44;
		return a;
	}

	template<class TYPE>
	TMat3<TYPE> Minor(const TMat4<TYPE> &m, const size_t row, const size_t col) // Return matrix minor of specified row and column
	{
		return Minor<TYPE, 4, 4>(m.M, row, col);
	}

	template<class TYPE>
	void Transpose(TMat4<TYPE> &m) // Transpose matrix
	{
		Swap<TYPE>(m._21, m._12);
		Swap<TYPE>(m._31, m._13);
		Swap<TYPE>(m._32, m._23);
		Swap<TYPE>(m._41, m._14);
		Swap<TYPE>(m._42, m._24);
		Swap<TYPE>(m._43, m._34);
	}

	template<class TYPE>
	TMat4<TYPE> Transposed(const TMat4<TYPE> &m) // Return transposed matrix
	{
		return TMat4<TYPE>{
			m._11, m._21, m._31, m._41,
			m._12, m._22, m._32, m._42,
			m._13, m._23, m._33, m._43,
			m._14, m._24, m._34, m._44
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Determinant(const TMat4<TYPE> &m) // Return matrix determinant. Can be used with arithmetic data types only
	{
		return Determinant<TYPE, 4>(m.M);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Inverse(TMat4<TYPE> &m) // Inverse matrix. Can be used with arithmetic data types only
	{
		Inverse<TYPE, 4>(m.M);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Inversed(const TMat4<TYPE> &m) // Return inversed matrix. Can be used with arithmetic data types only
	{
		return TMat4<TYPE>{Inversed<TYPE, 4>(m.M) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Identity(TMat4<TYPE> &m) // Makes matrix identity. Can be used with arithmetic data types only
	{
		m._11 = 1; m._12 = 0; m._13 = 0; m._14 = 0;
		m._21 = 0; m._22 = 1; m._23 = 0; m._24 = 0;
		m._31 = 0; m._32 = 0; m._33 = 1; m._34 = 0;
		m._41 = 0; m._42 = 0; m._43 = 0; m._44 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Diagonal(TMat4<TYPE> &m, const TYPE v) // Makes matrix diagonal. Can be used with arithmetic data types only
	{
		m._11 = v; m._12 = 0; m._13 = 0; m._14 = 0;
		m._21 = 0; m._22 = v; m._23 = 0; m._24 = 0;
		m._31 = 0; m._32 = 0; m._33 = v; m._34 = 0;
		m._41 = 0; m._42 = 0; m._43 = 0; m._44 = v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Translate(TMat4<TYPE> &m, const TYPE x, const TYPE y, const TYPE z) // Makes translation matrix. Can be used with arithmetic data types only
	{
		m._11 = 1; m._12 = 0; m._13 = 0; m._14 = x;
		m._21 = 0; m._22 = 1; m._23 = 0; m._24 = y;
		m._31 = 0; m._32 = 0; m._33 = 1; m._34 = z;
		m._41 = 0; m._42 = 0; m._43 = 0; m._44 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> RotateX(TMat4<TYPE> &m, const TYPE a) // Makes rotation around X-axis matrix. Can be used with arithmetic data types only
	{
		TYPE C{ std::cos(a) }, S{ std::sin(a) }, s{ -S };
		m._11 = 1; m._12 = 0; m._13 = 0; m._14 = 0;
		m._21 = 0; m._22 = C; m._23 = s; m._24 = 0;
		m._31 = 0; m._32 = S; m._33 = C; m._34 = 0;
		m._41 = 0; m._42 = 0; m._43 = 0; m._44 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> RotateY(TMat4<TYPE> &m, const TYPE a) // Makes rotation around Y-axis matrix. Can be used with arithmetic data types only
	{
		TYPE C{ std::cos(a) }, S{ std::sin(a) }, s{ -S };
		m._11 = C; m._12 = 0; m._13 = S; m._14 = 0;
		m._21 = 0; m._22 = 1; m._23 = 0; m._24 = 0;
		m._31 = s; m._32 = 0; m._33 = C; m._34 = 0;
		m._41 = 0; m._42 = 0; m._43 = 0; m._44 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> RotateZ(TMat4<TYPE> &m, const TYPE a) // Makes rotation around Z-axis matrix. Can be used with arithmetic data types only
	{
		TYPE C{ std::cos(a) }, S{ std::sin(a) }, s{ -S };
		m._11 = C; m._12 = s; m._13 = 0; m._14 = 0;
		m._21 = S; m._22 = C; m._23 = 0; m._24 = 0;
		m._31 = 0; m._32 = 0; m._33 = 1; m._34 = 0;
		m._41 = 0; m._42 = 0; m._43 = 0; m._44 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Scale(TMat4<TYPE> &m, const TYPE x, const TYPE y, const TYPE z) // Makes scaling matrix. Can be used with arithmetic data types only
	{
		m._11 = x; m._12 = 0; m._13 = 0; m._14 = 0;
		m._21 = 0; m._22 = y; m._23 = 0; m._24 = 0;
		m._31 = 0; m._32 = 0; m._33 = z; m._34 = 0;
		m._41 = 0; m._42 = 0; m._43 = 0; m._44 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Euler(TMat4<TYPE> &m, const TYPE roll, const TYPE pitch, const TYPE yaw) // Makes matrix with Euler angles. Can be used with arithmetic data types only
	{
		TYPE sr{ std::sin(roll) }, cr{ std::cos(roll) };
		TYPE sp{ std::sin(pitch) }, cp{ std::cos(pitch) };
		TYPE sy{ std::sin(yaw) }, cy{ std::cos(yaw) };
		m._11 = cr * cy - sr * sp * sy;	m._12 = -sr * cp;	m._13 = cr * sy + sr * sp * cy;	m._14 = 0;
		m._21 = sr * cy + cr * sp * sy;	m._22 = cr * cp;	m._23 = sr * sy - cr * sp * cy;	m._24 = 0;
		m._31 = -cp * sy;				m._32 = sp;			m._33 = cp * cy;				m._34 = 0;
		m._41 = 0;						m._42 = 0;			m._43 = 0;						m._44 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Ortho(TMat4<TYPE> &m, const TYPE l, const TYPE t, const TYPE r, const TYPE b, const TYPE n, const TYPE f) // Makes orthographic projection matrix. Can be used with arithmetic data types only
	{
		m._11 = 2 / (r - l);	m._12 = 0;				m._13 = 0;				m._14 = (l + r) / (l - r);
		m._21 = 0;				m._22 = 2 / (t - b);	m._23 = 0;				m._24 = (b + t) / (b - t);
		m._31 = 0;				m._32 = 0;				m._33 = 2 / (n - f);	m._34 = (n + f) / (n - f);
		m._41 = 0;				m._42 = 0;				m._43 = 0;				m._44 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Frustum(TMat4<TYPE> &m, const TYPE l, const TYPE t, const TYPE r, const TYPE b, const TYPE n, const TYPE f) // Makes perspective projection matrix. Can be used with arithmetic data types only
	{
		m._11 = 2 * n / (r - l);	m._12 = 0;					m._13 = (r + l) / (r - l);	m._14 = 0;
		m._21 = 0;					m._22 = 2 * n / (t - b);	m._23 = (t + b) / (t - b);	m._24 = 0;
		m._31 = 0;					m._32 = 0;					m._33 = (n + f) / (n - f);	m._34 = 2 * n * f / (n - f);
		m._41 = 0;					m._42 = 0;					m._43 = -1;					m._44 = 0;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Perspective(TMat4<TYPE> &m, const TYPE fov, const TYPE aspect, const TYPE n, const TYPE f) // Makes perspective projection matrix. Can be used with arithmetic data types only
	{
		TYPE q{ 1 / std::tan(fov / 2) }, a{ q / aspect }, b{ (n + f) / (n - f) }, c{ 2 * n * f / (n - f) };
		m._11 = a;	m._12 = 0;	m._13 = 0;	m._14 = 0;
		m._21 = 0;	m._22 = q;	m._23 = 0;	m._24 = 0;
		m._31 = 0;	m._32 = 0;	m._33 = b;	m._34 = c;
		m._41 = 0;	m._42 = 0;	m._43 = -1;	m._44 = 0;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> LookAt(TMat4<TYPE> &m, const TVec3<TYPE> &camera, const TVec3<TYPE> &target, const TVec3<TYPE> &up) // Makes "look at" matrix. Can be used with arithmetic data types only
	{
		TVec3<TYPE> f{ target }, s{ Normalized<TYPE>(f ^ up) }, u{ Normalized<TYPE>(s ^ f) };
		m._11 = s.X;	m._12 = s.Y;	m._13 = s.Z;	m._14 = -(s * camera);
		m._21 = u.X;	m._22 = u.Y;	m._23 = u.Z;	m._24 = -(u * camera);
		m._31 = -f.X;	m._32 = -f.Y;	m._33 = -f.Z;	m._34 = f * camera;
		m._41 = 0;		m._42 = 0;		m._43 = 0;		m._44 = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> LookAt(TMat4<TYPE> &m, const TVec4<TYPE> &camera, const TVec4<TYPE> &target, const TVec4<TYPE> &up) // Makes "look at" matrix. Can be used with arithmetic data types only
	{
		LookAt<TYPE>(m, camera.V3, target.V3, up.V3);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> LookAt(TMat4<TYPE> &m, const TQuaternion<TYPE> &camera, const TQuaternion<TYPE> &target, const TQuaternion<TYPE> &up) // Makes "look at" matrix. Can be used with arithmetic data types only
	{
		LookAt<TYPE>(m, camera.V3, target.V3, up.V3);
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TMat4<TYPE> &a, const TMat4<TYPE> &b) // Compare whether matrices are equal
	{
		for (size_t r = 0; r < 4; r++)
			for (size_t c = 0; c < 4; c++)
				if (a.Rows[r].Data[c] != b.Rows[r].Data[c])
					return false;
		return true;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TMat4<TYPE> &a, const TMat4<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether matrices are equal
	{
		for (size_t r = 0; r < 4; r++)
			for (size_t c = 0; c < 4; c++)
				if (IsNotEqual<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return false;
		return true;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TMat4<TYPE> &a, const TMat4<TYPE> &b) // Compare whether matrices aren't equal
	{
		for (size_t r = 0; r < 4; r++)
			for (size_t c = 0; c < 4; c++)
				if (a.Rows[r].Data[c] != b.Rows[r].Data[c])
					return true;
		return false;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TMat4<TYPE> &a, const TMat4<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether matrices aren't equal
	{
		for (size_t r = 0; r < 4; r++)
			for (size_t c = 0; c < 4; c++)
				if (IsNotEqual<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return true;
		return false;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TMat4<TYPE> &a, const TMat4<TYPE> &b, const FLOAT tolerance) // Check whether matrices are equal using relative comparison
	{
		for (size_t r = 0; r < 4; r++)
			for (size_t c = 0; c < 4; c++)
				if (NotEquals<TYPE, FLOAT>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return false;
		return true;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TMat4<TYPE> &a, const TMat4<TYPE> &b, const TYPE tolerance) // Check whether matrices are equal using relative comparison
	{
		for (size_t r = 0; r < 4; r++)
			for (size_t c = 0; c < 4; c++)
				if (NotEquals<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return false;
		return true;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TMat4<TYPE> &a, const TMat4<TYPE> &b, const FLOAT tolerance) // Check whether matrices aren't equal using relative comparison
	{
		for (size_t r = 0; r < 4; r++)
			for (size_t c = 0; c < 4; c++)
				if (NotEquals<TYPE, FLOAT>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return true;
		return false;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TMat4<TYPE> &a, const TMat4<TYPE> &b, const TYPE tolerance) // Check whether matrices aren't equal using relative comparison
	{
		for (size_t r = 0; r < 4; r++)
			for (size_t c = 0; c < 4; c++)
				if (NotEquals<TYPE>(a.Rows[r].Data[c], b.Rows[r].Data[c], tolerance))
					return true;
		return false;
	}

	template<class TO, class FROM>
	TMat4<TO> Convert(const TMat4<FROM> &m) // Convert to matrix with another data type
	{
		return TMat4<TO>{
			(TO)m._11, (TO)m._12, (TO)m._13, (TO)m._14,
			(TO)m._21, (TO)m._22, (TO)m._23, (TO)m._24,
			(TO)m._31, (TO)m._32, (TO)m._33, (TO)m._34,
			(TO)m._41, (TO)m._42, (TO)m._43, (TO)m._44,
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4Identity() // Return identity matrix
	{
		return TMat4<TYPE>{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4Diagonal(const TYPE v) // Return diagonal matrix
	{
		return TMat4<TYPE>{
			v, 0, 0, 0,
			0, v, 0, 0,
			0, 0, v, 0,
			0, 0, 0, v
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4Translate(const TYPE x, const TYPE y, const TYPE z) // Return translation matrix
	{
		return TMat4<TYPE>{
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4RotateX(const TYPE a) // Return rotation around X-axis matrix
	{
		TYPE C{ std::cos(a) }, S{ std::sin(a) }, s{ -S };
		return TMat4<TYPE>{
			1, 0, 0, 0,
			0, C, s, 0,
			0, S, C, 0,
			0, 0, 0, 1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4RotateY(const TYPE a) // Return rotation around Y-axis matrix
	{
		TYPE C{ std::cos(a) }, S{ std::sin(a) }, s{ -S };
		return TMat4<TYPE>{
			C, 0, S, 0,
			0, 1, 0, 0,
			s, 0, C, 0,
			0, 0, 0, 1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4RotateZ(const TYPE a) // Return rotation around Z-axis matrix
	{
		TYPE C{ std::cos(a) }, S{ std::sin(a) }, s{ -S };
		return TMat4<TYPE>{
			C, s, 0, 0,
			S, C, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4Scale(const TYPE x, const TYPE y, const TYPE z) // Return scaling matrix
	{
		return TMat4<TYPE>{
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4Euler(const TYPE roll, const TYPE pitch, const TYPE yaw) // Return matrix with Euler angles
	{
		TYPE sr{ std::sin(roll) }, cr{ std::cos(roll) };
		TYPE sp{ std::sin(pitch) }, cp{ std::cos(pitch) };
		TYPE sy{ std::sin(yaw) }, cy{ std::cos(yaw) };
		return TMat4<TYPE>{
			cr * cy - sr * sp * sy,		-sr * cp,	cr * sy + sr * sp * cy,		0,
			sr * cy + cr * sp * sy,		cr * cp,	sr * sy - cr * sp * cy,		0,
			-cp * sy,					sp,			cp * cy,					0,
			0,							0,			0,							1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4Ortho(const TYPE l, const TYPE t, const TYPE r, const TYPE b, const TYPE n, const TYPE f) // Return orthographic projection matrix
	{
		return TMat4<TYPE>{
			2 / (r - l),	0,				0,				(l + r) / (l - r),
			0,				2 / (t - b),	0,				(b + t) / (b - t),
			0,				0,				2 / (n - f),	(n + f) / (n - f),
			0,				0,				0,				1
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4Frustum(const TYPE l, const TYPE t, const TYPE r, const TYPE b, const TYPE n, const TYPE f) // Return perspective projection matrix
	{
		return TMat4<TYPE>{
			2 * n / (r - l),	0,					(r + l) / (r - l),	0,
			0,					2 * n / (t - b),	(t + b) / (t - b),	0,
			0,					0,					(n + f) / (n - f),	2 * n * f / (n - f),
			0,					0,					-1,					0
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4Perspective(const TYPE fov, const TYPE aspect, const TYPE n, const TYPE f) // Return perspective projection matrix
	{
		TYPE q{ 1 / std::tan(fov / 2) }, a{ q / aspect }, b{ (n + f) / (n - f) }, c{ 2 * n * f / (n - f) };
		return TMat4<TYPE>{
			a,	0,	0,	0,
			0,	q,	0,	0,
			0,	0,	b,	c,
			0,	0,	-1,	0
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4LookAt(const TVec3<TYPE> &camera, const TVec3<TYPE> &target, const TVec3<TYPE> &up) // Return "look at" matrix
	{
		TVec3<TYPE> f{ target }, s{ Normalized<TYPE>(f ^ up) }, u{ Normalized<TYPE>(s ^ f) };
		return TMat4<TYPE>{
			s.X,	s.Y,	s.Z,	-(s * camera),
			u.X,	u.Y,	u.Z,	-(u * camera),
			-f.X,	-f.Y,	-f.Z,	f * camera,
			0,		0,		0,		1,
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4LookAt(const TVec4<TYPE> &camera, const TVec4<TYPE> &target, const TVec4<TYPE> &up) // Return "look at" matrix
	{
		return Mat4LookAt<TYPE>(camera.V3, target.V3, up.V3);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMat4<TYPE>> Mat4LookAt(const TQuaternion<TYPE> &camera, const TQuaternion<TYPE> &target, const TQuaternion<TYPE> &up) // Return "look at" matrix
	{
		return Mat4LookAt<TYPE>(camera.V3, target.V3, up.V3);
	}
}