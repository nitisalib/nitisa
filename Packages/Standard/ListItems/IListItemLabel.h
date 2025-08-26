// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IListItemCaption.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemLabel :public virtual IListItemCaption
		{
		protected:
			IListItemLabel() = default;
			~IListItemLabel() = default;
			IListItemLabel(const IListItemLabel &other) = delete;
			IListItemLabel(IListItemLabel &&other) = delete;
			IListItemLabel &operator=(const IListItemLabel &other) = delete;
			IListItemLabel &operator=(IListItemLabel &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}