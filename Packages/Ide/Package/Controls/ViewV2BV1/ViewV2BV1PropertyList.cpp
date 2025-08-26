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
		CViewV2BV1PropertyList::CViewV2BV1PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewV2BV1*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewV2BV1*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH", false, nullptr,
				[](IClass *parent) {return cast<CViewV2BV1*>(parent)->getSeparatorH(); },
				[](IClass *parent, const float value) { return cast<CViewV2BV1*>(parent)->setSeparatorH(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewV2BV1*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewV2BV1*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorX", false, nullptr,
				[](IClass *parent) {return cast<CViewV2BV1*>(parent)->getSeparatorX(); },
				[](IClass *parent, const float value) { return cast<CViewV2BV1*>(parent)->setSeparatorX(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewV2BV1*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewV2BV1*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV2BV1*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV2BV1*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewV2BV1*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewV2BV1*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewV2BV1*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewV2BV1*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewV2BV1PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewV2BV1::State CViewV2BV1PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewV2BV1::State::Active;
			return CViewV2BV1::State::Normal;
		}

		StringArray CViewV2BV1PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Right",
				L"View::LeftTop",
				L"View::LeftBottom",
				L"View::RightBottom" };
		}

		CViewV2BV1::View CViewV2BV1PropertyList::StringToView(const String &value)
		{
			if (value == L"View::Right")
				return CViewV2BV1::View::Right;
			if (value == L"View::LeftTop")
				return CViewV2BV1::View::LeftTop;
			if (value == L"View::LeftBottom")
				return CViewV2BV1::View::LeftBottom;
			if (value == L"View::RightBottom")
				return CViewV2BV1::View::RightBottom;
			return CViewV2BV1::View::None;
		}

		String CViewV2BV1PropertyList::ViewToString(const CViewV2BV1::View value)
		{
			switch (value)
			{
			case CViewV2BV1::View::Right:		return L"View::Right";
			case CViewV2BV1::View::LeftTop:		return L"View::LeftTop";
			case CViewV2BV1::View::LeftBottom:	return L"View::LeftBottom";
			case CViewV2BV1::View::RightBottom:	return L"View::RightBottom";
			default:							return L"View::None";
			}
		}
	}
}