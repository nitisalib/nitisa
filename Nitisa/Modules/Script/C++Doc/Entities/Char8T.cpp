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
				CChar8T::CChar8T() :
					CEntity(EntityType::Char8T)
				{

				}

				String CChar8T::toString(const String &tabs, const bool is_last) const
				{
					return L"char8_t";
				}

				void CChar8T::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"char8_t";
				}
			}
		}
	}
}