// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		// Minimum and maximum constraints(year + month + day) works together. For example, if MaxYear = 2000, MaxMonth = February, MaxDay = 5 it means the date can be set to any value less or equal to 2000-02-05
		class IDatePicker :public virtual IControl
		{
		protected:
			IDatePicker() = default;
			~IDatePicker() = default;
			IDatePicker(const IDatePicker &other) = delete;
			IDatePicker(IDatePicker &&other) = delete;
			IDatePicker &operator=(const IDatePicker &other) = delete;
			IDatePicker &operator=(IDatePicker &&other) = delete;
		public:
			void(*OnChange)(IDatePicker *sender); // Event called when new date is activated

			virtual int getYear() = 0; // Return year
			virtual int getMonth() = 0; // Return month
			virtual int getDay() = 0; // Return day
			virtual int getMinYear() = 0; // Return minimum allowed year
			virtual int getMinMonth() = 0; // Return minimum allowed month
			virtual int getMinDay() = 0; // Return minimum allowed day
			virtual int getMaxYear() = 0; // Return maximum allowed year
			virtual int getMaxMonth() = 0; // Return maximum allowed month
			virtual int getMaxDay() = 0; // Return maximum allowed day

			virtual bool setYear(const int value) = 0; // Set year
			virtual bool setMonth(const int value) = 0; // Set month
			virtual bool setDay(const int value) = 0; // Set day
			virtual bool setMinYear(const int value) = 0; // Set minimum allowed year
			virtual bool setMinMonth(const int value) = 0; // Set minimum allowed month
			virtual bool setMinDay(const int value) = 0; // Set minimum allowed day
			virtual bool setMaxYear(const int value) = 0; // Set maximum allowed year
			virtual bool setMaxMonth(const int value) = 0; // Set maximum allowed month
			virtual bool setMaxDay(const int value) = 0; // Set maximum allowed day
		};
	}
}