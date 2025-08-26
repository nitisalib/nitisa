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
				CUsing::CUsing() :
					CEntity(EntityType::Using)
				{

				}

				String CUsing::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) + tabs + L"using"};
					for (size_t i = 0; i < Declarators.size(); i++)
					{
						if (i > 0)
							result += L",";
						if (Declarators[i].isTypename)
							result += L" typename";
						result += L" " + Declarators[i].Identifier.toString(true);
						if (Declarators[i].isPackExpansion)
							result += L"...";
					}
					result += L";" + toStringTrailingComments(!is_last);
					return result;
				}

				void CUsing::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"using";
					for (auto const &declarator : Declarators)
					{
						Variable d;
						d[L"is_typename"] = declarator.isTypename;
						d[L"is_pack_expansion"] = declarator.isPackExpansion;
						declarator.Identifier.toVariable(d[L"name"]);
						target[L"declarators"].push_back(d);
					}
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}