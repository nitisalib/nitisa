// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../../../ListItems/StatusPanelLabel/ListItemStatusPanelLabel.h"
#include "../StatusPanel/ListItemStatusPanelPropertyList.h"

namespace nitisa
{
	class IListItem;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CListItemStatusPanelLabelPropertyList :public CListItemStatusPanelPropertyList
		{
		private:
			static StringArray StateItems();
			static CListItemStatusPanelLabel::State StringToState(const String &state);
		public:
			CListItemStatusPanelLabelPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity);
		};
	}
}