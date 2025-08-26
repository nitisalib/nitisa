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
				CSimpleDeclaration::CSimpleDeclaration() :
					CEntity(EntityType::SimpleDeclaration)
				{

				}

				void CSimpleDeclaration::BeforeRelease()
				{
					for (auto specifier : Specifiers)
						specifier->Release();
					Specifiers.clear();
					for (auto declarator : Declarators)
						declarator->Release();
					Declarators.clear();
					CEntity::BeforeRelease();
				}

				String CSimpleDeclaration::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) };
					bool first{ true };
					for (auto specifier : Specifiers)
					{
						if (first)
						{
							result += tabs;
							first = false;
						}
						else
							result += L" ";
						result += specifier->toString(in(specifier->Type, { EntityType::Class, EntityType::Enum }) ? tabs : L"", false);
					}
					for (size_t i = 0; i < Declarators.size(); i++)
					{
						if (first)
						{
							result += tabs;
							first = false;
						}
						else if (i == 0)
							result += L" ";
						if (i > 0)
							result += L", ";
						result += Declarators[i]->toString(tabs, false);
					}
					result += L";" + toStringTrailingComments(!is_last);
					return result;
				}

				void CSimpleDeclaration::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"simple_declaration";
					for (auto const &specifier : Specifiers)
					{
						Variable s;
						specifier->toVariable(s, attributes, comments);
						target[L"specifiers"].push_back(s);
					}
					for (auto const &declarator : Declarators)
					{
						Variable d;
						declarator->toVariable(d, attributes, comments);
						target[L"declarators"].push_back(d);
					}
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}