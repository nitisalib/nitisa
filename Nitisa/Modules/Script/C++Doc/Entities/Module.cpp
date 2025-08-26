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
				CModule::CModule() :
					CEntity(EntityType::Module),
					isExport{ false },
					isPrivate{ false }
				{

				}

				String CModule::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) + tabs };
					if (isExport)
						result += L"export module";
					else
						result += L"module";
					if (isPrivate)
						result += L" : private";
					else
					{
						result += L" " + Name;
						if (!Partition.empty())
							result += L" " + Partition;
					}
					result += toStringAttributes(L" ", false, true) + L";" + toStringTrailingComments(!is_last || !Entities.empty());
					for (size_t i = 0; i < Entities.size(); i++)
						result += L"\n" + Entities[i]->toString(tabs, is_last && i == Entities.size() - 1);
					return result;
				}

				void CModule::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"module";
					target[L"is_export"] = isExport;
					target[L"is_private"] = isPrivate;
					target[L"name"] = Name;
					target[L"partition"] = Partition;
					for (auto const &entity : Entities)
					{
						Variable e;
						entity->toVariable(e, attributes, comments);
						target[L"entities"].push_back(e);
					}
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}