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
				CPtrDeclarator::CPtrDeclarator() :
					CBaseDeclarator(EntityType::PtrDeclarator)
				{

				}

				void CPtrDeclarator::BeforeRelease()
				{
					for (auto specifier : Specifiers)
						specifier->Release();
					Specifiers.clear();
					CBaseDeclarator::BeforeRelease();
				}

				String CPtrDeclarator::toString(const String &tabs, const bool is_last) const
				{
					String result{ L"*" }, decl;
					if (!CallSpecifiers.empty())
						result += L" " + toStringCallSpecifiers();
					result += toStringAttributes(L" ", false, true);
					for (auto specifier : Specifiers)
						result += L" " + specifier->toString(L"", false);
					if (Declarator)
					{
						if (result.length() > 1)
							result += L" ";
						result += decl = Declarator->toString(tabs, false);
					}
					result += toStringBitfieldAndInitialization(!decl.empty());
					return result;
				}

				void CPtrDeclarator::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"ptr_declarator";
					for (auto const &specifier : Specifiers)
					{
						Variable s;
						specifier->toVariable(s, attributes, comments);
						target[L"specifiers"].push_back(s);
					}
					if (Declarator)
						Declarator->toVariable(target[L"declarator"], attributes, comments);
					toVariableBitfieldAndInitialization(target);
					toVariableAttributesAndComments(target, attributes, comments);
					toVariableCallSpecifiers(target, attributes, comments);
				}
			}
		}
	}
}