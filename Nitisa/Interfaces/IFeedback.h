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
	class IFeedbackListener;

	class IFeedback
	{
	protected:
		IFeedbackListener *m_pListener;
	protected:
		IFeedback() = default;
		~IFeedback() = default;
		IFeedback(const IFeedback &other) = delete;
		IFeedback(IFeedback &&other) = delete;
		IFeedback &operator=(const IFeedback &other) = delete;
		IFeedback &operator=(IFeedback &&other) = delete;
	public:
		IFeedbackListener* const &Listener{ m_pListener }; // Assigned listener

		virtual bool setListener(IFeedbackListener *listener) = 0; // Assign new listener
	};
}