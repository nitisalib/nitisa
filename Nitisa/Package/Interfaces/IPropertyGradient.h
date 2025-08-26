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
	class Gradient;

	class IPropertyGradient :public virtual IProperty
	{
	protected:
		IPropertyGradient() = default;
		~IPropertyGradient() = default;
		IPropertyGradient(const IPropertyGradient &other) = delete;
		IPropertyGradient(IPropertyGradient &&other) = delete;
		IPropertyGradient &operator=(const IPropertyGradient &other) = delete;
		IPropertyGradient &operator=(IPropertyGradient &&other) = delete;
	public:
		virtual Gradient *getValue() = 0; // Return value
	};
}