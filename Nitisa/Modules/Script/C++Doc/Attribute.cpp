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
			CAttribute::CAttribute() :
				CReleasable(),
				hasArguments{ false }
			{

			}
		
			String CAttribute::toString() const
			{
				String result{ Identifier.toString(true) };
				if (hasArguments)
				{
					result += L"(";
					for (size_t i = 0; i < Arguments.size(); i++)
					{
						if (i > 0)
							result += L", ";
						result += Arguments[i].toString();
					}
					result += L")";
				}
				return result;
			}

			void CAttribute::toVariable(Variable &target) const
			{
				Identifier.toVariable(target[L"name"]);
				target[L"has_arguments"] = hasArguments;
				for (auto const &arg : Arguments)
					target[L"arguments"].push_back(arg.toStringEx());
			}
		}
	}
}