// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/FloatArray.h"
#include "IProperty.h"
#include <vector>

namespace nitisa
{
	class IPropertyFloatArray :public virtual IProperty
	{
	protected:
		IPropertyFloatArray() = default;
		~IPropertyFloatArray() = default;
		IPropertyFloatArray(const IPropertyFloatArray &other) = delete;
		IPropertyFloatArray(IPropertyFloatArray &&other) = delete;
		IPropertyFloatArray &operator=(const IPropertyFloatArray &other) = delete;
		IPropertyFloatArray &operator=(IPropertyFloatArray &&other) = delete;
	public:
		virtual FloatArray getValue() = 0; // Return value
		virtual int getMinCount() = 0; // Return minimum allowed item count in array
		virtual bool hasMin() = 0; // Whether has minimum limit
		virtual bool hasMax() = 0; // Whether has maximum limit
		virtual float getMin() = 0; // Return minimum limit
		virtual float getMax() = 0; // Return maximum limit

		virtual bool setValue(const FloatArray value) = 0; // Set value
		virtual IPropertyFloatArray *setMinCount(const int value) = 0; // Set minimum allowed item count in array
		virtual IPropertyFloatArray *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyFloatArray *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyFloatArray *setMin(const float value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyFloatArray *setMax(const float value) = 0; // Set maximum limit and hasMax to true
	};
}