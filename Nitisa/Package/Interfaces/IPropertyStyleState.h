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
	class IStyle;

	class IPropertyStyleState :public virtual IPropertyState
	{
	protected:
		IPropertyStyleState() = default;
		~IPropertyStyleState() = default;
		IPropertyStyleState(const IPropertyStyleState &other) = delete;
		IPropertyStyleState(IPropertyStyleState &&other) = delete;
		IPropertyStyleState &operator=(const IPropertyStyleState &other) = delete;
		IPropertyStyleState &operator=(IPropertyStyleState &&other) = delete;
	public:
		virtual IStyle *getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, IStyle *value) = 0; // Set value of state
	};
}