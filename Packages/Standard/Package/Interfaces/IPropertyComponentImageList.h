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
		class IImageList;

		class IPropertyComponentImageList :public virtual IProperty
		{
		protected:
			IPropertyComponentImageList() = default;
			~IPropertyComponentImageList() = default;
			IPropertyComponentImageList(const IPropertyComponentImageList &other) = delete;
			IPropertyComponentImageList(IPropertyComponentImageList &&other) = delete;
			IPropertyComponentImageList &operator=(const IPropertyComponentImageList &other) = delete;
			IPropertyComponentImageList &operator=(IPropertyComponentImageList &&other) = delete;
		public:
			virtual IImageList *getValue() = 0; // Return value

			virtual bool setValue(IImageList *value) = 0; // Set value
		};
	}
}