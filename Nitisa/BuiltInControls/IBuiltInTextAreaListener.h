// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces//IBuiltInControlListener.h"

namespace nitisa
{
	class IBuiltInControl;

	class IBuiltInTextAreaListener :public virtual IBuiltInControlListener
	{
	protected:
		IBuiltInTextAreaListener() = default;
		~IBuiltInTextAreaListener() = default;
		IBuiltInTextAreaListener(const IBuiltInTextAreaListener &other) = delete;
		IBuiltInTextAreaListener(IBuiltInTextAreaListener &&other) = delete;
		IBuiltInTextAreaListener &operator=(const IBuiltInTextAreaListener &other) = delete;
		IBuiltInTextAreaListener &operator=(IBuiltInTextAreaListener &&other) = delete;
	public:
		virtual void NotifyOnTextChanged(IBuiltInControl *sender) = 0; // Notify about changes in text. Use only this for running updates like scroll availability recalculation. This method is called each time such a change happens in notifications received by the built-in textarea
		virtual void NotifyOnChanged(IBuiltInControl *sender) = 0; // Notify about another changes required to redraw control
	};
}