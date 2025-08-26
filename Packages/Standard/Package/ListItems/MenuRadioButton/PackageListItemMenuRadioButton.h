// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../Menu/PackageListItemMenu.h"

namespace nitisa
{
	class IListItem;
	class IPackage;
	class IPropertyList;

	namespace standard
	{
		class CPackageListItemMenuRadioButton :public CPackageListItemMenu
		{
		public:
			String getClassName() override;
			String getTitle() override;
			String getDescription() override;
			String getReferenceUrl() override;
			bool isInstance(IListItem *listitem) override;

			IListItem *Create(IPropertyList **properties) override;
			IPropertyList *CreatePropertyList(IListItem *listitem) override;

			CPackageListItemMenuRadioButton(IPackage *package);
		};
	}
}