// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IListItem.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemStatusPanel :public virtual IListItem
		{
		protected:
			IListItemStatusPanel() = default;
			~IListItemStatusPanel() = default;
			IListItemStatusPanel(const IListItemStatusPanel &other) = delete;
			IListItemStatusPanel(IListItemStatusPanel &&other) = delete;
			IListItemStatusPanel &operator=(const IListItemStatusPanel &other) = delete;
			IListItemStatusPanel &operator=(IListItemStatusPanel &&other) = delete;
		public:
			virtual float getWidth() = 0; // Return panel width

			virtual bool setWidth(const float value) = 0; // Set panel width. <= 0 means auto size
		};
	}
}