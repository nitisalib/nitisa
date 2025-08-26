// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Image/BorderColor.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyBorderColorState :public virtual IPropertyState
	{
	protected:
		IPropertyBorderColorState() = default;
		~IPropertyBorderColorState() = default;
		IPropertyBorderColorState(const IPropertyBorderColorState &other) = delete;
		IPropertyBorderColorState(IPropertyBorderColorState &&other) = delete;
		IPropertyBorderColorState &operator=(const IPropertyBorderColorState &other) = delete;
		IPropertyBorderColorState &operator=(IPropertyBorderColorState &&other) = delete;
	public:
		virtual BorderColor getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const BorderColor value) = 0; // Set value of state
	};
}