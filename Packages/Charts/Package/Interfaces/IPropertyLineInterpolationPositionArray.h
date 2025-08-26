// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Package/Interfaces/IProperty.h"
#include "../../Core/Enums.h"
#include <vector>

namespace nitisa
{
	namespace charts
	{
		class IPropertyLineInterpolationPositionArray :public virtual IProperty
		{
		protected:
			IPropertyLineInterpolationPositionArray() = default;
			~IPropertyLineInterpolationPositionArray() = default;
			IPropertyLineInterpolationPositionArray(const IPropertyLineInterpolationPositionArray &other) = delete;
			IPropertyLineInterpolationPositionArray(IPropertyLineInterpolationPositionArray &&other) = delete;
			IPropertyLineInterpolationPositionArray &operator=(const IPropertyLineInterpolationPositionArray &other) = delete;
			IPropertyLineInterpolationPositionArray &operator=(IPropertyLineInterpolationPositionArray &&other) = delete;
		public:
			virtual std::vector<LineInterpolationPosition> getValue() = 0; // Return value
			virtual int getMinCount() = 0; // Return minimum allowed item count in array

			virtual bool setValue(const std::vector<LineInterpolationPosition> value) = 0; // Set value
			virtual IPropertyLineInterpolationPositionArray *setMinCount(const int value) = 0; // Set minimum allowed item count in array
		};
	}
}