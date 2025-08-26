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
		CMultiButtonEventList::CMultiButtonEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// Events from child controls
			Delete(L"OnChildStyleChange");
			Delete(L"OnChildFontChange");
			Delete(L"OnChildTransform");
			Delete(L"OnChildResize");
			Delete(L"OnChildShow");
			Delete(L"OnChildHide");
			Delete(L"OnChildAttach");
			Delete(L"OnChildDetach");
			Delete(L"OnChildEnable");
			Delete(L"OnChildDisable");
			Delete(L"OnChildBeforeTransform");
			Delete(L"OnChildBeforeResize");
			Delete(L"OnChildBeforeShow");
			Delete(L"OnChildBeforeHide");
			Delete(L"OnChildBeforeEnable");
			Delete(L"OnChildBeforeDisable");

			// State change events
			Delete(L"OnTransformControls");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			Add(new CEvent(this, control, L"OnClick", L"{namespace}IMultiButton *sender", L"sender"))
				->AddForwardDeclaration(L"class IMultiButton;", L"Standard/Controls/IMultiButton.h", L"standard");
		}
	}
}