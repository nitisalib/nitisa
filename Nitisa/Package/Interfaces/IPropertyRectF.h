// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/RectF.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyRectF :public virtual IProperty
	{
	protected:
		IPropertyRectF() = default;
		~IPropertyRectF() = default;
		IPropertyRectF(const IPropertyRectF &other) = delete;
		IPropertyRectF(IPropertyRectF &&other) = delete;
		IPropertyRectF &operator=(const IPropertyRectF &other) = delete;
		IPropertyRectF &operator=(IPropertyRectF &&other) = delete;
	public:
		virtual RectF getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual bool isAllowEmpty() const = 0; // Whether empty rectangle is allowed or not
		virtual bool isAllowInvalid() const = 0; // Whether invalid rectangle is allowed or not
		virtual float getMin() const = 0; // Return minimum limit
		virtual float getMax() const = 0; // Return maximum limit

		virtual bool setValue(const RectF value) = 0; // Set value
		virtual IPropertyRectF *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyRectF *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyRectF *setAllowEmpty(const bool value) = 0; // Set whether empty rectangle is allowed or not
		virtual IPropertyRectF *setAllowInvalid(const bool value) = 0; // Set whether invalid rectangle is allowed or not
		virtual IPropertyRectF *setMin(const float value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyRectF *setMax(const float value) = 0; // Set maximum limit and hasMax to true
	};
}