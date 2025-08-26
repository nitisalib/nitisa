// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Vec4.h"
#include "../Core/Strings.h"

namespace nitisa
{
	using Vec4f = ntl::TVec4<float>;

	String AsSourceCode(const Vec4f &a);
}