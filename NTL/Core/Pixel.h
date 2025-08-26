// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Utils.h"
#include <limits>

namespace ntl
{
	template<class TYPE, size_t CHANNELS = 4>
	struct TPixel
	{
		TYPE Data[CHANNELS]; // Elements/Channels

		TYPE operator[](const size_t index) const // Return element/channel at specified column. Allowed index range is from 0 to CHANNELS - 1. Used when TPixel is a constant object only
		{
			return Data[index];
		}

		TYPE &operator[](const size_t index) // Return element/channel at specified column. Allowed index range is from 0 to CHANNELS - 1
		{
			return Data[index];
		}
	};

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Check whether pixels are equal. Can be used for non-float data types only
	{
		for (size_t i = 0; i < CHANNELS; i++)
			if (a.Data[i] != b.Data[i])
				return false;
		return true;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Check whether pixels aren't equal. Can be used for non-float data types only
	{
		for (size_t i = 0; i < CHANNELS; i++)
			if (a.Data[i] != b.Data[i])
				return true;
		return false;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> operator+(const TPixel<TYPE, CHANNELS> &p, const TYPE val) // Add pixel and scalar
	{
		TPixel<TYPE, CHANNELS> r;
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = p.Data[i] + val;
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> operator-(const TPixel<TYPE, CHANNELS> &p, const TYPE val) // Subtract pixel and scalar
	{
		TPixel<TYPE, CHANNELS> r;
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = p.Data[i] - val;
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> operator*(const TPixel<TYPE, CHANNELS> &p, const TYPE val) // Multiply pixel and scalar
	{
		TPixel<TYPE, CHANNELS> r;
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = p.Data[i] * val;
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> operator/(const TPixel<TYPE, CHANNELS> &p, const TYPE val) // Divide pixel and scalar
	{
		TPixel<TYPE, CHANNELS> r;
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = p.Data[i] / val;
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> operator+(const TYPE val, const TPixel<TYPE, CHANNELS> &p) // Add scalar and pixel
	{
		TPixel<TYPE, CHANNELS> r;
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = val + p.Data[i];
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> operator-(const TYPE val, const TPixel<TYPE, CHANNELS> &p) // Subtract scalar and pixel
	{
		TPixel<TYPE, CHANNELS> r;
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = val - p.Data[i];
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> operator*(const TYPE val, const TPixel<TYPE, CHANNELS> &p) // Multiply scalar and pixel
	{
		TPixel<TYPE, CHANNELS> r;
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = val * p.Data[i];
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> operator/(const TYPE val, const TPixel<TYPE, CHANNELS> &p) // Divide scalar and pixel
	{
		TPixel<TYPE, CHANNELS> r;
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = val / p.Data[i];
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> &operator+=(TPixel<TYPE, CHANNELS> &p, const TYPE val) // Add scalar to pixel
	{
		for (size_t i = 0; i < CHANNELS; i++)
			p.Data[i] += val;
		return p;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> &operator-=(TPixel<TYPE, CHANNELS> &p, const TYPE val) // Subtract scalar from pixel
	{
		for (size_t i = 0; i < CHANNELS; i++)
			p.Data[i] -= val;
		return p;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> &operator*=(TPixel<TYPE, CHANNELS> &p, const TYPE val) // Multiply pixel by scalar
	{
		for (size_t i = 0; i < CHANNELS; i++)
			p.Data[i] *= val;
		return p;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPixel<TYPE, CHANNELS>> &operator/=(TPixel<TYPE, CHANNELS> &p, const TYPE val) // Divide pixel by scalar
	{
		for (size_t i = 0; i < CHANNELS; i++)
			p.Data[i] /= val;
		return p;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_unsigned_v<TYPE> && (CHANNELS > 1) && (sizeof(TYPE) < 8), TPixel<TYPE, CHANNELS>> operator+(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Blend pixels
	{
		TPixel<TYPE, CHANNELS> r;
		unsigned long long m{ (unsigned long long)(std::numeric_limits<TYPE>::max)() };
		const size_t ac{ CHANNELS - 1 };
		for (size_t i = 0; i < ac; i++)
			r.Data[i] = (TYPE)(((b.Data[i] * m) + a.Data[i] * (m - b.Data[ac])) / m);
		r.Data[ac] = (TYPE)((b.Data[ac] * (m - a.Data[ac]) + (a.Data[ac] * m)) / m);
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TYPE> && (CHANNELS > 1), TPixel<TYPE, CHANNELS>> operator+(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Blend pixels
	{
		TPixel<TYPE, CHANNELS> r;
		const size_t ac{ CHANNELS - 1 };
		for (size_t i = 0; i < ac; i++)
			r.Data[i] = b.Data[i] + a.Data[i] * (1 - b.Data[ac]);
		r.Data[ac] = b.Data[ac] * (1 - a.Data[ac]) + a.Data[ac];
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_unsigned_v<TYPE> && (CHANNELS > 1) && (sizeof(TYPE) < 8), TPixel<TYPE, CHANNELS>> &operator+=(TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Blend pixel with the second one
	{
		unsigned long long m{ (unsigned long long)(std::numeric_limits<TYPE>::max)() };
		const size_t ac{ CHANNELS - 1 };
		for (size_t i = 0; i < ac; i++)
			a.Data[i] = (TYPE)(((b.Data[i] * m) + a.Data[i] * (m - b.Data[ac])) / m);
		a.Data[ac] = (TYPE)((b.Data[ac] * (m - a.Data[ac]) + (a.Data[ac] * m)) / m);
		return a;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TYPE> && (CHANNELS > 1), TPixel<TYPE, CHANNELS>> &operator+=(TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Blend pixel with the second one
	{
		const size_t ac{ CHANNELS - 1 };
		for (size_t i = 0; i < ac; i++)
			a.Data[i] = b.Data[i] + a.Data[i] * (1 - b.Data[ac]);
		a.Data[ac] = b.Data[ac] * (1 - a.Data[ac]) + a.Data[ac];
		return a;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_unsigned_v<TYPE> && (CHANNELS > 1) && (sizeof(TYPE) < 8), TPixel<TYPE, CHANNELS>> operator*(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Blend pixels with the same algo renderers use
	{
		TPixel<TYPE, CHANNELS> r;
		const size_t ac{ CHANNELS - 1 };
		double m{ (double)(std::numeric_limits<TYPE>::max)() }, A{ 1 - b.Data[ac] / m };
		for (size_t i = 0; i < ac; i++)
			r.Data[i] = (TYPE)((double)a.Data[i] * A + (double)b.Data[i] * (double)b.Data[ac] / m);
		r.Data[ac] = a.Data[ac];
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TYPE> && (CHANNELS > 1), TPixel<TYPE, CHANNELS>> operator*(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b)// Blend pixels with the same algo renderers use
	{
		TPixel<TYPE, CHANNELS> r;
		const size_t ac{ CHANNELS - 1 };
		TYPE A{ 1 - b.Data[ac] };
		for (size_t i = 0; i < ac; i++)
			r.Data[i] = a.Data[i] * A + b.Data[i] * b.Data[ac];
		r.Data[ac] = a.Data[ac];
		return r;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_unsigned_v<TYPE> && (CHANNELS > 1) && (sizeof(TYPE) < 8), TPixel<TYPE, CHANNELS>> &operator*=(TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Blend pixel with the second one using the same algo renderers use
	{
		const size_t ac{ CHANNELS - 1 };
		double m{ (double)(std::numeric_limits<TYPE>::max)() }, A{ 1 - b.Data[ac] / m };
		for (size_t i = 0; i < ac; i++)
			a.Data[i] = (TYPE)((double)a.Data[i] * A + (double)b.Data[i] * (double)b.Data[ac] / m);
		return a;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TYPE> && (CHANNELS > 1), TPixel<TYPE, CHANNELS>> &operator*=(TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Blend pixel with the second one using the same algo renderers use
	{
		const size_t ac{ CHANNELS - 1 };
		TYPE A{ 1 - b.Data[ac] };
		for (size_t i = 0; i < ac; i++)
			a.Data[i] = a.Data[i] * A + b.Data[i] * b.Data[ac];
		return a;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Compare whether pixels are equal
	{
		for (size_t i = 0; i < CHANNELS; i++)
			if (a.Data[i] != b.Data[i])
				return false;
		return true;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether pixels are equal
	{
		for (size_t i = 0; i < CHANNELS; i++)
			if (IsNotEqual(a.Data[i], b.Data[i], tolerance))
				return false;
		return true;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b) // Compare whether pixels aren't equal
	{
		for (size_t i = 0; i < CHANNELS; i++)
			if (a.Data[i] != b.Data[i])
				return true;
		return false;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether pixels aren't equal
	{
		for (size_t i = 0; i < CHANNELS; i++)
			if (IsNotEqual(a.Data[i], b.Data[i], tolerance))
				return true;
		return false;
	}

	template<class TO, class FROM, size_t CHANNELS = 4>
	std::enable_if_t<std::is_integral_v<TO> && std::is_unsigned_v<TO> && std::is_integral_v<FROM> && std::is_unsigned_v<FROM>, TPixel<TO, CHANNELS>> Convert(const TPixel<FROM, CHANNELS> &p) // Convert to pixel with another data type
	{
		TPixel<TO, CHANNELS> r;
		long double k{ (long double)(std::numeric_limits<TO>::max)() / (long double)(std::numeric_limits<FROM>::max)() };
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = TO(p.Data[i] * k);
		return r;
	}

	template<class TO, class FROM, size_t CHANNELS = 4>
	std::enable_if_t<std::is_integral_v<TO> && std::is_unsigned_v<TO> && std::is_floating_point_v<FROM>, TPixel<TO, CHANNELS>> Convert(const TPixel<FROM, CHANNELS> &p) // Convert to pixel with another data type
	{
		TPixel<TO, CHANNELS> r;
		long double k{ (long double)(std::numeric_limits<TO>::max)() };
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = TO(p.Data[i] * k);
		return r;
	}

	template<class TO, class FROM, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TO> && std::is_integral_v<FROM> && std::is_unsigned_v<FROM>, TPixel<TO, CHANNELS>> Convert(const TPixel<FROM, CHANNELS> &p) // Convert to pixel with another data type
	{
		TPixel<TO, CHANNELS> r;
		long double k{ 1 / (long double)(std::numeric_limits<FROM>::max)() };
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = TO(p.Data[i] * k);
		return r;
	}

	template<class TO, class FROM, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TO> && std::is_floating_point_v<FROM>, TPixel<TO, CHANNELS>> Convert(const TPixel<FROM, CHANNELS> &p) // Convert to pixel with another data type
	{
		TPixel<TO, CHANNELS> r;
		for (size_t i = 0; i < CHANNELS; i++)
			r.Data[i] = (TO)p.Data[i];
		return r;
	}

	template<class TYPE, size_t CHANNELS, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b, const FLOAT relative_tolerance) // Check whether pixels are equal using relative comparison
	{
		for (size_t i = 0; i < CHANNELS; i++)
			if (NotEquals<TYPE, FLOAT>(a.Data[i], b.Data[i], relative_tolerance))
				return false;
		return true;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b, const TYPE relative_tolerance) // Check whether pixels are equal using relative comparison
	{
		for (size_t i = 0; i < CHANNELS; i++)
			if (NotEquals<TYPE>(a.Data[i], b.Data[i], relative_tolerance))
				return false;
		return true;
	}

	template<class TYPE, size_t CHANNELS, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b, const FLOAT relative_tolerance) // Check whether pixels aren't equal using relative comparison
	{
		for (size_t i = 0; i < CHANNELS; i++)
			if (NotEquals<TYPE, FLOAT>(a.Data[i], b.Data[i], relative_tolerance))
				return true;
		return false;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TPixel<TYPE, CHANNELS> &a, const TPixel<TYPE, CHANNELS> &b, const TYPE relative_tolerance) // Check whether pixels aren't equal using relative comparison
	{
		for (size_t i = 0; i < CHANNELS; i++)
			if (NotEquals<TYPE>(a.Data[i], b.Data[i], relative_tolerance))
				return true;
		return false;
	}
}