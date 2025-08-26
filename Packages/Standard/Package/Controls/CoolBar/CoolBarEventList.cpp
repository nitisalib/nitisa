// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		CCoolBarEventList::CCoolBarEventList(IPackage *package, IDialogBox *control, IPackageEntity *entity) :CDialogBoxEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// State change events
			Delete(L"OnTransformControls");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetFocus");
			Delete(L"OnKillFocus");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			// IDialogBox events
			Delete(L"OnDestroy");
			Delete(L"OnClose");
			Delete(L"OnRestore");
			Delete(L"OnMinimize");
			Delete(L"OnMaximize");
		}
	}
}