// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "IPropertyState.h"

namespace nitisa
{
	class Gradient;

	class IPropertyGradientState :public virtual IPropertyState
	{
	protected:
		IPropertyGradientState() = default;
		~IPropertyGradientState() = default;
		IPropertyGradientState(const IPropertyGradientState &other) = delete;
		IPropertyGradientState(IPropertyGradientState &&other) = delete;
		IPropertyGradientState &operator=(const IPropertyGradientState &other) = delete;
		IPropertyGradientState &operator=(IPropertyGradientState &&other) = delete;
	public:
		virtual Gradient *getValue(const String &state) = 0; // Return value depending on state
	};
}