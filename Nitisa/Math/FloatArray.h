// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "../Core/Strings.h"
#include "../Core/Variant.h"
#include <vector>

namespace nitisa
{
	using FloatArray = std::vector<float>;

	bool IsEqual(const FloatArray &a, const FloatArray &b, const float tolerance = ntl::Tolerance<float>); // Check if float arrays are equal
	bool IsNotEqual(const FloatArray &a, const FloatArray &b, const float tolerance = ntl::Tolerance<float>); // Check if float arrays are not equal
	String AsSourceCode(const FloatArray &a);
	String ToString(const FloatArray &value);
	Variant ToVariant(const FloatArray &value);
	void FromVariant(const Variant &value, FloatArray &dest);
}