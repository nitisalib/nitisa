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
		class ISysSaveDialog :public virtual IComponent
		{
		protected:
			ISysSaveDialog() = default;
			~ISysSaveDialog() = default;
			ISysSaveDialog(const ISysSaveDialog &other) = delete;
			ISysSaveDialog(ISysSaveDialog &&other) = delete;
			ISysSaveDialog &operator=(const ISysSaveDialog &other) = delete;
			ISysSaveDialog &operator=(ISysSaveDialog &&other) = delete;
		public:
			virtual String getFilter() = 0; // Return filter
			virtual int getFilterIndex() = 0; // Return active index
			virtual String getFileName() = 0; // Return first selected file name
			virtual String getDefaultExtension() = 0; // Return default extension
			virtual bool isCreatePrompt() = 0; // Whether ask for creation
			virtual bool isMustExists() = 0; // Whether file must exists
			virtual bool isShowHidden() = 0; // Whether show hidden files
			virtual bool isHideReadOnly() = 0; // Whether show readonly files
			virtual bool isNoNetwork() = 0; // Whether hide network
			virtual bool isOverwritePrompt() = 0; // Whether to show overwrite prompt

			virtual bool setFilter(const String &value) = 0; // Set filter
			virtual bool setFilterIndex(const int value) = 0; // Set active filter index
			virtual bool setFileName(const String &value) = 0; // Set file name
			virtual bool setDefaultExtension(const String &value) = 0; // Set default extension
			virtual bool setCreatePrompt(const bool value) = 0; // Set whether ask for creation
			virtual bool setMustExists(const bool value) = 0; // Set whether file must exists
			virtual bool setShowHidden(const bool value) = 0; // Set whether show hidden files
			virtual bool setHideReadOnly(const bool value) = 0; // Set whether show readonly files
			virtual bool setNoNetwork(const bool value) = 0; // Set whether hide network
			virtual bool setOverwritePrompt(const bool value) = 0; // Set whether to show overwrite prompt

			virtual bool Execute() = 0; // Show dialog
		};
	}
}