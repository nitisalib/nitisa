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
		CViewH1H2RPropertyList::CViewH1H2RPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2R*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewH1H2R*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2R*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2R*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2R*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2R*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorX", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2R*>(parent)->getSeparatorX(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2R*>(parent)->setSeparatorX(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewH1H2R*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewH1H2R*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2R*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2R*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH1H2R*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH1H2R*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewH1H2R*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewH1H2R*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewH1H2RPropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewH1H2R::State CViewH1H2RPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewH1H2R::State::Active;
			return CViewH1H2R::State::Normal;
		}

		StringArray CViewH1H2RPropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Top",
				L"View::LeftBottom",
				L"View::RightTop",
				L"View::RightBottom" };
		}

		CViewH1H2R::View CViewH1H2RPropertyList::StringToView(const String &value)
		{
			if (value == L"View::Top")
				return CViewH1H2R::View::Top;
			if (value == L"View::LeftBottom")
				return CViewH1H2R::View::LeftBottom;
			if (value == L"View::RightTop")
				return CViewH1H2R::View::RightTop;
			if (value == L"View::RightBottom")
				return CViewH1H2R::View::RightBottom;
			return CViewH1H2R::View::None;
		}

		String CViewH1H2RPropertyList::ViewToString(const CViewH1H2R::View value)
		{
			switch (value)
			{
			case CViewH1H2R::View::Top:			return L"View::Top";
			case CViewH1H2R::View::LeftBottom:	return L"View::LeftBottom";
			case CViewH1H2R::View::RightTop:	return L"View::RightTop";
			case CViewH1H2R::View::RightBottom:	return L"View::RightBottom";
			default:							return L"View::None";
			}
		}
	}
}