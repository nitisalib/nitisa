// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/PointL.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyPointL :public virtual IProperty
	{
	protected:
		IPropertyPointL() = default;
		~IPropertyPointL() = default;
		IPropertyPointL(const IPropertyPointL &other) = delete;
		IPropertyPointL(IPropertyPointL &&other) = delete;
		IPropertyPointL &operator=(const IPropertyPointL &other) = delete;
		IPropertyPointL &operator=(IPropertyPointL &&other) = delete;
	public:
		virtual PointL getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual long long getMin() const = 0; // Return minimum limit
		virtual long long getMax() const = 0; // Return maximum limit

		virtual bool setValue(const PointL value) = 0; // Set value
		virtual IPropertyPointL *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyPointL *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyPointL *setMin(const long long value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyPointL *setMax(const long long value) = 0; // Set maximum limit and hasMax to true
	};
}