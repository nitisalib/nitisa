// This file is a part of Nitisa framework
// Copyright © 2024 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Releasable.h"
#include "../../../Core/Strings.h"
#include "../Core/Token.h"
#include "../Interfaces/IParser.h"

namespace nitisa
{
	namespace script
	{
		class ILexic;
		class IReader;

		class CParserString :public virtual IParser, public CReleasable
		{
		private:
			IReader *m_pReader;
			ILexic *m_pLexic;

			bool CheckName(const String &name, const size_t index);
			bool CheckNames(const StringKeyValueArray &names, const size_t index, size_t &name_index);
			size_t Find(const String &substring, const size_t start, const bool multiline);
		public:
			// IParser methods
			bool Parse(size_t &index, Token &token) override;

			CParserString(IReader *reader, ILexic *lexic);
		};
	}
}