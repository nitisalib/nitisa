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
		class IGroupBox :public virtual IControl
		{
		protected:
			IGroupBox() = default;
			~IGroupBox() = default;
			IGroupBox(const IGroupBox &other) = delete;
			IGroupBox(IGroupBox &&other) = delete;
			IGroupBox &operator=(const IGroupBox &other) = delete;
			IGroupBox &operator=(IGroupBox &&other) = delete;
		public:
			virtual String getCaption() = 0; // Return caption

			virtual bool setCaption(const String &value) = 0; // Set caption
		};
	}
}