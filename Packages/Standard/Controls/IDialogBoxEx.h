// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IDialogBox.h"

namespace nitisa
{
	namespace standard
	{
		class IDialogBoxEx :public virtual IDialogBox
		{
		protected:
			IDialogBoxEx() = default;
			~IDialogBoxEx() = default;
			IDialogBoxEx(const IDialogBoxEx &other) = delete;
			IDialogBoxEx(IDialogBoxEx &&other) = delete;
			IDialogBoxEx &operator=(const IDialogBoxEx &other) = delete;
			IDialogBoxEx &operator=(IDialogBoxEx &&other) = delete;
		public:
			virtual void AutoResize(const bool transform) = 0; // Set size automatically depending on children controls and optionally set position depending on WindowPosition property
		};
	}
}