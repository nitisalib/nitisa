// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
namespace nitisa
{
	class ITimerListener
	{
	protected:
		ITimerListener() = default;
		~ITimerListener() = default;
		ITimerListener(const ITimerListener &other) = delete;
		ITimerListener(ITimerListener &&other) = delete;
		ITimerListener &operator=(const ITimerListener &other) = delete;
		ITimerListener &operator=(ITimerListener &&other) = delete;
	public:
		virtual void NotifyOnTimer(const PlatformHandle id) = 0; // Notification is called when time elapsed
	};
}