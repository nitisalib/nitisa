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
		CTrackBarPropertyList::CTrackBarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
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
				[](IClass *parent) {return cast<CTrackBar*>(parent)->getMin(); },
				[](IClass *parent, const int value) {return cast<CTrackBar*>(parent)->setMin(value); }));
			Add(new CPropertyInteger(this, control, L"Max", false, nullptr,
				[](IClass *parent) {return cast<CTrackBar*>(parent)->getMax(); },
				[](IClass *parent, const int value) {return cast<CTrackBar*>(parent)->setMax(value); }));
			Add(new CPropertyInteger(this, control, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CTrackBar*>(parent)->getValue(); },
				[](IClass *parent, const int value) {return cast<CTrackBar*>(parent)->setValue(value); }));
			Add(new CPropertyEnum(this, control, L"TrackerStyle", false, TrackerStyleItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return TrackerStyleToString(cast<CTrackBar*>(parent)->getTrackerStyle()); },
				[](IClass *parent, const String value) {return cast<CTrackBar*>(parent)->setTrackerStyle(StringToTrackerStyle(value)); }));
			Add(new CPropertyRectFState(this, control, L"BackPadding", false, TrackerStyleItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBackPadding(StringToTrackerStyle(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackBar*>(parent)->setBackPadding(StringToTrackerStyle(state), value); }))
				->setMin(0);
			Add(new CPropertyFloatState(this, control, L"BackMargin", false, TrackerStyleItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBackMargin(StringToTrackerStyle(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CTrackBar*>(parent)->setBackMargin(StringToTrackerStyle(state), value); }))
				->setMin(0);
			Add(new CPropertyPointFState(this, control, L"TickSize", false, TrackerStyleItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getTickSize(StringToTrackerStyle(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CTrackBar*>(parent)->setTickSize(StringToTrackerStyle(state), value); }))
				->setMin(0);
			Add(new CPropertyPointFState(this, control, L"BigTickSize", false, TrackerStyleItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBigTickSize(StringToTrackerStyle(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CTrackBar*>(parent)->setBigTickSize(StringToTrackerStyle(state), value); }))
				->setMin(0);
			Add(new CPropertyPointFState(this, control, L"TrackerPadding", false, TrackerStyleItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getTrackerPadding(StringToTrackerStyle(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CTrackBar*>(parent)->setTrackerPadding(StringToTrackerStyle(state), value); }))
				->setMin(0);
			Add(new CPropertyFloatState(this, control, L"TrackerWidth", false, TrackerStyleItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getTrackerWidth(StringToTrackerStyle(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CTrackBar*>(parent)->setTrackerWidth(StringToTrackerStyle(state), value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"TickInterval", false, nullptr,
				[](IClass *parent) {return cast<CTrackBar*>(parent)->getTickInterval(); },
				[](IClass *parent, const int value) {return cast<CTrackBar*>(parent)->setTickInterval(value); }));
			Add(new CPropertyInteger(this, control, L"BigTickInterval", false, nullptr,
				[](IClass *parent) {return cast<CTrackBar*>(parent)->getBigTickInterval(); },
				[](IClass *parent, const int value) {return cast<CTrackBar*>(parent)->setBigTickInterval(value); }));
			Add(new CPropertyRectFState(this, control, L"BorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackBar*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackBar*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTrackBar*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackBar*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CTrackBar*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CTrackBar*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackBar*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"BackBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBackBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackBar*>(parent)->setBackBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"BackBorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBackBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackBar*>(parent)->setBackBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BackBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBackBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTrackBar*>(parent)->setBackBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBackBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackBar*>(parent)->setBackBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBackBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"TrackerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getTrackerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackBar*>(parent)->setTrackerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"TrackerBorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getTrackerBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTrackBar*>(parent)->setTrackerBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"TrackerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getTrackerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTrackBar*>(parent)->setTrackerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"TrackerBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getTrackerBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackBar*>(parent)->setTrackerBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"TrackerBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getTrackerBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"TickColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getTickColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackBar*>(parent)->setTickColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BigTickColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getBigTickColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackBar*>(parent)->setBigTickColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"OutlineColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getOutlineColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTrackBar*>(parent)->setOutlineColor(StringToState(state), value); }));
			Add(new CPropertyMaskState(this, control, L"OutlineMask", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTrackBar*>(parent)->getOutlineMask(StringToState(state)); },
				[](IClass *parent, const String &state, const unsigned int value) {return cast<CTrackBar*>(parent)->setOutlineMask(StringToState(state), value); }));
		}

		StringArray CTrackBarPropertyList::StateItems()
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

		CTrackBar::State CTrackBarPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CTrackBar::State::Hovered;
			if (state == L"State::Focused")
				return CTrackBar::State::Focused;
			if (state == L"State::FocusedHovered")
				return CTrackBar::State::FocusedHovered;
			if (state == L"State::Active")
				return CTrackBar::State::Active;
			if (state == L"State::ActiveHovered")
				return CTrackBar::State::ActiveHovered;
			if (state == L"State::Disabled")
				return CTrackBar::State::Disabled;
			return CTrackBar::State::Normal;
		}

		StringArray CTrackBarPropertyList::TrackerStyleItems()
		{
			return StringArray{
				L"TrackerStyle::Down",
				L"TrackerStyle::Up",
				L"TrackerStyle::Both" };
		}

		CTrackBar::TrackerStyle CTrackBarPropertyList::StringToTrackerStyle(const String &state)
		{
			if (state == L"TrackerStyle::Down")
				return CTrackBar::TrackerStyle::Down;
			if (state == L"TrackerStyle::Up")
				return CTrackBar::TrackerStyle::Up;
			return CTrackBar::TrackerStyle::Both;
		}

		String CTrackBarPropertyList::TrackerStyleToString(const CTrackBar::TrackerStyle style)
		{
			switch (style)
			{
			case CTrackBar::TrackerStyle::Down:	return L"TrackerStyle::Down";
			case CTrackBar::TrackerStyle::Up:	return L"TrackerStyle::Up";
			default:							return L"TrackerStyle::Both";
			}
		}
	}
}