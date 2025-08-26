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
	class IPropertyIntegerState :public virtual IPropertyState
	{
	protected:
		IPropertyIntegerState() = default;
		~IPropertyIntegerState() = default;
		IPropertyIntegerState(const IPropertyIntegerState &other) = delete;
		IPropertyIntegerState(IPropertyIntegerState &&other) = delete;
		IPropertyIntegerState &operator=(const IPropertyIntegerState &other) = delete;
		IPropertyIntegerState &operator=(IPropertyIntegerState &&other) = delete;
	public:
		virtual int getValue(const String &state) = 0; // Return value depending on state
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual int getMin() const = 0; // Return minimum limit
		virtual int getMax() const = 0; // Return maximum limit

		virtual bool setValue(const String &state, const int value) = 0; // Set value of state
		virtual IPropertyIntegerState *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyIntegerState *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyIntegerState *setMin(const int value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyIntegerState *setMax(const int value) = 0; // Set maximum limit and hasMax to true
	};
}