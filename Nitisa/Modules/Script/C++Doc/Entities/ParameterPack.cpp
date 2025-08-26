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
				CParameterPack::CParameterPack() :
					CEntity(EntityType::ParameterPack)
				{

				}

				String CParameterPack::toString(const String &tabs, const bool is_last) const
				{
					return L"..." + Identifier.toString(true) + toStringAttributes(L" ", false, true);
				}

				void CParameterPack::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"parameter_pack";
					Identifier.toVariable(target[L"name"]);
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}