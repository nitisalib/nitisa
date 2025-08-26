// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/PointD.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyPointD :public virtual IProperty
	{
	protected:
		IPropertyPointD() = default;
		~IPropertyPointD() = default;
		IPropertyPointD(const IPropertyPointD &other) = delete;
		IPropertyPointD(IPropertyPointD &&other) = delete;
		IPropertyPointD &operator=(const IPropertyPointD &other) = delete;
		IPropertyPointD &operator=(IPropertyPointD &&other) = delete;
	public:
		virtual PointD getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual double getMin() const = 0; // Return minimum limit
		virtual double getMax() const = 0; // Return maximum limit

		virtual bool setValue(const PointD value) = 0; // Set value
		virtual IPropertyPointD *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyPointD *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyPointD *setMin(const double value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyPointD *setMax(const double value) = 0; // Set maximum limit and hasMax to true
	};
}