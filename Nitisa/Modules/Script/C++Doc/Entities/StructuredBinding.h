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
#include "../Range.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			namespace entities
			{
				// [attr] decl-specifier-seq [ref-qualifier] [ sb-identifier-list ] initializer;
				class CStructuredBinding :public CEntity
				{
				public:
					enum class InitializationType
					{
						Equals,
						Braces,
						Parentheses
					};

					struct Identifier
					{
						bool Pack;
						String Name;
					};
				protected:
					void BeforeRelease() override;
				public:
					InitializationType InitializationType;
					Range Initialization;
					std::vector<Identifier> Identifiers; // Instances of CName class
					std::vector<CEntity *> Specifiers;

					CStructuredBinding();

					String toString(const String &tabs, const bool is_last) const override;
					void toVariable(Variable &target, const bool attributes, const bool comments) const override;
				};
			}
		}
	}
}