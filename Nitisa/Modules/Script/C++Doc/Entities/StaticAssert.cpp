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
				CStaticAssert::CStaticAssert() :
					CEntity(EntityType::StaticAssert),
					Body{ nullptr, nullptr }
				{

				}

				String CStaticAssert::toString(const String &tabs, const bool is_last) const
				{
					return toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) + tabs + L"static_assert(...);" + toStringTrailingComments(!is_last);
				}

				void CStaticAssert::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"static_assert";
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}