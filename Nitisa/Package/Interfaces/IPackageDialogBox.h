// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "IPackageControl.h"

namespace nitisa
{
	// Additional header files will be added to exported file in Form Builder only when using dialog box as base class. Most often it will be only a header file where control's service is.
	class IPackageDialogBox :public virtual IPackageControl
	{
	protected:
		IPackageDialogBox() = default;
		~IPackageDialogBox() = default;
		IPackageDialogBox(const IPackageDialogBox &other) = delete;
		IPackageDialogBox(IPackageDialogBox &&other) = delete;
		IPackageDialogBox &operator=(const IPackageDialogBox &other) = delete;
		IPackageDialogBox &operator=(IPackageDialogBox &&other) = delete;
	public:
		// DialogBox additional header files
		virtual int getDialogBoxHeaderFileCount() = 0; // Return additional header file count
		virtual String getDialogBoxHeaderFile(const int index) = 0; // Return additional header file by index. Relative to the package directory(for example, if entity will be in "/Packages/Vendor/Controls/Name/Name.h", this should return "Vendor/Controls/Name.h")
	};
}