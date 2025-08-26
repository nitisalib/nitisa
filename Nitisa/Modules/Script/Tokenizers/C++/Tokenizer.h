// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../../Core/Strings.h"
#include "../../Core/Groups.h"
#include "../../Core/Operator.h"
#include "../../Core/Operators.h"
#include "../../Core/Tokenizer.h"
#include "../../Lexics/C++/Lexic.h"
#include "../../Parsers/C++/ParserBinary.h"
#include "../../Parsers/C++/ParserHexadecimal.h"
#include "../../Parsers/C++/ParserNumeric.h"
#include "../../Parsers/C++/ParserOctal.h"
#include "../../Parsers/C++/ParserOperator.h"
#include "../../Parsers/C++/ParserString.h"
#include "../../Parsers/ParserIdentifier.h"
#include "../../Readers/ReaderSensitive.h"

namespace nitisa
{
	namespace script
	{
		namespace cpp
		{
			class CTokenizer :public script::CTokenizer
			{
			private:
				CReaderSensitive m_cReader;
				CReaderSensitive *m_pReaderSensitive;
				CLexic m_cLexic;
				CParserOperator m_cParserOperator;
				CParserString m_cParserString;
				CParserBinary m_cParserBinary;
				CParserOctal m_cParserOctal;
				CParserHexadecimal m_cParserHexadecimal;
				CParserNumeric m_cParserNumeric;
				CParserIdentifier m_cParserIdentifier;
			public:
				static const Operator Op2Greater;
				static const Operator OpSingleQuote;
				static const Operator OpDoubleQuote;
				static const Operator OpN;
				static const Operator OpR;
				static const Operator OpRN;
				static const Operator OpBackSlashN;
				static const Operator OpBackSlashR;
				static const Operator OpBackSlashRN;
				static const Operator OpSpace;
				static const Operator OpTab;
				static const Operator OpVTab;
				static const Operator OpFormFeed;
				static const Operator Op2Slash;
				static const Operator OpSlashAsterisk;
				static const Operator Op3Dot;
				static const Operator OpHash;
				static const Operator Op2Hash;
				static const Operator OpPercentColon;
				static const Operator OpPercentColonPercentColon;
				static const Operator OpOpenBrace;
				static const Operator OpCloseBrace;
				static const Operator OpOpenBracket;
				static const Operator OpCloseBracket;
				static const Operator OpOpenParenthese;
				static const Operator OpCloseParenthese;
				static const Operator OpLessColon;
				static const Operator OpColonGreater;
				static const Operator OpLessPercent;
				static const Operator OpPercentGreater;
				static const Operator Op2SquareOpenBracket;
				static const Operator Op2SquareCloseBracket;
				static const Operator OpSemicolon;
				static const Operator OpColon;
				static const Operator OpQuestion;
				static const Operator Op2Colon;
				static const Operator OpDot;
				static const Operator OpDotAsterisk;
				static const Operator OpMinusGreater;
				static const Operator OpMinusGreaterAsterisk;
				static const Operator OpTilde;
				static const Operator OpExclamation;
				static const Operator OpPlus;
				static const Operator OpMinus;
				static const Operator OpAsterisk;
				static const Operator OpSlash;
				static const Operator OpPercent;
				static const Operator OpCaret;
				static const Operator OpAmpersand;
				static const Operator OpPipe;
				static const Operator OpEquals;
				static const Operator OpPlusEquals;
				static const Operator OpMinusEquals;
				static const Operator OpAsteriskEquals;
				static const Operator OpSlashEquals;
				static const Operator OpPercentEquals;
				static const Operator OpCaretEquals;
				static const Operator OpAmpersandEquals;
				static const Operator OpPipeEquals;
				static const Operator Op2Equals;
				static const Operator OpExclamationEquals;
				static const Operator OpLess;
				static const Operator OpGreater;
				static const Operator OpLessEquals;
				static const Operator OpGreaterEquals;
				static const Operator OpLessEqualsGreater;
				static const Operator Op2Ampersand;
				static const Operator Op2Pipe;
				static const Operator Op2Less;
				static const Operator Op2LessEquals;
				static const Operator Op2GreaterEquals;
				static const Operator Op2Plus;
				static const Operator Op2Minus;
				static const Operator OpComma;
				static const Operator OpAnd;
				static const Operator OpOr;
				static const Operator OpXor;
				static const Operator OpNot;
				static const Operator OpBitAnd;
				static const Operator OpBitOr;
				static const Operator OpCompl;
				static const Operator OpAndEq;
				static const Operator OpOrEq;
				static const Operator OpXorEq;
				static const Operator OpNotEq;

				static const Operators Ops; // Operators

				CReaderSensitive *const &Reader{ m_pReaderSensitive };

				// ITokenizer methods
				bool Next(size_t &index, Token &token) override; // Changes only parsing order: attempts to parse numerical value first if it starts from "." (like, ".1f")
				bool Next(size_t &index, Tokens &tokens) override;

				CTokenizer(const Groups &skip_groups = {});
				CTokenizer(const String &source, const Groups &skip_groups = {});
				CTokenizer(const String &source, const size_t min, const size_t max, const Groups &skip_groups = {});
			};
		}
	}
}