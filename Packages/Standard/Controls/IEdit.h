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
		class IEdit :public virtual IControl
		{
		protected:
			IEdit() = default;
			~IEdit() = default;
			IEdit(const IEdit &other) = delete;
			IEdit(IEdit &&other) = delete;
			IEdit &operator=(const IEdit &other) = delete;
			IEdit &operator=(IEdit &&other) = delete;
		public:
			virtual String getText() = 0; // Return text

			virtual bool setText(const String &value) = 0; // Set text
		};
	}
}