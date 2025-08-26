// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/Mat4f.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyMatrix :public virtual IProperty
	{
	protected:
		IPropertyMatrix() = default;
		~IPropertyMatrix() = default;
		IPropertyMatrix(const IPropertyMatrix &other) = delete;
		IPropertyMatrix(IPropertyMatrix &&other) = delete;
		IPropertyMatrix &operator=(const IPropertyMatrix &other) = delete;
		IPropertyMatrix &operator=(IPropertyMatrix &&other) = delete;
	public:
		virtual Mat4f getValue() = 0; // Return value

		virtual bool setValue(const Mat4f value) = 0; // Set value
	};
}