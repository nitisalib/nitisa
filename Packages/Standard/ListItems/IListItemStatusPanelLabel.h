// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IListItemCaption.h"
#include "IListItemStatusPanel.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemStatusPanelLabel :public virtual IListItemStatusPanel, public virtual IListItemCaption
		{
		protected:
			IListItemStatusPanelLabel() = default;
			~IListItemStatusPanelLabel() = default;
			IListItemStatusPanelLabel(const IListItemStatusPanelLabel &other) = delete;
			IListItemStatusPanelLabel(IListItemStatusPanelLabel &&other) = delete;
			IListItemStatusPanelLabel &operator=(const IListItemStatusPanelLabel &other) = delete;
			IListItemStatusPanelLabel &operator=(IListItemStatusPanelLabel &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}