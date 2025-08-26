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
				CImport::CImport() :
					CEntity(EntityType::Import),
					isExport{ false },
					isStdHeader{ false }
				{

				}

				String CImport::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) };
					if (isExport)
						result += tabs + L"export import";
					else
						result += tabs + L"import";
					if (!Name.empty())
						result += L" " + Name;
					if (!Partition.empty())
						result += L" " + Partition;
					if (!Header.empty())
					{
						result += L" ";
						if (isStdHeader)
							result += L"<" + Header + L">";
						else
							result += L"\"" + Header + L"\"";
					}
					result += toStringAttributes(L" ", false, true) + L";" + toStringTrailingComments(!is_last);
					return result;
				}

				void CImport::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"import";
					target[L"is_export"] = isExport;
					target[L"name"] = Name;
					target[L"partition"] = Partition;
					target[L"header"] = Header;
					target[L"is_std_header"] = isStdHeader;
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}