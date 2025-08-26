// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyString :public virtual IProperty
	{
	protected:
		IPropertyString() = default;
		~IPropertyString() = default;
		IPropertyString(const IPropertyString &other) = delete;
		IPropertyString(IPropertyString &&other) = delete;
		IPropertyString &operator=(const IPropertyString &other) = delete;
		IPropertyString &operator=(IPropertyString &&other) = delete;
	public:
		virtual String getValue() = 0; // Return value

		virtual bool setValue(const String value) = 0; // Set value
	};
}