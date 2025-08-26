// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/DialogBoxPropertyList.h"
#include "../../../Controls/CoolBar/CoolBar.h"
#include "../../../Controls/ICoolBar.h"

namespace nitisa
{
	class IDialogBox;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CCoolBarPropertyList :public CDialogBoxPropertyList
		{
		private:
			static StringArray AlignItems();

			static StringArray StateItems();
			static CCoolBar::State StringToState(const String &state);

			static StringArray OrientationItems();
			static String OrientationToString(const ICoolBar::Orientation orientation);
			static ICoolBar::Orientation StringToOrientation(const String &orientation);

			static StringArray MoverKindItems();
			static String MoverKindToString(const CCoolBar::MoverKind kind);
			static CCoolBar::MoverKind StringToMoverKind(const String &kind);
		public:
			CCoolBarPropertyList(IPackage *package, IDialogBox *control, IPackageEntity *entity);
		};
	}
}