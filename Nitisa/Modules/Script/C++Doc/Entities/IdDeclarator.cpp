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
				CIdDeclarator::CIdDeclarator() :
					CBaseDeclarator(EntityType::IdDeclarator),
					Pack{ false }
				{

				}

				void CIdDeclarator::BeforeRelease()
				{
					for (auto specifier : Specifiers)
						specifier->Release();
					Specifiers.clear();
					CBaseDeclarator::BeforeRelease();
				}

				String CIdDeclarator::toString(const String &tabs, const bool is_last) const
				{
					String decl{ Identifier.toString(true) }, result{ toStringCallSpecifiers() };
					if (Pack)
					{
						if (!result.empty())
							result += L" ";
						result += L"...";
					}
					else if (!result.empty())
						result += L" ";
					result += decl;
					result += toStringAttributes(L" ", false, true);
					for (auto specifier : Specifiers)
					{
						if (!result.empty())
							result += L" ";
						result += specifier->toString(L"", false);
					}
					if (Declarator)
					{
						if (!result.empty())
							result += L" ";
						result += Declarator->toString(tabs, false);
					}
					result += toStringBitfieldAndInitialization(!decl.empty());
					return result;
				}

				void CIdDeclarator::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"id_declarator";
					target[L"is_pack"] = Pack;
					Identifier.toVariable(target[L"name"]);
					for (auto const &specifier : Specifiers)
					{
						Variable s;
						specifier->toVariable(s, attributes, comments);
						target[L"specifiers"].push_back(s);
					}
					if (Declarator)
						Declarator->toVariable(target[L"declarator"], attributes, comments);
					toVariableBitfieldAndInitialization(target);
					toVariableCallSpecifiers(target, attributes, comments);
				}
			}
		}
	}
}