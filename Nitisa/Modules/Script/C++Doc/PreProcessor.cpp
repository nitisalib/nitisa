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
			const StringArray CPreProcessor::PP_HASH{ L"#", L"%:" };
			const StringArray CPreProcessor::PP_2HASH{ L"##", L"%:%:" };

		#pragma region Constructor & destructor
			CPreProcessor::CPreProcessor(cpp::CTokenizer &tokenizer, std::vector<Token*> &tokens, IErrorListener *error_listener, IProgressListener *progress_listener) :
				m_cTokenizer{ tokenizer },
				m_aTokens{ tokens },
				m_pErrorListener{ error_listener },
				m_pProgressListener{ progress_listener },
				m_bAborted{ false }
			{
				
			}

			CPreProcessor::~CPreProcessor()
			{
				ClearDefinitions();
				ClearStoredDefinitions();
			}
		#pragma endregion

		#pragma region Definitions
			bool CPreProcessor::AddDefinition(CDefinition *definition, List *begin, const size_t &name_token_index, bool &is_copy)
			{
				if (!begin)
					definition->m_eType = DefinitionType::Define;
				else if (begin->Item->Type == TokenType::Operator && begin->Item->Op->Name == L"(")
					definition->m_eType = DefinitionType::Function;
				else
					definition->m_eType = DefinitionType::Expression;
				CDefinition *copy{ FindDefinition(definition->Name, EmptyStringArray) };
				if (copy)
				{
					if (*definition == *copy)
					{
						is_copy = true;
						return true;
					}
					E_DefinitionExists(__FUNCTION__, __LINE__, name_token_index, definition->Name);
					return false;
				}
				// Build parameter list for function definition
				if (definition->Type == DefinitionType::Function)
				{
					bool is_parameter{ true };
					List *lst{ Next(*begin, true, true, false, false) }, *last{ begin }; // current == "("
					while (lst)
					{
						last = lst;
						if (lst->Item->Type == TokenType::Operator && lst->Item->Op->Name == L")")
						{
							definition->Body = Next(*lst, true, true, false, false);
							if (definition->Body && (isNewLines(*definition->Body) || isSLComment(*definition->Body)))
								definition->Body = nullptr;
							break;
						}
						if (is_parameter)
						{
							if (definition->Variadic)
							{
								E_DuplicateVariadic(__FUNCTION__, __LINE__, lst->Item->Index);
								return false;
							}
							if (lst->Item->Type == TokenType::Operator && lst->Item->Op->Name == L"...")
							{
								definition->Variadic = true;
								is_parameter = false;
								lst = Next(*lst, true, true, false, false);
								continue;
							}
							if (lst->Item->Type == TokenType::Identifier)
							{
								
								definition->Parameters.push_back(lst->Item->Value);
								is_parameter = false;
								lst = Next(*lst, true, true, false, false);
								continue;
							}
							E_ExpectedParameter(__FUNCTION__, __LINE__, lst->Item->Index);
							return false;
						}
						if (lst->Item->Type != TokenType::Operator || lst->Item->Op->Name != L",")
						{
							E_ExpectedComma(__FUNCTION__, __LINE__, lst->Item->Index, TokenToString(*lst->Item));
							return false;
						}
						lst = Next(*lst, true, true, false, false);
						is_parameter = true;
					}
					if (!lst) // Should be ")"
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, last->Item->Index, L")");
						return false;
					}
					if (is_parameter && (definition->Variadic || !definition->Parameters.empty())) // Should be parameter after ","
					{
						E_ExpectedParameter(__FUNCTION__, __LINE__, lst->Item->Index);
						return false;
					}
				}
				definition->Begin = begin;
				m_aDefinitions[definition->Name] = definition;
				is_copy = false;
				return true;
			}

			bool CPreProcessor::AddDefinition(const String &source)
			{
				CDefinition *definition{ new CDefinition() };
				Tokenize(m_cTokenizer, source, definition->m_aTokens);
				size_t index{ 0 }, token_index;

				// Check for "#" or "%:"
				while (index < definition->m_aTokens.size() && ShouldSkip(definition->m_aTokens[index]))
					index++;
				if (index == definition->m_aTokens.size() || definition->m_aTokens[index].Type != TokenType::Operator || !in(definition->m_aTokens[index].Op->Name, PP_HASH))
				{
					E_ExpectedHash(__FUNCTION__, __LINE__, 0);
					definition->Release();
					return false;
				}
				token_index = definition->m_aTokens[index].Index;
				index++;
				// Check for "define"
				while (index < definition->m_aTokens.size() && ShouldSkip(definition->m_aTokens[index]))
					index++;
				if (index == definition->m_aTokens.size() || definition->m_aTokens[index].Type != TokenType::Identifier || definition->m_aTokens[index].Value != L"define")
				{
					E_ExpectedDefineAfterHash(__FUNCTION__, __LINE__, token_index);
					definition->Release();
					return false;
				}
				token_index = definition->m_aTokens[index].Index;
				index++;
				// Check for name
				while (index < definition->m_aTokens.size() && ShouldSkip(definition->m_aTokens[index]))
					index++;
				if (index == definition->m_aTokens.size() || definition->m_aTokens[index].Type != TokenType::Identifier)
				{
					E_ExpectedIdentifierAfterDefine(__FUNCTION__, __LINE__, token_index);
					definition->Release();
					return false;
				}
				token_index = definition->m_aTokens[index].Index;
				definition->m_sName = definition->m_aTokens[index].Value;
				index++;

				// Skip spaces and comments
				while (index < definition->m_aTokens.size() && ShouldSkip(definition->m_aTokens[index]))
					index++;
				definition->m_aTokens.erase(definition->m_aTokens.begin(), definition->m_aTokens.begin() + index);
				List *list{ MakeList(definition->m_aTokens, nullptr) };
				bool is_copy;
				if (!AddDefinition(definition, list, token_index, is_copy))
				{
					definition->Release();
					Free(list);
					return false;
				}
				if (is_copy)
				{
					definition->Release();
					Free(list);
				}
				return true;
			}

			CDefinition *CPreProcessor::FindDefinition(const String &name, const StringArray &exclude)
			{
				if (in(name, exclude))
					return nullptr;
				auto pos{ m_aDefinitions.find(name) };
				if (pos != m_aDefinitions.end())
					return pos->second;
				return nullptr;
			}

			bool CPreProcessor::DeleteDefinition(const String &name)
			{
				auto pos{ m_aDefinitions.find(name) };
				if (pos != m_aDefinitions.end())
				{
					pos->second->Release();
					m_aDefinitions.erase(pos);
					return true;
				}
				return false;
			}

			void CPreProcessor::ClearDefinitions()
			{
				for (auto pos : m_aDefinitions)
					pos.second->Release();
				m_aDefinitions.clear();
			}

			void CPreProcessor::ClearStoredDefinitions()
			{
				for (auto pos : m_aStoredDefinitions)
					pos->Release();
				m_aStoredDefinitions.clear();
			}

			CDefinition *CPreProcessor::PopStoredDefinition(const String &name)
			{
				if (!m_aStoredDefinitions.empty())
				{
					int i{ (int)m_aStoredDefinitions.size() - 1 };
					while (i >= 0)
					{
						if (m_aStoredDefinitions[i]->Name == name)
						{
							CDefinition *result{ m_aStoredDefinitions[i] };
							m_aStoredDefinitions.erase(m_aStoredDefinitions.begin() + i);
							return result;
						}
						i--;
					}
				}
				return nullptr;
			}
		#pragma endregion

		#pragma region Includes
			bool CPreProcessor::AddIncludePath(const String &path)
			{
				if (!path.empty())
				{
					if (Application && path[path.length() - 1] != Application->System->DirectorySeparator)
						m_aIncludePathes.push_back(path + Application->System->DirectorySeparator);
					else
						m_aIncludePathes.push_back(path);
					return true;
				}
				return false;
			}

			bool CPreProcessor::AddHasInclude(const String &filename)
			{
				if (!filename.empty())
				{
					m_aHasIncludes.push_back(filename);
					return true;
				}
				return false;
			}

			bool CPreProcessor::hasInclude(const String &filename)
			{
				for (auto const &fn : m_aHasIncludes)
					if (fn == filename)
						return true;
				if (Application)
				{
					for (auto const &path : m_aIncludePathes)
						if (Application->FileSystem->FileExists(path + filename))
							return true;
				}
				return false;
			}

			void CPreProcessor::ClearIncludes()
			{
				m_aIncludePathes.clear();
				m_aHasIncludes.clear();
			}
		#pragma endregion

		#pragma region Attributes
			bool CPreProcessor::AddHasAttribute(const String &attribute)
			{
				if (!attribute.empty())
				{
					m_aHasAttributes.push_back(attribute);
					return true;
				}
				return false;
			}

			bool CPreProcessor::hasAttribute(const String &attribute)
			{
				for (auto const &attr : m_aHasAttributes)
					if (attr == attribute)
						return true;
				return false;
			}

			void CPreProcessor::ClearAttributes()
			{
				m_aHasAttributes.clear();
			}
		#pragma endregion

		#pragma region Helpers
			size_t CPreProcessor::FindArgumentIndex(const String &name, const StringArray &parameters) const
			{
				for (size_t i = 0; i < parameters.size(); i++)
					if (parameters[i] == name)
						return i;
				return npos;
			}

			bool CPreProcessor::ShouldSkip(const Token &token) const
			{
				if (token.Type == TokenType::Group && token.Op->Group == GROUP_SPACE)
					return true;
				if (token.Type == TokenType::Operator && token.Op->Group == GROUP_SPACE)
					return true;
				if (token.Type == TokenType::String && token.Op->Name == L"/*")
					return true;
				return false;
			}

			void CPreProcessor::DeleteUnusedTokens(PList &head)
			{
				List *list{ head }, *next;
				while (list)
				{
					// Preserve all tokens after "import" directive if it indicates header import in form "import <filename>"
					if (list->Item->Type == TokenType::Identifier && list->Item->Value == L"import" && (next = list->Next) && next->Item->Type == TokenType::Operator && next->Item->Op->Name == L">")
					{
						list = next->Next;
						while (list && list->Item->Type != TokenType::Operator && list->Item->Op->Name != L">")
							list = list->Next;
						continue;
					}
					if (isSpaces(*list))
					{
						list = Delete(head, list);
						continue;
					}
					if (isNewLines(*list) && list->Prev && isNewLines(*list->Prev))
					{
						if (list->Prev->Item->Type == TokenType::Operator)
						{
							list->Prev->Item->Type = TokenType::Group;
							list->Prev->Item->Count = 1;
						}
						list->Prev->Item->Count += (list->Item->Type == TokenType::Group) ? list->Item->Count : 1;
						list = Delete(head, list);
						continue;
					}
					list = list->Next;
				}
				while (head && isNewLines(*head))
					Delete(head, head);
				List *tail{ Tail(head) };
				while (tail && isNewLines(*tail))
				{
					list = tail->Prev;
					Delete(tail);
					tail = list;
				}
			}
		#pragma endregion

		#pragma region Error helpers
			void CPreProcessor::E_DefinitionExists(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_DEFINITION_EXISTS,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_DuplicateVariadic(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_DUPLICATE_VARIADIC,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_ExpectedParameter(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_PARAMETER,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_ExpectedComma(const AnsiString &function, int line, const size_t &index, const String &token)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_GENERAL_EXPECTED_COMMA,
						E(L"{index}", ToString((uint64)index), L"{token}", token)
					);
				}
			}

			void CPreProcessor::E_UnexpectedEnd(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_UNEXPECTED_END,
						E(L"{index}", ToString((uint64)index), L"{name}", L")")
					);
				}
			}

			void CPreProcessor::E_ExpectedHash(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_HASH,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_ExpectedDefineAfterHash(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_DEFINE_AFTER_HASH,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_ExpectedIdentifierAfterDefine(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_IDENTIFIER_AFTER_DEFINE,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_UnexpectedEndExpectedIdentifier(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_UNEXPECTED_END_EXPECTED_IDENTIFIER,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_ExpectedIdentifier(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_IDENTIFIER,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_UnknownDirective(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_UNKNOWN_DIRECTIVE,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_UnexpectedEndExpectedExpression(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_UNEXPECTED_END_EXPECTED_EXPRESSION,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_UnfinishedBranch(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_UNFINISHED_BRANCH,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_ExpectedToken(const AnsiString &function, int line, const size_t &index, const String &expected, const String &found)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_TOKEN,
						E(L"{index}", ToString((uint64)index), L"{token}", expected, L"{name}", found)
					);
				}
			}

			void CPreProcessor::E_ExpectedAnsiString(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_ANSI_STRING,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_UnexpectedToken(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_UNEXPECTED_TOKEN,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_TooFewArguments(const AnsiString &function, int line, const size_t &index, const size_t &count, const size_t &expected)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_TOO_FEW_ARGUMENTS,
						E(L"{index}", ToString((uint64)index), L"{count}", ToString((uint64)count), L"{expected}", ToString((uint64)expected))
					);
				}
			}

			void CPreProcessor::E_InvalidArgumentCount(const AnsiString &function, int line, const size_t &index, const size_t &count, const size_t &expected)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_INVALID_ARGUMENT_COUNT,
						E(L"{index}", ToString((uint64)index), L"{count}", ToString((uint64)count), L"{expected}", ToString((uint64)expected))
					);
				}
			}

			void CPreProcessor::E_MissingPrevConcatinateArgument(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_MISSING_PREV_CONCATINATE_ARGUMENT,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_MissingNextConcatinateArgument(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_MISSING_NEXT_CONCATINATE_ARGUMENT,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_InvalidPrevConcatinateArgument(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_INVALID_PREV_CONCATINATE_ARGUMENT,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_InvalidNextConcatinateArgument(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_INVALID_NEXT_CONCATINATE_ARGUMENT,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_ExpectedExpression(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_EXPRESSION,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_ExpectedNewLine(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_NEW_LINE,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_ExpectedOperand(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_OPERAND,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_UnexpectedEndExpectedOperand(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_UNEXPECTED_END_EXPECTED_OPERAND,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_ExpectedOperator(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_OPERATOR,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_InvalidExpression(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_INVALID_EXPRESSION,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_UnsupportedOperator(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_UNSUPPORTED_OPERATOR,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_InvalidOperand(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_INVALID_OPERAND,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}

			void CPreProcessor::E_ExpectedOneArgument(const AnsiString &function, int line, const size_t &index, const size_t &count)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_EXPECTED_ONE_ARGUMENT,
						E(L"{index}", ToString((uint64)index), L"{count}", ToString((uint64)count))
					);
				}
			}

			void CPreProcessor::E_UnexpectedPriorOperators(const AnsiString &function, int line, const size_t &index)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_UNEXPECTED_PRIOR_OPERATORS,
						E(L"{index}", ToString((uint64)index))
					);
				}
			}

			void CPreProcessor::E_UnknownFunction(const AnsiString &function, int line, const size_t &index, const String &name)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						function,
						line,
						ERROR_CPPDOC_PP_UNKNOWN_FUNCTION,
						E(L"{index}", ToString((uint64)index), L"{name}", name)
					);
				}
			}
		#pragma endregion

		#pragma region Search
			List *CPreProcessor::FindNewLineOrSLComment(List &list)
			{
				List *current{ &list };
				while (current)
				{
					if (isNewLines(*current) || isSLComment(*current))
						return current;
					current = current->Next;
				}
				return nullptr;
			}

			List *CPreProcessor::FindNewLineOrSLCommentOrTail(List &list)
			{
				List *current{ &list };
				while (current->Next)
				{
					if (isNewLines(*current) || isSLComment(*current))
						return current;
					current = current->Next;
				}
				return current;
			}

			List *CPreProcessor::FindEndIf(List &list)
			{
				List *current{ &list };
				while (current)
				{
					// Skip inner branch
					if (isCondition(*current))
					{
						if (!(current = FindNewLineOrSLComment(*current)))
							return nullptr;
						if (!(current = FindEndIf(*current)))
							return nullptr;
						if (!(current = FindNewLineOrSLComment(*current)))
							return nullptr;
						current = current->Next;
						continue;
					}
					if (isEndIf(*current))
						return current;
					current = current->Next;
				}
				return nullptr;
			}

			List *CPreProcessor::FindBranchEnd(List &list)
			{
				List *current{ &list };
				while (current)
				{
					// Skip inner branch
					if (isCondition(*current))
					{
						if (!(current = FindNewLineOrSLComment(*current)))
							return nullptr;
						if (!(current = FindEndIf(*current)))
							return nullptr;
						if (!(current = FindNewLineOrSLComment(*current)))
							return nullptr;
						current = current->Next;
						continue;
					}
					if (isBranchEnd(*current))
						return current;
					current = current->Next;
				}
				return nullptr;
			}

			List *CPreProcessor::FindCommaOrBracketClose(List &list)
			{
				List *current{ &list };
				while (current)
				{
					if (current->Item->Type == TokenType::Operator)
					{
						if (current->Item->Op->Name == L")" || current->Item->Op->Name == L",")
							return current;
						if (current->Item->Op->Name == L"(")
						{
							if (!(current = Next(*current, true, true, true, true)))
								return nullptr;
							if (!(current = FindBracketClose(*current)))
								return nullptr;
						}
					}
					current = current->Next;
				}
				return nullptr;
			}

			List *CPreProcessor::FindBracketClose(List &list)
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
							if (!(current = Next(*current, true, true, true, true)))
								return nullptr;
							if (!(current = FindBracketClose(*current)))
								return nullptr;
						}
					}
					current = current->Next;
				}
				return nullptr;
			}

			List *CPreProcessor::FindGreater(List &list)
			{
				List *current{ &list };
				while (current && (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L">"))
					current = current->Next;
				return current;
			}
		#pragma endregion

		#pragma region Checks
			bool CPreProcessor::isCondition(List &list)
			{
				static const StringArray CONDITIONS{ L"if", L"ifdef", L"ifndef" };

				if (list.Item->Type != TokenType::Operator)
					return false;
				if (!in(list.Item->Op->Name, PP_HASH))
					return false;
				List *next{ Next(list, true, true, false, false) };
				if (!next)
					return false;
				if (next->Item->Type != TokenType::Identifier)
					return false;
				if (!in(next->Item->Value, CONDITIONS))
					return false;
				return true;
			}

			bool CPreProcessor::isBranchEnd(List &list)
			{
				static const StringArray ENDS{ L"elif", L"elifdef", L"elifndef", L"else", L"endif" };

				if (list.Item->Type != TokenType::Operator)
					return false;
				if (!in(list.Item->Op->Name, PP_HASH))
					return false;
				List *next{ Next(list, true, true, false, false) };
				if (!next)
					return false;
				if (next->Item->Type != TokenType::Identifier)
					return false;
				if (!in(next->Item->Value, ENDS))
					return false;
				return true;
			}

			bool CPreProcessor::isEndIf(List &list)
			{
				if (list.Item->Type != TokenType::Operator)
					return false;
				if (!in(list.Item->Op->Name, PP_HASH))
					return false;
				List *next{ Next(list, true, true, false, false) };
				if (!next)
					return false;
				if (next->Item->Type != TokenType::Identifier)
					return false;
				if (next->Item->Value != L"endif")
					return false;
				return true;
			}

			bool CPreProcessor::isStringification(List &list)
			{
				return list.Item->Type == TokenType::Operator && in(list.Item->Op->Name, PP_HASH);
			}

			bool CPreProcessor::isConcatenation(List &list)
			{
				return list.Item->Type == TokenType::Operator && in(list.Item->Op->Name, PP_2HASH);
			}

			bool CPreProcessor::isVaArgs(List &list)
			{
				return list.Item->Type == TokenType::Identifier && list.Item->Value == L"__VA_ARGS__";
			}

			bool CPreProcessor::isVaOpt(List &list)
			{
				return list.Item->Type == TokenType::Identifier && list.Item->Value == L"__VA_OPT__";
			}
		#pragma endregion

		#pragma region Pre-processing
			bool CPreProcessor::Process(Tokens &tokens, PList &out)
			{
				m_bAborted = false;
				out = nullptr;
				if (tokens.empty())
					return true;
				ClearStoredDefinitions();
				ListGuard list{ MakeList(tokens, nullptr) };
				List *target{ nullptr }, *tail{ nullptr };
				ListGuard target_guard{ &target };
				if (!ProcessList(target, tail, *list, npos))
					return false;
				DeleteUnusedTokens(target);
				target_guard.Free();
				out = target;
				return true;
			}

			bool CPreProcessor::ProcessList(PList &target, PList &tail, List &list, const size_t &token_index)
			{
				List *current{ &list }, *last{ current };
				while (current && !m_bAborted)
				{
					if (m_pProgressListener)
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
					last = current;
					// Pre-processor directive
					if (current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, PP_HASH))
					{
						if (!(current = Next(*current, true, true, false, false))) // Directive name (if, define, etc)
						{
							E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, token_index == npos ? last->Item->Index : token_index);
							return false;
						}
						if (current->Item->Type != TokenType::Identifier)
						{
							E_ExpectedIdentifier(__FUNCTION__, __LINE__, token_index == npos ? current->Item->Index : token_index, TokenToString(*current->Item));
							return false;
						}
						if (!ProcessDirective(target, tail, *current, current))
							return false;
						continue;
					}
					// Expand macro if needed, otherwise add token to the list
					if (!Expand(target, tail, *current, false, EmptyStringArray, token_index == npos ? current->Item->Index : token_index, current))
						return false;
				}
				return true;
			}

			bool CPreProcessor::ProcessDirective(PList &target, PList &tail, List &list, PList &out)
			{
				if (list.Item->Value == L"error")
					return ProcessError(target, tail, list, out);
				if (list.Item->Value == L"warning")
					return ProcessWarning(target, tail, list, out);
				if (list.Item->Value == L"line")
					return ProcessLine(target, tail, list, out);
				if (list.Item->Value == L"undef")
					return ProcessUnDef(target, tail, list, out);
				if (list.Item->Value == L"define")
					return ProcessDefine(target, tail, list, out);
				if (list.Item->Value == L"ifdef")
					return ProcessIf(target, tail, list, out);
				if (list.Item->Value == L"ifndef")
					return ProcessIf(target, tail, list, out);
				if (list.Item->Value == L"if")
					return ProcessIf(target, tail, list, out);
				if (list.Item->Value == L"include")
					return ProcessInclude(target, tail, list, out);
				if (list.Item->Value == L"pragma")
					return ProcessPragma(target, tail, list, out);
				E_UnknownDirective(__FUNCTION__, __LINE__, list.Item->Index, TokenToString(*list.Item));
				return false;
			}

			bool CPreProcessor::ProcessError(PList &target, PList &tail, List &list, PList &out)
			{
				// No need to do anything, just skip to the directive end
				if ((out = FindNewLineOrSLComment(list)))
					out = Next(*out, true, false, false, false);
				return true;
			}

			bool CPreProcessor::ProcessWarning(PList &target, PList &tail, List &list, PList &out)
			{
				// No need to do anything, just skip to the directive end
				if ((out = FindNewLineOrSLComment(list)))
					out = Next(*out, true, false, false, false);
				return true;
			}

			bool CPreProcessor::ProcessLine(PList &target, PList &tail, List &list, PList &out)
			{
				// No need to do anything, just skip to the directive end
				if ((out = FindNewLineOrSLComment(list)))
					out = Next(*out, true, false, false, false);
				return true;
			}

			bool CPreProcessor::ProcessUnDef(PList &target, PList &tail, List &list, PList &out)
			{
				List *current{ Next(list, true, true, false, false) };
				if (!current)
				{
					E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list.Item->Index);
					return false;
				}
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, current->Item->Index, TokenToString(*current->Item));
					return false;
				}
				DeleteDefinition(current->Item->Value);
				if ((out = FindNewLineOrSLComment(*current)))
					out = Next(*out, true, false, false, false);
				return true;
			}

			bool CPreProcessor::ProcessDefine(PList &target, PList &tail, List &list, PList &out)
			{
				List *current{ Next(list, true, true, false, false) };
				if (!current)
				{
					E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, list.Item->Index);
					return false;
				}
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, current->Item->Index, TokenToString(*current->Item));
					return false;
				}
				String name{ current->Item->Value };
				size_t name_token_index{ current->Item->Index };
				List *end{ nullptr }, *copy{ nullptr };
				if ((current = Next(*current, true, true, false, false)) && !isNewLines(*current) && !isSLComment(*current))
				{
					end = FindNewLineOrSLCommentOrTail(*current);
					if (isNewLines(*end) || isSLComment(*end))
						end = end->Prev;
					copy = Copy<TokenEx>(*current, end, nullptr);
				}
				bool is_copy;
				CDefinition *definition{ new CDefinition() };
				definition->m_sName = name;
				if (!AddDefinition(definition, copy, name_token_index, is_copy))
				{
					definition->Release();
					Free(copy);
					return false;
				}
				if (is_copy)
				{
					definition->Release();
					Free(copy);
				}
				if ((out = end ? end->Next : current) && (isNewLines(*out) || isSLComment(*out))) // If there is new lines/single-line comment, skip them
					out = Next(*out, true, false, false, false);
				return true;
			}

			bool CPreProcessor::ProcessIf(PList &target, PList &tail, List &list, PList &out)
			{
				static const StringArray ELIFS{ L"elif", L"elifdef", L"elifndef" };

				List *current{ Next(list, true, true, false, false) };
				if (!current)
				{
					E_UnexpectedEndExpectedExpression(__FUNCTION__, __LINE__, list.Item->Index);
					return false;
				}
				bool condition{ false };
				if (!Condition(list.Item->Value, *current, condition, current)) // After this, "current" points to the first token inside condition or branch end if condition is empty
					return false;

				if (condition)
				{
					List *end;
					if (!(end = FindBranchEnd(*current)))
					{
						E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
						return false;
					}
					if (end != current)
					{
						ListGuard copy{ Copy<TokenEx>(*current, end->Prev, nullptr) };
						if (!ProcessList(target, tail, *copy, current->Item->Index))
							return false;
					}
					if (!(end = FindEndIf(*end)))
					{
						E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
						return false;
					}
					if ((out = FindNewLineOrSLComment(*end)))
						out = Next(*out, true, false, false, false);
					return true;
				}

				while (true)
				{
					if (!(current = FindBranchEnd(*current)))
					{
						E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
						return false;
					}
					current = Next(*current, true, true, false, false);

					if (current->Item->Value == L"endif")
					{
						if ((out = FindNewLineOrSLComment(*current)))
							out = Next(*out, true, false, false, false);
						return true;
					}

					if (current->Item->Value == L"else")
					{
						if (!(current = FindNewLineOrSLComment(*current)))
						{
							E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
							return false;
						}
						if (!(current = current->Next))
						{
							E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
							return false;
						}
						List *end{ FindBranchEnd(*current) };
						if (!end)
						{
							E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
							return false;
						}
						if (!isEndIf(*end))
						{
							E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
							return false;
						}
						if (end != current)
						{
							ListGuard copy{ Copy<TokenEx>(*current, end->Prev, nullptr) };
							if (!ProcessList(target, tail, *copy, current->Item->Index))
								return false;
						}
						if ((out = FindNewLineOrSLComment(*end)))
							out = Next(*out, true, false, false, false);
						return true;
					}

					if (in(current->Item->Value, ELIFS))
					{
						List *last{ current };
						String type{ current->Item->Value };
						if (!(current = Next(*current, true, true, false, false)))
						{
							E_UnexpectedEndExpectedExpression(__FUNCTION__, __LINE__, last->Item->Index);
							return false;
						}
						if (!Condition(type, *current, condition, current))
							return false;
						if (!condition)
							continue;
						List *end{ FindBranchEnd(*current) };
						if (!end)
						{
							E_UnfinishedBranch(__FUNCTION__, __LINE__, last->Item->Index);
							return false;
						}
						if (end != current)
						{
							ListGuard copy{ Copy<TokenEx>(*current, end->Prev, nullptr) };
							if (!ProcessList(target, tail, *copy, current->Item->Index))
								return false;
						}
						if (!(end = FindEndIf(*end)))
						{
							E_UnfinishedBranch(__FUNCTION__, __LINE__, last->Item->Index);
							return false;
						}
						if ((out = FindNewLineOrSLComment(*end)))
							out = Next(*out, true, false, false, false);
						return true;
					}

					break;
				}

				E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
				return false;
			}

			bool CPreProcessor::ProcessInclude(PList &target, PList &tail, List &list, PList &out)
			{
				// No need to do anything, just skip to the directive end
				if ((out = FindNewLineOrSLComment(list)))
					out = Next(*out, true, false, false, false);
				return true;
			}

			bool CPreProcessor::ProcessPragma(PList &target, PList &tail, List &list, PList &out)
			{
				List *current{ Next(list, true, true, false, false) };
				if (current && current->Item->Type == TokenType::Identifier && (current->Item->Value == L"push_macro" || current->Item->Value == L"pop_macro"))
				{
					bool is_push{ current->Item->Value == L"push_macro" };
					List *next(Next(*current, true, true, false, false));
					if (!next)
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, current->Item->Index, L"(");
						return false;
					}
					if (next->Item->Type != TokenType::Operator || next->Item->Op->Name != L"(")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, next->Item->Index, L"(", TokenToString(*next->Item));
						return false;
					}
					if (!(next = Next(*next, true, true, false, false)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, current->Item->Index, L"(");
						return false;
					}
					if (next->Item->Type != TokenType::String || next->Item->Op->Name != L"\"" || !next->Item->Prefix.empty())
					{
						E_ExpectedAnsiString(__FUNCTION__, __LINE__, next->Item->Index, TokenToString(*next->Item));
						return false;
					}
					String name{ next->Item->Value };
					if (!(next = Next(*next, true, true, false, false)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, current->Item->Index, L")");
						return false;
					}
					if (next->Item->Type != TokenType::Operator || next->Item->Op->Name != L")")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, next->Item->Index, L")", TokenToString(*next->Item));
						return false;
					}
					CDefinition *definition;
					if (is_push)
					{
						if ((definition = FindDefinition(name, EmptyStringArray)))
							m_aStoredDefinitions.push_back(definition->Clone());
					}
					else
					{
						if ((definition = PopStoredDefinition(name)))
						{
							auto pos{ m_aDefinitions.find(name) };
							if (pos != m_aDefinitions.end())
								pos->second->Release();
							m_aDefinitions[name] = definition;
						}
					}
					current = next->Next;
				}
				if ((out = current ? FindNewLineOrSLComment(*current) : nullptr))
					out = Next(*out, true, false, false, false);
				return true;
			}
		#pragma endregion

		#pragma region Expanding
			bool CPreProcessor::Expand(PList &target, PList &tail, List &list, const bool defined_allowed, const StringArray &exclude, const size_t &token_index, PList &out)
			{
				CDefinition *definition;
				if (defined_allowed && list.Item->Type == TokenType::Identifier && list.Item->Value == L"defined")
				{
					if (!ExpandDefined(target, tail, list, token_index, out))
						return false;
				}
				else if (list.Item->Type == TokenType::Identifier && (definition = FindDefinition(list.Item->Value, exclude)))
				{
					if (definition->Type == DefinitionType::Expression) // Expand expression definition
					{
						if (!ExpandExpression(target, tail, definition, defined_allowed, exclude, token_index))
							return false;
						out = list.Next;
					}
					else if (definition->Type == DefinitionType::Function) // Expand function definition
					{
						if (!ExpandCall(target, tail, list, definition, defined_allowed, exclude, token_index, out))
							return false;
					}
					else
						out = list.Next;
				}
				else
				{
					tail = Append(target, tail, TokenEx{ list.Item, token_index });
					out = list.Next;
				}
				return true;
			}

			bool CPreProcessor::ExpandList(PList &target, PList &tail, List &list, const bool defined_allowed, const StringArray &exclude, const size_t &token_index)
			{
				List *current{ &list };
				while (current)
				{
					if (!Expand(target, tail, *current, defined_allowed, exclude, token_index, current))
						return false;
				}
				return true;
			}

			bool CPreProcessor::ExpandDefined(PList &target, PList &tail, List &list, const size_t &token_index, PList &out)
			{
				List *current{ &list };
				tail = Append(target, tail, TokenEx{ current->Item, token_index });
				if (!(current = Next(*current, true, true, false, false)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L"(");
					return false;
				}
				if (current->Item->Type == TokenType::Identifier)
				{
					tail = Append(target, tail, TokenEx{ current->Item, token_index });
					out = Next(*current, true, false, false, false);
					return true;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, token_index, L"(", TokenToString(*current->Item));
					return false;
				}
				tail = Append(target, tail, TokenEx{ current->Item, token_index });
				if (!(current = Next(*current, true, true, false, false)))
				{
					E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, token_index);
					return false;
				}
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, token_index, TokenToString(*current->Item));
					return false;
				}
				tail = Append(target, tail, TokenEx{ current->Item, token_index });
				if (!(current = Next(*current, true, true, false, false)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L")")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, token_index, L")", TokenToString(*current->Item));
					return false;
				}
				tail = Append(target, tail, TokenEx{ current->Item, token_index });
				out = Next(*current, true, false, false, false);
				return true;
			}

			bool CPreProcessor::ExpandExpression(PList &target, PList &tail, CDefinition *definition, const bool defined_allowed, const StringArray &exclude, const size_t &token_index)
			{
				StringArray new_exclude{ exclude };
				new_exclude.push_back(definition->Name);
				return ExpandList(target, tail, *definition->Begin, defined_allowed, new_exclude, token_index);
			}

			bool CPreProcessor::ExpandCall(PList &target, PList &tail, List &list, CDefinition *definition, const bool defined_allowed, const StringArray &exclude, const size_t &token_index, PList &out)
			{
				// Make argument list
				List *current{ Next(list, true, true, false, false) };
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L"(");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, token_index, L"(", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, false, false)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
					return false;
				}
				Arguments arguments;
				List *last;
				while (current)
				{
					if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L")")
						break;
					if (!(last = FindCommaOrBracketClose(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
						return false;
					}
					if (last == current)
					{
						E_UnexpectedToken(__FUNCTION__, __LINE__, token_index, TokenToString(*current->Item));
						return false;
					}
					arguments.push_back(Argument{ current, last->Prev });
					current = last;
					if (current->Item->Op->Name == L"," && !(current = Next(*current, true, true, false, false)))
					{
						E_UnexpectedEndExpectedExpression(__FUNCTION__, __LINE__, token_index);
						return false;
					}
				}
				if (definition->Variadic)
				{
					if (arguments.size() < definition->Parameters.size())
					{
						E_TooFewArguments(__FUNCTION__, __LINE__, token_index, arguments.size(), definition->Parameters.size());
						return false;
					}
				}
				else
				{
					if (definition->Parameters.size() != arguments.size())
					{
						E_InvalidArgumentCount(__FUNCTION__, __LINE__, token_index, arguments.size(), definition->Parameters.size());
						return false;
					}
				}
				out = Next(*current, true, false, false, false);
				if (!definition->Body)
					return true;

				// Make variadic argument list
				Arguments variadics;
				for (size_t i = definition->Parameters.size(); i < arguments.size(); i++)
					variadics.push_back(arguments[i]);
				arguments.erase(arguments.begin() + definition->Parameters.size(), arguments.end());

				// Expand macro body
				List *temp_target{ nullptr }, *temp_tail{ nullptr };
				ListGuard guard{ &temp_target };
				String stringified;
				size_t argument_index;
				current = definition->Body;
				while (current)
				{
					if (isSpaces(*current))
					{
						current = current->Next;
						continue;
					}
					if (current->Item->Type == TokenType::Identifier && (argument_index = FindArgumentIndex(current->Item->Value, definition->Parameters)) != npos)
					{
						ExpandArgument(temp_target, temp_tail, arguments[argument_index], token_index);
						current = current->Next;
					}
					else if (isStringification(*current))
					{
						if (!Stringify(temp_target, temp_tail, *current, definition->Parameters, arguments, variadics, token_index, current))
							return false;
					}
					else if (isConcatenation(*current))
					{
						if (!Concatinate(temp_target, temp_tail, *current, definition->Parameters, arguments, token_index, current))
							return false;
					}
					else if (isVaArgs(*current))
					{
						ExpandVaArgs(temp_target, temp_tail, variadics, token_index);
						current = current->Next;
					}
					else if (isVaOpt(*current))
					{
						if (!ExpandVaOpts(temp_target, temp_tail, *current, definition->Parameters, arguments, variadics, token_index, current))
							return false;
					}
					else
					{
						temp_tail = Append(temp_target, temp_tail, TokenEx{ current->Item, token_index });
						current = current->Next;
					}
				}
			
				// Final expand
				StringArray new_exclude{ exclude };
				new_exclude.push_back(definition->Name);
				return ExpandList(target, tail, *temp_target, false, new_exclude, token_index);
			}

			void CPreProcessor::ExpandArgument(PList &target, PList &tail, const Argument &argument, const size_t &token_index)
			{
				List *current{ argument.first };
				while (current)
				{
					if (!isSpaces(*current))
						tail = Append(target, tail, TokenEx{ current->Item, token_index });
					if (current == argument.second)
						break;
					current = current->Next;
				}
			}

			String CPreProcessor::StringifyArgument(const Argument &argument)
			{
				String result;
				List *current{ argument.first };
				while (current)
				{
					if (!isMLComment(*current))
					{
						if (current->Item->Type == TokenType::String && current->Item->Op->Name == L"\"")
							result += L"\\\"" + current->Item->Value + L"\\\"";
						else if (isNewLines(*current) || isSpaces(*current))
							result += L" ";
						else
							result += current->Item->Value;
					}
					if (current == argument.second)
						break;
					current = current->Next;
				}
				return result;
			}

			String CPreProcessor::StringifyVariadics(const Arguments &variadics)
			{
				String result;
				for (size_t i = 0; i < variadics.size(); i++)
				{
					if (i > 0)
						result += L", ";
					result += StringifyArgument(variadics[i]);
				}
				return result;
			}

			bool CPreProcessor::StringifyVariadicOpts(String &target, List &list, const StringArray &parameters, const Arguments &arguments, const Arguments &variadics, const size_t &token_index, PList &out)
			{
				List *current{ Next(list, true, true, false, false) };
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L"(");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, token_index, L"(", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, false, false)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
					return false;
				}
				target.clear();
				if (variadics.empty())
				{
					if (!(out = FindBracketClose(*current)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
						return false;
					}
					out = Next(*out, true, false, false, false);
					return true;
				}
				size_t argument_index;
				while (current)
				{
					if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L")")
						break;
					if (!isMLComment(*current))
					{
						if (current->Item->Type == TokenType::Identifier)
						{
							if (current->Item->Value == L"__VA_ARGS__")
								target += StringifyVariadics(variadics);
							else if ((argument_index = FindArgumentIndex(current->Item->Value, parameters)) != npos)
								target += StringifyArgument(arguments[argument_index]);
							else
								target += current->Item->Value;
						}
						else
							target += current->Item->Value;
					}
					current = Next(*current, true, true, false, false);
				}
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
					return false;
				}
				out = Next(*current, true, false, false, false);
				return true;
			}

			bool CPreProcessor::Stringify(PList &target, PList &tail, List &list, const StringArray &parameters, const Arguments &arguments, const Arguments &variadics, const size_t &token_index, PList &out)
			{
				static const StringArray PREFIXES{ L"R", L"L", L"LR", L"u8", L"u8R", L"u", L"uR", L"U", L"UR" };

				List *current{ Next(list, true, true, false, false) };
				if (!current)
				{
					E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, token_index);
					return false;
				}
				if (current->Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, token_index, TokenToString(*current->Item));
					return false;
				}
				size_t argument_index;
				String stringified;
				if ((argument_index = FindArgumentIndex(current->Item->Value, parameters)) != npos)
				{
					stringified = StringifyArgument(arguments[argument_index]);
					out = Next(*current, true, false, false, false);
				}
				else if (current->Item->Value == L"__VA_ARGS__")
				{
					stringified = StringifyVariadics(variadics);
					out = Next(*current, true, false, false, false);
				}
				else if (current->Item->Value == L"__VA_OPT__")
				{
					if (!StringifyVariadicOpts(stringified, *current, parameters, arguments, variadics, token_index, out))
						return false;
				}
				else
				{
					if (!isMLComment(*current) && !isSpaces(*current))
						stringified = current->Item->Value;
					out = Next(*current, true, false, false, false);
				}
				if (!stringified.empty())
				{
					Token *token{ new Token{ TokenType::String, 0, 0, 0, 0, stringified, L"", L"", 0, true, &cpp::CTokenizer::OpDoubleQuote, 0, 0, 0 } };
					m_aTokens.push_back(token);
					if (tail && tail->Item->Type == TokenType::Identifier && in(tail->Item->Value, PREFIXES))
					{
						token->Prefix = tail->Item->Value;
						current = tail->Prev;
						Delete(target, tail, tail);
						tail = current;
					}
					tail = Append(target, tail, TokenEx{ token, token_index });
				}
				return true;
			}

			bool CPreProcessor::Concatinate(PList &target, PList &tail, List &list, const StringArray &parameters, const Arguments &arguments, const size_t &token_index, PList &out)
			{
				List *prev{ tail }, *next{ Next(list, true, true, false, false) };
				if (prev && (isMLComment(*prev) || isSpaces(*prev)))
					prev = Prev(*prev, true, true, false, false);
				if (!prev)
				{
					E_MissingPrevConcatinateArgument(__FUNCTION__, __LINE__, token_index);
					return false;
				}
				if (!next)
				{
					E_MissingNextConcatinateArgument(__FUNCTION__, __LINE__, token_index);
					return false;
				}
				if (prev->Item->Type != TokenType::Identifier &&
					(prev->Item->Type != TokenType::Integer || !prev->Item->Postfix.empty()) &&
					(prev->Item->Type != TokenType::Operator || prev->Item->Op->Name == L"/"))
				{
					E_InvalidPrevConcatinateArgument(__FUNCTION__, __LINE__, token_index, TokenToString(*prev->Item));
					return false;
				}
				if (next->Item->Type != TokenType::Identifier &&
					next->Item->Type != TokenType::Operator &&
					(next->Item->Type != TokenType::Integer || next->Item->Base != 10))
				{
					E_InvalidNextConcatinateArgument(__FUNCTION__, __LINE__, token_index, TokenToString(*prev->Item));
					return false;
				}

				String src;
				if (prev->Item->Type == TokenType::Operator && prev->Item->Op->Name == L">" &&
					prev->Prev && prev->Prev->Item->Type == TokenType::Operator && prev->Prev->Item->Op->Name == L">")
				{
					src = L">>" + src;
					prev = prev->Prev;
				}
				else
					src = prev->Item->Prefix + prev->Item->Value + prev->Item->Postfix;
				size_t argument_index;
				if (next->Item->Type == TokenType::Identifier && (argument_index = FindArgumentIndex(next->Item->Value, parameters)) != npos)
				{
					const Argument &arg{ arguments[argument_index] };
					if (arg.second != arg.first)
					{
						E_InvalidNextConcatinateArgument(__FUNCTION__, __LINE__, token_index, TokenToString(*arg.first->Item));
						return false;
					}
					if (arg.first->Item->Type != TokenType::Identifier &&
						arg.first->Item->Type != TokenType::Operator &&
						(arg.first->Item->Type != TokenType::Integer || arg.first->Item->Base != 10))
					{
						E_InvalidNextConcatinateArgument(__FUNCTION__, __LINE__, token_index, TokenToString(*arg.first->Item));
						return false;
					}
					src += arg.first->Item->Prefix + arg.first->Item->Value + arg.first->Item->Postfix;
				}
				else
					src += next->Item->Prefix + next->Item->Value + next->Item->Postfix;

				Tokens tokens;
				Tokenize(m_cTokenizer, src, tokens);
				
				List *new_tail{ (prev == target) ? nullptr : prev->Prev };
				Delete(target, prev, tail);
				tail = new_tail;

				for (auto const &token : tokens)
				{
					Token *t{ new Token{ token.Type, 0, 0, 0, 0, token.Value, token.Prefix, token.Postfix, token.Count, token.Finished, token.Op, token.Base, token.Integer, token.Float } };
					m_aTokens.push_back(t);
					tail = Append(target, tail, TokenEx{ t, token_index });
				}
				out = Next(*next, true, false, false, false);
				return true;
			}

			void CPreProcessor::ExpandVaArgs(PList &target, PList &tail, const Arguments &variadics, const size_t &token_index)
			{
				if (variadics.empty())
					return;
				for (size_t i = 0; i < variadics.size(); i++)
				{
					if (i > 0)
					{
						Token *t{ new Token{ TokenType::Operator, 0, 0, 0, 0, L",", L"", L"", 1, true, &cpp::CTokenizer::OpComma, 0, 0, 0 } };
						m_aTokens.push_back(t);
						tail = Append(target, tail, TokenEx{ t, token_index });
					}
					List *current{ variadics[i].first };
					while (current)
					{
						if (!isMLComment(*current) && !isSpaces(*current))
							tail = Append(target, tail, TokenEx{ current->Item, token_index });
						if (current == variadics[i].second)
							break;
						current = current->Next;
					}
				}
			}

			bool CPreProcessor::ExpandVaOpts(PList &target, PList &tail, List &list, const StringArray &parameters, const Arguments &arguments, const Arguments &variadics, const size_t &token_index, PList &out)
			{
				List *current{ Next(list, true, true, false, false) };
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L"(");
					return false;
				}
				if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
				{
					E_ExpectedToken(__FUNCTION__, __LINE__, token_index, L"(", TokenToString(*current->Item));
					return false;
				}
				if (!(current = Next(*current, true, true, false, false)))
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
					return false;
				}
				List *end{ FindBracketClose(*current) };
				if (!end)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
					return false;
				}
				out = Next(*end, true, false, false, false);
				if (end == current || variadics.empty())
					return true;
				size_t argument_index;
				while (current)
				{
					if (isSpaces(*current))
					{
						if (current == end)
							break;
						current = current->Next;
						continue;
					}
					if (current->Item->Type == TokenType::Identifier && (argument_index = FindArgumentIndex(current->Item->Value, parameters)) != npos)
					{
						ExpandArgument(target, tail, arguments[argument_index], token_index);
						current = current->Next;
					}
					else if (isStringification(*current))
					{
						if (!Stringify(target, tail, *current, parameters, arguments, variadics, token_index, current))
							return false;
					}
					else if (isConcatenation(*current))
					{
						if (!Concatinate(target, tail, *current, parameters, arguments, token_index, current))
							return false;
					}
					else if (isVaArgs(*current))
					{
						ExpandVaArgs(target, tail, variadics, token_index);
						current = current->Next;
					}
					else if (isVaOpt(*current))
					{
						if (!ExpandVaOpts(target, tail, *current, parameters, arguments, variadics, token_index, current))
							return false;
					}
					else
					{
						tail = Append(target, tail, TokenEx{ current->Item, token_index });
						current = current->Next;
					}
					if (current == end)
						break;
				}
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
					return false;
				}
				return true;
			}
		#pragma endregion

		#pragma region Evaluation
			bool CPreProcessor::Condition(const String &type, List &list, bool &condition, PList &out)
			{
				if (type == L"if" || type == L"elif")
				{
					List *end{ FindNewLineOrSLComment(list) };
					if (!end)
					{
						E_UnexpectedEndExpectedExpression(__FUNCTION__, __LINE__, list.Item->Index);
						return false;
					}
					if (end == &list)
					{
						E_ExpectedExpression(__FUNCTION__, __LINE__, list.Item->Index);
						return false;
					}
					ListGuard copy{ Copy<TokenEx>(list, end->Prev, nullptr) };
					if (!Evaluate(*copy, list.Item->Index, condition))
						return false;
					if (!(out = Next(*end, true, false, false, false)))
					{
						E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
						return false;
					}
					return true;
				}

				if (type == L"ifdef" || type == L"elifdef")
				{
					if (list.Item->Type != TokenType::Identifier)
					{
						E_ExpectedIdentifier(__FUNCTION__, __LINE__, list.Item->Index, TokenToString(*list.Item));
						return false;
					}
					condition = FindDefinition(list.Item->Value, EmptyStringArray) ? true : false;
					if (!(out = Next(list, true, true, false, false)))
					{
						E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
						return false;
					}
					if (!isNewLines(*out) && !isSLComment(*out))
					{
						E_ExpectedNewLine(__FUNCTION__, __LINE__, out->Item->Index);
						return false;
					}
					if (!(out = Next(*out, true, false, false, false)))
					{
						E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
						return false;
					}
					return true;
				}

				//if (type == L"ifndef" || type == L"elifndef")
				if (list.Item->Type != TokenType::Identifier)
				{
					E_ExpectedIdentifier(__FUNCTION__, __LINE__, list.Item->Index, TokenToString(*list.Item));
					return false;
				}
				condition = FindDefinition(list.Item->Value, EmptyStringArray) ? false : true;
				if (!(out = Next(list, true, true, false, false)))
				{
					E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
					return false;
				}
				if (!isNewLines(*out) && !isSLComment(*out))
				{
					E_ExpectedNewLine(__FUNCTION__, __LINE__, out->Item->Index);
					return false;
				}
				if (!(out = Next(*out, true, false, false, false)))
				{
					E_UnfinishedBranch(__FUNCTION__, __LINE__, list.Item->Index);
					return false;
				}
				return true;
			}

			bool CPreProcessor::Evaluate(List &list, const size_t &token_index, bool &target)
			{
				List *temp_target{ nullptr }, *temp_tail{ nullptr };
				ListGuard guard{ temp_target };
				if (!ExpandList(temp_target, temp_tail, list, true, EmptyStringArray, token_index) || !temp_target)
					return false;

				CExpression *expression{ nullptr };
				List *dummy;
				if (!BuildExpressionList(expression, *temp_target, false, token_index, dummy))
					return BuildExpressionFailed(expression);
				int64 value;
				if (!EvaluateList(expression, token_index, value))
					return BuildExpressionFailed(expression);
				target = value ? true : false;
				expression->Release();
				return true;
			}

			bool CPreProcessor::BuildExpressionList(PExpression &target, List &list, const bool is_block, const size_t &token_index, PList &out)
			{
				static const StringArray ALLOWED_PRIORS{ L"~", L"compl", L"!", L"not", L"+", L"-" };

				CExpression *item;
				List *current{ &list }, *next;
				if (!target)
					target = new CExpression();
				bool is_operand{ true }, block_end{ false };
				while (current)
				{
					if (is_block && current->Item->Type == TokenType::Operator && current->Item->Op->Name == L")")
					{
						if (is_operand && !target->Items.empty())
						{
							E_ExpectedOperand(__FUNCTION__, __LINE__, token_index, L")");
							return BuildExpressionFailed(target);
						}
						block_end = true;
						break;
					}
					if (is_operand)
					{
						std::vector<List *> priors;
						while (current && current->Item->Type == TokenType::Operator && in(current->Item->Op->Name, ALLOWED_PRIORS))
						{
							priors.push_back(current);
							current = Next(*current, true, true, false, false);
						}
						if (!current)
						{
							E_UnexpectedEndExpectedOperand(__FUNCTION__, __LINE__, token_index);
							return BuildExpressionFailed(target);
						}

						switch (current->Item->Type)
						{
						case TokenType::Integer:
						case TokenType::String:
							target->Items.push_back(new CExpression(current, priors));
							current = Next(*current, true, true, false, false);
							break;
						case TokenType::Identifier:
							if (current->Item->Value == L"defined" || ((next = Next(*current, true, true, false, false)) && next->Item->Type == TokenType::Operator && next->Item->Op->Name == L"("))
							{
								if (!BuildExpressionCall(item, *current, token_index, current))
									return BuildExpressionFailed(target);
								item->Priors = priors;
								target->Items.push_back(item);
							}
							else
							{
								target->Items.push_back(new CExpression(current, priors));
								current = Next(*current, true, true, false, false);
							}
							break;
						case TokenType::Operator:
							if (current->Item->Op->Name == L"<")
							{
								target->Items.push_back(new CExpression(current, priors));
								if (!(current = FindGreater(*current)))
								{
									E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L">");
									return BuildExpressionFailed(target);
								}
								current = Next(*current, true, true, false, false);
								break;
							}
							if (current->Item->Op->Name != L"(")
							{
								E_ExpectedToken(__FUNCTION__, __LINE__, token_index, L"(", TokenToString(*current->Item));
								return BuildExpressionFailed(target);
							}
							if (!(current = Next(*current, true, true, false, false)))
							{
								E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
								return BuildExpressionFailed(target);
							}
							item = nullptr;
							if (!BuildExpressionList(item, *current, true, token_index, current))
								return BuildExpressionFailed(target);
							item->Priors = priors;
							target->Items.push_back(item);
							break;
						default:
							E_UnexpectedEndExpectedOperand(__FUNCTION__, __LINE__, token_index);
							return BuildExpressionFailed(target);
						}
						is_operand = false;
						continue;
					}

					if (current->Item->Type != TokenType::Operator)
					{
						E_ExpectedOperator(__FUNCTION__, __LINE__, token_index, TokenToString(*current->Item));
						return BuildExpressionFailed(target);
					}
					if (current->Item->Op->Name == L">" && (next = current->Next) && next->Item->Type == TokenType::Operator && next->Item->Op->Name == L">")
					{
						// Convert two ">" to single ">>" operator
						Token *t{ new Token{ TokenType::Operator, 0, 0, 0, 0, L">>", L"", L"", 1, true, &cpp::CTokenizer::Op2Greater, 0, 0, 0 } };
						m_aTokens.push_back(t);
						current->Item = TokenEx{ t, token_index };
						Delete(next);
					}
					target->Items.push_back(new CExpression(current));
					current = Next(*current, true, true, false, false);
					is_operand = true;
				}
				if (is_block && !block_end)
				{
					if (!current)
						E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
					else
						E_ExpectedToken(__FUNCTION__, __LINE__, token_index, L")", TokenToString(*current->Item));
					return BuildExpressionFailed(target);
				}
				out = current ? Next(*current, true, false, false, false) : nullptr;

				// Re-arrange accordingly to operators precedence
				bool changed{ true };
				while (changed)
				{
					if (target->Items.size() <= 3)
						break;

					changed = false;
					size_t i{ target->Items.size() - 2 };
					while (i >= 3)
					{
						if (target->Items[i]->Begin->Item->Op->Precedence < target->Items[i - 2]->Begin->Item->Op->Precedence)
						{
							item = new CExpression();
							item->Items.push_back(target->Items[i - 1]);
							item->Items.push_back(target->Items[i]);
							item->Items.push_back(target->Items[i + 1]);
							target->Items.erase(target->Items.begin() + (i - 1), target->Items.begin() + (i + 2));
							target->Items.insert(target->Items.begin() + (i - 1), item);
							changed = true;
						}
						i -= 2;
					}
				}
				changed = true;
				while (changed)
				{
					changed = false;
					size_t i{ 1 };
					while (target->Items.size() > 3 && i <= target->Items.size() - 4)
					{
						if (target->Items[i]->Begin->Item->Op->Precedence < target->Items[i + 2]->Begin->Item->Op->Precedence)
						{
							item = new CExpression();
							item->Items.push_back(target->Items[i - 1]);
							item->Items.push_back(target->Items[i]);
							item->Items.push_back(target->Items[i + 1]);
							target->Items.erase(target->Items.begin() + (i - 1), target->Items.begin() + (i + 2));
							target->Items.insert(target->Items.begin() + (i - 1), item);
							changed = true;
							continue;
						}
						i += 2;
					}
				}

				return true;
			}

			bool CPreProcessor::BuildExpressionCall(PExpression &target, List &list, const size_t &token_index, PList &out)
			{
				target = new CExpression(list.Item->Value);
				List *current{ Next(list, true, true, false, false) };
				if (!current)
				{
					E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L"(");
					return BuildExpressionFailed(target);
				}
				if (target->Name == L"defined" && current->Item->Type == TokenType::Identifier) // Handle "defined IDENTIFIER" operator
				{
					target->Items.push_back(new CExpression(current));
					out = Next(*current, true, false, false, false);
				}
				else
				{
					if (current->Item->Type != TokenType::Operator || current->Item->Op->Name != L"(")
					{
						E_ExpectedToken(__FUNCTION__, __LINE__, token_index, L"(", TokenToString(*current->Item));
						return false;
					}
					if (!(current = Next(*current, true, true, false, false)))
					{
						E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L")");
						return false;
					}
					if (!BuildExpressionList(target, *current, true, token_index, out))
						return BuildExpressionFailed(target);
				}
				return true;
			}

			bool CPreProcessor::BuildExpressionFailed(PExpression &target)
			{
				if (target)
				{
					target->Release();
					target = nullptr;
				}
				return false;
			}

			bool CPreProcessor::EvaluateList(CExpression *expression, const size_t &token_index, int64 &target)
			{
				if (expression->Items.empty())
				{
					E_InvalidExpression(__FUNCTION__, __LINE__, token_index);
					return false;
				}
				if (!EvaluateOperand(expression->Items[0], token_index, target))
					return false;
				int64 t;
				const Operator *op;
				for (size_t i = 2; i < expression->Items.size(); i += 2)
				{
					if (!EvaluateOperand(expression->Items[i], token_index, t))
						return false;
					op = expression->Items[i - 1]->Begin->Item->Op;
					if (op->Name == L">>")
						target >>= t;
					else if (op->Name == L"+")
						target += t;
					else if (op->Name == L"-")
						target -= t;
					else if (op->Name == L"*")
						target *= t;
					else if (op->Name == L"/")
						target /= t;
					else if (op->Name == L"%")
						target %= t;
					else if (op->Name == L"^" || op->Name == L"xor")
						target ^= t;
					else if (op->Name == L"&" || op->Name == L"bitand")
						target &= t;
					else if (op->Name == L"|" || op->Name == L"bitor")
						target |= t;
					else if (op->Name == L"==")
						target = (target == t) ? 1 : 0;
					else if (op->Name == L"!=")
						target = (target != t) ? 1 : 0;
					else if (op->Name == L"<")
						target = (target < t) ? 1 : 0;
					else if (op->Name == L">")
						target = (target > t) ? 1 : 0;
					else if (op->Name == L"<=")
						target = (target <= t) ? 1 : 0;
					else if (op->Name == L">=")
						target = (target >= t) ? 1 : 0;
					else if (op->Name == L"&&" || op->Name == L"and")
						target = (target && t) ? 1 : 0;
					else if (op->Name == L"||" || op->Name == L"or")
						target = (target || t) ? 1 : 0;
					else if (op->Name == L"<<")
						target <<= t;
					else
					{
						E_UnsupportedOperator(__FUNCTION__, __LINE__, token_index, op->Name);
						return false;
					}
				}
				ApplyPriors(target, expression->Priors);
				return true;
			}

			bool CPreProcessor::EvaluateOperand(CExpression *expression, const size_t &token_index, int64 &target)
			{
				if (!expression->Name.empty())
					return EvaluateCall(expression, token_index, target);
				if (!expression->Begin)
					return EvaluateList(expression, token_index, target);
				switch (expression->Begin->Item->Type)
				{
				case TokenType::Integer:
					target = expression->Begin->Item->Integer;
					break;
				case TokenType::Identifier: // All definitions are expanded, so the only identifier expanding to 1 is "true"
					target = (expression->Begin->Item->Value == L"true") ? 1 : 0;
					break;
				default:
					E_InvalidOperand(__FUNCTION__, __LINE__, token_index, TokenToString(*expression->Begin->Item));
					return false;
				}
				ApplyPriors(target, expression->Priors);
				return true;
			}

			bool CPreProcessor::EvaluateCall(CExpression *expression, const size_t &token_index, int64 &target)
			{
				if (expression->Name == L"defined")
				{
					if (expression->Items.size() != 1)
					{
						E_ExpectedOneArgument(__FUNCTION__, __LINE__, token_index, expression->Items.size());
						return false;
					}
					if (!expression->Items[0]->Priors.empty())
					{
						E_UnexpectedPriorOperators(__FUNCTION__, __LINE__, token_index);
						return false;
					}
					if (!expression->Items[0]->Begin || expression->Items[0]->Begin->Item->Type != TokenType::Identifier)
					{
						if (!expression->Items[0]->Begin)
							E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, token_index);
						else
							E_ExpectedIdentifier(__FUNCTION__, __LINE__, token_index, TokenToString(*expression->Items[0]->Begin->Item));
						return false;
					}
					target = FindDefinition(expression->Items[0]->Begin->Item->Value, EmptyStringArray) ? 1 : 0;
					ApplyPriors(target, expression->Priors);
					return true;
				}

				if (expression->Name == L"__has_include")
				{
					if (expression->Items.size() != 1)
					{
						E_ExpectedOneArgument(__FUNCTION__, __LINE__, token_index, expression->Items.size());
						return false;
					}
					if (!expression->Items[0]->Priors.empty())
					{
						E_UnexpectedPriorOperators(__FUNCTION__, __LINE__, token_index);
						return false;
					}
					if (!expression->Items[0]->Begin)
					{
						E_UnexpectedEndExpectedOperand(__FUNCTION__, __LINE__, token_index);
						return false;
					}
					if (expression->Items[0]->Begin->Item->Type == TokenType::String)
					{
						if (expression->Items[0]->Begin->Item->Op->Name != L"\"")
						{
							E_ExpectedAnsiString(__FUNCTION__, __LINE__, token_index, TokenToString(*expression->Items[0]->Begin->Item));
							return false;
						}
						if (!expression->Items[0]->Begin->Item->Prefix.empty())
						{
							E_ExpectedAnsiString(__FUNCTION__, __LINE__, token_index, TokenToString(*expression->Items[0]->Begin->Item));
							return false;
						}
						target = hasInclude(expression->Items[0]->Begin->Item->Value) ? 1 : 0;
						ApplyPriors(target, expression->Priors);
						return true;
					}
					if (expression->Items[0]->Begin->Item->Type == TokenType::Operator)
					{
						if (expression->Items[0]->Begin->Item->Op->Name != L"<")
						{
							E_ExpectedToken(__FUNCTION__, __LINE__, token_index, L"<", expression->Items[0]->Begin->Item->Op->Name);
							return false;
						}
						String filename;
						List *current{ Next(*expression->Items[0]->Begin, true, false, false, false) };
						while (current)
						{
							if (current->Item->Type == TokenType::Operator && current->Item->Op->Name == L">")
								break;
							if (current->Item->Type == TokenType::Group) // Here can only be the GROUP_SPACE, because new line is directive end and there are no other groups in use
								filename += PadRight(L" ", L' ', current->Item->Count);
							else
								filename += current->Item->Value;
							current = current->Next;
						}
						if (!current)
						{
							E_UnexpectedEnd(__FUNCTION__, __LINE__, token_index, L">");
							return false;
						}
						target = hasInclude(filename) ? 1 : 0;
						ApplyPriors(target, expression->Priors);
						return true;
					}

					E_ExpectedOperand(__FUNCTION__, __LINE__, token_index, TokenToString(*expression->Items[0]->Begin->Item));
					return false;
				}

				if (expression->Name == L"__has_cpp_attribute")
				{
					if (expression->Items.size() != 1)
					{
						E_ExpectedOneArgument(__FUNCTION__, __LINE__, token_index, expression->Items.size());
						return false;
					}
					if (!expression->Items[0]->Priors.empty())
					{
						E_UnexpectedPriorOperators(__FUNCTION__, __LINE__, token_index);
						return false;
					}
					if (!expression->Items[0]->Begin)
					{
						E_UnexpectedEndExpectedIdentifier(__FUNCTION__, __LINE__, token_index);
						return false;
					}
					if (expression->Items[0]->Begin->Item->Type != TokenType::Identifier)
					{
						E_ExpectedIdentifier(__FUNCTION__, __LINE__, token_index, TokenToString(*expression->Items[0]->Begin->Item));
						return false;
					}
					target = hasAttribute(expression->Items[0]->Begin->Item->Value) ? 1 : 0;
					ApplyPriors(target, expression->Priors);
					return true;
				}

				E_UnknownFunction(__FUNCTION__, __LINE__, token_index, expression->Name);
				return false;
			}

			void CPreProcessor::ApplyPriors(int64 &target, const std::vector<List *> &priors)
			{
				const Operator *op;
				for (auto pos = priors.rbegin(); pos != priors.rend(); pos++)
				{
					op = (*pos)->Item->Op;
					if (op->Name == L"~" || op->Name == L"compl")
						target = ~target;
					else if (op->Name == L"!" || op->Name == L"not")
						target = target ? 0 : 1;
					else if (op->Name == L"-")
						target = -target;
				}
			}
		#pragma endregion
		}
	}
}