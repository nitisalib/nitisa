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
				CEntity::CEntity() :
					TDbActiveRecord(L"entities"),
					CActiveRecord(),
					Id{ this, L"id" },
					Version{ this, L"version" },
					ParentId{ this, L"parent_id" },
					Name{ this, L"name" },
					Qualified{ this, L"qualified" },
					Path{ this, L"path" },
					Type{ this, L"type" },
					Access{ this, L"access" },
					Language{ this, L"language" },
					isExported{ this, L"is_exported" },
					FileId{ this, L"file_id" },
					Parent{ this, L"Parent", L"parent_id", L"id", false },
					Tags{ this, L"Tags", L"id", L"entity_id", true },
					Comments{ this, L"Comments", L"id", L"entity_id", true },
					Entities{ this, L"Entities", L"id", L"parent_id", true },
					File{ this, L"File", L"file_id", L"id", false }
				{

				}
			}
		}
	}
}