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
	class IPropertyInteger :public virtual IProperty
	{
	protected:
		IPropertyInteger() = default;
		~IPropertyInteger() = default;
		IPropertyInteger(const IPropertyInteger &other) = delete;
		IPropertyInteger(IPropertyInteger &&other) = delete;
		IPropertyInteger &operator=(const IPropertyInteger &other) = delete;
		IPropertyInteger &operator=(IPropertyInteger &&other) = delete;
	public:
		virtual int getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual int getMin() const = 0; // Return minimum limit
		virtual int getMax() const = 0; // Return maximum limit

		virtual bool setValue(const int value) = 0; // Set value
		virtual IPropertyInteger *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyInteger *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyInteger *setMin(const int value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyInteger *setMax(const int value) = 0; // Set maximum limit and hasMax to true
	};
}