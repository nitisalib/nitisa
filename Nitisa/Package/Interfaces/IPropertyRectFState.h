// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/RectF.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyRectFState :public virtual IPropertyState
	{
	protected:
		IPropertyRectFState() = default;
		~IPropertyRectFState() = default;
		IPropertyRectFState(const IPropertyRectFState &other) = delete;
		IPropertyRectFState(IPropertyRectFState &&other) = delete;
		IPropertyRectFState &operator=(const IPropertyRectFState &other) = delete;
		IPropertyRectFState &operator=(IPropertyRectFState &&other) = delete;
	public:
		virtual RectF getValue(const String &state) = 0; // Return value depending on state
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual bool isAllowEmpty() const = 0; // Whether empty rectangle is allowed or not
		virtual bool isAllowInvalid() const = 0; // Whether invalid rectangle is allowed or not
		virtual float getMin() const = 0; // Return minimum limit
		virtual float getMax() const = 0; // Return maximum limit

		virtual bool setValue(const String &state, const RectF value) = 0; // Set value of state
		virtual IPropertyRectFState *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyRectFState *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyRectFState *setAllowEmpty(const bool value) = 0; // Set whether empty rectangle is allowed or not
		virtual IPropertyRectFState *setAllowInvalid(const bool value) = 0; // Set whether invalid rectangle is allowed or not
		virtual IPropertyRectFState *setMin(const float value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyRectFState *setMax(const float value) = 0; // Set maximum limit and hasMax to true
	};
}