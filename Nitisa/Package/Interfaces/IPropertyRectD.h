// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/RectD.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyRectD :public virtual IProperty
	{
	protected:
		IPropertyRectD() = default;
		~IPropertyRectD() = default;
		IPropertyRectD(const IPropertyRectD &other) = delete;
		IPropertyRectD(IPropertyRectD &&other) = delete;
		IPropertyRectD &operator=(const IPropertyRectD &other) = delete;
		IPropertyRectD &operator=(IPropertyRectD &&other) = delete;
	public:
		virtual RectD getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual bool isAllowEmpty() const = 0; // Whether empty rectangle is allowed or not
		virtual bool isAllowInvalid() const = 0; // Whether invalid rectangle is allowed or not
		virtual double getMin() const = 0; // Return minimum limit
		virtual double getMax() const = 0; // Return maximum limit

		virtual bool setValue(const RectD value) = 0; // Set value
		virtual IPropertyRectD *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyRectD *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyRectD *setAllowEmpty(const bool value) = 0; // Set whether empty rectangle is allowed or not
		virtual IPropertyRectD *setAllowInvalid(const bool value) = 0; // Set whether invalid rectangle is allowed or not
		virtual IPropertyRectD *setMin(const double value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyRectD *setMax(const double value) = 0; // Set maximum limit and hasMax to true
	};
}