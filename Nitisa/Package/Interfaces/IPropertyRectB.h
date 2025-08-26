// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/RectB.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyRectB :public virtual IProperty
	{
	protected:
		IPropertyRectB() = default;
		~IPropertyRectB() = default;
		IPropertyRectB(const IPropertyRectB &other) = delete;
		IPropertyRectB(IPropertyRectB &&other) = delete;
		IPropertyRectB &operator=(const IPropertyRectB &other) = delete;
		IPropertyRectB &operator=(IPropertyRectB &&other) = delete;
	public:
		virtual RectB getValue() = 0; // Return value

		virtual bool setValue(const RectB value) = 0; // Set value
	};
}