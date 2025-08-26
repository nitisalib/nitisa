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
			CExpressionRunner::CExpressionRunner(const bool with_function_factory):
				script::CExpressionRunner(),
				m_pDefaultFunctionFactory{ with_function_factory ? new CFunctionFactory() : nullptr },
				m_pFunctionFactory{ nullptr }
			{

			}

			void CExpressionRunner::BeforeRelease()
			{
				if (m_pDefaultFunctionFactory)
					m_pDefaultFunctionFactory->Release();
			}
		#pragma endregion

		#pragma region IExpressionRunner getters
			IFunctionFactory *CExpressionRunner::getFunctionFactory()
			{
				return m_pFunctionFactory;
			}
		#pragma endregion

		#pragma region IExpressionRunner setters
			bool CExpressionRunner::setFunctionFactory(IFunctionFactory *factory)
			{
				if (factory != m_pFunctionFactory)
				{
					m_pFunctionFactory = factory;
					return true;
				}
				return false;
			}
		#pragma endregion

		#pragma region IExpressionRunner methods
			bool CExpressionRunner::Prepare(IExpression *expression)
			{
				if (!expression)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_EXPECTED_EXPRESSION
						);
					}
					return false;
				}
				if (m_pFunction)
				{
					m_pFunction->Release();
					m_pFunction = nullptr;
				}
				IFunction *modify;
				if (!MakeOperand(expression, &m_pFunction, &modify))
					return false;
				return true;
			}

			bool CExpressionRunner::Run()
			{
				m_sResult.clear();
				if (!m_pFunction)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_NOT_PREPARED
						);
					}
					return false;
				}
				if (!m_pFunction->Run())
					return false;
				m_sResult = *m_pFunction->Result;
				return true;
			}
		#pragma endregion

		#pragma region Helpers
			bool CExpressionRunner::CreateFunction(const String &name, const IFunction::Arguments &arguments, IFunction **target, IFunction *modify)
			{
				*target = nullptr;
				IFunction *result{ nullptr };
				if (m_pDefaultFunctionFactory)
					result = m_pDefaultFunctionFactory->Create(name, m_pErrorListener, arguments, modify);
				if (!result && m_pFunctionFactory)
					result = m_pFunctionFactory->Create(name, m_pErrorListener, arguments, modify);
				if (!result)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_FUNCTION_NOT_FOUND,
							StringKeyValueArray{ StringKeyValue{ L"{name}", name }, StringKeyValue{ L"{count}", ToString(uint64(arguments.size()) + (modify ? 1 : 0)) } }
						);
					}
					return false;
				}
				*target = result;
				return true;
			}

			void CExpressionRunner::FreeArguments(IFunction::Arguments &arguments)
			{
				for (auto a : arguments)
					a->Release();
				arguments.clear();
			}

			bool CExpressionRunner::Prepare(const String &source)
			{
				CTokenizer tokenizer{ source };
				IExpression *expression;
				CExpressionBuilder builder;
				builder.ErrorListener = m_pErrorListener;
				if (!builder.Build(&tokenizer, &expression))
					return false;
				if (!expression)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_EXPECTED_EXPRESSION
						);
					}
					return false;
				}
				bool result{ Prepare(expression) };
				expression->Release();
				return result;
			}
		#pragma endregion

		#pragma region Make
			bool CExpressionRunner::MakeOperand(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = nullptr;
				switch (expression->Type)
				{
				case ExpressionType::Bool:
					return MakeBool(expression, target, modify);
				case ExpressionType::Brace:
					return MakeBrace(expression, target, modify);
				case ExpressionType::Call:
					return MakeCall(expression, target, modify);
				case ExpressionType::Cast:
					return MakeCast(expression, target, modify);
				case ExpressionType::Float:
					return MakeFloat(expression, target, modify);
				case ExpressionType::Identifier:
					return MakeVariable(expression, target, modify);
				case ExpressionType::Integer:
					return MakeInteger(expression, target, modify);
				case ExpressionType::Null:
					return MakeNull(expression, target, modify);
				case ExpressionType::Sequence:
					return MakeSequence(expression, target, modify);
				case ExpressionType::String:
					return MakeString(expression, target, modify);
				case ExpressionType::Subscript:
					return MakeSubscript(expression, target, modify);
				default:
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_UNSUPPORTED_EXPRESSION_TYPE,
							StringKeyValueArray{ StringKeyValue{ L"{type}", ExpressionTypeToString(expression->Type) }, StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
						);
					}
					return false;
				}
			}

			bool CExpressionRunner::MakeOperators(IExpression *expression, IFunction **target)
			{
				IFunction *f, *modify{ *target };
				for (size_t i = 0; i < expression->getPriorOperatorCount(); i++)
				{
					if (!CreateFunction(expression->getPriorOperator(i)->Name + L"x", IFunction::Arguments{ *target }, &f, modify))
					{
						(*target)->Release();
						*target = nullptr;
						return false;
					}
					*target = f;
				}
				for (size_t i = 0; i < expression->getPosteriorOperatorCount(); i++)
				{
					if (!CreateFunction(L"x" + expression->getPosteriorOperator(i)->Name, IFunction::Arguments { *target }, &f, modify))
					{
						(*target)->Release();
						*target = nullptr;
						return false;
					}
					*target = f;
				}
				return true;
			}

			bool CExpressionRunner::MakeBool(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = *modify = new CFunctionLiteral(m_pErrorListener, cast<CExpressionBool*>(expression)->Value);
				return MakeOperators(expression, target);
			}

			bool CExpressionRunner::MakeNull(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = *modify = new CFunctionLiteral(m_pErrorListener, Variable{ });
				return MakeOperators(expression, target);
			}

			bool CExpressionRunner::MakeInteger(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = *modify = new CFunctionLiteral(m_pErrorListener, (int64)cast<CExpressionInteger*>(expression)->Value);
				return MakeOperators(expression, target);
			}

			bool CExpressionRunner::MakeFloat(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = *modify = new CFunctionLiteral(m_pErrorListener, cast<CExpressionFloat*>(expression)->Value);
				return MakeOperators(expression, target);
			}

			bool CExpressionRunner::MakeString(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = *modify = new CFunctionLiteral(m_pErrorListener, cast<CExpressionString*>(expression)->Value);
				return MakeOperators(expression, target);
			}

			bool CExpressionRunner::MakeVariable(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = nullptr;
				Variable *v{ getVariable(cast<CExpressionIdentifier*>(expression)->Name) };
				if (!v)
				{
					m_aVariables.push_back({ cast<CExpressionIdentifier*>(expression)->Name, new Variable() });
					v = m_aVariables[m_aVariables.size() - 1].second;
				}
				*target = *modify = new CFunctionVariable(m_pErrorListener, *v);
				return MakeOperators(expression, target);
			}

			bool CExpressionRunner::MakeIdentifier(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = nullptr;
				if (expression->getPriorOperatorCount() > 0)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_IDENTIFIER_WITH_PRIOR_OPERATORS,
							StringKeyValueArray{ StringKeyValue{ L"{name}", cast<CExpressionIdentifier*>(expression)->Name }, StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
						);
					}
					return false;
				}
				if (expression->getPosteriorOperatorCount() > 0)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_IDENTIFIER_WITH_POSTERIOR_OPERATORS,
							StringKeyValueArray{ StringKeyValue{ L"{name}", cast<CExpressionIdentifier*>(expression)->Name }, StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
						);
					}
					return false;
				}
				*target = *modify = new CFunctionIdentifier(m_pErrorListener, cast<CExpressionIdentifier*>(expression)->Name);
				return true;
			}

			bool CExpressionRunner::MakeBrace(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = nullptr;
				CExpressionBrace *brace{ cast<CExpressionBrace*>(expression) };
				if (brace->Name)
				{
					if (brace->Name->Type != ExpressionType::Cast)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_BRACE_NAME_EXPRESSION_TYPE,
								StringKeyValueArray{ StringKeyValue{ L"{type}", ExpressionTypeToString(brace->Name->Type) }, StringKeyValue{ L"{index}", ToString(uint64(brace->Name->Index)) } }
							);
						}
						return false;
					}
					if (brace->Name->getPriorOperatorCount() > 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_BRACE_NAME_WITH_PRIOR_OPERATORS,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
							);
						}
						return false;
					}
					if (brace->Name->getPosteriorOperatorCount() > 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_BRACE_NAME_WITH_POSTERIOR_OPERATORS,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
							);
						}
						return false;
					}
				}
				if (!brace->Arguments)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_EXPECTED_BRACE_ARGUMENTS,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(brace->Index)) } }
						);
					}
					return false;
				}
				if (brace->Arguments->getExpressionCount() > 0)
				{
					if (brace->Arguments->getPriorOperatorCount() > 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_BRACE_ARGUMENTS_WITH_PRIOR_OPERATORS,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(brace->Arguments->Index)) } }
							);
						}
						return false;
					}
					if (brace->Arguments->getPosteriorOperatorCount() > 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_BRACE_ARGUMENTS_WITH_POSTERIOR_OPERATORS,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(brace->Arguments->Index)) } }
							);
						}
						return false;
					}
					if (brace->Arguments->getExpressionCount() % 2 == 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_EXPECTED_ODD_ARGUMENT_COUNT,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(brace->Arguments)) } }
							);
						}
						return false;
					}
					for (size_t i = 0; i < brace->Arguments->getExpressionCount(); i += 2)
						if (brace->Arguments->getExpression(i)->Type == ExpressionType::Operator)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_ER_EXPECTED_OPERAND,
									StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(brace->Arguments->getExpression(i)->Index)) } }
								);
							}
							return false;
						}
					for (size_t i = 1; i < brace->Arguments->getExpressionCount(); i += 2)
					{
						if (brace->Arguments->getExpression(i)->Type != ExpressionType::Operator)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_ER_EXPECTED_OPERATOR,
									StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(brace->Arguments->getExpression(i)->Index)) } }
								);
							}
							return false;
						}
						if (cast<CExpressionOperator*>(brace->Arguments->getExpression(i))->Op->Name != cast<CExpressionOperator*>(brace->Arguments->getExpression(1))->Op->Name)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_EXPECTED_OPERATOR_NAME,
									StringKeyValueArray{
										StringKeyValue{ L"{name}", cast<CExpressionOperator*>(brace->Arguments->getExpression(1))->Op->Name },
										StringKeyValue{ L"{index}", ToString(uint64(brace->Arguments->getExpression(i)->Index)) },
										StringKeyValue{ L"{token}", cast<CExpressionOperator*>(brace->Arguments->getExpression(i))->Op->Name } }
								);
							}
							return false;
						}
					}
				}
				IFunction::Arguments arguments;
				IFunction *argument;
				if (brace->Arguments->getExpressionCount() > 0)
				{
					for (size_t i = 0; i < brace->Arguments->getExpressionCount(); i += 2)
					{
						if (!MakeOperand(brace->Arguments->getExpression(i), &argument, modify))
						{
							FreeArguments(arguments);
							return false;
						}
						arguments.push_back(argument);
					}
				}
				else
				{
					if (!MakeOperand(brace->Arguments, &argument, modify))
						return false;
					arguments.push_back(argument);
				}
				IFunction *operand;
				if (!CreateFunction(brace->Op->Name + brace->Op->Close, arguments, &operand, nullptr))
				{
					FreeArguments(arguments);
					return false;
				}
				if (brace->Name && !MakeCast(brace->Name, target, modify, operand))
				{
					operand->Release();
					return false;
				}
				else
					*target = *modify = operand;
				return MakeOperators(expression, target);
			}

			bool CExpressionRunner::MakeCall(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = nullptr;
				CExpressionCall *call{ cast<CExpressionCall*>(expression) };
				if (!call->Name || call->Name->Type == ExpressionType::Cast)
				{
					if (!MakeOperand(call->Arguments, target, modify))
						return false;
					if (call->Name)
					{
						IFunction *t{ *target };
						if (!MakeCast(call->Name, &t, modify, *target))
						{
							(*target)->Release();
							return false;
						}
						*target = t;
					}
					return MakeOperators(expression, target);
				}
				if (call->Name->Type != ExpressionType::Identifier)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_CALL_NAME_EXPRESSION_TYPE,
							StringKeyValueArray{ StringKeyValue{ L"{type}", ExpressionTypeToString(call->Name->Type) }, StringKeyValue{ L"{index}", ToString(uint64(call->Name->Index)) } }
						);
					}
					return false;
				}
				if (call->Name->getPriorOperatorCount() > 0)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_CALL_NAME_WITH_PRIOR_OPERATORS,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
						);
					}
					return false;
				}
				if (call->Name->getPosteriorOperatorCount() > 0)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_CALL_NAME_WITH_POSTERIOR_OPERATORS,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
						);
					}
					return false;
				}
				if (call->Arguments && call->Arguments->getExpressionCount() > 0)
				{
					if (call->Arguments->getPriorOperatorCount() > 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_CALL_ARGUMENTS_WITH_PRIOR_OPERATORS,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(call->Arguments->Index)) } }
							);
						}
						return false;
					}
					if (call->Arguments->getPosteriorOperatorCount() > 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_CALL_ARGUMENTS_WITH_POSTERIOR_OPERATORS,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(call->Arguments->Index)) } }
							);
						}
						return false;
					}
					if (call->Arguments->getExpressionCount() % 2 == 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_EXPECTED_ODD_ARGUMENT_COUNT,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(call->Arguments->Index)) } }
							);
						}
						return false;
					}
					for (size_t i = 0; i < call->Arguments->getExpressionCount(); i += 2)
						if (call->Arguments->getExpression(i)->Type == ExpressionType::Operator)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_ER_EXPECTED_OPERAND,
									StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(call->Arguments->getExpression(i)->Index)) } }
								);
							}
							return false;
						}
					for (size_t i = 1; i < call->Arguments->getExpressionCount(); i += 2)
					{
						if (call->Arguments->getExpression(i)->Type != ExpressionType::Operator)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_ER_EXPECTED_OPERATOR,
									StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(call->Arguments->getExpression(i)->Index)) } }
								);
							}
							return false;
						}
						if (cast<CExpressionOperator*>(call->Arguments->getExpression(i))->Op->Name != cast<CExpressionOperator*>(call->Arguments->getExpression(1))->Op->Name)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_EXPECTED_OPERATOR_NAME,
									StringKeyValueArray{
										StringKeyValue{ L"{name}", cast<CExpressionOperator*>(call->Arguments->getExpression(1))->Op->Name },
										StringKeyValue{ L"{index}", ToString(uint64(call->Arguments->getExpression(i)->Index)) },
										StringKeyValue{ L"{token}", cast<CExpressionOperator*>(call->Arguments->getExpression(i))->Op->Name } }
								);
							}
							return false;
						}
					}
				}
				IFunction::Arguments arguments;
				if (call->Arguments)
				{
					IFunction *argument;
					if (call->Arguments->getExpressionCount() > 0)
					{
						for (size_t i = 0; i < call->Arguments->getExpressionCount(); i += 2)
						{
							if (!MakeOperand(call->Arguments->getExpression(i), &argument, modify))
							{
								FreeArguments(arguments);
								return false;
							}
							arguments.push_back(argument);
						}
					}
					else
					{
						if (!MakeOperand(call->Arguments, &argument, modify))
							return false;
						arguments.push_back(argument);
					}
				}
				if (!CreateFunction(cast<CExpressionIdentifier*>(call->Name)->Name, arguments, target, nullptr))
				{
					FreeArguments(arguments);
					return false;
				}
				*modify = *target;
				return MakeOperators(expression, target);
			}

			bool CExpressionRunner::MakeSubscript(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = nullptr;
				CExpressionSubscript *subscript{ cast<CExpressionSubscript*>(expression) };
				if (!subscript->Name)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_EXPECTED_SUBSCRIPT_NAME,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(subscript->Index)) } }
						);
					}
					return false;
				}
				if (!subscript->Arguments)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_EXPECTED_SUBSCRIPT_ARGUMENTS,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(subscript->Index)) } }
						);
					}
					return false;
				}
				if (subscript->Name->getPriorOperatorCount() > 0)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_SUBSCRIPT_NAME_WITH_PRIOR_OPERATORS,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
						);
					}
					return false;
				}
				if (subscript->Name->getPosteriorOperatorCount() > 0)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_SUBSCRIPT_NAME_WITH_POSTERIOR_OPERATORS,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
						);
					}
					return false;
				}
				if (subscript->Arguments->getExpressionCount() > 0)
				{
					if (subscript->Arguments->getExpressionCount() != 1)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_EXPECTED_ONE_ARGUMENT,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(subscript->Arguments->Index)) } }
							);
						}
						return false;
					}
					if (subscript->Arguments->getPriorOperatorCount() > 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_SUBSCRIPT_ARGUMENTS_WITH_PRIOR_OPERATORS,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
							);
						}
						return false;
					}
					if (subscript->Arguments->getPosteriorOperatorCount() > 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_SUBSCRIPT_ARGUMENTS_WITH_POSTERIOR_OPERATORS,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
							);
						}
						return false;
					}
					if (subscript->Arguments->getExpression(0)->Type == ExpressionType::Operator)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_EXPECTED_OPERAND,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(subscript->Arguments->getExpression(0)->Index)) } }
							);
						}
						return false;
					}
				}
				IFunction *argument;
				if (!MakeOperand(subscript->Arguments->getExpressionCount() > 0 ? subscript->Arguments->getExpression(0) : subscript->Arguments, &argument, modify))
					return false;
				IFunction *result;
				switch (subscript->Name->Type)
				{
				case ExpressionType::Brace:
				case ExpressionType::Call:
				case ExpressionType::Identifier:
				case ExpressionType::Subscript:
					if (!MakeOperand(subscript->Name, &result, modify))
					{
						argument->Release();
						return false;
					}
					if (!CreateFunction(subscript->Op->Name + subscript->Op->Close, IFunction::Arguments{ result, argument }, target, nullptr))
					{
						result->Release();
						argument->Release();
						return false;
					}
					break;
				case ExpressionType::Sequence:
					if (!MakeSequence(subscript->Name, &result, modify))
					{
						argument->Release();
						return false;
					}
					if (!CreateFunction(subscript->Op->Name + subscript->Op->Close, IFunction::Arguments{ result, argument }, target, nullptr))
					{
						result->Release();
						argument->Release();
						return false;
					}
					break;
				default:
					argument->Release();
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_UNSUPPORTED_SUBSCRIPT_NAME_EXPRESSION_TYPE,
							StringKeyValueArray{ StringKeyValue{ L"{type}", ExpressionTypeToString(subscript->Name->Type) }, StringKeyValue{ L"{index}", ToString(uint64(subscript->Name->Index)) } }
						);
					}
					return false;
				}
				*modify = *target;
				return MakeOperators(expression, target);
			}

			bool CExpressionRunner::MakeCast(IExpression *expression, IFunction **target, IFunction **modify) // Standalone cast (operand should exist and should be processed)
			{
				*target = nullptr;
				CExpressionCast *cast{ nitisa::cast<CExpressionCast*>(expression) };
				if (!cast->Operand)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_EXPECTED_CAST_OPERAND,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(cast->Index)) } }
						);
					}
					return false;
				}
				IFunction *operand;
				if (!MakeOperand(cast->Operand, &operand, modify))
					return false;
				if (!MakeCast(expression, target, modify, operand))
				{
					operand->Release();
					return false;
				}
				return MakeOperators(expression, target);
			}

			bool CExpressionRunner::MakeCast(IExpression *expression, IFunction **target, IFunction **modify, IFunction *operand) // Part of brace/call (operand shouldn't exist and shouldn't be processed because of it's specified as argument to the method)
			{
				*target = nullptr;
				CExpressionCast *cast{ nitisa::cast<CExpressionCast*>(expression) };
				if (cast->Name)
				{
					if (cast->Name->Type != ExpressionType::Cast)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_UNSUPPORTED_CAST_NAME_EXPRESSION_TYPE,
								StringKeyValueArray{ StringKeyValue{ L"{type}", ExpressionTypeToString(cast->Name->Type) }, StringKeyValue{ L"{index}", ToString(uint64(cast->Name->Index)) } }
							);
						}
						return false;
					}
					if (cast->Name->getPriorOperatorCount() > 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_CAST_NAME_WITH_PRIOR_OPERATORS,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(cast->Name->Index)) } }
							);
						}
						return false;
					}
					if (cast->Name->getPosteriorOperatorCount() > 0)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_CAST_NAME_WITH_POSTERIOR_OPERATORS,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(cast->Name->Index)) } }
							);
						}
						return false;
					}
				}
				if (cast->DataType.empty())
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_CAST_DATA_TYPE_EMPTY,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(cast->Index)) } }
						);
					}
					return false;
				}
				IFunction *result;
				if (!CreateFunction(L"__cast(" + cast->DataType + L")", IFunction::Arguments{ operand }, &result, nullptr))
					return false;
				if (!cast->Name)
				{
					*target = result;
					return true;
				}
				if (!MakeCast(cast->Name, target, modify, result))
				{
					result->Release();
					return false;
				}
				return true;
			}

			bool CExpressionRunner::MakeSequence(IExpression *expression, IFunction **target, IFunction **modify)
			{
				*target = nullptr;
				if (expression->getExpressionCount() == 0)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_EMPTY_SEQUENCE,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
						);
					}
					return false;
				}
				if (expression->getExpressionCount() == 1)
				{
					if (!MakeOperand((*expression)[0], target, modify))
						return false;
					return MakeOperators(expression, target);
				}
				if (expression->getExpressionCount() % 2 == 0)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_ER_EXPECTED_ODD_EXPRESSION_COUNT,
							StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
						);
					}
					return false;
				}
				for (size_t i = 0; i < expression->getExpressionCount(); i += 2)
					if (expression->getExpression(i)->Type == ExpressionType::Operator)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_EXPECTED_OPERAND,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->getExpression(i)->Index)) } }
							);
						}
						return false;
					}
				for (size_t i = 1; i < expression->getExpressionCount(); i += 2)
					if (expression->getExpression(i)->Type != ExpressionType::Operator)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_EXPECTED_OPERATOR,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->getExpression(i)->Index)) } }
							);
						}
						return false;
					}
				IFunction *operand1, *operand2, *operand3, *modify1, *modify2, *modify3;
				// Ternary
				if (cast<CExpressionSequence*>(expression)->Ternary)
				{
					if (expression->getExpressionCount() != 5)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_ER_EXPECTED_FIVE_EXPRESSIONS_FOR_TERNARY,
								StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(uint64(expression->Index)) } }
							);
						}
						return false;
					}
					if (!MakeOperand((*expression)[0], &operand1, &modify1))
						return false;
					if (!MakeOperand((*expression)[2], &operand2, &modify2))
					{
						operand1->Release();
						return false;
					}
					if (!MakeOperand((*expression)[4], &operand3, &modify3))
					{
						operand1->Release();
						operand2->Release();
						return false;
					}
					if (!CreateFunction(cast<CExpressionOperator*>((*expression)[1])->Op->Name + cast<CExpressionOperator*>((*expression)[3])->Op->Name, IFunction::Arguments{ operand1, operand2, operand3 }, target, nullptr))
					{
						operand1->Release();
						operand2->Release();
						operand3->Release();
						return false;
					}
					return MakeOperators(expression, target);
				}
				// Sequence
				if (!MakeOperand((*expression)[0], &operand1, &modify1))
					return false;
				size_t i = 1;
				while (i < expression->getExpressionCount() - 1)
				{
					if (cast<CExpressionOperator*>((*expression)[i])->MemberAccess && (*expression)[i + 1]->Type == ExpressionType::Identifier)
					{
						if (!MakeIdentifier((*expression)[i + 1], &operand2, &modify2))
						{
							operand1->Release();
							return false;
						}
					}
					else
					{
						if (!MakeOperand((*expression)[i + 1], &operand2, &modify2))
						{
							operand1->Release();
							return false;
						}
					}
					if (!CreateFunction(cast<CExpressionOperator*>((*expression)[i])->Op->Name, IFunction::Arguments { operand1, operand2 }, &operand3, modify1))
					{
						operand1->Release();
						operand2->Release();
						return false;
					}
					operand1 = operand3;
					modify1 = modify2;
					i += 2;
				}
				*target = *modify = operand1;
				return MakeOperators(expression, target);
			}
		#pragma endregion
		}
	}
}