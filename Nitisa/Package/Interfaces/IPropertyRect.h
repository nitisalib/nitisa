// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/Rect.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyRect :public virtual IProperty
	{
	protected:
		IPropertyRect() = default;
		~IPropertyRect() = default;
		IPropertyRect(const IPropertyRect &other) = delete;
		IPropertyRect(IPropertyRect &&other) = delete;
		IPropertyRect &operator=(const IPropertyRect &other) = delete;
		IPropertyRect &operator=(IPropertyRect &&other) = delete;
	public:
		virtual Rect getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual bool isAllowEmpty() const = 0; // Whether empty rectangle is allowed or not
		virtual bool isAllowInvalid() const = 0; // Whether invalid rectangle is allowed or not
		virtual int getMin() const = 0; // Return minimum limit
		virtual int getMax() const = 0; // Return maximum limit

		virtual bool setValue(const Rect value) = 0; // Set value
		virtual IPropertyRect *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyRect *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyRect *setAllowEmpty(const bool value) = 0; // Set whether empty rectangle is allowed or not
		virtual IPropertyRect *setAllowInvalid(const bool value) = 0; // Set whether invalid rectangle is allowed or not
		virtual IPropertyRect *setMin(const int value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyRect *setMax(const int value) = 0; // Set maximum limit and hasMax to true
	};
}