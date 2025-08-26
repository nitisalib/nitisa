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
			namespace entities
			{
				CPackIndexing::CPackIndexing() :
					CEntity(EntityType::PackIndexing),
					Body{ nullptr, nullptr }
				{

				}

				String CPackIndexing::toString(const String &tabs, const bool is_last) const
				{
					return Identifier.toString(false) + L"...[...]";
				}

				void CPackIndexing::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"pack_indexing";
					Identifier.toVariable(target[L"name"]);
					if (Body.Begin)
						target[L"body"] = Body.toStringEx();
				}
			}
		}
	}
}