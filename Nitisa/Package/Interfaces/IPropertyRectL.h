// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/RectL.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyRectL :public virtual IProperty
	{
	protected:
		IPropertyRectL() = default;
		~IPropertyRectL() = default;
		IPropertyRectL(const IPropertyRectL &other) = delete;
		IPropertyRectL(IPropertyRectL &&other) = delete;
		IPropertyRectL &operator=(const IPropertyRectL &other) = delete;
		IPropertyRectL &operator=(IPropertyRectL &&other) = delete;
	public:
		virtual RectL getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual bool isAllowEmpty() const = 0; // Whether empty rectangle is allowed or not
		virtual bool isAllowInvalid() const = 0; // Whether invalid rectangle is allowed or not
		virtual long long getMin() const = 0; // Return minimum limit
		virtual long long getMax() const = 0; // Return maximum limit

		virtual bool setValue(const RectL value) = 0; // Set value
		virtual IPropertyRectL *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyRectL *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyRectL *setAllowEmpty(const bool value) = 0; // Set whether empty rectangle is allowed or not
		virtual IPropertyRectL *setAllowInvalid(const bool value) = 0; // Set whether invalid rectangle is allowed or not
		virtual IPropertyRectL *setMin(const long long value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyRectL *setMax(const long long value) = 0; // Set maximum limit and hasMax to true
	};
}