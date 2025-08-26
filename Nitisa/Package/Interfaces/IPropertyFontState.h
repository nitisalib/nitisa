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
	class IFont;

	class IPropertyFontState :public virtual IPropertyState
	{
	protected:
		IPropertyFontState() = default;
		~IPropertyFontState() = default;
		IPropertyFontState(const IPropertyFontState &other) = delete;
		IPropertyFontState(IPropertyFontState &&other) = delete;
		IPropertyFontState &operator=(const IPropertyFontState &other) = delete;
		IPropertyFontState &operator=(IPropertyFontState &&other) = delete;
	public:
		virtual IFont *getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, IFont *value) = 0; // Set value of state
	};
}