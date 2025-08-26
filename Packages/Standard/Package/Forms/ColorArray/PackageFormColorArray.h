// This file is a part of Nitisa framework
// Copyright © 2020Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Package/Core/PackageForm.h"

namespace nitisa
{
	class IForm;
	class IEventList;
	class IPackage;
	class IPropertyList;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CPackageFormColorArray :public CPackageForm
		{
		public:
			String getCategory() override;
			String getClassName() override;
			String getTitle() override;
			String getDescription() override;
			String getReferenceUrl() override;
			const Image *getIcon() override;
			IForm *getInstance() override;

			IForm *Create(IWindow *window, IRenderer *renderer) override;
			IPropertyList *CreatePropertyList(IForm *form) override;
			IEventList *CreateEventList(IForm *form) override;

			CPackageFormColorArray(IPackage *package);
		};
	}
}