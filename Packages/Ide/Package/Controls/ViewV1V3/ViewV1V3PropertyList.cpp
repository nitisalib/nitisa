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
		CViewV1V3PropertyList::CViewV1V3PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V3*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewV1V3*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V3*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewV1V3*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV1", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V3*>(parent)->getSeparatorV1(); },
				[](IClass *parent, const float value) { return cast<CViewV1V3*>(parent)->setSeparatorV1(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV2", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V3*>(parent)->getSeparatorV2(); },
				[](IClass *parent, const float value) { return cast<CViewV1V3*>(parent)->setSeparatorV2(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewV1V3*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewV1V3*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V3*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV1V3*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V3*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV1V3*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewV1V3*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewV1V3*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewV1V3PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewV1V3::State CViewV1V3PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewV1V3::State::Active;
			return CViewV1V3::State::Normal;
		}

		StringArray CViewV1V3PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Top",
				L"View::Middle",
				L"View::Bottom",
				L"View::Left" };
		}

		CViewV1V3::View CViewV1V3PropertyList::StringToView(const String &value)
		{
			if (value == L"View::Top")
				return CViewV1V3::View::Top;
			if (value == L"View::Middle")
				return CViewV1V3::View::Middle;
			if (value == L"View::Bottom")
				return CViewV1V3::View::Bottom;
			if (value == L"View::Left")
				return CViewV1V3::View::Left;
			return CViewV1V3::View::None;
		}

		String CViewV1V3PropertyList::ViewToString(const CViewV1V3::View value)
		{
			switch (value)
			{
			case CViewV1V3::View::Top:		return L"View::Top";
			case CViewV1V3::View::Middle:	return L"View::Middle";
			case CViewV1V3::View::Bottom:	return L"View::Bottom";
			case CViewV1V3::View::Left:		return L"View::Left";
			default:						return L"View::None";
			}
		}
	}
}