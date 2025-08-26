// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Image/ColorArray.h"
#include "IProperty.h"
#include <vector>

namespace nitisa
{
	class IPropertyColorArray :public virtual IProperty
	{
	protected:
		IPropertyColorArray() = default;
		~IPropertyColorArray() = default;
		IPropertyColorArray(const IPropertyColorArray &other) = delete;
		IPropertyColorArray(IPropertyColorArray &&other) = delete;
		IPropertyColorArray &operator=(const IPropertyColorArray &other) = delete;
		IPropertyColorArray &operator=(IPropertyColorArray &&other) = delete;
	public:
		virtual ColorArray getValue() = 0; // Return value
		virtual int getMinCount() = 0; // Return minimum allowed item count in array

		virtual bool setValue(const ColorArray values) = 0; // Set value
		virtual IPropertyColorArray *setMinCount(const int value) = 0; // Set minimum allowed item count in array
	};
}