// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"

namespace nitisa
{
	namespace standard
	{
		class IFormReplace
		{
		protected:
			IFormReplace() = default;
			~IFormReplace() = default;
			IFormReplace(const IFormReplace &other) = delete;
			IFormReplace(IFormReplace &&other) = delete;
			IFormReplace &operator=(const IFormReplace &other) = delete;
			IFormReplace &operator=(IFormReplace &&other) = delete;
		public:
			enum class SearchDirection
			{
				Up, // Search to the beginning
				Down, // Search to the end
				Selection // Replace only in selection
			};
		public:
			void(*OnReplace)(IFormReplace *sender); // Callback functions used to inform parent which showed the form about user intention to replace next entry
			void(*OnReplaceAll)(IFormReplace *sender); // Callback functions used to inform parent which showed the form about user intention to search and replace all

			virtual String getText() = 0; // Return search text
			virtual String getReplace() = 0; // Return replace text
			virtual bool isMatchWholeWords() = 0; // Return whether "match whole words" checkbox is checked
			virtual bool isMatchCase() = 0; // Return whether "match case" checkbox is checked
			virtual SearchDirection getSearchDirection() = 0; // Return search direction

			virtual bool setText(const String &value) = 0; // Set search text
			virtual bool setReplace(const String &value) = 0; // Set replace text
			virtual bool setMatchWholeWords(const bool value) = 0; // Set whether "match whole words" checkbox is checked
			virtual bool setMatchCase(const bool value) = 0; // Set whether "match case" checkbox is checked
			virtual bool setSearchDirection(const SearchDirection value) = 0; // Set search direction

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}