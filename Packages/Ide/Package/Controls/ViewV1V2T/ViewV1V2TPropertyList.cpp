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
		CViewV1V2TPropertyList::CViewV1V2TPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2T*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewV1V2T*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2T*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewV1V2T*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2T*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewV1V2T*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorX", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2T*>(parent)->getSeparatorX(); },
				[](IClass *parent, const float value) { return cast<CViewV1V2T*>(parent)->setSeparatorX(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewV1V2T*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewV1V2T*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2T*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV1V2T*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV1V2T*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV1V2T*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewV1V2T*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewV1V2T*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewV1V2TPropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewV1V2T::State CViewV1V2TPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewV1V2T::State::Active;
			return CViewV1V2T::State::Normal;
		}

		StringArray CViewV1V2TPropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Left",
				L"View::RightBottom",
				L"View::LeftTop",
				L"View::RightTop" };
		}

		CViewV1V2T::View CViewV1V2TPropertyList::StringToView(const String &value)
		{
			if (value == L"View::Left")
				return CViewV1V2T::View::Left;
			if (value == L"View::RightBottom")
				return CViewV1V2T::View::RightBottom;
			if (value == L"View::LeftTop")
				return CViewV1V2T::View::LeftTop;
			if (value == L"View::RightTop")
				return CViewV1V2T::View::RightTop;
			return CViewV1V2T::View::None;
		}

		String CViewV1V2TPropertyList::ViewToString(const CViewV1V2T::View value)
		{
			switch (value)
			{
			case CViewV1V2T::View::Left:		return L"View::Left";
			case CViewV1V2T::View::RightBottom:	return L"View::RightBottom";
			case CViewV1V2T::View::LeftTop:		return L"View::LeftTop";
			case CViewV1V2T::View::RightTop:	return L"View::RightTop";
			default:							return L"View::None";
			}
		}
	}
}