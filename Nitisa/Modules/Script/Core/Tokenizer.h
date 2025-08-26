// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Releasable.h"
#include "../Core/Groups.h"
#include "../Core/Token.h"
#include "../Core/Tokens.h"
#include "../Interfaces/ITokenizer.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	namespace script
	{
		class IParser;
		class IReader;

		class CTokenizer :public virtual ITokenizer, public CReleasable
		{
		protected:
			~CTokenizer() = default;
			CTokenizer(const CTokenizer &other) = delete;
			CTokenizer(CTokenizer &&other) = delete;
			CTokenizer &operator=(const CTokenizer &other) = delete;
			CTokenizer &operator=(CTokenizer &&other) = delete;
		protected:
			IReader *m_pReader; // Pointer to source reader or nullptr
			IParser *m_pParserOperator; // Pointer to operator parser or nullptr
			IParser *m_pParserString; // Pointer to string parser or nullptr
			IParser *m_pParserBinary; // Pointer to binary number parser or nullptr
			IParser *m_pParserOctal; // Pointer to octal number parser or nullptr
			IParser *m_pParserHexadecimal; // Pointer to hexadecimal number parser or nullptr
			IParser *m_pParserNumeric; // Pointer to numerical value parser or nullptr
			IParser *m_pParserIdentifier; // Pointer to identifier parser or nullptr
			Groups m_aSkipGroups;

			CTokenizer(const Groups &skip_groups = {}); // Constructor
		public:
			void setSkipGroups(const Groups &skip_groups);

			// ITokenizer methods
			bool Next(size_t &index, Token &token) override;
			bool Next(size_t &index, Tokens &tokens) override;
		};
	}
}