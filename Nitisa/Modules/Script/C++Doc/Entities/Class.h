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
				class CClassBase;

				class CClass :public CEntity
				{
				public:
					enum class ClassType
					{
						Class,
						Struct,
						Union
					};
				protected:
					void BeforeRelease() override;
				public:
					ClassType ClassType;
					CIdentifier Identifier;
					bool isForward;
					bool isFinal;
					bool isTriviallyRelocatableIfEligible;
					bool isReplaceableIfEligible;
					std::vector<CClassBase*> Bases;

					CClass();

					String toString(const String &tabs, const bool is_last) const override;
					void toVariable(Variable &target, const bool attributes, const bool comments) const override;
				};
			}
		}
	}
}