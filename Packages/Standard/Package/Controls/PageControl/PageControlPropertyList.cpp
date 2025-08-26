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
		CPageControlPropertyList::CPageControlPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"WantTabs");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyInteger(this, control, L"ActiveIndex", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getActiveIndex(); },
				[](IClass *parent, const int value) {return cast<CPageControl*>(parent)->setActiveIndex(value); }));
			Add(new CPropertyPointF(this, control, L"HeaderSize", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getHeaderSize(); },
				[](IClass *parent, const PointF value) {return cast<CPageControl*>(parent)->setHeaderSize(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"HeaderPosition", false, HeaderPositionItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return HeaderPositionToString(cast<CPageControl*>(parent)->getHeaderPosition()); },
				[](IClass *parent, const String value) {return cast<CPageControl*>(parent)->setHeaderPosition(StringToHeaderPosition(value)); }));
			Add(new CPropertyBool(this, control, L"Multiline", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->isMultiline(); },
				[](IClass *parent, const bool value) {return cast<CPageControl*>(parent)->setMultiline(value); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CPageControl*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"BorderColor", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CPageControl*>(parent)->setBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CPageControl*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyPointF(this, control, L"HeaderShift", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getHeaderShift(); },
				[](IClass *parent, const PointF value) {return cast<CPageControl*>(parent)->setHeaderShift(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"HeaderPadding", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getHeaderPadding(); },
				[](IClass *parent, const RectF value) {return cast<CPageControl*>(parent)->setHeaderPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"HeaderBorderWidth", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getHeaderBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CPageControl*>(parent)->setHeaderBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"HeaderBorderColor", false, TabStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getHeaderBorderColor(StringToTabState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CPageControl*>(parent)->setHeaderBorderColor(StringToTabState(state), value); }));
			Add(new CPropertyColorState(this, control, L"HeaderBackgroundColor", false, TabStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getHeaderBackgroundColor(StringToTabState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CPageControl*>(parent)->setHeaderBackgroundColor(StringToTabState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"HeaderBackgroundGradient", TabStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getHeaderBackgroundGradient(StringToTabState(state)); }));
			Add(new CPropertyColorState(this, control, L"CaptionColor", false, TabStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getCaptionColor(StringToTabState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CPageControl*>(parent)->setCaptionColor(StringToTabState(state), value); }));
			Add(new CPropertyColorState(this, control, L"CaptionShadowColor", false, TabStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getCaptionShadowColor(StringToTabState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CPageControl*>(parent)->setCaptionShadowColor(StringToTabState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"CaptionShadowShift", false, TabStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getCaptionShadowShift(StringToTabState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CPageControl*>(parent)->setCaptionShadowShift(StringToTabState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"CaptionShadowRadius", false, TabStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getCaptionShadowRadius(StringToTabState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CPageControl*>(parent)->setCaptionShadowRadius(StringToTabState(state), value); }))
				->setMin(1);
			Add(new CPropertyComponentImageList(this, control, L"ImageList", nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getImageList(); },
				[](IClass *parent, IImageList *value) {return cast<CPageControl*>(parent)->setImageList(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollArrowSize", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getScrollArrowSize(); },
				[](IClass *parent, const float value) {return cast<CPageControl*>(parent)->setScrollArrowSize(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ScrollBorderWidth", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getScrollBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CPageControl*>(parent)->setScrollBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ScrollBorderRadius", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getScrollBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CPageControl*>(parent)->setScrollBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"ScrollBorderColor", false, ScrollStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getScrollBorderColor(StringToScrollState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CPageControl*>(parent)->setScrollBorderColor(StringToScrollState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ScrollBackgroundColor", false, ScrollStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getScrollBackgroundColor(StringToScrollState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CPageControl*>(parent)->setScrollBackgroundColor(StringToScrollState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"ScrollBackgroundGradient", ScrollStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getScrollBackgroundGradient(StringToScrollState(state)); }));
			Add(new CPropertyColorState(this, control, L"ScrollArrowColor", false, ScrollStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) { return cast<CPageControl*>(parent)->getScrollArrowColor(StringToScrollState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CPageControl*>(parent)->setScrollArrowColor(StringToScrollState(state), value); }));
			Add(new CPropertyRectF(this, control, L"IconPadding", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getIconPadding(); },
				[](IClass *parent, const RectF value) {return cast<CPageControl*>(parent)->setIconPadding(value); }))
				->setMin(0);
			Add(new CPropertyBool(this, control, L"UseMask", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->isUseMask(); },
				[](IClass *parent, const bool value) {return cast<CPageControl*>(parent)->setUseMask(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CPageControl*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"DeltaScrollTimer", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getDeltaScrollTimer(); },
				[](IClass *parent, const float value) {return cast<CPageControl*>(parent)->setDeltaScrollTimer(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"DeltaScrollWheel", false, nullptr,
				[](IClass *parent) { return cast<CPageControl*>(parent)->getDeltaScrollWheel(); },
				[](IClass *parent, const float value) {return cast<CPageControl*>(parent)->setDeltaScrollWheel(value); }))
				->setMin(0);
		}

		StringArray CPageControlPropertyList::HeaderPositionItems()
		{
			return StringArray{
				L"HeaderPosition::Left",
				L"HeaderPosition::Top",
				L"HeaderPosition::Right",
				L"HeaderPosition::Bottom" };
		}

		String CPageControlPropertyList::HeaderPositionToString(const CPageControl::HeaderPosition value)
		{
			switch (value)
			{
			case CPageControl::HeaderPosition::Left:	return L"HeaderPosition::Left";
			case CPageControl::HeaderPosition::Right:	return L"HeaderPosition::Right";
			case CPageControl::HeaderPosition::Bottom:	return L"HeaderPosition::Bottom";
			default:									return L"HeaderPosition::Top";
			}
		}

		CPageControl::HeaderPosition CPageControlPropertyList::StringToHeaderPosition(const String &value)
		{
			if (value == L"HeaderPosition::Left")
				return CPageControl::HeaderPosition::Left;
			if (value == L"HeaderPosition::Right")
				return CPageControl::HeaderPosition::Right;
			if (value == L"HeaderPosition::Bottom")
				return CPageControl::HeaderPosition::Bottom;
			return CPageControl::HeaderPosition::Top;
		}

		StringArray CPageControlPropertyList::TabStateItems()
		{
			return StringArray{
				L"TabState::Normal",
				L"TabState::Hovered",
				L"TabState::Active",
				L"TabState::ActiveFocused",
				L"TabState::Disabled" };
		}

		CPageControl::TabState CPageControlPropertyList::StringToTabState(const String &state)
		{
			if (state == L"TabState::Hovered")
				return CPageControl::TabState::Hovered;
			if (state == L"TabState::Active")
				return CPageControl::TabState::Active;
			if (state == L"TabState::ActiveFocused")
				return CPageControl::TabState::ActiveFocused;
			if (state == L"TabState::Disabled")
				return CPageControl::TabState::Disabled;
			return CPageControl::TabState::Normal;
		}

		StringArray CPageControlPropertyList::ScrollStateItems()
		{
			return StringArray{
				L"ScrollState::Normal",
				L"ScrollState::Hovered",
				L"ScrollState::Active",
				L"ScrollState::ActiveHovered",
				L"ScrollState::Disabled" };
		}

		CPageControl::ScrollState CPageControlPropertyList::StringToScrollState(const String &state)
		{
			if (state == L"ScrollState::Hovered")
				return CPageControl::ScrollState::Hovered;
			if (state == L"ScrollState::Active")
				return CPageControl::ScrollState::Active;
			if (state == L"ScrollState::ActiveHovered")
				return CPageControl::ScrollState::ActiveHovered;
			if (state == L"ScrollState::Disabled")
				return CPageControl::ScrollState::Disabled;
			return CPageControl::ScrollState::Normal;
		}
	}
}