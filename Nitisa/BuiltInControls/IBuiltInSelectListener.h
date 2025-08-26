// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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

	class IBuiltInSelectListener :public virtual IBuiltInControlListener
	{
	protected:
		IBuiltInSelectListener() = default;
		~IBuiltInSelectListener() = default;
		IBuiltInSelectListener(const IBuiltInSelectListener &other) = delete;
		IBuiltInSelectListener(IBuiltInSelectListener &&other) = delete;
		IBuiltInSelectListener &operator=(const IBuiltInSelectListener &other) = delete;
		IBuiltInSelectListener &operator=(IBuiltInSelectListener &&other) = delete;
	public:
		virtual void NotifyOnFilterChange(IBuiltInControl *sender) = 0; // Notify about filter change
		virtual void NotifyOnSelect(IBuiltInControl *sender, const int index) = 0; // Notify when user selects other item
		virtual void NotifyOnOpen(IBuiltInControl *sender) = 0; // Notify when dropdown becomes opened
		virtual void NotifyOnClose(IBuiltInControl *sender) = 0; // Notify when dropdown becomes closed
	};
}