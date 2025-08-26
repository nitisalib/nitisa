// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"

namespace nitisa
{
	namespace standard
	{
		class IFormMemo
		{
		protected:
			IFormMemo() = default;
			~IFormMemo() = default;
			IFormMemo(const IFormMemo &other) = delete;
			IFormMemo(IFormMemo &&other) = delete;
			IFormMemo &operator=(const IFormMemo &other) = delete;
			IFormMemo &operator=(IFormMemo &&other) = delete;
		public:
			virtual String getValue() = 0; // Return value

			virtual bool setValue(const String &value) = 0; // Set value

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}