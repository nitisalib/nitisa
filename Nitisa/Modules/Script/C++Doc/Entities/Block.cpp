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
				CBlock::CBlock() :
					CEntity(EntityType::Block)
				{

				}

				String CBlock::toString(const String &tabs, const bool is_last) const
				{
					String result{ toStringPrecedingComments(tabs) + toStringAttributes(tabs, true, false) };
					result += tabs + L"{\n";
					for (size_t i = 0; i < Entities.size(); i++)
					{
						if (i > 0)
							result += L"\n";
						result += Entities[i]->toString(tabs + L"\t", false);
					}
					if (Entities.empty())
						result += L"\n";
					result += tabs + L"}" + toStringTrailingComments(!is_last);
					return result;
				}

				void CBlock::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"block";
					for (auto const &entity : Entities)
					{
						Variable e;
						entity->toVariable(e, attributes, comments);
						target[L"entities"].push_back(e);
					}
					toVariableAttributesAndComments(target, attributes, comments);
				}
			}
		}
	}
}