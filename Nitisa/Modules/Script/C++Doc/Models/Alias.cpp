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
				CAlias::CAlias() :
					TDbActiveRecord(L"aliases"),
					CActiveRecord(),
					Id{ this, L"id" },
					Version{ this, L"version" },
					EntityId{ this, L"entity_id" },
					AttributeLists{ this, L"attributes" },
					isTemplate{ this, L"is_template" },
					TemplateParameters{ this, L"template_parameters" },
					TemplateRequires{ this, L"template_requires" },
					TypeName{ this, L"type_name" },
					TypeId{ this, L"type_id" },
					Entity{ this, L"Entity", L"entity_id", L"id", false },
					Type{ this, L"Type", L"type_id", L"id", false }
				{

				}
			}
		}
	}
}