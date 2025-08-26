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
				CNaked::CNaked() :
					CEntity(EntityType::Naked)
				{

				}

				String CNaked::toString(const String &tabs, const bool is_last) const
				{
					return L"__declspec(naked)";
				}

				void CNaked::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"__declspec(naked)";
				}
			}
		}
	}
}