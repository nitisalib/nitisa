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
				CRegister::CRegister() :
					CEntity(EntityType::Register)
				{

				}

				String CRegister::toString(const String &tabs, const bool is_last) const
				{
					return L"register";
				}

				void CRegister::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"register";
				}
			}
		}
	}
}