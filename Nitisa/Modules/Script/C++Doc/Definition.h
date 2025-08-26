// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Releasable.h"
#include "../../../Core/Strings.h"
#include "../Core/Tokens.h"
#include "DefinitionType.h"
#include "List.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			class CDefinition :public CReleasable
			{
				friend class CPreProcessor;
			private:
				DefinitionType m_eType;
				String m_sName;
				Tokens m_aTokens;
			protected:
				void BeforeRelease() override;
			public:
				DefinitionType const &Type{ m_eType };
				String const &Name{ m_sName };

				List *Begin;
				List *Body; // Function body start
				StringArray Parameters;
				bool Variadic;

				CDefinition();

				bool operator==(const CDefinition &other);

				CDefinition *Clone() const;
			};
		}
	}
}