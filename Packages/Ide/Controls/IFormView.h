// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace ide
	{
		class IFormView :public virtual IControl
		{
		protected:
			IFormView() = default;
			~IFormView() = default;
			IFormView(const IFormView &other) = delete;
			IFormView(IFormView &&other) = delete;
			IFormView &operator=(const IFormView &other) = delete;
			IFormView &operator=(IFormView &&other) = delete;
		public:
			virtual String getCaption() = 0; // Return caption

			virtual bool setCaption(const String &value) = 0; // Set caption

			virtual bool LoadLayout(const String &filename) = 0; // Load layout
		};
	}
}