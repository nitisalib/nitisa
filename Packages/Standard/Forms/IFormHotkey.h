// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Hotkey.h"

namespace nitisa
{
	namespace standard
	{
		class IFormHotkey
		{
		protected:
			IFormHotkey() = default;
			~IFormHotkey() = default;
			IFormHotkey(const IFormHotkey &other) = delete;
			IFormHotkey(IFormHotkey &&other) = delete;
			IFormHotkey &operator=(const IFormHotkey &other) = delete;
			IFormHotkey &operator=(IFormHotkey &&other) = delete;
		public:
			virtual Hotkey getValue() = 0; // Return value

			virtual bool setValue(const Hotkey &value) = 0; // Set value

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}