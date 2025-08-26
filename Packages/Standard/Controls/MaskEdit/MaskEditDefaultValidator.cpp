// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		CMaskEdit::CDefaultValidator::CDefaultValidator() 
		{

		}

		bool CMaskEdit::CDefaultValidator::Validate(IMaskEdit *edit, const String &mask, const String &original, String &text, int &caret_position)
		{
			if (mask.empty())
				return true;
			if (text.length() > mask.length())
				return false;
			size_t len{ ntl::Min<size_t>(mask.length(), text.length()) };
			for (size_t i = 0; i < len; i++)
				switch (mask[i])
				{
				case L'#':
					if (!std::isdigit(text[i], std::locale()))
						return false;
					break;
				case L'*':
					if (!std::isalpha(text[i], std::locale()))
						return false;
					break;
				default:
					if (text[i] != mask[i])
						return false;
				}
			// Handle input at the end
			if (caret_position >= (int)text.length() && text.length() > original.length())
				while (caret_position < (int)mask.length() && mask[caret_position] != L'#' && mask[caret_position] != L'*')
				{
					text += mask[caret_position];
					caret_position++;
				}
			return true;
		}
	}
}