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
				CTemplate::CTemplate() :
					CEntity(EntityType::Template),
					Requires{ nullptr, nullptr }
				{

				}

				String CTemplate::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) + tabs };
					result += L"template<";
					for (size_t i = 0; i < Parameters.size(); i++)
					{
						if (i > 0)
							result += L", ";
						result += Parameters[i].toString();
					}
					result += L">";
					if (Requires.Begin)
						result += L" requires ...";
					result += L"\n";
					result += Entities[0]->toString(tabs, is_last);
					return result;
				}

				void CTemplate::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"template";
					for (auto const &parameter : Parameters)
						target[L"parameters"].push_back(parameter.toStringEx());
					if (Requires.Begin)
						target[L"requires"] = Requires.toStringEx();
					Entities[0]->toVariable(target[L"entity"], attributes, comments);
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}