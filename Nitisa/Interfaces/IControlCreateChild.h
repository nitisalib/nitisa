// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IControl.h"

namespace nitisa
{
	class IControlCreateChild: public virtual IControl
	{
	protected:
		IControlCreateChild() = default;
		~IControlCreateChild() = default;
		IControlCreateChild(const IControlCreateChild &other) = delete;
		IControlCreateChild(IControlCreateChild &&other) = delete;
		IControlCreateChild &operator=(const IControlCreateChild &other) = delete;
		IControlCreateChild &operator=(IControlCreateChild &&other) = delete;
	public:
		virtual IControl *CreateChild() = 0; // Create child control
	};
}