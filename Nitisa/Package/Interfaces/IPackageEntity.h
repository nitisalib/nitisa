// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/PlatformVersion.h"
#include "../../Core/Strings.h"

namespace nitisa
{
	class IPackage;

	// Base class for all
	class IPackageEntity
	{
	protected:
		IPackageEntity() = default;
		~IPackageEntity() = default;
		IPackageEntity(const IPackageEntity &other) = delete;
		IPackageEntity(IPackageEntity &&other) = delete;
		IPackageEntity &operator=(const IPackageEntity &other) = delete;
		IPackageEntity &operator=(IPackageEntity &&other) = delete;
	public:
		struct ForwardDeclaration
		{
			String Declaration;
			String HeaderFile;
			String Namespace;
		};
	public:
		// Properties
		virtual IPackage *getPackage() = 0; // Return package
		virtual String getNamespace() = 0; // Return string representation of the namespace where entity is(like "standard" or "helpers::math")
		virtual String getCategory() = 0; // Return category where entity should appear in Form Builder
		virtual String getClassName() = 0; // Return class name
		virtual String getTitle() = 0; // Return title to be displayed in Form Builder
		virtual String getDescription() = 0; // Return description
		virtual String getReferenceUrl() = 0; // Return documentation URL(if empty Form Builder will use package reference url + entity class name)
		virtual int getPlatformCount() = 0; // Return supported platform count. Return 0 if support same to package platforms
		virtual PlatformVersion getPlatform(const int index) = 0; // Return supported platform by index
		virtual int getHeaderFileCount() = 0; // Return header file count
		virtual String getHeaderFile(const int index) = 0; // Return header file by index. Relative to the package directory(for example, if entity will be in "/Packages/Vendor/Components/Name/Name.h", this should return "Vendor/Components/Name.h")
		virtual int getForwardDeclarationCount() = 0;
		virtual ForwardDeclaration getForwardDeclaration(const int index) = 0;

		virtual bool setNamespace(const String &value) = 0; // Set new namespace. Used only in Form Builder to overwrite namespace in form prototype header file by user request(via changing settings)

		virtual void Release() = 0; // Destroy instance
	};
}