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

	class IBuiltInDropDownListener :public virtual IBuiltInControlListener
	{
	protected:
		IBuiltInDropDownListener() = default;
		~IBuiltInDropDownListener() = default;
		IBuiltInDropDownListener(const IBuiltInDropDownListener &other) = delete;
		IBuiltInDropDownListener(IBuiltInDropDownListener &&other) = delete;
		IBuiltInDropDownListener &operator=(const IBuiltInDropDownListener &other) = delete;
		IBuiltInDropDownListener &operator=(IBuiltInDropDownListener &&other) = delete;
	public:
		virtual void NotifyOnTextChange(IBuiltInControl *sender) = 0; // Notify about text change
		virtual void NotifyOnSelect(IBuiltInControl *sender, const int index) = 0; // Notify when user selects other item
		virtual void NotifyOnOpen(IBuiltInControl *sender) = 0; // Notify when dropdown becomes opened
		virtual void NotifyOnClose(IBuiltInControl *sender) = 0; // Notify when dropdown becomes closed
	};
}