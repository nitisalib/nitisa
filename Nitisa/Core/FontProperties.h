// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IFontProperties.h"

namespace nitisa
{
	class CFontProperties :public virtual IFontProperties
	{
	public:
		bool isEqual(IFontProperties *font) override;

		bool Copy(IFontProperties *src) override;

		CFontProperties(); // Create with default properties
		CFontProperties(IFontProperties *other); // Create and copy properties from specified font properties
		virtual ~CFontProperties() = default;
	};
}