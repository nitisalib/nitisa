// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Nitisa/Package/Core/PackageControl.h"
#include <iostream>

namespace nitisa
{
	class IEventList;
	class IPackage;
	class IPropertyList;

	namespace standard
	{
		class CPackageCustomListBox :public CPackageControl
		{
		public:
			void Save(Variant &dest, IPropertyList *properties, IEventList *events) override;
			void Load(const Variant &src, IPropertyList *properties, IEventList *events) override;
			void Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box) override;

			CPackageCustomListBox(IPackage *package, const String &ns);
		};
	}
}