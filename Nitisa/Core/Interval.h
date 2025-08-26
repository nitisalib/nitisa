// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	class CInterval
	{
	private:
		int m_iYears;
		int m_iMonths;
		int m_iDays;
		int m_iHours;
		int m_iMinutes;
		int m_iSeconds;

		void Normalize(int &years, int &months, int &days, int &hours, int &minutes, int &seconds) const;
	public:
		CInterval(); // Create empty interval
		CInterval(const int years, const int months, const int days, const int hours, const int minutes, const int seconds); // Create interval with specified parameters
		CInterval(const long long seconds); // Create interval with specified number of seconds
		CInterval(const CInterval &other) = default;
		CInterval(CInterval &&other) = default;

		int getYears() const; // Return years
		int getMonths() const; // Return months
		int getDays() const; // Return days
		int getHours() const; // Return hours
		int getMinutes() const; // Return minutes
		int getSeconds() const; // Return seconds

		bool setYears(const int value); // Set years
		bool setMonths(const int value); // Set months
		bool setDays(const int value); // Set days
		bool setHours(const int value); // Set hours
		bool setMinutes(const int value); // Set minutes
		bool setSeconds(const int value); // Set seconds

		CInterval &operator=(const CInterval &other) = default;
		CInterval &operator=(CInterval &&other) = default;

		explicit operator long long() const; // Convert to time interval in seconds
	};
}