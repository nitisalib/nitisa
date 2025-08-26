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
		CFileListPropertyList::CFileListPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyString(this, control, L"Directory", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->getDirectory(); },
				[](IClass *parent, const String value) {return cast<CFileList*>(parent)->setDirectory(value); }));
			Add(new CPropertyString(this, control, L"Filter", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->getFilter(); },
				[](IClass *parent, const String value) {return cast<CFileList*>(parent)->setFilter(value); }));
			Add(new CPropertyBool(this, control, L"ShowArchieved", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->isShowArchieved(); },
				[](IClass *parent, const bool value) {return cast<CFileList*>(parent)->setShowArchieved(value); }));
			Add(new CPropertyBool(this, control, L"ShowCompressed", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->isShowCompressed(); },
				[](IClass *parent, const bool value) {return cast<CFileList*>(parent)->setShowCompressed(value); }));
			Add(new CPropertyBool(this, control, L"ShowEncrypted", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->isShowEncrypted(); },
				[](IClass *parent, const bool value) {return cast<CFileList*>(parent)->setShowEncrypted(value); }));
			Add(new CPropertyBool(this, control, L"ShowHidden", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->isShowHidden(); },
				[](IClass *parent, const bool value) {return cast<CFileList*>(parent)->setShowHidden(value); }));
			Add(new CPropertyBool(this, control, L"ShowNormal", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->isShowNormal(); },
				[](IClass *parent, const bool value) {return cast<CFileList*>(parent)->setShowNormal(value); }));
			Add(new CPropertyBool(this, control, L"ShowOffline", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->isShowOffline(); },
				[](IClass *parent, const bool value) {return cast<CFileList*>(parent)->setShowOffline(value); }));
			Add(new CPropertyBool(this, control, L"ShowReadOnly", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->isShowReadOnly(); },
				[](IClass *parent, const bool value) {return cast<CFileList*>(parent)->setShowReadOnly(value); }));
			Add(new CPropertyBool(this, control, L"ShowSystem", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->isShowSystem(); },
				[](IClass *parent, const bool value) {return cast<CFileList*>(parent)->setShowSystem(value); }));
			Add(new CPropertyBool(this, control, L"ShowTemporary", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->isShowTemporary(); },
				[](IClass *parent, const bool value) {return cast<CFileList*>(parent)->setShowTemporary(value); }));
			Add(new CPropertyInteger(this, control, L"ActiveIndex", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->getActiveIndex(); },
				[](IClass *parent, const int value) {return cast<CFileList*>(parent)->setActiveIndex(value); }));
			Add(new CPropertyFloat(this, control, L"SearchResetInterval", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->getSearchResetInterval(); },
				[](IClass *parent, const float value) {return cast<CFileList*>(parent)->setSearchResetInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"Columns", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->getColumns(); },
				[](IClass *parent, const int value) {return cast<CFileList*>(parent)->setColumns(value); }))
				->setMin(1);
			Add(new CPropertyBool(this, control, L"Multiselect", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->isMultiselect(); },
				[](IClass *parent, const bool value) {return cast<CFileList*>(parent)->setMultiselect(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CFileList*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CFileList*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CFileList*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CFileList*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CFileList*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"HorizontalScrollBar", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CFileList*>(parent)->getHorizontalScrollBar()); },
				[](IClass *parent, const String value) {return cast<CFileList*>(parent)->setHorizontalScrollBar(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyEnum(this, control, L"VerticalScrollBar", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CFileList*>(parent)->getVerticalScrollBar()); },
				[](IClass *parent, const String value) {return cast<CFileList*>(parent)->setVerticalScrollBar(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFileList*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFileList*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFileList*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CFileList*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFileList*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CFileList*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFileList*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CFileList*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFileList*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFileList*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFileList*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"CornerColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFileList*>(parent)->getCornerColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFileList*>(parent)->setCornerColor(StringToState(state), value); }));
		}

		StringArray CFileListPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CFileList::State CFileListPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CFileList::State::Hovered;
			if (state == L"State::Focused")
				return CFileList::State::Focused;
			if (state == L"State::FocusedHovered")
				return CFileList::State::FocusedHovered;
			if (state == L"State::Disabled")
				return CFileList::State::Disabled;
			return CFileList::State::Normal;
		}
	}
}