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
		CLabelPropertyList::CLabelPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Size");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyPointF(this, control, L"Size", false,
				[](IClass *parent) { return cast<CLabel*>(parent)->isAutoSize(); },
				[](IClass *parent) { return cast<CLabel*>(parent)->getSize(); },
				[](IClass *parent, const PointF value) { return cast<CLabel*>(parent)->setSize(value); }))
				->setMin(0);
			Add(new CPropertyText(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CLabel*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CLabel*>(parent)->setCaption(value); }))
				->setChanged(true);
			Add(new CPropertyEnum(this, control, L"CaptionHorizontalAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CLabel*>(parent)->getCaptionHorizontalAlign()); },
				[](IClass *parent, const String value) {return cast<CLabel*>(parent)->setCaptionHorizontalAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnum(this, control, L"CaptionVerticalAlign", false, VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return VerticalAlignToString(cast<CLabel*>(parent)->getCaptionVerticalAlign()); },
				[](IClass *parent, const String value) {return cast<CLabel*>(parent)->setCaptionVerticalAlign(StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyBool(this, control, L"Multiline", false, nullptr,
				[](IClass *parent) {return cast<CLabel*>(parent)->isMultiline(); },
				[](IClass *parent, const bool value) {return cast<CLabel*>(parent)->setMultiline(value); }));
			Add(new CPropertyBool(this, control, L"AutoSize", false, nullptr,
				[](IClass *parent) {return cast<CLabel*>(parent)->isAutoSize(); },
				[](IClass *parent, const bool value) {return cast<CLabel*>(parent)->setAutoSize(value); }));
			Add(new CPropertyColorState(this, control, L"Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CLabel*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CLabel*>(parent)->setColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CLabel*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CLabel*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CLabel*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CLabel*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CLabel*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CLabel*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);

			Add(new CPropertyString(this, control, L"Text", false,
				[](IClass *parent) { return true; },
				[](IClass *parent) { return cast<CLabel*>(parent)->getCaption(); },
				[](IClass *parent, const String value) { return cast<CLabel*>(parent)->setCaption(value); }));
		}

		StringArray CLabelPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Disabled" };
		}

		CLabel::State CLabelPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CLabel::State::Hovered;
			if (state == L"State::Disabled")
				return CLabel::State::Disabled;
			return CLabel::State::Normal;
		}
	}
}