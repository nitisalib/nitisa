// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include <type_traits>

namespace ntl
{
#pragma region Helper functions
	template<class FLOAT>
	constexpr std::enable_if_t<std::is_same_v<FLOAT, float>, FLOAT> getTolerance() // Return 0.001f
	{
		return 0.001f;
	}

	template<class FLOAT>
	constexpr std::enable_if_t<std::is_same_v<FLOAT, double>, FLOAT> getTolerance() // Return 0.000001
	{
		return 0.000001;
	}

	template<class FLOAT>
	constexpr std::enable_if_t<std::is_same_v<FLOAT, long double>, FLOAT> getTolerance() // Return 0.000001
	{
		return 0.000001;
	}

	template<class FLOAT>
	constexpr std::enable_if_t<std::is_same_v<FLOAT, float>, FLOAT> getRelativeTolerance() // Return 0.000001f
	{
		return 0.000001f;
	}

	template<class FLOAT>
	constexpr std::enable_if_t<std::is_same_v<FLOAT, double>, FLOAT> getRelativeTolerance() // Return 0.000000001
	{
		return 0.000000001;
	}

	template<class FLOAT>
	constexpr std::enable_if_t<std::is_same_v<FLOAT, long double>, FLOAT> getRelativeTolerance() // Return 0.000000001
	{
		return 0.000000001;
	}
#pragma endregion

#pragma region Consts
	template<class FLOAT> constexpr FLOAT Tolerance{ getTolerance<FLOAT>() };
	template<class FLOAT> constexpr FLOAT RelativeTolerance{ getRelativeTolerance<FLOAT>() };
	template<class TYPE> constexpr TYPE Pi{			(TYPE)3.14159265358979323846 };
	template<class TYPE> constexpr TYPE DoublePi{	(TYPE)6.28318530717958647692 };
	template<class TYPE> constexpr TYPE HalfPi{		(TYPE)1.57079632679489661923 };
#pragma endregion
}