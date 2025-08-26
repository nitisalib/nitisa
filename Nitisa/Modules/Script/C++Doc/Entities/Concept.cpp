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
				CConcept::CConcept() :
					CEntity(EntityType::Concept),
					Body{ nullptr, nullptr }
				{

				}

				String CConcept::toString(const String &tabs, const bool is_last) const
				{
					return tabs + L"concept " + Name + toStringAttributes(L" ", false, true) + L" = ...;" + toStringTrailingComments(!is_last);
				}

				void CConcept::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"concept";
					target[L"name"] = Name;
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}