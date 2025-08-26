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
		class IFileList;

		class IPropertyControlFileListState :public virtual IPropertyState
		{
		protected:
			IPropertyControlFileListState() = default;
			~IPropertyControlFileListState() = default;
			IPropertyControlFileListState(const IPropertyControlFileListState &other) = delete;
			IPropertyControlFileListState(IPropertyControlFileListState &&other) = delete;
			IPropertyControlFileListState &operator=(const IPropertyControlFileListState &other) = delete;
			IPropertyControlFileListState &operator=(IPropertyControlFileListState &&other) = delete;
		public:
			virtual IFileList *getValue(const String &state) = 0; // Return value depending on state

			virtual bool setValue(const String &state, IFileList *value) = 0; // Set value of state
		};
	}
}