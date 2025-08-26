// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IFileList :public virtual IControl
		{
		protected:
			IFileList() = default;
			~IFileList() = default;
			IFileList(const IFileList &other) = delete;
			IFileList(IFileList &&other) = delete;
			IFileList &operator=(const IFileList &other) = delete;
			IFileList &operator=(IFileList &&other) = delete;
		public:
			virtual String getDirectory() = 0; // Return directory where to search files
			virtual String getFilter() = 0; // Return filter
			virtual bool isShowArchieved() = 0; // Return whether archived directories are shown
			virtual bool isShowCompressed() = 0; // Return whether compressed directories are shown
			virtual bool isShowEncrypted() = 0; // Return whether encrypted directories are shown
			virtual bool isShowHidden() = 0; // Return whether hidden directories are shown
			virtual bool isShowNormal() = 0; // Return whether normal directories are shown
			virtual bool isShowOffline() = 0; // Return whether offline directories are shown
			virtual bool isShowReadOnly() = 0; // Return whether read only directories are shown
			virtual bool isShowSystem() = 0; // Return whether system directories are shown
			virtual bool isShowTemporary() = 0; // Return whether temporary directories are shown
			virtual String getActiveFile() = 0; // Return active file
			virtual int getFileCount() = 0; // Return found file count
			virtual String getFile(const int index) = 0; // Return found file by index
			virtual bool isFileSelected(const int index) = 0; // Return whether file is selected

			virtual bool setDirectory(const String &value) = 0; // Set directory where to search files
			virtual bool setFilter(const String &value) = 0; // Set filter. Only files accepted by filter will be displayed. You may use ? to represent any character and * to represent any substring. If empty, *.* is used
			virtual bool setShowArchieved(const bool value) = 0; // Set whether archived directories are shown
			virtual bool setShowCompressed(const bool value) = 0; // Set whether compressed directories are shown
			virtual bool setShowEncrypted(const bool value) = 0; // Set whether encrypted directories are shown
			virtual bool setShowHidden(const bool value) = 0; // Set whether hidden directories are shown
			virtual bool setShowNormal(const bool value) = 0; // Set whether normal directories are shown
			virtual bool setShowOffline(const bool value) = 0; // Set whether offline directories are shown
			virtual bool setShowReadOnly(const bool value) = 0; // Set whether read only directories are shown
			virtual bool setShowSystem(const bool value) = 0; // Set whether system directories are shown
			virtual bool setShowTemporary(const bool value) = 0; // Set whether temporary directories are shown
			virtual bool setFileSelected(const int index, const bool value) = 0; // Selected/deselect file by index

			virtual bool Rescan() = 0; // Search files again
		};
	}
}
