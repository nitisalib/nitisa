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
			CBaseDeclarator::CBaseDeclarator(const EntityType &type) :
				CEntity(type),
				Declarator{ nullptr },
				InitializationType{ InitializationType::None },
				Initialization{ nullptr, nullptr },
				Bitfield{ nullptr, nullptr }
			{

			}

			void CBaseDeclarator::BeforeRelease()
			{
				if (Declarator)
				{
					Declarator->Release();
					Declarator = nullptr;
				}
				for (auto specifier : CallSpecifiers)
					specifier->Release();
				CallSpecifiers.clear();
			}

			String CBaseDeclarator::toStringBitfieldAndInitialization(const bool has_declarator) const
			{
				String result;
				if (Bitfield.Begin)
				{
					if (has_declarator)
						result += L" ";
					result += L": " + Bitfield.toString();
				}
				switch (InitializationType)
				{
				case InitializationType::Equals:
					if (has_declarator)
						result += L" ";
					result += L"= ...";
					break;
				case InitializationType::Parentheses:
					result += L"(...)";
					break;
				case InitializationType::Braces:
					result += L"{...}";
					break;
				default:
					break;
				}
				return result;
			}

			String CBaseDeclarator::toStringCallSpecifiers() const
			{
				String result;
				for (size_t i = 0; i < CallSpecifiers.size(); i++)
				{
					if (i > 0)
						result += L" ";
					result += CallSpecifiers[i]->toString(L"", false);
				}
				return result;
			}

			void CBaseDeclarator::toVariableBitfieldAndInitialization(Variable &target) const
			{
				if (Bitfield.Begin)
					target[L"bitfield"] = Bitfield.toStringEx();
				if (Initialization.Begin)
					target[L"initialization"] = Initialization.toStringEx();
			}

			void CBaseDeclarator::toVariableCallSpecifiers(Variable &target, const bool attributes, const bool comments) const
			{
				for (auto const &specifier : CallSpecifiers)
				{
					Variable s;
					specifier->toVariable(s, attributes, comments);
					target[L"call_specifiers"].push_back(s);
				}
			}
		}
	}
}