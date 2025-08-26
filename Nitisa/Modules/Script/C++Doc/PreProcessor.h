// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../Core/Token.h"
#include "../Core/Tokens.h"
#include "../Tokenizers/C++/Tokenizer.h"
#include "List.h"
#include "PList.h"
#include <unordered_map>
#include <utility>
#include <vector>

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IProgressListener;

		namespace cppdoc
		{
			class CDefinition;
			class CExpression;

			// #error/#warning/#line/#include are skipped.
			// Only #pragma push_macro and #pragma pop_macro are processed. Other pragmas are skipped.
			class CPreProcessor
			{
			private:
				using Argument = std::pair<List *, List *>;
				using Arguments = std::vector<Argument>;
				using PExpression = CExpression *;
				using PToken = Token *;
			private:
				cpp::CTokenizer &m_cTokenizer;
				std::vector<Token*> &m_aTokens; // Created tokens will be added to this list
				IErrorListener *m_pErrorListener;
				IProgressListener *m_pProgressListener;
				std::unordered_map<String, CDefinition *> m_aDefinitions;
				StringArray m_aIncludePathes;
				StringArray m_aHasIncludes;
				StringArray m_aHasAttributes;
				std::vector<CDefinition *> m_aStoredDefinitions;
				bool m_bAborted;

				static const StringArray PP_HASH;
				static const StringArray PP_2HASH;

				// Definitions and directives cannot have new lines or single-line comments because they mean directive end
				bool AddDefinition(CDefinition *definition, List *begin, const size_t &name_token_index, bool &is_copy); // "first" points to name, "last" points to the last token of definition(the one before line feed/eof)
				void ClearStoredDefinitions();
				CDefinition *PopStoredDefinition(const String &name);

				// Helpers
				size_t FindArgumentIndex(const String &name, const StringArray &parameters) const;
				bool ShouldSkip(const Token &token) const; // Whether token is space or multi-line comment
				void DeleteUnusedTokens(PList &head); // Remove all spaces, collapse adjacent new lines into single token, remove leading and trailing new lines

				// Error helpers
				void E_DefinitionExists(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_DuplicateVariadic(const AnsiString &function, int line, const size_t &index);
				void E_ExpectedParameter(const AnsiString &function, int line, const size_t &index);
				void E_ExpectedComma(const AnsiString &function, int line, const size_t &index, const String &token);
				void E_UnexpectedEnd(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_ExpectedHash(const AnsiString &function, int line, const size_t &index);
				void E_ExpectedDefineAfterHash(const AnsiString &function, int line, const size_t &index);
				void E_ExpectedIdentifierAfterDefine(const AnsiString &function, int line, const size_t &index);
				void E_UnexpectedEndExpectedIdentifier(const AnsiString &function, int line, const size_t &index);
				void E_ExpectedIdentifier(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_UnknownDirective(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_UnexpectedEndExpectedExpression(const AnsiString &function, int line, const size_t &index);
				void E_UnfinishedBranch(const AnsiString &function, int line, const size_t &index);
				void E_ExpectedToken(const AnsiString &function, int line, const size_t &index, const String &expected, const String &found);
				void E_ExpectedAnsiString(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_UnexpectedToken(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_TooFewArguments(const AnsiString &function, int line, const size_t &index, const size_t &count, const size_t &expected);
				void E_InvalidArgumentCount(const AnsiString &function, int line, const size_t &index, const size_t &count, const size_t &expected);
				void E_MissingPrevConcatinateArgument(const AnsiString &function, int line, const size_t &index);
				void E_MissingNextConcatinateArgument(const AnsiString &function, int line, const size_t &index);
				void E_InvalidPrevConcatinateArgument(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_InvalidNextConcatinateArgument(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_ExpectedExpression(const AnsiString &function, int line, const size_t &index);
				void E_ExpectedNewLine(const AnsiString &function, int line, const size_t &index);
				void E_ExpectedOperand(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_UnexpectedEndExpectedOperand(const AnsiString &function, int line, const size_t &index);
				void E_ExpectedOperator(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_InvalidExpression(const AnsiString &function, int line, const size_t &index);
				void E_UnsupportedOperator(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_InvalidOperand(const AnsiString &function, int line, const size_t &index, const String &name);
				void E_ExpectedOneArgument(const AnsiString &function, int line, const size_t &index, const size_t &count);
				void E_UnexpectedPriorOperators(const AnsiString &function, int line, const size_t &index);
				void E_UnknownFunction(const AnsiString &function, int line, const size_t &index, const String &name);

				List *FindNewLineOrSLComment(List &list); // Return either pointer to new lines/single-line comment or nullptr
				List *FindNewLineOrSLCommentOrTail(List &list); // Return either pointer to new lines/single-line comment or to the last token in the list
				List *FindEndIf(List &list);
				List *FindBranchEnd(List &list);
				List *FindCommaOrBracketClose(List &list);
				List *FindBracketClose(List &list);
				List *FindGreater(List &list);

				bool isCondition(List &list);
				bool isBranchEnd(List &list);
				bool isEndIf(List &list);
				bool isStringification(List &list);
				bool isConcatenation(List &list);
				bool isVaArgs(List &list);
				bool isVaOpt(List &list);

				// "out" always points to the next item after the last processed one
				bool ProcessList(PList &target, PList &tail, List &list, const size_t &token_index);
				bool ProcessDirective(PList &target, PList &tail, List &list, PList &out); // "List" points to directive name (if, define, etc)
				bool ProcessError(PList &target, PList &tail, List &list, PList &out); // "List" points to "error"
				bool ProcessWarning(PList &target, PList &tail, List &list, PList &out); // "List" points to "warning"
				bool ProcessLine(PList &target, PList &tail, List &list, PList &out); // "List" points to "line"
				bool ProcessUnDef(PList &target, PList &tail, List &list, PList &out); // "List" points to "undef"
				bool ProcessDefine(PList &target, PList &tail, List &list, PList &out); // "List" points to "define"
				bool ProcessIf(PList &target, PList &tail, List &list, PList &out); // "List" points to "if/ifdef/ifndef"
				bool ProcessInclude(PList &target, PList &tail, List &list, PList &out); // "List" points to "include"
				bool ProcessPragma(PList &target, PList &tail, List &list, PList &out); // "List" points to "pragma"

				bool Expand(PList &target, PList &tail, List &list, const bool defined_allowed, const StringArray &exclude, const size_t &token_index, PList &out); // "current" points to the name
				bool ExpandList(PList &target, PList &tail, List &list, const bool defined_allowed, const StringArray &exclude, const size_t &token_index); // "current" points to the name
				bool ExpandDefined(PList &target, PList &tail, List &list, const size_t &token_index, PList &out);
				bool ExpandExpression(PList &target, PList &tail, CDefinition *definition, const bool defined_allowed, const StringArray &exclude, const size_t &token_index);
				bool ExpandCall(PList &target, PList &tail, List &list, CDefinition *definition, const bool defined_allowed, const StringArray &exclude, const size_t &token_index, PList &out);
				void ExpandArgument(PList &target, PList &tail, const Argument &argument, const size_t &token_index);
				String StringifyArgument(const Argument &argument);
				String StringifyVariadics(const Arguments &variadics);
				bool StringifyVariadicOpts(String &target, List &list, const StringArray &parameters, const Arguments &arguments, const Arguments &variadics, const size_t &token_index, PList &out); // "out" points to ")"
				bool Stringify(PList &target, PList &tail, List &list, const StringArray &parameters, const Arguments &arguments, const Arguments &variadics, const size_t &token_index, PList &out); // "out"  points to the last processed item
				bool Concatinate(PList &target, PList &tail, List &list, const StringArray &parameters, const Arguments &arguments, const size_t &token_index, PList &out); // "out" points to the last processed item
				void ExpandVaArgs(PList &target, PList &tail, const Arguments &variadics, const size_t &token_index);
				bool ExpandVaOpts(PList &target, PList &tail, List &list, const StringArray &parameters, const Arguments &arguments, const Arguments &variadics, const size_t &token_index, PList &out);

				bool Condition(const String &type, List &list, bool &condition, PList &out);
				bool Evaluate(List &list, const size_t &token_index, bool &target); // "list" points to the first and "end" to the last token of expression
				bool BuildExpressionList(PExpression &target, List &list, const bool is_block, const size_t &token_index, PList &out); // If building block, the "current" will point to the ")"
				bool BuildExpressionCall(PExpression &target, List &list, const size_t &token_index, PList &out); // "current" points to the name and will point to ")" after building a function call
				bool BuildExpressionFailed(PExpression &target);
				bool EvaluateList(CExpression *expression, const size_t &token_index, int64 &target);
				bool EvaluateOperand(CExpression *expression, const size_t &token_index, int64 &target);
				bool EvaluateCall(CExpression *expression, const size_t &token_index, int64 &target);
				void ApplyPriors(int64 &target, const std::vector<List *> &priors);
			public:
				bool const &Aborted{ m_bAborted };

				CPreProcessor(cpp::CTokenizer &tokenizer, std::vector<Token*> &tokens, IErrorListener *error_listener = nullptr, IProgressListener *progress_listener = nullptr);
				~CPreProcessor();

				bool AddDefinition(const String &source); // In form as it appears in the code: "#define WINAPI __stdcall"
				CDefinition *FindDefinition(const String &name, const StringArray &exclude);
				bool DeleteDefinition(const String &name);
				void ClearDefinitions();

				bool AddIncludePath(const String &path);
				bool AddHasInclude(const String &filename);
				bool hasInclude(const String &filename);
				void ClearIncludes();

				bool AddHasAttribute(const String &attribute);
				bool hasAttribute(const String &attribute);
				void ClearAttributes();

				bool Process(Tokens &tokens, PList &out);
			};
		}
	}
}