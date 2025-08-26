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
		class IMemo :public virtual IControl
		{
		protected:
			IMemo() = default;
			~IMemo() = default;
			IMemo(const IMemo &other) = delete;
			IMemo(IMemo &&other) = delete;
			IMemo &operator=(const IMemo &other) = delete;
			IMemo &operator=(IMemo &&other) = delete;
		public:
			virtual String getText() = 0; // Return text

			virtual bool setText(const String &value) = 0; // Set text
		};
	}
}