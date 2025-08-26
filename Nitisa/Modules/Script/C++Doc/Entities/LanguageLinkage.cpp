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
				CLanguageLinkage::CLanguageLinkage() :
					CEntity(EntityType::LanguageLinkage)
				{

				}

				String CLanguageLinkage::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) };
					result += tabs + L"extern \"" + Name + L"\"\n";
					result += Entities[0]->toString(tabs, is_last);
					return result;
				}

				void CLanguageLinkage::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"language_linkage";
					target[L"language"] = Name;
					Entities[0]->toVariable(target[L"entity"], attributes, comments);
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}