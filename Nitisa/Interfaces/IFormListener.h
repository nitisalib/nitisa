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
	class IForm;

	class IFormListener
	{
	protected:
		IFormListener() = default;
		~IFormListener() = default;
		IFormListener(const IFormListener &other) = delete;
		IFormListener(IFormListener &&other) = delete;
		IFormListener &operator=(const IFormListener &other) = delete;
		IFormListener &operator=(IFormListener &&other) = delete;
	public:
		virtual void OnClose(IForm *sender) = 0; // Called when form has just been closed
		virtual void OnRestore(IForm *sender) = 0; // Called when form has just been restored
		virtual void OnMinimize(IForm *sender) = 0; // Called when form has just been minimized
		virtual void OnMaximize(IForm *sender) = 0; // Called when form has just been maximized
	};
}