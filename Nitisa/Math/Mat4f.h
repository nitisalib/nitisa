// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Mat4.h"
#include "../Core/Strings.h"
#include "../Core/Variant.h"

namespace nitisa
{
	using Mat4f = ntl::TMat4<float>;

	String AsSourceCode(const Mat4f &a);
	String ToString(const Mat4f &value);
	Variant ToVariant(const Mat4f &value);
	void FromVariant(const Variant &value, Mat4f &dest);
}