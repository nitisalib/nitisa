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
	namespace standard
	{
		CBitBtnPropertyList::CBitBtnPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CBitBtn*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CBitBtn*>(parent)->setCaption(value); }))
				->setChanged(true);
			Add(new CPropertyEnum(this, control, L"Kind", false, KindItems(), ExportPrefixType::Namespace, L"IBitBtn::", nullptr,
				[](IClass *parent) {return KindToString(cast<CBitBtn*>(parent)->getKind()); },
				[](IClass *parent, const String value) {return cast<CBitBtn*>(parent)->setKind(StringToKind(value)); }))
				->AddHeaderFile(L"Standard/Controls/IBitBtn.h");
			Add(new CPropertyRectFState(this, control, L"OuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CBitBtn*>(parent)->setOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"InnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CBitBtn*>(parent)->setInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CBitBtn*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"OuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CBitBtn*>(parent)->setOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"InnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CBitBtn*>(parent)->setInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CBitBtn*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CBitBtn*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CBitBtn*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CBitBtn*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyRectFState(this, control, L"Padding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CBitBtn*>(parent)->setPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyEnumState(this, control, L"ContentHorizontalAlign", false, StateItems(), ExportPrefixType::NamespaceParent, L"", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CBitBtn*>(parent)->getContentHorizontalAlign(StringToState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CBitBtn*>(parent)->setContentHorizontalAlign(StringToState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnumState(this, control, L"ContentVerticalAlign", false, StateItems(), ExportPrefixType::NamespaceParent, L"", VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return VerticalAlignToString(cast<CBitBtn*>(parent)->getContentVerticalAlign(StringToState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CBitBtn*>(parent)->setContentVerticalAlign(StringToState(state), StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyColorState(this, control, L"CaptionColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getCaptionColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CBitBtn*>(parent)->setCaptionColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"CaptionShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getCaptionShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CBitBtn*>(parent)->setCaptionShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"CaptionShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getCaptionShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CBitBtn*>(parent)->setCaptionShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"CaptionShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getCaptionShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CBitBtn*>(parent)->setCaptionShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyFloatState(this, control, L"IconPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->getIconPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CBitBtn*>(parent)->setIconPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBoolState(this, control, L"IconOnRight", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CBitBtn*>(parent)->isIconOnRight(StringToState(state)); },
				[](IClass *parent, const String &state, const bool value) {return cast<CBitBtn*>(parent)->setIconOnRight(StringToState(state), value); }));
		}

		StringArray CBitBtnPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Active",
				L"State::ActiveHovered",
				L"State::Disabled" };
		}

		CBitBtn::State CBitBtnPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CBitBtn::State::Hovered;
			if (state == L"State::Focused")
				return CBitBtn::State::Focused;
			if (state == L"State::FocusedHovered")
				return CBitBtn::State::FocusedHovered;
			if (state == L"State::Active")
				return CBitBtn::State::Active;
			if (state == L"State::ActiveHovered")
				return CBitBtn::State::ActiveHovered;
			if (state == L"State::Disabled")
				return CBitBtn::State::Disabled;
			return CBitBtn::State::Normal;
		}

		StringArray CBitBtnPropertyList::KindItems()
		{
			return StringArray{
				L"Kind::Abord",
				L"Kind::All",
				L"Kind::Cancel",
				L"Kind::Close",
				L"Kind::Help",
				L"Kind::Ignore",
				L"Kind::No",
				L"Kind::Ok",
				L"Kind::Retry",
				L"Kind::Yes" };
		}

		String CBitBtnPropertyList::KindToString(const IBitBtn::Kind value)
		{
			switch (value)
			{
			case IBitBtn::Kind::Abord:		return L"Kind::Abord";
			case IBitBtn::Kind::All:		return L"Kind::All";
			case IBitBtn::Kind::Cancel:		return L"Kind::Cancel";
			case IBitBtn::Kind::Close:		return L"Kind::Close";
			case IBitBtn::Kind::Help:		return L"Kind::Help";
			case IBitBtn::Kind::Ignore:		return L"Kind::Ignore";
			case IBitBtn::Kind::No:			return L"Kind::No";
			case IBitBtn::Kind::Ok:			return L"Kind::Ok";
			case IBitBtn::Kind::Retry:		return L"Kind::Retry";
			default:						return L"Kind::Yes";
			}
		}

		IBitBtn::Kind CBitBtnPropertyList::StringToKind(const String &state)
		{
			if (state == L"Kind::Abord")
				return CBitBtn::Kind::Abord;
			if (state == L"Kind::All")
				return CBitBtn::Kind::All;
			if (state == L"Kind::Cancel")
				return CBitBtn::Kind::Cancel;
			if (state == L"Kind::Close")
				return CBitBtn::Kind::Close;
			if (state == L"Kind::Help")
				return CBitBtn::Kind::Help;
			if (state == L"Kind::Ignore")
				return CBitBtn::Kind::Ignore;
			if (state == L"Kind::No")
				return CBitBtn::Kind::No;
			if (state == L"Kind::Ok")
				return CBitBtn::Kind::Ok;
			if (state == L"Kind::Retry")
				return CBitBtn::Kind::Retry;
			return CBitBtn::Kind::Yes;
		}
	}
}