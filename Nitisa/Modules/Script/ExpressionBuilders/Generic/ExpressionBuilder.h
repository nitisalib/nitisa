// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../../Core/Aliases.h"
#include "../../../../Core/Releasable.h"
#include "../../../../Core/Strings.h"
#include "../../Core/PostfixType.h"
#include "../../Core/PrefixType.h"
#include "../../Core/Tokens.h"
#include "../../Interfaces/IExpressionBuilder.h"
#include <vector>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IExpression;
		class ITokenizer;

		namespace generic
		{
			class CExpressionBuilder :public virtual IExpressionBuilder, public virtual CReleasable
			{
			private:
				const Token *m_pTokens;
				IErrorListener *m_pErrorListener;
				size_t m_iMaxTokenIndex;
				size_t m_iMinTokenIndex;

				StringKeyValueArray m_aCastOperators;
				StringKeyValueArray m_aCallOperators;
				StringKeyValueArray m_aBraceOperators;
				StringKeyValueArray m_aSubscriptOperators;
				StringArray m_aComments;
				StringArray m_aPointers;
				StringArray m_aTrueKeywords;
				StringArray m_aFalseKeywords;
				StringArray m_aNullKeywords;
				StringArray m_aDataTypes;
				StringArray m_aMemberAccessOperators;
				bool m_bCaseSensitive;
				bool m_bAllowUserDefinedLiterals;
				bool m_bAllowStringConcatenation;
				bool m_bAllowPrecedence;
				std::vector<uint> m_aSkipGroups;
				String m_sTernaryOperator1;
				String m_sTernaryOperator2;

				StringArray m_aTrueKeywordsPrepared;
				StringArray m_aFalseKeywordsPrepared;
				StringArray m_aNullKeywordsPrepared;
				StringArray m_aDataTypesPrepared;

				void PrepareKeywords(const StringArray &source, StringArray &target);
				const Token *Next(const Token *token, const bool do_next) const;
				const Token *Prev(const Token *token) const;
				bool ReArrange(IExpression *expression) const;
				bool SearchOperand(const Token *token, const Token **target, const String &close) const;
				bool AddPriorOperators(IExpression *operand, const Token *current_token, const Token *operand_token) const;
				bool AddPosteriorOperators(IExpression *prev, const Token **token, const String &close) const;
				bool AddOperators(IExpression *prev, IExpression *operand, const Token *prev_next_token, const Token *operand_token, IExpression **op) const;
				PrefixType CalculatePrefixType(const String &prefix, const String &postfix, bool &is_raw, String &raw_separator) const;
				PostfixType CalculatePostfixType(const String &postfix) const;
				bool isKeyword(const String &value, const StringArray &keywords) const;
				bool isCast(const Token *token, size_t &operator_index) const;
				bool has(const String &value, const StringKeyValueArray &list) const;
				bool has(const String &value, const StringKeyValueArray &list, size_t &index) const;
				bool MakeMemberAccess(IExpression **sequence) const;
				bool MakeTernary(IExpression *sequence) const;

				bool DecodeSequence(const Token **token, IExpression **target, const String &close) const;
				bool DecodeOperand(const Token *token, IExpression **target, const Token **next_token) const;
				bool DecodeInteger(const Token *token, IExpression **target, const Token **next_token) const;
				bool DecodeFloat(const Token *token, IExpression **target, const Token **next_token) const;
				bool DecodeString(const Token *token, IExpression **target, const Token **next_token) const;
				bool DecodeTrue(const Token *token, IExpression **target, const Token **next_token) const;
				bool DecodeFalse(const Token *token, IExpression **target, const Token **next_token) const;
				bool DecodeNull(const Token *token, IExpression **target, const Token **next_token) const;
				bool DecodeIdentifier(const Token *token, IExpression **target, const Token **next_token) const;
				bool DecodeCast(const Token *token, IExpression **target, const Token **next_token, IExpression *name, size_t operator_index) const;
				bool DecodeCall(const Token *token, IExpression **target, const Token **next_token, IExpression *name, size_t operator_index) const;
				bool DecodeBrace(const Token *token, IExpression **target, const Token **next_token, IExpression *name, size_t operator_index) const;
				bool DecodeSubscript(const Token *token, IExpression **target, const Token **next_token, IExpression *name, size_t operator_index) const;
			public:
				IErrorListener* &ErrorListener{ m_pErrorListener }; // Error listener or nullptr
				StringKeyValueArray &CastOperators{ m_aCastOperators }; // Default: "(". If empty, casts disabled
				StringKeyValueArray &CallOperators{ m_aCallOperators }; // Default: "(". If empty, calls disabled
				StringKeyValueArray &BraceOperators{ m_aBraceOperators }; // Default: "{". If empty, brace blocks disabled
				StringKeyValueArray &SubscriptOperators{ m_aSubscriptOperators }; // Default: "[". If empty, subscripts disabled
				StringArray &Comments{ m_aComments }; // Default: "/*" and "//". If empty, comments disabled
				StringArray &Pointers{ m_aPointers }; // Default: "*" and "&". If empty, no pointers allowed
				StringArray &TrueKeywords{ m_aTrueKeywords }; // Default: "true". If empty, "true" is treated as identifier otherwise as "true" literal
				StringArray &FalseKeywords{ m_aFalseKeywords }; // Default: "false". If empty, "false" is treated as identifier otherwise as "false" literal
				StringArray &NullKeywords{ m_aNullKeywords }; // Default: "nullptr". If empty, "nullptr" is treated as identifier otherwise as "nullptr" literal
				StringArray &DataTypes{ m_aDataTypes }; // Default: { "bool", "double", "float", "int", "int64", "Integer", "String" }. If empty, casts disabled
				StringArray &MemberAccessOperators{ m_aMemberAccessOperators }; // Default: "::", "." and "->"
				bool &CaseSensitive{ m_bCaseSensitive }; // Whether case match is required during keyword recognition. Default: true
				bool &AllowUserDefinedLiterals{ m_bAllowUserDefinedLiterals }; // Whether user-defined literals allowed after integers, floats and strings (identifier after integer, float, string token). Default: true
				bool &AllowStringConcatenation{ m_bAllowStringConcatenation }; // Whether strings standing near each other should be treated as one string. Default: true
				bool &AllowPrecedence{ m_bAllowPrecedence }; // Whether sequences should be re-arranged accordingly to operators precedence order. Default: true
				std::vector<uint> &SkipGroups{ m_aSkipGroups }; // Operator group ids which should be ignored. Default: { GROUP_SPACE, GROUP_NEW_LINE, GROUP_SEPARATOR }
				String &TernaryOperator1{ m_sTernaryOperator1 }; // First part of ternary operator. Default: "?". If empty, no ternary wrapping allowed
				String &TernaryOperator2{ m_sTernaryOperator2 }; // Second part of ternary operator. Default: ":". If empty, no ternary wrapping allowed

				// IExpressionBuilder methods
				bool Build(ITokenizer *tokenizer, IExpression **target) override;
				bool Build(const Tokens &tokens, IExpression **target) override;
				bool Build(const Tokens &tokens, const size_t first, const size_t last, IExpression **target) override;

				CExpressionBuilder();
			};
		}
	}
}