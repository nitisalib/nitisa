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
		CViewH1H2LPropertyList::CViewH1H2LPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2L*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewH1H2L*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2L*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2L*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2L*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2L*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorX", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2L*>(parent)->getSeparatorX(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2L*>(parent)->setSeparatorX(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewH1H2L*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewH1H2L*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2L*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2L*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2L*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2L*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewH1H2L*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewH1H2L*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewH1H2LPropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewH1H2L::State CViewH1H2LPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewH1H2L::State::Active;
			return CViewH1H2L::State::Normal;
		}

		StringArray CViewH1H2LPropertyList::ViewItems()
		{
			return StringArray{
				L"View::Top",
				L"View::RightBottom",
				L"View::LeftTop",
				L"View::LeftBottom" };
		}

		CViewH1H2L::View CViewH1H2LPropertyList::StringToView(const String &value)
		{
			if (value == L"View::Top")
				return CViewH1H2L::View::Top;
			if (value == L"View::RightBottom")
				return CViewH1H2L::View::RightBottom;
			if (value == L"View::LeftTop")
				return CViewH1H2L::View::LeftTop;
			if (value == L"View::LeftBottom")
				return CViewH1H2L::View::LeftBottom;
			return CViewH1H2L::View::None;
		}

		String CViewH1H2LPropertyList::ViewToString(const CViewH1H2L::View value)
		{
			switch (value)
			{
			case CViewH1H2L::View::Top:			return L"View::Top";
			case CViewH1H2L::View::RightBottom:	return L"View::RightBottom";
			case CViewH1H2L::View::LeftTop:		return L"View::LeftTop";
			case CViewH1H2L::View::LeftBottom:	return L"View::LeftBottom";
			default:							return L"View::None";
			}
		}
	}
}