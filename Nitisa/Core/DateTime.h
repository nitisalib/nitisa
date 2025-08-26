// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Interval.h"
#include "Strings.h"
#include "Variant.h"
#include <iostream>

namespace nitisa
{
	class CDateTime
	{
	private:
		int m_iYear;
		int m_iMonth;
		int m_iDay;
		int m_iHour;
		int m_iMinute;
		int m_iSecond;

		bool m_bTimePointValid;
		long long m_iTimePoint;
		void Validate(int &year, int &month, int &day, int &hour, int &minute, int &second) const;
		void NormalizeInterval(int &years, int &months, int &days, int &hours, int &minutes, int &seconds) const;

		long long Pack(const int year, const int month, const int day, const int hour, const int minute, const int second) const;
		void Unpack(const long long tp, int &year, int &month, int &day, int &hour, int &minute, int &second) const;
	public:
		// Months
		static const int January{ 1 };
		static const int February{ 2 };
		static const int March{ 3 };
		static const int April{ 4 };
		static const int May{ 5 };
		static const int June{ 6 };
		static const int July{ 7 };
		static const int August{ 8 };
		static const int September{ 9 };
		static const int October{ 10 };
		static const int November{ 11 };
		static const int December{ 12 };
		// Days of week
		static const int Monday{ 0 };
		static const int Tuesday{ 1 };
		static const int Wednesday{ 2 };
		static const int Thursday{ 3 };
		static const int Friday{ 4 };
		static const int Saturday{ 5 };
		static const int Sunday{ 6 };

		CDateTime(const bool local_time = false); // Create with current date and time
		CDateTime(const int year, const int month, const int day, const int hour, const int minute, const int second); // Create with specified date and time
		CDateTime(const CDateTime &other) = default;
		CDateTime(CDateTime &&other) = default;
		CDateTime(const long long datetime); // Create from specified time point

		int getYear() const; // Return year
		int getMonth() const; // Return month. In range 1-12
		int getDay() const; // Return day. In range 1-31
		int getHour() const; // Return hour. In range 0-23
		int getMinute() const; // Return minute. In range 0-59
		int getSecond() const; // Return second. In range 0-60
		int getDayOfWeek(); // Return day of week. In range 0-6
		int getDaysInMonth() const; // Return count of days in current object
		bool isLeap() const; // Return whether current object year is leap or not

		bool setYear(const int value); // Set year
		bool setMonth(const int value); // Set month
		bool setDay(const int value); // Set day
		bool setHour(const int value); // Set hour
		bool setMinute(const int value); // Set minute
		bool setSecond(const int value); // Set second

		static int getDaysInMonth(const int year, const int month); // Return count of days in specified year and month
		static bool isLeap(const int year); // Return whether specified year is leap or not

		bool setDate(const int year, const int month, const int day); // Set date
		bool setTime(const int hour, const int minute, const int second); // Set time
		bool setDateTime(const int year, const int month, const int day, const int hour, const int minute, const int second); // Set date and time

		bool operator==(const CDateTime &other) const; // Compare if this object date and time is equal to another one
		bool operator!=(const CDateTime &other) const; // Compare if this object date and time is not equal to another one
		bool operator>(CDateTime &other); // Compare if this object date-time is greater than in another one
		bool operator>=(CDateTime &other); // Compare if this object date-time is greater or equal to another one
		bool operator<(CDateTime &other); // Compare if this object date-time is less than in another one
		bool operator<=(CDateTime &other); // Compare if this object date-time is less or equal to another one
		CDateTime operator+(const CInterval &value); // Return date-time object equal to the current object date-time increasaed by specified interval
		CDateTime &operator+=(const CInterval &value); // Add specified interval to the current object and return this object
		CInterval operator-(CDateTime &other); // Return difference between this and another date-time objects
		CDateTime operator-(const CInterval &value); // Return date-time object equal to the current object date-time decreasaed by specified interval
		CDateTime &operator-=(const CInterval &value); // Subtract specified interval from the current object and return this object
		CDateTime &operator=(const CDateTime &other) = default;
		CDateTime &operator=(CDateTime &&other) = default;

		explicit operator long long(); // Convert to time point(long long)

		String asDateString() const; // Return date part as string in YYYY-MM-DD format
		String asDateTimeString(const bool short_time) const; // Return as string in YYYY-MM-DD hh:mm:ss (long) or YYYY-MM-DD hh:mm (short) format
		String asTimeString(const bool short_time) const; // Return time part as string in hh:mm:ss (long) or hh:mm (short) format
	};

	std::wostream &operator<<(std::wostream &stream, const CDateTime &a); // Output as source code

	String ToString(const CDateTime &value);
	Variant ToVariant(const CDateTime &value);
	void FromVariant(const Variant &value, CDateTime &dest);
}