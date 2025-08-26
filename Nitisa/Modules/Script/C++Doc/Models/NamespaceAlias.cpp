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
				CNamespaceAlias::CNamespaceAlias() :
					TDbActiveRecord(L"namespace_aliases"),
					CActiveRecord(),
					Id{ this, L"id" },
					Version{ this, L"version" },
					EntityId{ this, L"entity_id" },
					AttributeLists{ this, L"attributes" },
					NamespaceName{ this, L"namespace_name" },
					NamespaceId{ this, L"namespace_id" },
					Entity{ this, L"Entity", L"entity_id", L"id", false },
					Namespace{ this, L"Namespace", L"namespace_id", L"id", false }
				{

				}
			}
		}
	}
}