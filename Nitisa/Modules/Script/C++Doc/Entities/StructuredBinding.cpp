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
				CStructuredBinding::CStructuredBinding() :
					CEntity(EntityType::StructuredBinding),
					InitializationType{ InitializationType::Equals },
					Initialization{ nullptr, nullptr}
				{

				}

				void CStructuredBinding::BeforeRelease()
				{
					for (auto specifier : Specifiers)
						specifier->Release();
					Specifiers.clear();
					CEntity::BeforeRelease();
				}

				String CStructuredBinding::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) + tabs + toStringAttributes(L"", false, true) };
					bool first{ true };
					for (auto list : AttributeLists)
						if (list->isAfter)
						{
							first = false;
							break;
						}
					for (auto specifier : Specifiers)
					{
						if (!first)
							result += L" ";
						first = false;
						result += specifier->toString(L"", false);
					}
					result += L" [";
					for (size_t i = 0; i < Identifiers.size(); i++)
					{
						if (i > 0)
							result += L", ";
						if (Identifiers[i].Pack)
							result += L"...";
						result += Identifiers[i].Name;
					}
					result += L"]";
					switch (InitializationType)
					{
					case InitializationType::Equals:
						result += L" = ...";
						break;
					case InitializationType::Parentheses:
						result += L"(...)";
						break;
					case InitializationType::Braces:
						result += L"{...}";
						break;
					}
					result += L";" + toStringTrailingComments(!is_last);
					return result;
				}

				void CStructuredBinding::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"structured_binding";
					for (auto const &specifier : Specifiers)
					{
						Variable s;
						specifier->toVariable(s, attributes, comments);
						target[L"specifiers"].push_back(s);
					}
					for (auto const &identifier : Identifiers)
					{
						Variable i;
						i[L"pack"] = identifier.Pack;
						i[L"name"] = identifier.Name;
						target[L"identifiers"].push_back(i);
					}
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}