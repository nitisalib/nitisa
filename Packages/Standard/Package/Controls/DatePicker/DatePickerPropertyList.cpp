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
		CDatePickerPropertyList::CDatePickerPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyInteger(this, control, L"Year", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getYear(); },
				[](IClass *parent, const int value) {return cast<CDatePicker*>(parent)->setYear(value); }));
			Add(new CPropertyInteger(this, control, L"Month", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getMonth(); },
				[](IClass *parent, const int value) {return cast<CDatePicker*>(parent)->setMonth(value); }))
				->setMin(1)->setMax(12);
			Add(new CPropertyInteger(this, control, L"Day", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getDay(); },
				[](IClass *parent, const int value) {return cast<CDatePicker*>(parent)->setDay(value); }))
				->setMin(1)->setMax(31);
			Add(new CPropertyInteger(this, control, L"MinYear", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getMinYear(); },
				[](IClass *parent, const int value) {return cast<CDatePicker*>(parent)->setMinYear(value); }));
			Add(new CPropertyInteger(this, control, L"MinMonth", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getMinMonth(); },
				[](IClass *parent, const int value) {return cast<CDatePicker*>(parent)->setMinMonth(value); }))
				->setMin(1)->setMax(12);
			Add(new CPropertyInteger(this, control, L"MinDay", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getMinDay(); },
				[](IClass *parent, const int value) {return cast<CDatePicker*>(parent)->setMinDay(value); }))
				->setMin(1)->setMax(31);
			Add(new CPropertyInteger(this, control, L"MaxYear", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getMaxYear(); },
				[](IClass *parent, const int value) {return cast<CDatePicker*>(parent)->setMaxYear(value); }));
			Add(new CPropertyInteger(this, control, L"MaxMonth", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getMaxMonth(); },
				[](IClass *parent, const int value) {return cast<CDatePicker*>(parent)->setMaxMonth(value); }))
				->setMin(1)->setMax(12);
			Add(new CPropertyInteger(this, control, L"MaxDay", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getMaxDay(); },
				[](IClass *parent, const int value) {return cast<CDatePicker*>(parent)->setMaxDay(value); }))
				->setMin(1)->setMax(31);

			Add(new CPropertyEnum(this, control, L"CalendarMode", false, ModeItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return ModeToString(cast<CDatePicker*>(parent)->getCalendarMode()); },
				[](IClass *parent, const String value) {return cast<CDatePicker*>(parent)->setCalendarMode(StringToMode(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyBool(this, control, L"CalendarShowToday", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->isCalendarShowToday(); },
				[](IClass *parent, const bool value) {return cast<CDatePicker*>(parent)->setCalendarShowToday(value); }));
			Add(new CPropertyRectF(this, control, L"CalendarTitlePadding", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarTitlePadding(); },
				[](IClass *parent, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTitlePadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"CalendarTodayPadding", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarTodayPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTodayPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"CalendarElementPadding", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarElementPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarElementPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"CalendarDayPadding", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarDayPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarDayPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"CalendarTodayMargin", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarTodayMargin(); },
				[](IClass *parent, const float value) {return cast<CDatePicker*>(parent)->setCalendarTodayMargin(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"CalendarTodayRectWidth", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarTodayRectWidth(); },
				[](IClass *parent, const float value) {return cast<CDatePicker*>(parent)->setCalendarTodayRectWidth(value); }))
				->setMin(0);
			Add(new CPropertyBool(this, control, L"CalendarAnimate", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->isCalendarAnimate(); },
				[](IClass *parent, const bool value) {return cast<CDatePicker*>(parent)->setCalendarAnimate(value); }));
			Add(new CPropertyFloat(this, control, L"CalendarAnimateInterval", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarAnimateInterval(); },
				[](IClass *parent, const float value) {return cast<CDatePicker*>(parent)->setCalendarAnimateInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"CalendarAnimateMinScale", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarAnimateMinScale(); },
				[](IClass *parent, const float value) {return cast<CDatePicker*>(parent)->setCalendarAnimateMinScale(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyFloat(this, control, L"CalendarAnimateTime", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarAnimateTime(); },
				[](IClass *parent, const float value) {return cast<CDatePicker*>(parent)->setCalendarAnimateTime(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"CalendarScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CDatePicker*>(parent)->setCalendarScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyEnumState(this, control, L"CalendarTitleAlign", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CDatePicker*>(parent)->getCalendarTitleAlign(StringToTitleState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CDatePicker*>(parent)->setCalendarTitleAlign(StringToTitleState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			CPropertyRectFState *rectf_state{ new CPropertyRectFState(this, control, L"CalendarTitleBorderRadius", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleBorderRadius(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTitleBorderRadius(StringToTitleState(state), value); }) };
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTitleBorderWidth", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleBorderWidth(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTitleBorderWidth(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			Add(new CPropertyBorderColorState(this, control, L"CalendarTitleBorderColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleBorderColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setCalendarTitleBorderColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTitleBackgroundColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleBackgroundColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTitleBackgroundColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"CalendarTitleBackgroundGradient", TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleBackgroundGradient(StringToTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTitleColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTitleColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTitlePrevRangeBorderRadius", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitlePrevRangeBorderRadius(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTitlePrevRangeBorderRadius(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTitlePrevRangeBorderWidth", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitlePrevRangeBorderWidth(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTitlePrevRangeBorderWidth(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			Add(new CPropertyBorderColorState(this, control, L"CalendarTitlePrevRangeBorderColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitlePrevRangeBorderColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setCalendarTitlePrevRangeBorderColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTitlePrevRangeBackgroundColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitlePrevRangeBackgroundColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTitlePrevRangeBackgroundColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"CalendarTitlePrevRangeBackgroundGradient", TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitlePrevRangeBackgroundGradient(StringToTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTitlePrevRangePadding", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitlePrevRangePadding(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTitlePrevRangePadding(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			Add(new CPropertyColorState(this, control, L"CalendarTitlePrevRangeColor1", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitlePrevRangeColor1(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTitlePrevRangeColor1(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTitlePrevRangeColor2", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitlePrevRangeColor2(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTitlePrevRangeColor2(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTitlePrevRangeColor3", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitlePrevRangeColor3(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTitlePrevRangeColor3(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTitleNextRangeBorderRadius", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleNextRangeBorderRadius(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTitleNextRangeBorderRadius(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTitleNextRangeBorderWidth", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleNextRangeBorderWidth(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTitleNextRangeBorderWidth(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			Add(new CPropertyBorderColorState(this, control, L"CalendarTitleNextRangeBorderColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleNextRangeBorderColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setCalendarTitleNextRangeBorderColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTitleNextRangeBackgroundColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleNextRangeBackgroundColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTitleNextRangeBackgroundColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"CalendarTitleNextRangeBackgroundGradient", TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleNextRangeBackgroundGradient(StringToTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTitleNextRangePadding", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleNextRangePadding(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTitleNextRangePadding(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			Add(new CPropertyColorState(this, control, L"CalendarTitleNextRangeColor1", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleNextRangeColor1(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTitleNextRangeColor1(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTitleNextRangeColor2", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleNextRangeColor2(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTitleNextRangeColor2(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTitleNextRangeColor3", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTitleNextRangeColor3(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTitleNextRangeColor3(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyEnumState(this, control, L"CalendarTodayAlign", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CDatePicker*>(parent)->getCalendarTodayAlign(StringToTitleState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CDatePicker*>(parent)->setCalendarTodayAlign(StringToTitleState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTodayBorderRadius", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayBorderRadius(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTodayBorderRadius(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTodayBorderWidth", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayBorderWidth(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTodayBorderWidth(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			Add(new CPropertyBorderColorState(this, control, L"CalendarTodayBorderColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayBorderColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setCalendarTodayBorderColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTodayBackgroundColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayBackgroundColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTodayBackgroundColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"CalendarTodayBackgroundGradient", TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayBackgroundGradient(StringToTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTodayColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTodayColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTodayRectBorderRadius", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayRectBorderRadius(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTodayRectBorderRadius(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			rectf_state = new CPropertyRectFState(this, control, L"CalendarTodayRectBorderWidth", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayRectBorderWidth(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarTodayRectBorderWidth(StringToTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			Add(new CPropertyBorderColorState(this, control, L"CalendarTodayRectBorderColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayRectBorderColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setCalendarTodayRectBorderColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarTodayRectBackgroundColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayRectBackgroundColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarTodayRectBackgroundColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"CalendarTodayRectBackgroundGradient", TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarTodayRectBackgroundGradient(StringToTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyEnumState(this, control, L"CalendarElementHorizontalAlign", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CDatePicker*>(parent)->getCalendarElementHorizontalAlign(StringToElementState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CDatePicker*>(parent)->setCalendarElementHorizontalAlign(StringToElementState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnumState(this, control, L"CalendarElementVerticalAlign", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return VerticalAlignToString(cast<CDatePicker*>(parent)->getCalendarElementVerticalAlign(StringToElementState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CDatePicker*>(parent)->setCalendarElementVerticalAlign(StringToElementState(state), StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			rectf_state = new CPropertyRectFState(this, control, L"CalendarElementBorderRadius", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarElementBorderRadius(StringToElementState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarElementBorderRadius(StringToElementState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			rectf_state = new CPropertyRectFState(this, control, L"CalendarElementBorderWidth", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarElementBorderWidth(StringToElementState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarElementBorderWidth(StringToElementState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			Add(new CPropertyBorderColorState(this, control, L"CalendarElementBorderColor", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarElementBorderColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setCalendarElementBorderColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarElementBackgroundColor", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarElementBackgroundColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarElementBackgroundColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"CalendarElementBackgroundGradient", ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarElementBackgroundGradient(StringToElementState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarElementColor", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarElementColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarElementColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarElementOutlineColor", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarElementOutlineColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarElementOutlineColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyMaskState(this, control, L"CalendarElementOutlineMask", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarElementOutlineMask(StringToElementState(state)); },
				[](IClass *parent, const String &state, const unsigned int value) {return cast<CDatePicker*>(parent)->setCalendarElementOutlineMask(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyEnumState(this, control, L"CalendarDayHorizontalAlign", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CDatePicker*>(parent)->getCalendarDayHorizontalAlign(StringToElementState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CDatePicker*>(parent)->setCalendarDayHorizontalAlign(StringToElementState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnumState(this, control, L"CalendarDayVerticalAlign", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return VerticalAlignToString(cast<CDatePicker*>(parent)->getCalendarDayVerticalAlign(StringToElementState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CDatePicker*>(parent)->setCalendarDayVerticalAlign(StringToElementState(state), StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyEnumState(this, control, L"CalendarDayTitleHorizontalAlign", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CDatePicker*>(parent)->getCalendarDayTitleHorizontalAlign(StringToDayTitleState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CDatePicker*>(parent)->setCalendarDayTitleHorizontalAlign(StringToDayTitleState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnumState(this, control, L"CalendarDayTitleVerticalAlign", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return VerticalAlignToString(cast<CDatePicker*>(parent)->getCalendarDayTitleVerticalAlign(StringToDayTitleState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CDatePicker*>(parent)->setCalendarDayTitleVerticalAlign(StringToDayTitleState(state), StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			rectf_state = new CPropertyRectFState(this, control, L"CalendarDayTitleBorderRadius", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarDayTitleBorderRadius(StringToDayTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarDayTitleBorderRadius(StringToDayTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			rectf_state = new CPropertyRectFState(this, control, L"CalendarDayTitleBorderWidth", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarDayTitleBorderWidth(StringToDayTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarDayTitleBorderWidth(StringToDayTitleState(state), value); });
			rectf_state->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			rectf_state->setMin(0);
			Add(rectf_state);
			Add(new CPropertyBorderColorState(this, control, L"CalendarDayTitleBorderColor", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarDayTitleBorderColor(StringToDayTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setCalendarDayTitleBorderColor(StringToDayTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarDayTitleBackgroundColor", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarDayTitleBackgroundColor(StringToDayTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarDayTitleBackgroundColor(StringToDayTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"CalendarDayTitleBackgroundGradient", DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarDayTitleBackgroundGradient(StringToDayTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"CalendarDayTitleColor", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getCalendarDayTitleColor(StringToDayTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setCalendarDayTitleColor(StringToDayTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h");

			Add(new CPropertyEnum(this, control, L"DisplayMode", false, DisplayModeItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return DisplayModeToString(cast<CDatePicker*>(parent)->getDisplayMode()); },
				[](IClass *parent, const String value) {return cast<CDatePicker*>(parent)->setDisplayMode(StringToDisplayMode(value)); }));
			Add(new CPropertyEnum(this, control, L"MonthFormat", false, MonthFormatItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return MonthFormatToString(cast<CDatePicker*>(parent)->getMonthFormat()); },
				[](IClass *parent, const String value) {return cast<CDatePicker*>(parent)->setMonthFormat(StringToMonthFormat(value)); }));
			Add(new CPropertyEnum(this, control, L"ElementOrder", false, ElementOrderItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return ElementOrderToString(cast<CDatePicker*>(parent)->getElementOrder()); },
				[](IClass *parent, const String value) {return cast<CDatePicker*>(parent)->setElementOrder(StringToElementOrder(value)); }));
			Add(new CPropertyEnum(this, control, L"OpenDirection", false, OpenDirectionItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return OpenDirectionToString(cast<CDatePicker*>(parent)->getOpenDirection()); },
				[](IClass *parent, const String value) {return cast<CDatePicker*>(parent)->setOpenDirection(StringToOpenDirection(value)); }));
			Add(new CPropertyEnum(this, control, L"OpenAlign", false, DisplayModeItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return OpenAlignToString(cast<CDatePicker*>(parent)->getOpenAlign()); },
				[](IClass *parent, const String value) {return cast<CDatePicker*>(parent)->setOpenAlign(StringToOpenAlign(value)); }));
			Add(new CPropertyString(this, control, L"Separator1", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getSeparator1(); },
				[](IClass *parent, const String value) {return cast<CDatePicker*>(parent)->setSeparator1(value); }));
			Add(new CPropertyString(this, control, L"Separator2", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getSeparator2(); },
				[](IClass *parent, const String value) {return cast<CDatePicker*>(parent)->setSeparator2(value); }));
			Add(new CPropertyBool(this, control, L"ShowDayLeadingZeros", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->isShowDayLeadingZeros(); },
				[](IClass *parent, const bool value) {return cast<CDatePicker*>(parent)->setShowDayLeadingZeros(value); }));
			Add(new CPropertyBool(this, control, L"ShowMonthLeadingZeros", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->isShowMonthLeadingZeros(); },
				[](IClass *parent, const bool value) {return cast<CDatePicker*>(parent)->setShowMonthLeadingZeros(value); }));
			Add(new CPropertyBool(this, control, L"ShowYearLeadingZeros", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->isShowYearLeadingZeros(); },
				[](IClass *parent, const bool value) {return cast<CDatePicker*>(parent)->setShowYearLeadingZeros(value); }));
			Add(new CPropertyBool(this, control, L"ShowIcon", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->isShowIcon(); },
				[](IClass *parent, const bool value) {return cast<CDatePicker*>(parent)->setShowIcon(value); }));
			Add(new CPropertyFloat(this, control, L"TimerInterval", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getTimerInterval(); },
				[](IClass *parent, const float value) {return cast<CDatePicker*>(parent)->setTimerInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyBool(this, control, L"ArrowsAtRight", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->isArrowsAtRight(); },
				[](IClass *parent, const bool value) {return cast<CDatePicker*>(parent)->setArrowsAtRight(value); }));
			Add(new CPropertyEnum(this, control, L"ContentAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CDatePicker*>(parent)->getContentAlign()); },
				[](IClass *parent, const String value) {return cast<CDatePicker*>(parent)->setContentAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CDatePicker*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CDatePicker*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"OuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"OuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"InnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"InnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"UpArrowBorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setUpArrowBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"UpArrowOuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setUpArrowOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"UpArrowInnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setUpArrowInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"UpArrowOuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setUpArrowOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"UpArrowInnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setUpArrowInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"UpArrowBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setUpArrowBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"UpArrowBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"UpArrowPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setUpArrowPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"UpArrowColor1", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowColor1(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setUpArrowColor1(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"UpArrowColor2", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowColor2(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setUpArrowColor2(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"UpArrowColor3", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getUpArrowColor3(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setUpArrowColor3(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"DownArrowBorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setDownArrowBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"DownArrowOuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setDownArrowOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"DownArrowInnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setDownArrowInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"DownArrowOuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setDownArrowOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"DownArrowInnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setDownArrowInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"DownArrowBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setDownArrowBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"DownArrowBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"DownArrowPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setDownArrowPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"DownArrowColor1", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowColor1(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setDownArrowColor1(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"DownArrowColor2", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowColor2(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setDownArrowColor2(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"DownArrowColor3", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getDownArrowColor3(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setDownArrowColor3(StringToState(state), value); }));
			Add(new CPropertyFloatState(this, control, L"ArrowDistance", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowDistance(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CDatePicker*>(parent)->setArrowDistance(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"ArrowBorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setArrowBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"ArrowOuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setArrowOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"ArrowInnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setArrowInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"ArrowOuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setArrowOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"ArrowInnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDatePicker*>(parent)->setArrowInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ArrowBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setArrowBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"DownArrowBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"ArrowPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setArrowPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"ArrowColor1", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowColor1(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setArrowColor1(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ArrowColor2", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowColor2(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setArrowColor2(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ArrowColor3", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getArrowColor3(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setArrowColor3(StringToState(state), value); }));
			Add(new standard::CPropertyComponentImageList(this, control, L"ImageList", nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getImageList(); },
				[](IClass *parent, standard::IImageList *value) {return cast<CDatePicker*>(parent)->setImageList(value); }));
			Add(new CPropertyIntegerState(this, control, L"IconIndex", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getIconIndex(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CDatePicker*>(parent)->setIconIndex(StringToState(state), value); }))
				->setMin(-1);
			Add(new CPropertyRectFState(this, control, L"IconPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getIconPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CDatePicker*>(parent)->setIconPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"ElementBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getElementBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setElementBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"ElementBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getElementBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ElementColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getElementColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDatePicker*>(parent)->setElementColor(StringToState(state), value); }));
			Add(new CPropertyFloatState(this, control, L"ElementPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CDatePicker*>(parent)->getElementPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CDatePicker*>(parent)->setElementPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"CalendarMargin", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarMargin(); },
				[](IClass *parent, const float value) {return cast<CDatePicker*>(parent)->setCalendarMargin(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"CalendarOuterBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarOuterBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarOuterBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"CalendarInnerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarInnerBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarInnerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"CalendarPadding", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarPadding(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"CalendarShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CDatePicker*>(parent)->setCalendarShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyPointF(this, control, L"CalendarShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CDatePicker*>(parent)->setCalendarShadowShift(value); }));
			Add(new CPropertyColor(this, control, L"CalendarShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CDatePicker*>(parent)->setCalendarShadowColor(value); }));
			Add(new CPropertyRectF(this, control, L"CalendarBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CDatePicker*>(parent)->setCalendarBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"CalendarOuterBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarOuterBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CDatePicker*>(parent)->setCalendarOuterBorderColor(value); }));
			Add(new CPropertyBorderColor(this, control, L"CalendarInnerBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarInnerBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CDatePicker*>(parent)->setCalendarInnerBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"CalendarBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CDatePicker*>(parent)->setCalendarBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"CalendarBackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CDatePicker*>(parent)->getCalendarBackgroundGradient(); }));
		}

		StringArray CDatePickerPropertyList::StateItems()
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

		CDatePicker::State CDatePickerPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CDatePicker::State::Hovered;
			if (state == L"State::Focused")
				return CDatePicker::State::Focused;
			if (state == L"State::FocusedHovered")
				return CDatePicker::State::FocusedHovered;
			if (state == L"State::Active")
				return CDatePicker::State::Active;
			if (state == L"State::ActiveHovered")
				return CDatePicker::State::ActiveHovered;
			if (state == L"State::Disabled")
				return CDatePicker::State::Disabled;
			return CDatePicker::State::Normal;
		}

		StringArray CDatePickerPropertyList::DisplayModeItems()
		{
			return StringArray{
				L"DisplayMode::UpDown",
				L"DisplayMode::Simple",
				L"DisplayMode::DropDown" };
		}

		CDatePicker::DisplayMode CDatePickerPropertyList::StringToDisplayMode(const String &state)
		{
			if (state == L"DisplayMode::UpDown")
				return CDatePicker::DisplayMode::UpDown;
			if (state == L"DisplayMode::Simple")
				return CDatePicker::DisplayMode::Simple;
			return CDatePicker::DisplayMode::DropDown;
		}

		String CDatePickerPropertyList::DisplayModeToString(const CDatePicker::DisplayMode state)
		{
			switch (state)
			{
			case CDatePicker::DisplayMode::DropDown:	return L"DisplayMode::DropDown";
			case CDatePicker::DisplayMode::UpDown:		return L"DisplayMode::UpDown";
			default:									return L"DisplayMode::Simple";
			}
		}

		StringArray CDatePickerPropertyList::MonthFormatItems()
		{
			return StringArray{
				L"MonthFormat::Short",
				L"MonthFormat::Medium",
				L"MonthFormat::Long" };
		}

		CDatePicker::MonthFormat CDatePickerPropertyList::StringToMonthFormat(const String &state)
		{
			if (state == L"MonthFormat::Medium")
				return CDatePicker::MonthFormat::Medium;
			if (state == L"MonthFormat::Long")
				return CDatePicker::MonthFormat::Long;
			return CDatePicker::MonthFormat::Short;
		}

		String CDatePickerPropertyList::MonthFormatToString(const CDatePicker::MonthFormat state)
		{
			switch (state)
			{
			case CDatePicker::MonthFormat::Medium:	return L"MonthFormat::Medium";
			case CDatePicker::MonthFormat::Long:	return L"MonthFormat::Long";
			default:								return L"MonthFormat::Short";
			}
		}

		StringArray CDatePickerPropertyList::ElementOrderItems()
		{
			return StringArray{
				L"ElementOrder::DayMonthYear",
				L"ElementOrder::DayYearMonth",
				L"ElementOrder::MonthDayYear",
				L"ElementOrder::MonthYearDay",
				L"ElementOrder::YearDayMonth",
				L"ElementOrder::YearMonthDay" };
		}

		CDatePicker::ElementOrder CDatePickerPropertyList::StringToElementOrder(const String &state)
		{
			if (state == L"ElementOrder::DayYearMonth")
				return CDatePicker::ElementOrder::DayYearMonth;
			if (state == L"ElementOrder::MonthDayYear")
				return CDatePicker::ElementOrder::MonthDayYear;
			if (state == L"ElementOrder::MonthYearDay")
				return CDatePicker::ElementOrder::MonthYearDay;
			if (state == L"ElementOrder::YearDayMonth")
				return CDatePicker::ElementOrder::YearDayMonth;
			if (state == L"ElementOrder::YearMonthDay")
				return CDatePicker::ElementOrder::YearMonthDay;
			return CDatePicker::ElementOrder::DayMonthYear;
		}

		String CDatePickerPropertyList::ElementOrderToString(const CDatePicker::ElementOrder state)
		{
			
			switch (state)
			{
			case CDatePicker::ElementOrder::DayYearMonth:	return L"ElementOrder::DayYearMonth";
			case CDatePicker::ElementOrder::MonthDayYear:	return L"ElementOrder::MonthDayYear";
			case CDatePicker::ElementOrder::MonthYearDay:	return L"ElementOrder::MonthYearDay";
			case CDatePicker::ElementOrder::YearDayMonth:	return L"ElementOrder::YearDayMonth";
			case CDatePicker::ElementOrder::YearMonthDay:	return L"ElementOrder::YearMonthDay";
			default:										return L"ElementOrder::DayMonthYear";
			}
		}

		StringArray CDatePickerPropertyList::OpenDirectionItems()
		{
			return StringArray{
				L"OpenDirection::Auto",
				L"OpenDirection::Up",
				L"OpenDirection::Down" };
		}

		CDatePicker::OpenDirection CDatePickerPropertyList::StringToOpenDirection(const String &state)
		{
			if (state == L"OpenDirection::Up")
				return CDatePicker::OpenDirection::Up;
			if (state == L"OpenDirection::Down")
				return CDatePicker::OpenDirection::Down;
			return CDatePicker::OpenDirection::Auto;
		}

		String CDatePickerPropertyList::OpenDirectionToString(const CDatePicker::OpenDirection state)
		{
			switch (state)
			{
			case CDatePicker::OpenDirection::Up:	return L"OpenDirection::Up";
			case CDatePicker::OpenDirection::Down:	return L"OpenDirection::Down";
			default:								return L"OpenDirection::Auto";
			}
		}

		StringArray CDatePickerPropertyList::OpenAlignItems()
		{
			return StringArray{
				L"OpenAlign::Left",
				L"OpenAlign::Right",
				L"OpenAlign::Center",
				L"OpenAlign::Justify" };
		}

		CDatePicker::OpenAlign CDatePickerPropertyList::StringToOpenAlign(const String &state)
		{
			if (state == L"OpenAlign::Right")
				return CDatePicker::OpenAlign::Right;
			if (state == L"OpenAlign::Center")
				return CDatePicker::OpenAlign::Center;
			if (state == L"OpenAlign::Justify")
				return CDatePicker::OpenAlign::Justify;
			return CDatePicker::OpenAlign::Left;
		}

		String CDatePickerPropertyList::OpenAlignToString(const CDatePicker::OpenAlign state)
		{
			switch (state)
			{
			case CDatePicker::OpenAlign::Right:		return L"OpenAlign::Right";
			case CDatePicker::OpenAlign::Center:	return L"OpenAlign::Center";
			case CDatePicker::OpenAlign::Justify:	return L"OpenAlign::Justify";
			default:								return L"OpenAlign::Left";
			}
		}

		StringArray CDatePickerPropertyList::ModeItems()
		{
			return StringArray{
				L"Mode::Month",
				L"Mode::Year",
				L"Mode::Decade",
				L"Mode::Century" };
		}

		CBuiltInMonthCalendar::Mode CDatePickerPropertyList::StringToMode(const String &state)
		{
			if (state == L"Mode::Year")
				return CBuiltInMonthCalendar::Mode::Year;
			if (state == L"Mode::Decade")
				return CBuiltInMonthCalendar::Mode::Decade;
			if (state == L"Mode::Century")
				return CBuiltInMonthCalendar::Mode::Century;
			return CBuiltInMonthCalendar::Mode::Month;
		}

		String CDatePickerPropertyList::ModeToString(const CBuiltInMonthCalendar::Mode state)
		{
			switch (state)
			{
			case CBuiltInMonthCalendar::Mode::Year:		return L"Mode::Year";
			case CBuiltInMonthCalendar::Mode::Decade:	return L"Mode::Decade";
			case CBuiltInMonthCalendar::Mode::Century:	return L"Mode::Century";
			default:									return L"Mode::Month";
			}
		}

		StringArray CDatePickerPropertyList::ElementStateItems()
		{
			return StringArray{
				L"ElementState::Normal",
				L"ElementState::Hovered",
				L"ElementState::Today",
				L"ElementState::TodayHovered",
				L"ElementState::Active",
				L"ElementState::ActiveHovered",
				L"ElementState::TodayActive",
				L"ElementState::TodayActiveHovered",
				L"ElementState::OtherRange",
				L"ElementState::OtherRangeHovered",
				L"ElementState::Disabled" };
		}

		CBuiltInMonthCalendar::ElementState CDatePickerPropertyList::StringToElementState(const String &state)
		{
			if (state == L"ElementState::Hovered")
				return CBuiltInMonthCalendar::ElementState::Hovered;
			if (state == L"ElementState::Today")
				return CBuiltInMonthCalendar::ElementState::Today;
			if (state == L"ElementState::TodayHovered")
				return CBuiltInMonthCalendar::ElementState::TodayHovered;
			if (state == L"ElementState::Active")
				return CBuiltInMonthCalendar::ElementState::Active;
			if (state == L"ElementState::ActiveHovered")
				return CBuiltInMonthCalendar::ElementState::ActiveHovered;
			if (state == L"ElementState::TodayActive")
				return CBuiltInMonthCalendar::ElementState::TodayActive;
			if (state == L"ElementState::TodayActiveHovered")
				return CBuiltInMonthCalendar::ElementState::TodayActiveHovered;
			if (state == L"ElementState::OtherRange")
				return CBuiltInMonthCalendar::ElementState::OtherRange;
			if (state == L"ElementState::OtherRangeHovered")
				return CBuiltInMonthCalendar::ElementState::OtherRangeHovered;
			if (state == L"ElementState::Disabled")
				return CBuiltInMonthCalendar::ElementState::Disabled;
			return CBuiltInMonthCalendar::ElementState::Normal;
		}

		StringArray CDatePickerPropertyList::TitleStateItems()
		{
			return StringArray{
				L"TitleState::Normal",
				L"TitleState::Hovered",
				L"TitleState::Active",
				L"TitleState::ActiveHovered",
				L"TitleState::Disabled" };
		}

		CBuiltInMonthCalendar::TitleState CDatePickerPropertyList::StringToTitleState(const String &state)
		{
			if (state == L"TitleState::Hovered")
				return CBuiltInMonthCalendar::TitleState::Hovered;
			if (state == L"TitleState::Active")
				return CBuiltInMonthCalendar::TitleState::Active;
			if (state == L"TitleState::ActiveHovered")
				return CBuiltInMonthCalendar::TitleState::ActiveHovered;
			if (state == L"TitleState::Disabled")
				return CBuiltInMonthCalendar::TitleState::Disabled;
			return CBuiltInMonthCalendar::TitleState::Normal;
		}

		StringArray CDatePickerPropertyList::DayTitleStateItems()
		{
			return StringArray{
				L"DayTitleState::Normal",
				L"DayTitleState::Disabled" };
		}

		CBuiltInMonthCalendar::DayTitleState CDatePickerPropertyList::StringToDayTitleState(const String &state)
		{
			if (state == L"DayTitleState::Disabled")
				return CBuiltInMonthCalendar::DayTitleState::Disabled;
			return CBuiltInMonthCalendar::DayTitleState::Normal;
		}
	}
}