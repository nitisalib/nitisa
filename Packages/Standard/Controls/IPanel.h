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
	namespace standard
	{
		class IPanel :public virtual IControl
		{
		protected:
			IPanel() = default;
			~IPanel() = default;
			IPanel(const IPanel &other) = delete;
			IPanel(IPanel &&other) = delete;
			IPanel &operator=(const IPanel &other) = delete;
			IPanel &operator=(IPanel &&other) = delete;
		public:
			virtual String getCaption() = 0; // Return caption

			virtual bool setCaption(const String &value) = 0; // Set caption
		};
	}
}