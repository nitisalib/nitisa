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
				CNoPtrDeclarator::CNoPtrDeclarator() :
					CBaseDeclarator(EntityType::NoPtrDeclarator)
				{

				}

				String CNoPtrDeclarator::toString(const String &tabs, const bool is_last) const
				{
					String result{ L"(" + toStringCallSpecifiers() };
					if (Declarator)
					{
						if (!CallSpecifiers.empty())
							result += L" ";
						result += Declarator->toString(tabs, false);
					}
					result += L")" + toStringBitfieldAndInitialization(true);
					return result;
				}

				void CNoPtrDeclarator::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"noptr_declarator";
					if (Declarator)
						Declarator->toVariable(target[L"declarator"], attributes, comments);
					toVariableBitfieldAndInitialization(target);
					toVariableCallSpecifiers(target, attributes, comments);
				}
			}
		}
	}
}