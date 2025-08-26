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
	class IPropertyMask :public virtual IProperty
	{
	protected:
		IPropertyMask() = default;
		~IPropertyMask() = default;
		IPropertyMask(const IPropertyMask &other) = delete;
		IPropertyMask(IPropertyMask &&other) = delete;
		IPropertyMask &operator=(const IPropertyMask &other) = delete;
		IPropertyMask &operator=(IPropertyMask &&other) = delete;
	public:
		virtual unsigned int getValue() = 0; // Return value

		virtual bool setValue(const unsigned int value) = 0; // Set value
	};
}