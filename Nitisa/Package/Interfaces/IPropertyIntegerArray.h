// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/IntegerArray.h"
#include "IProperty.h"
#include <vector>

namespace nitisa
{
	class IPropertyIntegerArray :public virtual IProperty
	{
	protected:
		IPropertyIntegerArray() = default;
		~IPropertyIntegerArray() = default;
		IPropertyIntegerArray(const IPropertyIntegerArray &other) = delete;
		IPropertyIntegerArray(IPropertyIntegerArray &&other) = delete;
		IPropertyIntegerArray &operator=(const IPropertyIntegerArray &other) = delete;
		IPropertyIntegerArray &operator=(IPropertyIntegerArray &&other) = delete;
	public:
		virtual IntegerArray getValue() = 0; // Return value
		virtual int getMinCount() = 0; // Return minimum allowed item count in array
		virtual bool hasMin() = 0; // Whether has minimum limit
		virtual bool hasMax() = 0; // Whether has maximum limit
		virtual int getMin() = 0; // Return minimum limit
		virtual int getMax() = 0; // Return maximum limit

		virtual bool setValue(const IntegerArray value) = 0; // Set value
		virtual IPropertyIntegerArray *setMinCount(const int value) = 0; // Set minimum allowed item count in array
		virtual IPropertyIntegerArray *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyIntegerArray *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyIntegerArray *setMin(const int value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyIntegerArray *setMax(const int value) = 0; // Set maximum limit and hasMax to true
	};
}