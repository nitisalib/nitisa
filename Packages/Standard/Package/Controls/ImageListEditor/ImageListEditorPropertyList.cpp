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
		CImageListEditorPropertyList::CImageListEditorPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyComponentImageList(this, control, L"ImageList", nullptr,
				[](IClass *parent) {return cast<CImageListEditor*>(parent)->getImageList(); },
				[](IClass *parent, IImageList *value) {return cast<CImageListEditor*>(parent)->setImageList(value); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CImageListEditor*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CImageListEditor*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CImageListEditor*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CImageListEditor*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CImageListEditor*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CImageListEditor*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ItemDistance", false, nullptr,
				[](IClass *parent) {return cast<CImageListEditor*>(parent)->getItemDistance(); },
				[](IClass *parent, const float value) {return cast<CImageListEditor*>(parent)->setItemDistance(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CImageListEditor*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CImageListEditor*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CImageListEditor*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CImageListEditor*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CImageListEditor*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyRectFState(this, control, L"ItemBorderWidth", false, ItemStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getItemBorderWidth(StringToItemState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CImageListEditor*>(parent)->setItemBorderWidth(StringToItemState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"ItemBorderColor", false, ItemStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getItemBorderColor(StringToItemState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CImageListEditor*>(parent)->setItemBorderColor(StringToItemState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ItemBackgroundColor", false, ItemStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getItemBackgroundColor(StringToItemState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CImageListEditor*>(parent)->setItemBackgroundColor(StringToItemState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"ItemBackgroundGradient", ItemStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getItemBackgroundGradient(StringToItemState(state)); }));
			Add(new CPropertyColorState(this, control, L"ItemTextColor", false, ItemStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getItemTextColor(StringToItemState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CImageListEditor*>(parent)->setItemTextColor(StringToItemState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ItemTextShadowColor", false, ItemStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getItemTextShadowColor(StringToItemState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CImageListEditor*>(parent)->setItemTextShadowColor(StringToItemState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ItemTextShadowShift", false, ItemStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getItemTextShadowShift(StringToItemState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CImageListEditor*>(parent)->setItemTextShadowShift(StringToItemState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ItemTextShadowRadius", false, ItemStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CImageListEditor*>(parent)->getItemTextShadowRadius(StringToItemState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CImageListEditor*>(parent)->setItemTextShadowRadius(StringToItemState(state), value); }))
				->setMin(1);
		}

		StringArray CImageListEditorPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Disabled" };
		}

		CImageListEditor::State CImageListEditorPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CImageListEditor::State::Hovered;
			if (state == L"State::Disabled")
				return CImageListEditor::State::Disabled;
			return CImageListEditor::State::Normal;
		}

		StringArray CImageListEditorPropertyList::ItemStateItems()
		{
			return StringArray{
				L"ItemState::Normal",
				L"ItemState::Hovered",
				L"ItemState::Selected",
				L"ItemState::SelectedHovered",
				L"ItemState::SelectedDisabled",
				L"ItemState::Disabled" };
		}

		CImageListEditor::ItemState CImageListEditorPropertyList::StringToItemState(const String &state)
		{
			if (state == L"ItemState::Hovered")
				return CImageListEditor::ItemState::Hovered;
			if (state == L"ItemState::Selected")
				return CImageListEditor::ItemState::Selected;
			if (state == L"ItemState::SelectedHovered")
				return CImageListEditor::ItemState::SelectedHovered;
			if (state == L"ItemState::SelectedDisabled")
				return CImageListEditor::ItemState::SelectedDisabled;
			if (state == L"ItemState::Disabled")
				return CImageListEditor::ItemState::Disabled;
			return CImageListEditor::ItemState::Normal;
		}
	}
}