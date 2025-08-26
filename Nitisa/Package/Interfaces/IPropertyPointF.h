// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/PointF.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyPointF :public virtual IProperty
	{
	protected:
		IPropertyPointF() = default;
		~IPropertyPointF() = default;
		IPropertyPointF(const IPropertyPointF &other) = delete;
		IPropertyPointF(IPropertyPointF &&other) = delete;
		IPropertyPointF &operator=(const IPropertyPointF &other) = delete;
		IPropertyPointF &operator=(IPropertyPointF &&other) = delete;
	public:
		virtual PointF getValue() = 0; // Return value
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual float getMin() const = 0; // Return minimum limit
		virtual float getMax() const = 0; // Return maximum limit

		virtual bool setValue(const PointF value) = 0; // Set value
		virtual IPropertyPointF *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyPointF *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyPointF *setMin(const float value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyPointF *setMax(const float value) = 0; // Set maximum limit and hasMax to true
	};
}