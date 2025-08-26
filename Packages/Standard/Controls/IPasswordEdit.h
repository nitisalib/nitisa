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
		class IPasswordEdit :public virtual IControl
		{
		protected:
			IPasswordEdit() = default;
			~IPasswordEdit() = default;
			IPasswordEdit(const IPasswordEdit &other) = delete;
			IPasswordEdit(IPasswordEdit &&other) = delete;
			IPasswordEdit &operator=(const IPasswordEdit &other) = delete;
			IPasswordEdit &operator=(IPasswordEdit &&other) = delete;
		public:
			virtual String getPassword() = 0; // Return password
			virtual wchar_t getReplaceSymbol() = 0; // Return character which will replace password characters when displayed

			virtual bool setPassword(const String &value) = 0; // Set password
			virtual bool setReplaceSymbol(const wchar_t value) = 0; // Set character which will replace password characters when displayed
		};
	}
}