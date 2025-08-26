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
	class IPropertyFloat :public virtual IProperty
	{
	protected:
		IPropertyFloat() = default;
		~IPropertyFloat() = default;
		IPropertyFloat(const IPropertyFloat &other) = delete;
		IPropertyFloat(IPropertyFloat &&other) = delete;
		IPropertyFloat &operator=(const IPropertyFloat &other) = delete;
		IPropertyFloat &operator=(IPropertyFloat &&other) = delete;
	public:
		virtual float getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual float getMin() const = 0; // Return minimum limit
		virtual float getMax() const = 0; // Return maximum limit

		virtual bool setValue(const float value) = 0; // Set value
		virtual IPropertyFloat *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyFloat *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyFloat *setMin(const float value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyFloat *setMax(const float value) = 0; // Set maximum limit and hasMax to true
	};
}