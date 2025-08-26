// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Types.h"

namespace ntl
{
	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b) // Check whether matrices are equal. Can be used for non-float data types only
	{
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				if (a.Data[row][col] != b.Data[row][col])
					return false;
		return true;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b) // Check whether matrices aren't equal. Can be used for non-float data types only
	{
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				if (a.Data[row][col] != b.Data[row][col])
					return true;
		return false;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> operator+(const TMatrix<TYPE, ROWS, COLUMNS> &m, const TYPE val) // Add matrix and scalar
	{
		TMatrix<TYPE, ROWS, COLUMNS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[row][col] = m.Data[row][col] + val;
		return r;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> operator-(const TMatrix<TYPE, ROWS, COLUMNS> &m, const TYPE val) // Subtract matrix and scalar
	{
		TMatrix<TYPE, ROWS, COLUMNS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[row][col] = m.Data[row][col] - val;
		return r;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> operator*(const TMatrix<TYPE, ROWS, COLUMNS> &m, const TYPE val) // Multiply matrix and scalar
	{
		TMatrix<TYPE, ROWS, COLUMNS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[row][col] = m.Data[row][col] * val;
		return r;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> operator/(const TMatrix<TYPE, ROWS, COLUMNS> &m, const TYPE val) // Divide matrix and scalar
	{
		TMatrix<TYPE, ROWS, COLUMNS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[row][col] = m.Data[row][col] / val;
		return r;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> operator+(const TYPE val, const TMatrix<TYPE, ROWS, COLUMNS> &m) // Add scalar and matrix
	{
		TMatrix<TYPE, ROWS, COLUMNS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[row][col] = val + m.Data[row][col];
		return r;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> operator-(const TYPE val, const TMatrix<TYPE, ROWS, COLUMNS> &m) // Subtract scalar and matrix
	{
		TMatrix<TYPE, ROWS, COLUMNS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[row][col] = val - m.Data[row][col];
		return r;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> operator*(const TYPE val, const TMatrix<TYPE, ROWS, COLUMNS> &m) // Multiply scalar and matrix
	{
		TMatrix<TYPE, ROWS, COLUMNS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[row][col] = val * m.Data[row][col];
		return r;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> operator/(const TYPE val, const TMatrix<TYPE, ROWS, COLUMNS> &m) // Divide scalar and matrix
	{
		TMatrix<TYPE, ROWS, COLUMNS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[row][col] = val / m.Data[row][col];
		return r;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> &operator+=(TMatrix<TYPE, ROWS, COLUMNS> &m, const TYPE val) // Add scalar to matrix
	{
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				m.Data[row][col] += val;
		return m;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> &operator-=(TMatrix<TYPE, ROWS, COLUMNS> &m, const TYPE val) // Subtract scalar from matrix
	{
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				m.Data[row][col] -= val;
		return m;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> &operator*=(TMatrix<TYPE, ROWS, COLUMNS> &m, const TYPE val) // Multiply matrix by scalar
	{
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				m.Data[row][col] *= val;
		return m;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> &operator/=(TMatrix<TYPE, ROWS, COLUMNS> &m, const TYPE val) // Divide matrix by scalar
	{
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				m.Data[row][col] /= val;
		return m;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> operator+(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b) // Add matrices
	{
		TMatrix<TYPE, ROWS, COLUMNS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[row][col] = a.Data[row][col] + b.Data[row][col];
		return r;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> operator-(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b) // Subtract matrices
	{
		TMatrix<TYPE, ROWS, COLUMNS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[row][col] = a.Data[row][col] - b.Data[row][col];
		return r;
	}

	template<class TYPE, size_t ROWS_A, size_t COLUMNS_A, size_t COLUMNS_B>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS_A, COLUMNS_B>> operator*(const TMatrix<TYPE, ROWS_A, COLUMNS_A> &a, const TMatrix<TYPE, COLUMNS_A, COLUMNS_B> &b) // Multiply matrices
	{
		TMatrix<TYPE, ROWS_A, COLUMNS_B> r;
		for (size_t row = 0; row < ROWS_A; row++)
			for (size_t col = 0; col < COLUMNS_B; col++)
			{
				r.Data[row][col] = 0;
				for (size_t k = 0; k < COLUMNS_A; k++)
					r.Data[row][col] += a.Data[row][k] * b.Data[k][col];
			}
		return r;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> &operator+=(TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b) // Add matrix to matrix
	{
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				a.Data[row][col] += b.Data[row][col];
		return a;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> &operator-=(TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b) // Subtract matrix from matrix
	{
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				a.Data[row][col] -= b.Data[row][col];
		return a;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TMatrix<TYPE, ROWS, COLUMNS>> &operator*=(TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, COLUMNS, COLUMNS> &b) // Multiply matrix by matrix
	{
		TMatrix<TYPE, ROWS, COLUMNS> t;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
			{
				t.Data[row][col] = 0;
				for (size_t k = 0; k < COLUMNS; k++)
					t.Data[row][col] += a.Data[row][k] * b.Data[k][col];
			}
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				a.Data[row][col] = t.Data[row][col];
		return a;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<(ROWS == 2 && COLUMNS == 2), TYPE> Minor(const TMatrix<TYPE, ROWS, COLUMNS> &m, const size_t row, const size_t col) // Return matrix minor of specified row and column
	{
		return m.Data[(row + 1) % 2][(col + 1) % 2];
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<(ROWS > 1 && COLUMNS > 1 && (ROWS > 2 || COLUMNS > 2)), TMatrix<TYPE, ROWS - 1, COLUMNS - 1>> Minor(const TMatrix<TYPE, ROWS, COLUMNS> &m, const size_t row, const size_t col) // Return matrix minor of specified row and column
	{
		TMatrix<TYPE, ROWS - 1, COLUMNS - 1> result;
		size_t i{ 0 }, j{ 0 };
		for (size_t r = 0; r < ROWS; r++)
		{
			if (r == row)
				continue;
			j = 0;
			for (size_t c = 0; c < COLUMNS; c++)
				if (c != col)
					result.Data[i][j++] = m.Data[r][c];
			i++;
		}
		return result;
	}

	template<class TYPE, size_t SIZE>
	void Transpose(TMatrix<TYPE, SIZE, SIZE> &m) // Transpose matrix
	{
		for (size_t row = 0; row < SIZE; row++)
			for (size_t col = 0; col < row; col++)
				Swap<TYPE>(m.Data[row][col], m.Data[col][row]);
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	TMatrix<TYPE, COLUMNS, ROWS> Transposed(const TMatrix<TYPE, ROWS, COLUMNS> &m) // Return transposed matrix
	{
		TMatrix<TYPE, COLUMNS, ROWS> r;
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				r.Data[col][row] = m.Data[row][col];
		return r;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<SIZE == 1 && std::is_arithmetic_v<TYPE>, TYPE> Determinant(const TMatrix<TYPE, SIZE, SIZE> &m) // Return matrix determinant. Can be used with arithmetic data types only
	{
		return m.Data[0][0];
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<SIZE == 2 && std::is_arithmetic_v<TYPE>, TYPE> Determinant(const TMatrix<TYPE, SIZE, SIZE> &m) // Return matrix determinant. Can be used with arithmetic data types only
	{
		return m.Data[0][0] * m.Data[1][1] - m.Data[0][1] * m.Data[1][0];
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<SIZE == 3 && std::is_arithmetic_v<TYPE>, TYPE> Determinant(const TMatrix<TYPE, SIZE, SIZE> &m) // Return matrix determinant. Can be used with arithmetic data types only
	{
		return
			m.Data[0][0] * m.Data[1][1] * m.Data[2][2] -
			m.Data[0][0] * m.Data[1][2] * m.Data[2][1] -
			m.Data[0][1] * m.Data[1][0] * m.Data[2][2] +
			m.Data[0][1] * m.Data[1][2] * m.Data[2][0] +
			m.Data[0][2] * m.Data[1][0] * m.Data[2][1] -
			m.Data[0][2] * m.Data[1][1] * m.Data[2][0];
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<(SIZE > 3) && std::is_arithmetic_v<TYPE>, TYPE> Determinant(const TMatrix<TYPE, SIZE, SIZE> &m) // Return matrix determinant. Can be used with arithmetic data types only
	{
		TYPE result{ 0 }, k{ 1 };
		for (size_t j = 0; j < SIZE; j++)
		{
			result += k * m.Data[0][j] * Determinant<TYPE, SIZE - 1>(Minor<TYPE, SIZE, SIZE>(m, 0, j));
			k = -k;
		}
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<SIZE == 1 && std::is_arithmetic_v<TYPE>, void> Inverse(TMatrix<TYPE, SIZE, SIZE> &m) // Inverse matrix. Can be used with arithmetic data types only
	{
		
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<SIZE == 2 && std::is_arithmetic_v<TYPE>, void> Inverse(TMatrix<TYPE, SIZE, SIZE> &m) // Inverse matrix. Can be used with arithmetic data types only
	{
		TMatrix<TYPE, SIZE, SIZE> t;
		TYPE d{ Determinant<TYPE, SIZE>(m) };
		for (size_t row = 0; row < SIZE; row++)
			for (size_t col = 0; col < SIZE; col++)
				t.Data[row][col] = Minor<TYPE, SIZE, SIZE>(m, row, col) * (((row + col) % 2 == 0) ? 1 : -1);
		Transpose<TYPE, SIZE>(t);
		for (size_t row = 0; row < SIZE; row++)
			for (size_t col = 0; col < SIZE; col++)
				m.Data[row][col] = t.Data[row][col] / d;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<(SIZE > 2) && std::is_arithmetic_v<TYPE>, void> Inverse(TMatrix<TYPE, SIZE, SIZE> &m) // Inverse matrix. Can be used with arithmetic data types only
	{
		TMatrix<TYPE, SIZE, SIZE> t;
		TYPE d{ Determinant<TYPE, SIZE>(m) };
		for (size_t row = 0; row < SIZE; row++)
			for (size_t col = 0; col < SIZE; col++)
				t.Data[row][col] = Determinant<TYPE, SIZE - 1>(Minor<TYPE, SIZE, SIZE>(m, row, col)) * (((row + col) % 2 == 0) ? 1 : -1);
		Transpose<TYPE, SIZE>(t);
		for (size_t row = 0; row < SIZE; row++)
			for (size_t col = 0; col < SIZE; col++)
				m.Data[row][col] = t.Data[row][col] / d;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<SIZE == 1 && std::is_arithmetic_v<TYPE>, TMatrix<TYPE, SIZE, SIZE>> Inversed(const TMatrix<TYPE, SIZE, SIZE> &m) // Return inversed matrix. Can be used with arithmetic data types only
	{
		return m;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<SIZE == 2 && std::is_arithmetic_v<TYPE>, TMatrix<TYPE, SIZE, SIZE>> Inversed(const TMatrix<TYPE, SIZE, SIZE> &m) // Return inversed matrix. Can be used with arithmetic data types only
	{
		TMatrix<TYPE, SIZE, SIZE> result;
		TYPE d{ Determinant<TYPE, SIZE>(m) };
		for (size_t row = 0; row < SIZE; row++)
			for (size_t col = 0; col < SIZE; col++)
				result.Data[row][col] = Minor<TYPE, SIZE, SIZE>(m, row, col) * (((row + col) % 2 == 0) ? 1 : -1) / d;
		return Transposed<TYPE, SIZE>(result);
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<(SIZE > 2) && std::is_arithmetic_v<TYPE>, TMatrix<TYPE, SIZE, SIZE>> Inversed(const TMatrix<TYPE, SIZE, SIZE> &m) // Return inversed matrix. Can be used with arithmetic data types only
	{
		TMatrix<TYPE, SIZE, SIZE> result;
		TYPE d{ Determinant<TYPE, SIZE>(m) };
		for (size_t row = 0; row < SIZE; row++)
			for (size_t col = 0; col < SIZE; col++)
				result.Data[row][col] = Determinant<TYPE, SIZE - 1>(Minor<TYPE, SIZE, SIZE>(m, row, col)) * (((row + col) % 2 == 0) ? 1 : -1) / d;
		return Transposed<TYPE, SIZE>(result);
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Identity(TMatrix<TYPE, ROWS, COLUMNS> &m) // Makes matrix identity. Can be used with arithmetic data types only
	{
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				m.Data[row][col] = (row == col) ? 1 : 0;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Diagonal(TMatrix<TYPE, ROWS, COLUMNS> &m, const TYPE diagonal) // Makes matrix diagonal. Can be used with arithmetic data types only
	{
		for (size_t row = 0; row < ROWS; row++)
			for (size_t col = 0; col < COLUMNS; col++)
				m.Data[row][col] = (row == col) ? diagonal : 0;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b) // Compare whether matrices are equal
	{
		for (size_t r = 0; r < ROWS; r++)
			for (size_t c = 0; c < COLUMNS; c++)
				if (a.Data[r][c] != b.Data[r][c])
					return false;
		return true;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether matrices are equal
	{
		for (size_t r = 0; r < ROWS; r++)
			for (size_t c = 0; c < COLUMNS; c++)
				if (IsNotEqual<TYPE>(a.Data[r][c], b.Data[r][c], tolerance))
					return false;
		return true;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b) // Compare whether matrices aren't equal
	{
		for (size_t r = 0; r < ROWS; r++)
			for (size_t c = 0; c < COLUMNS; c++)
				if (a.Data[r][c] != b.Data[r][c])
					return true;
		return false;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether matrices aren't equal
	{
		for (size_t r = 0; r < ROWS; r++)
			for (size_t c = 0; c < COLUMNS; c++)
				if (IsNotEqual<TYPE>(a.Data[r][c], b.Data[r][c], tolerance))
					return true;
		return false;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b, const FLOAT tolerance) // Check whether matrices are equal using relative comparison
	{
		for (size_t r = 0; r < ROWS; r++)
			for (size_t c = 0; c < COLUMNS; c++)
				if (NotEquals<TYPE, FLOAT>(a.Data[r][c], b.Data[r][c], tolerance))
					return false;
		return true;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b, const TYPE tolerance) // Check whether matrices are equal using relative comparison
	{
		for (size_t r = 0; r < ROWS; r++)
			for (size_t c = 0; c < COLUMNS; c++)
				if (NotEquals<TYPE>(a.Data[r][c], b.Data[r][c], tolerance))
					return false;
		return true;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b, const FLOAT tolerance) // Check whether matrices aren't equal using relative comparison
	{
		for (size_t r = 0; r < ROWS; r++)
			for (size_t c = 0; c < COLUMNS; c++)
				if (NotEquals<TYPE, FLOAT>(a.Data[r][c], b.Data[r][c], tolerance))
					return true;
		return false;
	}

	template<class TYPE, size_t ROWS, size_t COLUMNS>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TMatrix<TYPE, ROWS, COLUMNS> &a, const TMatrix<TYPE, ROWS, COLUMNS> &b, const TYPE tolerance) // Check whether matrices aren't equal using relative comparison
	{
		for (size_t r = 0; r < ROWS; r++)
			for (size_t c = 0; c < COLUMNS; c++)
				if (NotEquals<TYPE>(a.Data[r][c], b.Data[r][c], tolerance))
					return true;
		return false;
	}

	template<class TO, size_t ROWS, size_t COLUMNS, class FROM>
	TMatrix<TO, ROWS, COLUMNS> Convert(const TMatrix<FROM, ROWS, COLUMNS> &m) // Convert to matrix with another data type
	{
		TMatrix<TO, ROWS, COLUMNS> result;
		for (size_t i = 0; i < ROWS; i++)
			for (size_t j = 0; j < COLUMNS; j++)
				result.Data[i][j] = (TO)m.Data[i][j];
		return result;
	}
}