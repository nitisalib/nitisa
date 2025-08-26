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
	class IDialogBox;

	class IDialogBoxListener
	{
	protected:
		IDialogBoxListener() = default;
		~IDialogBoxListener() = default;
		IDialogBoxListener(const IDialogBoxListener &other) = delete;
		IDialogBoxListener(IDialogBoxListener &&other) = delete;
		IDialogBoxListener &operator=(const IDialogBoxListener &other) = delete;
		IDialogBoxListener &operator=(IDialogBoxListener &&other) = delete;
	public:
		virtual void OnClose(IDialogBox *sender) = 0; // Called when dialog box has just been closed
		virtual void OnRestore(IDialogBox *sender) = 0; // Called when dialog box has just been restored
		virtual void OnMinimize(IDialogBox *sender) = 0; // Called when dialog box has just been minimized
		virtual void OnMaximize(IDialogBox *sender) = 0; // Called when dialog box has just been maximized
	};
}