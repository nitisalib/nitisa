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
		CDirectoryTreePropertyList::CDirectoryTreePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyString(this, control, L"RootDirectory", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getRootDirectory(); },
				[](IClass *parent, const String value) {return cast<CDirectoryTree*>(parent)->setRootDirectory(value); }));
			Add(new CPropertyString(this, control, L"Filter", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getFilter(); },
				[](IClass *parent, const String value) {return cast<CDirectoryTree*>(parent)->setFilter(value); }));
			Add(new CPropertyControlFileList(this, control, L"FileList", nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getFileList(); },
				[](IClass *parent, IFileList *value) {return cast<CDirectoryTree*>(parent)->setFileList(value); }));
			Add(new CPropertyBool(this, control, L"ShowArchieved", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->isShowArchieved(); },
				[](IClass *parent, const bool value) {return cast<CDirectoryTree*>(parent)->setShowArchieved(value); }));
			Add(new CPropertyBool(this, control, L"ShowCompressed", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->isShowCompressed(); },
				[](IClass *parent, const bool value) {return cast<CDirectoryTree*>(parent)->setShowCompressed(value); }));
			Add(new CPropertyBool(this, control, L"ShowEncrypted", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->isShowEncrypted(); },
				[](IClass *parent, const bool value) {return cast<CDirectoryTree*>(parent)->setShowEncrypted(value); }));
			Add(new CPropertyBool(this, control, L"ShowHidden", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->isShowHidden(); },
				[](IClass *parent, const bool value) {return cast<CDirectoryTree*>(parent)->setShowHidden(value); }));
			Add(new CPropertyBool(this, control, L"ShowNormal", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->isShowNormal(); },
				[](IClass *parent, const bool value) {return cast<CDirectoryTree*>(parent)->setShowNormal(value); }));
			Add(new CPropertyBool(this, control, L"ShowOffline", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->isShowOffline(); },
				[](IClass *parent, const bool value) {return cast<CDirectoryTree*>(parent)->setShowOffline(value); }));
			Add(new CPropertyBool(this, control, L"ShowReadOnly", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->isShowReadOnly(); },
				[](IClass *parent, const bool value) {return cast<CDirectoryTree*>(parent)->setShowReadOnly(value); }));
			Add(new CPropertyBool(this, control, L"ShowSystem", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->isShowSystem(); },
				[](IClass *parent, const bool value) {return cast<CDirectoryTree*>(parent)->setShowSystem(value); }));
			Add(new CPropertyBool(this, control, L"ShowTemporary", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->isShowTemporary(); },
				[](IClass *parent, const bool value) {return cast<CDirectoryTree*>(parent)->setShowTemporary(value); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CDirectoryTree*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CDirectoryTree*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDirectoryTree*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDirectoryTree*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDirectoryTree*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDirectoryTree*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CDirectoryTree*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CDirectoryTree*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyColorState(this, control, L"CornerColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getCornerColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDirectoryTree*>(parent)->setCornerColor(StringToState(state), value); }));
			Add(new CPropertyFloat(this, control, L"ItemHeight", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getItemHeight(); },
				[](IClass *parent, const float value) {return cast<CDirectoryTree*>(parent)->setItemHeight(value); }));
			Add(new CPropertyPointF(this, control, L"FolderSize", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getFolderSize(); },
				[](IClass *parent, const PointF value) {return cast<CDirectoryTree*>(parent)->setFolderSize(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"FolderLinesColor", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getFolderLinesColor(); },
				[](IClass *parent, const Color value) {return cast<CDirectoryTree*>(parent)->setFolderLinesColor(value); }));
			Add(new CPropertyRectFState(this, control, L"FolderBorderWidth", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getFolderBorderWidth(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDirectoryTree*>(parent)->setFolderBorderWidth(StringToFolderState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"FolderBorderRadius", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getFolderBorderRadius(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDirectoryTree*>(parent)->setFolderBorderRadius(StringToFolderState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"FolderBorderColor", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getFolderBorderColor(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDirectoryTree*>(parent)->setFolderBorderColor(StringToFolderState(state), value); }));
			Add(new CPropertyColorState(this, control, L"FolderBackgroundColor", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getFolderBackgroundColor(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDirectoryTree*>(parent)->setFolderBackgroundColor(StringToFolderState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"FolderBackgroundGradient", FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getFolderBackgroundGradient(StringToFolderState(state)); }));
			Add(new CPropertyPointFState(this, control, L"FolderSignSize", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getFolderSignSize(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CDirectoryTree*>(parent)->setFolderSignSize(StringToFolderState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"FolderSignColor", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDirectoryTree*>(parent)->getFolderSignColor(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDirectoryTree*>(parent)->setFolderSignColor(StringToFolderState(state), value); }));
			Add(new CPropertyBool(this, control, L"Multiselect", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->isMultiselect(); },
				[](IClass *parent, const bool value) {return cast<CDirectoryTree*>(parent)->setMultiselect(value); }));
			Add(new CPropertyEnum(this, control, L"HorisontalScroll", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CDirectoryTree*>(parent)->getHScrollVisibility()); },
				[](IClass *parent, const String value) {return cast<CDirectoryTree*>(parent)->setHScrollVisibility(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyEnum(this, control, L"VerticalScroll", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CDirectoryTree*>(parent)->getVScrollVisibility()); },
				[](IClass *parent, const String value) {return cast<CDirectoryTree*>(parent)->setVScrollVisibility(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CDirectoryTree*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"ScrollDelta", false, nullptr,
				[](IClass *parent) {return cast<CDirectoryTree*>(parent)->getScrollDelta(); },
				[](IClass *parent, const float value) {return cast<CDirectoryTree*>(parent)->setScrollDelta(value); }))
				->setMin(1);
		}

		StringArray CDirectoryTreePropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CDirectoryTree::State CDirectoryTreePropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CDirectoryTree::State::Hovered;
			if (state == L"State::Focused")
				return CDirectoryTree::State::Focused;
			if (state == L"State::FocusedHovered")
				return CDirectoryTree::State::FocusedHovered;
			if (state == L"State::Disabled")
				return CDirectoryTree::State::Disabled;
			return CDirectoryTree::State::Normal;
		}

		StringArray CDirectoryTreePropertyList::FolderStateItems()
		{
			return StringArray{
				L"FolderState::Normal",
				L"FolderState::Hovered" };
		}

		CDirectoryTree::FolderState CDirectoryTreePropertyList::StringToFolderState(const String &state)
		{
			if (state == L"FolderState::Hovered")
				return CDirectoryTree::FolderState::Hovered;
			return CDirectoryTree::FolderState::Normal;
		}
	}
}