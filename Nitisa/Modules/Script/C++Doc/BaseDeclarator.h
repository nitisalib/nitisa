// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../Core/Variable.h"
#include "Entity.h"
#include "EntityType.h"
#include "Range.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			class CBaseDeclarator :public CEntity
			{
			public:
				enum class InitializationType
				{
					None,
					Equals, // = expression
					Parentheses, // (...)
					Braces, // {...}
				};
			protected:
				void BeforeRelease() override;

				CBaseDeclarator(const EntityType &type);

				String toStringBitfieldAndInitialization(const bool has_declarator) const;
				String toStringCallSpecifiers() const;
				void toVariableBitfieldAndInitialization(Variable &target) const;
				void toVariableCallSpecifiers(Variable &target, const bool attributes, const bool comments) const;
			public:
				CEntity *Declarator;
				InitializationType InitializationType;
				Range Initialization;
				Range Bitfield;
				std::vector<CEntity *> CallSpecifiers;
			};
		}
	}
}