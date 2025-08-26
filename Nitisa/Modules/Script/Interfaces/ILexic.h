// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Interfaces/IReleasable.h"

namespace nitisa
{
	namespace script
	{
		class ILexic :public virtual IReleasable
		{
		protected:
			ILexic() = default;
			~ILexic() = default;
			ILexic(const ILexic &other) = delete;
			ILexic(ILexic &&other) = delete;
			ILexic &operator=(const ILexic &other) = delete;
			ILexic &operator=(ILexic &&other) = delete;
		public:
			virtual bool IsSpace(const wchar_t chr) = 0; // Return whether specified character is space or not
			virtual bool IsNewLine(const wchar_t chr) = 0; // Return whether specified character is line feed or not
			virtual bool IsIdentifier(const wchar_t chr) = 0; // Return whether specified character is allowed in identifier or not
			virtual bool IsIdentifierNotStart(const wchar_t chr) = 0; // Return whether specified character is allowed in identifier but not as start of the one or not
			virtual bool IsIdentifierNotAll(const wchar_t chr) = 0; // Return whether specified character is allowed in identifier but not all the characters of the one or not
			virtual bool IsIdentifierBoundary(const wchar_t chr) = 0; // Return whether specified character is not a part of identifier

			virtual size_t Escape(const size_t index) = 0; // Return index + 2 if character is \ or index otherwise. Used to parse strings having escaped symbols equal to enclosed ones (like ' or "). For example: "Say \"Hello\" to him"
		};
	}
}