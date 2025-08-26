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
		CViewV3PropertyList::CViewV3PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewV3*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewV3*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"Separator1", false, nullptr,
				[](IClass *parent) {return cast<CViewV3*>(parent)->getSeparator1(); },
				[](IClass *parent, const float value) { return cast<CViewV3*>(parent)->setSeparator1(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"Separator2", false, nullptr,
				[](IClass *parent) {return cast<CViewV3*>(parent)->getSeparator2(); },
				[](IClass *parent, const float value) { return cast<CViewV3*>(parent)->setSeparator2(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewV3*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewV3*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV3*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV3*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV3*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV3*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewV3*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewV3*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewV3PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewV3::State CViewV3PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewV3::State::Active;
			return CViewV3::State::Normal;
		}

		StringArray CViewV3PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Top",
				L"View::Middle",
				L"View::Bottom" };
		}

		CViewV3::View CViewV3PropertyList::StringToView(const String &value)
		{
			if (value == L"View::Top")
				return CViewV3::View::Top;
			if (value == L"View::Middle")
				return CViewV3::View::Middle;
			if (value == L"View::Bottom")
				return CViewV3::View::Bottom;
			return CViewV3::View::None;
		}

		String CViewV3PropertyList::ViewToString(const CViewV3::View value)
		{
			switch (value)
			{
			case CViewV3::View::Top:	return L"View::Top";
			case CViewV3::View::Middle:	return L"View::Middle";
			case CViewV3::View::Bottom:	return L"View::Bottom";
			default:					return L"View::None";
			}
		}
	}
}