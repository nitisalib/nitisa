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
				CTag::CTag() :
					TDbActiveRecord(L"tags"),
					CActiveRecord(),
					Id{ this, L"id" },
					Version{ this, L"version" },
					EntityId{ this, L"entity_id" },
					Name{ this, L"name" },
					Options{ this, L"options" },
					Entity{ this, L"Entity", L"entity_id", L"id", false }
				{

				}
			}
		}
	}
}