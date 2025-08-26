// This file is a part of Nitisa framework
// Copyright © 2024 Nitisa. All rights reserved.
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
				CRoot::CRoot() :
					CEntity(EntityType::Root)
				{

				}

				String CRoot::toString(const String &tabs, const bool is_last) const
				{
					String result;
					for (size_t i = 0; i < Entities.size(); i++)
					{
						if (i > 0)
							result += L"\n";
						result += Entities[i]->toString(L"", i == Entities.size() - 1);
					}
					return result;
				}

				void CRoot::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"root";
					for (auto const &entity : Entities)
					{
						Variable e;
						entity->toVariable(e, attributes, comments);
						target[L"entities"].push_back(e);
					}
				}
			}
		}
	}
}