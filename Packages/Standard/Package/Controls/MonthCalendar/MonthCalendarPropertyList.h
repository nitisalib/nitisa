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
#include "../../../Controls/MonthCalendar/MonthCalendar.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CMonthCalendarPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CMonthCalendar::State StringToState(const String &state);

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
			CMonthCalendarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}