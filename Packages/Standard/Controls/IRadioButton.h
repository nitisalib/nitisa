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
		class IRadioButton :public virtual IControl
		{
		protected:
			IRadioButton() = default;
			~IRadioButton() = default;
			IRadioButton(const IRadioButton &other) = delete;
			IRadioButton(IRadioButton &&other) = delete;
			IRadioButton &operator=(const IRadioButton &other) = delete;
			IRadioButton &operator=(IRadioButton &&other) = delete;
		public:
			virtual String getCaption() = 0; // Return caption
			virtual int getGroupIndex() = 0; // Return group index. < 0 means no group. Default 0.
			virtual bool isChecked() = 0; // Return whether is checked

			virtual bool setCaption(const String &value) = 0; // Set caption
			virtual bool setGroupIndex(const int value) = 0; // Set group index
			virtual bool setChecked(const bool value) = 0; // Set whether is checked
		};
	}
}