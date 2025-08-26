// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Hotkey.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyHotkey :public virtual IProperty
	{
	protected:
		IPropertyHotkey() = default;
		~IPropertyHotkey() = default;
		IPropertyHotkey(const IPropertyHotkey &other) = delete;
		IPropertyHotkey(IPropertyHotkey &&other) = delete;
		IPropertyHotkey &operator=(const IPropertyHotkey &other) = delete;
		IPropertyHotkey &operator=(IPropertyHotkey &&other) = delete;
	public:
		virtual Hotkey getValue() = 0; // Return value

		virtual bool setValue(const Hotkey value) = 0; // Set value
	};
}