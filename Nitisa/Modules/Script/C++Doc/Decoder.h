// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/ReleasablePtr.h"
#include "../../../Core/Strings.h"
#include "../Core/Tokens.h"
#include "../Tokenizers/C++/Tokenizer.h"
#include "Entities/ClassBase.h"
#include "Identifier.h"
#include "List.h"
#include "PEntity.h"
#include "PList.h"
#include "PreProcessor.h"
#include "Version.h"
#include <vector>

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IProgressListener;

		namespace cppdoc
		{
			class CAttribute;
			class CBaseDeclarator;
			class CEntity;
			class IErrorListenerEx;

			namespace entities
			{
				class CFunctionParameter;
			}

			// As includes are not processed, the decoder has no idea about object types.
			// All "identifier<..." constructions are supposed to be template arguments. If argument has condition with the same form, it should be enclosed in ().
			// Version only affects "explicit" parsing as it has incomatible forms in v20+ and prior.
			// It is better to use "{ ... }" or " = ..." initializations as the "( ... )" is first considered to be a function and if parameters looks OK it may be processed incorrectly.
			class CDecoder
			{
			private:
				using PBaseDeclarator = CBaseDeclarator *;
				using PFunctionParameter = entities::CFunctionParameter *;
			private:
				IErrorListener *m_pErrorListener;
				IProgressListener *m_pProgressListener;
				bool m_bAborted;
				Tokens m_aTokens;
				std::vector<Token *> m_aNewTokens;
				cpp::CTokenizer m_cTokenizer;
				CPreProcessor m_cPreProcessor;
				List *m_pList;
				CEntity *m_pRoot;
				Version m_eVersion;

				static const StringArray BRACES;
				static const StringArray BRACKETS;
				static const StringArray BRACE_ENDS;
				static const StringArray BRACKET_ENDS;
				static const StringArray ATTRIBUTE_LIST_ENDS;
				static const StringArray CLASS_TYPES;
				static const StringArray REFS;

				void ClearNewTokens();
				void Clear();
				List *Next(List &list, const bool skip_ml_comments, const bool skip_sl_comments, const bool skip_new_lines);
				List *Prev(List &list, const bool skip_ml_comments, const bool skip_sl_comments, const bool skip_new_lines);
				List *Skip(List &list, const bool skip_attributes); // Return list address or the next item that is not a comment or a new lines [or attribute list]
				void Dump(IErrorListenerEx *listener, List &list);

				// Check
				bool isAttributeList(List &list);
				bool isModule(List &list);
				bool isImport(List &list);
				bool isExport(List &list); // Should be used ONLY AFTER isModule() and isImport()
				bool isEmpty(List &list); // ;
				bool isBlock(List &list); // { } or <% %>
				bool isLanguageLinkage(List &list); // extern "string" ...
				bool isAsm(List &list); // asm (...)
				bool isNamespaceAlias(List &list); // namespace alias = name;
				bool isNamespace(List &list); // [inline] namespace ...
				bool isUsingNamespace(List &list); // using namespace ...
				bool isUsingEnum(List &list); // using enum identifier;
				bool isTypeAlias(List &list); // using identifier [attr] = type-id;
				bool isUsing(List &list); // using ...
				bool isTemplate(List &list); // template <[...]>
				bool isConcept(List &list); // concept name = ...;
				bool isPublic(List &list); // public
				bool isProtected(List &list); // protected
				bool isPrivate(List &list); // private
				bool isParameterPack(List &list); // ... identifier [attr]
				bool isFunction(CIdentifier *identifier, List &list);
				bool isStructuredBinding(List &list);
				bool isStaticAssert(List &list);
				bool isFriend(List &list);

				// Search
				List *FindCloseParenthese(List &list);
				List *FindCloseParentheseOrCommaOrSemicolon(List &list);
				List *FindCloseBracket(List &list);
				List *FindCloseBrace(List &list);
				List *FindCloseBraceOrComma(List &list, const bool allow_templates);
				List *FindCloseParentheseOrComma(List &list, const bool allow_templates);
				List *FindAttributeListEnd(List &list);
				List *FindGreater(List &list, const bool allow_templates);
				List *FindCommaOrGreater(List &list, const bool allow_templates);
				List *FindCommaOrSemicolon(List &list, const bool allow_templates);
				List *FindSemicolon(List &list);
				List *FindBraceOrSemicolon(List &list);
				List *FindBraceOrCommaOrEqualOrSemicolon(List &list);
				List *FindEntity(List &list); // Skips preceding new lines, attribute lists and comments (if they belong to entity - there are no extra new lines between comments and entity)
				List *FindRequiresEnd(List &list, const bool is_clause); // "list" is the Next token after "requires"
				List *FindFunctionTrailingEnd(List &list);
				List *FindMemberInitializationEnd(List &list); // "list" points to ":". Result points to "{"
				List *FindTryCatchEnd(List &list, const bool allow_ctor_initialization); // "list" points to "try". Result points to the "}" of the last "catch"

				// Parsing
				bool ParseIdentifierArguments(List &list, CIdentifier::Name &name, PList &out);
				bool ParseIdentifier(
					List &list,
					CIdentifier &identifier,
					const bool allow_arguments,
					const bool allow_template,
					const bool allow_destructor,
					const bool allow_nested_name,
					const bool allow_operator,
					PList &out);
				bool ParseModuleName(List &list, String &name, PList &out);
				bool ParsePartitionName(List &list, String &name, PList &out);
				bool ParseAttribute(ReleasablePtr<CAttributeList> &parent, List &list, PList &out);
				bool ParseAttributeList(PEntity &parent, List &list, const bool is_after, PList &out); // [[attribute-list]]
				bool ParseCommentsAndAttributes(PEntity &parent, List &list, PList &out);
				void ParsePrecedingComments(PEntity &parent, List &list);
				void ParseTrailingComments(PEntity &parent, List &list, PList &out);
				bool ParseClassBase(entities::CClassBase &target, List &list, PList &out); // "out" points to "," or to "{"
				bool ParseTypeSpecifierSeq(PEntity &parent, std::vector<CEntity *> &specifiers, List &list, const bool is_parameter, PList &out);
				bool ParseParameterPack(PEntity &target, List &list, PList &out); // ... identifier [attr]
				void ParseCallSpecifiers(std::vector<CEntity *> &specifiers, List &list, PList &out);
				bool ParsePtrDeclarator(PBaseDeclarator &target, List &list, const bool is_parameter, const bool allow_bitfield, bool &has_body, PList &out); // * [attr] [cv] declarator
				bool ParseLValueDeclarator(PBaseDeclarator &target, List &list, const bool is_parameter, const bool allow_bitfield, bool &has_body, PList &out); // & [attr] declarator
				bool ParseRValueDeclarator(PBaseDeclarator &target, List &list, const bool is_parameter, const bool allow_bitfield, bool &has_body, PList &out); // & [attr] declarator
				bool ParseNoPtrDeclarator(PBaseDeclarator &target, List &list, const bool allow_bitfield, bool &has_body, PList &out); // & [attr] declarator
				bool ParseIdDeclarator(PBaseDeclarator &target, List &list, const bool is_parameter, const bool allow_bitfield, bool &has_body, PList &out); // identifier [attr] [cv] [declarator]
				bool ParseArray(PBaseDeclarator &target, List &list, PList &out);
				bool ParseFunctionParameter(PFunctionParameter &target, List &list, PList &out);
				bool ParseFunctionPreContract(PEntity &target, List &list, PList &out);
				bool ParseFunctionPostContract(PEntity &target, List &list, PList &out);
				bool ParseFunction(PBaseDeclarator &target, List &list, bool &parameters_valid, PList &out);
				bool ParseBitfield(PBaseDeclarator &parent, List &list, PList &out);
				bool ParseInitialization(PBaseDeclarator &parent, List &list, const bool is_parameter, PList &out);
				bool ParseEntity(PEntity &parent, List &list, const bool in_block, const bool declaration_only, const bool allow_bitfield, bool &should_break, PList &out); // Parse single entity. If there are new lines before it, they are skipped. If there are comments unrelated to entity, they are added to parent separately
				bool ParseList(PEntity &parent, List &list, const bool in_block, const bool allow_bitfield, PList &out);
				void ParseSLComment(PEntity &parent, List &list, PList &out); // // Comment
				void ParseMLComment(PEntity &parent, List &list, PList &out); // /* Comment */
				bool ParseEmpty(PEntity &parent, List &list, PList &out); // ;
				bool ParseBlock(PEntity &parent, List &list, PList &out); // { ... } or <% ... %>
				bool ParseModule(PEntity &parent, List &list, PList &out); // [export] module [name [partition] [attr]] || [: private];
				bool ParseImport(PEntity &parent, List &list, PList &out); // [export] import module-name | partition-name | header-name [attr];
				bool ParseExport(PEntity &parent, List &list, PList &out); // export declaration | { [declarations] }
				bool ParseLanguageLinkage(PEntity &parent, List &list, PList &out); // extern string-literal declaration | { [declarations] }
				bool ParseAsm(PEntity &parent, List &list, PList &out); // asm ( string-literal | balanced-token-seq }
				bool ParseNamespaceAlias(PEntity &parent, List &list, PList &out); // namespace alias = name;
				bool ParseNamespace(PEntity &parent, List &list, PList &out); // [inline] namespace alias = name;
				bool ParseUsingNamespace(PEntity &parent, List &list, PList &out); // using namespace name;
				bool ParseUsingEnum(PEntity &parent, List &list, PList &out); // using enum identifier;
				bool ParseTypeAlias(PEntity &parent, List &list, PList &out); // using identifier [attr] = type-id;
				bool ParseUsing(PEntity &parent, List &list, PList &out); // using [typename] name [...], ...;
				bool ParseTemplate(PEntity &parent, List &list, PList &out); // template ...
				bool ParseConcept(PEntity &parent, List &list, PList &out); // concept name = ...;
				bool ParseEnum(PEntity &target, List &list, PList &out); // enum ...;
				bool ParseEnumerator(PEntity &parent, List &list, PList &out); // enum ...;
				bool ParseClass(PEntity &target, List &list, PList &out); // class|struct|union ...;
				bool ParsePublic(PEntity &parent, List &list, PList &out); // public:
				bool ParseProtected(PEntity &parent, List &list, PList &out); // protected:
				bool ParsePrivate(PEntity &parent, List &list, PList &out); // private:
				bool ParseSimpleDeclaration(PEntity &parent, List &list, const bool require_declarators, const bool allow_bitfield, bool &has_body, PList &out);
				bool ParseDeclarator(
					PEntity &target,
					List &list,
					const bool is_parameter, // Whether declarator is function argument
					const bool allow_bitfield, // Whether bitfield part is allowed
					bool &has_body, // [out] Whether declarator is a function with body (no other declarators are allowed after it)
					PList &out
				);
				bool ParseDeclaration(PEntity &parent, List &list, const bool allow_bitfield, PList &out);
				bool ParseStructuredBinding(PEntity &parent, List &list, PList &out);
				bool ParseStaticAssert(PEntity &parent, List &list, PList &out); // static_assert(...);
				bool ParseFriend(PEntity &parent, List &list, PList &out); // static_assert(...);

				void E_UnexpectedEnd(const AnsiString &function, int line, List &list, const String &name);
				void E_ExpectedArgument(const AnsiString &function, int line, List &list, const String &name);
				void E_UnexpectedEndExpectedArgument(const AnsiString &function, int line, List &list);
				void E_InvalidIdentifier(const AnsiString &function, int line, List &list);
				void E_InvalidIdentifierDoubleDestructor(const AnsiString &function, int line, List &list);
				void E_UnexpectedEndExpectedIdentifier(const AnsiString &function, int line, List &list);
				void E_ExpectedIdentifier(const AnsiString &function, int line, List &list, const String &name);
				void E_ExpectedToken(const AnsiString &function, int line, List &list, const String &name, const String &found);
				void E_InvalidPartitionName(const AnsiString &function, int line, List &list);
				void E_UnexpectedEndAfterAttributeList(const AnsiString &function, int line, List &list);
				void E_DuplicateProtected(const AnsiString &function, int line, List &list);
				void E_DuplicatePrivate(const AnsiString &function, int line, List &list);
				void E_DuplicatePublic(const AnsiString &function, int line, List &list);
				void E_DuplicateVirtual(const AnsiString &function, int line, List &list);
				void E_UnexpectedEndExpectedBaseClass(const AnsiString &function, int line, List &list);
				void E_ExpectedSpecifier(const AnsiString &function, int line, List &list, const String &name);
				void E_UnexpectedEndExpectedDeclarator(const AnsiString &function, int line, List &list);
				void E_ExpectedDeclarator(const AnsiString &function, int line, List &list, const String &name);
				void E_UnexpectedEndAfterToken(const AnsiString &function, int line, List &list, const String &name);
				void E_UnexpectedEndAfterArray(const AnsiString &function, int line, List &list);
				void E_UnexpectedEndAfterDeclarator(const AnsiString &function, int line, List &list);
				void E_UnexpectedFunctionDefinition(const AnsiString &function, int line, List &list);
				void E_UnexpectedEndAfterParameters(const AnsiString &function, int line, List &list);
				void E_ExpectedTrailing(const AnsiString &function, int line, List &list, const String &name);
				void E_ExpectedString(const AnsiString &function, int line, List &list, const String &name);
				void E_UnexpectedEndAfterMemberInitialization(const AnsiString &function, int line, List &list);
				void E_BitfieldRequireIdDeclarator(const AnsiString &function, int line, List &list);
				void E_ExportPrivateModule(const AnsiString &function, int line, List &list);
				void E_ExportModuleWithoutName(const AnsiString &function, int line, List &list);
				void E_UnexpectedEndAfterModuleName(const AnsiString &function, int line, List &list);
				void E_UnexpectedEndAfterPartitionName(const AnsiString &function, int line, List &list);
				void E_ExpectedAnsi(const AnsiString &function, int line, List &list, const String &name);
				void E_UnexpectedEndAfterString(const AnsiString &function, int line, List &list);
				void E_InlineNotAllowed(const AnsiString &function, int line, List &list);
				void E_ExpectedTypeId(const AnsiString &function, int line, List &list, const String &name);
				void E_ExpectedExpression(const AnsiString &function, int line, List &list, const String &name);
				void E_DuplicateFinal(const AnsiString &function, int line, List &list);
				void E_DuplicateTriviallyRelocatable(const AnsiString &function, int line, List &list);
				void E_DuplicateReplaceable(const AnsiString &function, int line, List &list);
				void E_UnionWithBaseClass(const AnsiString &function, int line, List &list);
				void E_InvalidDeclarator(const AnsiString &function, int line, List &list);
				void E_DuplicateAuto(const AnsiString &function, int line, List &list);
				void E_ExpectedAuto(const AnsiString &function, int line, List &list);
				void E_UnexpectedEndExpectedAttributeList(const AnsiString &function, int line, List &list);
				void E_ExpectedInitialization(const AnsiString &function, int line, List &list, const String &name);
			public:
				bool const &Aborted{ m_bAborted };
				CPreProcessor *PreProcessor{ &m_cPreProcessor };
				CEntity *const &Root{ m_pRoot };
				Version const &CppVersion{ m_eVersion };

				CDecoder(IErrorListener *error_listener = nullptr, IProgressListener *progress_listener = nullptr);
				~CDecoder();

				bool Decode(const String &source);

				bool setVersion(const enum Version value);
			};
		}
	}
}