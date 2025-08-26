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
		CViewH3H1PropertyList::CViewH3H1PropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CViewH3H1*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) { return cast<CViewH3H1*>(parent)->setResizable(value); }));
			Add(new CPropertyFloat(this, control, L"SeparatorH1", false, nullptr,
				[](IClass *parent) {return cast<CViewH3H1*>(parent)->getSeparatorH1(); },
				[](IClass *parent, const float value) { return cast<CViewH3H1*>(parent)->setSeparatorH1(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorH2", false, nullptr,
				[](IClass *parent) {return cast<CViewH3H1*>(parent)->getSeparatorH2(); },
				[](IClass *parent, const float value) { return cast<CViewH3H1*>(parent)->setSeparatorH2(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyFloat(this, control, L"SeparatorV", false, nullptr,
				[](IClass *parent) {return cast<CViewH3H1*>(parent)->getSeparatorV(); },
				[](IClass *parent, const float value) { return cast<CViewH3H1*>(parent)->setSeparatorV(value); }))
				->setMin(0)
				->setMax(1);

			Add(new CPropertyEnum(this, control, L"ActiveView", false, ViewItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return ViewToString(cast<CViewH3H1*>(parent)->getActiveView()); },
				[](IClass *parent, const String value) { return cast<CViewH3H1*>(parent)->setActiveView(StringToView(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH3H1*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH3H1*>(parent)->setBorderWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CViewH3H1*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CViewH3H1*>(parent)->setSeparatorWidth(value); }))
				->setMin(0)
				->setMax(16);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CViewH3H1*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CViewH3H1*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CViewH3H1PropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CViewH3H1::State CViewH3H1PropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CViewH3H1::State::Active;
			return CViewH3H1::State::Normal;
		}

		StringArray CViewH3H1PropertyList::ViewItems()
		{
			return StringArray{
				L"View::None",
				L"View::Left",
				L"View::Middle",
				L"View::Right",
				L"View::Bottom" };
		}

		CViewH3H1::View CViewH3H1PropertyList::StringToView(const String &value)
		{
			if (value == L"View::Left")
				return CViewH3H1::View::Left;
			if (value == L"View::Middle")
				return CViewH3H1::View::Middle;
			if (value == L"View::Right")
				return CViewH3H1::View::Right;
			if (value == L"View::Bottom")
				return CViewH3H1::View::Bottom;
			return CViewH3H1::View::None;
		}

		String CViewH3H1PropertyList::ViewToString(const CViewH3H1::View value)
		{
			switch (value)
			{
			case CViewH3H1::View::Left:		return L"View::Left";
			case CViewH3H1::View::Middle:	return L"View::Middle";
			case CViewH3H1::View::Right:	return L"View::Right";
			case CViewH3H1::View::Bottom:	return L"View::Bottom";
			default:						return L"View::None";
			}
		}
	}
}