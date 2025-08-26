// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Image.h"
#include "PackageCustomListBox.h"

namespace nitisa
{
	class IControl;
	class IEventList;
	class IPackage;
	class IPropertyList;

	namespace standard
	{
		class CPackageListBox :public CPackageCustomListBox
		{
		private:
			const Image m_cIcon;
		public:
			String getCategory() override;
			String getClassName() override;
			String getTitle() override;
			String getDescription() override;
			String getReferenceUrl() override;
			const Image *getIcon() override;
			bool isVisible() override;
			bool isDisplayIcon() override;
			bool isInstance(IControl *control) override;
			bool isTransformable() override;

			IControl *Create(IPropertyList **properties, IEventList **events) override;
			IPropertyList *CreatePropertyList(IControl *control) override;
			IEventList *CreateEventList(IControl *control) override;
			bool CreateListItem(IComponent *component, IListItem *parent, IListItem **item, IPackageControlListener *listener = nullptr) override;

			CPackageListBox(IPackage *package);
		};
	}
}