// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IComponent.h"
#include "../Forms/IFormFind.h"

namespace nitisa
{
	namespace standard
	{
		class IFindDialog :public virtual IComponent
		{
		protected:
			IFindDialog() = default;
			~IFindDialog() = default;
			IFindDialog(const IFindDialog &other) = delete;
			IFindDialog(IFindDialog &&other) = delete;
			IFindDialog &operator=(const IFindDialog &other) = delete;
			IFindDialog &operator=(IFindDialog &&other) = delete;
		public:
			void(*OnSearch)(IFormFind *sender); // Callback functions used to inform parent which called the dialog about user intention to search

			virtual String getText() = 0; // Return search text
			virtual bool isMatchWholeWords() = 0; // Return whether "match whole words" checkbox is checked
			virtual bool isMatchCase() = 0; // Return whether "match case" checkbox is checked
			virtual IFormFind::SearchDirection getSearchDirection() = 0; // Return search direction
			virtual bool isUseDialogBox() = 0; // Return whether dialog box or regular form should be used

			virtual bool setText(const String &value) = 0; // Set search text
			virtual bool setMatchWholeWords(const bool value) = 0; // Set whether "match whole words" checkbox is checked
			virtual bool setMatchCase(const bool value) = 0; // Set whether "match case" checkbox is checked
			virtual bool setSearchDirection(const IFormFind::SearchDirection value) = 0; // Set search direction
			virtual bool setUseDialogBox(const bool value) = 0; // Set whether dialog box or regular form should be used

			virtual bool Execute() = 0; // Show dialog
		};
	}
}