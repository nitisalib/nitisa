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
				CChar32T::CChar32T() :
					CEntity(EntityType::Char32T)
				{

				}

				String CChar32T::toString(const String &tabs, const bool is_last) const
				{
					return L"char32_t";
				}

				void CChar32T::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"char32_t";
				}
			}
		}
	}
}