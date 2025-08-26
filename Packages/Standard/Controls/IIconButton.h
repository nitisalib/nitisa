// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		class IIconButton :public virtual IControl
		{
		protected:
			IIconButton() = default;
			~IIconButton() = default;
			IIconButton(const IIconButton &other) = delete;
			IIconButton(IIconButton &&other) = delete;
			IIconButton &operator=(const IIconButton &other) = delete;
			IIconButton &operator=(IIconButton &&other) = delete;
		public:
			virtual void Click() = 0; // Emulate click
		};
	}
}