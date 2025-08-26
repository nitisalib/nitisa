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
				CName::CName() :
					CEntity(EntityType::Name),
					ParameterPack{ false }
				{

				}

				String CName::toString(const String &tabs, const bool is_last) const
				{
					String result{ Identifier.toString(true) };
					if (ParameterPack)
						result += L"...";
					return result;
				}

				void CName::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"name";
					target[L"is_parameter_pack"] = ParameterPack;
					target[L"name"] = Identifier.toString(false);
					Identifier.toVariable(target[L"identifier"]);
				}
			}
		}
	}
}