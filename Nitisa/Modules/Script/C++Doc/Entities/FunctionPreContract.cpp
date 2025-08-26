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
				CFunctionPreContract::CFunctionPreContract() :
					CEntity(EntityType::FunctionPreContract),
					Body{ nullptr, nullptr }
				{

				}

				String CFunctionPreContract::toString(const String &tabs, const bool is_last) const
				{
					return L"pre(" + Body.toString() + L")";
				}

				void CFunctionPreContract::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"pre";
					target[L"body"] = Body.toStringEx();
				}
			}
		}
	}
}