// This file is a part of Nitisa framework
// Copyright © 2024 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace script
	{
		namespace generic
		{
			const Operator CTokenizer::OpDoubleQuote{ L"\"", L"\"", StringKeyValueArray{ { L"\\\"", L"\"" } }, false,  true, false, GROUP_NO_SKIP, false, false, false, false, false, false, 255 };
			const Operator CTokenizer::OpSingleQuote{ L"'",   L"'",   StringKeyValueArray{ { L"\\'", L"'" } }, false,  true, false, GROUP_NO_SKIP, false, false, false, false, false, false, 255 };

			const Operators CTokenizer::Ops{
				//             Name         Close              Replace        R.Sp    Seq  MLine           Group Normal  Block  Prior   Post  APrior APost P-ce
				OpSingleQuote,
				OpDoubleQuote,
				Operator{      L"\n", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NEW_LINE, false, false, false, false, false, false, 255 }, // \n
				Operator{      L"\r", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NEW_LINE, false, false, false, false, false, false, 255 }, // \r
				Operator{    L"\r\n", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NEW_LINE, false, false, false, false, false, false, 255 }, // \r\n
				Operator{    L"\\\n", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NEW_LINE, false, false, false, false, false, false, 255 }, // \ + \n
				Operator{    L"\\\r", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NEW_LINE, false, false, false, false, false, false, 255 }, // \ + \r
				Operator{ L"\\\r\\n", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NEW_LINE, false, false, false, false, false, false, 255 }, // \ + \r\n
				Operator{       L" ", EmptyString, EmptyStringKeyValueArray, false, false, false,    GROUP_SPACE, false, false, false, false, false, false, 255 }, // space
				Operator{      L"\t", EmptyString, EmptyStringKeyValueArray, false, false, false,    GROUP_SPACE, false, false, false, false, false, false, 255 }, // tab
				Operator{      L"\v", EmptyString, EmptyStringKeyValueArray, false, false, false,    GROUP_SPACE, false, false, false, false, false, false, 255 }, // vertical 1tab
				Operator{      L"\f", EmptyString, EmptyStringKeyValueArray, false, false, false,    GROUP_SPACE, false, false, false, false, false, false, 255 }, // form feed
				Operator{      L"//",       L"\n", EmptyStringKeyValueArray, false,  true, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }, // //
				Operator{      L"/*",       L"*/", EmptyStringKeyValueArray, false,  true,  true,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }, // /*

				Operator{       L"{",        L"}", EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP, false,  true, false, false, false, false, 255 }, // {
				Operator{       L"}", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }, // }
				Operator{       L"[",        L"]", EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP, false,  true, false, false, false, false, 255 }, // [
				Operator{       L"]", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }, // ]
				Operator{       L"(",        L")", EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP, false,  true, false, false, false, false, 255 }, // (
				Operator{       L")", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }, // )
				Operator{       L":", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  13 }, // :
				Operator{       L"?", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  13 }, // ?
				Operator{      L"::", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   0 }, // ::
				Operator{       L".", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false,  true, false, false, false,   1 }, // .
				Operator{      L"->", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   1 }, // ->
				Operator{       L"~", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP, false, false,  true, false,  true, false, 255 }, // ~
				Operator{       L"!", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP, false, false,  true, false,  true, false, 255 }, // !
				Operator{       L"+", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false,  true, false,  true, false,   4 }, // +
				Operator{       L"-", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false,  true, false,  true, false,   4 }, // -
				Operator{       L"*", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false,  true, false, false, false,   3 }, // *
				Operator{       L"/", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   3 }, // /
				Operator{       L"%", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   3 }, // %
				Operator{       L"^", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  10 }, // ^
				Operator{       L"&", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   9 }, // &
				Operator{       L"|", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  11 }, // |
				Operator{       L"=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }, // =
				Operator{      L"+=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }, // +=
				Operator{      L"-=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }, // -=
				Operator{      L"*=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }, // *=
				Operator{      L"/=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }, // /=
				Operator{      L"%=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }, // %=
				Operator{      L"^=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }, // ^=
				Operator{      L"&=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }, // &=
				Operator{      L"|=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }, // |=
				Operator{      L"==", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   8 }, // ==
				Operator{      L"!=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   8 }, // !=
				Operator{       L"<", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   7 }, // <
				Operator{       L">", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   7 }, // >
				Operator{      L"<=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   7 }, // <=
				Operator{      L">=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   7 }, // >=
				Operator{     L"<=>", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   6 }, // <=>
				Operator{      L"&&", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  12 }, // &&
				Operator{      L"||", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  13 }, // ||
				Operator{      L"<<", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   5 }, // <<
				Operator{      L">>", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   5 }, // >>
				Operator{     L"<<=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  13 }, // <<=
				Operator{     L">>=", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  13 }, // >>=
				Operator{      L"++", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP, false, false,  true,  true,  true,  true, 255 }, // ++
				Operator{      L"--", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP, false, false,  true,  true,  true,  true, 255 }, // --
				Operator{       L",", EmptyString, EmptyStringKeyValueArray, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  15 }, // ,
			};

		#pragma region Constructor & destructor
			CTokenizer::CTokenizer(const String &source) :
				script::CTokenizer(),
				m_cReader{ source },
				m_cLexic{ &m_cReader },
				m_cParserString{ &m_cReader, &m_cLexic, &OpSingleQuote, &OpDoubleQuote },
				m_cParserBinary{ &m_cReader, &m_cLexic },
				m_cParserOctal{ &m_cReader, &m_cLexic },
				m_cParserHexadecimal{ &m_cReader, &m_cLexic },
				m_cParserNumeric{ &m_cReader, &m_cLexic },
				m_cParserOperator{ Ops, &m_cReader, &m_cLexic },
				m_cParserIdentifier{ &m_cReader, &m_cLexic }
			{
				m_pReader = &m_cReader;
				m_pParserOperator = &m_cParserOperator;
				m_pParserString = &m_cParserString;
				m_pParserBinary = &m_cParserBinary;
				m_pParserOctal = &m_cParserOctal;
				m_pParserHexadecimal = &m_cParserHexadecimal;
				m_pParserNumeric = &m_cParserNumeric;
				m_pParserIdentifier = &m_cParserIdentifier;
			}

			CTokenizer::CTokenizer(const String &source, const size_t min, const size_t max) :
				script::CTokenizer(),
				m_cReader{ source, min, max },
				m_cLexic{ &m_cReader },
				m_cParserString{ &m_cReader, &m_cLexic, &OpSingleQuote, &OpDoubleQuote },
				m_cParserBinary{ &m_cReader, &m_cLexic },
				m_cParserOctal{ &m_cReader, &m_cLexic },
				m_cParserHexadecimal{ &m_cReader, &m_cLexic },
				m_cParserNumeric{ &m_cReader, &m_cLexic },
				m_cParserOperator{ Ops, &m_cReader, &m_cLexic },
				m_cParserIdentifier{ &m_cReader, &m_cLexic }
			{
				m_pReader = &m_cReader;
				m_pParserOperator = &m_cParserOperator;
				m_pParserString = &m_cParserString;
				m_pParserBinary = &m_cParserBinary;
				m_pParserOctal = &m_cParserOctal;
				m_pParserHexadecimal = &m_cParserHexadecimal;
				m_pParserNumeric = &m_cParserNumeric;
				m_pParserIdentifier = &m_cParserIdentifier;
			}
		#pragma endregion

		#pragma region ITokenizer methods
			bool CTokenizer::Next(size_t &index, Token &token)
			{
				if (!m_pReader || index < m_pReader->Min || index >= m_pReader->Max)
					return false;
				size_t old_index{ index };
				if (m_pReader->Read(index) == L'.' && m_pParserNumeric->Parse(index, token))
					return true;
				index = old_index;
				return script::CTokenizer::Next(index, token);
			}

			bool CTokenizer::Next(size_t &index, Tokens &tokens)
			{
				return script::CTokenizer::Next(index, tokens);
			}
		#pragma endregion
		}
	}
}