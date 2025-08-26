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
				CFunctionPostContract::CFunctionPostContract() :
					CEntity(EntityType::FunctionPostContract),
					Body{ nullptr, nullptr }
				{

				}

				String CFunctionPostContract::toString(const String &tabs, const bool is_last) const
				{
					return L"post(" + Body.toString() + L")";
				}

				void CFunctionPostContract::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"post";
					target[L"body"] = Body.toStringEx();
				}
			}
		}
	}
}