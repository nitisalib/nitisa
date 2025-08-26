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
		CViewH1H2PropertyList::CViewH1H2PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewH1H2*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewH1H2*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewH1H2*>(parent)->setActiveView(StringToView(value)); }))
				->AddHeaderFile(L"Ide/Controls/ViewH1H2/ViewH1H2.h");
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewH1H2*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewH1H2*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewH1H2PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewH1H2::State CViewH1H2PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewH1H2::State::Active;
			return CViewH1H2::State::Normal;
		}

		StringArray CViewH1H2PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Left",
				L"View::Right",
				L"View::Top" };
		}

		CViewH1H2::View CViewH1H2PropertyList::StringToView(const String &value)
		{
			if (value == L"View::Left")
				return CViewH1H2::View::Left;
			if (value == L"View::Right")
				return CViewH1H2::View::Right;
			if (value == L"View::Top")
				return CViewH1H2::View::Top;
			return CViewH1H2::View::None;
		}

		String CViewH1H2PropertyList::ViewToString(const CViewH1H2::View value)
		{
			switch (value)
			{
			case CViewH1H2::View::Left:		return L"View::Left";
			case CViewH1H2::View::Right:	return L"View::Right";
			case CViewH1H2::View::Top:		return L"View::Top";
			default:						return L"View::None";
			}
		}
	}
}