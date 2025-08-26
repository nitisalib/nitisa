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
			CIdentifier::CIdentifier() :
				Destructor{ false },
				UserDefinedOperator{ false }
			{

			}

			String CIdentifier::toString(const bool arguments) const
			{
				String result;
				for (size_t i = 0; i < Names.size(); i++)
				{
					if (i > 0)
						result += L"::";
					if (Destructor && i == Names.size() - 1)
						result += L"~";
					if (arguments && Names[i].Template)
						result += L"template ";
					result += Names[i].Name;
					if (arguments && (Operator.empty() || i != Names.size() - 1) && Names[i].hasArguments)
					{
						result += L"<";
						for (size_t j = 0; j < Names[i].Arguments.size(); j++)
						{
							if (j > 0)
								result += L", ";
							result += Names[i].Arguments[j].toString();
						}
						result += L">";
					}
				}
				if (UserDefinedOperator || !Operator.empty())
					result += L" ";
				if (UserDefinedOperator)
					result += L"\"\"" + Operator;
				else
					result += Operator;
				if (arguments && !Operator.empty() && Names[Names.size() - 1].hasArguments)
				{
					result += L"<";
					for (size_t j = 0; j < Names[Names.size() - 1].Arguments.size(); j++)
					{
						if (j > 0)
							result += L", ";
						result += Names[Names.size() - 1].Arguments[j].toString();
					}
					result += L">";
				}
				return result;
			}

			void CIdentifier::toVariable(Variable &target) const
			{
				target[L"is_destructor"] = Destructor;
				target[L"is_user_defined_operator"] = UserDefinedOperator;
				target[L"operator"] = Operator;
				for (auto const &name : Names)
				{
					Variable n;
					n[L"is_template"] = name.Template;
					n[L"has_arguments"] = name.hasArguments;
					n[L"name"] = name.Name;
					for (auto const &arg : name.Arguments)
						n[L"arguments"].push_back(arg.toStringEx());
					target[L"parts"].push_back(n);
				}
			}
		}
	}
}