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
	class IFeedbackExListener;

	class IFeedbackEx
	{
	protected:
		IFeedbackExListener *m_pListener;
	protected:
		IFeedbackEx() = default;
		~IFeedbackEx() = default;
		IFeedbackEx(const IFeedbackEx &other) = delete;
		IFeedbackEx(IFeedbackEx &&other) = delete;
		IFeedbackEx &operator=(const IFeedbackEx &other) = delete;
		IFeedbackEx &operator=(IFeedbackEx &&other) = delete;
	public:
		IFeedbackExListener* const &Listener{ m_pListener }; // Assigned listener

		virtual bool setListener(IFeedbackExListener *listener) = 0; // Assign new listener
	};
}