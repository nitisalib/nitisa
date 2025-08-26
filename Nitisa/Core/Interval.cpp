// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CInterval::CInterval() :
		m_iYears{ 0 },
		m_iMonths{ 0 },
		m_iDays{ 0 },
		m_iHours{ 0 },
		m_iMinutes{ 0 },
		m_iSeconds{ 0 }
	{

	}

	CInterval::CInterval(const int years, const int months, const int days, const int hours, const int minutes, const int seconds) :
		m_iYears{ years },
		m_iMonths{ months },
		m_iDays{ days },
		m_iHours{ hours },
		m_iMinutes{ minutes },
		m_iSeconds{ seconds }
	{
		
	}

	CInterval::CInterval(const long long seconds)
	{
		long long t{ ntl::Abs<long long>(seconds) };
		m_iYears = int(t / (365 * 86400));
		t -= m_iYears * 365 * 86400;
		m_iDays = int(t / 86400);
		t -= m_iDays * 86400;
		m_iMonths = 0;
		int days_in_month;
		while (m_iDays > (days_in_month = CDateTime::getDaysInMonth(1, m_iMonths + 1)))
		{
			m_iDays -= days_in_month;
			m_iMonths++;
		}
		m_iHours = int(t / 3600);
		t -= m_iHours * 3600;
		m_iMinutes = int(t / 60);
		m_iSeconds = int(t % 60);
		if (seconds < 0)
		{
			m_iYears = -m_iYears;
			m_iMonths = -m_iMonths;
			m_iDays = -m_iDays;
			m_iHours = -m_iHours;
			m_iMinutes = -m_iMinutes;
			m_iSeconds = -m_iSeconds;
		}
	}
#pragma endregion

#pragma region Getters
	int CInterval::getYears() const
	{
		return m_iYears;
	}

	int CInterval::getMonths() const
	{
		return m_iMonths;
	}

	int CInterval::getDays() const
	{
		return m_iDays;
	}

	int CInterval::getHours() const
	{
		return m_iHours;
	}

	int CInterval::getMinutes() const
	{
		return m_iMinutes;
	}

	int CInterval::getSeconds() const
	{
		return m_iSeconds;
	}
#pragma endregion

#pragma region Setters
	bool CInterval::setYears(const int value)
	{
		if (value != m_iYears)
		{
			m_iYears = value;
			return true;
		}
		return false;
	}

	bool CInterval::setMonths(const int value)
	{
		if (value != m_iMonths)
		{
			m_iMonths = value;
			return true;
		}
		return false;
	}

	bool CInterval::setDays(const int value)
	{
		if (value != m_iDays)
		{
			m_iDays = value;
			return true;
		}
		return false;
	}

	bool CInterval::setHours(const int value)
	{
		if (value != m_iHours)
		{
			m_iHours = value;
			return true;
		}
		return false;
	}

	bool CInterval::setMinutes(const int value)
	{
		if (value != m_iMinutes)
		{
			m_iMinutes = value;
			return true;
		}
		return false;
	}

	bool CInterval::setSeconds(const int value)
	{
		if (value != m_iSeconds)
		{
			m_iSeconds = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Operators
	CInterval::operator long long() const
	{
		int years{ m_iYears }, months{ m_iMonths }, days{ m_iDays }, hours{ m_iHours }, minutes{ m_iMinutes }, seconds{ m_iSeconds };
		Normalize(years, months, days, hours, minutes, seconds);
		long long result{ years * 365 * 86400 };
		for (int i = 0; i < ntl::Abs<int>(months); i++)
			result += CDateTime::getDaysInMonth(1, i + 1) * ntl::Sign<int>(months) * 86400;
		return result + days * 86400 + hours * 3600 + minutes * 60 + seconds;
	}
#pragma endregion

#pragma region Helpers
	void CInterval::Normalize(int &years, int &months, int &days, int &hours, int &minutes, int &seconds) const
	{
		// Adjust seconds
		if (seconds >= 60)
		{
			minutes += seconds / 60;
			seconds %= 60;
		}
		else if (seconds <= -60)
		{
			minutes += seconds / 60;
			seconds = seconds % 60;
		}
		// Adjust minutes
		if (minutes >= 60)
		{
			hours += minutes / 60;
			minutes %= 60;
		}
		else if (minutes <= -60)
		{
			hours += minutes / 60;
			minutes = minutes % 60;
		}
		// Adjust hours
		if (hours >= 24)
		{
			days += hours / 24;
			hours %= 24;
		}
		else if (hours <= -24)
		{
			days += hours / 24;
			hours = hours % 24;
		}
		// Adjust months
		if (months >= 12)
		{
			years += months / 12;
			months %= 12;
		}
		else if (months <= -12)
		{
			years += months / 12;
			months = months % 12;
		}
	}
#pragma endregion
}