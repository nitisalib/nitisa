// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IComponent.h"

namespace nitisa
{
	namespace standard
	{
		class ISysBrowseFolderDialog :public virtual IComponent
		{
		protected:
			ISysBrowseFolderDialog() = default;
			~ISysBrowseFolderDialog() = default;
			ISysBrowseFolderDialog(const ISysBrowseFolderDialog &other) = delete;
			ISysBrowseFolderDialog(ISysBrowseFolderDialog &&other) = delete;
			ISysBrowseFolderDialog &operator=(const ISysBrowseFolderDialog &other) = delete;
			ISysBrowseFolderDialog &operator=(ISysBrowseFolderDialog &&other) = delete;
		public:
			virtual String getFolder() = 0; // Return selected folder
			virtual String getTitle() = 0; // Return dialog title
			virtual bool isOnlyFileSystem() = 0; // Return whether only file system directories will be returned
			virtual bool isNoNetwork() = 0; // Return whether hide network directories
			virtual bool isNoAncestors() = 0; // Return whether only file system ancestors should be returned
			virtual bool isShowEditBox() = 0; // Return whether edit box should be shown
			virtual bool isNewStyle() = 0; // Return whether new style should be used
			virtual bool isShowHint() = 0; // Return whether hint should be shown
			virtual bool isHideNewFolder() = 0; // Return whether "New folder" button should be hidden
			virtual bool isDontTranslateTargets() = 0; // Return whether shortcuts shouldn't be processed
			virtual bool isOnlyComputers() = 0; // Return whether only computers can be selected
			virtual bool isOnlyPrinters() = 0; // Return whether only printers can be selected
			virtual bool isShowFiles() = 0; // Return whether file also should be shown
			virtual bool isShowShareable() = 0; // Return whether shareable remote resources should be visible

			virtual bool setTitle(const String &value) = 0; // Set dialog title
			virtual bool setOnlyFileSystem(const bool value) = 0; // Set whether only file system directories will be returned
			virtual bool setNoNetwork(const bool value) = 0; // Set whether hide network directories
			virtual bool setNoAncestors(const bool value) = 0; // Set whether only file system ancestors should be returned
			virtual bool setShowEditBox(const bool value) = 0; // Set whether edit box should be shown
			virtual bool setNewStyle(const bool value) = 0; // Set whether new style should be used
			virtual bool setShowHint(const bool value) = 0; // Set whether hint should be shown
			virtual bool setHideNewFolder(const bool value) = 0; // Set whether "New folder" button should be hidden
			virtual bool setDontTranslateTargets(const bool value) = 0; // Set whether shortcuts shouldn't be processed
			virtual bool setOnlyComputers(const bool value) = 0; // Set whether only computers can be selected
			virtual bool setOnlyPrinters(const bool value) = 0; // Set whether only printers can be selected
			virtual bool setShowFiles(const bool value) = 0; // Set whether file also should be shown
			virtual bool setShowShareable(const bool value) = 0; // Set whether shareable remote resources should be visible

			virtual bool Execute() = 0; // Show dialog
		};
	}
}