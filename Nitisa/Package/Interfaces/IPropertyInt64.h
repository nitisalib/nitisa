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
	class IPropertyInt64 :public virtual IProperty
	{
	protected:
		IPropertyInt64() = default;
		~IPropertyInt64() = default;
		IPropertyInt64(const IPropertyInt64 &other) = delete;
		IPropertyInt64(IPropertyInt64 &&other) = delete;
		IPropertyInt64 &operator=(const IPropertyInt64 &other) = delete;
		IPropertyInt64 &operator=(IPropertyInt64 &&other) = delete;
	public:
		virtual long long getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual long long getMin() const = 0; // Return minimum limit
		virtual long long getMax() const = 0; // Return maximum limit

		virtual bool setValue(const long long value) = 0; // Set value
		virtual IPropertyInt64 *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyInt64 *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyInt64 *setMin(const long long value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyInt64 *setMax(const long long value) = 0; // Set maximum limit and hasMax to true
	};
}