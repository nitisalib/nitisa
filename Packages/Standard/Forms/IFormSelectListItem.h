// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"

namespace nitisa
{
	namespace standard
	{
		class IFormSelectListItem
		{
		protected:
			IFormSelectListItem() = default;
			~IFormSelectListItem() = default;
			IFormSelectListItem(const IFormSelectListItem &other) = delete;
			IFormSelectListItem(IFormSelectListItem &&other) = delete;
			IFormSelectListItem &operator=(const IFormSelectListItem &other) = delete;
			IFormSelectListItem &operator=(IFormSelectListItem &&other) = delete;
		public:
			virtual int getItemTypeIndex() = 0; // Return item type index
			virtual String getItemCaption() = 0; // Return item caption

			virtual bool setItemTypeIndex(const int value) = 0; // Set item type index
			virtual bool setItemCaption(const String &value) = 0; // Set item caption
		};
	}
}