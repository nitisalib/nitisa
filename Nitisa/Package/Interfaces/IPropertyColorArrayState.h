// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Image/ColorArray.h"
#include "IPropertyState.h"
#include <vector>

namespace nitisa
{
	class IPropertyColorArrayState :public virtual IPropertyState
	{
	protected:
		IPropertyColorArrayState() = default;
		~IPropertyColorArrayState() = default;
		IPropertyColorArrayState(const IPropertyColorArrayState &other) = delete;
		IPropertyColorArrayState(IPropertyColorArrayState &&other) = delete;
		IPropertyColorArrayState &operator=(const IPropertyColorArrayState &other) = delete;
		IPropertyColorArrayState &operator=(IPropertyColorArrayState &&other) = delete;
	public:
		virtual ColorArray getValue(const String &state) = 0; // Return value depending on state
		virtual int getMinCount() = 0; // Return minimum allowed item count in array

		virtual bool setValue(const String &state, const ColorArray value) = 0; // Set value of state
		virtual IPropertyColorArrayState *setMinCount(const int value) = 0; // Set minimum allowed item count in array
	};
}