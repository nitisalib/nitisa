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
		class IFileList;

		class IPropertyControlFileList :public virtual IProperty
		{
		protected:
			IPropertyControlFileList() = default;
			~IPropertyControlFileList() = default;
			IPropertyControlFileList(const IPropertyControlFileList &other) = delete;
			IPropertyControlFileList(IPropertyControlFileList &&other) = delete;
			IPropertyControlFileList &operator=(const IPropertyControlFileList &other) = delete;
			IPropertyControlFileList &operator=(IPropertyControlFileList &&other) = delete;
		public:
			virtual IFileList *getValue() = 0; // Return value

			virtual bool setValue(IFileList *value) = 0; // Set value
		};
	}
}