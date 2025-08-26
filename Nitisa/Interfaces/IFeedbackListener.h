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
	class IFeedbackListener
	{
	protected:
		IFeedbackListener() = default;
		~IFeedbackListener() = default;
		IFeedbackListener(const IFeedbackListener &other) = delete;
		IFeedbackListener(IFeedbackListener &&other) = delete;
		IFeedbackListener &operator=(const IFeedbackListener &other) = delete;
		IFeedbackListener &operator=(IFeedbackListener &&other) = delete;
	public:
		virtual void NotifyOnChange() = 0; // Notification is called right before a change
	};
}