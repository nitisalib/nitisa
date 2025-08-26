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
		CDialogBoxExPropertyList::CDialogBoxExPropertyList(IPackage *package, IDialogBox *control, IPackageEntity *entity) : CDialogBoxPropertyList(package, control, entity)
		{
			Delete(L"Align");

			Add(new CPropertyBool(this, control, L"UseMask", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->isUseMask(); },
				[](IClass *parent, const bool value) {return cast<CDialogBoxEx*>(parent)->setUseMask(value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyFloat(this, control, L"CaptionHeight", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getCaptionHeight(); },
				[](IClass *parent, const float value) {return cast<CDialogBoxEx*>(parent)->setCaptionHeight(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDialogBoxEx*>(parent)->setCaptionPadding(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"CaptionHorizontalAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CDialogBoxEx*>(parent)->getCaptionHorizontalAlign()); },
				[](IClass *parent, const String value) {return cast<CDialogBoxEx*>(parent)->setCaptionHorizontalAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnum(this, control, L"CaptionVerticalAlign", false, VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return VerticalAlignToString(cast<CDialogBoxEx*>(parent)->getCaptionVerticalAlign()); },
				[](IClass *parent, const String value) {return cast<CDialogBoxEx*>(parent)->setCaptionVerticalAlign(StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyColorState(this, control, L"CaptionColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getCaptionColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDialogBoxEx*>(parent)->setCaptionColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"CaptionGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getCaptionGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"CaptionTextColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getCaptionTextColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDialogBoxEx*>(parent)->setCaptionTextColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, WindowStateItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getBorderRadius(StringToWindowState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDialogBoxEx*>(parent)->setBorderRadius(StringToWindowState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ResizeBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getResizeBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CDialogBoxEx*>(parent)->setResizeBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Margin", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getMargin(); },
				[](IClass *parent, const RectF value) {return cast<CDialogBoxEx*>(parent)->setMargin(value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"RimWidth", false, WindowStateItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getRimWidth(StringToWindowState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDialogBoxEx*>(parent)->setRimWidth(StringToWindowState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDialogBoxEx*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDialogBoxEx*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyPointF(this, control, L"ButtonSize", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getButtonSize(); },
				[](IClass *parent, const PointF value) {return cast<CDialogBoxEx*>(parent)->setButtonSize(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ButtonPadding", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getButtonPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDialogBoxEx*>(parent)->setButtonPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ButtonBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getButtonBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CDialogBoxEx*>(parent)->setButtonBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ButtonBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getButtonBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CDialogBoxEx*>(parent)->setButtonBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"ButtonBorderColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getButtonBorderColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDialogBoxEx*>(parent)->setButtonBorderColor(StringToButtonState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ButtonBackgroundColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getButtonBackgroundColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDialogBoxEx*>(parent)->setButtonBackgroundColor(StringToButtonState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"ButtonBackgroundGradient", ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getButtonBackgroundGradient(StringToButtonState(state)); }));
			Add(new CPropertyComponentImageList(this, control, L"ButtonIcons", nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getButtonIcons(); },
				[](IClass *parent, IImageList *value) {return cast<CDialogBoxEx*>(parent)->setButtonIcons(value); }));
			Add(new CPropertyIntegerState(this, control, L"CloseIconIndex", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getCloseIconIndex(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CDialogBoxEx*>(parent)->setCloseIconIndex(StringToButtonState(state), value); }))
				->setMin(-1);
			Add(new CPropertyIntegerState(this, control, L"MinimizeIconIndex", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getMinimizeIconIndex(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CDialogBoxEx*>(parent)->setMinimizeIconIndex(StringToButtonState(state), value); }))
				->setMin(-1);
			Add(new CPropertyIntegerState(this, control, L"MaximizeIconIndex", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getMaximizeIconIndex(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CDialogBoxEx*>(parent)->setMaximizeIconIndex(StringToButtonState(state), value); }))
				->setMin(-1);
			Add(new CPropertyIntegerState(this, control, L"RestoreIconIndex", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getRestoreIconIndex(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CDialogBoxEx*>(parent)->setRestoreIconIndex(StringToButtonState(state), value); }))
				->setMin(-1);
			Add(new CPropertyBool(this, control, L"UseDefaultCloseIcon", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->isUseDefaultCloseIcon(); },
				[](IClass *parent, const bool value) {return cast<CDialogBoxEx*>(parent)->setUseDefaultCloseIcon(value); }));
			Add(new CPropertyBool(this, control, L"UseDefaultMinimizeIcon", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->isUseDefaultMinimizeIcon(); },
				[](IClass *parent, const bool value) {return cast<CDialogBoxEx*>(parent)->setUseDefaultMinimizeIcon(value); }));
			Add(new CPropertyBool(this, control, L"UseDefaultMaximizeIcon", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->isUseDefaultMaximizeIcon(); },
				[](IClass *parent, const bool value) {return cast<CDialogBoxEx*>(parent)->setUseDefaultMaximizeIcon(value); }));
			Add(new CPropertyBool(this, control, L"UseDefaultRestoreIcon", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->isUseDefaultRestoreIcon(); },
				[](IClass *parent, const bool value) {return cast<CDialogBoxEx*>(parent)->setUseDefaultRestoreIcon(value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDialogBoxEx*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CDialogBoxEx*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CDialogBoxEx*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyFloat(this, control, L"MinimizedWidth", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getMinimizedWidth(); },
				[](IClass *parent, const float value) {return cast<CDialogBoxEx*>(parent)->setMinimizedWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"IconPadding", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getIconPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDialogBoxEx*>(parent)->setIconPadding(value); }))
				->setMin(0);
			Add(new CPropertyComponentImageList(this, control, L"Icons", nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getIcons(); },
				[](IClass *parent, IImageList *value) {return cast<CDialogBoxEx*>(parent)->setIcons(value); }));
			Add(new CPropertyIntegerState(this, control, L"IconIndex", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDialogBoxEx*>(parent)->getIconIndex(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CDialogBoxEx*>(parent)->setIconIndex(StringToState(state), value); }))
				->setMin(-1);
			Add(new CPropertyFloat(this, control, L"BlinkInterval", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getBlinkInterval(); },
				[](IClass *parent, const float value) {return cast<CDialogBoxEx*>(parent)->setBlinkInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"BlinkCount", false, nullptr,
				[](IClass *parent) {return cast<CDialogBoxEx*>(parent)->getBlinkCount(); },
				[](IClass *parent, const int value) {return cast<CDialogBoxEx*>(parent)->setBlinkCount(value); }))
				->setMin(0);
		}

		StringArray CDialogBoxExPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active",
				L"State::Modal",
				L"State::Blinking",
				L"State::Disabled" };
		}

		CDialogBoxEx::State CDialogBoxExPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CDialogBoxEx::State::Active;
			if (state == L"State::Modal")
				return CDialogBoxEx::State::Modal;
			if (state == L"State::Blinking")
				return CDialogBoxEx::State::Blinking;
			if (state == L"State::Disabled")
				return CDialogBoxEx::State::Disabled;
			return CDialogBoxEx::State::Normal;
		}

		StringArray CDialogBoxExPropertyList::ButtonStateItems()
		{
			return StringArray{
				L"ButtonState::Normal",
				L"ButtonState::Hovered",
				L"ButtonState::Down",
				L"ButtonState::DownHovered",
				L"ButtonState::Disabled" };
		}

		CDialogBoxEx::ButtonState CDialogBoxExPropertyList::StringToButtonState(const String &state)
		{
			if (state == L"ButtonState::Hovered")
				return CDialogBoxEx::ButtonState::Hovered;
			if (state == L"ButtonState::Down")
				return CDialogBoxEx::ButtonState::Down;
			if (state == L"ButtonState::DownHovered")
				return CDialogBoxEx::ButtonState::DownHovered;
			if (state == L"ButtonState::Disabled")
				return CDialogBoxEx::ButtonState::Disabled;
			return CDialogBoxEx::ButtonState::Normal;
		}
	}
}