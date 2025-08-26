// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyMaskState :public virtual IPropertyState
	{
	protected:
		IPropertyMaskState() = default;
		~IPropertyMaskState() = default;
		IPropertyMaskState(const IPropertyMaskState &other) = delete;
		IPropertyMaskState(IPropertyMaskState &&other) = delete;
		IPropertyMaskState &operator=(const IPropertyMaskState &other) = delete;
		IPropertyMaskState &operator=(IPropertyMaskState &&other) = delete;
	public:
		virtual unsigned int getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const unsigned int value) = 0; // Set value of state
	};
}