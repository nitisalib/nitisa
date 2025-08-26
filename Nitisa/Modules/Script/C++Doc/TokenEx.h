// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	namespace script
	{
		struct Token;

		namespace cppdoc
		{
			class TokenEx
			{
			private:
				Token *m_pToken;
				size_t m_iIndex;
			public:
				size_t const &Index{ m_iIndex }; // Either token index or index of the token where macro expanding occured

				TokenEx(script::Token *token, const size_t &index);
				TokenEx(const TokenEx &other) = default;
				TokenEx(TokenEx &&other) = default;

				script::Token *operator->();
				bool operator==(const TokenEx &other) const;
				bool operator!=(const TokenEx &other) const;
				operator script::Token *();
				TokenEx &operator=(const TokenEx &other);
				TokenEx &operator=(TokenEx &&other);
			};
		}
	}
}