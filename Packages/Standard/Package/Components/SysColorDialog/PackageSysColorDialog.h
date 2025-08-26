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
#include "Nitisa/Package/Core/PackageComponent.h"

namespace nitisa
{
	class IComponent;
	class IEventList;
	class IPackage;
	class IPropertyList;

	namespace standard
	{
		class CPackageSysColorDialog :public CPackageComponent
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
			bool isInstance(IComponent *component) override;

			IComponent *Create(IPropertyList **properties, IEventList **events) override;
			IPropertyList *CreatePropertyList(IComponent *component) override;
			IEventList *CreateEventList(IComponent *component) override;

			CPackageSysColorDialog(IPackage *package);
		};
	}
}