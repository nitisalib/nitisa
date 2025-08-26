// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IPackageEntity.h"

namespace nitisa
{
	class IEventList;
	class IForm;
	class IPropertyList;
	class IRenderer;
	class IWindow;

	class Image;

	class IPackageForm :public virtual IPackageEntity
	{
	protected:
		IPackageForm() = default;
		~IPackageForm() = default;
		IPackageForm(const IPackageForm &other) = delete;
		IPackageForm(IPackageForm &&other) = delete;
		IPackageForm &operator=(const IPackageForm &other) = delete;
		IPackageForm &operator=(IPackageForm &&other) = delete;
	public:
		virtual const Image *getIcon() = 0; // Return icon. Could be nullptr
		virtual IForm *getInstance() = 0; // Return corresponding form instance if form has already been created

		virtual IForm *Create(IWindow *window, IRenderer *renderer) = 0; // Create new instance of the corresponding form with specified window and renderer
		virtual IPropertyList *CreatePropertyList(IForm *form) = 0; // Create property list for specified form
		virtual IEventList *CreateEventList(IForm *form) = 0; // Create event list for specified form
	};
}