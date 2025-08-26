// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/PointL.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyPointLState :public virtual IPropertyState
	{
	protected:
		IPropertyPointLState() = default;
		~IPropertyPointLState() = default;
		IPropertyPointLState(const IPropertyPointLState &other) = delete;
		IPropertyPointLState(IPropertyPointLState &&other) = delete;
		IPropertyPointLState &operator=(const IPropertyPointLState &other) = delete;
		IPropertyPointLState &operator=(IPropertyPointLState &&other) = delete;
	public:
		virtual PointL getValue(const String &state) = 0; // Return value depending on state
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual long long getMin() const = 0; // Return minimum limit
		virtual long long getMax() const = 0; // Return maximum limit

		virtual bool setValue(const String &state, const PointL value) = 0; // Set value of state
		virtual IPropertyPointLState *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyPointLState *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyPointLState *setMin(const long long value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyPointLState *setMax(const long long value) = 0; // Set maximum limit and hasMax to true
	};
}