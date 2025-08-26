// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../../Core/Strings.h"
#include "../../Core/Operator.h"
#include "../../Core/Operators.h"
#include "../../Core/Tokenizer.h"
#include "../../Lexics/C++/Lexic.h"
#include "../../Parsers/C++/ParserBinary.h"
#include "../../Parsers/C++/ParserHexadecimal.h"
#include "../../Parsers/C++/ParserNumeric.h"
#include "../../Parsers/C++/ParserOctal.h"
#include "../../Parsers/C++/ParserString.h"
#include "../../Parsers/ParserIdentifier.h"
#include "../../Parsers/ParserOperator.h"
#include "../../Readers/ReaderSensitive.h"

namespace nitisa
{
	namespace script
	{
		namespace generic
		{
			class CTokenizer :public script::CTokenizer
			{
			private:
				CReaderSensitive m_cReader;
				cpp::CLexic m_cLexic;
				cpp::CParserString m_cParserString;
				cpp::CParserBinary m_cParserBinary;
				cpp::CParserOctal m_cParserOctal;
				cpp::CParserHexadecimal m_cParserHexadecimal;
				cpp::CParserNumeric m_cParserNumeric;
				CParserOperator m_cParserOperator;
				CParserIdentifier m_cParserIdentifier;

				static const Operator OpDoubleQuote;
				static const Operator OpSingleQuote;
			public:
				static const Operators Ops; // Operators

				// ITokenizer methods
				bool Next(size_t &index, Token &token) override; // Changes only parsing order: attempts to parse numerical value first if it starts from "." (like, ".1f")
				bool Next(size_t &index, Tokens &tokens) override;

				CTokenizer(const String &source);
				CTokenizer(const String &source, const size_t min, const size_t max);
			};
		}
	}
}