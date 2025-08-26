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
		CFormStyleSolidPropertyList::CFormStyleSolidPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Align");
			Delete(L"Transform");
			Delete(L"TransformControls");
			Delete(L"Constraints");
			Delete(L"Size");
			Delete(L"Cursor");
			Delete(L"TabOrder");
			Delete(L"HintText");
			Delete(L"HintDelay");
			Delete(L"HintShift");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Visible");
			Delete(L"Enabled");
			Delete(L"ShowHint");
			Delete(L"UseParentShowHint");
			Delete(L"UseParentHintDelay");
			Delete(L"UseParentHintShift");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyBool(this, control, L"ShowCaption", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->isShowCaption(); },
				[](IClass *parent, const bool value) {return cast<CFormStyleSolid*>(parent)->setShowCaption(value); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CFormStyleSolid*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"CaptionHeight", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->getCaptionHeight(); },
				[](IClass *parent, const float value) {return cast<CFormStyleSolid*>(parent)->setCaptionHeight(value); }))
				->setMin(0);
			Add(new CPropertyPointF(this, control, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const PointF value) {return cast<CFormStyleSolid*>(parent)->setCaptionPadding(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"BorderColor", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->getBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CFormStyleSolid*>(parent)->setBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"CaptionBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->getCaptionBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CFormStyleSolid*>(parent)->setCaptionBackgroundColor(value); }));
			Add(new CPropertyEnum(this, control, L"CaptionAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CFormStyleSolid*>(parent)->getCaptionAlign()); },
				[](IClass *parent, const String value) {return cast<CFormStyleSolid*>(parent)->setCaptionAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");

			Add(new CPropertyBool(this, control, L"BtnMinimizeVisible", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->isBtnMinimizeVisible(); },
				[](IClass *parent, const bool value) {return cast<CFormStyleSolid*>(parent)->setBtnMinimizeVisible(value); }));
			Add(new CPropertyBool(this, control, L"BtnMinimizeEnabled", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->isBtnMinimizeEnabled(); },
				[](IClass *parent, const bool value) {return cast<CFormStyleSolid*>(parent)->setBtnMinimizeEnabled(value); }));
			Add(new CPropertyRectFState(this, control, L"BtnMinimizeBorderWidth", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormStyleSolid*>(parent)->getBtnMinimizeBorderWidth(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CFormStyleSolid*>(parent)->setBtnMinimizeBorderWidth(StringToButtonState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BtnMinimizeBorderColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormStyleSolid*>(parent)->getBtnMinimizeBorderColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CFormStyleSolid*>(parent)->setBtnMinimizeBorderColor(StringToButtonState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BtnMinimizeBackgroundColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormStyleSolid*>(parent)->getBtnMinimizeBackgroundColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFormStyleSolid*>(parent)->setBtnMinimizeBackgroundColor(StringToButtonState(state), value); }));

			Add(new CPropertyBool(this, control, L"BtnRestoreVisible", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->isBtnRestoreVisible(); },
				[](IClass *parent, const bool value) {return cast<CFormStyleSolid*>(parent)->setBtnRestoreVisible(value); }));
			Add(new CPropertyBool(this, control, L"BtnRestoreEnabled", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->isBtnRestoreEnabled(); },
				[](IClass *parent, const bool value) {return cast<CFormStyleSolid*>(parent)->setBtnRestoreEnabled(value); }));
			Add(new CPropertyRectFState(this, control, L"BtnRestoreBorderWidth", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormStyleSolid*>(parent)->getBtnRestoreBorderWidth(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CFormStyleSolid*>(parent)->setBtnRestoreBorderWidth(StringToButtonState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BtnRestoreBorderColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormStyleSolid*>(parent)->getBtnRestoreBorderColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CFormStyleSolid*>(parent)->setBtnRestoreBorderColor(StringToButtonState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BtnRestoreBackgroundColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormStyleSolid*>(parent)->getBtnRestoreBackgroundColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFormStyleSolid*>(parent)->setBtnRestoreBackgroundColor(StringToButtonState(state), value); }));

			Add(new CPropertyBool(this, control, L"BtnCloseVisible", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->isBtnCloseVisible(); },
				[](IClass *parent, const bool value) {return cast<CFormStyleSolid*>(parent)->setBtnCloseVisible(value); }));
			Add(new CPropertyBool(this, control, L"BtnCloseEnabled", false, nullptr,
				[](IClass *parent) {return cast<CFormStyleSolid*>(parent)->isBtnCloseEnabled(); },
				[](IClass *parent, const bool value) {return cast<CFormStyleSolid*>(parent)->setBtnCloseEnabled(value); }));
			Add(new CPropertyRectFState(this, control, L"BtnCloseBorderWidth", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormStyleSolid*>(parent)->getBtnCloseBorderWidth(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CFormStyleSolid*>(parent)->setBtnCloseBorderWidth(StringToButtonState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BtnCloseBorderColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormStyleSolid*>(parent)->getBtnCloseBorderColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CFormStyleSolid*>(parent)->setBtnCloseBorderColor(StringToButtonState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BtnCloseBackgroundColor", false, ButtonStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormStyleSolid*>(parent)->getBtnCloseBackgroundColor(StringToButtonState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CFormStyleSolid*>(parent)->setBtnCloseBackgroundColor(StringToButtonState(state), value); }));
		}

		StringArray CFormStyleSolidPropertyList::ButtonStateItems()
		{
			return StringArray{
				L"ButtonState::Normal",
				L"ButtonState::Hovered",
				L"ButtonState::Active",
				L"ButtonState::Disabled" };
		}

		CFormStyleSolid::ButtonState CFormStyleSolidPropertyList::StringToButtonState(const String &state)
		{
			if (state == L"ButtonState::Hovered")
				return CFormStyleSolid::ButtonState::Hovered;
			if (state == L"ButtonState::Active")
				return CFormStyleSolid::ButtonState::Active;
			if (state == L"ButtonState::Disabled")
				return CFormStyleSolid::ButtonState::Disabled;
			return CFormStyleSolid::ButtonState::Normal;
		}
	}
}