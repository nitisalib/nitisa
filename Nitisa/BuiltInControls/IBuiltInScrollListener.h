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

	class IBuiltInScrollListener :public virtual IBuiltInControlListener
	{
	protected:
		IBuiltInScrollListener() = default;
		~IBuiltInScrollListener() = default;
		IBuiltInScrollListener(const IBuiltInScrollListener &other) = delete;
		IBuiltInScrollListener(IBuiltInScrollListener &&other) = delete;
		IBuiltInScrollListener &operator=(const IBuiltInScrollListener &other) = delete;
		IBuiltInScrollListener &operator=(IBuiltInScrollListener &&other) = delete;
	public:
		virtual void NotifyOnScroll(IBuiltInControl *sender) = 0; // Called when scrolled by timer
	};
}