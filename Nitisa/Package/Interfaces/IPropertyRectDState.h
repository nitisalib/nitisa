// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/RectD.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyRectDState :public virtual IPropertyState
	{
	protected:
		IPropertyRectDState() = default;
		~IPropertyRectDState() = default;
		IPropertyRectDState(const IPropertyRectDState &other) = delete;
		IPropertyRectDState(IPropertyRectDState &&other) = delete;
		IPropertyRectDState &operator=(const IPropertyRectDState &other) = delete;
		IPropertyRectDState &operator=(IPropertyRectDState &&other) = delete;
	public:
		virtual RectD getValue(const String &state) = 0; // Return value depending on state
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual bool isAllowEmpty() const = 0; // Whether empty rectangle is allowed or not
		virtual bool isAllowInvalid() const = 0; // Whether invalid rectangle is allowed or not
		virtual double getMin() const = 0; // Return minimum limit
		virtual double getMax() const = 0; // Return maximum limit

		virtual bool setValue(const String &state, const RectD value) = 0; // Set value of state
		virtual IPropertyRectDState *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyRectDState *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyRectDState *setAllowEmpty(const bool value) = 0; // Set whether empty rectangle is allowed or not
		virtual IPropertyRectDState *setAllowInvalid(const bool value) = 0; // Set whether invalid rectangle is allowed or not
		virtual IPropertyRectDState *setMin(const double value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyRectDState *setMax(const double value) = 0; // Set maximum limit and hasMax to true
	};
}