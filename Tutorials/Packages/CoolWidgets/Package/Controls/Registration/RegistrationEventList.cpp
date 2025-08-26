#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		CRegistrationEventList::CRegistrationEventList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlEventList(package, control, entity)
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
			Delete(L"OnResize");
			Delete(L"OnTransformControls");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetFocus");
			Delete(L"OnKillFocus");
			Delete(L"OnSetCaptureMouse");
			Delete(L"OnKillCaptureMouse");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			// Add widget event
			Add(new CEvent(this, control, L"OnChange", L"IControl *sender", L"sender"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		}
	}
}