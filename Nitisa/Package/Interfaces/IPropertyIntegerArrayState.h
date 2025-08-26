// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/IntegerArray.h"
#include "IPropertyState.h"
#include <vector>

namespace nitisa
{
	class IPropertyIntegerArrayState :public virtual IPropertyState
	{
	protected:
		IPropertyIntegerArrayState() = default;
		~IPropertyIntegerArrayState() = default;
		IPropertyIntegerArrayState(const IPropertyIntegerArrayState &other) = delete;
		IPropertyIntegerArrayState(IPropertyIntegerArrayState &&other) = delete;
		IPropertyIntegerArrayState &operator=(const IPropertyIntegerArrayState &other) = delete;
		IPropertyIntegerArrayState &operator=(IPropertyIntegerArrayState &&other) = delete;
	public:
		virtual IntegerArray getValue(const String &state) = 0; // Return value depending on state
		virtual int getMinCount() = 0; // Return minimum allowed item count in array
		virtual bool hasMin() = 0; // Whether has minimum limit
		virtual bool hasMax() = 0; // Whether has maximum limit
		virtual int getMin() = 0; // Return minimum limit
		virtual int getMax() = 0; // Return maximum limit

		virtual bool setValue(const String &state, const IntegerArray value) = 0; // Set value of state
		virtual IPropertyIntegerArrayState *setMinCount(const int value) = 0; // Set minimum allowed item count in array
		virtual IPropertyIntegerArrayState *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyIntegerArrayState *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyIntegerArrayState *setMin(const int value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyIntegerArrayState *setMax(const int value) = 0; // Set maximum limit and hasMax to true
	};
}