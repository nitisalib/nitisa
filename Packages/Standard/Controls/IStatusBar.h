// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Interfaces/IComponentItemList.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemStatusPanelLabel;

		class IStatusBar :public virtual IControl, public virtual IComponentItemList
		{
		protected:
			IStatusBar() = default;
			~IStatusBar() = default;
			IStatusBar(const IStatusBar &other) = delete;
			IStatusBar(IStatusBar &&other) = delete;
			IStatusBar &operator=(const IStatusBar &other) = delete;
			IStatusBar &operator=(IStatusBar &&other) = delete;
		public:
			virtual IListItemStatusPanelLabel *getPanel(const int index) = 0; // Return panel by index if exists and it is derived from IListItemStatusPanelLabel
			virtual IListItemStatusPanelLabel *getPanel(const String &name) = 0; // Return first panel by name if exists and it is derived from IListItemStatusPanelLabel
		};
	}
}