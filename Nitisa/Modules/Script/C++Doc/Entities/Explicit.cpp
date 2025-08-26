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
				CExplicit::CExplicit() :
					CEntity(EntityType::Explicit),
					Body{ nullptr, nullptr }
				{

				}

				String CExplicit::toString(const String &tabs, const bool is_last) const
				{
					String result{ L"explicit" };
					if (Body.Begin)
						result += L"(" + Body.toString() + L")";
					return result;
				}

				void CExplicit::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"explicit";
					if (Body.Begin)
						target[L"body"] = Body.toStringEx();
				}
			}
		}
	}
}