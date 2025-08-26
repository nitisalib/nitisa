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
		CViewH2PropertyList::CViewH2PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewH2*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewH2*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"Separator", false, nullptr,
				[](IClass *parent) {return cast<CViewH2*>(parent)->getSeparator(); },
				[](IClass *parent, const float value) { return cast<CViewH2*>(parent)->setSeparator(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewH2*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewH2*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH2*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH2*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH2*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH2*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewH2*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewH2*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewH2PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewH2::State CViewH2PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewH2::State::Active;
			return CViewH2::State::Normal;
		}

		StringArray CViewH2PropertyList::ViewItems()
		{
			return StringArray{
				L"View::Left",
				L"View::Right" };
		}

		CViewH2::View CViewH2PropertyList::StringToView(const String &value)
		{
			if (value == L"View::Left")
				return CViewH2::View::Left;
			if (value == L"View::Right")
				return CViewH2::View::Right;
			return CViewH2::View::None;
		}

		String CViewH2PropertyList::ViewToString(const CViewH2::View value)
		{
			switch (value)
			{
			case CViewH2::View::Left:	return L"View::Left";
			case CViewH2::View::Right:	return L"View::Right";
			default:					return L"View::None";
			}
		}
	}
}