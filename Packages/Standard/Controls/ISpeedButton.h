// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class ISpeedButton :public virtual IControl
		{
		protected:
			ISpeedButton() = default;
			~ISpeedButton() = default;
			ISpeedButton(const ISpeedButton &other) = delete;
			ISpeedButton(ISpeedButton &&other) = delete;
			ISpeedButton &operator=(const ISpeedButton &other) = delete;
			ISpeedButton &operator=(ISpeedButton &&other) = delete;
		public:
			virtual int getGroupIndex() = 0; // Return group index
			virtual bool isDown() = 0; // Whether is down

			virtual bool setGroupIndex(const int value) = 0; // Set group index
			virtual bool setDown(const bool value) = 0; // Set whether is down
		};
	}
}