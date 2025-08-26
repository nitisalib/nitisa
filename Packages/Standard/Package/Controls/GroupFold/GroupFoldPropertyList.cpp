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
		CGroupFoldPropertyList::CGroupFoldPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");

			Add(new CPropertyBool(this, control, L"Folded", false, nullptr,
				[](IClass *parent) {return cast<CGroupFold*>(parent)->isFolded(); },
				[](IClass *parent, const bool value) {return cast<CGroupFold*>(parent)->setFolded(value); }));
			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CGroupFold*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CGroupFold*>(parent)->setCaption(value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CGroupFold*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CGroupFold*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CGroupFold*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"BorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CGroupFold*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CGroupFold*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CGroupFold*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CGroupFold*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"CaptionColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getCaptionColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CGroupFold*>(parent)->setCaptionColor(StringToState(state), value); }));
			Add(new CPropertyFloatState(this, control, L"CaptionMargin", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getCaptionMargin(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CGroupFold*>(parent)->setCaptionMargin(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyPointFState(this, control, L"CaptionPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getCaptionPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CGroupFold*>(parent)->setCaptionPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"CaptionBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getCaptionBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CGroupFold*>(parent)->setCaptionBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"CaptionBorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getCaptionBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CGroupFold*>(parent)->setCaptionBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"CaptionBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getCaptionBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CGroupFold*>(parent)->setCaptionBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"CaptionBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getCaptionBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CGroupFold*>(parent)->setCaptionBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"CaptionBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getCaptionBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyFloatState(this, control, L"PlusSize", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getPlusSize(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CGroupFold*>(parent)->setPlusSize(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyFloatState(this, control, L"PlusPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getPlusPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CGroupFold*>(parent)->setPlusPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"Padding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGroupFold*>(parent)->getPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CGroupFold*>(parent)->setPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBool(this, control, L"UseMask", false, nullptr,
				[](IClass *parent) {return cast<CGroupFold*>(parent)->isUseMask(); },
				[](IClass *parent, const bool value) {return cast<CGroupFold*>(parent)->setUseMask(value); }));
		}

		StringArray CGroupFoldPropertyList::StateItems()
		{
			return StringArray{
				L"State::FoldedNormal",
				L"State::FoldedHovered",
				L"State::FoldedDisabled",
				L"State::Normal",
				L"State::Hovered",
				L"State::Disabled" };
		}

		CGroupFold::State CGroupFoldPropertyList::StringToState(const String &state)
		{
			if (state == L"State::FoldedNormal")
				return CGroupFold::State::FoldedNormal;
			if (state == L"State::FoldedHovered")
				return CGroupFold::State::FoldedHovered;
			if (state == L"State::FoldedDisabled")
				return CGroupFold::State::FoldedDisabled;
			if (state == L"State::Normal")
				return CGroupFold::State::Normal;
			if (state == L"State::Hovered")
				return CGroupFold::State::Hovered;
			return CGroupFold::State::Disabled;
		}
	}
}