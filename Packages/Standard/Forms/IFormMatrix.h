// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/Mat4f.h"

namespace nitisa
{
	namespace standard
	{
		class IFormMatrix
		{
		protected:
			IFormMatrix() = default;
			~IFormMatrix() = default;
			IFormMatrix(const IFormMatrix &other) = delete;
			IFormMatrix(IFormMatrix &&other) = delete;
			IFormMatrix &operator=(const IFormMatrix &other) = delete;
			IFormMatrix &operator=(IFormMatrix &&other) = delete;
		public:
			virtual Mat4f getValue() = 0; // Return value

			virtual bool setValue(const Mat4f &value) = 0; // Set value

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}