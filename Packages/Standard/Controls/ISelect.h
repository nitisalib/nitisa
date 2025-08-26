// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Interfaces/IComponentItemList.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IBuiltInSelect;
	class IFont;

	namespace standard
	{
		class ISelect :public virtual IControl, public virtual IComponentItemList
		{
		protected:
			ISelect() = default;
			~ISelect() = default;
			ISelect(const ISelect &other) = delete;
			ISelect(ISelect &&other) = delete;
			ISelect &operator=(const ISelect &other) = delete;
			ISelect &operator=(ISelect &&other) = delete;
		public:
			virtual String getFilter() = 0; // Return active filter
			virtual int getActiveIndex() = 0; // Return active item index
			virtual IBuiltInSelect *getSelect() = 0; // Return built-in select
			virtual IFont *getCategoryFont() = 0; // Return font used for category items

			virtual bool setFilter(const String &value) = 0; // Set filter
			virtual bool setActiveIndex(const int value) = 0; // Set active item
			virtual bool setSelect(IBuiltInSelect *value) = 0; // Set built-in select
			virtual bool setCategoryFont(IFont *value) = 0; // Set font used for category items

			virtual bool Open() = 0; // Open list
			virtual bool Close() = 0; // Close list
		};
	}
}