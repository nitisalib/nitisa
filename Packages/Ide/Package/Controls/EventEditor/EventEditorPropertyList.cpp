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
		CEventEditorPropertyList::CEventEditorPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Cursor");
			Delete(L"TransformControls");
			Delete(L"Enabled");

			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CEventEditor*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) { return cast<CEventEditor*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"BorderColor", false, nullptr,
				[](IClass *parent) {return cast<CEventEditor*>(parent)->getBorderColor(); },
				[](IClass *parent, const BorderColor value) { return cast<CEventEditor*>(parent)->setBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CEventEditor*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) { return cast<CEventEditor*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CEventEditor*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyFloat(this, control, L"CaptionWidth", false, nullptr,
				[](IClass *parent) {return cast<CEventEditor*>(parent)->getCaptionWidth(); },
				[](IClass *parent, const float value) { return cast<CEventEditor*>(parent)->setCaptionWidth(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyFloat(this, control, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CEventEditor*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const float value) { return cast<CEventEditor*>(parent)->setCaptionPadding(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"CaptionColor", false, EventStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CEventEditor*>(parent)->getCaptionColor(StringToEventState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CEventEditor*>(parent)->setCaptionColor(StringToEventState(state), value); }));
			Add(new CPropertyFloatState(this, control, L"CaptionBorderWidth", false, EventStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CEventEditor*>(parent)->getCaptionBorderWidth(StringToEventState(state)); },
				[](IClass *parent, const String &state, const float value) { return cast<CEventEditor*>(parent)->setCaptionBorderWidth(StringToEventState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"CaptionBorderColor", false, EventStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CEventEditor*>(parent)->getCaptionBorderColor(StringToEventState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CEventEditor*>(parent)->setCaptionBorderColor(StringToEventState(state), value); }));
			Add(new CPropertyColorState(this, control, L"CaptionBackgroundColor", false, EventStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CEventEditor*>(parent)->getCaptionBackgroundColor(StringToEventState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CEventEditor*>(parent)->setCaptionBackgroundColor(StringToEventState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"CaptionBackgroundGradient", EventStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CEventEditor*>(parent)->getCaptionBackgroundGradient(StringToEventState(state)); }));
			Add(new CPropertyFloat(this, control, L"CaptionSeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CEventEditor*>(parent)->getCaptionSeparatorWidth(); },
				[](IClass *parent, const float value) { return cast<CEventEditor*>(parent)->setCaptionSeparatorWidth(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"CaptionSeparatorColor", false, nullptr,
				[](IClass *parent) {return cast<CEventEditor*>(parent)->getCaptionSeparatorColor(); },
				[](IClass *parent, const Color value) { return cast<CEventEditor*>(parent)->setCaptionSeparatorColor(value); }));
			Add(new CPropertyGradient(this, control, L"CaptionSeparatorGradient", nullptr,
				[](IClass *parent) {return cast<CEventEditor*>(parent)->getCaptionSeparatorGradient(); }));
		}

		StringArray CEventEditorPropertyList::EventStates()
		{
			return StringArray{
				L"EventState::Normal",
				L"EventState::Hovered",
				L"EventState::Focused" };
		}

		CEventEditor::EventState CEventEditorPropertyList::StringToEventState(const String &state)
		{
			if (state == L"EventState::Hovered")
				return CEventEditor::EventState::Hovered;
			if (state == L"EventState::Focused")
				return CEventEditor::EventState::Focused;
			return CEventEditor::EventState::Normal;
		}
	}
}