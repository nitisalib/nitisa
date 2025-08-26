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
				CExport::CExport() :
					CEntity(EntityType::Export)
				{

				}

				String CExport::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) + tabs + L"export" };
					if (Entities[0]->Type == EntityType::Block)
						result += L"\n" + Entities[0]->toString(tabs, is_last);
					else
						result += L" " + Entities[0]->toString(L"", is_last);
					return result;
				}

				void CExport::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"export";
					Entities[0]->toVariable(target[L"entity"], attributes, comments);
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}