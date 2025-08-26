// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/FloatArray.h"
#include "IPropertyState.h"
#include <vector>

namespace nitisa
{
	class IPropertyFloatArrayState :public virtual IPropertyState
	{
	protected:
		IPropertyFloatArrayState() = default;
		~IPropertyFloatArrayState() = default;
		IPropertyFloatArrayState(const IPropertyFloatArrayState &other) = delete;
		IPropertyFloatArrayState(IPropertyFloatArrayState &&other) = delete;
		IPropertyFloatArrayState &operator=(const IPropertyFloatArrayState &other) = delete;
		IPropertyFloatArrayState &operator=(IPropertyFloatArrayState &&other) = delete;
	public:
		virtual FloatArray getValue(const String &state) = 0; // Return value depending on state
		virtual int getMinCount() = 0; // Return minimum allowed item count in array
		virtual bool hasMin() = 0; // Whether has minimum limit
		virtual bool hasMax() = 0; // Whether has maximum limit
		virtual float getMin() = 0; // Return minimum limit
		virtual float getMax() = 0; // Return maximum limit

		virtual bool setValue(const String &state, const FloatArray value) = 0; // Set value of state
		virtual IPropertyFloatArrayState *setMinCount(const int value) = 0; // Set minimum allowed item count in array
		virtual IPropertyFloatArrayState *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyFloatArrayState *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyFloatArrayState *setMin(const float value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyFloatArrayState *setMax(const float value) = 0; // Set maximum limit and hasMax to true
	};
}