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
		class IListItemSelectLabel :public virtual IListItemLabel
		{
		protected:
			IListItemSelectLabel() = default;
			~IListItemSelectLabel() = default;
			IListItemSelectLabel(const IListItemSelectLabel &other) = delete;
			IListItemSelectLabel(IListItemSelectLabel &&other) = delete;
			IListItemSelectLabel &operator=(const IListItemSelectLabel &other) = delete;
			IListItemSelectLabel &operator=(IListItemSelectLabel &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}