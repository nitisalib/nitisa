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
		CViewV2V2PropertyList::CViewV2V2PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V2*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewV2V2*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V2*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewV2V2*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV1", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V2*>(parent)->getSeparatorV1(); },
				[](IClass *parent, const float value) { return cast<CViewV2V2*>(parent)->setSeparatorV1(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV2", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V2*>(parent)->getSeparatorV2(); },
				[](IClass *parent, const float value) { return cast<CViewV2V2*>(parent)->setSeparatorV2(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewV2V2*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewV2V2*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V2*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV2V2*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV2V2*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV2V2*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewV2V2*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewV2V2*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewV2V2PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewV2V2::State CViewV2V2PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewV2V2::State::Active;
			return CViewV2V2::State::Normal;
		}

		StringArray CViewV2V2PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::LeftTop",
				L"View::RightTop",
				L"View::LeftBottom",
				L"View::RightBottom" };
		}

		CViewV2V2::View CViewV2V2PropertyList::StringToView(const String &value)
		{
			if (value == L"View::LeftTop")
				return CViewV2V2::View::LeftTop;
			if (value == L"View::RightTop")
				return CViewV2V2::View::RightTop;
			if (value == L"View::LeftBottom")
				return CViewV2V2::View::LeftBottom;
			if (value == L"View::RightBottom")
				return CViewV2V2::View::RightBottom;
			return CViewV2V2::View::None;
		}

		String CViewV2V2PropertyList::ViewToString(const CViewV2V2::View value)
		{
			switch (value)
			{
			case CViewV2V2::View::LeftTop:		return L"View::LeftTop";
			case CViewV2V2::View::RightTop:		return L"View::RightTop";
			case CViewV2V2::View::LeftBottom:	return L"View::LeftBottom";
			case CViewV2V2::View::RightBottom:	return L"View::RightBottom";
			default:							return L"View::None";
			}
		}
	}
}