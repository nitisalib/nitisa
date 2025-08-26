// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	namespace standard
	{
		class IFormMask
		{
		protected:
			IFormMask() = default;
			~IFormMask() = default;
			IFormMask(const IFormMask &other) = delete;
			IFormMask(IFormMask &&other) = delete;
			IFormMask &operator=(const IFormMask &other) = delete;
			IFormMask &operator=(IFormMask &&other) = delete;
		public:
			virtual unsigned int getValue() = 0; // Return value

			virtual bool setValue(const unsigned int value) = 0; // Set value
		};
	}
}