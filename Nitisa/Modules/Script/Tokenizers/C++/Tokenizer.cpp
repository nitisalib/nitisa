// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
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
		namespace cpp
		{
			const String EMPTY;
			const StringKeyValueArray REPL_EMPTY{ };
			const StringKeyValueArray REPL_SNG_QUOTE{ StringKeyValue{ L"\\'", L"'" } };
			const StringKeyValueArray REPL_DBL_QUOTE{ StringKeyValue{ L"\\\"", L"\"" } };
			const StringKeyValueArray REPL_DBL_SLASH{ StringKeyValue{ L"\\\r\n", L"" }, StringKeyValue{ L"\\\n", L"" } , StringKeyValue{ L"\\\r", L"" } };

			// Not in operators list
			const Operator CTokenizer::Op2Greater					{      L">>", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   5 };
			
			const Operator CTokenizer::OpSingleQuote				{       L"'",  L"'", REPL_SNG_QUOTE, false,  true, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 };
			const Operator CTokenizer::OpDoubleQuote				{      L"\"", L"\"", REPL_DBL_QUOTE, false,  true, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 };
			const Operator CTokenizer::OpN							{      L"\n", EMPTY,     REPL_EMPTY, false, false, false, GROUP_NEW_LINE, false, false, false, false, false, false, 255 }; // \n
			const Operator CTokenizer::OpR							{      L"\r", EMPTY,     REPL_EMPTY, false, false, false, GROUP_NEW_LINE, false, false, false, false, false, false, 255 }; // \r
			const Operator CTokenizer::OpRN							{    L"\r\n", EMPTY,     REPL_EMPTY, false, false, false, GROUP_NEW_LINE, false, false, false, false, false, false, 255 }; // \r\n
			const Operator CTokenizer::OpBackSlashN					{    L"\\\n", EMPTY,     REPL_EMPTY, false, false, false,     GROUP_SKIP, false, false, false, false, false, false, 255 }; // \ + \n Means command continue on the next line
			const Operator CTokenizer::OpBackSlashR					{    L"\\\r", EMPTY,     REPL_EMPTY, false, false, false,     GROUP_SKIP, false, false, false, false, false, false, 255 }; // \ + \r Means command continue on the next line
			const Operator CTokenizer::OpBackSlashRN				{ L"\\\r\\n", EMPTY,     REPL_EMPTY, false, false, false,     GROUP_SKIP, false, false, false, false, false, false, 255 }; // \ + \r\n Means command continue on the next line
			const Operator CTokenizer::OpSpace						{       L" ", EMPTY,     REPL_EMPTY, false, false, false,    GROUP_SPACE, false, false, false, false, false, false, 255 }; // space
			const Operator CTokenizer::OpTab						{      L"\t", EMPTY,     REPL_EMPTY, false, false, false,    GROUP_SPACE, false, false, false, false, false, false, 255 }; // tab
			const Operator CTokenizer::OpVTab						{      L"\v", EMPTY,     REPL_EMPTY, false, false, false,     GROUP_SKIP, false, false, false, false, false, false, 255 }; // vertical 1tab
			const Operator CTokenizer::OpFormFeed					{      L"\f", EMPTY,     REPL_EMPTY, false, false, false,     GROUP_SKIP, false, false, false, false, false, false, 255 }; // form feed
			const Operator CTokenizer::Op2Slash						{      L"//", L"\n", REPL_DBL_SLASH, false,  true, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // //
			const Operator CTokenizer::OpSlashAsterisk				{      L"/*", L"*/",     REPL_EMPTY, false,  true,  true,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // /*
			const Operator CTokenizer::Op3Dot						{     L"...", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false,  true, false, false, 255 }; // ...
			const Operator CTokenizer::OpHash						{       L"#", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // #
			const Operator CTokenizer::Op2Hash						{      L"##", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // ##
			const Operator CTokenizer::OpPercentColon				{      L"%:", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // %: eqvivalent to #
			const Operator CTokenizer::OpPercentColonPercentColon	{    L"%:%:", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // %:%: eqvivalent to ##
			const Operator CTokenizer::OpOpenBrace					{       L"{",  L"}",     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false,  true, false, false, false, false, 255 }; // {
			const Operator CTokenizer::OpCloseBrace					{       L"}", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // }
			const Operator CTokenizer::OpOpenBracket				{       L"[",  L"]",     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false,  true, false, false, false, false, 255 }; // [
			const Operator CTokenizer::OpCloseBracket				{       L"]", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // ]
			const Operator CTokenizer::OpOpenParenthese				{       L"(",  L")",     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false,  true, false, false, false, false, 255 }; // (
			const Operator CTokenizer::OpCloseParenthese			{       L")", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // )
			const Operator CTokenizer::OpLessColon					{      L"<:", L":>",     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false,  true, false, false, false, false, 255 }; // <: eqvivalent to [
			const Operator CTokenizer::OpColonGreater				{      L":>", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // :> eqvivalent to ]
			const Operator CTokenizer::OpLessPercent				{      L"<%", L"%>",     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false,  true, false, false, false, false, 255 }; // <% eqvivalent to {
			const Operator CTokenizer::OpPercentGreater				{      L"%>", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // %> eqvivalent to }
			const Operator CTokenizer::Op2SquareOpenBracket			{      L"[[", L"]]",     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false,  true, false, false, false, false, 255 }; // [[
			const Operator CTokenizer::Op2SquareCloseBracket		{      L"]]", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // ]]
			const Operator CTokenizer::OpSemicolon					{       L";", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false, 255 }; // ;
			const Operator CTokenizer::OpColon						{       L":", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  13 }; // :
			const Operator CTokenizer::OpQuestion					{       L"?", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  13 }; // ?
			const Operator CTokenizer::Op2Colon						{      L"::", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false, false, false, false, false,   0 }; // ::
			const Operator CTokenizer::OpDot						{       L".", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false,  true, false, false, false,   1 }; // .
			const Operator CTokenizer::OpDotAsterisk				{      L".*", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   2 }; // .*
			const Operator CTokenizer::OpMinusGreater				{      L"->", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   1 }; // ->
			const Operator CTokenizer::OpMinusGreaterAsterisk		{     L"->*", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   2 }; // ->*
			const Operator CTokenizer::OpTilde						{       L"~", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false,  true, false,  true, false, 255 }; // ~
			const Operator CTokenizer::OpExclamation				{       L"!", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false,  true, false,  true, false, 255 }; // !
			const Operator CTokenizer::OpPlus						{       L"+", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false,  true, false,  true, false,   4 }; // +
			const Operator CTokenizer::OpMinus						{       L"-", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false,  true, false,  true, false,   4 }; // -
			const Operator CTokenizer::OpAsterisk					{       L"*", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false,  true,  true,  true, false,   3 }; // *
			const Operator CTokenizer::OpSlash						{       L"/", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   3 }; // /
			const Operator CTokenizer::OpPercent					{       L"%", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   3 }; // %
			const Operator CTokenizer::OpCaret						{       L"^", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  10 }; // ^
			const Operator CTokenizer::OpAmpersand					{       L"&", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false,  true,  true,  true, false,   9 }; // &
			const Operator CTokenizer::OpPipe						{       L"|", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  11 }; // |
			const Operator CTokenizer::OpEquals						{       L"=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // =
			const Operator CTokenizer::OpPlusEquals					{      L"+=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // +=
			const Operator CTokenizer::OpMinusEquals				{      L"-=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // -=
			const Operator CTokenizer::OpAsteriskEquals				{      L"*=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // *=
			const Operator CTokenizer::OpSlashEquals				{      L"/=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // /=
			const Operator CTokenizer::OpPercentEquals				{      L"%=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // %=
			const Operator CTokenizer::OpCaretEquals				{      L"^=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // ^=
			const Operator CTokenizer::OpAmpersandEquals			{      L"&=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // &=
			const Operator CTokenizer::OpPipeEquals					{      L"|=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // |=
			const Operator CTokenizer::Op2Equals					{      L"==", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   8 }; // ==
			const Operator CTokenizer::OpExclamationEquals			{      L"!=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   8 }; // !=
			const Operator CTokenizer::OpLess						{       L"<",  L">",     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true,  true, false, false, false, false,   7 }; // <
			const Operator CTokenizer::OpGreater					{       L">", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   7 }; // >
			const Operator CTokenizer::OpLessEquals					{      L"<=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   7 }; // <=
			const Operator CTokenizer::OpGreaterEquals				{      L">=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   7 }; // >=
			const Operator CTokenizer::OpLessEqualsGreater			{     L"<=>", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   6 }; // <=>
			const Operator CTokenizer::Op2Ampersand					{      L"&&", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  12 }; // &&
			const Operator CTokenizer::Op2Pipe						{      L"||", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  13 }; // ||
			const Operator CTokenizer::Op2Less						{      L"<<", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   5 }; // <<
			const Operator CTokenizer::Op2LessEquals				{     L"<<=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  13 }; // <<=
			const Operator CTokenizer::Op2GreaterEquals				{     L">>=", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  13 }; // >>=
			const Operator CTokenizer::Op2Plus						{      L"++", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false,  true,  true,  true,  true, 255 }; // ++
			const Operator CTokenizer::Op2Minus						{      L"--", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP, false, false,  true,  true,  true,  true, 255 }; // --
			const Operator CTokenizer::OpComma						{       L",", EMPTY,     REPL_EMPTY, false, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  15 }; // ,
			const Operator CTokenizer::OpAnd						{     L"and", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  12 }; // and eqvivalent to &&
			const Operator CTokenizer::OpOr							{      L"or", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  12 }; // or eqvivalent to ||
			const Operator CTokenizer::OpXor						{     L"xor", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  10 }; // xor eqvivalent to ^
			const Operator CTokenizer::OpNot						{     L"not", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP, false, false,  true, false,  true, false, 255 }; // not eqvivalent to !
			const Operator CTokenizer::OpBitAnd						{  L"bitand", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   9 }; // bitend eqvivalent to &
			const Operator CTokenizer::OpBitOr						{   L"bitor", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  11 }; // bitor eqvivalent to |
			const Operator CTokenizer::OpCompl						{   L"compl", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP, false, false,  true, false, false, false, 255 }; // compl eqvivalent to ~
			const Operator CTokenizer::OpAndEq						{  L"and_eq", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // and_eq eqvivalent to &=
			const Operator CTokenizer::OpOrEq						{   L"or_eq", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // or_eq eqvivalent to |=
			const Operator CTokenizer::OpXorEq						{  L"xor_eq", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,  14 }; // xor_eq eqvivalent to ^=
			const Operator CTokenizer::OpNotEq						{  L"not_eq", EMPTY,     REPL_EMPTY,  true, false, false,  GROUP_NO_SKIP,  true, false, false, false, false, false,   8 }; // not_eq eqvivalent to !=

			const Operators CTokenizer::Ops{
				OpSingleQuote,
				OpDoubleQuote,
				OpN,
				OpR,
				OpRN,
				OpBackSlashN,
				OpBackSlashR,
				OpBackSlashRN,
				OpSpace,
				OpTab,
				OpVTab,
				OpFormFeed,
				Op2Slash,
				OpSlashAsterisk,
				Op3Dot,
				OpHash,
				Op2Hash,
				OpPercentColon,
				OpPercentColonPercentColon,
				OpOpenBrace,
				OpCloseBrace,
				OpOpenBracket,
				OpCloseBracket,
				OpOpenParenthese,
				OpCloseParenthese,
				OpLessColon,
				OpColonGreater,
				OpLessPercent,
				OpPercentGreater,
				Op2SquareOpenBracket,
				Op2SquareCloseBracket,
				OpSemicolon,
				OpColon,
				OpQuestion,
				Op2Colon,
				OpDot,
				OpDotAsterisk,
				OpMinusGreater,
				OpMinusGreaterAsterisk,
				OpTilde,
				OpExclamation,
				OpPlus,
				OpMinus,
				OpAsterisk,
				OpSlash,
				OpPercent,
				OpCaret,
				OpAmpersand,
				OpPipe,
				OpEquals,
				OpPlusEquals,
				OpMinusEquals,
				OpAsteriskEquals,
				OpSlashEquals,
				OpPercentEquals,
				OpCaretEquals,
				OpAmpersandEquals,
				OpPipeEquals,
				Op2Equals,
				OpExclamationEquals,
				OpLess,
				OpGreater,
				OpLessEquals,
				OpGreaterEquals,
				OpLessEqualsGreater,
				Op2Ampersand,
				Op2Pipe,
				Op2Less,
				Op2LessEquals,
				Op2GreaterEquals,
				Op2Plus,
				Op2Minus,
				OpComma,
				OpAnd,
				OpOr,
				OpXor,
				OpNot,
				OpBitAnd,
				OpBitOr,
				OpCompl,
				OpAndEq,
				OpOrEq,
				OpXorEq,
				OpNotEq
			};

		#pragma region Constructor & destructor
			CTokenizer::CTokenizer(const Groups &skip_groups) :
				script::CTokenizer(skip_groups),
				m_cLexic{ &m_cReader },
				m_cParserOperator{ Ops, &m_cReader, &m_cLexic },
				m_cParserString{ &m_cReader, &m_cLexic, &OpSingleQuote, &OpDoubleQuote },
				m_cParserBinary{ &m_cReader, &m_cLexic },
				m_cParserOctal{ &m_cReader, &m_cLexic },
				m_cParserHexadecimal{ &m_cReader, &m_cLexic },
				m_cParserNumeric{ &m_cReader, &m_cLexic },
				m_cParserIdentifier{ &m_cReader, &m_cLexic }
			{
				m_pReader = &m_cReader;
				m_pReaderSensitive = &m_cReader;
				m_pParserOperator = &m_cParserOperator;
				m_pParserString = &m_cParserString;
				m_pParserBinary = &m_cParserBinary;
				m_pParserOctal = &m_cParserOctal;
				m_pParserHexadecimal = &m_cParserHexadecimal;
				m_pParserNumeric = &m_cParserNumeric;
				m_pParserIdentifier = &m_cParserIdentifier;
			}

			CTokenizer::CTokenizer(const String &source, const Groups &skip_groups) :
				script::CTokenizer(skip_groups),
				m_cReader{ source },
				m_cLexic{ &m_cReader },
				m_cParserOperator{ Ops, &m_cReader, &m_cLexic },
				m_cParserString{ &m_cReader, &m_cLexic, &OpSingleQuote, &OpDoubleQuote },
				m_cParserBinary{ &m_cReader, &m_cLexic },
				m_cParserOctal{ &m_cReader, &m_cLexic },
				m_cParserHexadecimal{ &m_cReader, &m_cLexic },
				m_cParserNumeric{ &m_cReader, &m_cLexic },
				m_cParserIdentifier{ &m_cReader, &m_cLexic }
			{
				m_pReader = &m_cReader;
				m_pReaderSensitive = &m_cReader;
				m_pParserOperator = &m_cParserOperator;
				m_pParserString = &m_cParserString;
				m_pParserBinary = &m_cParserBinary;
				m_pParserOctal = &m_cParserOctal;
				m_pParserHexadecimal = &m_cParserHexadecimal;
				m_pParserNumeric = &m_cParserNumeric;
				m_pParserIdentifier = &m_cParserIdentifier;
			}

			CTokenizer::CTokenizer(const String &source, const size_t min, const size_t max, const Groups &skip_groups) :
				script::CTokenizer(skip_groups),
				m_cReader{ source, min, max },
				m_cLexic{ &m_cReader },
				m_cParserOperator{ Ops, &m_cReader, &m_cLexic },
				m_cParserString{ &m_cReader, &m_cLexic, &OpSingleQuote, &OpDoubleQuote },
				m_cParserBinary{ &m_cReader, &m_cLexic },
				m_cParserOctal{ &m_cReader, &m_cLexic },
				m_cParserHexadecimal{ &m_cReader, &m_cLexic },
				m_cParserNumeric{ &m_cReader, &m_cLexic },
				m_cParserIdentifier{ &m_cReader, &m_cLexic }
			{
				m_pReader = &m_cReader;
				m_pReaderSensitive = &m_cReader;
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