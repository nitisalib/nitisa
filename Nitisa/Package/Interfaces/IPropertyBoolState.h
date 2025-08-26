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
	class IPropertyBoolState :public virtual IPropertyState
	{
	protected:
		IPropertyBoolState() = default;
		~IPropertyBoolState() = default;
		IPropertyBoolState(const IPropertyBoolState &other) = delete;
		IPropertyBoolState(IPropertyBoolState &&other) = delete;
		IPropertyBoolState &operator=(const IPropertyBoolState &other) = delete;
		IPropertyBoolState &operator=(IPropertyBoolState &&other) = delete;
	public:
		virtual bool getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const bool value) = 0; // Set value of state
	};
}