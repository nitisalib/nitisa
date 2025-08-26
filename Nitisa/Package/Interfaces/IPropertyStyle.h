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
	class IStyle;

	class IPropertyStyle :public virtual IProperty
	{
	protected:
		IPropertyStyle() = default;
		~IPropertyStyle() = default;
		IPropertyStyle(const IPropertyStyle &other) = delete;
		IPropertyStyle(IPropertyStyle &&other) = delete;
		IPropertyStyle &operator=(const IPropertyStyle &other) = delete;
		IPropertyStyle &operator=(IPropertyStyle &&other) = delete;
	public:
		virtual IStyle *getValue() = 0; // Return value

		virtual bool setValue(IStyle *value) = 0; // Set value
	};
}