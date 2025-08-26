// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IBuiltInControl.h"
#include "../Math/PointF.h"

namespace nitisa
{
	// MinYear/MinMonth/MinDay properties as well as MaxYear/MaxMonth/MaxDay ones are work together
	class IBuiltInMonthCalendar :public virtual IBuiltInControl
	{
	protected:
		IBuiltInMonthCalendar() = default;
		~IBuiltInMonthCalendar() = default;
		IBuiltInMonthCalendar(const IBuiltInMonthCalendar &other) = delete;
		IBuiltInMonthCalendar(IBuiltInMonthCalendar &&other) = delete;
		IBuiltInMonthCalendar &operator=(const IBuiltInMonthCalendar &other) = delete;
		IBuiltInMonthCalendar &operator=(IBuiltInMonthCalendar &&other) = delete;
	public:
		virtual PointF getRequiredSize() = 0; // Return size of the calendar
		virtual int getYear() = 0; // Return year
		virtual int getMonth() = 0; // Return month
		virtual int getDay() = 0; // Return day
		virtual int getMinYear() = 0; // Return minimum allowed year
		virtual int getMinMonth() = 0; // Return minimum allowed month
		virtual int getMinDay() = 0; // Return minimum allowed day
		virtual int getMaxYear() = 0; // Return maximum allowed year
		virtual int getMaxMonth() = 0; // Return maximum allowed month
		virtual int getMaxDay() = 0; // Return maximum allowed day
		virtual bool isAnimating() = 0; // Return whether control is in animation mode

		virtual bool setYear(const int value) = 0; // Set year
		virtual bool setMonth(const int value) = 0; // Set month
		virtual bool setDay(const int value) = 0; // Set day
		virtual bool setMinYear(const int value) = 0; // Set minimum allowed year
		virtual bool setMinMonth(const int value) = 0; // Set minimum allowed month
		virtual bool setMinDay(const int value) = 0; // Set minimum allowed day
		virtual bool setMaxYear(const int value) = 0; // Set maximum allowed year
		virtual bool setMaxMonth(const int value) = 0; // Set maximum allowed month
		virtual bool setMaxDay(const int value) = 0; // Set maximum allowed day

		virtual bool Next() = 0; // Show next month/year/...
		virtual bool Prev() = 0; // Show previous month/year/...
		virtual bool Today() = 0; // Set active date to today(if it is in allowed range of course)
	};
}