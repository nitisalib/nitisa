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

	class IBuiltInTextInputListener :public virtual IBuiltInControlListener
	{
	protected:
		IBuiltInTextInputListener() = default;
		~IBuiltInTextInputListener() = default;
		IBuiltInTextInputListener(const IBuiltInTextInputListener &other) = delete;
		IBuiltInTextInputListener(IBuiltInTextInputListener &&other) = delete;
		IBuiltInTextInputListener &operator=(const IBuiltInTextInputListener &other) = delete;
		IBuiltInTextInputListener &operator=(IBuiltInTextInputListener &&other) = delete;
	public:
		virtual void NotifyOnTextChanged(IBuiltInControl *sender) = 0; // Notify about changes in text
	};
}