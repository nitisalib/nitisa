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
	class Image;

	class IPropertyImage :public virtual IProperty
	{
	protected:
		IPropertyImage() = default;
		~IPropertyImage() = default;
		IPropertyImage(const IPropertyImage &other) = delete;
		IPropertyImage(IPropertyImage &&other) = delete;
		IPropertyImage &operator=(const IPropertyImage &other) = delete;
		IPropertyImage &operator=(IPropertyImage &&other) = delete;
	public:
		virtual Image* getValue() = 0; // Return value

		virtual void Update() = 0; // Call to update owner after image change
	};
}