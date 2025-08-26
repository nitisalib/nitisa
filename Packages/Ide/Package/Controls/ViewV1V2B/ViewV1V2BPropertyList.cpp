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
		CViewV1V2BPropertyList::CViewV1V2BPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2B*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewV1V2B*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2B*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewV1V2B*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2B*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewV1V2B*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorX", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2B*>(parent)->getSeparatorX(); },
				[](IClass *parent, const float value) { return cast<CViewV1V2B*>(parent)->setSeparatorX(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewV1V2B*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewV1V2B*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2B*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV1V2B*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2B*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV1V2B*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewV1V2B*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewV1V2B*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewV1V2BPropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewV1V2B::State CViewV1V2BPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewV1V2B::State::Active;
			return CViewV1V2B::State::Normal;
		}

		StringArray CViewV1V2BPropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Left",
				L"View::RightTop",
				L"View::LeftBottom",
				L"View::RightBottom" };
		}

		CViewV1V2B::View CViewV1V2BPropertyList::StringToView(const String &value)
		{
			if (value == L"View::Left")
				return CViewV1V2B::View::Left;
			if (value == L"View::RightTop")
				return CViewV1V2B::View::RightTop;
			if (value == L"View::LeftBottom")
				return CViewV1V2B::View::LeftBottom;
			if (value == L"View::RightBottom")
				return CViewV1V2B::View::RightBottom;
			return CViewV1V2B::View::None;
		}

		String CViewV1V2BPropertyList::ViewToString(const CViewV1V2B::View value)
		{
			switch (value)
			{
			case CViewV1V2B::View::Left:		return L"View::Left";
			case CViewV1V2B::View::RightTop:	return L"View::RightTop";
			case CViewV1V2B::View::LeftBottom:	return L"View::LeftBottom";
			case CViewV1V2B::View::RightBottom:	return L"View::RightBottom";
			default:							return L"View::None";
			}
		}
	}
}