// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Package/Core/PackageControl.h"
#include <iostream>

namespace nitisa
{
	class IControl;
	class IEventList;
	class IPackage;
	class IPropertyList;

	namespace standard
	{
		class CPackageMultiButton :public CPackageControl
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

			void Save(Variant &dest, IPropertyList *properties, IEventList *events) override;
			void Load(const Variant &src, IPropertyList *properties, IEventList *events) override;
			void Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box) override;

			CPackageMultiButton(IPackage *package);
		};
	}
}