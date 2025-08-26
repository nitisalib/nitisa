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
		CScrollListPropertyList::CScrollListPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");

			Add(new CPropertyEnum(this, control, L"Orientation", false, OrientationItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return OrientationToString(cast<CScrollList*>(parent)->getOrientation()); },
				[](IClass *parent, const String value) {return cast<CScrollList*>(parent)->setOrientation(StringToOrientation(value)); }));
			Add(new CPropertyFloat(this, control, L"Scroll", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getScroll(); },
				[](IClass *parent, const float value) {return cast<CScrollList*>(parent)->setScroll(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ScrollSize", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getScrollSize(); },
				[](IClass *parent, const float value) {return cast<CScrollList*>(parent)->setScrollSize(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"ScrollVisibility", false, ScrollVisibilityItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CScrollList*>(parent)->getScrollVisibility()); },
				[](IClass *parent, const String value) {return cast<CScrollList*>(parent)->setScrollVisibility(StringToScrollVisibility(value)); }));
			Add(new CPropertyInteger(this, control, L"ShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CScrollList*>(parent)->setShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyColor(this, control, L"ShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CScrollList*>(parent)->setShadowColor(value); }));
			Add(new CPropertyPointF(this, control, L"ShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CScrollList*>(parent)->setShadowShift(value); }));
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CScrollList*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CScrollList*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyPointF(this, control, L"ScrollPadding", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getScrollPadding(); },
				[](IClass *parent, const PointF value) {return cast<CScrollList*>(parent)->setScrollPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"OuterBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getOuterBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CScrollList*>(parent)->setOuterBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"InnerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getInnerBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CScrollList*>(parent)->setInnerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"OuterBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getOuterBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CScrollList*>(parent)->setOuterBorderColor(value); }));
			Add(new CPropertyBorderColor(this, control, L"InnerBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getInnerBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CScrollList*>(parent)->setInnerBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CScrollList*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyFloat(this, control, L"Margin", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getMargin(); },
				[](IClass *parent, const float value) {return cast<CScrollList*>(parent)->setMargin(value); }))
				->setMin(0);

			Add(new CPropertyFloat(this, control, L"ScrollBarDeltaMedium", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getScrollBarDeltaMedium(); },
				[](IClass *parent, const float value) {return cast<CScrollList*>(parent)->setScrollBarDeltaMedium(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ScrollBarDeltaLarge", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getScrollBarDeltaLarge(); },
				[](IClass *parent, const float value) {return cast<CScrollList*>(parent)->setScrollBarDeltaLarge(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ScrollBarScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getScrollBarScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CScrollList*>(parent)->setScrollBarScrollInterval(value); }))
				->setMin(0.001f);
			CPropertyIntegerState *pis{ new CPropertyIntegerState(this, control, L"ScrollBarShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollList*>(parent)->getScrollBarShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CScrollList*>(parent)->setScrollBarShadowRadius(StringToState(state), value); }) };
			pis->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyColorState(this, control, L"ScrollBarShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollList*>(parent)->getScrollBarShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollList*>(parent)->setScrollBarShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyPointFState(this, control, L"ScrollBarShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollList*>(parent)->getScrollBarShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CScrollList*>(parent)->setScrollBarShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyBool(this, control, L"ScrollBarBorderRound", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->isScrollBarBorderRound(); },
				[](IClass *parent, const bool value) {return cast<CScrollList*>(parent)->setScrollBarBorderRound(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollBarBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getScrollBarBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CScrollList*>(parent)->setScrollBarBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"ScrollBarBorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollList*>(parent)->getScrollBarBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollList*>(parent)->setScrollBarBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyColorState(this, control, L"ScrollBarBackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollList*>(parent)->getScrollBarBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollList*>(parent)->setScrollBarBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyGradientState(this, control, L"ScrollBarBackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollList*>(parent)->getScrollBarBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyBool(this, control, L"ScrollBarScrollerRound", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->isScrollBarScrollerRound(); },
				[](IClass *parent, const bool value) {return cast<CScrollList*>(parent)->setScrollBarScrollerRound(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollBarScrollerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollList*>(parent)->getScrollBarScrollerBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CScrollList*>(parent)->setScrollBarScrollerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"ScrollBarScrollerBorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollList*>(parent)->getScrollBarScrollerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollList*>(parent)->setScrollBarScrollerBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyColorState(this, control, L"ScrollBarScrollerBackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollList*>(parent)->getScrollBarScrollerBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollList*>(parent)->setScrollBarScrollerBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyGradientState(this, control, L"ScrollBarScrollerBackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollList*>(parent)->getScrollBarScrollerBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
		}

		StringArray CScrollListPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Active",
				L"State::Disabled" };
		}

		CBuiltInScrollLite::State CScrollListPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CBuiltInScrollLite::State::Hovered;
			if (state == L"State::Active")
				return CBuiltInScrollLite::State::Active;
			if (state == L"State::Disabled")
				return CBuiltInScrollLite::State::Disabled;
			return CBuiltInScrollLite::State::Normal;
		}

		StringArray CScrollListPropertyList::OrientationItems()
		{
			return StringArray{
				L"Orientation::LeftToRight",
				L"Orientation::TopToBottom" };
		}

		String CScrollListPropertyList::OrientationToString(const IScrollList::Orientation value)
		{
			switch (value)
			{
			case IScrollList::Orientation::TopToBottom:	return L"Orientation::TopToBottom";
			default:									return L"Orientation::LeftToRight";
			}
		}

		IScrollList::Orientation CScrollListPropertyList::StringToOrientation(const String &value)
		{
			if (value == L"Orientation::TopToBottom")
				return IScrollList::Orientation::TopToBottom;
			return IScrollList::Orientation::LeftToRight;
		}
	}
}