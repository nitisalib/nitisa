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
	class IPropertyInt64State :public virtual IPropertyState
	{
	protected:
		IPropertyInt64State() = default;
		~IPropertyInt64State() = default;
		IPropertyInt64State(const IPropertyInt64State &other) = delete;
		IPropertyInt64State(IPropertyInt64State &&other) = delete;
		IPropertyInt64State &operator=(const IPropertyInt64State &other) = delete;
		IPropertyInt64State &operator=(IPropertyInt64State &&other) = delete;
	public:
		virtual long long getValue(const String &state) = 0; // Return value depending on state
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual long long getMin() const = 0; // Return minimum limit
		virtual long long getMax() const = 0; // Return maximum limit

		virtual bool setValue(const String &state, const long long value) = 0; // Set value of state
		virtual IPropertyInt64State *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyInt64State *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyInt64State *setMin(const long long value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyInt64State *setMax(const long long value) = 0; // Set maximum limit and hasMax to true
	};
}