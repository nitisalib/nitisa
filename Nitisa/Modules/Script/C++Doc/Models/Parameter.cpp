// This file is a part of Nitisa L3GameServer
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://l3.nitisa.com
// Download: http://l3.nitisa.com/downloads
// Documentation: http://l3.nitisa.com/documentation
// License: http://l3.nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			namespace models
			{
				CParameter::CParameter() :
					TDbActiveRecord(L"parameters"),
					CActiveRecord(),
					Id{ this, L"id" },
					Version{ this, L"version" },
					EntityId{ this, L"entity_id" },
					AttributeLists{ this, L"attributes" },
					Declaration{ this, L"declaration" },
					SpecifierId{ this, L"specifier_id" },
					Entity{ this, L"Entity", L"entity_id", L"id", false },
					Specifier{ this, L"Specifier", L"specifier_id", L"id", false }
				{

				}
			}
		}
	}
}