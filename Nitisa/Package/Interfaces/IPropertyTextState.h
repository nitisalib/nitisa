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
	class IPropertyTextState :public virtual IPropertyState
	{
	protected:
		IPropertyTextState() = default;
		~IPropertyTextState() = default;
		IPropertyTextState(const IPropertyTextState &other) = delete;
		IPropertyTextState(IPropertyTextState &&other) = delete;
		IPropertyTextState &operator=(const IPropertyTextState &other) = delete;
		IPropertyTextState &operator=(IPropertyTextState &&other) = delete;
	public:
		virtual String getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const String value) = 0; // Set value of state
	};
}