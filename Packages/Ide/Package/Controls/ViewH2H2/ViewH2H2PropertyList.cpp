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
		CViewH2H2PropertyList::CViewH2H2PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewH2H2*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewH2H2*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH1", false, nullptr,
				[](IClass *parent) {return cast<CViewH2H2*>(parent)->getSeparatorH1(); },
				[](IClass *parent, const float value) { return cast<CViewH2H2*>(parent)->setSeparatorH1(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorH2", false, nullptr,
				[](IClass *parent) {return cast<CViewH2H2*>(parent)->getSeparatorH2(); },
				[](IClass *parent, const float value) { return cast<CViewH2H2*>(parent)->setSeparatorH2(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewH2H2*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewH2H2*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewH2H2*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewH2H2*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH2H2*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH2H2*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH2H2*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH2H2*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewH2H2*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewH2H2*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewH2H2PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewH2H2::State CViewH2H2PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewH2H2::State::Active;
			return CViewH2H2::State::Normal;
		}

		StringArray CViewH2H2PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::LeftTop",
				L"View::RightTop",
				L"View::LeftBottom",
				L"View::RightBottom" };
		}

		CViewH2H2::View CViewH2H2PropertyList::StringToView(const String &value)
		{
			if (value == L"View::LeftTop")
				return CViewH2H2::View::LeftTop;
			if (value == L"View::RightTop")
				return CViewH2H2::View::RightTop;
			if (value == L"View::LeftBottom")
				return CViewH2H2::View::LeftBottom;
			if (value == L"View::RightBottom")
				return CViewH2H2::View::RightBottom;
			return CViewH2H2::View::None;
		}

		String CViewH2H2PropertyList::ViewToString(const CViewH2H2::View value)
		{
			switch (value)
			{
			case CViewH2H2::View::LeftTop:		return L"View::LeftTop";
			case CViewH2H2::View::RightTop:		return L"View::RightTop";
			case CViewH2H2::View::LeftBottom:	return L"View::LeftBottom";
			case CViewH2H2::View::RightBottom:	return L"View::RightBottom";
			default:							return L"View::None";
			}
		}
	}
}