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
			CEntity::CEntity(const EntityType &type) :
				CReleasable(),
				m_eType{ type }
			{

			}

			void CEntity::BeforeRelease()
			{
				for (auto entity : Entities)
					entity->Release();
				Entities.clear();
				for (auto attribute_list : AttributeLists)
					attribute_list->Release();
				AttributeLists.clear();
				Comments.clear();
			}

			String CEntity::toStringPrecedingComments(const String &tabs) const
			{
				String result;
				for (auto const &comment : Comments)
				{
					if (comment.isAfter)
						continue;
					if (!comment.isMultiline)
					{
						result += tabs + L"// " + Trim(comment.Content) + L"\n";
						continue;
					}
					String content{ Trim(ReplaceAll(comment.Content, L"\t", L"")) };
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
						result += tabs + L"// " + line + L"\n";
				}
				return result;
			}

			String CEntity::toStringAttributes(const String &tabs, const bool nl, const bool is_after) const
			{
				String result;
				bool first{ true };
				for (size_t i = 0; i < AttributeLists.size(); i++)
				{
					if (AttributeLists[i]->isAfter != is_after)
						continue;
					if (first)
					{
						result += tabs;
						first = false;
					}
					else
						result += L" ";
					result += AttributeLists[i]->toString();
				}
				if (nl && !first)
					result += L"\n";
				return result;
			}

			String CEntity::toStringTrailingComments(const bool nl) const
			{
				String result;
				for (auto const &comment : Comments)
				{
					if (!comment.isAfter)
						continue;
					if (!comment.isMultiline)
					{
						result += L" // " + Trim(comment.Content);
						break;
					}

					StringArray lines{ Explode(comment.Content, L"\n") };
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
						if (!line.empty())
							result += L" /* " + line + L" */";
				}
				if (nl)
					result += L"\n";
				return result;
			}

			void CEntity::toVariableAttributesAndComments(Variable &target, const bool attributes, const bool comments) const
			{
				if (attributes)
					for (auto const &attr : AttributeLists)
					{
						Variable a;
						attr->toVariable(a);
						target[L"attribute_lists"].push_back(a);
					}
				if (comments)
					for (auto const &comment : Comments)
					{
						Variable c;
						c[L"content"] = comment.Content;
						c[L"is_multiline"] = comment.isMultiline;
						target[L"comments"].push_back(c);
					}
			}
		}
	}
}