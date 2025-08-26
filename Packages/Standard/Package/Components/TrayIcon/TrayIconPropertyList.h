// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ComponentPropertyList.h"
#include "../../../Components/TrayIcon/TrayIcon.h"

namespace nitisa
{
	class IComponent;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CTrayIconPropertyList :public CComponentPropertyList
		{
		private:
			static StringArray NotificationIconTypeItems();
			static CTrayIcon::NotificationIconType StringToNotificationIconType(const String &state);
			static String NotificationIconTypeToString(const CTrayIcon::NotificationIconType state);
		public:
			CTrayIconPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity);
		};
	}
}