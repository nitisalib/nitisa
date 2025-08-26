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
		class IDirectoryTree;

		class IDriveDropDown :public virtual IControl
		{
		protected:
			IDriveDropDown() = default;
			~IDriveDropDown() = default;
			IDriveDropDown(const IDriveDropDown &other) = delete;
			IDriveDropDown(IDriveDropDown &&other) = delete;
			IDriveDropDown &operator=(const IDriveDropDown &other) = delete;
			IDriveDropDown &operator=(IDriveDropDown &&other) = delete;
		public:
			virtual int getDriveCount() = 0; // Return found drive(volume) count
			virtual String getDrive(const int index) = 0; // Return drive path by index
			virtual int getSelectedDriveIndex() = 0; // Return selected drive index
			virtual String getSelectedDrive() = 0; // Return selected drive path
			virtual IDirectoryTree *getDirectoryTree() = 0; // Return assigned DirectoryTree control

			virtual bool setSelectedDriveIndex(const int value) = 0; // Select drive by index
			virtual bool setSelectedDrive(const String &value) = 0; // Select drive by name
			virtual bool setDirectoryTree(IDirectoryTree *value) = 0; // Assign DirectoryTree control

			virtual bool Rescan() = 0; // Rescan drives
		};
	}
}