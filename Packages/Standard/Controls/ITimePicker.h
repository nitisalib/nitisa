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
		// Minimum and maximum constraints(hour + minute + second) works together. For example, if MaxHour = 5, MaxMinute = 10 it means the time can be set to any value less or equal to 5h 10m
		class ITimePicker :public virtual IControl
		{
		protected:
			ITimePicker() = default;
			~ITimePicker() = default;
			ITimePicker(const ITimePicker &other) = delete;
			ITimePicker(ITimePicker &&other) = delete;
			ITimePicker &operator=(const ITimePicker &other) = delete;
			ITimePicker &operator=(ITimePicker &&other) = delete;
		public:
			void(*OnChange)(ITimePicker *sender);

			virtual int getHour() = 0; // Return hour
			virtual int getMinute() = 0; // Return minute
			virtual int getSecond() = 0; // Return second
			virtual int getMinHour() = 0; // Return minimum allowed hour
			virtual int getMinMinute() = 0; // Return minimum allowed minute
			virtual int getMinSecond() = 0; // Return minimum allowed second
			virtual int getMaxHour() = 0; // Return maximum allowed hour
			virtual int getMaxMinute() = 0; // Return maximum allowed minute
			virtual int getMaxSecond() = 0; // Return maximum allowed second

			virtual bool setHour(const int value) = 0; // Set hour
			virtual bool setMinute(const int value) = 0; // Set minute
			virtual bool setSecond(const int value) = 0; // Set second
			virtual bool setMinHour(const int value) = 0; // Set minimum allowed hour
			virtual bool setMinMinute(const int value) = 0; // Set minimum allowed minute
			virtual bool setMinSecond(const int value) = 0; // Set minimum allowed second
			virtual bool setMaxHour(const int value) = 0; // Set maximum allowed hour
			virtual bool setMaxMinute(const int value) = 0; // Set maximum allowed minute
			virtual bool setMaxSecond(const int value) = 0; // Set maximum allowed second
		};
	}
}