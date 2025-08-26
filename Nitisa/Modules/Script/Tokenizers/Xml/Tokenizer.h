// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../../Core/Strings.h"
#include "../../Core/Operators.h"
#include "../../Core/Tokenizer.h"
#include "../../Lexics/Xml/Lexic.h"
#include "../../Parsers/ParserHexadecimal.h"
#include "../../Parsers/ParserIdentifier.h"
#include "../../Parsers/ParserOperator.h"
#include "../../Parsers/ParserString.h"
#include "../../Readers/ReaderSensitive.h"

namespace nitisa
{
	namespace script
	{
		namespace xml
		{
			class CTokenizer :public script::CTokenizer
			{
			private:
				CReaderSensitive m_cReader;
				CLexic m_cLexic;
				CParserOperator m_cParserOperator;
				CParserString m_cParserString;
				CParserIdentifier m_cParserIdentifier;
			public:
				static const Operators Ops; // Operators

				CTokenizer(const String &source);
				CTokenizer(const String &source, const size_t min, const size_t max);
			};
		}
	}
}