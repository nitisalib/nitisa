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
		CViewH2LH1PropertyList::CViewH2LH1PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewH2LH1*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewH2LH1*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewH2LH1*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewH2LH1*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewH2LH1*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewH2LH1*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorX", false, nullptr,
				[](IClass *parent) {return cast<CViewH2LH1*>(parent)->getSeparatorX(); },
				[](IClass *parent, const float value) { return cast<CViewH2LH1*>(parent)->setSeparatorX(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewH2LH1*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewH2LH1*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH2LH1*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH2LH1*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH2LH1*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH2LH1*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewH2LH1*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewH2LH1*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewH2LH1PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewH2LH1::State CViewH2LH1PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewH2LH1::State::Active;
			return CViewH2LH1::State::Normal;
		}

		StringArray CViewH2LH1PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Bottom",
				L"View::RightTop",
				L"View::LeftTop",
				L"View::LeftBottom" };
		}

		CViewH2LH1::View CViewH2LH1PropertyList::StringToView(const String &value)
		{
			if (value == L"View::Bottom")
				return CViewH2LH1::View::Bottom;
			if (value == L"View::RightTop")
				return CViewH2LH1::View::RightTop;
			if (value == L"View::LeftTop")
				return CViewH2LH1::View::LeftTop;
			if (value == L"View::LeftBottom")
				return CViewH2LH1::View::LeftBottom;
			return CViewH2LH1::View::None;
		}

		String CViewH2LH1PropertyList::ViewToString(const CViewH2LH1::View value)
		{
			switch (value)
			{
			case CViewH2LH1::View::Bottom:		return L"View::Bottom";
			case CViewH2LH1::View::RightTop:	return L"View::RightTop";
			case CViewH2LH1::View::LeftTop:		return L"View::LeftTop";
			case CViewH2LH1::View::LeftBottom:	return L"View::LeftBottom";
			default:							return L"View::None";
			}
		}
	}
}