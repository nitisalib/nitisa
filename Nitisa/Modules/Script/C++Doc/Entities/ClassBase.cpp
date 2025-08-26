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
				CClassBase::CClassBase() :
					CEntity(EntityType::ClassBase),
					isVirtual{ false },
					isPublic{ false },
					isProtected{ false },
					isPrivate{ false },
					Pack{ false },
					Decltype{ nullptr, nullptr },
					PackIndex{ nullptr, nullptr }
				{

				}

				String CClassBase::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringAttributes(L"", false, false) };
					if (isVirtual)
					{
						if (!result.empty())
							result += L" ";
						result += L"virtual";
					}
					if (isPrivate)
					{
						if (!result.empty())
							result += L" ";
						result += L"private";
					}
					if (isProtected)
					{
						if (!result.empty())
							result += L" ";
						result += L"protected";
					}
					if (isPublic)
					{
						if (!result.empty())
							result += L" ";
						result += L"public";
					}
					if (Decltype.Begin)
					{
						if (!result.empty())
							result += L" ";
						result += L"decltype(...)";
					}
					if (!result.empty())
						result += L" ";
					result += Identifier.toString(true);
					if (PackIndex.Begin)
						result += L"...[...]";
					if (Pack)
						result += L"...";
					return result;
				}

				void CClassBase::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"class_base";
					target[L"is_virtual"] = isVirtual;
					target[L"is_private"] = isPrivate;
					target[L"is_protected"] = isProtected;
					target[L"is_public"] = isPublic;
					target[L"is_pack"] = Pack;
					target[L"name"] = Identifier.toString(false);
					Identifier.toVariable(target[L"identifier"]);
					if (Decltype.Begin)
						target[L"decltype"] = Decltype.toStringEx();
					if (PackIndex.Begin)
						target[L"pack_indexing"] = PackIndex.toStringEx();
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}