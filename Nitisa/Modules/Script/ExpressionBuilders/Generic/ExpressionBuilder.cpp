// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		#pragma region Constructor & destructor
			CExpressionBuilder::CExpressionBuilder():
				CReleasable(),
				m_pTokens{ nullptr },
				m_pErrorListener{ nullptr },
				m_aCastOperators{ StringKeyValue{ L"(", L")" } },
				m_aCallOperators{ StringKeyValue{ L"(", L")" } },
				m_aBraceOperators{ StringKeyValue{ L"{", L"}" } },
				m_aSubscriptOperators{ StringKeyValue{ L"[", L"]" } },
				m_aComments{ L"/*", L"//" },
				m_aPointers{ L"*", L"&" },
				m_aTrueKeywords{ L"true" },
				m_aFalseKeywords{ L"false" },
				m_aNullKeywords{ L"nullptr" },
				m_aDataTypes{ L"bool", L"double", L"float", L"int", L"int64", L"Integer", L"String" },
				m_aMemberAccessOperators{ L"::", L".", L"->" },
				m_bCaseSensitive{ true },
				m_bAllowUserDefinedLiterals{ true },
				m_bAllowStringConcatenation{ true },
				m_bAllowPrecedence{ true },
				m_aSkipGroups{ GROUP_SPACE, GROUP_NEW_LINE, GROUP_SEPARATOR },
				m_sTernaryOperator1{ L"?" },
				m_sTernaryOperator2{ L":" }
			{

			}
		#pragma endregion

		#pragma region IExpressionBuilder methods
			bool CExpressionBuilder::Build(ITokenizer *tokenizer, IExpression **target)
			{
				*target = nullptr;
				if (!tokenizer)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_EB_EXPECTED_TOKENIZER
						);
					}
					return false;
				}
				Tokens tokens;
				size_t index{ 0 };
				while (tokenizer->Next(index, tokens));
				return Build(tokens, 0, tokens.size() - 1, target);
			}

			bool CExpressionBuilder::Build(const Tokens &tokens, IExpression **target)
			{
				*target = nullptr;
				if (tokens.empty())
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_EB_EXPECTED_TOKENS
						);
					}
					return false;
				}
				return Build(tokens, 0, tokens.size() - 1, target);
			}

			bool CExpressionBuilder::Build(const Tokens &tokens, const size_t first, const size_t last, IExpression **target)
			{
				*target = nullptr;
				if (tokens.empty())
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_EB_EXPECTED_TOKENS
						);
					}
					return false;
				}
				if (first > last)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_EB_INVALID_TOKENS_RANGE,
							StringKeyValueArray{ StringKeyValue{ L"{first}", ToString(uint64(first)) }, StringKeyValue{ L"{last}", ToString(uint64(last)) } }
						);
					}
					return false;
				}
				if (first >= tokens.size())
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_EB_INVALID_TOKENS_RANGE_START,
							StringKeyValueArray{ StringKeyValue{ L"{first}", ToString(uint64(first)) }, StringKeyValue{ L"{size}", ToString(uint64(tokens.size())) } }
						);
					}
					return false;
				}
				if (last >= tokens.size())
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_EB_INVALID_TOKENS_RANGE_END,
							StringKeyValueArray{ StringKeyValue{ L"{last}", ToString(uint64(first)) }, StringKeyValue{ L"{size}", ToString(uint64(tokens.size())) } }
						);
					}
					return false;
				}
				m_pTokens = &tokens[0];
				m_iMinTokenIndex = first;
				m_iMaxTokenIndex = last;
				PrepareKeywords(m_aTrueKeywords, m_aTrueKeywordsPrepared);
				PrepareKeywords(m_aFalseKeywords, m_aFalseKeywordsPrepared);
				PrepareKeywords(m_aNullKeywords, m_aNullKeywordsPrepared);
				PrepareKeywords(m_aDataTypes, m_aDataTypesPrepared);
				const Token *token{ Next(&tokens[first], false) };
				if (!DecodeSequence(&token, target, L""))
					return false;
				if (!MakeMemberAccess(target))
				{
					(*target)->Release();
					*target = nullptr;
					return false;
				}
				if (!ReArrange(*target))
				{
					(*target)->Release();
					*target = nullptr;
					return false;
				}
				if (!MakeTernary(*target))
				{
					(*target)->Release();
					*target = nullptr;
					return false;
				}
				return true;
			}
		#pragma endregion

		#pragma region Helpers
			void CExpressionBuilder::PrepareKeywords(const StringArray &source, StringArray &target)
			{
				if (!m_bCaseSensitive)
				{
					target.resize(source.size());
					for (size_t i = 0; i < source.size(); i++)
						target[i] = ToLower(source[i]);
				}
				else
					target = source;
			}

			const Token *CExpressionBuilder::Next(const Token *token, const bool do_next) const
			{
				if (!token)
					return nullptr;
				if (do_next)
					token++;
				while (true)
				{
					if (token - m_pTokens > (signed)m_iMaxTokenIndex)
						return nullptr;
					if (token->Type == TokenType::String && in(token->Op->Name, m_aComments))
					{
						token++;
						continue;
					}
					if ((token->Type == TokenType::Operator || token->Type == TokenType::Group) && in(token->Op->Group, m_aSkipGroups))
					{
						token++;
						continue;
					}
					break;
				}
				return token;
			}

			const Token *CExpressionBuilder::Prev(const Token *token) const
			{
				if (!token)
					token = m_pTokens + m_iMaxTokenIndex;
				else if (size_t(token - m_pTokens) == m_iMinTokenIndex)
					return nullptr;
				else
					token--;
				while (true)
				{
					if (size_t(token - m_pTokens) == m_iMinTokenIndex)
						return nullptr;
					if (token->Type == TokenType::String && in(token->Op->Name, m_aComments))
					{
						token--;
						continue;
					}
					if ((token->Type == TokenType::Operator || token->Type == TokenType::Group) && in(token->Op->Group, m_aSkipGroups))
					{
						token--;
						continue;
					}
					break;
				}
				return token;
			}

			bool CExpressionBuilder::ReArrange(IExpression *expression) const
			{
				if (!m_bAllowPrecedence || !expression)
					return true;
				switch (expression->Type)
				{
				case ExpressionType::Brace:
					if (!ReArrange(cast<CExpressionBrace*>(expression)->Name))
						return false;
					return ReArrange(cast<CExpressionBrace*>(expression)->Arguments);
				case ExpressionType::Call:
					if (!ReArrange(cast<CExpressionCall*>(expression)->Name))
						return false;
					return ReArrange(cast<CExpressionCall*>(expression)->Arguments);
				case ExpressionType::Cast:
					return ReArrange(cast<CExpressionCast*>(expression)->Operand);
				case ExpressionType::Sequence:
					for (size_t i = 0; i < expression->getExpressionCount(); i++)
						if (!ReArrange((*expression)[i]))
							return false;
					break;
				case ExpressionType::Subscript:
					if (!ReArrange(cast<CExpressionSubscript*>(expression)->Name))
						return false;
					return ReArrange(cast<CExpressionSubscript*>(expression)->Arguments);
				default:
					return true;
				}
				if (expression->getExpressionCount() < 5)
					return true;
				bool changed;
				do
				{
					changed = false;
					byte p_min{ cast<CExpressionOperator*>((*expression)[1])->Op->Precedence }, p_max{ p_min };
					size_t p_min_start{ 1 };
					CExpressionOperator *op;
					for (size_t i = 3; i < expression->getExpressionCount() - 1; i += 2)
					{
						op = cast<CExpressionOperator*>((*expression)[i]);
						if (op->Op->Precedence < p_min)
						{
							p_min = op->Op->Precedence;
							p_min_start = i;
						}
						else if (op->Op->Precedence > p_max)
							p_max = op->Op->Precedence;
					}
					if (p_min != p_max)
					{
						size_t p_min_last{ p_min_start };
						for (size_t i = p_min_start + 2; i < expression->getExpressionCount() - 1; i += 2)
							if (cast<CExpressionOperator*>((*expression)[i])->Op->Precedence == p_min)
								p_min_last = i;
							else
								break;
						CExpressionSequence *ar{ new CExpressionSequence((*expression)[p_min_start]->Index, false) };
						for (size_t i = p_min_start - 1; i <= p_min_last + 1; i++)
							ar->AddExpression(expression->getExpression(i));
						expression->DetachExpressions(p_min_start - 1, p_min_last - p_min_start + 3);
						expression->InsertExpression(ar, p_min_start - 1);
						changed = true;
					}
				} while (changed && expression->getExpressionCount() > 3);
				return true;
			}

			bool CExpressionBuilder::SearchOperand(const Token *token, const Token **target, const String &close) const
			{
				while (token)
				{
					switch (token->Type)
					{
					case TokenType::String:
					case TokenType::Integer:
					case TokenType::Float:
					case TokenType::Identifier:
						*target = token;
						return true;
					case TokenType::Operator:
						if (!close.empty() && token->Op->Name == close)
						{
							*target = nullptr;
							return true;
						}
						if (has(token->Op->Name, m_aCastOperators) || has(token->Op->Name, m_aCallOperators) || has(token->Op->Name, m_aBraceOperators))
						{
							*target = token;
							return true;
						}
						break;
					default: // Unknown, Group
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNEXPECTED_TOKEN,
								StringKeyValueArray{ StringKeyValue{ L"{token}", token->Value }, StringKeyValue{ L"{index}", ToString(uint64(token->Index)) } }
							);
						}
						return false;
					}
					token = Next(token, true);
				}
				*target = nullptr;
				return true;
			}

			bool CExpressionBuilder::AddPriorOperators(IExpression *operand, const Token *current_token, const Token *operand_token) const
			{
				// No prior operators
				if (current_token == operand_token)
					return true;
				std::vector<const Operator*> operators;
				const Token *next;
				while (current_token != operand_token)
				{
					if (!current_token->Op->Prior)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_OPERATOR_NOT_PRIOR,
								StringKeyValueArray{ StringKeyValue{ L"{name}", current_token->Op->Name }, StringKeyValue{ L"{index}", ToString(uint64(current_token->Index)) } }
							);
						}
						return false;
					}
					if ((next = Next(current_token, true)) && next != operand_token && !next->Op->AllowPrior)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_PRIOR_OPERATOR_NOT_ALLOWED,
								StringKeyValueArray{ StringKeyValue{ L"{name}", current_token->Op->Name }, StringKeyValue{ L"{index}", ToString(uint64(current_token->Index)) } }
							);
						}
						return false;
					}
					operators.push_back(current_token->Op);
					current_token = Next(current_token, true);
				}
				for (auto pos = operators.rbegin(); pos != operators.rend(); pos++)
					operand->AddPriorOperator(*pos);
				return true;
			}

			bool CExpressionBuilder::AddPosteriorOperators(IExpression *prev, const Token **token, const String &close) const
			{
				while (*token)
				{
					if (!close.empty() && (*token)->Type == TokenType::Operator && (*token)->Op->Name == close)
						return true;
					if (!(*token)->Op->Posterior)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_OPERATOR_NOT_POSTERIOR,
								StringKeyValueArray{ StringKeyValue{ L"{name}", (*token)->Op->Name }, StringKeyValue{ L"{index}", ToString(uint64((*token)->Index)) } }
							);
						}
						return false;
					}
					if (prev->getPosteriorOperatorCount() > 0 && !prev->getPosteriorOperator(prev->getPosteriorOperatorCount() - 1)->AllowPosterior)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_POSTERIOR_OPERATOR_NOT_ALLOWED,
								StringKeyValueArray{ StringKeyValue{ L"{name}", (*token)->Op->Name }, StringKeyValue{ L"{index}", ToString(uint64((*token)->Index)) } }
							);
						}
						return false;
					}
					prev->AddPosteriorOperator((*token)->Op);
					*token = Next(*token, true);
				}
				return true;
			}

			bool CExpressionBuilder::AddOperators(IExpression *prev, IExpression *operand, const Token *prev_next_token, const Token *operand_token, IExpression **op) const
			{
				*op = nullptr;
				if (prev_next_token == operand_token)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_EB_EXPECTED_OPERATOR_BETWEEN_OPERANDS,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(operand_token->Index)) } }
						);
					}
					return false;
				}
				const Token *first{ prev_next_token }, *last{ Prev(operand_token) };
				// Add posterior, not normal operators
				while (first <= last)
				{
					if (first->Op->Posterior && !first->Op->Normal)
					{
						if (prev->getPosteriorOperatorCount() > 0 && !prev->getPosteriorOperator(prev->getPosteriorOperatorCount() - 1)->AllowPosterior)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_POSTERIOR_OPERATOR_NOT_ALLOWED,
									StringKeyValueArray{ StringKeyValue{ L"{name}", first->Op->Name }, StringKeyValue{ L"{size}", ToString(uint64(first->Index)) } }
								);
							}
							return false;
						}
						prev->AddPosteriorOperator(first->Op);
						first = Next(first, true);
						continue;
					}
					break;
				}
				// Add prior, not normal operators
				while (last >= first)
				{
					if (last->Op->Prior && !last->Op->Normal)
					{
						if (operand->getPriorOperatorCount() > 0 && !operand->getPriorOperator(operand->getPriorOperatorCount() - 1)->AllowPrior)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_PRIOR_OPERATOR_NOT_ALLOWED,
									StringKeyValueArray{ StringKeyValue{ L"{name}", last->Op->Name }, StringKeyValue{ L"{size}", ToString(uint64(last->Index)) } }
								);
							}
							return false;
						}
						operand->AddPriorOperator(last->Op);
						last = Prev(last);
						continue;
					}
					break;
				}
				// first indicates first not added operator, last indicates last not added operator
				//if (last < first) // No normal operator between operands
				//	return true;
				if (last != first) // There are more than one operator left, try to add more prior and posterior ones using softer rules
				{
					// Add posterior operators, except last one
					while (first < last)
					{
						if (first->Op->Posterior)
						{
							if (prev->getPosteriorOperatorCount() > 0 && !prev->getPosteriorOperator(prev->getPosteriorOperatorCount() - 1)->AllowPosterior)
								break;
							prev->AddPosteriorOperator(first->Op);
							first = Next(first, true);
							continue;
						}
						break;
					}
					// Add prior operators, except last one
					while (last > first)
					{
						if (last->Op->Prior)
						{
							if (operand->getPriorOperatorCount() > 0 && !operand->getPriorOperator(operand->getPriorOperatorCount() - 1)->AllowPrior)
								break;
							operand->AddPriorOperator(last->Op);
							last = Prev(last);
							continue;
						}
						break;
					}
				}
				if (last == first) // Only one operator left. It should be normal one
				{
					if (!last->Op->Normal)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_EB_EXPECTED_NORMAL_OPERATOR,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(last->Index)) }, StringKeyValue{ L"{token}", ToString(uint64(last->Index)) } }
							);
						}
						return false;
					}
					*op = new CExpressionOperator(last->Index, last->Op);
					return true;
				}
				// Now can add any prior and posterior operators
				// Add posterior operators
				while (first <= last)
				{
					if (first->Op->Posterior)
					{
						if (prev->getPosteriorOperatorCount() > 0 && !prev->getPosteriorOperator(prev->getPosteriorOperatorCount() - 1)->AllowPosterior)
							break;
						prev->AddPosteriorOperator(first->Op);
						first = Next(first, true);
						continue;
					}
					break;
				}
				// Add prior operators
				while (last >= first)
				{
					if (last->Op->Prior)
					{
						if (operand->getPriorOperatorCount() > 0 && !operand->getPriorOperator(operand->getPriorOperatorCount() - 1)->AllowPrior)
							break;
						operand->AddPriorOperator(last->Op);
						last = Prev(last);
						continue;
					}
					break;
				}
				if (last == first) // Only one operator left. It should be normal one
				{
					if (!last->Op->Normal)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_EB_EXPECTED_NORMAL_OPERATOR,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(last->Index)) }, StringKeyValue{ L"{token}", last->Op->Name } }
							);
						}
						return false;
					}
					*op = new CExpressionOperator(last->Index, last->Op);
					return true;
				}
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						__FUNCTION__,
						__LINE__,
						ERROR_EB_EXPECTED_NORMAL_OPERATOR,
						StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(last->Index)) }, StringKeyValue{ L"{token}", last->Value } }
					);
				}
				return false;
			}

			PrefixType CExpressionBuilder::CalculatePrefixType(const String &prefix, const String &postfix, bool &is_raw, String &raw_separator) const
			{
				// Non-raw
				if (prefix.empty())
				{
					is_raw = false;
					raw_separator = L"";
					return PrefixType::None;
				}
				if (prefix == L"L")
				{
					is_raw = false;
					raw_separator = L"";
					return PrefixType::L;
				}
				if (prefix == L"U")
				{
					is_raw = false;
					raw_separator = L"";
					return PrefixType::U;
				}
				if (prefix == L"u")
				{
					is_raw = false;
					raw_separator = L"";
					return PrefixType::u;
				}
				if (prefix == L"u8")
				{
					is_raw = false;
					raw_separator = L"";
					return PrefixType::u8;
				}
				// Raw
				if (prefix == L"R")
				{
					is_raw = true;
					raw_separator = postfix;
					return PrefixType::None;
				}
				if (prefix == L"LR")
				{
					is_raw = true;
					raw_separator = postfix;
					return PrefixType::L;
				}
				if (prefix == L"UR")
				{
					is_raw = true;
					raw_separator = postfix;
					return PrefixType::U;
				}
				if (prefix == L"uR")
				{
					is_raw = true;
					raw_separator = postfix;
					return PrefixType::u;
				}
				if (prefix == L"u8R")
				{
					is_raw = true;
					raw_separator = postfix;
					return PrefixType::u8;
				}
				is_raw = false;
				return PrefixType::Custom;
			}

			PostfixType CExpressionBuilder::CalculatePostfixType(const String &postfix) const
			{
				if (postfix.empty())
					return PostfixType::None;
				if (postfix == L"F" || postfix == L"f")
					return PostfixType::F;
				size_t u_count{ 0 }, l_count{ 0 }, z_count{ 0 }, unknown{ 0 };
				for (auto c : postfix)
					if (c == L'U' || c == L'u')
						u_count++;
					else if (c == L'L' || c == L'l')
						l_count++;
					else if (c == L'Z' || c == L'z')
						z_count++;
					else
						unknown++;
				if (unknown > 0 || u_count > 1 || l_count > 2 || z_count > 1 || (z_count > 0 && l_count > 0))
					return PostfixType::Custom;
				if (u_count > 0)
				{
					if (l_count > 1)
						return PostfixType::ULL;
					if (l_count > 0)
						return PostfixType::UL;
					if (z_count > 0)
						return PostfixType::UZ;
					return PostfixType::U;
				}
				if (l_count > 1)
					return PostfixType::LL;
				if (l_count > 0)
					return PostfixType::L;
				return PostfixType::Z;
			}

			bool CExpressionBuilder::isKeyword(const String &value, const StringArray &keywords) const
			{
				if (!keywords.empty())
				{
					if (!m_bCaseSensitive)
					{
						String s{ ToLower(value) };
						return in(s, keywords);
					}
					return in(value, keywords);
				}
				return false;
			}

			bool CExpressionBuilder::isCast(const Token *token, size_t &operator_index) const
			{
				if (!has(token->Op->Name, m_aCastOperators, operator_index))
					return false;
				if (!(token = Next(token, true)))
					return false;
				if (token->Type != TokenType::Identifier)
					return false;
				if (isKeyword(token->Value, m_aDataTypesPrepared))
					return true;
				return false;
			}

			bool CExpressionBuilder::has(const String &value, const StringKeyValueArray &list) const
			{
				for (auto i : list)
					if (i.first == value)
						return true;
				return false;
			}

			bool CExpressionBuilder::has(const String &value, const StringKeyValueArray &list, size_t &index) const
			{
				for (index = 0; index < list.size(); index++)
					if (list[index].first == value)
						return true;
				return false;
			}

			bool CExpressionBuilder::MakeMemberAccess(IExpression **sequence) const
			{
				if (m_aMemberAccessOperators.empty() || !(*sequence))
					return true;
				switch ((*sequence)->Type)
				{
				case ExpressionType::Brace:
					if (!MakeMemberAccess(&cast<CExpressionBrace*>(*sequence)->Name))
						return false;
					return MakeMemberAccess(&cast<CExpressionBrace*>(*sequence)->Arguments);
				case ExpressionType::Call:
					if (!MakeMemberAccess(&cast<CExpressionCall*>(*sequence)->Name))
						return false;
					return MakeMemberAccess(&cast<CExpressionCall*>(*sequence)->Arguments);
				case ExpressionType::Cast:
					return MakeMemberAccess(&cast<CExpressionCast*>(*sequence)->Operand);
				case ExpressionType::Sequence:
					for (size_t i = 0; i < (*sequence)->getExpressionCount(); i++)
						if (!MakeMemberAccess(&cast<CExpression*>(*sequence)->m_aExpressions[i]))
							return false;
					break;
				case ExpressionType::Subscript:
					if (!MakeMemberAccess(&cast<CExpressionSubscript*>(*sequence)->Name))
						return false;
					return MakeMemberAccess(&cast<CExpressionSubscript*>(*sequence)->Arguments);
				default:
					return true;
				}
				if ((*sequence)->getExpressionCount() < 3)
					return true;
				bool changed;
				IExpression **name, *list{ nullptr };
				do // Move member access into call/brace/subscript names: "object . key[3]" becomes "(object . key)[3]"
				{
					changed = false;
					for (size_t i = 1; i < (*sequence)->getExpressionCount() - 1; i += 2)
						if (in(cast<CExpressionOperator*>((*sequence)->getExpression(i))->Op->Name, m_aMemberAccessOperators))
						{
							if ((*sequence)->getExpression(i - 1)->getPosteriorOperatorCount() > 0) // No additional operators between member parts are allowed
							{
								if (m_pErrorListener)
								{
									m_pErrorListener->NotifyOnError(
										__FUNCTION__,
										__LINE__,
										ERROR_EB_POSTERIOR_OPERATOR_BEFORE_MEMBER_ACCESS,
										StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64((*sequence)->getExpression(i - 1)->Index)) } }
									);
								}
								return false;
							}
							switch ((*sequence)->getExpression(i + 1)->Type)
							{
							case ExpressionType::Call:
								name = cast<CExpressionCall*>((*sequence)->getExpression(i + 1))->getInnerName();
								break;
							case ExpressionType::Brace:
								name = cast<CExpressionBrace*>((*sequence)->getExpression(i + 1))->getInnerName();
								break;
							case ExpressionType::Subscript:
								name = cast<CExpressionSubscript*>((*sequence)->getExpression(i + 1))->getInnerName();
								break;
							case ExpressionType::Identifier:
								if ((*sequence)->getExpression(i + 1)->getPriorOperatorCount() > 0) // No additional operators between member parts are allowed
								{
									if (m_pErrorListener)
									{
										m_pErrorListener->NotifyOnError(
											__FUNCTION__,
											__LINE__,
											ERROR_EB_PRIOR_OPERATOR_AFTER_MEMBER_ACCESS,
											StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64((*sequence)->getExpression(i + 1)->Index)) } }
										);
									}
									return false;
								}
								continue;
							default:
								if (m_pErrorListener)
								{
									m_pErrorListener->NotifyOnError(
										__FUNCTION__,
										__LINE__,
										ERROR_EB_UNEXPECTED_EXPRESSION_TYPE,
										StringKeyValueArray{
											StringKeyValue{ L"{type}", ExpressionTypeToString((*sequence)->getExpression(i + 1)->Type) },
											StringKeyValue{ L"{index}", ToString(uint64((*sequence)->getExpression(i + 1)->Index)) } }
									);
								}
								return false;
							}
							if (!name)
							{
								if (m_pErrorListener)
								{
									m_pErrorListener->NotifyOnError(
										__FUNCTION__,
										__LINE__,
										ERROR_EB_EXPECTED_EXPRESSION_NAME,
										StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64((*sequence)->getExpression(i + 1)->Index)) } }
									);
								}
								return false;
							}
							if (!in((*name)->Type, { ExpressionType::Identifier, ExpressionType::Sequence }))
							{
								if (m_pErrorListener)
								{
									m_pErrorListener->NotifyOnError(
										__FUNCTION__,
										__LINE__,
										ERROR_EB_UNEXPECTED_NAME_EXPRESSION_TYPE,
										StringKeyValueArray{ StringKeyValue{ L"{type}", ExpressionTypeToString((*name)->Type) }, StringKeyValue{ L"{index}", ToString(uint64((*name)->Index)) } }
									);
								}
								return false;
							}
							if ((*name)->getPriorOperatorCount() > 0) // No additional operators between member parts are allowed
							{
								if (m_pErrorListener)
								{
									m_pErrorListener->NotifyOnError(
										__FUNCTION__,
										__LINE__,
										ERROR_EB_PRIOR_OPERATOR_AFTER_MEMBER_ACCESS,
										StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64((*name)->Index)) } }
									);
								}
								return false;
							}
							if ((*name)->Type != ExpressionType::Sequence)
							{
								list = new CExpressionSequence((*name)->Index, false);
								list->AddExpression(*name);
								*name = list;
							}
							if (list->getExpression(0)->getPriorOperatorCount() > 0) // No additional operators between member parts are allowed
							{
								if (m_pErrorListener)
								{
									m_pErrorListener->NotifyOnError(
										__FUNCTION__,
										__LINE__,
										ERROR_EB_POSTERIOR_OPERATOR_BEFORE_MEMBER_ACCESS,
										StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(list->getExpression(0)->Index)) } }
									);
								}
								return false;
							}
							cast<CExpressionOperator*>((*sequence)->getExpression(i))->MemberAccess = true;
							(*name)->InsertExpression((*sequence)->getExpression(i), 0);
							(*name)->InsertExpression((*sequence)->getExpression(i - 1), 0);
							(*sequence)->DetachExpressions(i - 1, 2);
							changed = true;
							break;
						}
				} while (changed && (*sequence)->getExpressionCount() >= 3);
				// Move prior operators of call/brace/subscript names from first operator in sequence to sequence itself
				for (size_t i = 0; i < (*sequence)->getExpressionCount(); i += 2)
				{
					switch ((*sequence)->getExpression(i)->Type)
					{
					case ExpressionType::Call:
						name = cast<CExpressionCall*>((*sequence)->getExpression(i))->getInnerName();
						break;
					case ExpressionType::Brace:
						name = cast<CExpressionBrace*>((*sequence)->getExpression(i))->getInnerName();
						break;
					case ExpressionType::Subscript:
						name = cast<CExpressionSubscript*>((*sequence)->getExpression(i))->getInnerName();
						break;
					default:
						continue;
					}
					if (name && (*name)->Type == ExpressionType::Sequence && (*name)->getExpression(0)->getPriorOperatorCount() > 0)
					{
						if ((*sequence)->getExpression(i)->getPriorOperatorCount() > 0) // Call/Brace/Subscript already has prior operator
						{
								if (m_pErrorListener)
								{
									m_pErrorListener->NotifyOnError(
										__FUNCTION__,
										__LINE__,
										ERROR_EB_PRIOR_OPERATOR_AFTER_MEMBER_ACCESS,
										StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64((*sequence)->getExpression(i)->Index)) } }
									);
								}
							return false;
						}
						for (size_t j = 0; j < (*name)->getExpression(0)->getPriorOperatorCount(); j++)
							(*sequence)->getExpression(i)->AddPriorOperator((*name)->getExpression(0)->getPriorOperator(j));
						(*name)->getExpression(0)->DeletePriorOperators();
					}
				}
				// If there is only one entity left in the sequence, we can use this entity instead of sequence
				if ((*sequence)->getExpressionCount() == 1)
				{
					list = (*sequence)->getExpression(0);
					for (size_t i = 0; i < (*sequence)->getPriorOperatorCount(); i++)
						list->AddPriorOperator((*sequence)->getPriorOperator(i));
					for (size_t i = 0; i < (*sequence)->getPosteriorOperatorCount(); i++)
						list->AddPosteriorOperator((*sequence)->getPosteriorOperator(i));
					(*sequence)->DetachExpressions();
					(*sequence)->Release();
					*sequence = list;
					switch ((*sequence)->Type)
					{
					case ExpressionType::Call:
						name = cast<CExpressionCall*>(*sequence)->getInnerName();
						break;
					case ExpressionType::Brace:
						name = cast<CExpressionBrace*>(*sequence)->getInnerName();
						break;
					case ExpressionType::Subscript:
						name = cast<CExpressionSubscript*>(*sequence)->getInnerName();
						break;
					default:
						name = nullptr;
						break;
					}
					if (name && (*name)->Type == ExpressionType::Sequence)
					{
						for (size_t i = 0; i < (*name)->getExpression(0)->getPriorOperatorCount(); i++)
							(*name)->AddPriorOperator((*name)->getExpression(0)->getPriorOperator(i));
						(*name)->getExpression(0)->DeletePriorOperators();
					}
					return true;
				}
				// Multiple elements left in sequence. Move left-most prior operators out of member access sequence. "-object . key" becomes "-(object . key)"
				size_t i{ 1 }, start{ 0 }, end;
				while (i < (*sequence)->getExpressionCount() - 1)
				{
					if (in(cast<CExpressionOperator*>((*sequence)->getExpression(i))->Op->Name, m_aMemberAccessOperators))
					{
						cast<CExpressionOperator*>((*sequence)->getExpression(i))->MemberAccess = true;
						if (start == 0)
							start = i;
						end = i;
						i += 2;
						continue;
					}
					if (start > 0 && ((*sequence)->getExpression(start - 1)->getPriorOperatorCount() > 0 || (*sequence)->getExpression(end + 1)->getPosteriorOperatorCount() > 0))
					{
						list = new CExpressionSequence((*sequence)->getExpression(start - 1)->Index, false);
						for (size_t j = start - 1; j <= end + 1; j++)
							list->AddExpression((*sequence)->getExpression(j));
						// Move prior operators to list
						for (size_t j = 0; j < (*list)[0]->getPriorOperatorCount(); j++)
							list->AddPriorOperator((*list)[0]->getPriorOperator(j));
						(*list)[0]->DeletePriorOperators();
						// Move posterior operators to list
						for (size_t j = 0; j < (*list)[list->getExpressionCount() - 1]->getPosteriorOperatorCount(); j++)
							list->AddPosteriorOperator((*list)[list->getExpressionCount() - 1]->getPosteriorOperator(j));
						(*list)[list->getExpressionCount() - 1]->DeletePosteriorOperators();
						// Update sequence
						(*sequence)->DetachExpressions(start - 1, end - start + 3);
						(*sequence)->InsertExpression(list, start - 1);
						start = 0;
						continue;
					}
					start = 0;
					i += 2;
				}
				if (start > 0)
				{
					list = new CExpressionSequence((*sequence)->getExpression(start - 1)->Index, false);
					for (size_t j = start - 1; j <= end + 1; j++)
						list->AddExpression((*sequence)->getExpression(j));
					for (size_t j = 0; j < (*list)[0]->getPriorOperatorCount(); j++)
						list->AddPriorOperator((*list)[0]->getPriorOperator(j));
					(*list)[0]->DeletePriorOperators();
					for (size_t j = 0; j < (*list)[list->getExpressionCount() - 1]->getPosteriorOperatorCount(); j++)
						list->AddPosteriorOperator((*list)[list->getExpressionCount() - 1]->getPosteriorOperator(j));
					(*list)[list->getExpressionCount() - 1]->DeletePosteriorOperators();
					(*sequence)->DetachExpressions(start - 1, end - start + 3);
					(*sequence)->InsertExpression(list, start - 1);
				}
				if ((*sequence)->getExpressionCount() == 1)
				{
					list = (*sequence)->getExpression(0);
					(*sequence)->DetachExpressions();
					(*sequence)->Release();
					*sequence = list;
				}
				return true;
			}

			bool CExpressionBuilder::MakeTernary(IExpression *sequence) const
			{
				if (m_sTernaryOperator1.empty() || m_sTernaryOperator2.empty() || !sequence)
					return true;
				switch (sequence->Type)
				{
				case ExpressionType::Brace:
					if (!MakeTernary(cast<CExpressionBrace*>(sequence)->Name))
						return false;
					return MakeTernary(cast<CExpressionBrace*>(sequence)->Arguments);
				case ExpressionType::Call:
					if (!MakeTernary(cast<CExpressionCall*>(sequence)->Name))
						return false;
					return MakeTernary(cast<CExpressionCall*>(sequence)->Arguments);
				case ExpressionType::Cast:
					return MakeTernary(cast<CExpressionCast*>(sequence)->Operand);
				case ExpressionType::Sequence:
					for (size_t i = 0; i < sequence->getExpressionCount(); i++)
						if (!MakeTernary((*sequence)[i]))
							return false;
					break;
				case ExpressionType::Subscript:
					if (!MakeTernary(cast<CExpressionSubscript*>(sequence)->Name))
						return false;
					return MakeTernary(cast<CExpressionSubscript*>(sequence)->Arguments);
				default:
					return true;
				}
				if (sequence->getExpressionCount() < 5)
					return true;
				if (sequence->getExpressionCount() > 5)
				{
					bool changed;
					do
					{
						changed = false;
						CExpressionOperator *op1, *op2;
						CExpressionSequence *ar;
						for (size_t i = sequence->getExpressionCount() - 2; i >= 3; i -= 2)
						{
							op1 = cast<CExpressionOperator*>((*sequence)[i - 2]);
							if (op1->Op->Name != m_sTernaryOperator1)
								continue;
							op2 = cast<CExpressionOperator*>((*sequence)[i]);
							if (op2->Op->Name != m_sTernaryOperator2)
								continue;
							ar = new CExpressionSequence((*sequence)[i - 3]->Index, true);
							ar->AddExpression((*sequence)[i - 3]);
							ar->AddExpression((*sequence)[i - 2]);
							ar->AddExpression((*sequence)[i - 1]);
							ar->AddExpression((*sequence)[i]);
							ar->AddExpression((*sequence)[i + 1]);
							sequence->DetachExpressions(i - 3, 5);
							sequence->InsertExpression(ar, i - 3);
							changed = true;
							break;
						}
					} while (changed && sequence->getExpressionCount() >= 7);
				}
				// Mark remaining sequence as ternary if it is the one
				if (sequence->getExpressionCount() == 5 &&
					!cast<CExpressionSequence*>(sequence)->Ternary &&
					cast<CExpressionOperator*>((*sequence)[1])->Op->Name == m_sTernaryOperator1 &&
					cast<CExpressionOperator*>((*sequence)[3])->Op->Name == m_sTernaryOperator2)
					*const_cast<bool*>(&cast<CExpressionSequence*>(sequence)->Ternary) = true;
				return true;
			}
		#pragma endregion

		#pragma region Decode
			bool CExpressionBuilder::DecodeSequence(const Token **token, IExpression **target, const String &close) const
			{
				*target = nullptr;
				const Token *current_token{ *token }, *operand_token, *next_token, *prev_next_token;
				IExpression *operand, *prev{ nullptr }, *op;
				while (current_token)
				{
					if (!close.empty() && current_token->Type == TokenType::Operator && current_token->Op->Name == close)
						break;
					// Search token where operand starts
					if (!SearchOperand(current_token, &operand_token, close))
					{
						if (*target)
						{
							(*target)->Release();
							*target = nullptr;
						}
						return false;
					}
					// Check if no more operands left
					if (!operand_token)
						break;
					// Make operand
					if (!DecodeOperand(operand_token, &operand, &next_token))
					{
						if (prev)
							prev->Release();
						if (*target)
						{
							(*target)->Release();
							*target = nullptr;
						}
						return false;
					}
					// Previous operand exists
					if (prev)
					{
						if (!AddOperators(prev, operand, prev_next_token, operand_token, &op))
						{
							prev->Release();
							operand->Release();
							if (*target)
							{
								(*target)->Release();
								*target = nullptr;
							}
							return false;
						}
						if (!(*target))
							*target = new CExpressionSequence(prev->Index, false);
						(*target)->AddExpression(prev);
						(*target)->AddExpression(op);
						prev = operand;
						prev_next_token = next_token;
						current_token = next_token;
						continue;
					}
					// No previous operand yet
					prev = operand;
					prev_next_token = next_token;
					if (!AddPriorOperators(prev, current_token, operand_token))
					{
						prev->Release();
						if (*target)
						{
							(*target)->Release();
							*target = nullptr;
						}
						return false;
					}
					current_token = next_token;
				}
				if (!prev)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_EB_EXPECTED_OPERAND,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64((*token)->Index)) } }
						);
					}
					return false;
				}
				if (!AddPosteriorOperators(prev, &prev_next_token, close))
				{
					prev->Release();
					if (*target)
					{
						(*target)->Release();
						*target = nullptr;
					}
					return false;
				}
				if (*target)
					(*target)->AddExpression(prev);
				else
					*target = prev;
				*token = prev_next_token;
				return true;
			}

			bool CExpressionBuilder::DecodeOperand(const Token *token, IExpression **target, const Token **next_token) const
			{
				*target = nullptr;
				size_t operator_index;
				switch (token->Type)
				{
				case TokenType::Integer:
					return DecodeInteger(token, target, next_token);
				case TokenType::Float:
					return DecodeFloat(token, target, next_token);
				case TokenType::String:
					return DecodeString(token, target, next_token);
				case TokenType::Identifier:
					if (isKeyword(token->Value, m_aTrueKeywordsPrepared))
						return DecodeTrue(token, target, next_token);
					if (isKeyword(token->Value, m_aFalseKeywordsPrepared))
						return DecodeFalse(token, target, next_token);
					if (isKeyword(token->Value, m_aNullKeywordsPrepared))
						return DecodeNull(token, target, next_token);
					return DecodeIdentifier(token, target, next_token);
				case TokenType::Operator:
					if (isCast(token, operator_index))
						return DecodeCast(token, target, next_token, nullptr, operator_index);
					if (has(token->Op->Name, m_aCallOperators, operator_index))
						return DecodeCall(token, target, next_token, nullptr, operator_index);
					if (has(token->Op->Name, m_aBraceOperators, operator_index))
						return DecodeBrace(token, target, next_token, nullptr, operator_index);
				default:
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_UNEXPECTED_TOKEN,
							StringKeyValueArray{ StringKeyValue{ L"{token}", token->Value }, StringKeyValue{ L"{index}", ToString(uint64(token->Index)) } }
						);
					}
					return false;
				}
			}

			bool CExpressionBuilder::DecodeInteger(const Token *token, IExpression **target, const Token **next_token) const
			{
				*target = nullptr;
				ReleasablePtr<CExpressionInteger> result{ new CExpressionInteger(token->Index, token->Integer, token->Postfix, CalculatePostfixType(token->Postfix), token->Base, L"") };
				const Token *next{ token + 1 };
				token = Next(token, true);
				if (result->Postfix == L"" && token && token == next && token->Type == TokenType::Identifier)
				{
					if (!m_bAllowUserDefinedLiterals)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_EB_USER_DEFINED_LITERALS_NOT_ALLOWED,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(token->Index)) } }
							);
						}
						return false;
					}
					result->UserDefinedLiteral = token->Value;
					token = Next(token, true);
				}
				*target = result.move();
				*next_token = token;
				return true;
			}

			bool CExpressionBuilder::DecodeFloat(const Token *token, IExpression **target, const Token **next_token) const
			{
				*target = nullptr;
				ReleasablePtr<CExpressionFloat> result{ new CExpressionFloat(token->Index, token->Float, token->Postfix, CalculatePostfixType(token->Postfix), token->Base, L"") };
				token = Next(token, true);
				if (result->Postfix == L"" && token && token->Type == TokenType::Identifier)
				{
					if (!m_bAllowUserDefinedLiterals)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_EB_USER_DEFINED_LITERALS_NOT_ALLOWED,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(token->Index)) } }
							);
						}
						return false;
					}
					result->UserDefinedLiteral = token->Value;
					token = Next(token, true);
				}
				*target = result.move();
				*next_token = token;
				return true;
			}

			bool CExpressionBuilder::DecodeString(const Token *token, IExpression **target, const Token **next_token) const
			{
				*target = nullptr;
				ReleasablePtr<CExpressionString> result{ new CExpressionString(token->Index, L"", token->Prefix, PrefixType::None, token->Op, false, L"", L"") };
				PrefixType prefix_type;
				bool raw;
				String raw_separator;
				const Token *next{ nullptr };
				while (token && token->Type == TokenType::String)
				{
					result->Value += token->Value;
					prefix_type = CalculatePrefixType(token->Prefix, token->Postfix, raw, raw_separator);
					if (prefix_type != PrefixType::None)
					{
						if (result->TypeOfPrefix != PrefixType::None && prefix_type != result->TypeOfPrefix)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_EB_STRING_PREFIX_MISMATCH,
									StringKeyValueArray{
										StringKeyValue{ L"{1}", PrefixTypeToString(result->TypeOfPrefix, result->Prefix) },
										StringKeyValue{ L"{2}", PrefixTypeToString(prefix_type, token->Prefix) },
										StringKeyValue{ L"{index}", ToString(uint64(token->Index)) } }
								);
							}
							return false;
						}
						if (prefix_type == PrefixType::Custom && !result->Prefix.empty() && token->Prefix != result->Prefix)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_EB_STRING_PREFIX_MISMATCH,
									StringKeyValueArray{
										StringKeyValue{ L"{1}", PrefixTypeToString(result->TypeOfPrefix, result->Prefix) },
										StringKeyValue{ L"{2}", PrefixTypeToString(prefix_type, token->Prefix) },
										StringKeyValue{ L"{index}", ToString(uint64(token->Index)) } }
								);
							}
							return false;
						}
						result->TypeOfPrefix = prefix_type;
					}
					if (raw && !result->Raw)
						result->Raw = true;
					if (result->RawSeparator.length() < raw_separator.length())
						result->RawSeparator = raw_separator;
					next = token + 1;
					token = Next(token, true);
					if (!m_bAllowStringConcatenation)
						break;
				}
				if (token && token == next && token->Type == TokenType::Identifier)
				{
					if (!m_bAllowUserDefinedLiterals)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_EB_USER_DEFINED_LITERALS_NOT_ALLOWED,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(token->Index)) } }
							);
						}
						return false;
					}
					result->UserDefinedLiteral = token->Value;
					token = Next(token, true);
				}
				*target = result.move();
				*next_token = token;
				return true;
			}

			bool CExpressionBuilder::DecodeTrue(const Token *token, IExpression **target, const Token **next_token) const
			{
				*target = new CExpressionBool(token->Index, true);
				*next_token = Next(token, true);
				return true;
			}

			bool CExpressionBuilder::DecodeFalse(const Token *token, IExpression **target, const Token **next_token) const
			{
				*target = new CExpressionBool(token->Index, false);
				*next_token = Next(token, true);
				return true;
			}

			bool CExpressionBuilder::DecodeNull(const Token *token, IExpression **target, const Token **next_token) const
			{
				*target = new CExpressionNull(token->Index, token->Value);
				*next_token = Next(token, true);
				return true;
			}

			bool CExpressionBuilder::DecodeIdentifier(const Token *token, IExpression **target, const Token **next_token) const
			{
				*target = nullptr;
				ReleasablePtr<CExpressionIdentifier> result{ new CExpressionIdentifier(token->Index, token->Value) };
				token = Next(token, true);
				if (token && token->Type == TokenType::Operator)
				{
					size_t operator_index;
					if (has(token->Op->Name, m_aCallOperators, operator_index))
					{
						if (!DecodeCall(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					if (has(token->Op->Name, m_aBraceOperators, operator_index))
					{
						if (!DecodeBrace(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					if (has(token->Op->Name, m_aSubscriptOperators, operator_index))
					{
						if (!DecodeSubscript(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
				}
				*next_token = token;
				*target = result.move();
				return true;
			}

			bool CExpressionBuilder::DecodeCast(const Token *token, IExpression **target, const Token **next_token, IExpression *name, size_t operator_index) const
			{
				*target = nullptr;
				ReleasablePtr<CExpressionCast> result{ new CExpressionCast(token->Index, token->Op, name, L"", nullptr) };
				token = Next(token, true); // Skip "("
				result->DataType = token->Value;
				if (!(token = Next(token, true)))
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_UNEXPECTED_END
						);
					}
					return false;
				}
				if (token->Type != TokenType::Operator || token->Op->Name != m_aCastOperators[operator_index].second)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_OPERATOR_NAME,
							StringKeyValueArray{
								StringKeyValue{ L"{name}", m_aCastOperators[operator_index].second },
								StringKeyValue{ L"{index}", ToString(uint64(token->Index)) },
								StringKeyValue{ L"{token}", token->Value } }
						);
					}
					return false;
				}
				if (!(token = Next(token, true)))
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_UNEXPECTED_END
						);
					}
					return false;
				}
				if (token->Type == TokenType::Operator)
				{
					if (isCast(token, operator_index))
					{
						if (!DecodeCast(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					if (has(token->Op->Name, m_aCallOperators, operator_index))
					{
						if (!DecodeCall(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					if (has(token->Op->Name, m_aBraceOperators, operator_index))
					{
						if (!DecodeBrace(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					return false;
				}
				if (!DecodeOperand(token, &result->Operand, next_token))
					return false;
				*target = result.move();
				return true;
			}

			bool CExpressionBuilder::DecodeCall(const Token *token, IExpression **target, const Token **next_token, IExpression *name, size_t operator_index) const
			{
				*target = nullptr;
				ReleasablePtr<CExpressionCall> result{ new CExpressionCall(token->Index, token->Op, name, nullptr) };
				if (!(token = Next(token, true)))
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_UNEXPECTED_END
						);
					}
					return false;
				}
				if (token->Type != TokenType::Operator || token->Op->Name != m_aCallOperators[operator_index].second)
				{
					if (!DecodeSequence(&token, &result->Arguments, m_aCallOperators[operator_index].second))
						return false;
				}
				token = Next(token, true);
				if (token && token->Type == TokenType::Operator)
				{
					if (has(token->Op->Name, m_aCallOperators, operator_index))
					{
						if (!DecodeCall(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					if (has(token->Op->Name, m_aBraceOperators, operator_index))
					{
						if (!DecodeBrace(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					if (has(token->Op->Name, m_aSubscriptOperators, operator_index))
					{
						if (!DecodeSubscript(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
				}
				*next_token = token;
				*target = result.move();
				return true;
			}

			bool CExpressionBuilder::DecodeBrace(const Token *token, IExpression **target, const Token **next_token, IExpression *name, size_t operator_index) const
			{
				*target = nullptr;
				ReleasablePtr<CExpressionBrace> result{ new CExpressionBrace(token->Index, token->Op, name, nullptr) };
				if (!(token = Next(token, true)))
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_UNEXPECTED_END
						);
					}
					return false;
				}
				if (token->Type != TokenType::Operator || token->Op->Name != m_aBraceOperators[operator_index].second)
				{
					if (!DecodeSequence(&token, &result->Arguments, m_aBraceOperators[operator_index].second))
						return false;
				}
				token = Next(token, true);
				if (token && token->Type == TokenType::Operator)
				{
					if (has(token->Op->Name, m_aCallOperators, operator_index))
					{
						if (!DecodeCall(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					if (has(token->Op->Name, m_aBraceOperators, operator_index))
					{
						if (!DecodeBrace(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					if (has(token->Op->Name, m_aSubscriptOperators, operator_index))
					{
						if (!DecodeSubscript(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
				}
				*next_token = token;
				*target = result.move();
				return true;
			}

			bool CExpressionBuilder::DecodeSubscript(const Token *token, IExpression **target, const Token **next_token, IExpression *name, size_t operator_index) const
			{
				*target = nullptr;
				ReleasablePtr<CExpressionSubscript> result{ new CExpressionSubscript(token->Index, token->Op, name, nullptr) };
				if (!(token = Next(token, true)))
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_UNEXPECTED_END
						);
					}
					return false;
				}
				if (token->Type != TokenType::Operator || token->Op->Name != m_aSubscriptOperators[operator_index].second)
				{
					if (!DecodeSequence(&token, &result->Arguments, m_aSubscriptOperators[operator_index].second))
						return false;
				}
				token = Next(token, true);
				if (token && token->Type == TokenType::Operator)
				{
					if (has(token->Op->Name, m_aCallOperators, operator_index))
					{
						if (!DecodeCall(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					if (has(token->Op->Name, m_aBraceOperators, operator_index))
					{
						if (!DecodeBrace(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
					if (has(token->Op->Name, m_aSubscriptOperators, operator_index))
					{
						if (!DecodeSubscript(token, target, next_token, result.move(), operator_index))
							return false;
						return true;
					}
				}
				*next_token = token;
				*target = result.move();
				return true;
			}
		#pragma endregion
		}
	}
}