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
		CMaskEditPropertyList::CMaskEditPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyString(this, control, L"Text", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getText(); },
				[](IClass *parent, const String value) {return cast<CMaskEdit*>(parent)->setText(value); }))
				->setChanged(true);
			Add(new CPropertyString(this, control, L"Mask", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getMask(); },
				[](IClass *parent, const String value) {return cast<CMaskEdit*>(parent)->setMask(value); }));
			Add(new CPropertyPoint(this, control, L"Selection", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getSelection(); },
				[](IClass *parent, const Point value) {return cast<CMaskEdit*>(parent)->setSelection(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"CaretPosition", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getCaretPosition(); },
				[](IClass *parent, const int value) {return cast<CMaskEdit*>(parent)->setCaretPosition(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"MaxLength", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getMaxLength(); },
				[](IClass *parent, const int value) {return cast<CMaskEdit*>(parent)->setMaxLength(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"TextAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CMaskEdit*>(parent)->getTextAlign()); },
				[](IClass *parent, const String value) {return cast<CMaskEdit*>(parent)->setTextAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyBool(this, control, L"ReadOnly", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isReadOnly(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setReadOnly(value); }));
			Add(new CPropertyBool(this, control, L"Replacing", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isReplacing(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setReplacing(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CMaskEdit*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyBool(this, control, L"CopyByMouseEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isCopyByMouseEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setCopyByMouseEnabled(value); }));
			Add(new CPropertyBool(this, control, L"MoveByMouseEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isMoveByMouseEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setMoveByMouseEnabled(value); }));
			Add(new CPropertyBool(this, control, L"SelectWordByDoubleClickEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isSelectWordByDoubleClickEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setSelectWordByDoubleClickEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyLeftEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isKeyLeftEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setKeyLeftEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyRightEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isKeyRightEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setKeyRightEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyHomeEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isKeyHomeEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setKeyHomeEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyEndEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isKeyEndEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setKeyEndEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyDeleteEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isKeyDeleteEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setKeyDeleteEnabled(value); }));
			Add(new CPropertyBool(this, control, L"KeyBackspaceEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isKeyBackspaceEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setKeyBackspaceEnabled(value); }));
			Add(new CPropertyBool(this, control, L"SelectAllByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isSelectAllByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setSelectAllByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"PasteBuKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isPasteByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setPasteByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"CopyByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isCopyByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setCopyByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"CutByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isCutByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setCutByKeyEnabled(value); }));
			Add(new CPropertyBool(this, control, L"InsertReplaceChangeByKeyEnabled", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->isInsertReplaceChangeByKeyEnabled(); },
				[](IClass *parent, const bool value) {return cast<CMaskEdit*>(parent)->setInsertReplaceChangeByKeyEnabled(value); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CMaskEdit*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CMaskEdit*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CMaskEdit*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyString(this, control, L"Placeholder", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getPlaceholder(); },
				[](IClass *parent, const String value) {return cast<CMaskEdit*>(parent)->setPlaceholder(value); }));
			Add(new CPropertyColorState(this, control, L"TextColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getTextColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMaskEdit*>(parent)->setTextColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"PlaceholderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getPlaceholderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMaskEdit*>(parent)->setPlaceholderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"TextShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getTextShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMaskEdit*>(parent)->setTextShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"SelectionBackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getSelectionBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMaskEdit*>(parent)->setSelectionBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"SelectionTextColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getSelectionTextColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMaskEdit*>(parent)->setSelectionTextColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"SelectionTextShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getSelectionTextShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMaskEdit*>(parent)->setSelectionTextShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			Add(new CPropertyPointFState(this, control, L"TextShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getTextShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CMaskEdit*>(parent)->setTextShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			CPropertyIntegerState *pis{ new CPropertyIntegerState(this, control, L"TextShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getTextShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CMaskEdit*>(parent)->setTextShadowRadius(StringToState(state), value); }) };
			pis->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMaskEdit*>(parent)->setBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMaskEdit*>(parent)->setBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			pis = new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CMaskEdit*>(parent)->setShadowRadius(StringToState(state), value); });
			pis->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CMaskEdit*>(parent)->setShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInTextInput::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMaskEdit*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMaskEdit*>(parent)->setShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/TextInput/BuiltInTextInput.h");
			Add(new CPropertyFloat(this, control, L"Scroll", false, nullptr,
				[](IClass *parent) {return cast<CMaskEdit*>(parent)->getScroll(); },
				[](IClass *parent, const float value) {return cast<CMaskEdit*>(parent)->setScroll(value); }))
				->setMin(0);
		}

		StringArray CMaskEditPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CBuiltInTextInput::State CMaskEditPropertyList::StringToState(const String &state)
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