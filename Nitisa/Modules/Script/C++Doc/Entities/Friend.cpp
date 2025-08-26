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
				CFriend::CFriend() :
					CEntity(EntityType::Friend)
				{

				}

				String CFriend::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) + tabs + L"friend" };
					CSimpleDeclaration *declaration;
					for (size_t i = 0; i < Entities.size(); i++)
					{
						if (i > 0)
							result += L",";
						declaration = cast<CSimpleDeclaration *>(Entities[i]);
						for (auto specifier : declaration->Specifiers)
							result += L" " + specifier->toString(in(specifier->Type, {EntityType::Class, EntityType::Enum}) ? tabs : L"", false);
						for (size_t i = 0; i < declaration->Declarators.size(); i++)
						{
							if (i > 0)
								result += L",";
							result += L" " + declaration->Declarators[i]->toString(tabs, false);
						}
					}
					result += L";" + toStringTrailingComments(!is_last);
					return result;
				}

				void CFriend::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"friend";
					for (auto const &declaration : Entities)
					{
						Variable d;
						declaration->toVariable(d, attributes, comments);
						target[L"declarations"].push_back(d);
					}
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}