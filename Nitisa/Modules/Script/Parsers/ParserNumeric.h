// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Releasable.h"
#include "../Core/Token.h"
#include "../Interfaces/IParser.h"

namespace nitisa
{
	namespace script
	{
		class ILexic;
		class IReader;

		class CParserNumeric :public virtual IParser, public CReleasable
		{
		private:
			IReader *m_pReader;
			ILexic *m_pLexic;
		public:
			// IParser methods
			bool Parse(size_t &index, Token &token) override;

			CParserNumeric(IReader *reader, ILexic *lexic);
		};
	}
}