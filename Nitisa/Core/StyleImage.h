// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Image/Image.h"
#include "../Interfaces/IStyleImage.h"
#include "Strings.h"

namespace nitisa
{
	class CStyleImage :public virtual IStyleImage
	{
	public:
		CStyleImage(const String &name, const nitisa::Image &data); // Create with image copied from "data"
		CStyleImage(const String &name, const int width, const int height, const Color *data); // Create with image stored in "data"
		virtual ~CStyleImage() = default;
	};
}