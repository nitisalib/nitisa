// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Utils.h"
#include <initializer_list>

namespace ntl
{
	template<class TYPE, size_t ...Dimensions> class TTensor;

	// 1D tensor
	template<class TYPE, size_t SIZE>
	class TTensor<TYPE, SIZE>
	{
	private:
		TYPE m_aData[SIZE];
	public:
		const static size_t Size{ SIZE }; // Tensor size
		const static size_t TotalSize{ SIZE }; // Total element count in tensor

		TTensor() = default;

		TTensor(const std::initializer_list<TYPE> &values) // Create and fill with specified values
		{
			auto pos{ values.begin() };
			for (size_t i = 0; i < SIZE && pos != values.end(); i++, pos++)
				m_aData[i] = *pos;
		}

		const TYPE &operator[](const size_t index) const // Get element
		{
			return m_aData[index];
		}

		TYPE &operator[](const size_t index) // Get/set element
		{
			return m_aData[index];
		}
	};

	// MultiDimensional tensor
	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	class TTensor<TYPE, SIZE, Dimensions...>
	{
	private:
		TTensor<TYPE, Dimensions...> m_aData[SIZE];
	public:
		const static size_t Size{ SIZE }; // Element count
		const static size_t TotalSize{ SIZE * TTensor<TYPE, Dimensions ...>::TotalSize }; // Total element count

		TTensor() = default;

		TTensor(const std::initializer_list<TTensor<TYPE, Dimensions...>> &values) // Create and populate with specified values
		{
			auto pos{ values.begin() };
			for (size_t i = 0; i < SIZE && pos != values.end(); i++, pos++)
				m_aData[i] = *pos;
		}

		const TTensor<TYPE, Dimensions...> &operator[](const size_t index) const // Get element value
		{
			return m_aData[index];
		}

		TTensor<TYPE, Dimensions...> &operator[](const size_t index) // Get/set element value
		{
			return m_aData[index];
		}
	};

#pragma region 1D tensor
	template<class TYPE, size_t SIZE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Check whether tensors are equal. Can be used for non-float data types only
	{
		for (size_t i = 0; i < SIZE; i++)
			if (b[i] != a[i])
				return false;
		return true;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Check whether tensors aren't equal. Can be used for non-float data types only
	{
		for (size_t i = 0; i < SIZE; i++)
			if (b[i] != a[i])
				return true;
		return false;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator+(const TTensor<TYPE, SIZE> &a, const TYPE value) // Add tensor and scalar
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] + value;
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator-(const TTensor<TYPE, SIZE> &a, const TYPE value) // Subtract tensor and scalar
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] - value;
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator*(const TTensor<TYPE, SIZE> &a, const TYPE value) // Multiply tensor and scalar
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] * value;
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator/(const TTensor<TYPE, SIZE> &a, const TYPE value) // Divide tensor and scalar
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] / value;
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator+(const TYPE value, const TTensor<TYPE, SIZE> &a) // Add scalar and tensor
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = value + a[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator-(const TYPE value, const TTensor<TYPE, SIZE> &a) // Subtract scalar and tensor
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = value - a[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator*(const TYPE value, const TTensor<TYPE, SIZE> &a) // Multiply scalar and tensor
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = value * a[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator/(const TYPE value, const TTensor<TYPE, SIZE> &a) // Divide scalar and tensor
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = value / a[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> &operator+=(TTensor<TYPE, SIZE> &a, const TYPE value) // Add scalar to tensor
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] += value;
		return a;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> &operator-=(TTensor<TYPE, SIZE> &a, const TYPE value) // Subtract scalar from tensor
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] -= value;
		return a;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> &operator*=(TTensor<TYPE, SIZE> &a, const TYPE value) // Multiply tensor by scalar
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] *= value;
		return a;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> &operator/=(TTensor<TYPE, SIZE> &a, const TYPE value) // Divide tensor by scalar
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] /= value;
		return a;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator+(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Add tensors(their elements)
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] + b[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator-(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Subtract tensors(their elements)
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] - b[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator*(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Multiply tensors(their elements)
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] * b[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator/(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Divide tensors(their elements)
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] / b[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> &operator+=(TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Add tensor to tensor(its elements)
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] += b[i];
		return a;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> &operator-=(TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Subtract tensor from tensor(its elements)
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] -= b[i];
		return a;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> &operator*=(TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Multiply tensor by tensor(its elements)
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] *= b[i];
		return a;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> &operator/=(TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Divide tensor by tensor(its elements)
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] /= b[i];
		return a;
	}
	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE>> operator-(const TTensor<TYPE, SIZE> &a) // Inverse tensor
	{
		TTensor<TYPE, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = -a[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Compare whether tensors are equal
	{
		for (size_t i = 0; i < SIZE; i++)
			if (a[i] != b[i])
				return false;
		return true;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether tensors are equal
	{
		for (size_t i = 0; i < SIZE; i++)
			if (IsNotEqual<TYPE>(a[i], b[i], tolerance))
				return false;
		return true;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Compare whether tensors aren't equal
	{
		for (size_t i = 0; i < SIZE; i++)
			if (a[i] != b[i])
				return true;
		return false;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether tensors aren't equal
	{
		for (size_t i = 0; i < SIZE; i++)
			if (IsNotEqual<TYPE>(a[i], b[i], tolerance))
				return true;
		return false;
	}

	template<class TO, class FROM, size_t SIZE>
	void Convert(const TTensor<FROM, SIZE> &v, TTensor<TO, SIZE> &target) // Convert to tensor with another data type
	{
		for (size_t i = 0; i < SIZE; i++)
			target[i] = (TO)v[i];
	}

	template<class TO, class FROM, size_t SIZE>
	TTensor<TO, SIZE> Convert(const TTensor<FROM, SIZE> &v) // Convert to tensor with another data type
	{
		TTensor<TO, SIZE> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = (TO)v[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	void Fill(TTensor<TYPE, SIZE> &a, const TYPE value) // Fill tensor with specified value
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] = value;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> NormLMax(const TTensor<TYPE, SIZE> &a) // Return LMax norm
	{
		TYPE result{ Abs<TYPE>(a[0]) };
		for (size_t i = 1; i < SIZE; i++)
			result = Max<TYPE>(result, Abs<TYPE>(a[i]));
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> NormL1(const TTensor<TYPE, SIZE> &a) // Return L1 norm
	{
		TYPE result{ 0 };
		for (size_t i = 0; i < SIZE; i++)
			result += Abs<TYPE>(a[i]);
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> NormL2Sqr(const TTensor<TYPE, SIZE> &a) // Return square L2 norm
	{
		TYPE result{ 0 };
		for (size_t i = 0; i < SIZE; i++)
			result += a[i] * a[i];
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, TYPE> NormL2(const TTensor<TYPE, SIZE> &a) // Return L2 norm
	{
		return (TYPE)std::sqrt(NormL2Sqr<TYPE, SIZE>(a));
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> DistanceSqr(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Return square distance from other tensor
	{
		TYPE result{ 0 }, d;
		for (size_t i = 0; i < SIZE; i++)
		{
			d = a[i] - b[i];
			result += d * d;
		}
		return result;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, TYPE> Distance(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b) // Return distance from other tensor
	{
		return (TYPE)std::sqrt(DistanceSqr<TYPE, SIZE>(a, b));
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, void> Normalize(TTensor<TYPE, SIZE> &a) // Normalize
	{
		TYPE n{ NormL2<TYPE, SIZE>(a) };
		for (size_t i = 0; i < SIZE; i++)
			a[i] /= n;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, TTensor<TYPE, SIZE>> Normalized(const TTensor<TYPE, SIZE> &a) // Return normalized tensor
	{
		TTensor<TYPE, SIZE> result;
		TYPE n{ NormL2<TYPE, SIZE>(a) };
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] / n;
		return result;
	}

	template<class TYPE, class FLOAT, size_t SIZE>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b, const FLOAT tolerance) // Check whether tensors are equal using relative comparison
	{
		for (size_t i = 0; i < SIZE; i++)
			if (NotEquals<TYPE, FLOAT>(a[i], b[i], tolerance))
				return false;
		return true;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b, const TYPE tolerance) // Check whether tensors are equal using relative comparison
	{
		for (size_t i = 0; i < SIZE; i++)
			if (NotEquals<TYPE>(a[i], b[i], tolerance))
				return false;
		return true;
	}

	template<class TYPE, class FLOAT, size_t SIZE>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b, const FLOAT tolerance) // Check whether tensors aren't equal using relative comparison
	{
		for (size_t i = 0; i < SIZE; i++)
			if (NotEquals<TYPE, FLOAT>(a[i], b[i], tolerance))
				return true;
		return false;
	}

	template<class TYPE, size_t SIZE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TTensor<TYPE, SIZE> &a, const TTensor<TYPE, SIZE> &b, const TYPE tolerance) // Check whether tensors aren't equal using relative comparison
	{
		for (size_t i = 0; i < SIZE; i++)
			if (NotEquals<TYPE>(a[i], b[i], tolerance))
				return true;
		return false;
	}
#pragma endregion

#pragma region MultiDimensional tensor
	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Check whether tensors are equal. Can be used for non-float data types only
	{
		for (size_t i = 0; i < SIZE; i++)
			if (b[i] != a[i])
				return false;
		return true;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Check whether tensors aren't equal. Can be used for non-float data types only
	{
		for (size_t i = 0; i < SIZE; i++)
			if (b[i] != a[i])
				return true;
		return false;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator+(const TTensor<TYPE, SIZE, Dimensions...> &a, const TYPE value) // Add tensor and scalar
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] + value;
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator-(const TTensor<TYPE, SIZE, Dimensions...> &a, const TYPE value) // Subtract tensor and scalar
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] - value;
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator*(const TTensor<TYPE, SIZE, Dimensions...> &a, const TYPE value) // Multiply tensor and scalar
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] * value;
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator/(const TTensor<TYPE, SIZE, Dimensions...> &a, const TYPE value) // Divide tensor and scalar
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] / value;
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator+(const TYPE value, const TTensor<TYPE, SIZE, Dimensions...> &a) // Add scalar and tensor
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = value + a[i];
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator-(const TYPE value, const TTensor<TYPE, SIZE, Dimensions...> &a) // Subtract scalar and tensor
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = value - a[i];
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator*(const TYPE value, const TTensor<TYPE, SIZE, Dimensions...> &a) // Multiply scalar and tensor
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = value * a[i];
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator/(const TYPE value, const TTensor<TYPE, SIZE, Dimensions...> &a) // Divide scalar and tensor
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = value / a[i];
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> &operator+=(TTensor<TYPE, SIZE, Dimensions...> &a, const TYPE value) // Add scalar to tensor
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] += value;
		return a;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> &operator-=(TTensor<TYPE, SIZE, Dimensions...> &a, const TYPE value) // Subtract scalar from tensor
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] -= value;
		return a;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> &operator*=(TTensor<TYPE, SIZE, Dimensions...> &a, const TYPE value) // Multiply tensor by scalar
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] *= value;
		return a;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> &operator/=(TTensor<TYPE, SIZE, Dimensions...> &a, const TYPE value) // Divide tensor by scalar
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] /= value;
		return a;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator+(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Add tensors(their elements)
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] + b[i];
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator-(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Subtract tensors(their elements)
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] - b[i];
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator*(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Multiply tensors(their elements)
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] * b[i];
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator/(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Divide tensors(their elements)
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = a[i] / b[i];
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> &operator+=(TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Add tensor to tensor(its elements)
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] += b[i];
		return a;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> &operator-=(TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Subtract tensor from tensor(its elements)
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] -= b[i];
		return a;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> &operator*=(TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Multiply tensor by tensor(its elements)
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] *= b[i];
		return a;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> &operator/=(TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Divide tensor by tensor(its elements)
	{
		for (size_t i = 0; i < SIZE; i++)
			a[i] /= b[i];
		return a;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> operator-(const TTensor<TYPE, SIZE, Dimensions...> &a) // Inverse tensor
	{
		TTensor<TYPE, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			result[i] = -a[i];
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Compare whether tensors are equal
	{
		for (size_t i = 0; i < SIZE; i++)
			if (a[i] != b[i])
				return false;
		return true;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether tensors are equal
	{
		for (size_t i = 0; i < SIZE; i++)
			if (IsNotEqual<TYPE, Dimensions...>(a[i], b[i], tolerance))
				return false;
		return true;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Compare whether tensors aren't equal
	{
		for (size_t i = 0; i < SIZE; i++)
			if (a[i] != b[i])
				return true;
		return false;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether tensors aren't equal
	{
		for (size_t i = 0; i < SIZE; i++)
			if (IsNotEqual<TYPE, Dimensions...>(a[i], b[i], tolerance))
				return true;
		return false;
	}

	template<class TO, class FROM, size_t SIZE, size_t ...Dimensions>
	void Convert(const TTensor<FROM, SIZE, Dimensions...> &v, TTensor<TO, SIZE, Dimensions...> &target) // Convert to tensor with another data type
	{
		for (size_t i = 0; i < SIZE; i++)
			Convert<TO, FROM, Dimensions...>(v[i], target[i]);
	}

	template<class TO, class FROM, size_t SIZE, size_t ...Dimensions>
	TTensor<TO, SIZE, Dimensions...> Convert(const TTensor<FROM, SIZE, Dimensions...> &v) // Convert to tensor with another data type
	{
		TTensor<TO, SIZE, Dimensions...> result;
		for (size_t i = 0; i < SIZE; i++)
			Convert<TO, FROM, Dimensions...>(v[i], result[i]);
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	void Fill(TTensor<TYPE, SIZE, Dimensions...> &a, const TYPE value) // Fill tensor with specified value
	{
		for (size_t i = 0; i < SIZE; i++)
			Fill<TYPE, Dimensions...>(a[i], value);
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> NormLMax(const TTensor<TYPE, SIZE, Dimensions...> &a) // Return LMax norm
	{
		TYPE result{ NormLMax<TYPE, Dimensions...>(a[0]) };
		for (size_t i = 1; i < SIZE; i++)
			result = Max<TYPE>(result, NormLMax<TYPE, Dimensions...>(a[i]));
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> NormL1(const TTensor<TYPE, SIZE, Dimensions...> &a) // Return L1 norm
	{
		TYPE result{ 0 };
		for (size_t i = 0; i < SIZE; i++)
			result += NormL1<TYPE, Dimensions...>(a[i]);
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> NormL2Sqr(const TTensor<TYPE, SIZE, Dimensions...> &a) // Return square L2 norm
	{
		TYPE result{ 0 };
		for (size_t i = 0; i < SIZE; i++)
			result += NormL2Sqr<TYPE, Dimensions...>(a[i]);
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_floating_point_v<TYPE>, TYPE> NormL2(const TTensor<TYPE, SIZE, Dimensions...> &a) // Return L2 norm
	{
		return (TYPE)std::sqrt(NormL2Sqr<TYPE, SIZE>(a));
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> DistanceSqr(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Return square distance from other tensor
	{
		TYPE result{ 0 };
		for (size_t i = 0; i < SIZE; i++)
			result += DistanceSqr<TYPE, Dimensions...>(a[i], b[i]);
		return result;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_floating_point_v<TYPE>, TYPE> Distance(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b) // Return distance from other tensor
	{
		return (TYPE)std::sqrt(DistanceSqr<TYPE, SIZE>(a, b));
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_floating_point_v<TYPE>, void> Normalize(TTensor<TYPE, SIZE, Dimensions...> &a) // Normalize tensor
	{
		a /= NormL2<TYPE, SIZE, Dimensions...>(a);
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_floating_point_v<TYPE>, TTensor<TYPE, SIZE, Dimensions...>> Normalized(const TTensor<TYPE, SIZE, Dimensions...> &a) // Return normalized tensor
	{
		return a / NormL2<TYPE, SIZE, Dimensions...>(a);
	}

	template<class TYPE, class FLOAT, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b, const FLOAT tolerance) // Check whether tensors are equal using relative comparison
	{
		for (size_t i = 0; i < SIZE; i++)
			if (NotEquals<TYPE, FLOAT, Dimensions...>(a[i], b[i], tolerance))
				return false;
		return true;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b, const TYPE tolerance) // Check whether tensors are equal using relative comparison
	{
		for (size_t i = 0; i < SIZE; i++)
			if (NotEquals<TYPE, Dimensions...>(a[i], b[i], tolerance))
				return false;
		return true;
	}

	template<class TYPE, class FLOAT, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b, const FLOAT tolerance) // Check whether tensors aren't equal using relative comparison
	{
		for (size_t i = 0; i < SIZE; i++)
			if (NotEquals<TYPE, FLOAT, Dimensions...>(a[i], b[i], tolerance))
				return true;
		return false;
	}

	template<class TYPE, size_t SIZE, size_t ...Dimensions>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TTensor<TYPE, SIZE, Dimensions...> &a, const TTensor<TYPE, SIZE, Dimensions...> &b, const TYPE tolerance) // Check whether tensors aren't equal using relative comparison
	{
		for (size_t i = 0; i < SIZE; i++)
			if (NotEquals<TYPE, Dimensions...>(a[i], b[i], tolerance))
				return true;
		return false;
	}
#pragma endregion
}