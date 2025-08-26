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
			CDefinition::CDefinition() :
				CReleasable(),
				m_eType{ DefinitionType::Define },
				Begin{ nullptr },
				Body{ nullptr },
				Variadic{ false }
			{

			}

			void CDefinition::BeforeRelease()
			{
				List *head{ Head(Begin) };
				Free(head);
			}

			bool CDefinition::operator==(const CDefinition &other)
			{
				if (m_eType != other.m_eType)
					return false;
				if (m_sName != other.m_sName)
					return false;
				List *l1{ Begin }, *l2{ other.Begin };
				while (true)
				{
					if (!l1)
						return l2 ? false : true;
					if (!l2)
						return l1 ? false : true;
					if (l1->Item != l2->Item)
						return false;
					l1 = l1->Next;
					l2 = l2->Next;
				}
				return true;
			}

			CDefinition *CDefinition::Clone() const
			{
				CDefinition *result{ new CDefinition() };
				result->m_sName = m_sName;
				result->m_eType = m_eType;
				result->Parameters = Parameters;
				result->Variadic = Variadic;
				List *list{ Begin };
				while (list)
				{
					result->m_aTokens.push_back(*list->Item);
					list = list->Next;
				}
				list = Begin;
				List *tail{ nullptr };
				for (auto &token : result->m_aTokens)
				{
					tail = Append(result->Begin, tail, TokenEx{ &token, list->Item.Index });
					if (list == Body)
						result->Body = tail;
					list = list->Next;
				}
				return result;
			}
		}
	}
}