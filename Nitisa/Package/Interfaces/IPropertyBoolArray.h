// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/BoolArray.h"
#include "IProperty.h"
#include <vector>

namespace nitisa
{
	class IPropertyBoolArray :public virtual IProperty
	{
	protected:
		IPropertyBoolArray() = default;
		~IPropertyBoolArray() = default;
		IPropertyBoolArray(const IPropertyBoolArray &other) = delete;
		IPropertyBoolArray(IPropertyBoolArray &&other) = delete;
		IPropertyBoolArray &operator=(const IPropertyBoolArray &other) = delete;
		IPropertyBoolArray &operator=(IPropertyBoolArray &&other) = delete;
	public:
		virtual BoolArray getValue() = 0; // Return value
		virtual int getMinCount() = 0; // Return minimum allowed item count in array

		virtual bool setValue(const BoolArray value) = 0; // Set value
		virtual IPropertyBoolArray *setMinCount(const int value) = 0; // Set minimum allowed item count in array
	};
}