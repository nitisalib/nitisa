// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Enums.h"
#include <vector>

namespace nitisa
{
	namespace charts
	{
		class IFormLineInterpolationPositionArray
		{
		protected:
			IFormLineInterpolationPositionArray() = default;
			~IFormLineInterpolationPositionArray() = default;
			IFormLineInterpolationPositionArray(const IFormLineInterpolationPositionArray &other) = delete;
			IFormLineInterpolationPositionArray(IFormLineInterpolationPositionArray &&other) = delete;
			IFormLineInterpolationPositionArray &operator=(const IFormLineInterpolationPositionArray &other) = delete;
			IFormLineInterpolationPositionArray &operator=(IFormLineInterpolationPositionArray &&other) = delete;
		public:
			virtual std::vector<LineInterpolationPosition> getValue() = 0; // Return value
			virtual int getMinCount() = 0; // Return minimum allowed count of items in array

			virtual bool setValue(const std::vector<LineInterpolationPosition> &value) = 0; // Set value
			virtual bool setMinCount(const int value) = 0; // Set minimum allowed count of items in array
		};
	}
}