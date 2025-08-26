// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IComponentItemList.h"
#include "../Math/Point.h"
#include "Consts.h"
#include "Control.h"
#include "Strings.h"
#include <vector>

namespace nitisa
{
	class IListItem;

	class CControlItemList :public virtual IComponentItemList, public CControl
	{
	protected:
		std::vector<IListItem*> m_aItems; // Items

		void SortItems() override;
		void BeforeRelease() override;
	public:
		int getItemCount() override;
		IListItem *getItem(const int index) override;
		int getItemIndex(IListItem *item) override;
		bool isAcceptItem(IListItem *item) override;

		bool AddItem(IListItem *item) override;
		bool InsertItem(IListItem *item, const int before) override;
		bool DeleteItem(const int index) override;
		bool DeleteItem(IListItem *item) override;
		bool DeleteItems() override;

		CControlItemList(
			const String &class_name,
			const bool accept_form,
			const bool accept_control,
			const bool accept_controls,
			const bool accept_focus,
			const bool accept_modal,
			const bool tab_stop,
			const Point &design_dpi = DesignDPI);
	};
}