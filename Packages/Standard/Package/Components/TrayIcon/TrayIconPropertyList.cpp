// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		CTrayIconPropertyList::CTrayIconPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyString(this, component, L"Tip", false, nullptr,
				[](IClass *parent) {return cast<CTrayIcon*>(parent)->getTip(); },
				[](IClass *parent, const String value) {return cast<CTrayIcon*>(parent)->setTip(value); }));
			Add(new CPropertyImage(this, component, L"Icon", nullptr,
				[](IClass *parent) {return cast<CTrayIcon*>(parent)->getIcon(); },
				[](IClass *parent) {cast<CTrayIcon*>(parent)->Update(); }));
			Add(new CPropertyString(this, component, L"Title", false, nullptr,
				[](IClass *parent) {return cast<CTrayIcon*>(parent)->getTitle(); },
				[](IClass *parent, const String value) {return cast<CTrayIcon*>(parent)->setTitle(value); }));
			Add(new CPropertyString(this, component, L"Message", false, nullptr,
				[](IClass *parent) {return cast<CTrayIcon*>(parent)->getMessage(); },
				[](IClass *parent, const String value) {return cast<CTrayIcon*>(parent)->setMessage(value); }));
			Add(new CPropertyImage(this, component, L"NotificationIcon", nullptr,
				[](IClass *parent) {return cast<CTrayIcon*>(parent)->getNotificationIcon(); },
				[](IClass *parent) { }));
			Add(new CPropertyEnum(this, component, L"NotificationIconType", false, NotificationIconTypeItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return NotificationIconTypeToString(cast<CTrayIcon*>(parent)->getNotificationIconType()); },
				[](IClass *parent, const String value) {return cast<CTrayIcon*>(parent)->setNotificationIconType(StringToNotificationIconType(value)); }));
			Add(new CPropertyBool(this, component, L"PlaySound", false, nullptr,
				[](IClass *parent) {return cast<CTrayIcon*>(parent)->isPlaySound(); },
				[](IClass *parent, const bool value) {return cast<CTrayIcon*>(parent)->setPlaySound(value); }));
			Add(new CPropertyBool(this, component, L"RespectQuietTime", false, nullptr,
				[](IClass *parent) {return cast<CTrayIcon*>(parent)->isRespectQuietTime(); },
				[](IClass *parent, const bool value) {return cast<CTrayIcon*>(parent)->setRespectQuietTime(value); }));
		}

		StringArray CTrayIconPropertyList::NotificationIconTypeItems()
		{
			return StringArray{
				L"NotificationIconType::None",
				L"NotificationIconType::Info",
				L"NotificationIconType::Warning",
				L"NotificationIconType::Error",
				L"NotificationIconType::Custom" };
		}

		CTrayIcon::NotificationIconType CTrayIconPropertyList::StringToNotificationIconType(const String &state)
		{
			if (state == L"NotificationIconType::Info")
				return CTrayIcon::NotificationIconType::Info;
			if (state == L"NotificationIconType::Warning")
				return CTrayIcon::NotificationIconType::Warning;
			if (state == L"NotificationIconType::Error")
				return CTrayIcon::NotificationIconType::Error;
			if (state == L"NotificationIconType::Custom")
				return CTrayIcon::NotificationIconType::Custom;
			return CTrayIcon::NotificationIconType::None;
		}

		String CTrayIconPropertyList::NotificationIconTypeToString(const CTrayIcon::NotificationIconType state)
		{
			switch (state)
			{
			case CTrayIcon::NotificationIconType::Info:		return L"NotificationIconType::Info";
			case CTrayIcon::NotificationIconType::Warning:	return L"NotificationIconType::Warning";
			case CTrayIcon::NotificationIconType::Error:	return L"NotificationIconType::Error";
			case CTrayIcon::NotificationIconType::Custom:	return L"NotificationIconType::Custom";
			default:										return L"NotificationIconType::None";
			}
		}
	}
}