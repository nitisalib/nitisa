// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/Point.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyPoint :public virtual IProperty
	{
	protected:
		IPropertyPoint() = default;
		~IPropertyPoint() = default;
		IPropertyPoint(const IPropertyPoint &other) = delete;
		IPropertyPoint(IPropertyPoint &&other) = delete;
		IPropertyPoint &operator=(const IPropertyPoint &other) = delete;
		IPropertyPoint &operator=(IPropertyPoint &&other) = delete;
	public:
		virtual Point getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual int getMin() const = 0; // Return minimum limit
		virtual int getMax() const = 0; // Return maximum limit

		virtual bool setValue(const Point value) = 0; // Set value
		virtual IPropertyPoint *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyPoint *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyPoint *setMin(const int value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyPoint *setMax(const int value) = 0; // Set maximum limit and hasMax to true
	};
}