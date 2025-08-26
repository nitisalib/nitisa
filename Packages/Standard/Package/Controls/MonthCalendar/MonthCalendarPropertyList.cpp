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
		CMonthCalendarPropertyList::CMonthCalendarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"Constraints");
			Delete(L"Size");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Align");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyInteger(this, control, L"Year", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getYear(); },
				[](IClass *parent, const int value) {return cast<CMonthCalendar*>(parent)->setYear(value); }));
			Add(new CPropertyInteger(this, control, L"Month", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getMonth(); },
				[](IClass *parent, const int value) {return cast<CMonthCalendar*>(parent)->setMonth(value); }))
				->setMin(1)->setMax(12);
			Add(new CPropertyInteger(this, control, L"Day", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getDay(); },
				[](IClass *parent, const int value) {return cast<CMonthCalendar*>(parent)->setDay(value); }))
				->setMin(1)->setMax(31);
			Add(new CPropertyInteger(this, control, L"MinYear", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getMinYear(); },
				[](IClass *parent, const int value) {return cast<CMonthCalendar*>(parent)->setMinYear(value); }));
			Add(new CPropertyInteger(this, control, L"MinMonth", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getMinMonth(); },
				[](IClass *parent, const int value) {return cast<CMonthCalendar*>(parent)->setMinMonth(value); }))
				->setMin(1)->setMax(12);
			Add(new CPropertyInteger(this, control, L"MinDay", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getMinDay(); },
				[](IClass *parent, const int value) {return cast<CMonthCalendar*>(parent)->setMinDay(value); }))
				->setMin(1)->setMax(31);
			Add(new CPropertyInteger(this, control, L"MaxYear", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getMaxYear(); },
				[](IClass *parent, const int value) {return cast<CMonthCalendar*>(parent)->setMaxYear(value); }));
			Add(new CPropertyInteger(this, control, L"MaxMonth", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getMaxMonth(); },
				[](IClass *parent, const int value) {return cast<CMonthCalendar*>(parent)->setMaxMonth(value); }))
				->setMin(1)->setMax(12);
			Add(new CPropertyInteger(this, control, L"MaxDay", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getMaxDay(); },
				[](IClass *parent, const int value) {return cast<CMonthCalendar*>(parent)->setMaxDay(value); }))
				->setMin(1)->setMax(31);
			Add(new CPropertyRectF(this, control, L"OuterBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getOuterBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CMonthCalendar*>(parent)->setOuterBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"InnerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getInnerBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CMonthCalendar*>(parent)->setInnerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CMonthCalendar*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CMonthCalendar*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CMonthCalendar*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"OuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMonthCalendar*>(parent)->setOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"InnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMonthCalendar*>(parent)->setInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getBackgroundGradient(StringToState(state)); }));
			
			Add(new CPropertyEnum(this, control, L"Mode", false, ModeItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent) {return ModeToString(cast<CMonthCalendar*>(parent)->getMode()); },
				[](IClass *parent, const String value) {return cast<CMonthCalendar*>(parent)->setMode(StringToMode(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyBool(this, control, L"ShowToday", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->isShowToday(); },
				[](IClass *parent, const bool value) {return cast<CMonthCalendar*>(parent)->setShowToday(value); }));
			Add(new CPropertyRectF(this, control, L"TitlePadding", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getTitlePadding(); },
				[](IClass *parent, const RectF value) {return cast<CMonthCalendar*>(parent)->setTitlePadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"TodayPadding", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getTodayPadding(); },
				[](IClass *parent, const RectF value) {return cast<CMonthCalendar*>(parent)->setTodayPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ElementPadding", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getElementPadding(); },
				[](IClass *parent, const RectF value) {return cast<CMonthCalendar*>(parent)->setElementPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"DayPadding", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getDayPadding(); },
				[](IClass *parent, const RectF value) {return cast<CMonthCalendar*>(parent)->setDayPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"TodayMargin", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getTodayMargin(); },
				[](IClass *parent, const float value) {return cast<CMonthCalendar*>(parent)->setTodayMargin(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"TodayRectWidth", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getTodayRectWidth(); },
				[](IClass *parent, const float value) {return cast<CMonthCalendar*>(parent)->setTodayRectWidth(value); }))
				->setMin(0);
			Add(new CPropertyBool(this, control, L"Animate", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->isAnimate(); },
				[](IClass *parent, const bool value) {return cast<CMonthCalendar*>(parent)->setAnimate(value); }));
			Add(new CPropertyFloat(this, control, L"AnimateInterval", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getAnimateInterval(); },
				[](IClass *parent, const float value) {return cast<CMonthCalendar*>(parent)->setAnimateInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"AnimateMinScale", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getAnimateMinScale(); },
				[](IClass *parent, const float value) {return cast<CMonthCalendar*>(parent)->setAnimateMinScale(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyFloat(this, control, L"AnimateTime", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getAnimateTime(); },
				[](IClass *parent, const float value) {return cast<CMonthCalendar*>(parent)->setAnimateTime(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CMonthCalendar*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CMonthCalendar*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyEnumState(this, control, L"TitleAlign", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CMonthCalendar*>(parent)->getTitleAlign(StringToTitleState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMonthCalendar*>(parent)->setTitleAlign(StringToTitleState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			CPropertyRectFState *prf{ new CPropertyRectFState(this, control, L"TitleBorderRadius", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleBorderRadius(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTitleBorderRadius(StringToTitleState(state), value); }) };
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			prf = new CPropertyRectFState(this, control, L"TitleBorderWidth", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleBorderWidth(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTitleBorderWidth(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			Add(new CPropertyBorderColorState(this, control, L"TitleBorderColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleBorderColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMonthCalendar*>(parent)->setTitleBorderColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TitleBackgroundColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleBackgroundColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTitleBackgroundColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"TitleBackgroundGradient", TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleBackgroundGradient(StringToTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TitleColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTitleColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf = new CPropertyRectFState(this, control, L"TitlePrevRangeBorderRadius", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitlePrevRangeBorderRadius(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTitlePrevRangeBorderRadius(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			prf = new CPropertyRectFState(this, control, L"TitlePrevRangeBorderWidth", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitlePrevRangeBorderWidth(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTitlePrevRangeBorderWidth(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			Add(new CPropertyBorderColorState(this, control, L"TitlePrevRangeBorderColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitlePrevRangeBorderColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMonthCalendar*>(parent)->setTitlePrevRangeBorderColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TitlePrevRangeBackgroundColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitlePrevRangeBackgroundColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTitlePrevRangeBackgroundColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"TitlePrevRangeBackgroundGradient", TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitlePrevRangeBackgroundGradient(StringToTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf = new CPropertyRectFState(this, control, L"TitlePrevRangePadding", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitlePrevRangePadding(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTitlePrevRangePadding(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			Add(new CPropertyColorState(this, control, L"TitlePrevRangeColor1", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitlePrevRangeColor1(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTitlePrevRangeColor1(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TitlePrevRangeColor2", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitlePrevRangeColor2(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTitlePrevRangeColor2(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TitlePrevRangeColor3", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitlePrevRangeColor3(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTitlePrevRangeColor3(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf = new CPropertyRectFState(this, control, L"TitleNextRangeBorderRadius", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleNextRangeBorderRadius(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTitleNextRangeBorderRadius(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			prf = new CPropertyRectFState(this, control, L"TitleNextRangeBorderWidth", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleNextRangeBorderWidth(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTitleNextRangeBorderWidth(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			Add(new CPropertyBorderColorState(this, control, L"TitleNextRangeBorderColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleNextRangeBorderColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMonthCalendar*>(parent)->setTitleNextRangeBorderColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TitleNextRangeBackgroundColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleNextRangeBackgroundColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTitleNextRangeBackgroundColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"TitleNextRangeBackgroundGradient", TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleNextRangeBackgroundGradient(StringToTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf = new CPropertyRectFState(this, control, L"TitleNextRangePadding", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleNextRangePadding(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTitleNextRangePadding(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			Add(new CPropertyColorState(this, control, L"TitleNextRangeColor1", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleNextRangeColor1(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTitleNextRangeColor1(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TitleNextRangeColor2", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleNextRangeColor2(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTitleNextRangeColor2(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TitleNextRangeColor3", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTitleNextRangeColor3(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTitleNextRangeColor3(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyEnumState(this, control, L"TodayAlign", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CMonthCalendar*>(parent)->getTodayAlign(StringToTitleState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMonthCalendar*>(parent)->setTodayAlign(StringToTitleState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			prf = new CPropertyRectFState(this, control, L"TodayBorderRadius", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayBorderRadius(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTodayBorderRadius(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			prf = new CPropertyRectFState(this, control, L"TodayBorderWidth", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayBorderWidth(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTodayBorderWidth(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			Add(new CPropertyBorderColorState(this, control, L"TodayBorderColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayBorderColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMonthCalendar*>(parent)->setTodayBorderColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TodayBackgroundColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayBackgroundColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTodayBackgroundColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"TodayBackgroundGradient", TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayBackgroundGradient(StringToTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TodayColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTodayColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf = new CPropertyRectFState(this, control, L"TodayRectBorderRadius", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayRectBorderRadius(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTodayRectBorderRadius(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			prf = new CPropertyRectFState(this, control, L"TodayRectBorderWidth", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayRectBorderWidth(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setTodayRectBorderWidth(StringToTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			Add(new CPropertyBorderColorState(this, control, L"TodayRectBorderColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayRectBorderColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMonthCalendar*>(parent)->setTodayRectBorderColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"TodayRectBackgroundColor", false, TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayRectBackgroundColor(StringToTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setTodayRectBackgroundColor(StringToTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"TodayRectBackgroundGradient", TitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getTodayRectBackgroundGradient(StringToTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyEnumState(this, control, L"ElementHorizontalAlign", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CMonthCalendar*>(parent)->getElementHorizontalAlign(StringToElementState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMonthCalendar*>(parent)->setElementHorizontalAlign(StringToElementState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnumState(this, control, L"ElementVerticalAlign", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return VerticalAlignToString(cast<CMonthCalendar*>(parent)->getElementVerticalAlign(StringToElementState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMonthCalendar*>(parent)->setElementVerticalAlign(StringToElementState(state), StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			prf = new CPropertyRectFState(this, control, L"ElementBorderRadius", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getElementBorderRadius(StringToElementState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setElementBorderRadius(StringToElementState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			prf = new CPropertyRectFState(this, control, L"ElementBorderWidth", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getElementBorderWidth(StringToElementState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setElementBorderWidth(StringToElementState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			Add(new CPropertyBorderColorState(this, control, L"ElementBorderColor", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getElementBorderColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMonthCalendar*>(parent)->setElementBorderColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"ElementBackgroundColor", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getElementBackgroundColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setElementBackgroundColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"ElementBackgroundGradient", ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getElementBackgroundGradient(StringToElementState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"ElementColor", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getElementColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setElementColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"ElementOutlineColor", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getElementOutlineColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setElementOutlineColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyMaskState(this, control, L"ElementOutlineMask", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getElementOutlineMask(StringToElementState(state)); },
				[](IClass *parent, const String &state, const unsigned int value) {return cast<CMonthCalendar*>(parent)->setElementOutlineMask(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyEnumState(this, control, L"DayHorizontalAlign", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CMonthCalendar*>(parent)->getDayHorizontalAlign(StringToElementState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMonthCalendar*>(parent)->setDayHorizontalAlign(StringToElementState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnumState(this, control, L"DayVerticalAlign", false, ElementStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return VerticalAlignToString(cast<CMonthCalendar*>(parent)->getDayVerticalAlign(StringToElementState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMonthCalendar*>(parent)->setDayVerticalAlign(StringToElementState(state), StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyEnumState(this, control, L"DayTitleHorizontalAlign", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CMonthCalendar*>(parent)->getDayTitleHorizontalAlign(StringToDayTitleState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMonthCalendar*>(parent)->setDayTitleHorizontalAlign(StringToDayTitleState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnumState(this, control, L"DayTitleVerticalAlign", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return VerticalAlignToString(cast<CMonthCalendar*>(parent)->getDayTitleVerticalAlign(StringToDayTitleState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CMonthCalendar*>(parent)->setDayTitleVerticalAlign(StringToDayTitleState(state), StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h")
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			prf = new CPropertyRectFState(this, control, L"DayTitleBorderRadius", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getDayTitleBorderRadius(StringToDayTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setDayTitleBorderRadius(StringToDayTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			prf = new CPropertyRectFState(this, control, L"DayTitleBorderWidth", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getDayTitleBorderWidth(StringToDayTitleState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CMonthCalendar*>(parent)->setDayTitleBorderWidth(StringToDayTitleState(state), value); });
			prf->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			prf->setMin(0);
			Add(prf);
			Add(new CPropertyBorderColorState(this, control, L"DayTitleBorderColor", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getDayTitleBorderColor(StringToDayTitleState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMonthCalendar*>(parent)->setDayTitleBorderColor(StringToDayTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"DayTitleBackgroundColor", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getDayTitleBackgroundColor(StringToDayTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setDayTitleBackgroundColor(StringToDayTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyGradientState(this, control, L"DayTitleBackgroundGradient", DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getDayTitleBackgroundGradient(StringToDayTitleState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
			Add(new CPropertyColorState(this, control, L"DayTitleColor", false, DayTitleStateItems(), ExportPrefixType::Namespace, L"CBuiltInMonthCalendar::", nullptr,
				[](IClass *parent, const String &state) {return cast<CMonthCalendar*>(parent)->getDayTitleColor(StringToDayTitleState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMonthCalendar*>(parent)->setDayTitleColor(StringToDayTitleState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControl/MonthCalendar/BuiltInMonthCalendar.h");
		}

		StringArray CMonthCalendarPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Disabled" };
		}

		CMonthCalendar::State CMonthCalendarPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Novered")
				return CMonthCalendar::State::Hovered;
			if (state == L"State::Disabled")
				return CMonthCalendar::State::Disabled;
			return CMonthCalendar::State::Normal;
		}

		StringArray CMonthCalendarPropertyList::ModeItems()
		{
			return StringArray{
				L"Mode::Month",
				L"Mode::Year",
				L"Mode::Decade",
				L"Mode::Century" };
		}

		CBuiltInMonthCalendar::Mode CMonthCalendarPropertyList::StringToMode(const String &state)
		{
			if (state == L"Mode::Year")
				return CBuiltInMonthCalendar::Mode::Year;
			if (state == L"Mode::Decade")
				return CBuiltInMonthCalendar::Mode::Decade;
			if (state == L"Mode::Century")
				return CBuiltInMonthCalendar::Mode::Century;
			return CBuiltInMonthCalendar::Mode::Month;
		}

		String CMonthCalendarPropertyList::ModeToString(const CBuiltInMonthCalendar::Mode state)
		{
			switch (state)
			{
			case CBuiltInMonthCalendar::Mode::Year:		return L"Mode::Year";
			case CBuiltInMonthCalendar::Mode::Decade:	return L"Mode::Decade";
			case CBuiltInMonthCalendar::Mode::Century:	return L"Mode::Century";
			default:									return L"Mode::Month";
			}
		}

		StringArray CMonthCalendarPropertyList::ElementStateItems()
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

		CBuiltInMonthCalendar::ElementState CMonthCalendarPropertyList::StringToElementState(const String &state)
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

		StringArray CMonthCalendarPropertyList::TitleStateItems()
		{
			return StringArray{
				L"TitleState::Normal",
				L"TitleState::Hovered",
				L"TitleState::Active",
				L"TitleState::ActiveHovered",
				L"TitleState::Disabled" };
		}

		CBuiltInMonthCalendar::TitleState CMonthCalendarPropertyList::StringToTitleState(const String &state)
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

		StringArray CMonthCalendarPropertyList::DayTitleStateItems()
		{
			return StringArray{
				L"DayTitleState::Normal",
				L"DayTitleState::Disabled" };
		}

		CBuiltInMonthCalendar::DayTitleState CMonthCalendarPropertyList::StringToDayTitleState(const String &state)
		{
			if (state == L"DayTitleState::Disabled")
				return CBuiltInMonthCalendar::DayTitleState::Disabled;
			return CBuiltInMonthCalendar::DayTitleState::Normal;
		}
	}
}