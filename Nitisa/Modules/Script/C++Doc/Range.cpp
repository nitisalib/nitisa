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
			String Range::toString() const
			{
				static const StringArray SPACE_BEFORE{ L"=" };
				static const StringArray SPACE_AFTER{ L",", L"=" };

				String result;
				List *current{ Begin };
				while (current)
				{
					if (!isNewLines(*current) && !isComment(*current))
					{
						if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, SPACE_BEFORE))
							result += L" ";
						result += TokenToString(*current->Item);
						if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, SPACE_AFTER))
							result += L" ";
						else if (current->Item->Type == TokenType::Identifier && current != End && current->Next->Item->Type == TokenType::Identifier)
							result += L" ";
					}
					if (current == End)
						break;
					current = current->Next;
				}
				return result;
			}

			String Range::toStringEx() const
			{
				String result;
				List *current{ Begin }, *prev1{ nullptr }, *prev2{ nullptr };
				while (current)
				{
					switch (current->Item->Type)
					{
					case TokenType::Unknown:
						if (prev1)
							result += L" ";
						result += TokenToString(*current->Item);
						prev2 = prev1;
						prev1 = current;
						break;
					case TokenType::String:
						if (prev1 && (prev1->Item->Type != TokenType::Operator || !in(prev1->Item->Op->Name, StringArray{ L"[", L"<:", L"[[", L"<:<:", L"(" })))
							result += L" ";
						result += TokenToString(*current->Item);
						prev2 = prev1;
						prev1 = current;
						break;
					case TokenType::Integer:
					case TokenType::Float:
					case TokenType::Identifier:
						if (prev1)
						{
							if (prev1->Item->Type == TokenType::Operator)
							{
								if (in(prev1->Item->Op->Name, StringArray{ L"+", L"-"}))
								{
									if (!prev2 || prev2->Item->Type != TokenType::Operator)
										result += L" ";
								}
								else if (!in(prev1->Item->Op->Name, StringArray{ L"[", L"<:", L"[[", L"<:<:", L"(", L"++", L"--", L"!", L"~" }))
									result += L" ";
							}
							else
								result += L" ";
						}
						result += TokenToString(*current->Item);
						prev2 = prev1;
						prev1 = current;
						break;
					case TokenType::Operator:
						if (!in(current->Item->Op->Name, StringArray{ L";", L",", L"::", L".", L".*", L"->", L"->*" }) && prev1)
						{
							if (prev1->Item->Type == TokenType::Operator)
							{
								if (!in(current->Item->Op->Name, StringArray{ L"[", L"<:", L"[[", L"<:<:", L"(" }) ||
									!in(prev1->Item->Op->Name, StringArray{ L"[", L"<:", L"[[", L"<:<:", L"(" }))
									result += L" ";
							}
							else if (!in(current->Item->Op->Name, StringArray{ L"[", L"<:", L"[[", L"<:<:", L"(", L"<", L"++", L"--" }))
								result += L" ";
						}
						result += TokenToString(*current->Item);
						prev2 = prev1;
						prev1 = current;
						break;
					default:
						break;
					}
					if (current == End)
						break;
					current = current->Next;
				}
				return result;
			}
		}
	}
}