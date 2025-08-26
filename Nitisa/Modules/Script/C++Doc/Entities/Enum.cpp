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
				CEnum::CEnum() :
					CEntity(EntityType::Enum),
					Base{ nullptr, nullptr },
					isOpaque{ true }
				{

				}

				String CEnum::toString(const String &tabs, const bool is_last) const
				{
					String result{ L"enum" };
					if (!Scope.empty())
						result += L" " + Scope;
					result += toStringAttributes(L" ", false, true);
					if (!Identifier.Names.empty())
						result += L" " + Identifier.toString(true);
					if (Base.Begin)
						result += L" : " + Base.toString();
					if (!isOpaque)
					{
						result += L"\n";
						result += tabs + L"{\n";
						for (size_t i = 0; i < Entities.size(); i++)
							result += Entities[i]->toString(tabs + L"\t", i == Entities.size() - 1);
						if (Entities.empty())
							result += L"\n";
						result += tabs + L"}";
					}
					return result;
				}

				void CEnum::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"enum";
					target[L"scope"] = Scope;
					if (!Identifier.Names.empty())
					{
						target[L"name"] = Identifier.toString(false);
						Identifier.toVariable(target[L"identifier"]);
					}
					if (Base.Begin)
						target[L"base"] = Base.toStringEx();
					for (auto const &enumerator : Entities)
					{
						Variable e;
						enumerator->toVariable(e, attributes, comments);
						target[L"enumerators"].push_back(e);
					}
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}