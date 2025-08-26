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
	class IFont;

	class IPropertyFont :public virtual IProperty
	{
	protected:
		IPropertyFont() = default;
		~IPropertyFont() = default;
		IPropertyFont(const IPropertyFont &other) = delete;
		IPropertyFont(IPropertyFont &&other) = delete;
		IPropertyFont &operator=(const IPropertyFont &other) = delete;
		IPropertyFont &operator=(IPropertyFont &&other) = delete;
	public:
		virtual IFont *getValue() = 0; // Return value

		virtual bool setValue(IFont *value) = 0; // Set value
	};
}