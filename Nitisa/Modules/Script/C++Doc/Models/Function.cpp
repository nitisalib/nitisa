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
				CFunction::CFunction() :
					TDbActiveRecord(L"functions"),
					CActiveRecord(),
					Id{ this, L"id" },
					Version{ this, L"version" },
					EntityId{ this, L"entity_id" },
					AttributeLists{ this, L"attributes" },
					isTemplate{ this, L"is_template" },
					TemplateParameters{ this, L"template_parameters" },
					TemplateRequires{ this, L"template_requires" },
					Specifiers{ this, L"specifiers" },
					SpecifierId{ this, L"specifier_id" },
					Contracts{ this, L"contracts" },
					isThrow{ this, L"is_throw" },
					Throw{ this, L"throw" },
					isNoexcept{ this, L"is_noexcept" },
					Noexcept{ this, L"noexcept" },
					Trailing{ this, L"trailing" },
					Requires{ this, L"requires" },
					isAbstract{ this, L"is_abstract" },
					isDefault{ this, L"is_default" },
					isDeleted{ this, L"is_deleted" },
					DeleteReason{ this, L"delete_reason" },
					Entity{ this, L"Entity", L"entity_id", L"id", false },
					Specifier{ this, L"Specifier", L"specifier_id", L"id", false },
					Parameters{ this, L"Parameters", L"id", L"parent_id", true }
				{

				}
			}
		}
	}
}