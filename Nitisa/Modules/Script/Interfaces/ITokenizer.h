// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Interfaces/IReleasable.h"
#include "../Core/Token.h"
#include "../Core/Tokens.h"

namespace nitisa
{
	namespace script
	{
		class ITokenizer :public virtual IReleasable
		{
		protected:
			ITokenizer() = default;
			~ITokenizer() = default;
			ITokenizer(const ITokenizer &other) = delete;
			ITokenizer(ITokenizer &&other) = delete;
			ITokenizer &operator=(const ITokenizer &other) = delete;
			ITokenizer &operator=(ITokenizer &&other) = delete;
		public:
			virtual bool Next(size_t &index, Token &token) = 0; // Parse token at specified index. Update "index" and store token information in "token"
			virtual bool Next(size_t &index, Tokens &tokens) = 0; // Parse token at specified index, add to tokens list if needed (use grouping). If there are group operators, tokens can be used only after parsing completion
		};
	}
}