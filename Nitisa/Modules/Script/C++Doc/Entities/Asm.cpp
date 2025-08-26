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
				CAsm::CAsm() :
					CEntity(EntityType::Asm),
					Body{ nullptr, nullptr }
				{

				}

				String CAsm::toString(const String &tabs, const bool is_last) const
				{
					return toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) + tabs + L"asm(...);" + toStringTrailingComments(!is_last);
				}

				void CAsm::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"asm";
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}