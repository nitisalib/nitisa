// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/BoolArray.h"
#include "../../Core/Strings.h"
#include "IPropertyState.h"
#include <vector>

namespace nitisa
{
	class IPropertyBoolArrayState :public virtual IPropertyState
	{
	protected:
		IPropertyBoolArrayState() = default;
		~IPropertyBoolArrayState() = default;
		IPropertyBoolArrayState(const IPropertyBoolArrayState &other) = delete;
		IPropertyBoolArrayState(IPropertyBoolArrayState &&other) = delete;
		IPropertyBoolArrayState &operator=(const IPropertyBoolArrayState &other) = delete;
		IPropertyBoolArrayState &operator=(IPropertyBoolArrayState &&other) = delete;
	public:
		virtual BoolArray getValue(const String &state) = 0; // Return value depending on state
		virtual int getMinCount() = 0; // Return minimum allowed item count in array

		virtual bool setValue(const String &state, const BoolArray value) = 0; // Set value of state
		virtual IPropertyBoolArrayState *setMinCount(const int value) = 0; // Set minimum allowed item count in array
	};
}