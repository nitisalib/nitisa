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
				CNamespaceAlias::CNamespaceAlias() :
					CEntity(EntityType::NamespaceAlias)
				{

				}

				String CNamespaceAlias::toString(const String &tabs, const bool is_last) const
				{
					return toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false)
						+ tabs + L"namespace " + Alias + L" = " + Identifier.toString(true) + L";" + toStringTrailingComments(!is_last);
				}

				void CNamespaceAlias::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"namespace_alias";
					target[L"alias"] = Alias;
					Identifier.toVariable(target[L"namespace"]);
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}