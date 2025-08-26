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
		namespace cppdoc
		{
			using entities::CArray;
			using entities::CAsm;
			using entities::CAuto;
			using entities::CBlock;
			using entities::CBool;
			using entities::CCDecl;
			using entities::CChar;
			using entities::CChar16T;
			using entities::CChar32T;
			using entities::CChar8T;
			using entities::CClass;
			using entities::CClassBase;
			using entities::CComment;
			using entities::CConcept;
			using entities::CConst;
			using entities::CConsteval;
			using entities::CConstexpr;
			using entities::CConstinit;
			using entities::CDecltype;
			using entities::CDouble;
			using entities::CEmpty;
			using entities::CEnum;
			using entities::CEnumerator;
			using entities::CExplicit;
			using entities::CExport;
			using entities::CExtern;
			using entities::CFastCall;
			using entities::CFinal;
			using entities::CFloat;
			using entities::CFriend;
			using entities::CFunction;
			using entities::CFunctionParameter;
			using entities::CFunctionPostContract;
			using entities::CFunctionPreContract;
			using entities::CIdDeclarator;
			using entities::CImport;
			using entities::CInline;
			using entities::CInt;
			using entities::CLanguageLinkage;
			using entities::CLong;
			using entities::CLRef;
			using entities::CLValueDeclarator;
			using entities::CModule;
			using entities::CMutable;
			using entities::CNaked;
			using entities::CName;
			using entities::CNamespace;
			using entities::CNamespaceAlias;
			using entities::CNoPtrDeclarator;
			using entities::COverride;
			using entities::CPackIndexing;
			using entities::CParameterPack;
			using entities::CPrivate;
			using entities::CProtected;
			using entities::CPtrDeclarator;
			using entities::CPublic;
			using entities::CRegister;
			using entities::CRoot;
			using entities::CRRef;
			using entities::CRValueDeclarator;
			using entities::CShort;
			using entities::CSigned;
			using entities::CSimpleDeclaration;
			using entities::CStatic;
			using entities::CStaticAssert;
			using entities::CStdCall;
			using entities::CStructuredBinding;
			using entities::CTemplate;
			using entities::CTemplateSpecifier;
			using entities::CThisCall;
			using entities::CThreadLocal;
			using entities::CTypeAlias;
			using entities::CTypedef;
			using entities::CTypename;
			using entities::CUnsigned;
			using entities::CUsing;
			using entities::CUsingEnum;
			using entities::CUsingNamespace;
			using entities::CVirtual;
			using entities::CVoid;
			using entities::CVolatile;
			using entities::CWCharT;

			const StringArray CDecoder::BRACES{ L"{", L"<%" };
			const StringArray CDecoder::BRACKETS{ L"[", L"<:" };
			const StringArray CDecoder::BRACE_ENDS{ L"}", L"%>" };
			const StringArray CDecoder::BRACKET_ENDS{ L"]", L":>" };
			const StringArray CDecoder::ATTRIBUTE_LIST_ENDS{ L"]]", L":>:>" };
			const StringArray CDecoder::CLASS_TYPES{ L"class", L"struct", L"union" };
			const StringArray CDecoder::REFS{ L"&", L"&&" };

		#pragma region Constructor & destructor
			CDecoder::CDecoder(IErrorListener *error_listener, IProgressListener *progress_listener) :
				m_pErrorListener{ error_listener },
				m_pProgressListener{ progress_listener },
				m_bAborted{ false },
				m_cPreProcessor{ m_cTokenizer, m_aNewTokens, error_listener, progress_listener },
				m_pList{ nullptr },
				m_pRoot{ nullptr },
				m_eVersion{ Version::v23 }
			{

			}

			CDecoder::~CDecoder()
			{
				Clear();
			}
		#pragma endregion

		#pragma region Helpers
			void CDecoder::ClearNewTokens()
			{
				for (auto token : m_aNewTokens)
					delete token;
				m_aNewTokens.clear();
			}

			void CDecoder::Clear()
			{
				if (m_pRoot)
				{
					m_pRoot->Release();
					m_pRoot = nullptr;
				}
				Free(m_pList);
				ClearNewTokens();
				m_bAborted = false;
			}

			List *CDecoder::Next(List &list, const bool skip_ml_comments, const bool skip_sl_comments, const bool skip_new_lines)
			{
				List *current{ list.Next };
				while (current)
				{
					if (skip_ml_comments && isMLComment(*current))
					{
						current = current->Next;
						continue;
					}
					if (skip_sl_comments && isSLComment(*current))
					{
						current = current->Next;
						continue;
					}
					if (skip_new_lines && isNewLines(*current))
					{
						current = current->Next;
						continue;
					}
					break;
				}
				return current;
			}

			List *CDecoder::Prev(List &list, const bool skip_ml_comments, const bool skip_sl_comments, const bool skip_new_lines)
			{
				List *current{ list.Prev };
				while (current)
				{
					if (skip_ml_comments && isMLComment(*current))
					{
						current = current->Prev;
						continue;
					}
					if (skip_sl_comments && isSLComment(*current))
					{
						current = current->Prev;
						continue;
					}
					if (skip_new_lines && isNewLines(*current))
					{
						current = current->Prev;
						continue;
					}
					break;
				}
				return current;
			}

			List *CDecoder::Skip(List &list, const bool skip_attributes)
			{
				List *current{ &list };
				while (current)
				{
					if (isComment(*current) || isNewLines(*current))
					{
						current = Next(*current, true, true, true);
						continue;
					}
					if (skip_attributes && isAttributeList(*current))
					{
						if ((current = FindAttributeListEnd(*current)))
							current = Next(*current, true, true, true);
						continue;
					}
					break;
				}
				return current;
			}

			void CDecoder::Dump(IErrorListenerEx *listener, List &list)
			{
				if (listener)
					listener->Dump = DumpTokens(list, listener->Before, listener->After, listener->BeforeCount, listener->AfterCount);
			}
		#pragma endregion

		#pragma region Check
			bool CDecoder::isAttributeList(List &list)
			{
				static const StringArray ATTRS{ L"[[", L"<:" };

				List *next;
				if (list.Item->Type == TokenType::Identifier && list.Item->Value == L"alignas" &&
					(next = Next(list, true, true, true)) && next->Item->Type == TokenType::Operator && next->Item->Op->Name == L"(")
					return true;
				return list.Item->Type == TokenType::Operator && in(list.Item->Op->Name, ATTRS);
			}

			bool CDecoder::isModule(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value == L"module")
					return true;
				if (list.Item->Value != L"export")
					return false;
				List *next{ Next(list, true, true, true) };
				if (!next)
					return false;
				if (next->Item->Type != TokenType::Identifier)
					return false;
				if (next->Item->Value != L"module")
					return false;
				return true;
			}

			bool CDecoder::isImport(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value == L"import")
					return true;
				if (list.Item->Value != L"export")
					return false;
				List *next{ Next(list, true, true, true) };
				if (!next)
					return false;
				if (next->Item->Type != TokenType::Identifier)
					return false;
				if (next->Item->Value != L"import")
					return false;
				return true;
			}

			bool CDecoder::isExport(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"export")
					return false;
				return true;
			}

			bool CDecoder::isEmpty(List &list)
			{
				if (list.Item->Type != TokenType::Operator)
					return false;
				if (list.Item->Op->Name != L";")
					return false;
				return true;
			}

			bool CDecoder::isBlock(List &list)
			{
				if (list.Item->Type != TokenType::Operator)
					return false;
				if (!in(list.Item->Op->Name, BRACES))
					return false;
				return true;
			}

			bool CDecoder::isLanguageLinkage(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"extern")
					return false;
				List *next{ Next(list, true, true, true) };
				if (!next)
					return false;
				if (next->Item->Type != TokenType::String)
					return false;
				if (next->Item->Op->Name != L"\"")
					return false;
				if (!next->Item->Prefix.empty())
					return false;
				return true;
			}

			bool CDecoder::isAsm(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"asm")
					return false;
				List *next{ Next(list, true, true, true) };
				if (!next)
					return false;
				if (next->Item->Type != TokenType::Operator)
					return false;
				if (next->Item->Op->Name != L"(")
					return false;
				return true;
			}

			bool CDecoder::isNamespaceAlias(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"namespace")
					return false;
				List *next{ Next(list, true, true, true) };
				if (!next)
					return false;
				if (next->Item->Type != TokenType::Identifier)
					return false;
				if (!(next = Next(*next, true, true, true)))
					return false;
				if (next->Item->Type != TokenType::Operator)
					return false;
				if (next->Item->Op->Name != L"=")
					return false;
				return true;
			}

			bool CDecoder::isNamespace(List &list)
			{
				List *current{ &list };
				if (current->Item->Type != TokenType::Identifier)
					return false;
				if (current->Item->Value == L"inline")
				{
					if (!(current = Next(*current, true, true, true)))
						return false;
					if (current->Item->Type != TokenType::Identifier)
						return false;
				}
				if (current->Item->Value != L"namespace")
					return false;
				return true;
			}

			bool CDecoder::isUsingNamespace(List &list)
			{
				List *current{ &list };
				if (current->Item->Type != TokenType::Identifier)
					return false;
				if (current->Item->Value != L"using")
					return false;
				if (!(current = Next(*current, true, true, true)))
					return false;
				if (current->Item->Type != TokenType::Identifier)
					return false;
				if (current->Item->Value != L"namespace")
					return false;
				return true;
			}

			bool CDecoder::isUsingEnum(List &list)
			{
				List *current{ &list };
				if (current->Item->Type != TokenType::Identifier)
					return false;
				if (current->Item->Value != L"using")
					return false;
				if (!(current = Next(*current, true, true, true)))
					return false;
				if (current->Item->Type != TokenType::Identifier)
					return false;
				if (current->Item->Value != L"enum")
					return false;
				return true;
			}

			bool CDecoder::isTypeAlias(List &list)
			{
				List *current{ &list };
				if (current->Item->Type != TokenType::Identifier)
					return false;
				if (current->Item->Value != L"using")
					return false;
				if (!(current = Next(*current, true, true, true)))
					return false;
				if (current->Item->Type != TokenType::Identifier)
					return false;
				if (!(current = Next(*current, true, true, true)))
					return false;
				while (current && isAttributeList(*current))
				{
					if (!(current = FindAttributeListEnd(*current)))
						return false;
					current = Next(*current, true, true, true);
				}
				if (!current)
					return false;
				if (current->Item->Type != TokenType::Operator)
					return false;
				if (current->Item->Op->Name != L"=")
					return false;
				return true;
			}

			bool CDecoder::isUsing(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"using")
					return false;
				return true;
			}

			bool CDecoder::isTemplate(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"template")
					return false;
				List *next{ Next(list, true, true, true) };
				if (!next)
					return false;
				if (next->Item->Type != TokenType::Operator)
					return false;
				if (next->Item->Op->Name != L"<")
					return false;
				return true;
			}

			bool CDecoder::isConcept(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"concept")
					return false;
				return true;
			}

			bool CDecoder::isPublic(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"public")
					return false;
				return true;
			}

			bool CDecoder::isProtected(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"protected")
					return false;
				return true;
			}

			bool CDecoder::isPrivate(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"private")
					return false;
				return true;
			}

			bool CDecoder::isParameterPack(List &list)
			{
				List *current{ &list };
				if (current->Item->Type != TokenType::Operator)
					return false;
				if (current->Item->Op->Name != L"...")
					return false;
				if (!(current = Next(*current, true, true, true)))
					return false;
				return current->Item->Type == TokenType::Identifier || (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"::");
			}

			bool CDecoder::isFunction(CIdentifier *identifier, List &list)
			{
				if (identifier && identifier->Destructor) // Definitely function
					return true;
				if (identifier && !identifier->Operator.empty()) // Definitely function
					return true;
				List *current{ Next(list, true, true, true) };
				if (!current)  // Error, so doen't matter
					return false;
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L")") // empty () - definitely function
					return true;
				if (!(current = FindCloseParenthese(*current))) // Error, so doen't matter
					return false;
				if (!(current = Next(*current, true, true, true))) // Error, so doen't matter
					return false;
				if (isAttributeList(*current)) // Attribute list caanot be after initialization - definitely function
					return true;
				if (current->Item->Type != TokenType::Operator) // Nothing expect "," or ";" is allowed after initialization - definitely function
					return true;
				if (current->Item->Op->Name != L"," && current->Item->Op->Name != L";") // Nothing expect "," or ";" is allowed after initialization - definitely function
					return true;
				// Here can only by construction like this:
				// "type declarator(...)," or "type declarator(...);"
				// which can mean both function and initialization
				// assume this is a function
				return true;
			}

			bool CDecoder::isStructuredBinding(List &list)
			{
				static const StringArray SPECIFIERS{ L"constexpr", L"constinit", L"static", L"thread_local", L"const", L"volatile", L"auto" };
				
				List *current{ &list };
				bool has_auto{ false };
				while (current && current->Item->Type == TokenType::Identifier && in(current->Item->Value, SPECIFIERS))
				{
					if (current->Item->Value == L"auto")
					{
						if (has_auto)
							return false;
						has_auto = true;
					}
					current = Next(*current, true, true, true);
				}
				if (!has_auto || !current)
					return false;
				if (current && current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, REFS))
				{
					if (!(current = Next(*current, true, true, true)))
						return false;
				}
				if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, BRACKETS))
					return false;
				return true;
			}

			bool CDecoder::isStaticAssert(List &list)
			{
				List *current{ &list };
				if (current->Item->Type != TokenType::Identifier)
					return false;
				if (current->Item->Value != L"static_assert")
					return false;
				if (!(current = Next(*current, true, true, true)))
					return false;
				return current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"(";
			}

			bool CDecoder::isFriend(List &list)
			{
				if (list.Item->Type != TokenType::Identifier)
					return false;
				if (list.Item->Value != L"friend")
					return false;
				return true;
			}
		#pragma endregion

		#pragma region Search
			List *CDecoder::FindCloseParenthese(List &list)
			{
				List *current{ &list };
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L")")
							return current;
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindCloseParentheseOrCommaOrSemicolon(List &list)
			{
				List *current{ &list };
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L")")
							return current;
						if (current->Item->Op->Name == L",")
							return current;
						if (current->Item->Op->Name == L";")
							return current;
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACES))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBrace(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindCloseBracket(List &list)
			{
				List *current{ &list };
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (in(current->Item->Op->Name, BRACKET_ENDS))
							return current;
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindCloseBrace(List &list)
			{
				List *current{ &list };
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (in(current->Item->Op->Name, BRACE_ENDS))
							return current;
						if (in(current->Item->Op->Name, BRACES))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBrace(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindCloseBraceOrComma(List &list, const bool allow_templates)
			{
				List *current{ &list }, *prev;
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L",")
							return current;
						if (in(current->Item->Op->Name, BRACE_ENDS))
							return current;
						if (allow_templates && current->Item->Op->Name == L"<" && (prev = Prev(*current, true, true, true)) && prev->Item->Type == TokenType::Identifier)
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindGreater(*current, true)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACES))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBrace(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindCloseParentheseOrComma(List &list, const bool allow_templates)
			{
				List *current{ &list }, *prev;
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L",")
							return current;
						if (current->Item->Op->Name == L")")
							return current;
						if (allow_templates && current->Item->Op->Name == L"<" && (prev = Prev(*current, true, true, true)) && prev->Item->Type == TokenType::Identifier)
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindGreater(*current, true)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACES))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBrace(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindAttributeListEnd(List &list)
			{
				List *current{ &list };
				// alignas(...)
				if (current->Item->Type == TokenType::Identifier)
				{
					if (current->Item->Value != L"alignas")
						return nullptr;
					if (!(current = Next(*current, true, true, true)))
						return nullptr;
					if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
						return nullptr;
					if (!(current = Next(*current, true, true, true)))
						return nullptr;
					if (!(current = FindCloseParenthese(*current)))
						return nullptr;
					return current;
				}
				// [[...]]
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (in(current->Item->Op->Name, ATTRIBUTE_LIST_ENDS))
							return current;
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACES))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBrace(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindGreater(List &list, const bool allow_templates)
			{
				List *current{ &list }, *prev;
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L">")
							return current;
						if (allow_templates && current->Item->Op->Name == L"<" && (prev = Prev(*current, true, true, true)) && prev->Item->Type == TokenType::Identifier)
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindGreater(*current, true)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACES))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBrace(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindCommaOrGreater(List &list, const bool allow_templates)
			{
				List *current{ &list }, *prev;
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L",")
							return current;
						if (current->Item->Op->Name == L">")
							return current;
						if (allow_templates && current->Item->Op->Name == L"<" && (prev = Prev(*current, true, true, true)) && prev->Item->Type == TokenType::Identifier)
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindGreater(*current, true)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACES))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBrace(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindCommaOrSemicolon(List &list, const bool allow_templates)
			{
				List *current{ &list }, *prev;
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L",")
							return current;
						if (current->Item->Op->Name == L";")
							return current;
						if (allow_templates && current->Item->Op->Name == L"<" && (prev = Prev(*current, true, true, true)) && prev->Item->Type == TokenType::Identifier)
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindGreater(*current, true)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACES))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBrace(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindSemicolon(List &list)
			{
				List *current{ &list };
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L";")
							return current;
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACES))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBrace(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindBraceOrSemicolon(List &list)
			{
				List *current{ &list };
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L";")
							return current;
						if (in(current->Item->Op->Name, BRACES))
							return current;
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindBraceOrCommaOrEqualOrSemicolon(List &list)
			{
				List *current{ &list };
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (in(current->Item->Op->Name, BRACES))
							return current;
						if (current->Item->Op->Name == L",")
							return current;
						if (current->Item->Op->Name == L"=")
							return current;
						if (current->Item->Op->Name == L";")
							return current;
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindEntity(List &list)
			{
				List *current{ &list }, *next;
				bool has_attributes{ false };
				while (current)
				{
					if (isComment(*current))
					{
						if (has_attributes)
						{
							current = current->Next;
							continue;
						}
						if (!(next = current->Next))
							break;
						if (isNewLines(*next))
						{
							if (isSLComment(*current))
								break;
							if (next->Item->Type == TokenType::Group && next->Item->Count > 1)
								break;
							next = next->Next;
						}
						current = next;
						continue;
					}
					if (isAttributeList(*current))
					{
						if (!(current = FindAttributeListEnd(*current)))
							break;
						has_attributes = true;
						current = current->Next;
						continue;
					}
					if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACE_ENDS))
						break;
					return current;
				}
				return &list;
			}

			List *CDecoder::FindRequiresEnd(List &list, const bool is_clause)
			{
				static const StringArray OPERATORS{ L"&&", L"||" };

				List *current{ &list }, *next;
				// requires requires ...
				if (current->Item->Type == TokenType::Identifier && current->Item->Value == L"requires")
				{
					if (!(current = Next(*current, true, true, true)))
						return nullptr;
					return FindRequiresEnd(*current, false);
				}
				// requires {...}
				if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACES))
				{
					if (!(current = Next(*current, true, true, true)))
						return nullptr;
					return FindCloseBrace(*current);
				}
				// requires (...) {...}
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"(")
				{
					if (!(next = Next(*current, true, true, true)))
						return nullptr;
					if (!(next = FindCloseParenthese(*next)))
						return nullptr;
					if (!is_clause && (next = Next(*next, true, true, true)) && next->Item->Type == TokenType::Operator && in(next->Item->Op->Name, BRACES))
					{
						if (!(next = Next(*next, true, true, true)))
							return nullptr;
						return FindCloseBrace(*next);
					}
					return next;
				}
				// requires expression
				bool is_operand{ true };
				while (current)
				{
					if (is_operand)
					{
						// (...)
						if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							is_operand = false;
							continue;
						}
						// identifier
						CIdentifier identifier;
						if (!ParseIdentifier(*current, identifier, true, true, false, false, false, current))
							return nullptr;
						is_operand = false;
						continue;
					}
					if (current->Item->Type != TokenType::Operator)
						break;
					if (!in(current->Item->Op->Name, OPERATORS))
						break;
					current = Next(*current, true, true, true);
					is_operand = true;
				}
				if (!current)
					return nullptr;
				return Prev(*current, true, true, true);
			}

			List *CDecoder::FindFunctionTrailingEnd(List &list)
			{
				List *current{ &list }, *prev;
				while (current)
				{
					switch (current->Item->Type)
					{
					case TokenType::Operator:
						if (current->Item->Op->Name == L",")
							return current;
						if (current->Item->Op->Name == L";")
							return current;
						if (current->Item->Op->Name == L":")
							return current;
						if (current->Item->Op->Name == L"=")
							return current;
						if (in(current->Item->Op->Name, BRACES))
							return current;
						if (current->Item->Op->Name == L"<" && (prev = Prev(*current, true, true, true)) && prev->Item->Type == TokenType::Identifier)
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindGreater(*current, true)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseParenthese(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						if (in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (!(current = FindCloseBracket(*current)))
								return nullptr;
							current = Next(*current, true, true, true);
							continue;
						}
						break;
					case TokenType::Identifier:
						if (current->Item->Value == L"requires")
							return current;
						if (current->Item->Value == L"pre")
							return current;
						if (current->Item->Value == L"post")
							return current;
						if (current->Item->Value == L"try")
							return current;
						break;
					default:
						break;
					}
					current = Next(*current, true, true, true);
				}
				return nullptr;
			}

			List *CDecoder::FindMemberInitializationEnd(List &list)
			{
				List *current{ Next(list, true, true, true) };
				if (!current)
					return nullptr;
				while (current)
				{
					CIdentifier identifier;
					if (!ParseIdentifier(*current, identifier, true, true, false, false, false, current))
						return nullptr;
					if (!current)
						return nullptr;
					if (current->Item->Type != TokenType::Operator)
						return nullptr;
					if (current->Item->Op->Name == L"...")
					{
						if (!(current = Next(*current, true, true, true)))
							return nullptr;
						if (current->Item->Type != TokenType::Operator)
							return nullptr;
						if (in(current->Item->Op->Name, BRACES))
							return current;
						if (current->Item->Op->Name != L",")
							return nullptr;
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Op->Name == L"(")
					{
						if (!(current = Next(*current, true, true, true)))
							return nullptr;
						if (!(current = FindCloseParenthese(*current)))
							return nullptr;
						if (!(current = Next(*current, true, true, true)))
							return nullptr;
						if (current->Item->Type != TokenType::Operator)
							return nullptr;
						if (current->Item->Op->Name == L"...")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (current->Item->Type != TokenType::Operator)
								return nullptr;
						}
						if (in(current->Item->Op->Name, BRACES))
							return current;
						if (current->Item->Op->Name != L",")
							return nullptr;
						current = Next(*current, true, true, true);
						continue;
					}
					if (in(current->Item->Op->Name, BRACES))
					{
						if (!(current = Next(*current, true, true, true)))
							return nullptr;
						if (!(current = FindCloseBrace(*current)))
							return nullptr;
						if (!(current = Next(*current, true, true, true)))
							return nullptr;
						if (current->Item->Type != TokenType::Operator)
							return nullptr;
						if (current->Item->Op->Name == L"...")
						{
							if (!(current = Next(*current, true, true, true)))
								return nullptr;
							if (current->Item->Type != TokenType::Operator)
								return nullptr;
						}
						if (in(current->Item->Op->Name, BRACES))
							return current;
						if (current->Item->Op->Name != L",")
							return nullptr;
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Op->Name == L",")
					{
						current = Next(*current, true, true, true);
						continue;
					}
					break;
				}
				return nullptr;
			}

			List *CDecoder::FindTryCatchEnd(List &list, const bool allow_ctor_initialization)
			{
				List *current{ Next(list, true, true, true) }, *result;
				if (!current)
					return nullptr;
				if (allow_ctor_initialization && current->Item->Type == TokenType::Operator && current->Item->Op->Name == L":")
				{
					if (!(current = FindMemberInitializationEnd(*current)))
						return nullptr;
				}
				if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, BRACES))
					return nullptr;
				if (!(current = Next(*current, true, true, true)))
					return nullptr;
				if (!(result = FindCloseBrace(*current)))
					return nullptr;
				current = Next(*result, true, true, true);
				while (current && current->Item->Type == TokenType::Identifier && current->Item->Value == L"catch")
				{
					if (!(current = Next(*current, true, true, true)))
						return nullptr;
					if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
						return nullptr;
					if (!(current = Next(*current, true, true, true)))
						return nullptr;
					if (!(current = FindCloseParenthese(*current)))
						return nullptr;
					if (!(current = Next(*current, true, true, true)))
						return nullptr;
					if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, BRACES))
						return nullptr;
					if (!(current = Next(*current, true, true, true)))
						return nullptr;
					if (!(result = FindCloseBrace(*current)))
						return nullptr;
					current = Next(*result, true, true, true);
				}
				return result;
			}
		#pragma endregion

		#pragma region Parsing
			bool CDecoder::ParseIdentifierArguments(List &list, CIdentifier::Name &name, PList &out)
			{
				List *current{ &list }, *end;
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"<")
				{
					name.hasArguments = true;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L">");
						return false;
					}
					while (current)
					{
						if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L">")
							break;
						if (!(end = FindCommaOrGreater(*current, true)))
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, *current, L",' or '>");
							return false;
						}
						if (end == current)
						{
							E_ExpectedArgument(__FILE__, __LINE__, *end, TokenToString(*end->Item));
							return false;
						}
						name.Arguments.push_back(Range{ current, Prev(*end, true, true, true) });
						current = end;
						if (current->Item->Op->Name == L">")
							break;
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, *end);
							return false;
						}
						if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L">")
						{
							E_ExpectedArgument(__FILE__, __LINE__, *current, L">");
							return false;
						}
					}
				}
				out = current;
				return true;
			}

			bool CDecoder::ParseIdentifier(
				List &list,
				CIdentifier &identifier,
				const bool allow_arguments,
				const bool allow_template,
				const bool allow_destructor,
				const bool allow_nested_name,
				const bool allow_operator,
				PList &out)
			{
				static const StringArray OVERLOADED_OPERATORS{ L"+", L"-", L"*", L"/", L"%", L"^", L"&", L"|", L"~", L"!", L"=", L"<", L">", L"+=", L"-=", L"*=", L"/=",
					L"%=", L"^=", L"&=", L"|=", L"<<", L"<<=", L">>=", L"==", L"!=", L"<=", L">=", L"<=>", L"&&", L"||", L"++", L"--", L",", L"->", L"->*" };
				static const StringArray ALLOWED_OPERATORS_IN_OP{ L"*", L"&", L"&&", L"::"};

				List *current{ &list }, *next, *next2;
				bool is_operator{ current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"::"}, has_name{false};
				if (is_operator)
					identifier.Names.push_back(CIdentifier::Name{ false, L"", false });
				while (current)
				{
					if (is_operator)
					{
						if (identifier.Destructor || current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"::")
						{
							if (identifier.Names.empty() || (identifier.Names.size() == 1 && (identifier.Names[0].Name.empty() || identifier.Names[0].Name == L"*")))
							{
								E_InvalidIdentifier(__FUNCTION__, __LINE__, list);
								return false;
							}
							break;
						}
					}
					else
					{
						CIdentifier::Name name;
						name.Template = false;
						name.hasArguments = false;
						// [~]
						if (allow_destructor && current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"~")
						{
							if (identifier.Destructor)
							{
								E_InvalidIdentifierDoubleDestructor(__FUNCTION__, __LINE__, *current);
								return false;
							}
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
								return false;
							}
							identifier.Destructor = true;
						}
						if (current->Item->Type != TokenType::Identifier)
						{
							if (allow_nested_name && !identifier.Destructor && has_name) // Identifier ending with "::" is allowed
							{
								if (!(current = Next(*current, true, true, true)))
									return false;
								name.Name = L"*";
								identifier.Names.push_back(name);
								is_operator = true;
								break;
							}
							E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
							return false;
						}
						// [operator]
						if (allow_operator && !identifier.Destructor && current->Item->Value == L"operator" && (next = Next(*current, true, true, true)))
						{
							// operator ""name
							if (next->Item->Type == TokenType::String && next->Item->Op->Name == L"\"" && next->Item->Value.empty() && next->Item->Prefix.empty())
							{
								identifier.UserDefinedOperator = true;
								if (!(current = Next(*next, true, true, true)))
								{
									E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, *next);
									return false;
								}
								if (current->Item->Type != TokenType::Identifier)
								{
									E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
									return false;
								}
								identifier.Operator = current->Item->Value;
								identifier.Names.push_back(CIdentifier::Name{ false, L"operator", false });
								current = Next(*current, true, true, true);
								is_operator = true;
								break;
							}
							// operator new [[]]
							if (next->Item->Type == TokenType::Identifier && next->Item->Value == L"new")
							{
								identifier.Operator = L"new";
								if ((current = Next(*next, true, true, true)) && current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACKETS))
								{
									if (!(current = Next(*current, true, true, true)))
									{
										E_UnexpectedEnd(__FUNCTION__, __LINE__, *next, L"]");
										return false;
									}
									if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, BRACKET_ENDS))
									{
										E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"]", TokenToString(*current->Item));
										return false;
									}
									identifier.Operator += L"[]";
									current = Next(*current, true, true, true);
								}
								identifier.Names.push_back(CIdentifier::Name{ false, L"operator", false });
								is_operator = true;
								break;
							}
							// operator delete [[]]
							if (next->Item->Type == TokenType::Identifier && next->Item->Value == L"delete")
							{
								identifier.Operator = L"delete";
								if ((current = Next(*next, true, true, true)) && current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACKETS))
								{
									if (!(current = Next(*current, true, true, true)))
									{
										E_UnexpectedEnd(__FUNCTION__, __LINE__, *next, L"]");
										return false;
									}
									if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, BRACKET_ENDS))
									{
										E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"]", TokenToString(*current->Item));
										return false;
									}
									identifier.Operator += L"[]";
									current = Next(*current, true, true, true);
								}
								identifier.Names.push_back(CIdentifier::Name{ false, L"operator", false });
								is_operator = true;
								break;
							}
							// operator ()
							if (next->Item->Type == TokenType::Operator && next->Item->Op->Name == L"(")
							{
								if (!(current = Next(*next, true, true, true)))
								{
									E_UnexpectedEnd(__FUNCTION__, __LINE__, *next, L")");
									return false;
								}
								if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L")")
								{
									E_ExpectedToken(__FUNCTION__, __LINE__, *current, L")", TokenToString(*current->Item));
									return false;
								}
								current = Next(*current, true, true, true);
								identifier.Operator = L"()";
								identifier.Names.push_back(CIdentifier::Name{ false, L"operator", false });
								is_operator = true;
								break;
							}
							// operator []
							if (next->Item->Type == TokenType::Operator && in(next->Item->Op->Name, BRACKETS))
							{
								if (!(current = Next(*next, true, true, true)))
								{
									E_UnexpectedEnd(__FUNCTION__, __LINE__, *next, L"]");
									return false;
								}
								if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, BRACKET_ENDS))
								{
									E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"]", TokenToString(*current->Item));
									return false;
								}
								current = Next(*current, true, true, true);
								identifier.Operator = L"[]";
								identifier.Names.push_back(CIdentifier::Name{ false, L"operator", false });
								is_operator = true;
								break;
							}
							// operator >>
							if (next->Item->Type == TokenType::Operator && next->Item->Op->Name == L">" &&
								(next2 = Next(*next, true, true, true)) && next2->Item->Type == TokenType::Operator && next2->Item->Op->Name == L">")
							{
								current = Next(*next2, true, true, true);
								identifier.Operator = L">>";
								identifier.Names.push_back(CIdentifier::Name{ false, L"operator", false });
								is_operator = true;
								break;
							}
							// operator op
							if (next->Item->Type == TokenType::Operator && in(next->Item->Op->Name, OVERLOADED_OPERATORS))
							{
								current = Next(*next, true, true, true);
								identifier.Operator = next->Item->Op->Name;
								identifier.Names.push_back(CIdentifier::Name{ false, L"operator", false });
								is_operator = true;
								break;
							}
							// operator Name
							if (next->Item->Type == TokenType::Identifier)
							{
								identifier.Operator = next->Item->Value;
								List *prev{ next };
								current = Next(*next, true, true, true);
								while (current && (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"("))
								{
									if (current->Item->Type == TokenType::Identifier)
									{
										if (prev->Item->Type == TokenType::Identifier)
											identifier.Operator += L" ";
										identifier.Operator += current->Item->Value;
									}
									else if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, ALLOWED_OPERATORS_IN_OP))
									{
										if (prev->Item->Type == TokenType::Identifier)
											identifier.Operator += L" ";
										identifier.Operator += current->Item->Op->Name;
									}
									else
										break;
									prev = current;
									current = Next(*current, true, true, true);
								}
								identifier.Names.push_back(CIdentifier::Name{ false, L"operator", false });
								is_operator = true;
								break;
							}
						}
						// [template]
						if (allow_template && current->Item->Value == L"template")
						{
							name.Template = true;
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
								return false;
							}
							if (current->Item->Type != TokenType::Identifier)
							{
								E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
								return false;
							}
						}
						else
							name.Template = false;
						// name
						name.Name = current->Item->Value;
						// [<...>]
						if (allow_arguments && (next = Next(*current, true, true, true)))
						{
							List *stored{ current };
							if (!ParseIdentifierArguments(*next, name, current))
								return false;
							if (!name.hasArguments)
								current = stored;
						}
						identifier.Names.push_back(name);
						has_name = true;
					}
					is_operator = !is_operator;
					current = Next(*current, true, true, true);
				}
				if (!is_operator)
				{
					if (current)
						E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					else
						E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
					return false;
				}
				// Check if opreator have raguments
				if (!identifier.Operator.empty() && current && allow_arguments)
				{
					if (!ParseIdentifierArguments(*current, identifier.Names[identifier.Names.size() - 1], current))
						return false;
					if (identifier.Names[identifier.Names.size() - 1].hasArguments)
						current = Next(*current, true, true, true);
				}
				out = current;
				return true;
			}

			bool CDecoder::ParseModuleName(List &list, String &name, PList &out)
			{
				List *current{ &list };
				bool is_operator{ false };
				while (current)
				{
					if (is_operator)
					{
						if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L".")
							break;
						name += L".";
					}
					else
					{
						if (current->Item->Type != TokenType::Identifier)
							return false;
						name += current->Item->Value;
					}
					is_operator = !is_operator;
					current = Next(*current, true, true, true);
				}
				if (!is_operator)
				{
					if (current)
						E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					else
						E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
					return false;
				}
				out = current;
				return true;
			}

			bool CDecoder::ParsePartitionName(List &list, String &name, PList &out)
			{
				List *current{ &list };
				bool is_operator{ current->Item->Type == TokenType::Operator };
				while (current)
				{
					if (is_operator)
					{
						if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L":")
						{
							if (name.empty())
							{
								E_InvalidPartitionName(__FUNCTION__, __LINE__, *current);
								return false;
							}
							break;
						}
						name += L":";
					}
					else
					{
						if (current->Item->Type != TokenType::Identifier)
						{
							E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
							return false;
						}
						name += current->Item->Value;
					}
					is_operator = !is_operator;
					current = Next(*current, true, true, true);
				}
				if (!is_operator)
				{
					if (current)
						E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					else
						E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
					return false;
				}
				out = current;
				return true;
			}

			bool CDecoder::ParseAttribute(ReleasablePtr<CAttributeList> &parent, List &list, PList &out)
			{
				static const StringArray ENDS{ L"...", L",", L"]]", L":>:>" };

				ReleasablePtr<CAttribute> attribute{ new CAttribute() };
				List *current;
				if (!ParseIdentifier(list, attribute->Identifier, false, false, false, false, false, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"...'/','/']]");
					return false;
				}
				if (!(current = Skip(*current, false)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"...'/','/']]");
					return false;
				}
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"(")
				{
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
						return false;
					}
					List *argument_end;
					while (current)
					{
						if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L")")
							break;
						if (!(argument_end = FindCloseParentheseOrComma(*current, false)))
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, *current, L",' or ')");
							return false;
						}
						attribute->Arguments.push_back(Range{ current, Prev(*argument_end, true, true, true) });
						current = argument_end;
						if (current->Item->Op->Name == L",")
						{
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, *argument_end);
								return false;
							}
						}
					}
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"...'/','/']]");
						return false;
					}
					attribute->hasArguments = true;
				}
				if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, ENDS))
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"...'/','/']]", TokenToString(*current->Item));
					return false;
				}
				parent->Attributes.push_back(attribute.move());
				out = current;
				return true;
			}

			bool CDecoder::ParseAttributeList(PEntity &parent, List &list, const bool is_after, PList &out)
			{
				ReleasablePtr<CAttributeList> attribute_list{ new CAttributeList() };
				List *current{ &list };
				// alignas(...)
				if (current->Item->Type == TokenType::Identifier)
				{
					if (current->Item->Value != L"alignas")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"alignas", TokenToString(*current->Item));
						return false;
					}
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"(");
						return false;
					}
					if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"(", TokenToString(*current->Item));
						return false;
					}
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
						return false;
					}
					attribute_list->AlignAs.Begin = current;
					if (!(current = FindCloseParenthese(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
						return false;
					}
					if (current == attribute_list->AlignAs.Begin)
					{
						E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L")");
						return false;
					}
					attribute_list->AlignAs.End = Prev(*current, true, true, true);
					out = current->Next;
					attribute_list->isAfter = is_after;
					parent->AttributeLists.push_back(attribute_list.move());
					return true;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
					return false;
				}
				// using attribute-namespace:
				if (current->Item->Type == TokenType::Identifier && current->Item->Value == L"using")
				{
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (current->Item->Type != TokenType::Identifier)
					{
						E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
						return false;
					}
					attribute_list->Namespace = current->Item->Value;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L":");
						return false;
					}
					if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L":")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L":", TokenToString(*current->Item));
						return false;
					}
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// attribute-list
				while (true)
				{
					if (!ParseAttribute(attribute_list, *current, current))
						return false;
					if (in(current->Item->Op->Name, ATTRIBUTE_LIST_ENDS))
						break;
					if (current->Item->Op->Name == L"...")
					{
						attribute_list->isPackExpansion = true;
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"]]");
							return false;
						}
						if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, ATTRIBUTE_LIST_ENDS))
						{
							E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"]]", TokenToString(*current->Item));
							return false;
						}
						break;
					}
					if (current->Item->Op->Name != L",")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L",", TokenToString(*current->Item));
						return false;
					}
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				out = current->Next;
				attribute_list->isAfter = is_after;
				parent->AttributeLists.push_back(attribute_list.move());
				return true;
			}

			bool CDecoder::ParseCommentsAndAttributes(PEntity &parent, List &list, PList &out)
			{
				List *current{ &list };
				while (current)
				{
					if (isNewLines(*current))
					{
						current = current->Next;
						continue;
					}
					if (isSLComment(*current))
					{
						parent->Comments.push_back(CEntity::Comment{ current->Item->Value, false, false });
						current = current->Next;
						continue;
					}
					if (isMLComment(*current))
					{
						parent->Comments.push_back(CEntity::Comment{ current->Item->Value, true, false });
						current = current->Next;
						continue;
					}
					if (isAttributeList(*current))
					{
						if (!ParseAttributeList(parent, *current, false, current))
							return false;
						continue;
					}
					break;
				}
				out = current;
				return true;
			}

			void CDecoder::ParsePrecedingComments(PEntity &parent, List &list)
			{
				List *current{ list.Prev }, *prev;
				while (current)
				{
					if (isNewLines(*current))
					{
						if (current->Item->Type == TokenType::Group && current->Item->Count > 1)
							return;
						if (!(prev = current->Prev))
							return;
						if (prev->Item->Type != TokenType::String || prev->Item->Op->Name != L"/*")
							return;
						current = prev;
						continue;
					}
					if (!isComment(*current))
						return;
					if (!(prev = Prev(*current, true, false, false)) || isNewLines(*prev) || isSLComment(*prev))
					{
						parent->Comments.insert(parent->Comments.begin(), CEntity::Comment{ current->Item->Value, current->Item->Op->Name == L"/*", false });
						current = current->Prev;
						continue;
					}
					return;
				}
			}

			void CDecoder::ParseTrailingComments(PEntity &parent, List &list, PList &out)
			{
				List *current{ &list };
				while (current)
				{
					if (isSLComment(*current))
					{
						parent->Comments.push_back(CEntity::Comment{ current->Item->Value, false, true });
						current = current->Next;
						break;
					}
					if (isMLComment(*current))
					{
						parent->Comments.push_back(CEntity::Comment{ current->Item->Value, true, true });
						current = current->Next;
						continue;
					}
					break;
				}
				out = current;
			}

			bool CDecoder::ParseClassBase(entities::CClassBase &target, List &list, PList &out)
			{
				static const StringArray SPECIFIERS{ L"virtual", L"private", L"protected", L"public" };
				static const StringArray ENDS{ L",", L"{", L"<%" };

				List *current{ &list };
				CEntity *entity{ &target };
				// [attr]
				while (current && isAttributeList(*current))
				{
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!isAttributeList(*current))
						break;
				}
				// [virtual] [private | public | protected]
				while (current && current->Item->Type == TokenType::Identifier && in(current->Item->Value, SPECIFIERS))
				{
					if (current->Item->Value == L"virtual")
					{
						if (target.isVirtual)
						{
							E_DuplicateVirtual(__FUNCTION__, __LINE__, *current);
							return false;
						}
						target.isVirtual = true;
					}
					else if (current->Item->Value == L"public")
					{
						if (target.isPublic)
						{
							E_DuplicatePublic(__FUNCTION__, __LINE__, *current);
							return false;
						}
						target.isPublic = true;
					}
					else if (current->Item->Value == L"protected")
					{
						if (target.isProtected)
						{
							E_DuplicateProtected(__FUNCTION__, __LINE__, *current);
							return false;
						}
						target.isProtected = true;
					}
					else
					{
						if (target.isPrivate)
						{
							E_DuplicatePrivate(__FUNCTION__, __LINE__, *current);
							return false;
						}
						target.isPrivate = true;
					}
					current = Next(*current, true, true, true);
				}
				if (!current)
				{
					E_UnexpectedEndExpectedBaseClass(__FUNCTION__, __LINE__, list);
					return false;
				}
				// base
				if (current->Item->Type == TokenType::Identifier && current->Item->Value == L"decltype")
				{
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"(");
						return false;
					}
					if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"(", TokenToString(*current->Item));
						return false;
					}
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
						return false;
					}
					target.Decltype.Begin = current;
					if (!(current = FindCloseParenthese(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
						return false;
					}
					if (current == target.Decltype.Begin)
					{
						E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L")");
						return false;
					}
					target.Decltype.End = Prev(*current, true, true, true);
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L",' or '{");
						return false;
					}
				}
				else
				{
					if (!ParseIdentifier(*current, target.Identifier, true, true, false, false, false, current))
						return false;
					if (!current)
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L",' or '{");
						return false;
					}
					if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"...") // Pack or pack index
					{
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L",' or '{");
							return false;
						}
						if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACKETS))
						{
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
								return false;
							}
							target.PackIndex.Begin = current;
							if (!(current = FindCloseBracket(*current)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"]");
								return false;
							}
							if (current == target.PackIndex.Begin)
							{
								E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L"]");
								return false;
							}
							target.PackIndex.End = Prev(*current, true, true, true);
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L",' or '{");
								return false;
							}
						}
						else
							target.Pack = true;
					}
				}
				// , or {
				if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, ENDS))
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L",' or '{", TokenToString(*current->Item));
					return false;
				}
				out = current;
				if ((current = Prev(*current, true, true, true)) && (current = current->Next))
					ParseTrailingComments(entity, *current, current);
				return true;
			}

			bool CDecoder::ParseTypeSpecifierSeq(PEntity &parent, std::vector<CEntity *> &specifiers, List &list, const bool is_parameter, PList &out)
			{
				static const StringArray NO_SPECIFIERS{ L"new" };

				List *current{ &list }, *next;
				bool type_required{ true }, type_allowed{ true };
				while (current)
				{
					if (isAttributeList(*current))
					{
						if (!ParseAttributeList(parent, *current, false, current))
							return false;
						continue;
					}
					if (current->Item->Type == TokenType::Identifier)
					{
						if (type_required && in(current->Item->Value, NO_SPECIFIERS))
						{
							E_ExpectedSpecifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
							return false;
						}
						if (current->Item->Value == L"__stdcall")
						{
							specifiers.push_back(new CStdCall());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"__cdecl")
						{
							specifiers.push_back(new CCDecl());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"__thiscall")
						{
							specifiers.push_back(new CThisCall());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"__fastcall")
						{
							specifiers.push_back(new CFastCall());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"__declspec" &&
							(next = Next(*current, true, true, true)) && next->Item->Type == TokenType::Operator && next->Item->Op->Name == L"(" &&
							(next = Next(*next, true, true, true)) && next->Item->Type == TokenType::Identifier && next->Item->Value == L"naked" &&
							(next = Next(*next, true, true, true)) && next->Item->Type == TokenType::Operator && next->Item->Op->Name == L")")
						{
							specifiers.push_back(new CNaked());
							current = Next(*next, true, true, true);
							continue;
						}
						if (current->Item->Value == L"friend")
						{
							specifiers.push_back(new CFriend());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"template")
						{
							specifiers.push_back(new CTemplateSpecifier());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"typedef")
						{
							specifiers.push_back(new CTypedef());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"inline")
						{
							specifiers.push_back(new CInline());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"virtual")
						{
							specifiers.push_back(new CVirtual());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"explicit")
						{
							ReleasablePtr<CExplicit> releasable{ new CExplicit() };
							current = Next(*current, true, true, true);
							if (m_eVersion >= Version::v20 && current && current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"(")
							{
								if (!(current = Next(*current, true, true, true)))
								{
									E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
									return false;
								}
								releasable->Body.Begin = current;
								if (!(current = FindCloseParenthese(*current)))
								{
									E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
									return false;
								}
								if (current == releasable->Body.Begin)
								{
									E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L")");
									return false;
								}
								releasable->Body.End = Prev(*current, true, true, true);
								current = Next(*current, true, true, true);
							}
							specifiers.push_back(releasable.move());
							continue;
						}
						if (current->Item->Value == L"constexpr")
						{
							specifiers.push_back(new CConstexpr());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"consteval")
						{
							specifiers.push_back(new CConsteval());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"constinit")
						{
							specifiers.push_back(new CConstinit());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"register")
						{
							specifiers.push_back(new CRegister());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"static")
						{
							specifiers.push_back(new CStatic());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"thread_local")
						{
							specifiers.push_back(new CThreadLocal());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"extern")
						{
							specifiers.push_back(new CExtern());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"mutable")
						{
							specifiers.push_back(new CMutable());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"char")
						{
							type_allowed = false;
							type_required = false;
							specifiers.push_back(new CChar());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"char8_t")
						{
							type_allowed = false;
							type_required = false;
							specifiers.push_back(new CChar8T());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"char16_t")
						{
							type_allowed = false;
							type_required = false;
							specifiers.push_back(new CChar16T());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"char32_t")
						{
							type_allowed = false;
							type_required = false;
							specifiers.push_back(new CChar32T());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"wchar_t")
						{
							type_allowed = false;
							type_required = false;
							specifiers.push_back(new CWCharT());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"bool")
						{
							type_allowed = false;
							type_required = false;
							specifiers.push_back(new CBool());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"short")
						{
							type_required = false;
							specifiers.push_back(new CShort());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"int")
						{
							type_allowed = false;
							type_required = false;
							specifiers.push_back(new CInt());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"long")
						{
							type_required = false;
							specifiers.push_back(new CLong());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"signed")
						{
							type_required = false;
							specifiers.push_back(new CSigned());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"unsigned")
						{
							type_required = false;
							specifiers.push_back(new CUnsigned());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"float")
						{
							type_allowed = false;
							type_required = false;
							specifiers.push_back(new CFloat());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"double")
						{
							type_allowed = false;
							type_required = false;
							specifiers.push_back(new CDouble());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"void")
						{
							type_allowed = false;
							type_required = false;
							specifiers.push_back(new CVoid());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"auto")
						{
							type_required = false;
							specifiers.push_back(new CAuto());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"typename")
						{
							specifiers.push_back(new CTypename());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"const")
						{
							specifiers.push_back(new CConst());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"volatile")
						{
							specifiers.push_back(new CVolatile());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"decltype")
						{
							type_allowed = false;
							type_required = false;
							ReleasablePtr<CDecltype> releasable{ new CDecltype() };
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"(");
								return false;
							}
							if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
							{
								E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"(", TokenToString(*current->Item));
								return false;
							}
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
								return false;
							}
							releasable->Body.Begin = current;
							if (!(current = FindCloseParenthese(*current)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
								return false;
							}
							if (current == releasable->Body.Begin)
							{
								E_ExpectedArgument(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
								return false;
							}
							releasable->Body.End = Prev(*current, true, true, true);
							specifiers.push_back(releasable.move());
							current = Next(*current, true, true, true);
							continue;
						}
						if (type_allowed && current->Item->Value == L"enum")
						{
							type_allowed = false;
							type_required = false;
							CEntity *entity;
							if (!ParseEnum(entity, *current, current))
								return false;
							specifiers.push_back(entity);
							continue;
						}
						if (type_allowed && in(current->Item->Value, CLASS_TYPES))
						{
							type_allowed = false;
							type_required = false;
							CEntity *entity;
							if (!ParseClass(entity, *current, current))
								return false;
							specifiers.push_back(entity);
							continue;
						}
					}

					if (type_allowed && (current->Item->Type == TokenType::Identifier || (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"::")))
					{
						List *next2{ nullptr };
						CIdentifier identifier;
						if (!ParseIdentifier(*current, identifier, true, true, true, true, true, next))
							return false;
						if (!identifier.Operator.empty())
							break;
						// identifier...
						if (next && next->Item->Type == TokenType::Operator && next->Item->Op->Name == L"..." &&
							(next2 = Next(*next, true, true, true)) && next2->Item->Type == TokenType::Operator && in(next2->Item->Op->Name, BRACKETS))
						{
							ReleasablePtr<CPackIndexing> releasable{ new CPackIndexing() };
							if (!(current = Next(*next2, true, true, true)))
							{
								E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, *next2);
								return false;
							}
							releasable->Body.Begin = current;
							if (!(current = FindCloseBracket(*current)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, *next2, L"]");
								return false;
							}
							if (current == releasable->Body.Begin)
							{
								E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L"]");
								return false;
							}
							releasable->Body.End = Prev(*current, true, true, true);
							type_allowed = false;
							type_required = false;
							releasable->Identifier = identifier;
							specifiers.push_back(releasable.move());
							current = Next(*current, true, true, true);
							continue;
						}

						// unsigned int32 uint32;
						// unsigned a;
						bool is_next_identifier{ next && (next->Item->Type == TokenType::Identifier || (next->Item->Type == TokenType::Operator && next->Item->Op->Name == L"::")) };
						if (!type_required && !is_next_identifier)
							break;

						// identifier
						if (is_parameter || !next || next->Item->Type != TokenType::Operator || next->Item->Op->Name != L"(")
						{
							CName *name{ new CName() };
							name->Identifier = identifier;
							if (next && next->Item->Type == TokenType::Operator && next->Item->Op->Name == L"...")
							{
								name->ParameterPack = true;
								next = next2;
							}
							type_allowed = false;
							type_required = false;
							specifiers.push_back(name);
							current = next;
							continue;
						}
					}
					break;
				}
				out = current;
				return true;
			}

			bool CDecoder::ParseParameterPack(PEntity &target, List &list, PList &out)
			{
				ReleasablePtr<CParameterPack> releasable{ new CParameterPack() };
				CEntity *entity{ releasable };
				List *current{ Next(list, true, true, true) };
				if (!ParseIdentifier(*current, releasable->Identifier, false, false, false, false, false, current))
					return false;
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				out = current;
				target = releasable.move();
				return true;
			}

			void CDecoder::ParseCallSpecifiers(std::vector<CEntity *> &specifiers, List &list, PList &out)
			{
				List *current{ &list }, *next;
				while (current && current->Item->Type == TokenType::Identifier)
				{
					if (current->Item->Value == L"__stdcall")
					{
						specifiers.push_back(new CStdCall());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"__cdecl")
					{
						specifiers.push_back(new CCDecl());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"__thiscall")
					{
						specifiers.push_back(new CThisCall());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"__fastcall")
					{
						specifiers.push_back(new CFastCall());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"__declspec" &&
						(next = Next(*current, true, true, true)) && next->Item->Type == TokenType::Operator && next->Item->Op->Name == L"(" &&
						(next = Next(*next, true, true, true)) && next->Item->Type == TokenType::Identifier && next->Item->Value == L"naked" &&
						(next = Next(*next, true, true, true)) && next->Item->Type == TokenType::Operator && next->Item->Op->Name == L")")
					{
						specifiers.push_back(new CNaked());
						current = Next(*next, true, true, true);
						continue;
					}
					break;
				}
				out = current;
			}

			bool CDecoder::ParsePtrDeclarator(PBaseDeclarator &target, List &list, const bool is_parameter, const bool allow_bitfield, bool &has_body, PList &out)
			{
				ReleasablePtr<CPtrDeclarator> releasable{ new CPtrDeclarator() };
				CEntity *entity{ releasable };
				List *current{ Next(list, true, true, true) };
				if (current)
					ParseCallSpecifiers(releasable->CallSpecifiers, *current, current);
				if (!current)
				{
					E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// [cv]
				while (current)
				{
					if (current->Item->Type != TokenType::Identifier)
						break;
					if (current->Item->Value == L"const")
					{
						releasable->Specifiers.push_back(new CConst());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"volatile")
					{
						releasable->Specifiers.push_back(new CVolatile());
						current = Next(*current, true, true, true);
						continue;
					}
					break;
				}
				if (!current)
				{
					E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (!ParseDeclarator(releasable->Declarator, *current, is_parameter, allow_bitfield, has_body, out))
					return false;
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParseLValueDeclarator(PBaseDeclarator &target, List &list, const bool is_parameter, const bool allow_bitfield, bool &has_body, PList &out)
			{
				ReleasablePtr<CLValueDeclarator> releasable{ new CLValueDeclarator() };
				CEntity *entity{ releasable };
				List *current{ Next(list, true, true, true) };
				if (current)
					ParseCallSpecifiers(releasable->CallSpecifiers, *current, current);
				if (!current)
				{
					E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				if (!current)
				{
					E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (!ParseDeclarator(releasable->Declarator, *current, is_parameter, allow_bitfield, has_body, out))
					return false;
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParseRValueDeclarator(PBaseDeclarator &target, List &list, const bool is_parameter, const bool allow_bitfield, bool &has_body, PList &out)
			{
				ReleasablePtr<CRValueDeclarator> releasable{ new CRValueDeclarator() };
				CEntity *entity{ releasable };
				List *current{ Next(list, true, true, true) };
				if (current)
					ParseCallSpecifiers(releasable->CallSpecifiers, *current, current);
				if (!current)
				{
					E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				if (!current)
				{
					E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (!ParseDeclarator(releasable->Declarator, *current, is_parameter, allow_bitfield, has_body, out))
					return false;
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParseNoPtrDeclarator(PBaseDeclarator &target, List &list, const bool allow_bitfield, bool &has_body, PList &out)
			{
				ReleasablePtr<CNoPtrDeclarator> releasable{ new CNoPtrDeclarator() };
				List *current{ Next(list, true, true, true) };
				if (current)
					ParseCallSpecifiers(releasable->CallSpecifiers, *current, current);
				if (!current)
				{
					E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (!ParseDeclarator(releasable->Declarator, *current, false, allow_bitfield, has_body, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
					return false;
				}
				if (!releasable->Declarator)
				{
					E_ExpectedDeclarator(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L")")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L")", TokenToString(*current->Item));
					return false;
				}
				out = Next(*current, true, true, true);
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParseIdDeclarator(PBaseDeclarator &target, List &list, const bool is_parameter, const bool allow_bitfield, bool &has_body, PList &out)
			{
				static const StringArray OPS{ L"::", L"~" };

				ReleasablePtr<CIdDeclarator> releasable{ new CIdDeclarator() };
				CEntity *entity{ releasable };
				List *current{ &list };
				// [...]
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"...")
				{
					releasable->Pack = true;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"...");
						return false;
					}
				}
				// identifier
				if (current->Item->Type == TokenType::Identifier || (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, OPS)))
				{
					if (!ParseIdentifier(*current, releasable->Identifier, true, true, true, true, true, current))
						return false;
				}
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// nested-name-specifier* [attr] [cv] declarator
				if (!releasable->Identifier.Names.empty() && releasable->Identifier.Names[releasable->Identifier.Names.size() - 1].Name == L"*")
				{
					// [cv]
					while (current)
					{
						if (current->Item->Type == TokenType::Identifier)
						{
							if (current->Item->Value == L"const")
							{
								releasable->Specifiers.push_back(new CConst());
								current = Next(*current, true, true, true);
								continue;
							}
							if (current->Item->Value == L"volatile")
							{
								releasable->Specifiers.push_back(new CVolatile());
								current = Next(*current, true, true, true);
								continue;
							}
						}
						break;
					}
					if (!current)
					{
						E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!ParseDeclarator(releasable->Declarator, *current, is_parameter, allow_bitfield, has_body, current))
						return false;
				}
				out = current;
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParseArray(PBaseDeclarator &target, List &list, PList &out)
			{
				ReleasablePtr<CArray> releasable{ new CArray() };
				CEntity *entity{ releasable };
				// [...]
				List *current{ Next(list, true, true, true) }, *end;
				if (!current)
				{
					E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (!(end = FindCloseBracket(*current)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, *current, L"]");
					return false;
				}
				if (end != current)
				{
					releasable->Body.Begin = current;
					releasable->Body.End = Prev(*end, true, true, true);
				}
				current = Next(*end, true, true, true);
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				if (!(out = current))
				{
					E_UnexpectedEndAfterArray(__FUNCTION__, __LINE__, list);
					return false;
				}
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParseFunctionParameter(PFunctionParameter &target, List &list, PList &out)
			{
				ReleasablePtr<CFunctionParameter> releasable{ new CFunctionParameter() };
				CEntity *entity{ releasable };
				ParsePrecedingComments(entity, list);
				List *current{ &list };
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// [...]
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"...")
				{
					if (!(out = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"...");
						return false;
					}
					target = releasable.move();
					return true;
				}
				// [this]
				if (current->Item->Type == TokenType::Identifier && current->Item->Value == L"this")
				{
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"this");
						return false;
					}
					releasable->This = true;
				}
				// decl-specifier-seq
				if (!ParseTypeSpecifierSeq(entity, releasable->Specifiers, *current, true, current))
					return false;
				if (!current)
				{
					E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				// [ [...] ]
				if (!releasable->Specifiers.empty())
				{
					while (current && current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACKETS))
					{
						CBaseDeclarator *array_declarator;
						if (!ParseArray(array_declarator, *current, current))
							return false;
						array_declarator->Declarator = releasable->ArrayDeclarator;
						releasable->ArrayDeclarator = array_declarator;
					}
					if (!current)
					{
						E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// [declarator]
				bool has_body;
				if (!ParseDeclarator(releasable->Declarator, *current, true, false, has_body, current))
					return false;
				if (!current)
				{
					E_UnexpectedEndAfterDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (has_body)
				{
					E_UnexpectedFunctionDefinition(__FUNCTION__, __LINE__, list);
					return false;
				}
				out = current;
				target = releasable.move();
				// Comments. Could be before and after ","
				current = Prev(*out, true, true, true)->Next;
				ParseTrailingComments(entity, *current, current);
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"," && (current = current->Next))
					ParseTrailingComments(entity, *current, current);
				return true;
			}

			bool CDecoder::ParseFunctionPreContract(PEntity &target, List &list, PList &out)
			{
				ReleasablePtr<CFunctionPreContract> releasable{ new CFunctionPreContract() };
				CEntity *entity{ releasable };
				List *current{ Next(list, true, true, true) };
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// (...)
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"(");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"(", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
					return false;
				}
				releasable->Body.Begin = current;
				if (!(current = FindCloseParenthese(*current)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
					return false;
				}
				if (current == releasable->Body.Begin)
				{
					E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L")");
					return false;
				}
				releasable->Body.End = Prev(*current, true, true, true);
				if (!(out = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L")");
					return false;
				}
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParseFunctionPostContract(PEntity &target, List &list, PList &out)
			{
				ReleasablePtr<CFunctionPostContract> releasable{ new CFunctionPostContract() };
				CEntity *entity{ releasable };
				List *current{ Next(list, true, true, true) };
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// (...)
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"(");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"(", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
					return false;
				}
				releasable->Body.Begin = current;
				if (!(current = FindCloseParenthese(*current)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
					return false;
				}
				if (current == releasable->Body.Begin)
				{
					E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L")");
					return false;
				}
				releasable->Body.End = Prev(*current, true, true, true);
				if (!(out = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L")");
					return false;
				}
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParseFunction(PBaseDeclarator &target, List &list, bool &parameters_valid, PList &out)
			{
				parameters_valid = true;
				ReleasablePtr<CFunction> releasable{ new CFunction() };
				CEntity *entity{ releasable };
				CFunctionParameter *parameter;
				// ([parameter-list])
				List *current{ Next(list, true, true, true) }, *end, *next;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"(");
					return false;
				}
				bool is_variadic{ false }, require_parameter{ false };
				while (current)
				{
					if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L")")
					{
						if (require_parameter)
						{
							parameters_valid = false;
							return false;
						}
						break;
					}
					if (is_variadic)
					{
						parameters_valid = false;
						return false;
					}
					if (!ParseFunctionParameter(parameter, *current, current))
					{
						parameters_valid = false;
						return false;
					}
					releasable->Parameters.push_back(parameter);
					if (current->Item->Type != TokenType::Operator)
					{
						parameters_valid = false;
						return false;
					}
					if (current->Item->Op->Name == L",")
					{
						current = Next(*current, true, true, true);
						require_parameter = true;
					}
					else
						require_parameter = false;
					if (!parameter->Declarator && parameter->Specifiers.empty())
					{
						if (is_variadic)
						{
							parameters_valid = false;
							return false;
						}
						is_variadic = true;
					}
				}
				if (!current)
				{
					parameters_valid = false;
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L")");
					return false;
				}
				// [cv, override, final, &, &&, noexcept, throw]
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L"&")
						{
							releasable->Specifiers.push_back(new CLRef());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Op->Name == L"&&")
						{
							releasable->Specifiers.push_back(new CRRef());
							current = Next(*current, true, true, true);
							continue;
						}
						break;
					}
					if (current->Item->Type == TokenType::Identifier)
					{
						if (current->Item->Value == L"const")
						{
							releasable->Specifiers.push_back(new CConst());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"volatile")
						{
							releasable->Specifiers.push_back(new CVolatile());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"override")
						{
							releasable->Specifiers.push_back(new COverride());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"final")
						{
							releasable->Specifiers.push_back(new CFinal());
							current = Next(*current, true, true, true);
							continue;
						}
						if (current->Item->Value == L"noexcept")
						{
							releasable->NoExcept = true;
							if ((current = Next(*current, true, true, true)) && current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"(")
							{
								if (!(current = Next(*current, true, true, true)))
								{
									E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"(");
									return false;
								}
								if (!(end = FindCloseParenthese(*current)))
								{
									E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
									return false;
								}
								if (end != current)
								{
									releasable->NoExceptBody.Begin = current;
									releasable->NoExceptBody.End = Prev(*end, true, true, true);
								}
								current = Next(*end, true, true, true);
							}
							continue;
						}
						if (current->Item->Value == L"throw")
						{
							releasable->Throw = true;
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"(");
								return false;
							}
							if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
							{
								E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"(", TokenToString(*current->Item));
								return false;
							}
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
								return false;
							}
							if (!(end = FindCloseParenthese(*current)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, *current, L")");
								return false;
							}
							if (end != current)
							{
								releasable->ThrowBody.Begin = current;
								releasable->ThrowBody.End = Prev(*end, true, true, true);
							}
							current = Next(*end, true, true, true);
							continue;
						}
					}
					break;
				}
				if (!current)
				{
					E_UnexpectedEndAfterParameters(__FUNCTION__, __LINE__, list);
					return false;
				}
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// [->trailing]
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"->")
				{
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"->");
						return false;
					}
					releasable->Trailing.Begin = current;
					if (!(end = FindFunctionTrailingEnd(*current)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"->");
						return false;
					}
					if (end == current)
					{
						E_ExpectedTrailing(__FUNCTION__, __LINE__, *current, L"->");
						return false;
					}
					releasable->Trailing.End = Prev(*end, true, true, true);
					current = end;
				}
				// [requires-clause]
				if (current->Item->Type == TokenType::Identifier && current->Item->Value == L"requires")
				{
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"requires");
						return false;
					}
					releasable->Requires.Begin = current;
					if (!(current = FindRequiresEnd(*current, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"requires");
						return false;
					}
					releasable->Requires.End = current;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"requires");
						return false;
					}
				}
				// [contract-specs: pre [attr] (...), post [attr] (...)]
				while (current)
				{
					if (current->Item->Type != TokenType::Identifier)
						break;
					if (current->Item->Value == L"pre")
					{
						CEntity *pre_contract;
						if (!ParseFunctionPreContract(pre_contract, *current, current))
							return false;
						releasable->Contracts.push_back(pre_contract);
						continue;
					}
					if (current->Item->Value == L"post")
					{
						CEntity *post_contract;
						if (!ParseFunctionPostContract(post_contract, *current, current))
							return false;
						releasable->Contracts.push_back(post_contract);
						continue;
					}
					break;
				}
				if (!current)
				{
					E_UnexpectedEndAfterParameters(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"=")
				{
					if (!(next = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"=");
						return false;
					}
					// [= 0]
					if (next->Item->Type == TokenType::Integer && next->Item->Integer == 0)
					{
						releasable->Abstract = true;
						if (!(out = Next(*next, true, true, true)))
						{
							E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"= 0");
							return false;
						}
					}
					// [= default]
					else if (next->Item->Type == TokenType::Identifier && next->Item->Value == L"default")
					{
						releasable->Default = true;
						if (!(out = Next(*next, true, true, true)))
						{
							E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"= default");
							return false;
						}
					}
					// [= delete [(...)]]
					else if (next->Item->Type == TokenType::Identifier && next->Item->Value == L"delete")
					{
						releasable->Deleted = true;
						if (!(current = Next(*next, true, true, true)))
						{
							E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"= delete");
							return false;
						}
						if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
								return false;
							}
							if (current->Item->Type != TokenType::String || current->Item->Op->Name != L"\"")
							{
								E_ExpectedString(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
								return false;
							}
							releasable->DeleteReason = current->Item->Value;
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
								return false;
							}
							if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L")")
							{
								E_ExpectedToken(__FUNCTION__, __LINE__, *current, L")", TokenToString(*current->Item));
								return false;
							}
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L")");
								return false;
							}
						}
						out = current;
					}
					else
						out = current;
				}
				// [[:ctor-initializer] compaund-statement]
				else if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L":")
				{
					releasable->Body.Begin = current;
					if (!(current = FindMemberInitializationEnd(*current)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L":");
						return false;
					}
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterMemberInitialization(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = FindCloseBrace(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
						return false;
					}
					releasable->Body.End = current;
					out = current->Next;
				}
				// [try [:ctro-initializer] compaund-statement handler-seq]]
				else if (current->Item->Type == TokenType::Identifier && current->Item->Value == L"try")
				{
					releasable->Body.Begin = current;
					if (!(current = FindTryCatchEnd(*current, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"try");
						return false;
					}
					releasable->Body.End = current;
					out = current->Next;
				}
				// [compaund-statement]
				else if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACES))
				{
					releasable->Body.Begin = current;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"{");
						return false;
					}
					if (!(current = FindCloseBrace(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
						return false;
					}
					releasable->Body.End = current;
					out = current->Next;
				}
				else
					out = current;
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParseBitfield(PBaseDeclarator &parent, List &list, PList &out)
			{
				if (parent->Type != EntityType::IdDeclarator)
				{
					E_BitfieldRequireIdDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				CIdDeclarator *d{ cast<CIdDeclarator *>(parent) };
				if (d->Declarator)
				{
					E_BitfieldRequireIdDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (d->Identifier.Destructor)
				{
					E_BitfieldRequireIdDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (!d->Identifier.Operator.empty())
				{
					E_BitfieldRequireIdDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				List *current;
				if (!(current = Next(list, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L":");
					return false;
				}
				parent->Bitfield.Begin = current;
				if (!(current = FindBraceOrCommaOrEqualOrSemicolon(*current)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"{'/','/'='/=;");
					return false;
				}
				if (current == parent->Bitfield.Begin)
				{
					E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L":");
					return false;
				}
				parent->Bitfield.End = Prev(*current, true, true, true);
				out = current;
				return true;
			}

			bool CDecoder::ParseInitialization(PBaseDeclarator &parent, List &list, const bool is_parameter, PList &out)
			{
				if (list.Item->Type != TokenType::Operator)
					return true;
				List *current{ &list };
				if (current->Item->Op->Name == L"=")
				{
					parent->InitializationType = CBaseDeclarator::InitializationType::Equals;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"=");
						return false;
					}
					parent->Initialization.Begin = current;
					current = is_parameter ? FindCloseParentheseOrCommaOrSemicolon(*current) : FindCommaOrSemicolon(*current, true);
					if (!current)
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"=");
						return false;
					}
					if (current == parent->Initialization.Begin)
					{
						E_ExpectedArgument(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
						return false;
					}
					parent->Initialization.End = Prev(*current, true, true, true);
					out = current;
					return true;
				}
				if (!is_parameter)
				{
					if (current->Item->Op->Name == L"(")
					{
						parent->InitializationType = CBaseDeclarator::InitializationType::Parentheses;
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"(");
							return false;
						}
						if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L")")
						{
							parent->Initialization.Begin = current;
							if (!(current = FindCloseParenthese(*current)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
								return false;
							}
							parent->Initialization.End = Prev(*current, true, true, true);
						}
						out = Next(*current, true, true, true);
						return true;
					}
					if (in(current->Item->Op->Name, BRACES))
					{
						parent->InitializationType = CBaseDeclarator::InitializationType::Braces;
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"{");
							return false;
						}
						if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, BRACE_ENDS))
						{
							parent->Initialization.Begin = current;
							if (!(current = FindCloseBrace(*current)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
								return false;
							}
							parent->Initialization.End = Prev(*current, true, true, true);
						}
						out = Next(*current, true, true, true);
						return true;
					}
				}
				out = current;
				return true;
			}

			bool CDecoder::ParseEntity(PEntity &parent, List &list, const bool in_block, const bool declaration_only, const bool allow_bitfield, bool &should_break, PList &out)
			{
				should_break = false;
				List *current{ &list }, *start;
				// Parse and add standalone comments
				while (current)
				{
					if (isNewLines(*current))
					{
						current = current->Next;
						continue;
					}
					if (!(start = FindEntity(*current)))
						return false;
					if (isSLComment(*start))
					{
						ParseSLComment(parent, *start, current);
						continue;
					}
					if (isMLComment(*start))
					{
						ParseMLComment(parent, *start, current);
						continue;
					}
					break;
				}
				if (!current) // Only comments were here (at the end)
				{
					out = nullptr;
					return true;
				}
				if (in_block && current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACE_ENDS))
				{
					out = current;
					return true;
				}

				// Non-declarations
				if (!declaration_only)
				{
					if (isModule(*start))
					{
						if (parent->Type == EntityType::Module)
						{
							should_break = true;
							out = current;
							return true;
						}
						return ParseModule(parent, *current, out);
					}
					if (isImport(*start))
						return ParseImport(parent, *current, out);
				}

				if (isExport(*start))
					return ParseExport(parent, *current, out);

				return ParseDeclaration(parent, *current, allow_bitfield, out);
			}

			bool CDecoder::ParseList(PEntity &parent, List &list, const bool in_block, const bool allow_bitfield, PList &out)
			{
				static const std::vector<EntityType> ALL_ENTITIES{ EntityType::Root, EntityType::Module };

				List *current{ &list };
				bool should_break;
				while (current && !m_bAborted)
				{
					if (m_pProgressListener)
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
					if (isNewLines(*current))
					{
						current = current->Next;
						continue;
					}

					if (in_block && current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACE_ENDS))
						break;

					if (!ParseEntity(parent, *current, in_block, !in(parent->Type, ALL_ENTITIES), allow_bitfield, should_break, current))
						return false;
					if (should_break)
						break;
				}
				if (in_block && !current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
					return false;
				}
				out = current;
				return true;
			}

			void CDecoder::ParseSLComment(PEntity &parent, List &list, PList &out)
			{
				CComment *entity;
				parent->Entities.push_back(entity = new CComment(list.Item->Value, false));
				out = list.Next;
			}

			void CDecoder::ParseMLComment(PEntity &parent, List &list, PList &out)
			{
				CComment *entity;
				parent->Entities.push_back(entity = new CComment(list.Item->Value, true));
				out = list.Next;
			}

			bool CDecoder::ParseEmpty(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CEmpty> releasable{ new CEmpty() };
				CEntity *entity{ releasable };
				if (!ParseCommentsAndAttributes(entity, list, out))
					return false;
				if (!out)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
					return false;
				}
				if (out->Item->Type != TokenType::Operator || out->Item->Op->Name != L";")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *out, L";", TokenToString(*out->Item));
					return false;
				}
				if ((out = out->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseBlock(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CBlock> releasable{ new CBlock() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"{");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, BRACES))
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"{", TokenToString(*current->Item));
					return false;
				}
				current = current->Next;
				while (current)
				{
					if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACE_ENDS))
						break;
					if (!ParseList(entity, *current, true, false, current))
						return false;
				}
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseModule(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CModule> releasable{ new CModule() };
				CEntity *entity{ releasable };
				List *current, *next;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					return false;
				}
				if (current->Item->Value == L"export")
				{
					releasable->isExport = true;
					current = Next(*current, true, true, true);
				}
				else
				{
					if (current->Item->Value != L"module")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"module", TokenToString(*current->Item));
						return false;
					}
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"module");
					return false;
				}
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L";") // module;
				{
					if (releasable->isExport)
					{
						E_ExportModuleWithoutName(__FUNCTION__, __LINE__, *current);
						return false;
					}
				}
				else if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L":" &&
					(next = Next(*current, true, true, true)) && next->Item->Type == TokenType::Identifier && next->Item->Value == L"private") // module :private;
				{
					if (releasable->isExport)
					{
						E_ExportPrivateModule(__FUNCTION__, __LINE__, *current);
						return false;
					}
					if (!(current = Next(*next, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
						return false;
					}
					if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L";")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
						return false;
					}
					releasable->isPrivate = true;
				}
				else // [export] module name [partition] [attr];
				{
					if (!ParseModuleName(*current, releasable->Name, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterModuleName(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (current->Item->Type == TokenType::Identifier || (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L":"))
					{
						if (!ParsePartitionName(*current, releasable->Partition, current))
							return false;
						if (!current)
						{
							E_UnexpectedEndAfterPartitionName(__FUNCTION__, __LINE__, list);
							return false;
						}
					}
					while (isAttributeList(*current))
					{
						if (!ParseAttributeList(entity, *current, true, current))
							return false;
						if (!current)
						{
							E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
							return false;
						}
						if (!(current = Skip(*current, false)))
						{
							E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
							return false;
						}
					}
					if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L";")
						return false;
				}
				if ((current = current->Next))
				{
					ParseTrailingComments(entity, *current, current);
					if (current && !ParseList(entity, *current, false, false, current))
						return false;
				}
				parent->Entities.push_back(releasable.move());
				out = current;
				return true;
			}

			bool CDecoder::ParseImport(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CImport> releasable{ new CImport() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"import");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					return false;
				}
				if (current->Item->Value == L"export")
				{
					releasable->isExport = true;
					current = Next(*current, true, true, true);
				}
				else
				{
					if (current->Item->Value != L"import")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"import", TokenToString(*current->Item));
						return false;
					}
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"import");
					return false;
				}
				if (current->Item->Type == TokenType::Identifier)
				{
					if (!ParseModuleName(*current, releasable->Name, current))
						return false;
				}
				else if (current->Item->Type == TokenType::String && current->Item->Op->Name == L"\"")
				{
					if (!current->Item->Prefix.empty())
					{
						E_ExpectedAnsi(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
						return false;
					}
					releasable->Header = current->Item->Value;
					current = Next(*current, true, true, true);
				}
				else if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"<")
				{
					current = current->Next;
					while (current && (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L">"))
					{
						if (isNewLines(*current) || isSpaces(*current))
							releasable->Header += L" ";
						else
							releasable->Header += current->Item->Value;
						current = current->Next;
					}
					if (!current)
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
						return false;
					}
					current = Next(*current, true, true, true);
					releasable->isStdHeader = true;
				}
				else
				{
					if (!ParsePartitionName(*current, releasable->Partition, current))
						return false;
				}
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
					return false;
				}
				if (!(current = Skip(*current, false)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
					return false;
				}
				while (isAttributeList(*current))
				{
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L";")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
					return false;
				}
				if ((current = current->Next))
					ParseTrailingComments(entity, *current, current);
				out = current;
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseExport(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CExport> releasable{ new CExport() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"export");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"export")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"export", TokenToString(*current->Item));
					return false;
				}
				if (!(current = current->Next))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"export");
					return false;
				}
				bool dummy;
				if (!ParseEntity(entity, *current, false, true, false, dummy, out))
					return false;
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseLanguageLinkage(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CLanguageLinkage> releasable{ new CLanguageLinkage() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"extern");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"extern")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"extern", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"extern");
					return false;
				}
				if (current->Item->Type != TokenType::String || current->Item->Op->Name != L"\"" || !current->Item->Prefix.empty())
				{
					E_ExpectedAnsi(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					return false;
				}
				releasable->Name = current->Item->Value;
				if (!(current = current->Next))
				{
					E_UnexpectedEndAfterString(__FUNCTION__, __LINE__, list);
					return false;
				}
				bool dummy;
				if (!ParseEntity(entity, *current, false, true, false, dummy, out))
					return false;
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseAsm(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CAsm> releasable{ new CAsm() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"asm");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"asm")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"asm", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"(");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"(", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"(");
					return false;
				}
				releasable->Body.Begin = current;
				if (current->Item->Type == TokenType::String && current->Item->Op->Name == L"\"")
				{
					releasable->Body.End = current;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
						return false;
					}
				}
				else
				{
					List *end{ FindCloseParenthese(*current) };
					if (!end)
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, *current, L")");
						return false;
					}
					if (end == current)
					{
						E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L")");
						return false;
					}
					releasable->Body.End = Prev(*end, true, true, true);
					current = end;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L")")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L")", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, *current, L";");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L";")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseNamespaceAlias(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CNamespaceAlias> releasable{ new CNamespaceAlias() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"namespace");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"namespace")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"namespace", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					return false;
				}
				releasable->Alias = current->Item->Value;
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"=");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"=")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"=", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"=");
					return false;
				}
				if (!ParseIdentifier(*current, releasable->Identifier, false, false, false, false, false, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L";")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseNamespace(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CNamespace> releasable{ new CNamespace() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"namespace");
					return false;
				}
				// [inline]
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					return false;
				}
				if (current->Item->Value == L"inline")
				{
					releasable->isInline = true;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"namespace");
						return false;
					}
					if (current->Item->Type != TokenType::Identifier)
					{
						E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
						return false;
					}
				}
				// namespace
				if (current->Item->Value != L"namespace")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"namespace", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"namespace");
					return false;
				}
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// [names]
				if (current->Item->Type == TokenType::Identifier)
				{
					if (current->Item->Value == L"inline")
					{
						E_InlineNotAllowed(__FUNCTION__, __LINE__, *current);
						return false;
					}
					releasable->Name = current->Item->Value;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"{");
						return false;
					}
					CNamespace *t;
					while (current)
					{
						if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"::")
							break;
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
							return false;
						}
						if (current->Item->Type != TokenType::Identifier)
						{
							E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
							return false;
						}
						entity->Entities.push_back(t = new CNamespace());
						if (current->Item->Value == L"inline")
						{
							t->isInline = true;
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
								return false;
							}
							if (current->Item->Type != TokenType::Identifier)
							{
								E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
								return false;
							}
						}
						t->Name = current->Item->Value;
						entity = t;
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"{");
							return false;
						}
					}
				}
				// { }
				if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, BRACES))
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"{", TokenToString(*current->Item));
					return false;
				}
				if (!ParseBlock(entity, *current, out))
					return false;
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseUsingNamespace(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CUsingNamespace> releasable{ new CUsingNamespace() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"using");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"using")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"using", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"namespace");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"namespace")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"namespace", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"namespace");
					return false;
				}
				if (!ParseIdentifier(*current, releasable->Identifier, false, false, false, false, false, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L";")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseUsingEnum(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CUsingEnum> releasable{ new CUsingEnum() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"using");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"using")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"using", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"enum");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"enum")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"enum", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"enum");
					return false;
				}
				if (!ParseIdentifier(*current, releasable->Identifier, true, true, false, false, false, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L";")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseTypeAlias(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CTypeAlias> releasable{ new CTypeAlias() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"using");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"using")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"using", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"using");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					return false;
				}
				releasable->Alias = current->Item->Value;
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
					return false;
				}
				while (current && isAttributeList(*current))
				{
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"=")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"=", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"=");
					return false;
				}
				releasable->TypeId.Begin = current;
				if (!(current = FindSemicolon(*current)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
					return false;
				}
				if (current == releasable->TypeId.Begin)
				{
					E_ExpectedTypeId(__FUNCTION__, __LINE__, *current, L";");
					return false;
				}
				releasable->TypeId.End = Prev(*current, true, true, true);
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseUsing(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CUsing> releasable{ new CUsing() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"using");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"using")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"using", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"using");
					return false;
				}
				while (current)
				{
					CUsing::Declarator d{ false, false };
					if (current->Item->Type == TokenType::Identifier && current->Item->Value == L"typename")
					{
						d.isTypename = true;
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"typename");
							return false;
						}
					}
					if (!ParseIdentifier(*current, d.Identifier, true, true, true, false, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
						return false;
					}
					if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"...")
					{
						d.isPackExpansion = true;
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"...");
							return false;
						}
					}
					releasable->Declarators.push_back(d);
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L",")
						{
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L",");
								return false;
							}
							continue;
						}
						if (current->Item->Op->Name == L";")
							break;
					}
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseTemplate(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CTemplate> releasable{ new CTemplate() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"template");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"template")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"template", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"<");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"<")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"<", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L">");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L">")
				{
					List *end;
					while (current)
					{
						if (!(end = FindCommaOrGreater(*current, true)))
							return false;
						if (end == current)
						{
							E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
							return false;
						}
						releasable->Parameters.push_back(Range{ current, Prev(*end, true, true, true) });
						current = end;
						if (current->Item->Type != TokenType::Operator)
						{
							E_ExpectedToken(__FUNCTION__, __LINE__, *current, L",' or '>", TokenToString(*current->Item));
							return false;
						}
						if (current->Item->Op->Name == L",")
						{
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
								return false;
							}
							continue;
						}
						if (current->Item->Op->Name != L">")
						{
							E_ExpectedToken(__FUNCTION__, __LINE__, *current, L">", TokenToString(*current->Item));
							return false;
						}
						break;
					}
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L">");
					return false;
				}
				if (current->Item->Type == TokenType::Identifier && current->Item->Value == L"requires")
				{
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"requires");
						return false;
					}
					releasable->Requires.Begin = current;
					if (!(current = FindRequiresEnd(*current, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"requires");
						return false;
					}
					releasable->Requires.End = current;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"requires");
						return false;
					}
				}
				if (isConcept(*current))
				{
					if (!ParseConcept(entity, *current, out))
						return false;
				}
				else
				{
					bool dummy;
					if (!ParseEntity(entity, *current, false, true, false, dummy, out))
						return false;
				}
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseConcept(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CConcept> releasable{ new CConcept() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"concept");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"concept")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"concept", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"concept");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					return false;
				}
				releasable->Name = current->Item->Value;
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"=");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"=")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"=", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"=");
					return false;
				}
				releasable->Body.Begin = current;
				if (!(current = FindSemicolon(*current)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
					return false;
				}
				if (current == releasable->Body.Begin)
				{
					E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L";");
					return false;
				}
				releasable->Body.End = Prev(*current, true, true, true);
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseEnum(PEntity &target, List &list, PList &out)
			{
				static const StringArray SCOPES{ L"class", L"struct" };

				ReleasablePtr<CEnum> releasable{ new CEnum() };
				CEntity *entity{ releasable };
				List *current{ &list };
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"enum");
					return false;
				}
				// [scope]
				if (current->Item->Type == TokenType::Identifier && in(current->Item->Value, SCOPES))
				{
					releasable->Scope = current->Item->Value;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, releasable->Scope);
						return false;
					}
				}
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// [name]
				if (current->Item->Type == TokenType::Identifier || (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"::"))
				{
					if (!ParseIdentifier(*current, releasable->Identifier, false, false, false, false, false, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// [:base] TODO: rework, base is type-specifier-seq
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L":")
				{
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L":");
						return false;
					}
					releasable->Base.Begin = current;
					if (!(current = FindBraceOrSemicolon(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
						return false;
					}
					releasable->Base.End = Prev(*current, true, true, true);
				}
				// [{...}]
				if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACES))
				{
					releasable->isOpaque = false;
					List *start{ current->Next };
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
						return false;
					}
					while (current)
					{
						if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACE_ENDS))
							break;
						if (!ParseEnumerator(entity, *start, start))
							return false;
						if (!start)
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
							return false;
						}
						if (!(current = Skip(*start, false)))
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
							return false;
						}
					}
					if (!in(current->Item->Op->Name, BRACE_ENDS))
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"}", TokenToString(*current->Item));
						return false;
					}
					current = Next(*current, true, true, true);
				}
				out = current;
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParseEnumerator(PEntity &parent, List &list, PList &out)
			{
				static const StringArray SCOPES{ L"class", L"struct" };

				ReleasablePtr<CEnumerator> releasable{ new CEnumerator() };
				CEntity *entity{ releasable };
				List *current, *identifier;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				// identifier
				if (!current)
				{
					E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					return false;
				}
				releasable->Name = current->Item->Value;
				identifier = current;
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
					return false;
				}
				// [attr]
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// [= expression]
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"=")
				{
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"=");
						return false;
					}
					releasable->Value.Begin = current;
					if (!(current = FindCloseBraceOrComma(*current, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
						return false;
					}
					if (current == releasable->Value.Begin)
					{
						E_ExpectedExpression(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
						return false;
					}
					releasable->Value.End = Prev(*current, true, true, true);
				}
				// , or }
				if (current->Item->Type != TokenType::Operator)
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L",' or '}", TokenToString(*current->Item));
					return false;
				}
				if (current->Item->Op->Name == L",")
				{
					if ((out = current->Next))
						ParseTrailingComments(entity, *out, out);
				}
				else if (in(current->Item->Op->Name, BRACE_ENDS))
				{
					out = current;
					if (releasable->Value.Begin)
						ParseTrailingComments(entity, *releasable->Value.End->Next, current);
					else
						ParseTrailingComments(entity, *identifier->Next, current);
				}
				else
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"}", TokenToString(*current->Item));
					return false;
				}
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseClass(PEntity &target, List &list, PList &out)
			{
				static const StringArray SPECIFIERS{ L"final", L"trivially_relocatable_if_eligible", L"replaceable_if_eligible" };

				ReleasablePtr<CClass> releasable{ new CClass() };
				CEntity *entity{ releasable };
				List *current{ &list };
				// class|struct|union
				if (current->Item->Value == L"struct")
					releasable->ClassType = CClass::ClassType::Struct;
				else if (current->Item->Value == L"union")
					releasable->ClassType = CClass::ClassType::Union;
				// [attr]
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, list.Item->Value);
					return false;
				}
				while (current)
				{
					if (!isAttributeList(*current))
						break;
					if (!ParseAttributeList(entity, *current, true, current))
						return false;
					if (!current)
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
					if (!(current = Skip(*current, false)))
					{
						E_UnexpectedEndAfterAttributeList(__FUNCTION__, __LINE__, list);
						return false;
					}
				}
				// [name]
				if ((current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"::") || current->Item->Type == TokenType::Identifier)
				{
					if (!ParseIdentifier(*current, releasable->Identifier, true, true, false, false, false, current))
						return false;
				}
				// [specifiers]
				while (current && current->Item->Type == TokenType::Identifier && in(current->Item->Value, SPECIFIERS))
				{
					if (current->Item->Value == L"final")
					{
						if (releasable->isFinal)
						{
							E_DuplicateFinal(__FUNCTION__, __LINE__, *current);
							return false;
						}
						releasable->isFinal = true;
					}
					else if (current->Item->Value == L"trivially_relocatable_if_eligible")
					{
						if (releasable->isTriviallyRelocatableIfEligible)
						{
							E_DuplicateTriviallyRelocatable(__FUNCTION__, __LINE__, *current);
							return false;
						}
						releasable->isTriviallyRelocatableIfEligible = true;
					}
					else
					{
						if (releasable->isReplaceableIfEligible)
						{
							E_DuplicateReplaceable(__FUNCTION__, __LINE__, *current);
							return false;
						}
						releasable->isReplaceableIfEligible = true;
					}
					current = Next(*current, true, true, true);
				}
				// [:base]
				if (current && current->Item->Type == TokenType::Operator && current->Item->Op->Name == L":")
				{
					if (releasable->ClassType == CClass::ClassType::Union) // union can not have base
					{
						E_UnionWithBaseClass(__FUNCTION__, __LINE__, *current);
						return false;
					}
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L":");
						return false;
					}
					while (current)
					{
						CClassBase *class_base;
						ReleasablePtr<CClassBase> base{ class_base = new CClassBase() };
						if (!ParseClassBase(*class_base, *current, current))
							return false;
						releasable->Bases.push_back(base.move());
						if (current->Item->Op->Name == L",")
						{
							current = Next(*current, true, true, true);
							continue;
						}
						break;
					}
				}
				// [{...}]
				if (current && current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACES))
				{
					releasable->isForward = false;
					if (!(current = current->Next))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"{");
						return false;
					}
					if (!ParseList(entity, *current, true, true, current))
						return false;
					current = Next(*current, true, true, true);
				}
				out = current;
				target = releasable.move();
				return true;
			}

			bool CDecoder::ParsePublic(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CPublic> releasable{ new CPublic() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				// public
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"public");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"public")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"public", TokenToString(*current->Item));
					return false;
				}
				// :
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L":");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L":")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L":", TokenToString(*current->Item));
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseProtected(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CProtected> releasable{ new CProtected() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				// protected
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"protected");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"protected")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"protected", TokenToString(*current->Item));
					return false;
				}
				// :
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L":");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L":")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L":", TokenToString(*current->Item));
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParsePrivate(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CPrivate> releasable{ new CPrivate() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				// private
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"private");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"private")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"private", TokenToString(*current->Item));
					return false;
				}
				// :
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L":");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L":")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L":", TokenToString(*current->Item));
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseSimpleDeclaration(PEntity &parent, List &list, const bool require_declarators, const bool allow_bitfields, bool &has_body, PList &out)
			{
				static const StringArray ENDS{ L",", L")" };

				ReleasablePtr<CSimpleDeclaration> releasable{ new CSimpleDeclaration() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				if (!current)
					return false;
				// [specifiers]
				if (!ParseTypeSpecifierSeq(entity, releasable->Specifiers, *current, false, current))
					return false;
				if (!current)
				{
					E_UnexpectedEndExpectedDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				// [declarators]
				has_body = false;
				CEntity *declarator;
				while (current)
				{
					if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L";")
						break;
					if (!require_declarators && current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, ENDS))
					{
						if (releasable->Specifiers.empty() || !releasable->Declarators.empty())
						{
							E_ExpectedDeclarator(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
							return false;
						}
						break;
					}
					List *p{ current };
					if (!ParseDeclarator(declarator, *current, false, allow_bitfields, has_body, current))
						return false;
					if (!declarator)
					{
						E_ExpectedDeclarator(__FUNCTION__, __LINE__, *p, TokenToString(*p->Item));
						return false;
					}
					releasable->Declarators.push_back(declarator);
					if (has_body)
						break;
					if (!current)
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L",' or ';");
						return false;
					}
					if (current->Item->Type != TokenType::Operator)
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L",' or ';", TokenToString(*current->Item));
						return false;
					}
					if (current->Item->Op->Name == L",")
					{
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L",");
							return false;
						}
						continue;
					}
					if (current->Item->Op->Name != L";")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
						return false;
					}
					break;
				}
				if (!current && !has_body)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
					return false;
				}
				if ((out = (has_body || !require_declarators) ? current : current->Next))
				{
					if (require_declarators)
						ParseTrailingComments(entity, *out, out);
				}
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseDeclarator(PEntity &target, List &list, const bool is_parameter, const bool allow_bitfield, bool &has_body, PList &out)
			{
				static const StringArray PARAMETER_ENDS{ L"=", L",", L")", L";"};
				static const StringArray IDENTIFIER_OPERATORS{ L"::", L"~", L"..."};

				has_body = false;
				if (is_parameter && isParameterPack(list))
					return ParseParameterPack(target, list, out);

				CBaseDeclarator *declarator;

				// Function parameters can have no declarator (but it can have initialization after "="). "friend" can have none either
				if (list.Item->Type == TokenType::Operator && in(list.Item->Op->Name, PARAMETER_ENDS))
				{
					if (list.Item->Op->Name == L"=")
					{
						declarator = new CIdDeclarator();
						if (!ParseInitialization(declarator, list, is_parameter, out))
						{
							declarator->Release();
							return false;
						}
						target = declarator;
					}
					else
					{
						out = &list;
						target = nullptr;
					}
					return true;
				}

				CIdentifier *identifier{ nullptr };
				List *current{ &list };
				bool function_array_allowed{ true };
				if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"*")
				{
					if (!ParsePtrDeclarator(declarator, *current, is_parameter, allow_bitfield, has_body, current))
						return false;
					if (declarator->Declarator && declarator->Declarator->Type == EntityType::IdDeclarator)
						identifier = &cast<CIdDeclarator *>(declarator->Declarator)->Identifier;
				}
				else if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"&")
				{
					if (!ParseLValueDeclarator(declarator, *current, is_parameter, allow_bitfield, has_body, current))
						return false;
					if (declarator->Declarator && declarator->Declarator->Type == EntityType::IdDeclarator)
						identifier = &cast<CIdDeclarator *>(declarator->Declarator)->Identifier;
				}
				else if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"&&")
				{
					if (!ParseRValueDeclarator(declarator, *current, is_parameter, allow_bitfield, has_body, current))
						return false;
					if (declarator->Declarator && declarator->Declarator->Type == EntityType::IdDeclarator)
						identifier = &cast<CIdDeclarator *>(declarator->Declarator)->Identifier;
				}
				else if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"(")
				{
					if (!ParseNoPtrDeclarator(declarator, *current, allow_bitfield, has_body, current))
						return false;
				}
				else if (current->Item->Type == TokenType::Identifier || (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, IDENTIFIER_OPERATORS)))
				{
					if (!ParseIdDeclarator(declarator, *current, is_parameter, allow_bitfield, has_body, current))
						return false;
					identifier = &cast<CIdDeclarator*>(declarator)->Identifier;
				}
				else if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACKETS))
				{
					out = current;
					target = nullptr;
					return true;
				}
				else if (allow_bitfield && current->Item->Type == TokenType::Operator && current->Item->Op->Name == L":")
					declarator = new CIdDeclarator();
				else if (current->Item->Type == TokenType::Operator && (current->Item->Op->Name == L"(" || current->Item->Op->Name == L"=" || in(current->Item->Op->Name, BRACES)))
				{
					function_array_allowed = false;
					declarator = new CIdDeclarator();
				}
				else
				{
					E_InvalidDeclarator(__FUNCTION__, __LINE__, list);
					return false;
				}
				bool has_any_body{ false };
				if (function_array_allowed && current && current->Item->Type == TokenType::Operator)
				{
					if (in(current->Item->Op->Name, BRACKETS)) // array
					{
						while (current && current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, BRACKETS))
						{
							CBaseDeclarator *array_declarator;
							if (!ParseArray(array_declarator, *current, current))
							{
								declarator->Release();
								return false;
							}
							array_declarator->Declarator = declarator;
							declarator = array_declarator;
						}
						if (!current)
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
							return false;
						}
					}
					else if (current->Item->Op->Name == L"(" && isFunction(identifier, *current)) // function
					{
						CBaseDeclarator *function_declarator;
						bool parameters_valid;
						if (ParseFunction(function_declarator, *current, parameters_valid, current))
						{
							function_declarator->Declarator = declarator;
							declarator = function_declarator;
							CFunction *function{ cast<CFunction *>(function_declarator) };
							has_body = function->Body.Begin != nullptr;
							has_any_body = has_body || function->Abstract || function->Default || function->Deleted;
						}
						else if (parameters_valid)
						{
							declarator->Release();
							return false;
						}
						// If parsing of function failed because of function parameter parsing failed, it means it was not a function but "(...)" initialization and it will be handled later
					}
				}
				// [bitfield]
				if (current && allow_bitfield && !has_any_body && current->Item->Type == TokenType::Operator && current->Item->Op->Name == L":" && !ParseBitfield(declarator, *current, current))
				{
					declarator->Release();
					return false;
				}
				
				// [initialization]
				if (current && !has_any_body && !ParseInitialization(declarator, *current, function_array_allowed ? is_parameter : false, current))
				{
					declarator->Release();
					return false;
				}
				out = current;
				target = declarator;
				return true;
			}

			bool CDecoder::ParseDeclaration(PEntity &parent, List &list, const bool allow_bitfield, PList &out)
			{
				List *current{ &list }, *start;
				// Parse and add standalone comments
				while (current)
				{
					if (isNewLines(*current))
					{
						current = current->Next;
						continue;
					}
					if (!(start = FindEntity(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, *current, L"entity");
						return false;
					}
					if (isSLComment(*start))
					{
						ParseSLComment(parent, *start, current);
						continue;
					}
					if (isMLComment(*start))
					{
						ParseMLComment(parent, *start, current);
						continue;
					}
					break;
				}
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"entity");
					return false;
				}

				// Declarations
				if (isStaticAssert(*start))
					return ParseStaticAssert(parent, *current, out);
				if (isEmpty(*start))
					return ParseEmpty(parent, *current, out);
				if (isBlock(*start))
					return ParseBlock(parent, *current, out);
				if (isLanguageLinkage(*start))
					return ParseLanguageLinkage(parent, *current, out);
				if (isAsm(*start))
					return ParseAsm(parent, *current, out);
				if (isNamespaceAlias(*start))
					return ParseNamespaceAlias(parent, *current, out);
				if (isNamespace(*start))
					return ParseNamespace(parent, *current, out);
				if (isUsingNamespace(*start))
					return ParseUsingNamespace(parent, *current, out);
				if (isUsingEnum(*start))
					return ParseUsingEnum(parent, *current, out);
				if (isTypeAlias(*start))
					return ParseTypeAlias(parent, *current, out);
				if (isUsing(*start))
					return ParseUsing(parent, *current, out);
				if (isTemplate(*start))
					return ParseTemplate(parent, *current, out);
				if (isStructuredBinding(*start))
					return ParseStructuredBinding(parent, *current, out);
				if (isFriend(*start))
					return ParseFriend(parent, *current, out);

				if (parent->Type == EntityType::Class)
				{
					if (isPublic(*start))
						return ParsePublic(parent, *current, out);
					if (isProtected(*start))
						return ParseProtected(parent, *current, out);
					if (isPrivate(*start))
						return ParsePrivate(parent, *current, out);
				}

				bool dummy;
				return ParseSimpleDeclaration(parent, *current, true, allow_bitfield, dummy, out);
			}

			bool CDecoder::ParseStructuredBinding(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CStructuredBinding> releasable{ new CStructuredBinding() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				// decl-specifier-seq
				bool has_auto{ false };
				while (current)
				{
					if (current->Item->Type != TokenType::Identifier)
						break;
					if (current->Item->Value == L"constexpr")
					{
						releasable->Specifiers.push_back(new CConstexpr());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"constinit")
					{
						releasable->Specifiers.push_back(new CConstinit());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"static")
					{
						releasable->Specifiers.push_back(new CStatic());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"thread_local")
					{
						releasable->Specifiers.push_back(new CThreadLocal());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"const")
					{
						releasable->Specifiers.push_back(new CConst());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"volatile")
					{
						releasable->Specifiers.push_back(new CVolatile());
						current = Next(*current, true, true, true);
						continue;
					}
					if (current->Item->Value == L"auto")
					{
						if (has_auto)
						{
							E_DuplicateAuto(__FUNCTION__, __LINE__, *current);
							return false;
						}
						has_auto = true;
						releasable->Specifiers.push_back(new CAuto());
						current = Next(*current, true, true, true);
						continue;
					}
					break;
				}
				if (!has_auto)
				{
					E_ExpectedAuto(__FUNCTION__, __LINE__, list);
					return false;
				}
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"[");
					return false;
				}
				// [ref-qualifier]
				if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, REFS))
				{
					if (current->Item->Op->Name == L"&")
						releasable->Specifiers.push_back(new CLRef());
					else
						releasable->Specifiers.push_back(new CRRef());
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"[");
						return false;
					}
				}
				// [ sb-identifier-list ]
				if (current->Item->Type != TokenType::Operator || !in(current->Item->Op->Name, BRACKETS))
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"[", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
					return false;
				}
				while (current)
				{
					if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L"...")
					{
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"...");
							return false;
						}
						if (current->Item->Type != TokenType::Identifier)
						{
							E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
							return false;
						}
						releasable->Identifiers.push_back(CStructuredBinding::Identifier{ true, current->Item->Value });
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"]");
							return false;
						}
						while (current && isAttributeList(*current))
						{
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEndExpectedAttributeList(__FUNCTION__, __LINE__, list);
								return false;
							}
							if (!(current = FindAttributeListEnd(*current)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"attribute list end");
								return false;
							}
							if (!(current = Next(*current, true, true, true)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"]");
								return false;
							}
						}
						if (!current)
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"]");
							return false;
						}
						if (current->Item->Type != TokenType::Operator)
						{
							E_ExpectedToken(__FUNCTION__, __LINE__, *current, L",' or ']", TokenToString(*current->Item));
							return false;
						}
						if (current->Item->Op->Name == L",")
						{
							current = Next(*current, true, true, true);
							continue;
						}
						if (!in(current->Item->Op->Name, BRACKET_ENDS))
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"]");
							return false;
						}
						break;
					}
					if (current->Item->Type != TokenType::Identifier)
					{
						E_ExpectedIdentifier(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
						return false;
					}
					releasable->Identifiers.push_back(CStructuredBinding::Identifier{ false, current->Item->Value });
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"]");
						return false;
					}
					while (current && isAttributeList(*current))
					{
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEndExpectedAttributeList(__FUNCTION__, __LINE__, list);
							return false;
						}
						if (!(current = FindAttributeListEnd(*current)))
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"attribute list end");
							return false;
						}
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"]");
							return false;
						}
					}
					if (!current)
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"]");
						return false;
					}
					if (current->Item->Type != TokenType::Operator)
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L",' or ']", TokenToString(*current->Item));
						return false;
					}
					if (current->Item->Op->Name == L",")
					{
						current = Next(*current, true, true, true);
						continue;
					}
					if (!in(current->Item->Op->Name, BRACKET_ENDS))
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"]", TokenToString(*current->Item));
						return false;
					}
					break;
				}
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"]");
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"]");
					return false;
				}
				// initializer
				if (current->Item->Type != TokenType::Operator)
				{
					E_ExpectedInitialization(__FUNCTION__, __LINE__, *current, TokenToString(*current->Item));
					return false;
				}
				if (current->Item->Op->Name == L"=")
				{
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"=");
						return false;
					}
					releasable->Initialization.Begin = current;
					if (!(current = FindSemicolon(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
						return false;
					}
					if (current == releasable->Initialization.Begin)
					{
						E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
						return false;
					}
					releasable->Initialization.End = Prev(*current, true, true, true);
				}
				else if (current->Item->Op->Name == L"(")
				{
					releasable->InitializationType = CStructuredBinding::InitializationType::Parentheses;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"(");
						return false;
					}
					releasable->Initialization.Begin = current;
					if (!(current = FindCloseParenthese(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
						return false;
					}
					if (current == releasable->Initialization.Begin)
					{
						E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
						return false;
					}
					releasable->Initialization.End = Prev(*current, true, true, true);
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
						return false;
					}
				}
				else if (in(current->Item->Op->Name, BRACES))
				{
					releasable->InitializationType = CStructuredBinding::InitializationType::Braces;
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"{");
						return false;
					}
					releasable->Initialization.Begin = current;
					if (!(current = FindCloseBrace(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"}");
						return false;
					}
					if (current == releasable->Initialization.Begin)
					{
						E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
						return false;
					}
					releasable->Initialization.End = Prev(*current, true, true, true);
					if (!(current = Next(*current, true, true, true)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
						return false;
					}
				}
				else
					return false;
				// ;
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L";")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseStaticAssert(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CStaticAssert> releasable{ new CStaticAssert() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				// static_assert
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"static_assert");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"static_assert")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"static_assert", TokenToString(*current->Item));
					return false;
				}
				// (...)
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"(");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"(", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndExpectedArgument(__FUNCTION__, __LINE__, list);
					return false;
				}
				releasable->Body.Begin = current;
				if (!(current = FindCloseParenthese(*current)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L")");
					return false;
				}
				if (current == releasable->Body.Begin)
				{
					E_ExpectedArgument(__FUNCTION__, __LINE__, *current, L")");
					return false;
				}
				releasable->Body.End = Prev(*current, true, true, true);
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L";")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
					return false;
				}
				if ((out = current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}

			bool CDecoder::ParseFriend(PEntity &parent, List &list, PList &out)
			{
				ReleasablePtr<CFriend> releasable{ new CFriend() };
				CEntity *entity{ releasable };
				List *current;
				if (!ParseCommentsAndAttributes(entity, list, current))
					return false;
				// friend
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L"friend");
					return false;
				}
				if (current->Item->Type != TokenType::Identifier || current->Item->Value != L"friend")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, *current, L"friend", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, true)))
				{
					E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L"friend");
					return false;
				}
				// declarations
				bool has_body{ false };
				while (current)
				{
					if (!ParseSimpleDeclaration(entity, *current, false, false, has_body, current))
						return false;
					if (has_body)
						break;
					if (!current)
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, list, L";");
						return false;
					}
					if (current->Item->Type != TokenType::Operator)
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L",' or ';", TokenToString(*current->Item));
						return false;
					}
					if (current->Item->Op->Name == L",")
					{
						if (!(current = Next(*current, true, true, true)))
						{
							E_UnexpectedEndAfterToken(__FUNCTION__, __LINE__, list, L",");
							return false;
						}
						continue;
					}
					if (current->Item->Op->Name != L";")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, *current, L";", TokenToString(*current->Item));
						return false;
					}
					break;
				}
				if ((out = has_body ? current : current->Next))
					ParseTrailingComments(entity, *out, out);
				parent->Entities.push_back(releasable.move());
				return true;
			}
		#pragma endregion

		#pragma region Errors
			void CDecoder::E_UnexpectedEnd(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_ExpectedArgument(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_ARGUMENT,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_UnexpectedEndExpectedArgument(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_EXPECTED_ARGUMENT,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_InvalidIdentifier(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_INVALID_IDENTIFIER,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_InvalidIdentifierDoubleDestructor(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_INVALID_IDENTIFIER_DOUBLE_DESTRUCTOR,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_UnexpectedEndExpectedIdentifier(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_EXPECTED_IDENTIFIER,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_ExpectedIdentifier(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_IDENTIFIER,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_ExpectedToken(const AnsiString &function, int line, List &list, const String &name, const String &found)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_TOKEN,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{token}", name, L"{name}", found)
					);
				}
			}

			void CDecoder::E_InvalidPartitionName(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_INVALID_PARTITION_NAME,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_UnexpectedEndAfterAttributeList(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_AFTER_ATTRIBUTE_LIST,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_DuplicateProtected(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_DUPLICATE_PROTECTED,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_DuplicatePrivate(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_DUPLICATE_PRIVATE,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_DuplicatePublic(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_DUPLICATE_PUBLIC,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_DuplicateVirtual(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_DUPLICATE_VIRTUAL,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_UnexpectedEndExpectedBaseClass(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_EXPECTED_BASE_CLASS,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_ExpectedSpecifier(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_SPECIFIER,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_UnexpectedEndExpectedDeclarator(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_EXPECTED_DECLARATOR,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_ExpectedDeclarator(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_DECLARATOR,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_UnexpectedEndAfterToken(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_AFTER_TOKEN,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_UnexpectedEndAfterArray(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_AFTER_ARRAY,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_UnexpectedEndAfterDeclarator(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_AFTER_DECLARATOR,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_UnexpectedFunctionDefinition(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_FUNCTION_DEFINITION,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_UnexpectedEndAfterParameters(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_AFTER_PARAMETERS,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_ExpectedTrailing(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_TRAILING,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_ExpectedString(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_STRING,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_UnexpectedEndAfterMemberInitialization(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_AFTER_MEMBER_INITIALIZATION,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_BitfieldRequireIdDeclarator(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_BITFIELD_REQUIRE_ID_DECLARATOR,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_ExportPrivateModule(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPORT_PRIVATE_MODULE,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_ExportModuleWithoutName(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPORT_MODULE_WITHOUT_NAME,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_UnexpectedEndAfterModuleName(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_AFTER_MODULE_NAME,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_UnexpectedEndAfterPartitionName(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_AFTER_PARTITION_NAME,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_ExpectedAnsi(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_ANSI,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_UnexpectedEndAfterString(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_AFTER_STRING,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_InlineNotAllowed(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_INLINE_NOT_ALLOWED_HERE,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_ExpectedTypeId(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_TYPE_ID,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_ExpectedExpression(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_EXPRESSION,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}

			void CDecoder::E_DuplicateFinal(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_DUPLICATE_FINAL,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_DuplicateTriviallyRelocatable(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_DUPLICATE_TRIVIALLY_RELOCATABLE,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_DuplicateReplaceable(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_DUPLICATE_REPLACEABLE,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_UnionWithBaseClass(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNION_WITH_BASE_CLASS,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_InvalidDeclarator(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_INVALID_DECLARATOR,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_DuplicateAuto(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_DUPLICATE_AUTO,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_ExpectedAuto(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_AUTO,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_UnexpectedEndExpectedAttributeList(const AnsiString &function, int line, List &list)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_UNEXPECTED_END_EXPECTED_ATTRIBUTE_LIST,
						E(L"{index}", ToString((uint64)list.Item.Index))
					);
				}
			}

			void CDecoder::E_ExpectedInitialization(const AnsiString &function, int line, List &list, const String &name)
			{
				if (m_pErrorListener)
				{
					Dump(cast<IErrorListenerEx *>(m_pErrorListener), list);
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_EXPECTED_INITIALIZATION,
						E(L"{index}", ToString((uint64)list.Item.Index), L"{name}", name)
					);
				}
			}
		#pragma endregion

		#pragma region Decode
			bool CDecoder::Decode(const String &source)
			{
				// Cleanup
				Clear();

				// Tokenize
				Tokenize(m_cTokenizer, source, m_aTokens);
				if (m_aTokens.empty())
				{
					m_pRoot = new CRoot();
					return true;
				}

				// Preprocessing
				if (!m_cPreProcessor.Process(m_aTokens, m_pList))
					return false;
				if (m_cPreProcessor.Aborted)
				{
					m_bAborted = true;
					return true;
				}
				if (!m_pList)
				{
					m_pRoot = new CRoot();
					return true;
				}

				// Parsing
				List *out;
				m_pRoot = new CRoot();
				if (!ParseList(m_pRoot, *m_pList, false, false, out))
					return false;

				return true;
			}
		#pragma endregion

		#pragma region Setters
			bool CDecoder::setVersion(const enum Version value)
			{
				if (value != m_eVersion)
				{
					m_eVersion = value;
					return true;
				}
				return false;
			}
		#pragma endregion
		}
	}
}