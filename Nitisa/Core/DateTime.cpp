// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	const long long TP_SHIFT{ 250000000000 };
#pragma region Constructor & destructor
	CDateTime::CDateTime(const bool local_time):
		m_bTimePointValid{ false }
	{
		std::time_t t{ std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) };
	#ifdef _MSC_VER
		std::tm s;
		if ((local_time ? _localtime64_s(&s, &t) : _gmtime64_s(&s, &t)) == 0)
		{
			m_iYear = s.tm_year + 1900;
			m_iMonth = s.tm_mon + 1;
			m_iDay = s.tm_mday;
			m_iHour = s.tm_hour;
			m_iMinute = s.tm_min;
			m_iSecond = s.tm_sec;
		}
		else
		{
			m_iYear = 2018;
			m_iMonth = September;
			m_iDay = 3;
			m_iHour = 0;
			m_iMinute = 0;
			m_iSecond = 0;
		}
	#else
		std::tm *s;
		if ((s = local_time ? localtime(&t) : gmtime(&t)))
		{
			m_iYear = s->tm_year + 1900;
			m_iMonth = s->tm_mon + 1;
			m_iDay = s->tm_mday;
			m_iHour = s->tm_hour;
			m_iMinute = s->tm_min;
			m_iSecond = s->tm_sec;
		}
		else
		{
			m_iYear = 2018;
			m_iMonth = September;
			m_iDay = 3;
			m_iHour = 0;
			m_iMinute = 0;
			m_iSecond = 0;
		}
	#endif
	}

	CDateTime::CDateTime(const int year, const int month, const int day, const int hour, const int minute, const int second):
		m_iYear{ (year < 0) ? (year + 1) : year},
		m_iMonth{ ntl::Clamp<int>(month, 1, 12) },
		m_iHour{ ntl::Clamp<int>(hour, 0, 23) },
		m_iMinute{ ntl::Clamp<int>(minute, 0, 59) },
		m_iSecond{ ntl::Clamp<int>(second, 0, 59) },
		m_bTimePointValid{ false }
	{
		m_iDay = ntl::Clamp<int>(day, 1, getDaysInMonth((m_iYear <= 0) ? (m_iYear - 1) : m_iYear, m_iMonth));
	}

	CDateTime::CDateTime(const long long datetime) :
		m_bTimePointValid{ true },
		m_iTimePoint{ datetime }
	{
		Unpack(datetime, m_iYear, m_iMonth, m_iDay, m_iHour, m_iMinute, m_iSecond);
	}
#pragma endregion

#pragma region Getters
	int CDateTime::getYear() const
	{
		if (m_iYear <= 0)
			return m_iYear - 1;
		return m_iYear;
	}

	int CDateTime::getMonth() const
	{
		return m_iMonth;
	}

	int CDateTime::getDay() const
	{
		return m_iDay;
	}

	int CDateTime::getHour() const
	{
		return m_iHour;
	}

	int CDateTime::getMinute() const
	{
		return m_iMinute;
	}

	int CDateTime::getSecond() const
	{
		return m_iSecond;
	}

	int CDateTime::getDayOfWeek()
	{
		long long y1{ TP_SHIFT + m_iYear - 1 };
		long long result{ y1 * 365 + y1 / 400 - y1 / 100 + y1 / 4 };
		int y2{ (m_iYear <= 0) ? (m_iYear - 1) : m_iYear };
		for (int i = 1; i < m_iMonth; i++)
			result += getDaysInMonth(y2, i);
		result += m_iDay - 1;
		if (m_iYear <= 0) // Year 0 is not leap
			result++;
		return int(result % 7);
	}

	int CDateTime::getDaysInMonth() const
	{
		return getDaysInMonth((m_iYear <= 0) ? (m_iYear - 1) : m_iYear, m_iMonth);
	}

	bool CDateTime::isLeap() const
	{
		return isLeap((m_iYear <= 0) ? (m_iYear - 1) : m_iYear);
	}
#pragma endregion

