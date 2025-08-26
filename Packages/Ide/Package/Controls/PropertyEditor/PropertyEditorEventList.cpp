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
	namespace ide
	{
		CPropertyEditorEventList::CPropertyEditorEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
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

			// State change events
			Delete(L"OnEnable");
			Delete(L"OnDisable");
			Delete(L"OnTransformControls");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			Add(new CEvent(this, control, L"OnPropertyChange", L"{namespace}IPropertyEditor *sender, IProperty *property, IPropertyList *property_list, IClass *parent", L"sender, property, property_list, parent"))
				->AddForwardDeclaration(L"class IPropertyEditor;", L"Ide/Controls/IPropertyEditor.h", L"ide")
				->AddForwardDeclaration(L"class IProperty;", L"Nitisa/Package/Interfaces/IProperty.h", L"")
				->AddForwardDeclaration(L"class IPropertyList;", L"Nitisa/Package/Interfaces/IPropertyList.h", L"")
				->AddForwardDeclaration(L"class IClass;", L"Nitisa/Interfaces/IClass.h", L"");
		}
	}
}