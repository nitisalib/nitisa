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
		class IImageList;

		class IPropertyComponentImageListState :public virtual IPropertyState
		{
		protected:
			IPropertyComponentImageListState() = default;
			~IPropertyComponentImageListState() = default;
			IPropertyComponentImageListState(const IPropertyComponentImageListState &other) = delete;
			IPropertyComponentImageListState(IPropertyComponentImageListState &&other) = delete;
			IPropertyComponentImageListState &operator=(const IPropertyComponentImageListState &other) = delete;
			IPropertyComponentImageListState &operator=(IPropertyComponentImageListState &&other) = delete;
		public:
			virtual IImageList *getValue(const String &state) = 0; // Return value depending on state

			virtual bool setValue(const String &state, IImageList *value) = 0; // Set value of state
		};
	}
}