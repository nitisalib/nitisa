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
	class IPropertyDoubleState :public virtual IPropertyState
	{
	protected:
		IPropertyDoubleState() = default;
		~IPropertyDoubleState() = default;
		IPropertyDoubleState(const IPropertyDoubleState &other) = delete;
		IPropertyDoubleState(IPropertyDoubleState &&other) = delete;
		IPropertyDoubleState &operator=(const IPropertyDoubleState &other) = delete;
		IPropertyDoubleState &operator=(IPropertyDoubleState &&other) = delete;
	public:
		virtual double getValue(const String &state) = 0; // Return value depending on state
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual double getMin() const = 0; // Return minimum limit
		virtual double getMax() const = 0; // Return maximum limit

		virtual bool setValue(const String &state, const double value) = 0; // Set value of state
		virtual IPropertyDoubleState *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyDoubleState *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyDoubleState *setMin(const double value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyDoubleState *setMax(const double value) = 0; // Set maximum limit and hasMax to true
	};
}