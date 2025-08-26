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
#include "../Core/Variable.h"
#include "Range.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			class CAttribute;

			class CAttributeList :public CReleasable
			{
			protected:
				void BeforeRelease() override;
			public:
				bool isAfter; // Whether attribute list is located before of after an entity it belongs to
				bool isPackExpansion; // Whether attribte-list ends with ...
				String Namespace; // Not empty for form [[using attribute-namespace: attribute-list]]
				std::vector<CAttribute *> Attributes;
				Range AlignAs; // For "alignas" only

				CAttributeList();

				String toString() const;
				void toVariable(Variable &target) const;
			};
		}
	}
}