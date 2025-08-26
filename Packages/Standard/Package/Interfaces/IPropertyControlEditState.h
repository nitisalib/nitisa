// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/Interfaces/IPropertyState.h"

namespace nitisa
{
	namespace standard
	{
		class IEdit;

		class IPropertyControlEditState :public virtual IPropertyState
		{
		protected:
			IPropertyControlEditState() = default;
			~IPropertyControlEditState() = default;
			IPropertyControlEditState(const IPropertyControlEditState &other) = delete;
			IPropertyControlEditState(IPropertyControlEditState &&other) = delete;
			IPropertyControlEditState &operator=(const IPropertyControlEditState &other) = delete;
			IPropertyControlEditState &operator=(IPropertyControlEditState &&other) = delete;
		public:
			virtual IEdit *getValue(const String &state) = 0; // Return value depending on state

			virtual bool setValue(const String &state, IEdit *value) = 0; // Set value of state
		};
	}
}