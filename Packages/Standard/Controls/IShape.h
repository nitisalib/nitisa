// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IShape :public virtual IControl
		{
		protected:
			IShape() = default;
			~IShape() = default;
			IShape(const IShape &other) = delete;
			IShape(IShape &&other) = delete;
			IShape &operator=(const IShape &other) = delete;
			IShape &operator=(IShape &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}