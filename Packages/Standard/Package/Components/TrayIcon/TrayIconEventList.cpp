// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		CTrayIconEventList::CTrayIconEventList(IPackage *package, IComponent *component, IPackageEntity *entity) :CComponentEventList(package, component, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			Add(new CEvent(this, component, L"OnKeyDown", L"{namespace}ITrayIcon *sender, const MessageKey &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnKeyUp", L"{namespace}ITrayIcon *sender, const MessageKey &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnChar", L"{namespace}ITrayIcon *sender, const MessageChar &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnDeadChar", L"{namespace}ITrayIcon *sender, const MessageChar &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnMouseMove", L"{namespace}ITrayIcon *sender, const MessagePosition &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnLeftMouseButtonDown", L"{namespace}ITrayIcon *sender, const MessagePosition &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnLeftMouseButtonUp", L"{namespace}ITrayIcon *sender, const MessagePosition &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnLeftMouseButtonDoubleClick", L"{namespace}ITrayIcon *sender, const MessagePosition &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnRightMouseButtonDown", L"{namespace}ITrayIcon *sender, const MessagePosition &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnRightMouseButtonUp", L"{namespace}ITrayIcon *sender, const MessagePosition &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnRightMouseButtonDoubleClick", L"{namespace}ITrayIcon *sender, const MessagePosition &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnMiddleMouseButtonDown", L"{namespace}ITrayIcon *sender, const MessagePosition &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnMiddleMouseButtonUp", L"{namespace}ITrayIcon *sender, const MessagePosition &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnMiddleMouseButtonDoubleClick", L"{namespace}ITrayIcon *sender, const MessagePosition &m", L"sender, m"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
			Add(new CEvent(this, component, L"OnNotificationShow", L"{namespace}ITrayIcon *sender", L"sender"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard");
			Add(new CEvent(this, component, L"OnNotificationHide", L"{namespace}ITrayIcon *sender", L"sender"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard");
			Add(new CEvent(this, component, L"OnNotificationTimeout", L"{namespace}ITrayIcon *sender", L"sender"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard");
			Add(new CEvent(this, component, L"OnNotificationClick", L"{namespace}ITrayIcon *sender", L"sender"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard");
			Add(new CEvent(this, component, L"OnPopupOpen", L"{namespace}ITrayIcon *sender", L"sender"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard");
			Add(new CEvent(this, component, L"OnPopupClose", L"{namespace}ITrayIcon *sender", L"sender"))
				->AddForwardDeclaration(L"class ITrayIcon;", L"Standard/Components/ITrayIcon.h", L"standard");
		}
	}
}