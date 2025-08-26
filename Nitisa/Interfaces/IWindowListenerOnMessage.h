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
	class IWindowListenerOnMessage
	{
	protected:
		IWindowListenerOnMessage() = default;
		~IWindowListenerOnMessage() = default;
		IWindowListenerOnMessage(const IWindowListenerOnMessage &other) = delete;
		IWindowListenerOnMessage(IWindowListenerOnMessage &&other) = delete;
		IWindowListenerOnMessage &operator=(const IWindowListenerOnMessage &other) = delete;
		IWindowListenerOnMessage &operator=(IWindowListenerOnMessage &&other) = delete;
	public:
		virtual bool OnMessage(const unsigned int uMsg, const unsigned long long wParam, const long long lParam, long long &result) = 0; // Called when message was not handled. Should return true and set correct result value if message is handled. Otherwise should return false
	};
}