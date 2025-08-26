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
	namespace standard
	{
		class IHSVPlane;

		class IPropertyControlHSVPlane :public virtual IProperty
		{
		protected:
			IPropertyControlHSVPlane() = default;
			~IPropertyControlHSVPlane() = default;
			IPropertyControlHSVPlane(const IPropertyControlHSVPlane &other) = delete;
			IPropertyControlHSVPlane(IPropertyControlHSVPlane &&other) = delete;
			IPropertyControlHSVPlane &operator=(const IPropertyControlHSVPlane &other) = delete;
			IPropertyControlHSVPlane &operator=(IPropertyControlHSVPlane &&other) = delete;
		public:
			virtual IHSVPlane *getValue() = 0; // Return value

			virtual bool setValue(IHSVPlane *value) = 0; // Set value
		};
	}
}