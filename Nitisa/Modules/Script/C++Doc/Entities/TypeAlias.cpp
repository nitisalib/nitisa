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
				CTypeAlias::CTypeAlias() :
					CEntity(EntityType::TypeAlias),
					TypeId{ nullptr, nullptr }
				{

				}

				String CTypeAlias::toString(const String &tabs, const bool is_last) const
				{
					return toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false)
						+ tabs + L"using " + Alias + toStringAttributes(L" ", false, true) + L" = " + TypeId.toString() + L";" + toStringTrailingComments(!is_last);
				}

				void CTypeAlias::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"type_alias";
					target[L"alias"] = Alias;
					target[L"type_id"] = TypeId.toStringEx();
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}