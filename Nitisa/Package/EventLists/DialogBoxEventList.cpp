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
	CDialogBoxEventList::CDialogBoxEventList(IPackage *package, IDialogBox *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
	{
		// IDialogBox events
		Add(new CEvent(this, control, L"OnDestroy", L"IDialogBox *sender", L"sender"))
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"");
		Add(new CEvent(this, control, L"OnClose", L"IDialogBox *sender, CloseAction &action", L"sender, action"))
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"")
			->AddHeaderFile(L"Nitisa/Core/CloseAction.h");
		Add(new CEvent(this, control, L"OnRestore", L"IDialogBox *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnMinimize", L"IDialogBox *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnMaximize", L"IDialogBox *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnSetActive", L"IDialogBox *sender", L"sender"))
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"");
		Add(new CEvent(this, control, L"OnKillActive", L"IDialogBox *sender", L"sender"))
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"");
	}
}