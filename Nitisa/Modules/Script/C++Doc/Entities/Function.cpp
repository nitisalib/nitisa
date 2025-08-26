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
				CFunction::CFunction() :
					CBaseDeclarator(EntityType::Function),
					Throw{ false },
					ThrowBody{ nullptr, nullptr },
					NoExcept{ false },
					NoExceptBody{ nullptr, nullptr },
					Trailing{ nullptr, nullptr },
					Requires{ nullptr, nullptr },
					Abstract{ false },
					Default{ false },
					Deleted{ false },
					Body{ nullptr, nullptr }
				{

				}

				void CFunction::BeforeRelease()
				{
					for (auto parameter : Parameters)
						parameter->Release();
					Parameters.clear();
					for (auto specifier : Specifiers)
						specifier->Release();
					Specifiers.clear();
					for (auto contract : Contracts)
						contract->Release();
					Contracts.clear();
					CBaseDeclarator::BeforeRelease();
				}

				String CFunction::toString(const String &tabs, const bool is_last) const
				{
					String result;
					if (Declarator)
						result += Declarator->toString(L"", false);
					result += L"(";
					for (size_t i = 0; i < Parameters.size(); i++)
					{
						if (i == 0)
							result += L"\n";
						result += Parameters[i]->toString(tabs + L"\t", i == Parameters.size() - 1);
					}
					if (!Parameters.empty())
						result += tabs;
					result += L")";
					for (auto specifier : Specifiers)
						result += L" " + specifier->toString(L"", false);
					result += toStringAttributes(L" ", false, true);
					if (Throw)
						result += L" throw (" + ThrowBody.toString() + L")";
					if (NoExcept)
					{
						result += L" noexcept";
						if (NoExceptBody.Begin)
							result += L" (" + NoExceptBody.toString() + L")";
					}
					if (Trailing.Begin)
						result += L" -> " + Trailing.toString();
					if (Requires.Begin)
						result += L" requires ...";
					for (auto contract : Contracts)
						result += L" " + contract->toString(L"", false);
					if (Abstract)
						result += L" = 0";
					if (Default)
						result += L" = default";
					if (Deleted)
					{
						result += L" = delete";
						if (!DeleteReason.empty())
							result += L"(\"" + DeleteReason + L"\")";
					}
					result += toStringBitfieldAndInitialization(true);
					// Don't show body
					return result;
				}

				void CFunction::toVariable(Variable &target, const bool attributes, const bool comments) const
				{
					target[L"type"] = L"function";
					if (Declarator)
						Declarator->toVariable(target[L"declarator"], attributes, comments);
					for (auto const &parameter : Parameters)
					{
						Variable p;
						parameter->toVariable(p, attributes, comments);
						target[L"parameters"].push_back(p);
					}
					for (auto const &specifier : Specifiers)
					{
						Variable s;
						specifier->toVariable(s, attributes, comments);
						target[L"specifiers"].push_back(s);
					}
					for (auto const &contract : Contracts)
					{
						Variable c;
						contract->toVariable(c, attributes, comments);
						target[L"contracts"].push_back(c);
					}
					if (Throw)
						target[L"throw"] = ThrowBody.toStringEx();
					if (NoExcept)
						target[L"noexcept"] = NoExceptBody.toStringEx();
					if (Trailing.Begin)
						target[L"trailing"] = Trailing.toStringEx();
					if (Requires.Begin)
						target[L"requires"] = Requires.toStringEx();
					target[L"abstract"] = Abstract;
					target[L"default"] = Default;
					target[L"deleted"] = Deleted;
					target[L"delete_reason"] = DeleteReason;
					toVariableBitfieldAndInitialization(target);
					toVariableAttributesAndComments(target, attributes, comments);
					toVariableCallSpecifiers(target, attributes, comments);
				}
			}
		}
	}
}