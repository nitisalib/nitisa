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
		CMultiButtonPropertyList::CMultiButtonPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"TransformControls");
			Delete(L"Align");

			Add(new CPropertyFloat(this, control, L"Delay", false, nullptr,
				[](IClass *parent) {return cast<CMultiButton*>(parent)->getDelay(); },
				[](IClass *parent, const float value) {return cast<CMultiButton*>(parent)->setDelay(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"ActiveButtonIndex", false, nullptr,
				[](IClass *parent) {return cast<CMultiButton*>(parent)->getActiveButtonIndex(); },
				[](IClass *parent, const int value) {return cast<CMultiButton*>(parent)->setActiveButtonIndex(value); }))
				->setMin(-1);
			Add(new CPropertyComponentImageList(this, control, L"ImageList", nullptr,
				[](IClass *parent) {return cast<CMultiButton*>(parent)->getImageList(); },
				[](IClass *parent, IImageList *value) {return cast<CMultiButton*>(parent)->setImageList(value); }));
			Add(new CPropertyEnum(this, control, L"OpenDirection", false, OpenDirectionItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return OpenDirectionToString(cast<CMultiButton*>(parent)->getOpenDirection()); },
				[](IClass *parent, const String value) {return cast<CMultiButton*>(parent)->setOpenDirection(StringToOpenDirection(value)); }))
				->AddHeaderFile(L"Standard/Controls/MultiButton/MultiButton.h");
			Add(new CPropertyMaskState(this, control, L"OutlineMask", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getOutlineMask(StringToState(state)); },
				[](IClass *parent, const String &state, const unsigned int value) {return cast<CMultiButton*>(parent)->setOutlineMask(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"OutlineColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getOutlineColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMultiButton*>(parent)->setOutlineColor(StringToState(state), value); }));
			Add(new CPropertyFloatState(this, control, L"OpenerSize", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getOpenerSize(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CMultiButton*>(parent)->setOpenerSize(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"OpenerColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getOpenerColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMultiButton*>(parent)->setOpenerColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMultiButton*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"OuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMultiButton*>(parent)->setOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"OuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMultiButton*>(parent)->setOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"InnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMultiButton*>(parent)->setInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"InnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMultiButton*>(parent)->setInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMultiButton*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"Padding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMultiButton*>(parent)->setPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyEnumState(this, control, L"ImageSize", false, StateItems(), ExportPrefixType::NamespaceParent, L"", ImageSizeItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return ImageSizeToString(cast<CMultiButton*>(parent)->getImageSize(StringToState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMultiButton*>(parent)->setImageSize(StringToState(state), StringToImageSize(value)); }));
			Add(new CPropertyEnumState(this, control, L"CaptionHorizontalAlign", false, StateItems(), ExportPrefixType::NamespaceParent, L"", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CMultiButton*>(parent)->getCaptionHorizontalAlign(StringToState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMultiButton*>(parent)->setCaptionHorizontalAlign(StringToState(state), StringToTextAlign(value)); }));
			Add(new CPropertyEnumState(this, control, L"CaptionVerticalAlign", false, StateItems(), ExportPrefixType::NamespaceParent, L"", VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return VerticalAlignToString(cast<CMultiButton*>(parent)->getCaptionVerticalAlign(StringToState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMultiButton*>(parent)->setCaptionVerticalAlign(StringToState(state), StringToVerticalAlign(value)); }));
			Add(new CPropertyColorState(this, control, L"CaptionColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getCaptionColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMultiButton*>(parent)->setCaptionColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CMultiButton*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CMultiButton*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMultiButton*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMultiButton*>(parent)->setShadowColor(StringToState(state), value); }));
		}

		StringArray CMultiButtonPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Down",
				L"State::DownHovered",
				L"State::DownFocused",
				L"State::DownFocusedHovered",
				L"State::Active",
				L"State::ActiveHovered",
				L"State::Inactive",
				L"State::InactiveHovered",
				L"State::Disabled"
			};
		}

		CMultiButton::State CMultiButtonPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CMultiButton::State::Hovered;
			if (state == L"State::Focused")
				return CMultiButton::State::Focused;
			if (state == L"State::FocusedHovered")
				return CMultiButton::State::FocusedHovered;
			if (state == L"State::Down")
				return CMultiButton::State::Down;
			if (state == L"State::DownHovered")
				return CMultiButton::State::DownHovered;
			if (state == L"State::DownFocused")
				return CMultiButton::State::DownFocused;
			if (state == L"State::DownFocusedHovered")
				return CMultiButton::State::DownFocusedHovered;
			if (state == L"State::Active")
				return CMultiButton::State::Active;
			if (state == L"State::ActiveHovered")
				return CMultiButton::State::ActiveHovered;
			if (state == L"State::Inactive")
				return CMultiButton::State::Inactive;
			if (state == L"State::InactiveHovered")
				return CMultiButton::State::InactiveHovered;
			if (state == L"State::Disabled")
				return CMultiButton::State::Disabled;
			return CMultiButton::State::Normal;
		}

		StringArray CMultiButtonPropertyList::OpenDirectionItems()
		{
			return StringArray{
				L"OpenDirection::Left",
				L"OpenDirection::Top",
				L"OpenDirection::Right",
				L"OpenDirection::Bottom"
			};
		}

		String CMultiButtonPropertyList::OpenDirectionToString(const CMultiButton::OpenDirection state)
		{
			switch (state)
			{
			case CMultiButton::OpenDirection::Left: return L"OpenDirection::Left";
			case CMultiButton::OpenDirection::Top: return L"OpenDirection::Top";
			case CMultiButton::OpenDirection::Right: return L"OpenDirection::Right";
			default: return L"OpenDirection::Bottom";
			}
		}

		CMultiButton::OpenDirection CMultiButtonPropertyList::StringToOpenDirection(const String &state)
		{
			if (state == L"OpenDirection::Left")
				return CMultiButton::OpenDirection::Left;
			if (state == L"OpenDirection::Top")
				return CMultiButton::OpenDirection::Top;
			if (state == L"OpenDirection::Right")
				return CMultiButton::OpenDirection::Right;
			return CMultiButton::OpenDirection::Bottom;
		}

		StringArray CMultiButtonPropertyList::ImageSizeItems()
		{
			return StringArray{
				L"ImageSize::Original",
				L"ImageSize::Cover",
				L"ImageSize::Contain",
				L"ImageSize::Stretch"
			};
		}

		String CMultiButtonPropertyList::ImageSizeToString(const CMultiButton::ImageSize state)
		{
			switch (state)
			{
			case CMultiButton::ImageSize::Original: return L"ImageSize::Original";
			case CMultiButton::ImageSize::Cover: return L"ImageSize::Cover";
			case CMultiButton::ImageSize::Stretch: return L"ImageSize::Stretch";
			default: return L"ImageSize::Contain";
			}
		}

		CMultiButton::ImageSize CMultiButtonPropertyList::StringToImageSize(const String &state)
		{
			if (state == L"ImageSize::Original")
				return CMultiButton::ImageSize::Original;
			if (state == L"ImageSize::Cover")
				return CMultiButton::ImageSize::Cover;
			if (state == L"ImageSize::Stretch")
				return CMultiButton::ImageSize::Stretch;
			return CMultiButton::ImageSize::Contain;
		}
	}
}