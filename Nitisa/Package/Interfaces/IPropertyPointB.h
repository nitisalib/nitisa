// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/PointB.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyPointB :public virtual IProperty
	{
	protected:
		IPropertyPointB() = default;
		~IPropertyPointB() = default;
		IPropertyPointB(const IPropertyPointB &other) = delete;
		IPropertyPointB(IPropertyPointB &&other) = delete;
		IPropertyPointB &operator=(const IPropertyPointB &other) = delete;
		IPropertyPointB &operator=(IPropertyPointB &&other) = delete;
	public:
		virtual PointB getValue() = 0; // Return value

		virtual bool setValue(const PointB value) = 0; // Set value
	};
}