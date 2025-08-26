// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	class IFeedbackExListener
	{
	protected:
		IFeedbackExListener() = default;
		~IFeedbackExListener() = default;
		IFeedbackExListener(const IFeedbackExListener &other) = delete;
		IFeedbackExListener(IFeedbackExListener &&other) = delete;
		IFeedbackExListener &operator=(const IFeedbackExListener &other) = delete;
		IFeedbackExListener &operator=(IFeedbackExListener &&other) = delete;
	public:
		virtual void NotifyOnBeforeChange() = 0; // Notification is called right before a change
		virtual void NotifyOnBeforeChange(bool &allowed) = 0; // Notification is called right before a change. "allowed" can be set to false to prevent the change
		virtual void NotifyOnAfterChange() = 0; // Notification is called right after a change
	};
}