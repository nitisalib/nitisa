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
		class IFormFind
		{
		protected:
			IFormFind() = default;
			~IFormFind() = default;
			IFormFind(const IFormFind &other) = delete;
			IFormFind(IFormFind &&other) = delete;
			IFormFind &operator=(const IFormFind &other) = delete;
			IFormFind &operator=(IFormFind &&other) = delete;
		public:
			enum class SearchDirection
			{
				Up, // Search to the beginning
				Down // Search to the end
			};
		public:
			void(*OnSearch)(IFormFind *sender); // Callback functions used to inform parent which showed the form about user intention to search

			virtual String getText() = 0; // Return search text
			virtual bool isMatchWholeWords() = 0; // Return whether "match whole words" checkbox is checked
			virtual bool isMatchCase() = 0; // Return whether "match case" checkbox is checked
			virtual SearchDirection getSearchDirection() = 0; // Return search direction

			virtual bool setText(const String &value) = 0; // Set search text
			virtual bool setMatchWholeWords(const bool value) = 0; // Set whether "match whole words" checkbox is checked
			virtual bool setMatchCase(const bool value) = 0; // Set whether "match case" checkbox is checked
			virtual bool setSearchDirection(const SearchDirection value) = 0; // Set search direction

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}