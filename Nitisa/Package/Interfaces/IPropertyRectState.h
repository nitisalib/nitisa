// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/Rect.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyRectState :public virtual IPropertyState
	{
	protected:
		IPropertyRectState() = default;
		~IPropertyRectState() = default;
		IPropertyRectState(const IPropertyRectState &other) = delete;
		IPropertyRectState(IPropertyRectState &&other) = delete;
		IPropertyRectState &operator=(const IPropertyRectState &other) = delete;
		IPropertyRectState &operator=(IPropertyRectState &&other) = delete;
	public:
		virtual Rect getValue(const String &state) = 0; // Return value depending on state
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual bool isAllowEmpty() const = 0; // Whether empty rectangle is allowed or not
		virtual bool isAllowInvalid() const = 0; // Whether invalid rectangle is allowed or not
		virtual int getMin() const = 0; // Return minimum limit
		virtual int getMax() const = 0; // Return maximum limit

		virtual bool setValue(const String &state, const Rect value) = 0; // Set value of state
		virtual IPropertyRectState *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyRectState *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyRectState *setAllowEmpty(const bool value) = 0; // Set whether empty rectangle is allowed or not
		virtual IPropertyRectState *setAllowInvalid(const bool value) = 0; // Set whether invalid rectangle is allowed or not
		virtual IPropertyRectState *setMin(const int value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyRectState *setMax(const int value) = 0; // Set maximum limit and hasMax to true
	};
}