// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IBuiltInControlListener.h"

namespace nitisa
{
	class IBuiltInControl;

	class IBuiltInMonthCalendarListener :public virtual IBuiltInControlListener
	{
	protected:
		IBuiltInMonthCalendarListener() = default;
		~IBuiltInMonthCalendarListener() = default;
		IBuiltInMonthCalendarListener(const IBuiltInMonthCalendarListener &other) = delete;
		IBuiltInMonthCalendarListener(IBuiltInMonthCalendarListener &&other) = delete;
		IBuiltInMonthCalendarListener &operator=(const IBuiltInMonthCalendarListener &other) = delete;
		IBuiltInMonthCalendarListener &operator=(IBuiltInMonthCalendarListener &&other) = delete;
	public:
		virtual void NotifyOnChange(IBuiltInControl *sender) = 0; // Notification called when new date becomes active
	};
}