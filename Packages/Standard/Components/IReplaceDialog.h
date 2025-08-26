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
#include "../Forms/IFormReplace.h"

namespace nitisa
{
	namespace standard
	{
		class IReplaceDialog :public virtual IComponent
		{
		protected:
			IReplaceDialog() = default;
			~IReplaceDialog() = default;
			IReplaceDialog(const IReplaceDialog &other) = delete;
			IReplaceDialog(IReplaceDialog &&other) = delete;
			IReplaceDialog &operator=(const IReplaceDialog &other) = delete;
			IReplaceDialog &operator=(IReplaceDialog &&other) = delete;
		public:
			void(*OnReplace)(IFormReplace *sender); // Callback functions used to inform parent which called the dialog about user intention to replace next entry
			void(*OnReplaceAll)(IFormReplace *sender); // Callback functions used to inform parent which called the dialog about user intention to search and replace all

			virtual String getText() = 0; // Return search text
			virtual String getReplace() = 0; // Return replace text
			virtual bool isMatchWholeWords() = 0; // Return whether "match whole words" checkbox is checked
			virtual bool isMatchCase() = 0; // Return whether "match case" checkbox is checked
			virtual IFormReplace::SearchDirection getSearchDirection() = 0; // Return search direction
			virtual bool isUseDialogBox() = 0; // Return whether dialog box or regular form should be used

			virtual bool setText(const String &value) = 0; // Set search text
			virtual bool setReplace(const String &value) = 0; // Set replace text
			virtual bool setMatchWholeWords(const bool value) = 0; // Set whether "match whole words" checkbox is checked
			virtual bool setMatchCase(const bool value) = 0; // Set whether "match case" checkbox is checked
			virtual bool setSearchDirection(const IFormReplace::SearchDirection value) = 0; // Set search direction
			virtual bool setUseDialogBox(const bool value) = 0; // Set whether dialog box or regular form should be used

			virtual bool Execute() = 0; // Show dialog
		};
	}
}