#pragma region Setters
	bool CDateTime::setYear(const int value)
	{
		int y{ (value < 0) ? (value + 1) : value };
		if (y != m_iYear)
		{
			m_iYear = y;
			m_bTimePointValid = false;
			return true;
		}
		return false;
	}

	bool CDateTime::setMonth(const int value)
	{
		if (value >= 1 && value <= 12 && value != m_iMonth)
		{
			m_iMonth = value;
			m_bTimePointValid = false;
			return true;
		}
		return false;
	}

	bool CDateTime::setDay(const int value)
	{
		if (value >= 1 && value <= getDaysInMonth((m_iYear <= 0) ? (m_iYear - 1) : m_iYear, m_iMonth) && value != m_iDay)
		{
			if (m_bTimePointValid)
				m_iTimePoint += (value - m_iDay) * 86400;
			m_iDay = value;
			return true;
		}
		return false;
	}

	bool CDateTime::setHour(const int value)
	{
		if (value >= 0 && value <= 23 && value != m_iHour)
		{
			if (m_bTimePointValid)
				m_iTimePoint += (value - m_iHour) * 3600;
			m_iHour = value;
			return true;
		}
		return false;
	}

	bool CDateTime::setMinute(const int value)
	{
		if (value >= 0 && value <= 59 && value != m_iMinute)
		{
			if (m_bTimePointValid)
				m_iTimePoint += (value - m_iMinute) * 60;
			m_iMinute = value;
			return true;
		}
		return false;
	}

	bool CDateTime::setSecond(const int value)
	{
		if (value >= 0 && value <= 59 && value != m_iSecond)
		{
			if (m_bTimePointValid)
				m_iTimePoint += value - m_iSecond;
			m_iSecond = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Methods
	int CDateTime::getDaysInMonth(const int year, const int month)
	{
		if (month == April || month == June || month == September || month == November)
			return 30;
		if (month == February)
		{
			if (isLeap(year))
				return 29;
			return 28;
		}
		return 31;
	}

	bool CDateTime::isLeap(const int year)
	{
		if (year % 400 == 0)
			return true;
		if (year % 100 == 0)
			return false;
		return year % 4 == 0;
	}

	bool CDateTime::setDate(const int year, const int month, const int day)
	{
		int y{ (year < 0) ? (year + 1) : year };
		if (month >= 1 && month <= 12 && day >= 1 && day <= getDaysInMonth((y <= 0) ? (y - 1) : y, month))
		{
			if (y != m_iYear || month != m_iMonth || day != m_iDay)
			{
				m_iYear = y;
				m_iMonth = month;
				m_iDay = day;
				m_bTimePointValid = false;
				return true;
			}
		}
		return false;
	}

	bool CDateTime::setTime(const int hour, const int minute, const int second)
	{
		if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59 && (hour != m_iHour || minute != m_iMinute || second != m_iSecond))
		{
			if (m_bTimePointValid)
				m_iTimePoint += (hour - m_iHour) * 3600 + (minute - m_iMinute) * 60 + second - m_iSecond;
			m_iHour = hour;
			m_iMinute = minute;
			m_iSecond = second;
			return true;
		}
		return false;
	}

	bool CDateTime::setDateTime(const int year, const int month, const int day, const int hour, const int minute, const int second)
	{
		int y{ (year < 0) ? (year + 1) : year };
		if (month >= 1 && month <= 12 && day >= 1 && day <= getDaysInMonth((y <= 0) ? (y + 1) : y, month) && hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59)
		{
			if (y != m_iYear || month != m_iMonth || day != m_iDay || hour != m_iHour || minute != m_iMinute || second != m_iSecond)
			{
				m_iYear = y;
				m_iMonth = month;
				m_iDay = day;
				m_iHour = hour;
				m_iMinute = minute;
				m_iSecond = second;
				m_bTimePointValid = false;
				return true;
			}
		}
		return false;
	}
#pragma endregion

#pragma region Helpers
	long long CDateTime::Pack(const int year, const int month, const int day, const int hour, const int minute, const int second) const
	{
		long long y1{ TP_SHIFT + year - 1 };
		long long result{ y1 * 365 + y1 / 400 - y1 / 100 + y1 / 4 }; // TimePoint of year start
		int y2{ (year <= 0) ? (year - 1) : year };
		for (int i = 1; i < month; i++) // Add days from prev monthes(till specified one)
			result += getDaysInMonth(y2, i);
		result += day - 1; // Add day of month
		if (year <= 0) // Year 0 is not leap
			result++;
		return result * 86400 + hour * 3600 + minute * 60 + second;
	}

	void CDateTime::Unpack(const long long tp, int &year, int &month, int &day, int &hour, int &minute, int &second) const
	{
		// Date part
		long long date{ tp / 86400 };
		long long y400{ date / 146097 }; // Exact number of 400-year intervals
		day = int(date - y400 * 146097); // Days from the beginning of last 400-year interval
		// Year
		year = int(y400 * 400 + 1 - TP_SHIFT);
		while (day > 0)
		{
			int days_in_year{ isLeap(year) ? 366 : 365 };
			if (days_in_year > day)
				break;
			year++;
			day -= days_in_year;
		}
		if (year <= 0) // Year 0 is not leap
			day--;
		// Months
		int y{ (year <= 0) ? (year - 1) : year };
		month = 1;
		for (int i = 1; i < 12; i++)
		{
			int days_in_month{ getDaysInMonth(y, i) };
			if (days_in_month > day)
				break;
			month++;
			day -= days_in_month;
		}
		day++;
		// Time part
		int time{ int(tp % 86400) };
		hour = time / 3600;
		time -= hour * 3600;
		minute = time / 60;
		second = time % 60;
	}

	void CDateTime::Validate(int &year, int &month, int &day, int &hour, int &minute, int &second) const
	{
		// Adjust second
		if (second >= 60)
		{
			minute += second / 60;
			second %= 60;
		}
		else if(second < 0)
		{
			minute += second / 60 - 1;
			second = 60 + second % 60;
		}
		// Adjust minute
		if (minute >= 60)
		{
			hour += minute / 60;
			minute %= 60;
		}
		else if (minute < 0)
		{
			hour += minute / 60 - 1;
			minute = 60 + minute % 60;
		}
		// Adjust hour
		if (hour >= 24)
		{
			day += hour / 24;
			hour %= 24;
		}
		else if (hour < 0)
		{
			day += hour / 24 - 1;
			hour = 24 + hour % 24;
		}
		// Adjust month
		if (month > 12)
		{
			year += month / 12;
			month %= 12;
		}
		else if (month <= 0)
		{
			year += month / 12 - 1;
			month = 12 + month % 12;
		}
		// Adjust day
		while (day > getDaysInMonth((year <= 0) ? (year - 1) : year, month))
		{
			day -= getDaysInMonth((year <= 0) ? (year - 1) : year, month);
			month++;
			if (month > 12)
			{
				year++;
				month -= 12;
			}
		}
		while (day <= 0)
		{
			month--;
			if (month <= 0)
			{
				year--;
				month += 12;
			}
			day += getDaysInMonth((year <= 0) ? (year - 1) : year, month);
		}
	}

	void CDateTime::NormalizeInterval(int &years, int &months, int &days, int &hours, int &minutes, int &seconds) const
	{
		// Adjust seconds
		if (seconds >= 60)
		{
			minutes += seconds / 60;
			seconds %= 60;
		}
		else if (seconds < 0)
		{
			minutes += seconds / 60 - 1;
			seconds = 60 + seconds % 60;
		}
		// Adjust minutes
		if (minutes >= 60)
		{
			hours += minutes / 60;
			minutes %= 60;
		}
		else if (minutes < 0)
		{
			hours += minutes / 60 - 1;
			minutes = 60 + minutes % 60;
		}
		// Adjust hours
		if (hours >= 24)
		{
			days += hours / 24;
			hours %= 24;
		}
		else if (hours < 0)
		{
			days += hours / 24 - 1;
			hours = 24 + hours % 24;
		}
		// Adjust months
		if (months >= 12)
		{
			years += months / 12;
			months %= 12;
		}
		else if (months < 0)
		{
			years += months / 12 - 1;
			months = 12 + months % 12;
		}
		// Adjust day
		while (days >= getDaysInMonth(1, months))
		{
			days -= getDaysInMonth(1, months);
			months++;
			if (months >= 12)
			{
				years++;
				months -= 12;
			}
		}
		while (days < 0)
		{
			months--;
			if (months < 0)
			{
				years--;
				months += 12;
			}
			days += getDaysInMonth(1, months);
		}
	}
#pragma endregion

#pragma region Operators
	bool CDateTime::operator==(const CDateTime &other) const
	{
		return m_iYear == other.m_iYear && m_iMonth == other.m_iMonth && m_iDay == other.m_iDay && m_iHour == other.m_iHour && m_iMinute == other.m_iMinute && m_iSecond == other.m_iSecond;
	}

	bool CDateTime::operator!=(const CDateTime &other) const
	{
		return m_iYear != other.m_iYear || m_iMonth != other.m_iMonth || m_iDay != other.m_iDay || m_iHour != other.m_iHour || m_iMinute != other.m_iMinute || m_iSecond != other.m_iSecond;
	}

	bool CDateTime::operator>(CDateTime &other)
	{
		if (m_iYear > other.m_iYear)
			return true;
		if (m_iYear < other.m_iYear)
			return false;
		if (m_iMonth > other.m_iMonth)
			return true;
		if (m_iMonth < other.m_iMonth)
			return false;
		if (m_iDay > other.m_iDay)
			return true;
		if (m_iDay < other.m_iDay)
			return false;
		if (m_iHour > other.m_iHour)
			return true;
		if (m_iHour < other.m_iHour)
			return false;
		if (m_iMinute > other.m_iMinute)
			return true;
		if (m_iMinute < other.m_iMinute)
			return false;
		if (m_iSecond > other.m_iSecond)
			return true;
		return false;
	}

	bool CDateTime::operator>=(CDateTime &other)
	{
		if (m_iYear > other.m_iYear)
			return true;
		if (m_iYear < other.m_iYear)
			return false;
		if (m_iMonth > other.m_iMonth)
			return true;
		if (m_iMonth < other.m_iMonth)
			return false;
		if (m_iDay > other.m_iDay)
			return true;
		if (m_iDay < other.m_iDay)
			return false;
		if (m_iHour > other.m_iHour)
			return true;
		if (m_iHour < other.m_iHour)
			return false;
		if (m_iMinute > other.m_iMinute)
			return true;
		if (m_iMinute < other.m_iMinute)
			return false;
		if (m_iSecond >= other.m_iSecond)
			return true;
		return false;
	}

	bool CDateTime::operator<(CDateTime &other)
	{
		if (m_iYear < other.m_iYear)
			return true;
		if (m_iYear > other.m_iYear)
			return false;
		if (m_iMonth < other.m_iMonth)
			return true;
		if (m_iMonth > other.m_iMonth)
			return false;
		if (m_iDay < other.m_iDay)
			return true;
		if (m_iDay > other.m_iDay)
			return false;
		if (m_iHour < other.m_iHour)
			return true;
		if (m_iHour > other.m_iHour)
			return false;
		if (m_iMinute < other.m_iMinute)
			return true;
		if (m_iMinute > other.m_iMinute)
			return false;
		if (m_iSecond < other.m_iSecond)
			return true;
		return false;
	}

	bool CDateTime::operator<=(CDateTime &other)
	{
		if (m_iYear < other.m_iYear)
			return true;
		if (m_iYear > other.m_iYear)
			return false;
		if (m_iMonth < other.m_iMonth)
			return true;
		if (m_iMonth > other.m_iMonth)
			return false;
		if (m_iDay < other.m_iDay)
			return true;
		if (m_iDay > other.m_iDay)
			return false;
		if (m_iHour < other.m_iHour)
			return true;
		if (m_iHour > other.m_iHour)
			return false;
		if (m_iMinute < other.m_iMinute)
			return true;
		if (m_iMinute > other.m_iMinute)
			return false;
		if (m_iSecond <= other.m_iSecond)
			return true;
		return false;
	}

	CDateTime CDateTime::operator+(const CInterval &value)
	{
		return CDateTime{ (long long)(*this) + (long long)value };
	}

	CDateTime &CDateTime::operator+=(const CInterval &value)
	{
		m_iTimePoint = (long long)(*this) + (long long)value;
		Unpack(m_iTimePoint, m_iYear, m_iMonth, m_iDay, m_iHour, m_iMinute, m_iSecond);
		return *this;
	}

	CInterval CDateTime::operator-(CDateTime &other)
	{
		return CInterval{ (long long)(*this) - (long long)other };
	}

	CDateTime CDateTime::operator-(const CInterval &value)
	{
		return CDateTime{ (long long)(*this) - (long long)value };
	}

	CDateTime &CDateTime::operator-=(const CInterval &value)
	{
		m_iTimePoint = (long long)(*this) - (long long)value;
		Unpack(m_iTimePoint, m_iYear, m_iMonth, m_iDay, m_iHour, m_iMinute, m_iSecond);
		return *this;
	}

	CDateTime::operator long long()
	{
		if (!m_bTimePointValid)
		{
			m_iTimePoint = Pack(m_iYear, m_iMonth, m_iDay, m_iHour, m_iMinute, m_iSecond);
			m_bTimePointValid = true;
		}
		return m_iTimePoint;
	}
#pragma endregion

#pragma region Convertion to String
	String CDateTime::asDateString() const
	{
		return
			PadLeft(ToString(m_iYear), L'0', 4) + L"-" +
			PadLeft(ToString(m_iMonth), L'0', 2) + L"-" +
			PadLeft(ToString(m_iDay), L'0', 2);
	}

	String CDateTime::asDateTimeString(const bool short_time) const
	{
		if (short_time)
		{
			return
				PadLeft(ToString(m_iYear), L'0', 4) + L"-" +
				PadLeft(ToString(m_iMonth), L'0', 2) + L"-" +
				PadLeft(ToString(m_iDay), L'0', 2) + L" " +
				PadLeft(ToString(m_iHour), L'0', 2) + L":" +
				PadLeft(ToString(m_iMinute), L'0', 2);
		}
		return
			PadLeft(ToString(m_iYear), L'0', 4) + L"-" +
			PadLeft(ToString(m_iMonth), L'0', 2) + L"-" +
			PadLeft(ToString(m_iDay), L'0', 2) + L" " +
			PadLeft(ToString(m_iHour), L'0', 2) + L":" +
			PadLeft(ToString(m_iMinute), L'0', 2) + L":" +
			PadLeft(ToString(m_iSecond), L'0', 2);
	}

	String CDateTime::asTimeString(const bool short_time) const
	{
		if (short_time)
		{
			return
				PadLeft(ToString(m_iHour), L'0', 2) + L":" +
				PadLeft(ToString(m_iMinute), L'0', 2);
		}
		return
			PadLeft(ToString(m_iHour), L'0', 2) + L":" +
			PadLeft(ToString(m_iMinute), L'0', 2) + L":" +
			PadLeft(ToString(m_iSecond), L'0', 2);
	}
#pragma endregion

#pragma region Standalone operators
	std::wostream &operator<<(std::wostream &stream, const CDateTime &a)
	{
		stream
			<< (a.getYear() < 0 ? L"-" : L"") << PadLeft(ToString(ntl::Abs<int>(a.getYear())), L'0', 4)
			<< L"-" << PadLeft(ToString(a.getMonth()), L'0', 2)
			<< L"-" << PadLeft(ToString(a.getDay()), L'0', 2)
			<< L" " << PadLeft(ToString(a.getHour()), L'0', 2)
			<< L":" << PadLeft(ToString(a.getMinute()), L'0', 2)
			<< L":" << PadLeft(ToString(a.getSecond()), L'0', 2);
		return stream;
	}
#pragma endregion

#pragma region Functions
	String ToString(const CDateTime &value)
	{
		return
			String((value.getYear() < 0) ? L"-" : L"") + PadLeft(ToString(value.getYear()), L'0', 4) + L"-" +
			PadLeft(ToString(value.getMonth()), L'0', 2) + L"-" +
			PadLeft(ToString(value.getDay()), L'0', 2) + L" " +
			PadLeft(ToString(value.getHour()), L'0', 2) + L":" +
			PadLeft(ToString(value.getMinute()), L'0', 2) + L":" +
			PadLeft(ToString(value.getSecond()), L'0', 2);
	}

	Variant ToVariant(const CDateTime &value)
	{
		Variant result;
		result[L"Year"] = value.getYear();
		result[L"Month"] = value.getMonth();
		result[L"Day"] = value.getDay();
		result[L"Hour"] = value.getHour();
		result[L"Minute"] = value.getMinute();
		result[L"Second"] = value.getSecond();
		return result;
	}

	void FromVariant(const Variant &value, CDateTime &dest)
	{
		dest.setDateTime(int(value.get(L"Year")), int(value.get(L"Month")), int(value.get(L"Day")), int(value.get(L"Hour")), int(value.get(L"Minute")), int(value.get(L"Second")));
	}
#pragma endregion
}