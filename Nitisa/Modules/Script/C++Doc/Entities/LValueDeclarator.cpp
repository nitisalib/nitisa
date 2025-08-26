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
				CLValueDeclarator::CLValueDeclarator() :
					CBaseDeclarator(EntityType::LValueDeclarator)
				{

				}

				String CLValueDeclarator::toString(const String &tabs, const bool is_last) const
				{
					String result{ L"&" }, decl;
					if (!CallSpecifiers.empty())
						result += L" " + toStringCallSpecifiers();
					result += toStringAttributes(L" ", false, true);
					if (Declarator)
					{
						if (result.length() > 1)
							result += L" ";
						result += decl = Declarator->toString(tabs, false);
					}
					result += toStringBitfieldAndInitialization(!decl.empty());
					return result;
				}

				void CLValueDeclarator::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"lvalue_declarator";
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