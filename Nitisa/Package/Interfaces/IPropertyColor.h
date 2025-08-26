// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Image/Color.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyColor :public virtual IProperty
	{
	protected:
		IPropertyColor() = default;
		~IPropertyColor() = default;
		IPropertyColor(const IPropertyColor &other) = delete;
		IPropertyColor(IPropertyColor &&other) = delete;
		IPropertyColor &operator=(const IPropertyColor &other) = delete;
		IPropertyColor &operator=(IPropertyColor &&other) = delete;
	public:
		virtual Color getValue() = 0; // Return value

		virtual bool setValue(const Color value) = 0; // Set value
	};
}