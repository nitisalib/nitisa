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
		CTrackRangePropertyList::CTrackRangePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"UseParentFont");

			Add(new CPropertyInteger(this, control, L"Min", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getMin(); },
				[](IClass *parent, const int value) {return cast<CTrackRange*>(parent)->setMin(value); }));
			Add(new CPropertyInteger(this, control, L"Max", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getMax(); },
				[](IClass *parent, const int value) {return cast<CTrackRange*>(parent)->setMax(value); }));
			Add(new CPropertyPoint(this, control, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getValue(); },
				[](IClass *parent, const Point value) {return cast<CTrackRange*>(parent)->setValue(value); }));
			Add(new CPropertyPointB(this, control, L"TrackerEnabled", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getTrackerEnabled(); },
				[](IClass *parent, const PointB value) {return cast<CTrackRange*>(parent)->setTrackerEnabled(value); }));
			Add(new CPropertyPointB(this, control, L"TrackerVisible", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getTrackerVisible(); },
				[](IClass *parent, const PointB value) {return cast<CTrackRange*>(parent)->setTrackerVisible(value); }));
			Add(new CPropertyRectF(this, control, L"BackPadding", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getBackPadding(); },
				[](IClass *parent, const RectF value) {return cast<CTrackRange*>(parent)->setBackPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"BackMargin", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getBackMargin(); },
				[](IClass *parent, const float value) {return cast<CTrackRange*>(parent)->setBackMargin(value); }))
				->setMin(0);
			Add(new CPropertyPointF(this, control, L"TickSize", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getTickSize(); },
				[](IClass *parent, const PointF value) {return cast<CTrackRange*>(parent)->setTickSize(value); }))
				->setMin(0);
			Add(new CPropertyPointF(this, control, L"BigTickSize", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getBigTickSize(); },
				[](IClass *parent, const PointF value) {return cast<CTrackRange*>(parent)->setBigTickSize(value); }))
				->setMin(0);
			Add(new CPropertyPointF(this, control, L"TrackerPadding", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getTrackerPadding(); },
				[](IClass *parent, const PointF value) {return cast<CTrackRange*>(parent)->setTrackerPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"TrackerWidth", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getTrackerWidth(); },
				[](IClass *parent, const float value) {return cast<CTrackRange*>(parent)->setTrackerWidth(value); }))
				->setMin(0);
			Add(new CPropertyBool(this, control, L"TopTicksVisible", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->isTopTicksVisible(); },
				[](IClass *parent, const bool value) {return cast<CTrackRange*>(parent)->setTopTicksVisible(value); }));
			Add(new CPropertyBool(this, control, L"BottomTicksVisible", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->isBottomTicksVisible(); },
				[](IClass *parent, const bool value) {return cast<CTrackRange*>(parent)->setBottomTicksVisible(value); }));
			Add(new CPropertyInteger(this, control, L"TickInterval", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getTickInterval(); },
				[](IClass *parent, const int value) {return cast<CTrackRange*>(parent)->setTickInterval(value); }));
			Add(new CPropertyInteger(this, control, L"BigTickInterval", false, nullptr,
				[](IClass *parent) {return cast<CTrackRange*>(parent)->getBigTickInterval(); },
				[](IClass *parent, const int value) {return cast<CTrackRange*>(parent)->setBigTickInterval(value); }));
			Add(new CPropertyRectFState(this, control, L"BorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackRange*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackRange*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTrackRange*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackRange*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CTrackRange*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CTrackRange*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackRange*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"BackBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBackBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackRange*>(parent)->setBackBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"BackBorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBackBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackRange*>(parent)->setBackBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BackBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBackBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTrackRange*>(parent)->setBackBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBackBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackRange*>(parent)->setBackBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBackBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"BackSelectionBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBackSelectionBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackRange*>(parent)->setBackSelectionBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackSelectionBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBackSelectionBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"TrackerBorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getTrackerBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackRange*>(parent)->setTrackerBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"TrackerOuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getTrackerOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackRange*>(parent)->setTrackerOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"TrackerInnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getTrackerInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackRange*>(parent)->setTrackerInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"TrackerOuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getTrackerOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTrackRange*>(parent)->setTrackerOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"TrackerInnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getTrackerInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTrackRange*>(parent)->setTrackerInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"TrackerBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getTrackerBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackRange*>(parent)->setTrackerBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"TrackerBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getTrackerBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"TickColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getTickColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackRange*>(parent)->setTickColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BigTickColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getBigTickColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackRange*>(parent)->setBigTickColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"OutlineColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getOutlineColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackRange*>(parent)->setOutlineColor(StringToState(state), value); }));
			Add(new CPropertyMaskState(this, control, L"OutlineMask", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackRange*>(parent)->getOutlineMask(StringToState(state)); },
				[](IClass *parent, const String &state, const unsigned int value) {return cast<CTrackRange*>(parent)->setOutlineMask(StringToState(state), value); }));
		}

		StringArray CTrackRangePropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Active",
				L"State::ActiveHovered",
				L"State::Disabled" };
		}

		CTrackRange::State CTrackRangePropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CTrackRange::State::Hovered;
			if (state == L"State::Focused")
				return CTrackRange::State::Focused;
			if (state == L"State::FocusedHovered")
				return CTrackRange::State::FocusedHovered;
			if (state == L"State::Active")
				return CTrackRange::State::Active;
			if (state == L"State::ActiveHovered")
				return CTrackRange::State::ActiveHovered;
			if (state == L"State::Disabled")
				return CTrackRange::State::Disabled;
			return CTrackRange::State::Normal;
		}
	}
}