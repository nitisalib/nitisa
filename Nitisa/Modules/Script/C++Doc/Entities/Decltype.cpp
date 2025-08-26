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
				CDecltype::CDecltype() :
					CEntity(EntityType::Decltype),
					Body{ nullptr, nullptr }
				{

				}

				String CDecltype::toString(const String &tabs, const bool is_last) const
				{
					return L"decltype(" + Body.toString() + L")";
				}

				void CDecltype::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"decltype";
					target[L"body"] = Body.toStringEx();
				}
			}
		}
	}
}