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
		class IHSVPlane;

		class IPropertyControlHSVPlaneState :public virtual IPropertyState
		{
		protected:
			IPropertyControlHSVPlaneState() = default;
			~IPropertyControlHSVPlaneState() = default;
			IPropertyControlHSVPlaneState(const IPropertyControlHSVPlaneState &other) = delete;
			IPropertyControlHSVPlaneState(IPropertyControlHSVPlaneState &&other) = delete;
			IPropertyControlHSVPlaneState &operator=(const IPropertyControlHSVPlaneState &other) = delete;
			IPropertyControlHSVPlaneState &operator=(IPropertyControlHSVPlaneState &&other) = delete;
		public:
			virtual IHSVPlane *getValue(const String &state) = 0; // Return value depending on state

			virtual bool setValue(const String &state, IHSVPlane *value) = 0; // Set value of state
		};
	}
}