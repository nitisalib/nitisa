// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IListItemCaption.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemCheckBox :public virtual IListItemCaption
		{
		protected:
			IListItemCheckBox() = default;
			~IListItemCheckBox() = default;
			IListItemCheckBox(const IListItemCheckBox &other) = delete;
			IListItemCheckBox(IListItemCheckBox &&other) = delete;
			IListItemCheckBox &operator=(const IListItemCheckBox &other) = delete;
			IListItemCheckBox &operator=(IListItemCheckBox &&other) = delete;
		public:
			virtual bool isChecked() = 0; // Whether is checked

			virtual bool setChecked(const bool value) = 0; // Set checked/unchecked state
		};
	}
}