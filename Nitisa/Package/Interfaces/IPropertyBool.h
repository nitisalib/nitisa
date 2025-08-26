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
	class IPropertyBool :public virtual IProperty
	{
	protected:
		IPropertyBool() = default;
		~IPropertyBool() = default;
		IPropertyBool(const IPropertyBool &other) = delete;
		IPropertyBool(IPropertyBool &&other) = delete;
		IPropertyBool &operator=(const IPropertyBool &other) = delete;
		IPropertyBool &operator=(IPropertyBool &&other) = delete;
	public:
		virtual bool getValue() = 0; // Return value

		virtual bool setValue(const bool value) = 0; // Set value
	};
}