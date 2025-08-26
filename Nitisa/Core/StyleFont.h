// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IStyleFont.h"
#include "FontProperties.h"
#include "Strings.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class CStyleFont :public virtual IStyleFont, public CFontProperties
	{
	public:
		CStyleFont(const String &name);
	};
}