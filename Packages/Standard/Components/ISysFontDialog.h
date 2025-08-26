// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IComponent.h"

namespace nitisa
{
	class IFont;

	namespace standard
	{
		class ISysFontDialog :public virtual IComponent
		{
		protected:
			ISysFontDialog() = default;
			~ISysFontDialog() = default;
			ISysFontDialog(const ISysFontDialog &other) = delete;
			ISysFontDialog(ISysFontDialog &&other) = delete;
			ISysFontDialog &operator=(const ISysFontDialog &other) = delete;
			ISysFontDialog &operator=(ISysFontDialog &&other) = delete;
		public:
			virtual IFont *getFont() = 0; // Return selected font

			virtual bool setFont(IFont *font) = 0; // Set selected font(copy properties)

			virtual bool Execute() = 0; // Show dialog
		};
	}
}