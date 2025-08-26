// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IControlCreateChild.h"
#include "Nitisa/Interfaces/IControlService.h"

namespace nitisa
{
	namespace standard
	{
		class IPageControl;

		class ITabSheet :public virtual IControl
		{
		protected:
			ITabSheet() = default;
			~ITabSheet() = default;
			ITabSheet(const ITabSheet &other) = delete;
			ITabSheet(ITabSheet &&other) = delete;
			ITabSheet &operator=(const ITabSheet &other) = delete;
			ITabSheet &operator=(ITabSheet &&other) = delete;
		public:
			virtual IPageControl *getPageControl() = 0; // Return parent page control
			virtual int getIndex() = 0; // Return index on parent
			virtual bool isActive() = 0; // Whether is active
			virtual String getCaption() = 0; // Return caption

			virtual bool setCaption(const String &value) = 0; // Set caption
		};

		class IPageControlService :public virtual IControlService
		{
		protected:
			IPageControlService() = default;
			~IPageControlService() = default;
			IPageControlService(const IPageControlService &other) = delete;
			IPageControlService(IPageControlService &&other) = delete;
			IPageControlService &operator=(const IPageControlService &other) = delete;
			IPageControlService &operator=(IPageControlService &&other) = delete;
		public:
			virtual void NotifyOnTabSheetChanged(ITabSheet *tab) = 0;
		};

		class IPageControl :public virtual IControlCreateChild
		{
		protected:
			IPageControl() = default;
			~IPageControl() = default;
			IPageControl(const IPageControl &other) = delete;
			IPageControl(IPageControl &&other) = delete;
			IPageControl &operator=(const IPageControl &other) = delete;
			IPageControl &operator=(IPageControl &&other) = delete;
		public:
			virtual int getTabSheetCount() = 0; // Return tab count
			virtual ITabSheet *getTabSheet(const int index) = 0; // Return tab by index
			virtual ITabSheet *getActiveTabSheet() = 0; // Return active tab
			virtual int getActiveIndex() = 0; // Return active tab index

			virtual bool setActiveIndex(const int value) = 0; // Set active tab
			virtual bool setActiveTabSheet(ITabSheet *value) = 0; // Set active tab

			virtual ITabSheet *CreateTabSheet() = 0; // Create new tab
			virtual ITabSheet *CreateTabSheet(const int before) = 0; // Create new tab and insert before specified one
			virtual bool AddTabSheet(ITabSheet *tab) = 0; // Add tab
			virtual bool InsertTabSheet(ITabSheet *tab, const int before) = 0; // Insert tab before specified one
			virtual bool DeleteTabSheet(const int index) = 0; // Delete tab by index
			virtual bool DeleteTabSheet(ITabSheet *tab) = 0; // Delete specified tab
			virtual bool DeleteTabSheets() = 0; // Delete all tabs
		};
	}
}