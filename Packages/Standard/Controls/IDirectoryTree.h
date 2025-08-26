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
		class IFileList;

		class IDirectoryTree :public virtual IControl
		{
		protected:
			IDirectoryTree() = default;
			~IDirectoryTree() = default;
			IDirectoryTree(const IDirectoryTree &other) = delete;
			IDirectoryTree(IDirectoryTree &&other) = delete;
			IDirectoryTree &operator=(const IDirectoryTree &other) = delete;
			IDirectoryTree &operator=(IDirectoryTree &&other) = delete;
		public:
			virtual String getRootDirectory() = 0; // Return root directory
			virtual String getDirectory() = 0; // Return active directory full path or root directory if nothing is active/selected. If there is directory to return, it is returned with the directory separator at the end
			virtual String getFilter() = 0; // Return filter
			virtual IFileList *getFileList() = 0; // Return assigned FileList control
			virtual bool isShowArchieved() = 0; // Return whether archived directories are shown
			virtual bool isShowCompressed() = 0; // Return whether compressed directories are shown
			virtual bool isShowEncrypted() = 0; // Return whether encrypted directories are shown
			virtual bool isShowHidden() = 0; // Return whether hidden directories are shown
			virtual bool isShowNormal() = 0; // Return whether normal directories are shown
			virtual bool isShowOffline() = 0; // Return whether offline directories are shown
			virtual bool isShowReadOnly() = 0; // Return whether read only directories are shown
			virtual bool isShowSystem() = 0; // Return whether system directories are shown
			virtual bool isShowTemporary() = 0; // Return whether temporary directories are shown

			virtual bool setRootDirectory(const String &value) = 0; // Set root directory. Automatically adds directory separator at the end if there is none
			virtual bool setFilter(const String &value) = 0; // Set filter. Only directories accepted by filter will be displayed. You may use ? to represent any character and * to represent any substring. If empty, * is used
			virtual bool setFileList(IFileList *value) = 0; // Assign FileList control. Set nullptr to remove assignment
			virtual bool setShowArchieved(const bool value) = 0; // Set whether archived directories are shown
			virtual bool setShowCompressed(const bool value) = 0; // Set whether compressed directories are shown
			virtual bool setShowEncrypted(const bool value) = 0; // Set whether encrypted directories are shown
			virtual bool setShowHidden(const bool value) = 0; // Set whether hidden directories are shown
			virtual bool setShowNormal(const bool value) = 0; // Set whether normal directories are shown
			virtual bool setShowOffline(const bool value) = 0; // Set whether offline directories are shown
			virtual bool setShowReadOnly(const bool value) = 0; // Set whether read only directories are shown
			virtual bool setShowSystem(const bool value) = 0; // Set whether system directories are shown
			virtual bool setShowTemporary(const bool value) = 0; // Set whether temporary directories are shown

			virtual bool Rescan() = 0; // Rescan root directory
		};
	}
}