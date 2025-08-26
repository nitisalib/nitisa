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
	class IPropertyEnum :public virtual IProperty
	{
	protected:
		IPropertyEnum() = default;
		~IPropertyEnum() = default;
		IPropertyEnum(const IPropertyEnum &other) = delete;
		IPropertyEnum(IPropertyEnum &&other) = delete;
		IPropertyEnum &operator=(const IPropertyEnum &other) = delete;
		IPropertyEnum &operator=(IPropertyEnum &&other) = delete;
	public:
		virtual String getValue() = 0; // Return value
		virtual int getItemCount() const = 0; // Return allow values count
		virtual String getItem(const int index) const = 0; // Return allow values count

		virtual bool setValue(const String value) = 0; // Set value
	};
}