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
		CPropertyEditorPropertyList::CPropertyEditorPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Cursor");
			Delete(L"TransformControls");
			Delete(L"Enabled");

			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) { return cast<CPropertyEditor*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"BorderColor", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getBorderColor(); },
				[](IClass *parent, const BorderColor value) { return cast<CPropertyEditor*>(parent)->setBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) { return cast<CPropertyEditor*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyFloat(this, control, L"FolderWidth", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderWidth(); },
				[](IClass *parent, const float value) { return cast<CPropertyEditor*>(parent)->setFolderWidth(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"FolderBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderBackgroundColor(); },
				[](IClass *parent, const Color value) { return cast<CPropertyEditor*>(parent)->setFolderBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"FolderBackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderBackgroundGradient(); }));
			Add(new CPropertyFloat(this, control, L"FolderIconPadding", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderIconPadding(); },
				[](IClass *parent, const float value) { return cast<CPropertyEditor*>(parent)->setFolderIconPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"FolderIconBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderIconBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CPropertyEditor*>(parent)->setFolderIconBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"FolderIconBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderIconBorderRadius(); },
				[](IClass *parent, const float value) { return cast<CPropertyEditor*>(parent)->setFolderIconBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"FolderIconBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderIconBorderColor(); },
				[](IClass *parent, const Color value) { return cast<CPropertyEditor*>(parent)->setFolderIconBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"FolderIconBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderIconBackgroundColor(); },
				[](IClass *parent, const Color value) { return cast<CPropertyEditor*>(parent)->setFolderIconBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"FolderIconBackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderIconBackgroundGradient(); }));
			Add(new CPropertyFloat(this, control, L"FolderIconInnerPadding", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderIconInnerPadding(); },
				[](IClass *parent, const float value) { return cast<CPropertyEditor*>(parent)->setFolderIconInnerPadding(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"FolderIconLineColor", false, FolderStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CPropertyEditor*>(parent)->getFolderIconLineColor(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CPropertyEditor*>(parent)->setFolderIconLineColor(StringToFolderState(state), value); }));
			Add(new CPropertyFloat(this, control, L"FolderSeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CPropertyEditor*>(parent)->setFolderSeparatorWidth(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"FolderSeparatorColor", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderSeparatorColor(); },
				[](IClass *parent, const Color value) { return cast<CPropertyEditor*>(parent)->setFolderSeparatorColor(value); }));
			Add(new CPropertyGradient(this, control, L"FolderSeparatorGradient", nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getFolderSeparatorGradient(); }));
			Add(new CPropertyFloat(this, control, L"CaptionWidth", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getCaptionWidth(); },
				[](IClass *parent, const float value) { return cast<CPropertyEditor*>(parent)->setCaptionWidth(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyFloat(this, control, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const float value) { return cast<CPropertyEditor*>(parent)->setCaptionPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"CaptionStatePadding", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getCaptionStatePadding(); },
				[](IClass *parent, const float value) { return cast<CPropertyEditor*>(parent)->setCaptionStatePadding(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"CaptionColor", false, PropertyStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CPropertyEditor*>(parent)->getCaptionColor(StringToPropertyState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CPropertyEditor*>(parent)->setCaptionColor(StringToPropertyState(state), value); }));
			Add(new CPropertyFloatState(this, control, L"CaptionBorderWidth", false, PropertyStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CPropertyEditor*>(parent)->getCaptionBorderWidth(StringToPropertyState(state)); },
				[](IClass *parent, const String &state, const float value) { return cast<CPropertyEditor*>(parent)->setCaptionBorderWidth(StringToPropertyState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"CaptionBorderColor", false, PropertyStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CPropertyEditor*>(parent)->getCaptionBorderColor(StringToPropertyState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CPropertyEditor*>(parent)->setCaptionBorderColor(StringToPropertyState(state), value); }));
			Add(new CPropertyColorState(this, control, L"CaptionBackgroundColor", false, PropertyStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CPropertyEditor*>(parent)->getCaptionBackgroundColor(StringToPropertyState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CPropertyEditor*>(parent)->setCaptionBackgroundColor(StringToPropertyState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"CaptionBackgroundGradient", PropertyStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CPropertyEditor*>(parent)->getCaptionBackgroundGradient(StringToPropertyState(state)); }));
			Add(new CPropertyFloat(this, control, L"CaptionSeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getCaptionSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CPropertyEditor*>(parent)->setCaptionSeparatorWidth(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"CaptionSeparatorColor", false, nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getCaptionSeparatorColor(); },
				[](IClass *parent, const Color value) { return cast<CPropertyEditor*>(parent)->setCaptionSeparatorColor(value); }));
			Add(new CPropertyGradient(this, control, L"CaptionSeparatorGradient", nullptr,
				[](IClass *parent) {return cast<CPropertyEditor*>(parent)->getCaptionSeparatorGradient(); }));
		}

		StringArray CPropertyEditorPropertyList::FolderStates()
		{
			return StringArray{
				L"FolderState::Folded",
				L"FolderState::Unfolded" };
		}

		CPropertyEditor::FolderState CPropertyEditorPropertyList::StringToFolderState(const String &state)
		{
			if (state == L"FolderState::Unfolded")
				return CPropertyEditor::FolderState::Unfolded;
			return CPropertyEditor::FolderState::Folded;
		}

		StringArray CPropertyEditorPropertyList::PropertyStates()
		{
			return StringArray{
				L"PropertyState::Normal",
				L"PropertyState::Hovered",
				L"PropertyState::Focused" };
		}

		CPropertyEditor::PropertyState CPropertyEditorPropertyList::StringToPropertyState(const String &state)
		{
			if (state == L"PropertyState::Hovered")
				return CPropertyEditor::PropertyState::Hovered;
			if (state == L"PropertyState::Focused")
				return CPropertyEditor::PropertyState::Focused;
			return CPropertyEditor::PropertyState::Normal;
		}
	}
}