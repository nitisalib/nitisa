// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IListItemLabel.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemSelectCategory :public virtual IListItemLabel
		{
		protected:
			IListItemSelectCategory() = default;
			~IListItemSelectCategory() = default;
			IListItemSelectCategory(const IListItemSelectCategory &other) = delete;
			IListItemSelectCategory(IListItemSelectCategory &&other) = delete;
			IListItemSelectCategory &operator=(const IListItemSelectCategory &other) = delete;
			IListItemSelectCategory &operator=(IListItemSelectCategory &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}