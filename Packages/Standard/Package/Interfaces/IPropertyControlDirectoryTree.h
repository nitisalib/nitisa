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
		class IDirectoryTree;

		class IPropertyControlDirectoryTree :public virtual IProperty
		{
		protected:
			IPropertyControlDirectoryTree() = default;
			~IPropertyControlDirectoryTree() = default;
			IPropertyControlDirectoryTree(const IPropertyControlDirectoryTree &other) = delete;
			IPropertyControlDirectoryTree(IPropertyControlDirectoryTree &&other) = delete;
			IPropertyControlDirectoryTree &operator=(const IPropertyControlDirectoryTree &other) = delete;
			IPropertyControlDirectoryTree &operator=(IPropertyControlDirectoryTree &&other) = delete;
		public:
			virtual IDirectoryTree *getValue() = 0; // Return value

			virtual bool setValue(IDirectoryTree *value) = 0; // Set value
		};
	}
}