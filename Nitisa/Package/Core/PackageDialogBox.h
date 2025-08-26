// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../Interfaces/IPackageDialogBox.h"
#include "PackageControl.h"

namespace nitisa
{
	class IPackage;

	class CPackageDialogBox :public virtual IPackageDialogBox, public CPackageControl
	{
	private:
		StringArray m_aDialogBoxHeaderFiles;
	public:
		bool isDialogBox() override; // Return true

		// DialogBox additional header files
		int getDialogBoxHeaderFileCount() override;
		String getDialogBoxHeaderFile(const int index) override;

		CPackageDialogBox(
			IPackage *package, // Package to which the entity belongs
			const String &ns); // Namespace to which the entity belongs

		void AddDialogBoxHeaderFile(const String &value); // Add new additional header file to the list(use path relative to the Packages directory)
	};
}