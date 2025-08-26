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
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			class CEntity;

			namespace entities
			{
				class CPtrDeclarator :public CBaseDeclarator
				{
				protected:
					void BeforeRelease() override;
				public:
					std::vector<CEntity *> Specifiers;
			
					CPtrDeclarator();

					String toString(const String &tabs, const bool is_last) const override;
					void toVariable(Variable &target, const bool attributes, const bool comments) const override;
				};
			}
		}
	}
}