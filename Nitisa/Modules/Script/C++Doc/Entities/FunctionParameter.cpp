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
				CFunctionParameter::CFunctionParameter() :
					CEntity(EntityType::FunctionParameter),
					This{ false },
					Declarator{ nullptr },
					ArrayDeclarator{ nullptr }
				{

				}

				void CFunctionParameter::BeforeRelease()
				{
					if (Declarator)
					{
						Declarator->Release();
						Declarator = nullptr;
					}
					if (ArrayDeclarator)
					{
						ArrayDeclarator->Release();
						ArrayDeclarator = nullptr;
					}
					CEntity::BeforeRelease();
				}

				String CFunctionParameter::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, true) + tabs };
					bool first{ true };
					if (This)
					{
						result += L"this";
						first = false;
					}
					for (auto specifier : Specifiers)
					{
						if (!first)
							result += L" ";
						first = false;
						result += specifier->toString(L"", false);
					}
					if (ArrayDeclarator)
						result += ArrayDeclarator->toString(L"", false);
					if (Declarator)
					{
						if (!first)
							result += L" ";
						result += Declarator->toString(tabs, false);
					}
					if (!Declarator && Specifiers.empty())
						result += L"...";
					if (!is_last)
						result += L",";
					result += toStringTrailingComments(true);
					return result;
				}

				void CFunctionParameter::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"function_parameter";
					target[L"has_this"] = This;
					for (auto const &specifier : Specifiers)
					{
						Variable s;
						specifier->toVariable(s, attributes, comments);
						target[L"specifiers"].push_back(s);
					}
					if (ArrayDeclarator)
						ArrayDeclarator->toVariable(target[L"array_declarator"], attributes, comments);
					if (Declarator)
						Declarator->toVariable(target[L"declarator"], attributes, comments);
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}