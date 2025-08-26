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
		CMemoPropertyList::CMemoPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyText(this, control, L"Text", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->getText(); },
				[](IClass *parent, const String value) {return cast<CMemo*>(parent)->setText(value); }))
				->setChanged(true);
			Add(new CPropertyInteger(this, control, L"CaretPosition", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->getCaretPosition(); },
				[](IClass *parent, const int value) {return cast<CMemo*>(parent)->setCaretPosition(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"MaxLength", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->getMaxLength(); },
				[](IClass *parent, const int value) {return cast<CMemo*>(parent)->setMaxLength(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"UndoLimitCount", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->getUndoLimitCount(); },
				[](IClass *parent, const int value) {return cast<CMemo*>(parent)->setUndoLimitCount(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"UndoLimitSize", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->getUndoLimitSize(); },
				[](IClass *parent, const int value) {return cast<CMemo*>(parent)->setUndoLimitSize(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"TextAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CMemo*>(parent)->getTextAlign()); },
				[](IClass *parent, const String value) {return cast<CMemo*>(parent)->setTextAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyBool(this, control, L"WordWrap", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isWordWrap(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setWordWrap(value); }));
			Add(new CPropertyBool(this, control, L"WordBreak", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isWordBreak(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setWordBreak(value); }));
			Add(new CPropertyBool(this, control, L"ReadOnly", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isReadOnly(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setReadOnly(value); }));
			Add(new CPropertyBool(this, control, L"Replacing", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isReplacing(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setReplacing(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CMemo*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyColorState(this, control, L"TextColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getTextColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMemo*>(parent)->setTextColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			Add(new CPropertyColorState(this, control, L"TextShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getTextShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMemo*>(parent)->setTextShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			Add(new CPropertyColorState(this, control, L"SelectionBackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getSelectionBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMemo*>(parent)->setSelectionBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			Add(new CPropertyColorState(this, control, L"SelectionTextColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getSelectionTextColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMemo*>(parent)->setSelectionTextColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			Add(new CPropertyColorState(this, control, L"SelectionTextShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getSelectionTextShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMemo*>(parent)->setSelectionTextShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			Add(new CPropertyPointFState(this, control, L"TextShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getTextShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CMemo*>(parent)->setTextShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			CPropertyIntegerState *pis{ new CPropertyIntegerState(this, control, L"TextShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getTextShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CMemo*>(parent)->setTextShadowRadius(StringToState(state), value); }) };
			pis->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyBool(this, control, L"CopyByMouseEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isCopyByMouseEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setCopyByMouseEnabled(value); }));
			Add(new CPropertyBool(this, control, L"MoveByMouseEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isMoveByMouseEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setMoveByMouseEnabled(value); }));
			Add(new CPropertyBool(this, control, L"SelectWordByDoubleClickEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isSelectWordByDoubleClickEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setSelectWordByDoubleClickEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyLeftEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isKeyLeftEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setKeyLeftEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyRightEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isKeyRightEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setKeyRightEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyHomeEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isKeyHomeEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setKeyHomeEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyEndEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isKeyEndEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setKeyEndEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyDeleteEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isKeyDeleteEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setKeyDeleteEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyBackspaceEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isKeyBackspaceEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setKeyBackspaceEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyUpEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isKeyUpEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setKeyUpEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyDownEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isKeyDownEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setKeyDownEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyPageUpEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isKeyPageUpEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setKeyPageUpEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyPageDownEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isKeyPageDownEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setKeyPageDownEnabled(value); }));
			Add(new CPropertyBool(this, control, L"SelectAllByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isSelectAllByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setSelectAllByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"PasteByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isPasteByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setPasteByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"CopyByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isCopyByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setCopyByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"CutByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isCutByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setCutByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"HistoryByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isHistoryByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setHistoryByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"InsertReplaceChangeByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isInsertReplaceChangeByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setInsertReplaceChangeByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"WordWrapChangeByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->isWordWrapChangeByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMemo*>(parent)->setWordWrapChangeByKeyEnabled(value); }));
			Add(new CPropertyEnum(this, control, L"VerticalScrollType", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CMemo*>(parent)->getVerticalScrollType()); },
				[](IClass *parent, const String value) {return cast<CMemo*>(parent)->setVerticalScrollType(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyEnum(this, control, L"HorizontalScrollType", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CMemo*>(parent)->getHorizontalScrollType()); },
				[](IClass *parent, const String value) {return cast<CMemo*>(parent)->setHorizontalScrollType(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CMemo*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CMemo*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CMemo*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMemo*>(parent)->setBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMemo*>(parent)->setBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			pis = new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CMemo*>(parent)->setShadowRadius(StringToState(state), value); });
			pis->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CMemo*>(parent)->setShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMemo*>(parent)->setShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			Add(new CPropertyColorState(this, control, L"CornerColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextArea::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMemo*>(parent)->getCornerColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMemo*>(parent)->setCornerColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextArea/BuiltInTextArea.h");
			Add(new CPropertyPointF(this, control, L"Scroll", false, nullptr,
				[](IClass *parent) {return cast<CMemo*>(parent)->getScroll(); },
				[](IClass *parent, const PointF value) {return cast<CMemo*>(parent)->setScroll(value); }))
				->setMin(0);
		}

		StringArray CMemoPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CBuiltInTextArea::State CMemoPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CBuiltInTextArea::State::Hovered;
			if (state == L"State::Focused")
				return CBuiltInTextArea::State::Focused;
			if (state == L"State::FocusedHovered")
				return CBuiltInTextArea::State::FocusedHovered;
			if (state == L"State::Disabled")
				return CBuiltInTextArea::State::Disabled;
			return CBuiltInTextArea::State::Normal;
		}
	}
}