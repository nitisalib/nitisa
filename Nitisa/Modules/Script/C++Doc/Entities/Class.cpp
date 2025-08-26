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
				CClass::CClass() :
					CEntity(EntityType::Class),
					ClassType{ ClassType::Class },
					isForward{ true },
					isFinal{ false },
					isTriviallyRelocatableIfEligible{ false },
					isReplaceableIfEligible{ false }
				{

				}

				void CClass::BeforeRelease()
				{
					for (auto base : Bases)
						base->Release();
					Bases.clear();
					CEntity::BeforeRelease();
				}

				String CClass::toString(const String &tabs, const bool is_last) const
				{
					static const std::vector<EntityType> ACCESS_MODIFIERS{ EntityType::Private, EntityType::Protected, EntityType::Public };

					String result;
					switch (ClassType)
					{
					case ClassType::Class:
						result += L"class";
						break;
					case ClassType::Struct:
						result += L"struct";
						break;
					case ClassType::Union:
						result += L"union";
						break;
					}
					result += toStringAttributes(L" ", false, true);
					if (!Identifier.Names.empty())
						result += L" " + Identifier.toString(true);
					if (isFinal)
						result += L" final";
					if (isTriviallyRelocatableIfEligible)
						result += L" trivially_relocatable_if_eligible";
					if (isReplaceableIfEligible)
						result += L" replacable_if_eligible";
					if (!Bases.empty())
					{
						result += L" : ";
						for (size_t i = 0; i < Bases.size(); i++)
						{
							if (i > 0)
								result += L", ";
							result += Bases[i]->toString(L"", false);
						}
					}
					if (!isForward)
					{
						result += L"\n";
						result += tabs + L"{\n";
						for (size_t i = 0; i < Entities.size(); i++)
						{
							if (i > 0 && !in(Entities[i - 1]->Type, ACCESS_MODIFIERS) && !in(Entities[i]->Type, ACCESS_MODIFIERS))
								result += L"\n";
							result += Entities[i]->toString(in(Entities[i]->Type, ACCESS_MODIFIERS) ? tabs : (tabs + L"\t"), false);
						}
						if (Entities.empty())
							result += L"\n";
						result += tabs + L"}";
					}
					return result;
				}

				void CClass::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					if (ClassType == ClassType::Struct)
						target[L"type"] = L"struct";
					else if (ClassType == ClassType::Union)
						target[L"type"] = L"union";
					else
						target[L"type"] = L"class";
					if (!Identifier.Names.empty())
					{
						target[L"name"] = Identifier.toString(false);
						Identifier.toVariable(target[L"identifier"]);
					}
					target[L"is_final"] = isFinal;
					target[L"is_trivially_relocatable_if_eligible"] = isTriviallyRelocatableIfEligible;
					target[L"is_replaceable_if_eligible"] = isReplaceableIfEligible;
					for (auto const &base : Bases)
					{
						Variable b;
						base->toVariable(b, attributes, comments);
						target[L"bases"].push_back(b);
					}
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