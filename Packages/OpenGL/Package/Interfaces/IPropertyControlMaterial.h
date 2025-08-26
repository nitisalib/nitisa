// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Package/Interfaces/IProperty.h"

namespace nitisa
{
	namespace opengl
	{
		class IMaterialControl;

		class IPropertyControlMaterial :public virtual IProperty
		{
		protected:
			IPropertyControlMaterial() = default;
			~IPropertyControlMaterial() = default;
			IPropertyControlMaterial(const IPropertyControlMaterial &other) = delete;
			IPropertyControlMaterial(IPropertyControlMaterial &&other) = delete;
			IPropertyControlMaterial &operator=(const IPropertyControlMaterial &other) = delete;
			IPropertyControlMaterial &operator=(IPropertyControlMaterial &&other) = delete;
		public:
			virtual IMaterialControl *getValue() = 0; // Return value

			virtual bool setValue(IMaterialControl *value) = 0; // Set value
		};

		
	}
}