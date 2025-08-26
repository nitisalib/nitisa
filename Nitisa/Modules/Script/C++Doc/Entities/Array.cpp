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
				CArray::CArray() :
					CBaseDeclarator(EntityType::Array),
					Body{ nullptr, nullptr }
				{

				}

				String CArray::toString(const String &tabs, const bool is_last) const
				{
					String result;
					if (Declarator)
						result += Declarator->toString(L"", false);
					result += L"[" + Body.toString() + L"]" + toStringBitfieldAndInitialization(true);
					return result;
				}

				void CArray::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"array";
					if (Declarator)
						Declarator->toVariable(target[L"declarator"], attributes, comments);
					target[L"body"] = Body.toStringEx();
					toVariableBitfieldAndInitialization(target);
				}
			}
		}
	}
}