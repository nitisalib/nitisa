// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/RectB.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyRectBState :public virtual IPropertyState
	{
	protected:
		IPropertyRectBState() = default;
		~IPropertyRectBState() = default;
		IPropertyRectBState(const IPropertyRectBState &other) = delete;
		IPropertyRectBState(IPropertyRectBState &&other) = delete;
		IPropertyRectBState &operator=(const IPropertyRectBState &other) = delete;
		IPropertyRectBState &operator=(IPropertyRectBState &&other) = delete;
	public:
		virtual RectB getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const RectB value) = 0; // Set value of state
	};
}