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
#include "../Range.h"
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
				class CFunction :public CBaseDeclarator
				{
				protected:
					void BeforeRelease() override;
				public:
					std::vector<CEntity *> Parameters;
					std::vector<CEntity *> Specifiers;
					std::vector<CEntity *> Contracts;
					bool Throw;
					Range ThrowBody;
					bool NoExcept;
					Range NoExceptBody;
					Range Trailing;
					Range Requires;
					bool Abstract;
					bool Default;
					bool Deleted;
					String DeleteReason;
					Range Body; // Begin points to ":" or "try" or "{". End points to "}"

					CFunction();

					String toString(const String &tabs, const bool is_last) const override;
					void toVariable(Variable &target, const bool attributes, const bool comments) const override;
				};
			}
		}
	}
}