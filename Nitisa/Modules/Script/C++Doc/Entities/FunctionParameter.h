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
#include "../Entity.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			namespace entities
			{
				// No declarator and specifiers means it is "..."
				class CFunctionParameter :public CEntity
				{
				protected:
					void BeforeRelease() override;
				public:
					bool This;
					CEntity *Declarator;
					CEntity *ArrayDeclarator;
					std::vector<CEntity *> Specifiers;

					CFunctionParameter();

					String toString(const String &tabs, const bool is_last) const override;
					void toVariable(Variable &target, const bool attributes, const bool comments) const override;
				};
			}
		}
	}
}