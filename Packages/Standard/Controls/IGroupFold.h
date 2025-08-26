// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		class IGroupFold :public virtual IControl
		{
		protected:
			IGroupFold() = default;
			~IGroupFold() = default;
			IGroupFold(const IGroupFold &other) = delete;
			IGroupFold(IGroupFold &&other) = delete;
			IGroupFold &operator=(const IGroupFold &other) = delete;
			IGroupFold &operator=(IGroupFold &&other) = delete;
		public:
			virtual bool isFolded() = 0; // Return whether widget is in folded state
			virtual String getCaption() = 0; // Return caption

			virtual bool setFolded(const bool value) = 0; // Set whether widget is in folded state
			virtual bool setCaption(const String &value) = 0; // Set caption

			virtual void Toggle() = 0; // Switch folded and unfolded state
		};
	}
}