// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/PointF.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyPointFState :public virtual IPropertyState
	{
	protected:
		IPropertyPointFState() = default;
		~IPropertyPointFState() = default;
		IPropertyPointFState(const IPropertyPointFState &other) = delete;
		IPropertyPointFState(IPropertyPointFState &&other) = delete;
		IPropertyPointFState &operator=(const IPropertyPointFState &other) = delete;
		IPropertyPointFState &operator=(IPropertyPointFState &&other) = delete;
	public:
		virtual PointF getValue(const String &state) = 0; // Return value depending on state
		virtual bool hasMin() const = 0; // Whether has minimum limit
		virtual bool hasMax() const = 0; // Whether has maximum limit
		virtual float getMin() const = 0; // Return minimum limit
		virtual float getMax() const = 0; // Return maximum limit

		virtual bool setValue(const String &state, const PointF value) = 0; // Set value of state
		virtual IPropertyPointFState *setHasMin(const bool value) = 0; // Set whether has minimum limit
		virtual IPropertyPointFState *setHasMax(const bool value) = 0; // Set whether has maximum limit
		virtual IPropertyPointFState *setMin(const float value) = 0; // Set minimum limit and hasMin to true
		virtual IPropertyPointFState *setMax(const float value) = 0; // Set maximum limit and hasMax to true
	};
}