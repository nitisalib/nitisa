// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			String VersionToString(const Version &value)
			{
				switch (value)
				{
				case Version::v11: return L"v11";
				case Version::v14: return L"v14";
				case Version::v17: return L"v17";
				case Version::v20: return L"v20";
				case Version::v23: return L"v23";
				default: return L"";
				}
			}

			Version StringToVersion(const String &value)
			{
				if (value == L"v11") return Version::v11;
				if (value == L"v14") return Version::v14;
				if (value == L"v17") return Version::v17;
				if (value == L"v20") return Version::v20;
				if (value == L"v23") return Version::v23;
				return Version::v98;
			}

			StringArray VersionItems()
			{
				return StringArray{ L"v98", L"v11", L"v14", L"v17", L"v20", L"v23" };
			}
		}
	}
}