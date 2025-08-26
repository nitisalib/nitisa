// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IComponentItemList.h"
#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemMultiButton;

		class IMultiButton :public virtual IComponentItemList, public virtual IControl
		{
		protected:
			IMultiButton() = default;
			~IMultiButton() = default;
			IMultiButton(const IMultiButton &other) = delete;
			IMultiButton(IMultiButton &&other) = delete;
			IMultiButton &operator=(const IMultiButton &other) = delete;
			IMultiButton &operator=(IMultiButton &&other) = delete;
		public:
			// Events
			void(*OnClick)(IMultiButton *sender); // Event called when click happens on widget

			virtual float getDelay() = 0; // Return delay before showing button list
			virtual int getButtonCount() = 0; // Return button count
			virtual IListItemMultiButton *getButton(const int index) = 0; // Return button by index
			virtual int getButtonIndex(IListItemMultiButton *item) = 0; // Return button index in list or -1
			virtual int getActiveButtonIndex() = 0; // Return index of active button
			virtual IListItemMultiButton *getActiveButton() = 0; // Return active button

			virtual bool setDelay(const float value, const float tolerance = ntl::Tolerance<float>) = 0; // Set delay before showing button list
			virtual bool setActiveButtonIndex(const int value) = 0; // Set active button by index
			virtual bool setActiveButton(IListItemMultiButton *value) = 0; // Set active button

			virtual bool AddButton(IListItemMultiButton *item) = 0; // Add button to list
			virtual IListItemMultiButton *AddButton(const String &caption) = 0; // Add button to list
			virtual bool InsertButton(IListItemMultiButton *item, const int before) = 0; // Insert button in list before specified button index
			virtual IListItemMultiButton *InsertButton(const String &caption, const int before) = 0; // Insert button in list before specified button index
			virtual bool DeleteButton(const int index) = 0; // Delete button from list by index
			virtual bool DeleteButton(IListItemMultiButton *item) = 0; // Delete specified button from list
			virtual bool DeleteButtons() = 0; // Delete all buttons form list
		};
	}
}