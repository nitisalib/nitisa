// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		CCoolBarPropertyList::CCoolBarPropertyList(IPackage *package, IDialogBox *control, IPackageEntity *entity) :
			CDialogBoxPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"TransformControls");
			Delete(L"Align");
			Delete(L"Caption");
			Delete(L"ClientSize");
			Delete(L"WindowPosition");
			Delete(L"State");
			Delete(L"BorderWidth");
			Delete(L"HasCloseBox");
			Delete(L"HasMaximizeBox");
			Delete(L"HasMinimizeBox");
			Delete(L"HasSizeBox");
			Delete(L"HasSystemMenu");
			Delete(L"HasBorder");
			Delete(L"HasCaption");
			Delete(L"IsPopup");
			
			Add(new CPropertyEnum(this, control, L"Align", false, AlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) { return AlignToString(cast<CCoolBar*>(parent)->getAlign()); },
				[](IClass *parent, const String value) {return cast<CCoolBar*>(parent)->setAlign(StringToAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/Align.h");
			Add(new CPropertyEnum(this, control, L"Orientation", false, OrientationItems(), ExportPrefixType::Namespace, L"ICoolBar::", nullptr,
				[](IClass *parent) { return OrientationToString(cast<CCoolBar*>(parent)->getOrientation()); },
				[](IClass *parent, const String value) {return cast<CCoolBar*>(parent)->setOrientation(StringToOrientation(value)); }))
				->AddHeaderFile(L"Standard/Controls/ICoolBar.h");
			Add(new CPropertyFloat(this, control, L"StickDistance", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getStickDistance(); },
				[](IClass *parent, const float value) {return cast<CCoolBar*>(parent)->setStickDistance(value); }))
				->setMin(1);
			Add(new CPropertyBool(this, control, L"AutoAlign", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->isAutoAlign(); },
				[](IClass *parent, const bool value) {return cast<CCoolBar*>(parent)->setAutoAlign(value); }));
			Add(new CPropertyBool(this, control, L"Locked", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->isLocked(); },
				[](IClass *parent, const bool value) {return cast<CCoolBar*>(parent)->setLocked(value); }));
			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) {return cast<CCoolBar*>(parent)->setResizable(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CCoolBar*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyBool(this, control, L"MoverAlwaysVisible", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->isMoverAlwaysVisible(); },
				[](IClass *parent, const bool value) {return cast<CCoolBar*>(parent)->setMoverAlwaysVisible(value); }));
			Add(new CPropertyBool(this, control, L"ExtraAlwaysVisible", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->isExtraAlwaysVisible(); },
				[](IClass *parent, const bool value) {return cast<CCoolBar*>(parent)->setExtraAlwaysVisible(value); }));
			Add(new CPropertyEnum(this, control, L"MoverKind", false, MoverKindItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return MoverKindToString(cast<CCoolBar*>(parent)->getMoverKind()); },
				[](IClass *parent, const String value) {return cast<CCoolBar*>(parent)->setMoverKind(StringToMoverKind(value)); }));
			Add(new CPropertyRectF(this, control, L"OuterBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getOuterBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setOuterBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"OuterBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getOuterBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CCoolBar*>(parent)->setOuterBorderColor(value); }));
			Add(new CPropertyRectF(this, control, L"InnerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getInnerBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setInnerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"InnerBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getInnerBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CCoolBar*>(parent)->setInnerBorderColor(value); }));
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyRectF(this, control, L"MoverMargin", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getMoverMargin(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setMoverMargin(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"MoverBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getMoverBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setMoverBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"MoverPadding", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getMoverPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setMoverPadding(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"MoverBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getMoverBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCoolBar*>(parent)->setMoverBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"MoverBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getMoverBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCoolBar*>(parent)->setMoverBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"MoverBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getMoverBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"MoverForeground1Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getMoverForeground1Color(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCoolBar*>(parent)->setMoverForeground1Color(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"MoverForeground2Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getMoverForeground2Color(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCoolBar*>(parent)->setMoverForeground2Color(StringToState(state), value); }));
			Add(new CPropertyRectF(this, control, L"ExtraMargin", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraMargin(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setExtraMargin(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ExtraBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setExtraBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ExtraPadding", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setExtraPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ExtraSize", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraSize(); },
				[](IClass *parent, const float value) {return cast<CCoolBar*>(parent)->setExtraSize(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"ExtraBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getExtraBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCoolBar*>(parent)->setExtraBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ExtraBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getExtraBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCoolBar*>(parent)->setExtraBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"ExtraBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getExtraBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ExtraColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getExtraColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCoolBar*>(parent)->setExtraColor(StringToState(state), value); }));
			Add(new CPropertyPointF(this, control, L"ExtraListConstraints", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListConstraints(); },
				[](IClass *parent, const PointF value) {return cast<CCoolBar*>(parent)->setExtraListConstraints(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ExtraListOuterBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListOuterBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setExtraListOuterBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"ExtraListOuterBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListOuterBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CCoolBar*>(parent)->setExtraListOuterBorderColor(value); }));
			Add(new CPropertyRectF(this, control, L"ExtraListInnerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListInnerBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setExtraListInnerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"ExtraListInnerBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListInnerBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CCoolBar*>(parent)->setExtraListInnerBorderColor(value); }));
			Add(new CPropertyRectF(this, control, L"ExtraListPadding", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setExtraListPadding(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"ExtraListBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CCoolBar*>(parent)->setExtraListBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"ExtraListBackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListBackgroundGradient(); }));
			Add(new CPropertyInteger(this, control, L"ExtraListShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CCoolBar*>(parent)->setExtraListShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyPointF(this, control, L"ExtraListShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CCoolBar*>(parent)->setExtraListShadowShift(value); }));
			Add(new CPropertyColor(this, control, L"ExtraListShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CCoolBar*>(parent)->setExtraListShadowColor(value); }));
			Add(new CPropertyRectF(this, control, L"ExtraListButtonPadding", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListButtonPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setExtraListButtonPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ExtraListButtonBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getExtraListButtonBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setExtraListButtonBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"ExtraListButtonBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getExtraListButtonBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCoolBar*>(parent)->setExtraListButtonBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ExtraListButtonBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getExtraListButtonBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCoolBar*>(parent)->setExtraListButtonBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"ExtraListButtonBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getExtraListButtonBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ExtraListButtonColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getExtraListButtonColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCoolBar*>(parent)->setExtraListButtonColor(StringToState(state), value); }));
			Add(new CPropertyPointF(this, control, L"ToggleListConstraints", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListConstraints(); },
				[](IClass *parent, const PointF value) {return cast<CCoolBar*>(parent)->setToggleListConstraints(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ToggleListOuterBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListOuterBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setToggleListOuterBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"ToggleListOuterBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListOuterBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CCoolBar*>(parent)->setToggleListOuterBorderColor(value); }));
			Add(new CPropertyRectF(this, control, L"ToggleListInnerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListInnerBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setToggleListInnerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"ToggleListInnerBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListInnerBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CCoolBar*>(parent)->setToggleListInnerBorderColor(value); }));
			Add(new CPropertyRectF(this, control, L"ToggleListPadding", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setToggleListPadding(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"ToggleListBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CCoolBar*>(parent)->setToggleListBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"ToggleListBackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListBackgroundGradient(); }));
			Add(new CPropertyInteger(this, control, L"ToggleListShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CCoolBar*>(parent)->setToggleListShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyPointF(this, control, L"ToggleListShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CCoolBar*>(parent)->setToggleListShadowShift(value); }));
			Add(new CPropertyColor(this, control, L"ToggleListShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CCoolBar*>(parent)->setToggleListShadowColor(value); }));
			Add(new CPropertyFloat(this, control, L"ToggleListIconPadding", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListIconPadding(); },
				[](IClass *parent, const float value) {return cast<CCoolBar*>(parent)->setToggleListIconPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ToggleListElementPadding", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListElementPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setToggleListElementPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ToggleListElementBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCoolBar*>(parent)->getToggleListElementBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCoolBar*>(parent)->setToggleListElementBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"ToggleListElementBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getToggleListElementBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCoolBar*>(parent)->setToggleListElementBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ToggleListElementBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getToggleListElementBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCoolBar*>(parent)->setToggleListElementBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"ToggleListElementBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getToggleListElementBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ToggleListElementColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCoolBar*>(parent)->getToggleListElementColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCoolBar*>(parent)->setToggleListElementColor(StringToState(state), value); }));
		}

		StringArray CCoolBarPropertyList::AlignItems()
		{
			return StringArray{
				L"Align::None",
				L"Align::Left",
				L"Align::Top",
				L"Align::Right",
				L"Align::Bottom"
			};
		}

		StringArray CCoolBarPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Down",
				L"State::Disabled"
			};
		}

		CCoolBar::State CCoolBarPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CCoolBar::State::Hovered;
			if (state == L"State::Down")
				return CCoolBar::State::Down;
			if (state == L"State::Disabled")
				return CCoolBar::State::Disabled;
			return CCoolBar::State::Normal;
		}

		StringArray CCoolBarPropertyList::OrientationItems()
		{
			return StringArray{
				L"Orientation::LeftToRight",
				L"Orientation::TopToBottom",
				L"Orientation::RightToLeft",
				L"Orientation::BottomToTop"
			};
		}

		String CCoolBarPropertyList::OrientationToString(const ICoolBar::Orientation orientation)
		{
			switch (orientation)
			{
			case ICoolBar::Orientation::LeftToRight: return L"Orientation::LeftToRight";
			case ICoolBar::Orientation::TopToBottom: return L"Orientation::TopToBottom";
			case ICoolBar::Orientation::RightToLeft: return L"Orientation::RightToLeft";
			default: return L"Orientation::BottomToTop";
			}
		}

		ICoolBar::Orientation CCoolBarPropertyList::StringToOrientation(const String &orientation)
		{
			if (orientation == L"Orientation::TopToBottom")
				return ICoolBar::Orientation::TopToBottom;
			if (orientation == L"Orientation::RightToLeft")
				return ICoolBar::Orientation::RightToLeft;
			if (orientation == L"Orientation::BottomToTop")
				return ICoolBar::Orientation::BottomToTop;
			return ICoolBar::Orientation::LeftToRight;
		}

		StringArray CCoolBarPropertyList::MoverKindItems()
		{
			return StringArray{
				L"MoverKind::Flat",
				L"MoverKind::Line",
				L"MoverKind::DoubleLine",
				L"MoverKind::Dots",
				L"MoverKind::TripleDots"
			};
		}

		String CCoolBarPropertyList::MoverKindToString(const CCoolBar::MoverKind kind)
		{
			switch (kind)
			{
			case CCoolBar::MoverKind::Flat: return L"MoverKind::Flat";
			case CCoolBar::MoverKind::Line: return L"MoverKind::Line";
			case CCoolBar::MoverKind::DoubleLine: return L"MoverKind::DoubleLine";
			case CCoolBar::MoverKind::Dots: return L"MoverKind::Dots";
			default: return L"MoverKind::TripleDots";
			}
		}

		CCoolBar::MoverKind CCoolBarPropertyList::StringToMoverKind(const String &kind)
		{
			if (kind == L"MoverKind::Line")
				return CCoolBar::MoverKind::Line;
			if (kind == L"MoverKind::DoubleLine")
				return CCoolBar::MoverKind::DoubleLine;
			if (kind == L"MoverKind::Dots")
				return CCoolBar::MoverKind::Dots;
			if (kind == L"MoverKind::TripleDots")
				return CCoolBar::MoverKind::TripleDots;
			return CCoolBar::MoverKind::Flat;
		}
	}
}