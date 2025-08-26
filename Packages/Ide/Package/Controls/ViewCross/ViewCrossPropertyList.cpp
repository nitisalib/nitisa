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
		CViewCrossPropertyList::CViewCrossPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewCross*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewCross*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewCross*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewCross*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewCross*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewCross*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewCross*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewCross*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewCross*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewCross*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewCross*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewCross*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewCross*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewCross*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewCrossPropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewCross::State CViewCrossPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewCross::State::Active;
			return CViewCross::State::Normal;
		}

		StringArray CViewCrossPropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::LeftTop",
				L"View::RightTop",
				L"View::LeftBottom",
				L"View::RightBottom" };
		}

		CViewCross::View CViewCrossPropertyList::StringToView(const String &value)
		{
			if (value == L"View::LeftTop")
				return CViewCross::View::LeftTop;
			if (value == L"View::RightTop")
				return CViewCross::View::RightTop;
			if (value == L"View::LeftBottom")
				return CViewCross::View::LeftBottom;
			if (value == L"View::RightBottom")
				return CViewCross::View::RightBottom;
			return CViewCross::View::None;
		}

		String CViewCrossPropertyList::ViewToString(const CViewCross::View value)
		{
			switch (value)
			{
			case CViewCross::View::LeftTop:		return L"View::LeftTop";
			case CViewCross::View::RightTop:	return L"View::RightTop";
			case CViewCross::View::LeftBottom:	return L"View::LeftBottom";
			case CViewCross::View::RightBottom:	return L"View::RightBottom";
			default:							return L"View::None";
			}
		}
	}
}