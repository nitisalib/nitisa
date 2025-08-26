// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "IFontProperties.h"

namespace nitisa
{
	class IStyleFont :public virtual IFontProperties
	{
	protected:
		IStyleFont() = default;
		~IStyleFont() = default;
		IStyleFont(const IStyleFont &other) = delete;
		IStyleFont(IStyleFont &&other) = delete;
		IStyleFont &operator=(const IStyleFont &other) = delete;
		IStyleFont &operator=(IStyleFont &&other) = delete;
	protected:
		String m_sName;
	public:
		String const &Name{ m_sName }; // Name
	};
}