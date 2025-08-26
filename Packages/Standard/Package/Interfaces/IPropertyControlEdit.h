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
		class IEdit;

		class IPropertyControlEdit :public virtual IProperty
		{
		protected:
			IPropertyControlEdit() = default;
			~IPropertyControlEdit() = default;
			IPropertyControlEdit(const IPropertyControlEdit &other) = delete;
			IPropertyControlEdit(IPropertyControlEdit &&other) = delete;
			IPropertyControlEdit &operator=(const IPropertyControlEdit &other) = delete;
			IPropertyControlEdit &operator=(IPropertyControlEdit &&other) = delete;
		public:
			virtual IEdit *getValue() = 0; // Return value

			virtual bool setValue(IEdit *value) = 0; // Set value
		};
	}
}