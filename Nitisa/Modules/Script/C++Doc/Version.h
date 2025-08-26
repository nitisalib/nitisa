// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			enum class Version
			{
				v98, // All prior v11
				v11,
				v14,
				v17,
				v20,
				v23
			};

			String VersionToString(const Version &value);
			Version StringToVersion(const String &value);
			StringArray VersionItems();
		}
	}
}