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
		class IButton :public virtual IControl
		{
		protected:
			IButton() = default;
			~IButton() = default;
			IButton(const IButton &other) = delete;
			IButton(IButton &&other) = delete;
			IButton &operator=(const IButton &other) = delete;
			IButton &operator=(IButton &&other) = delete;
		public:
			virtual String getCaption() = 0; // Return caption
			virtual bool isDown() = 0; // Return whether button is in a down state

			virtual bool setCaption(const String &value) = 0; // Set caption
			virtual bool setDown(const bool value) = 0; // Set whether button is in a down state

			virtual void Click() = 0; // Emulate click
		};
	}
}