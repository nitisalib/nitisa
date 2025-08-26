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
		CFramePropertyList::CFramePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"WantTabs");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CFrame*>(parent)->setCaption(value); }))
				->setChanged(true);
			Add(new CPropertyBool(this, control, L"Minimizable", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->isMinimizable(); },
				[](IClass *parent, const bool value) {return cast<CFrame*>(parent)->setMinimizable(value); }));
			Add(new CPropertyBool(this, control, L"Maximizable", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->isMaximizable(); },
				[](IClass *parent, const bool value) {return cast<CFrame*>(parent)->setMaximizable(value); }));
			Add(new CPropertyBool(this, control, L"Closable", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->isClosable(); },
				[](IClass *parent, const bool value) {return cast<CFrame*>(parent)->setClosable(value); }));
			Add(new CPropertyBool(this, control, L"Resizable", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->isResizable(); },
				[](IClass *parent, const bool value) {return cast<CFrame*>(parent)->setResizable(value); }));
			Add(new CPropertyBool(this, control, L"Movable", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->isMovable(); },
				[](IClass *parent, const bool value) {return cast<CFrame*>(parent)->setMovable(value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFrame*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CFrame*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CFrame*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyRectF(this, control, L"OuterBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getOuterBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setOuterBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"OuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CFrame*>(parent)->setOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectF(this, control, L"MiddleBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getMiddleBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setMiddleBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"MiddleBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getMiddleBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CFrame*>(parent)->setMiddleBorderColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"MiddleBorderGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getMiddleBorderGradient(StringToState(state)); }));
			Add(new CPropertyRectF(this, control, L"InnerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getInnerBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setInnerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"InnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CFrame*>(parent)->setInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFrame*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyFloat(this, control, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const float value) {return cast<CFrame*>(parent)->setCaptionPadding(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"CaptionColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getCaptionColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFrame*>(parent)->setCaptionColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"CaptionShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getCaptionShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFrame*>(parent)->setCaptionShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"CaptionShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getCaptionShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CFrame*>(parent)->setCaptionShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"CaptionShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getCaptionShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CFrame*>(parent)->setCaptionShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyBool(this, control, L"UseMask", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->isUseMask(); },
				[](IClass *parent, const bool value) {return cast<CFrame*>(parent)->setUseMask(value); }));
			Add(new CPropertyFloat(this, control, L"MinimizedWidth", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getMinimizedWidth(); },
				[](IClass *parent, const float value) {return cast<CFrame*>(parent)->setMinimizedWidth(value); }))
				->setMin(0);

			Add(new CPropertyBool(this, control, L"BtnMinimizeRestoreDisplayDisabled", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->isBtnMinimizeRestoreDisplayDisabled(); },
				[](IClass *parent, const bool value) {return cast<CFrame*>(parent)->setBtnMinimizeRestoreDisplayDisabled(value); }));
			Add(new CPropertyPointF(this, control, L"BtnMinimizeRestoreSize", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnMinimizeRestoreSize(); },
				[](IClass *parent, const PointF value) {return cast<CFrame*>(parent)->setBtnMinimizeRestoreSize(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BtnMinimizeRestoreBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnMinimizeRestoreBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setBtnMinimizeRestoreBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BtnMinimizeRestoreBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnMinimizeRestoreBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setBtnMinimizeRestoreBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BtnMinimizeRestoreIconPadding", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnMinimizeRestoreIconPadding(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setBtnMinimizeRestoreIconPadding(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BtnMinimizeRestoreBorderColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMinimizeRestoreBorderColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CFrame*>(parent)->setBtnMinimizeRestoreBorderColor(StringToButtonState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BtnMinimizeRestoreBackgroundColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMinimizeRestoreBackgroundColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFrame*>(parent)->setBtnMinimizeRestoreBackgroundColor(StringToButtonState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BtnMinimizeRestoreBackgroundGradient", ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMinimizeRestoreBackgroundGradient(StringToButtonState(state)); }));
			Add(new CPropertyColorState(this, control, L"BtnMinimizeRestoreShadowColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMinimizeRestoreShadowColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFrame*>(parent)->setBtnMinimizeRestoreShadowColor(StringToButtonState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"BtnMinimizeRestoreShadowShift", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMinimizeRestoreShadowShift(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CFrame*>(parent)->setBtnMinimizeRestoreShadowShift(StringToButtonState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"BtnMinimizeRestoreShadowRadius", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMinimizeRestoreShadowRadius(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CFrame*>(parent)->setBtnMinimizeRestoreShadowRadius(StringToButtonState(state), value); }))
				->setMin(1);

			Add(new CPropertyBool(this, control, L"BtnMaximizeRestoreDisplayDisabled", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->isBtnMaximizeRestoreDisplayDisabled(); },
				[](IClass *parent, const bool value) {return cast<CFrame*>(parent)->setBtnMaximizeRestoreDisplayDisabled(value); }));
			Add(new CPropertyPointF(this, control, L"BtnMaximizeRestoreSize", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnMaximizeRestoreSize(); },
				[](IClass *parent, const PointF value) {return cast<CFrame*>(parent)->setBtnMaximizeRestoreSize(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BtnMaximizeRestoreBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnMaximizeRestoreBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setBtnMaximizeRestoreBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BtnMaximizeRestoreBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnMaximizeRestoreBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setBtnMaximizeRestoreBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BtnMaximizeRestoreIconPadding", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnMaximizeRestoreIconPadding(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setBtnMaximizeRestoreIconPadding(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BtnMaximizeRestoreBorderColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMaximizeRestoreBorderColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CFrame*>(parent)->setBtnMaximizeRestoreBorderColor(StringToButtonState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BtnMaximizeRestoreBackgroundColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMaximizeRestoreBackgroundColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFrame*>(parent)->setBtnMaximizeRestoreBackgroundColor(StringToButtonState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BtnMaximizeRestoreBackgroundGradient", ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMaximizeRestoreBackgroundGradient(StringToButtonState(state)); }));
			Add(new CPropertyColorState(this, control, L"BtnMaximizeRestoreShadowColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMaximizeRestoreShadowColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFrame*>(parent)->setBtnMaximizeRestoreShadowColor(StringToButtonState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"BtnMaximizeRestoreShadowShift", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMaximizeRestoreShadowShift(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CFrame*>(parent)->setBtnMaximizeRestoreShadowShift(StringToButtonState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"BtnMaximizeRestoreShadowRadius", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnMaximizeRestoreShadowRadius(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CFrame*>(parent)->setBtnMaximizeRestoreShadowRadius(StringToButtonState(state), value); }))
				->setMin(1);

			Add(new CPropertyBool(this, control, L"BtnCloseDisplayDisabled", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->isBtnCloseDisplayDisabled(); },
				[](IClass *parent, const bool value) {return cast<CFrame*>(parent)->setBtnCloseDisplayDisabled(value); }));
			Add(new CPropertyPointF(this, control, L"BtnCloseSize", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnCloseSize(); },
				[](IClass *parent, const PointF value) {return cast<CFrame*>(parent)->setBtnCloseSize(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BtnCloseBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnCloseBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setBtnCloseBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BtnCloseBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnCloseBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setBtnCloseBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BtnCloseIconPadding", false, nullptr,
				[](IClass *parent) {return cast<CFrame*>(parent)->getBtnCloseIconPadding(); },
				[](IClass *parent, const RectF value) {return cast<CFrame*>(parent)->setBtnCloseIconPadding(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BtnCloseBorderColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnCloseBorderColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CFrame*>(parent)->setBtnCloseBorderColor(StringToButtonState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BtnCloseBackgroundColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnCloseBackgroundColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFrame*>(parent)->setBtnCloseBackgroundColor(StringToButtonState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BtnCloseBackgroundGradient", ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnCloseBackgroundGradient(StringToButtonState(state)); }));
			Add(new CPropertyColorState(this, control, L"BtnCloseShadowColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnCloseShadowColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFrame*>(parent)->setBtnCloseShadowColor(StringToButtonState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"BtnCloseShadowShift", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnCloseShadowShift(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CFrame*>(parent)->setBtnCloseShadowShift(StringToButtonState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"BtnCloseShadowRadius", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFrame*>(parent)->getBtnCloseShadowRadius(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CFrame*>(parent)->setBtnCloseShadowRadius(StringToButtonState(state), value); }))
				->setMin(1);
		}

		StringArray CFramePropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Active",
				L"State::Disabled" };
		}

		CFrame::State CFramePropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CFrame::State::Hovered;
			if (state == L"State::Active")
				return CFrame::State::Active;
			if (state == L"State::Disabled")
				return CFrame::State::Disabled;
			return CFrame::State::Normal;
		}

		StringArray CFramePropertyList::ButtonStateItems()
		{
			return StringArray{
				L"ButtonState::InactiveNormal",
				L"ButtonState::InactiveHovered",
				L"ButtonState::InactiveDisabled",
				L"ButtonState::Normal",
				L"ButtonState::Hovered",
				L"ButtonState::Active",
				L"ButtonState::ActiveHovered",
				L"ButtonState::Disabled" };
		}

		CFrame::ButtonState CFramePropertyList::StringToButtonState(const String &state)
		{
			if (state == L"ButtonState::InactiveHovered")
				return CFrame::ButtonState::InactiveHovered;
			if (state == L"ButtonState::InactiveDisabled")
				return CFrame::ButtonState::InactiveDisabled;
			if (state == L"ButtonState::Normal")
				return CFrame::ButtonState::Normal;
			if (state == L"ButtonState::Hovered")
				return CFrame::ButtonState::Hovered;
			if (state == L"ButtonState::Active")
				return CFrame::ButtonState::Active;
			if (state == L"ButtonState::ActiveHovered")
				return CFrame::ButtonState::ActiveHovered;
			if (state == L"ButtonState::Disabled")
				return CFrame::ButtonState::Disabled;
			return CFrame::ButtonState::InactiveNormal;
		}
	}
}