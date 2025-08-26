// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	namespace script
	{
		struct Progress
		{
			size_t Current; // Current progress value
			size_t Total; // Maximum progress value corresponding to 100% completeness
		};
	}
}