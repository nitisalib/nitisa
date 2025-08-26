// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Key.h"

namespace nitisa
{
	// Handle keyboard related independent actions
	class IKeyboard
	{
	protected:
		IKeyboard() = default;
		~IKeyboard() = default;
		IKeyboard(const IKeyboard &other) = delete;
		IKeyboard(IKeyboard &&other) = delete;
		IKeyboard &operator=(const IKeyboard &other) = delete;
		IKeyboard &operator=(IKeyboard &&other) = delete;
	public:
		virtual bool isDown(const Key key) = 0; // Whether specified key is down
		virtual bool isToggled(const Key key) = 0; // Whether specified key is toggled
		virtual void getControlKeys(bool &ctrl, bool &alt, bool &shift) = 0; // Find out whether control keys are down or not
	};
}