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
				CComment::CComment(const String &value, const bool multiline) :
					CEntity(EntityType::Comment),
					m_sValue{ value },
					m_bMultiLine{ multiline }
				{

				}

				String CComment::toString(const String &tabs, const bool is_last) const
				{
					String result;
					if (m_bMultiLine)
					{
						String content{ Trim(ReplaceAll(m_sValue, L"\t", L"")) };
						ReplaceAllDirect(content, L"\r\n", L"\n");
						ReplaceAllDirect(content, L"\r", L"\n");
						size_t l{ content.length() };
						while (true)
						{
							ReplaceAllDirect(content, L"\n\n", L"\n");
							if (content.length() == l)
								break;
							l = content.length();
						}
						StringArray lines{ Explode(content, L"\n") };
						for (auto &line : lines)
						{
							TrimDirect(line);
							if (!line.empty() && line[0] == L'*')
							{
								line.erase(line.begin());
								TrimDirect(line);
							}
						}
						for (auto const &line : lines)
						{
							if (!result.empty())
								result += L"\n";
							result += tabs + L"// " + line;
						}
					}
					else
						result = tabs + L"// " + Trim(m_sValue);
					if (!is_last)
						result += L"\n";
					return result;
				}

				void CComment::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"comment";
					target[L"content"] = m_sValue;
					target[L"is_multiline"] = m_bMultiLine;
				}
			}
		}
	}
}