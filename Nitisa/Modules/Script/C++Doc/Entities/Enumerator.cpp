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
				CEnumerator::CEnumerator() :
					CEntity(EntityType::Enumerator),
					Value{ nullptr, nullptr }
				{

				}

				String CEnumerator::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) + tabs + Name };
					if (Value.Begin)
						result += L" = " + Value.toString();
					if (!is_last)
						result += L",";
					result += toStringTrailingComments(true);
					return result;
				}

				void CEnumerator::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"enumerator";
					target[L"name"] = Name;
					if (Value.Begin)
						target[L"body"] = Value.toStringEx();
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}