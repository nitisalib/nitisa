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
#include "../Range.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			namespace entities
			{
				class CClassBase :public CEntity
				{
				public:
					bool isVirtual;
					bool isPublic;
					bool isProtected;
					bool isPrivate;
					bool Pack;
					CIdentifier Identifier;
					Range Decltype; // Begin = Next("("), End = Prev(")")
					Range PackIndex; // if there is ...[...] after identifier. Begin = Next("["), End = Prev("]")

					CClassBase();

					String toString(const String &tabs, const bool is_last) const override;
					void toVariable(Variable &target, const bool attributes, const bool comments) const override;
				};
			}
		}
	}
}