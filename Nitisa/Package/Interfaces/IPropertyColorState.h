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
	class IPropertyColorState :public virtual IPropertyState
	{
	protected:
		IPropertyColorState() = default;
		~IPropertyColorState() = default;
		IPropertyColorState(const IPropertyColorState &other) = delete;
		IPropertyColorState(IPropertyColorState &&other) = delete;
		IPropertyColorState &operator=(const IPropertyColorState &other) = delete;
		IPropertyColorState &operator=(IPropertyColorState &&other) = delete;
	public:
		virtual Color getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const Color value) = 0; // Set value of state
	};
}