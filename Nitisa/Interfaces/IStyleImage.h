// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Image/Image.h"

namespace nitisa
{
	class IStyleImage
	{
	protected:
		IStyleImage() = default;
		~IStyleImage() = default;
		IStyleImage(const IStyleImage &other) = delete;
		IStyleImage(IStyleImage &&other) = delete;
		IStyleImage &operator=(const IStyleImage &other) = delete;
		IStyleImage &operator=(IStyleImage &&other) = delete;
	protected:
		String m_sName;
		nitisa::Image m_sImage;
	public:
		String const &Name{ m_sName }; // Name
		nitisa::Image const &Image{ m_sImage }; // Image
	};
}