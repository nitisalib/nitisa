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
	namespace ide
	{
		CViewV2PropertyList::CViewV2PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewV2*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewV2*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"Separator", false, nullptr,
				[](IClass *parent) {return cast<CViewV2*>(parent)->getSeparator(); },
				[](IClass *parent, const float value) { return cast<CViewV2*>(parent)->setSeparator(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewV2*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewV2*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV2*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV2*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV2*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV2*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewV2*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewV2*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewV2PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewV2::State CViewV2PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewV2::State::Active;
			return CViewV2::State::Normal;
		}

		StringArray CViewV2PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Top",
				L"View::Bottom" };
		}

		CViewV2::View CViewV2PropertyList::StringToView(const String &value)
		{
			if (value == L"View::Top")
				return CViewV2::View::Top;
			if (value == L"View::Bottom")
				return CViewV2::View::Bottom;
			return CViewV2::View::None;
		}

		String CViewV2PropertyList::ViewToString(const CViewV2::View value)
		{
			switch (value)
			{
			case CViewV2::View::Top:	return L"View::Top";
			case CViewV2::View::Bottom:	return L"View::Bottom";
			default:					return L"View::None";
			}
		}
	}
}