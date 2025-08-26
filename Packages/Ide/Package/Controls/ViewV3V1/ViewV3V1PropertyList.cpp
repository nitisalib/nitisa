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
		CViewV3V1PropertyList::CViewV3V1PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewV3V1*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewV3V1*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewV3V1*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewV3V1*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV1", false, nullptr,
				[](IClass *parent) {return cast<CViewV3V1*>(parent)->getSeparatorV1(); },
				[](IClass *parent, const float value) { return cast<CViewV3V1*>(parent)->setSeparatorV1(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV2", false, nullptr,
				[](IClass *parent) {return cast<CViewV3V1*>(parent)->getSeparatorV2(); },
				[](IClass *parent, const float value) { return cast<CViewV3V1*>(parent)->setSeparatorV2(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewV3V1*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewV3V1*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV3V1*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV3V1*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV3V1*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV3V1*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewV3V1*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewV3V1*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewV3V1PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewV3V1::State CViewV3V1PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewV3V1::State::Active;
			return CViewV3V1::State::Normal;
		}

		StringArray CViewV3V1PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Top",
				L"View::Middle",
				L"View::Bottom",
				L"View::Right" };
		}

		CViewV3V1::View CViewV3V1PropertyList::StringToView(const String &value)
		{
			if (value == L"View::Top")
				return CViewV3V1::View::Top;
			if (value == L"View::Middle")
				return CViewV3V1::View::Middle;
			if (value == L"View::Bottom")
				return CViewV3V1::View::Bottom;
			if (value == L"View::Right")
				return CViewV3V1::View::Right;
			return CViewV3V1::View::None;
		}

		String CViewV3V1PropertyList::ViewToString(const CViewV3V1::View value)
		{
			switch (value)
			{
			case CViewV3V1::View::Top:		return L"View::Top";
			case CViewV3V1::View::Middle:	return L"View::Middle";
			case CViewV3V1::View::Bottom:	return L"View::Bottom";
			case CViewV3V1::View::Right:	return L"View::Right";
			default:						return L"View::None";
			}
		}
	}
}