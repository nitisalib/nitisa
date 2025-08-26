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
		CViewV2V1PropertyList::CViewV2V1PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V1*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewV2V1*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V1*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewV2V1*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V1*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewV2V1*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewV2V1*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewV2V1*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V1*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV2V1*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V1*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV2V1*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewV2V1*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewV2V1*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewV2V1PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewV2V1::State CViewV2V1PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewV2V1::State::Active;
			return CViewV2V1::State::Normal;
		}

		StringArray CViewV2V1PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Top",
				L"View::Right",
				L"View::Bottom" };
		}

		CViewV2V1::View CViewV2V1PropertyList::StringToView(const String &value)
		{
			if (value == L"View::Top")
				return CViewV2V1::View::Top;
			if (value == L"View::Right")
				return CViewV2V1::View::Right;
			if (value == L"View::Bottom")
				return CViewV2V1::View::Bottom;
			return CViewV2V1::View::None;
		}

		String CViewV2V1PropertyList::ViewToString(const CViewV2V1::View value)
		{
			switch (value)
			{
			case CViewV2V1::View::Top:		return L"View::Top";
			case CViewV2V1::View::Right:	return L"View::Right";
			case CViewV2V1::View::Bottom:	return L"View::Bottom";
			default:						return L"View::None";
			}
		}
	}
}