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
				CNamespace::CNamespace() :
					CEntity(EntityType::Namespace),
					isInline{ false }
				{

				}

				String CNamespace::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) + tabs };
					if (isInline)
						result += L"inline namespace";
					else
						result += L"namespace";
					result += toStringAttributes(L" ", false, true);
					if (!Name.empty())
						result += L" " + Name;
					result += L"\n";
					if (Entities[0]->Type != EntityType::Block)
					{
						result += tabs + L"{\n" + Entities[0]->toString(tabs + L"\t", false) + tabs + L"}";
						if (!is_last)
							result += L"\n";
					}
					else
						result += Entities[0]->toString(tabs, is_last);
					return result;
				}

				void CNamespace::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"namespace";
					target[L"is_inline"] = isInline;
					target[L"name"] = Name;
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