// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IListItemService.h"
#include "IListItemCheckBox.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemRadioButtonService :public virtual IListItemService
		{
		protected:
			IListItemRadioButtonService() = default;
			~IListItemRadioButtonService() = default;
			IListItemRadioButtonService(const IListItemRadioButtonService &other) = delete;
			IListItemRadioButtonService(IListItemRadioButtonService &&other) = delete;
			IListItemRadioButtonService &operator=(const IListItemRadioButtonService &other) = delete;
			IListItemRadioButtonService &operator=(IListItemRadioButtonService &&other) = delete;
		public:
			virtual bool setChecked(const bool value) = 0; // Should change checked state and call OnChange if exists
		};

		class IListItemRadioButton :public virtual IListItemCheckBox
		{
		protected:
			IListItemRadioButton() = default;
			~IListItemRadioButton() = default;
			IListItemRadioButton(const IListItemRadioButton &other) = delete;
			IListItemRadioButton(IListItemRadioButton &&other) = delete;
			IListItemRadioButton &operator=(const IListItemRadioButton &other) = delete;
			IListItemRadioButton &operator=(IListItemRadioButton &&other) = delete;
		public:
			virtual int getGroupIndex() = 0; // Return group index. < 0 means no group. Default 0

			virtual bool setGroupIndex(const int value) = 0; // Set group index
		};
	}
}