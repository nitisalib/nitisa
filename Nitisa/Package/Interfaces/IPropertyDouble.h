// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IProperty.h"

namespace nitisa
{
	class IPropertyDouble :public virtual IProperty
	{
	protected:
		IPropertyDouble() = default;
		~IPropertyDouble() = default;
		IPropertyDouble(const IPropertyDouble &other) = delete;
		IPropertyDouble(IPropertyDouble &&other) = delete;
		IPropertyDouble &operator=(const IPropertyDouble &other) = delete;
		IPropertyDouble &operator=(IPropertyDouble &&other) = delete;
	public:
		virtual double getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual double getMin() const = 0; // Return minimum limit
		virtual double getMax() const = 0; // Return maximum limit

		virtual bool setValue(const double value) = 0; // Set value
		virtual IPropertyDouble *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyDouble *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyDouble *setMin(const double value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyDouble *setMax(const double value) = 0; // Set maximum limit and hasMax to true
	};
}