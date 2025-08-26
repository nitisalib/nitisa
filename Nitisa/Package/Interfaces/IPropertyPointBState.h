// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/PointB.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyPointBState :public virtual IPropertyState
	{
	protected:
		IPropertyPointBState() = default;
		~IPropertyPointBState() = default;
		IPropertyPointBState(const IPropertyPointBState &other) = delete;
		IPropertyPointBState(IPropertyPointBState &&other) = delete;
		IPropertyPointBState &operator=(const IPropertyPointBState &other) = delete;
		IPropertyPointBState &operator=(IPropertyPointBState &&other) = delete;
	public:
		virtual PointB getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const PointB value) = 0; // Set value of state
	};
}