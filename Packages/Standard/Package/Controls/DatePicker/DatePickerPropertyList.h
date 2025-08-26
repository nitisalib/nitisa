// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"
#include "../../../Controls/DatePicker/DatePicker.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CDatePickerPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CDatePicker::State StringToState(const String &state);

			static StringArray DisplayModeItems();
			static CDatePicker::DisplayMode StringToDisplayMode(const String &state);
			static String DisplayModeToString(const CDatePicker::DisplayMode state);

			static StringArray MonthFormatItems();
			static CDatePicker::MonthFormat StringToMonthFormat(const String &state);
			static String MonthFormatToString(const CDatePicker::MonthFormat state);

			static StringArray ElementOrderItems();
			static CDatePicker::ElementOrder StringToElementOrder(const String &state);
			static String ElementOrderToString(const CDatePicker::ElementOrder state);

			static StringArray OpenDirectionItems();
			static CDatePicker::OpenDirection StringToOpenDirection(const String &state);
			static String OpenDirectionToString(const CDatePicker::OpenDirection state);

			static StringArray OpenAlignItems();
			static CDatePicker::OpenAlign StringToOpenAlign(const String &state);
			static String OpenAlignToString(const CDatePicker::OpenAlign state);

			static StringArray ModeItems();
			static CBuiltInMonthCalendar::Mode StringToMode(const String &state);
			static String ModeToString(const CBuiltInMonthCalendar::Mode state);

			static StringArray ElementStateItems();
			static CBuiltInMonthCalendar::ElementState StringToElementState(const String &state);

			static StringArray TitleStateItems();
			static CBuiltInMonthCalendar::TitleState StringToTitleState(const String &state);

			static StringArray DayTitleStateItems();
			static CBuiltInMonthCalendar::DayTitleState StringToDayTitleState(const String &state);
		public:
			CDatePickerPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}