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
	namespace opengl
	{
		class IMaterialControl;

		class IPropertyControlMaterialState :public virtual IPropertyState
		{
		protected:
			IPropertyControlMaterialState() = default;
			~IPropertyControlMaterialState() = default;
			IPropertyControlMaterialState(const IPropertyControlMaterialState &other) = delete;
			IPropertyControlMaterialState(IPropertyControlMaterialState &&other) = delete;
			IPropertyControlMaterialState &operator=(const IPropertyControlMaterialState &other) = delete;
			IPropertyControlMaterialState &operator=(IPropertyControlMaterialState &&other) = delete;
		public:
			virtual IMaterialControl *getValue(const String &state) = 0; // Return value depending on state

			virtual bool setValue(const String &state, IMaterialControl *value) = 0; // Set value of state
		};
	}
}