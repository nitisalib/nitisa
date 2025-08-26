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
		CEditPropertyList::CEditPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyString(this, control, L"Text", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getText(); },
				[](IClass *parent, const String value) {return cast<CEdit*>(parent)->setText(value); }))
				->setChanged(true);
			Add(new CPropertyPoint(this, control, L"Selection", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getSelection(); },
				[](IClass *parent, const Point value) {return cast<CEdit*>(parent)->setSelection(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"CaretPosition", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getCaretPosition(); },
				[](IClass *parent, const int value) {return cast<CEdit*>(parent)->setCaretPosition(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"MaxLength", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getMaxLength(); },
				[](IClass *parent, const int value) {return cast<CEdit*>(parent)->setMaxLength(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"UndoLimitCount", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getUndoLimitCount(); },
				[](IClass *parent, const int value) {return cast<CEdit*>(parent)->setUndoLimitCount(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"UndoLimitSize", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getUndoLimitSize(); },
				[](IClass *parent, const int value) {return cast<CEdit*>(parent)->setUndoLimitSize(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"TextAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CEdit*>(parent)->getTextAlign()); },
				[](IClass *parent, const String value) {return cast<CEdit*>(parent)->setTextAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyBool(this, control, L"ReadOnly", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isReadOnly(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setReadOnly(value); }));
			Add(new CPropertyBool(this, control, L"Replacing", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isReplacing(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setReplacing(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CEdit*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyBool(this, control, L"CopyByMouseEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isCopyByMouseEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setCopyByMouseEnabled(value); }));
			Add(new CPropertyBool(this, control, L"MoveByMouseEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isMoveByMouseEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setMoveByMouseEnabled(value); }));
			Add(new CPropertyBool(this, control, L"SelectWordByDoubleClickEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isSelectWordByDoubleClickEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setSelectWordByDoubleClickEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyLeftEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isKeyLeftEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setKeyLeftEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyRightEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isKeyRightEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setKeyRightEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyHomeEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isKeyHomeEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setKeyHomeEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyEndEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isKeyEndEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setKeyEndEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyDeleteEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isKeyDeleteEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setKeyDeleteEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyBackspaceEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isKeyBackspaceEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setKeyBackspaceEnabled(value); }));
			Add(new CPropertyBool(this, control, L"SelectAllByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isSelectAllByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setSelectAllByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"PasteBuKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isPasteByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setPasteByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"CopyByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isCopyByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setCopyByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"CutByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isCutByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setCutByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"HistoryByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isHistoryByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setHistoryByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"InsertReplaceChangeByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->isInsertReplaceChangeByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CEdit*>(parent)->setInsertReplaceChangeByKeyEnabled(value); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CEdit*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CEdit*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CEdit*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyString(this, control, L"Placeholder", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getPlaceholder(); },
				[](IClass *parent, const String value) {return cast<CEdit*>(parent)->setPlaceholder(value); }));
			Add(new CPropertyColorState(this, control, L"TextColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getTextColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CEdit*>(parent)->setTextColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"PlaceholderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getPlaceholderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CEdit*>(parent)->setPlaceholderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"TextShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getTextShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CEdit*>(parent)->setTextShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"SelectionBackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getSelectionBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CEdit*>(parent)->setSelectionBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"SelectionTextColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getSelectionTextColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CEdit*>(parent)->setSelectionTextColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"SelectionTextShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getSelectionTextShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CEdit*>(parent)->setSelectionTextShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			Add(new CPropertyPointFState(this, control, L"TextShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getTextShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CEdit*>(parent)->setTextShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			CPropertyIntegerState *pis{ new CPropertyIntegerState(this, control, L"TextShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getTextShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CEdit*>(parent)->setTextShadowRadius(StringToState(state), value); }) };
			pis->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CEdit*>(parent)->setBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CEdit*>(parent)->setBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			pis = new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CEdit*>(parent)->setShadowRadius(StringToState(state), value); });
			pis->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CEdit*>(parent)->setShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CEdit*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CEdit*>(parent)->setShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h");
			Add(new CPropertyFloat(this, control, L"Scroll", false, nullptr,
				[](IClass *parent) {return cast<CEdit*>(parent)->getScroll(); },
				[](IClass *parent, const float value) {return cast<CEdit*>(parent)->setScroll(value); }))
				->setMin(0);
		}

		StringArray CEditPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CBuiltInTextInput::State CEditPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CBuiltInTextInput::State::Hovered;
			if (state == L"State::Focused")
				return CBuiltInTextInput::State::Focused;
			if (state == L"State::FocusedHovered")
				return CBuiltInTextInput::State::FocusedHovered;
			if (state == L"State::Disabled")
				return CBuiltInTextInput::State::Disabled;
			return CBuiltInTextInput::State::Normal;
		}
	}
}