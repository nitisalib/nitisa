// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../../Core/Strings.h"
#include "../../Core/Variable.h"
#include "../BaseDeclarator.h"
#include "../Identifier.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			namespace entities
			{
				// 1. unqualified-id [attr??]
				// 2. qualified-id [attr??]
				// 3. nested-name-specifier * [attr?] [cv] declarator
				class CIdDeclarator :public CBaseDeclarator
				{
				protected:
					void BeforeRelease() override;
				public:
					bool Pack;
					CIdentifier Identifier;
					std::vector<CEntity *> Specifiers; // [cv]

					CIdDeclarator();

					String toString(const String &tabs, const bool is_last) const override;
					void toVariable(Variable &target, const bool attributes, const bool comments) const override;
				};
			}
		}
	}
}