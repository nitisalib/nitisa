// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Math/RectF.h"

namespace nitisa
{
	namespace standard
	{
		// Simple control for holding another controls. It's usually invisible or has just plain background without any border and other complex elements
		class IContainer :public virtual IControl
		{
		protected:
			IContainer() = default;
			~IContainer() = default;
			IContainer(const IContainer &other) = delete;
			IContainer(IContainer &&other) = delete;
			IContainer &operator=(const IContainer &other) = delete;
			IContainer &operator=(IContainer &&other) = delete;
		public:
			virtual RectF getPadding() = 0; // Return padding

			virtual bool setPadding(const RectF &value) = 0; // Set padding
		};
	}
}