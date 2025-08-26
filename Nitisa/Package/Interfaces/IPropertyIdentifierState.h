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
	class IPropertyIdentifierState :public virtual IPropertyState
	{
	protected:
		IPropertyIdentifierState() = default;
		~IPropertyIdentifierState() = default;
		IPropertyIdentifierState(const IPropertyIdentifierState &other) = delete;
		IPropertyIdentifierState(IPropertyIdentifierState &&other) = delete;
		IPropertyIdentifierState &operator=(const IPropertyIdentifierState &other) = delete;
		IPropertyIdentifierState &operator=(IPropertyIdentifierState &&other) = delete;
	public:
		virtual String getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const String value) = 0; // Set value of state
	};
}