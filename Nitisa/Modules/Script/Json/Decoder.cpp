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
		namespace json
		{
		#pragma region Members
			bool Decoder::m_bAbort;
			bool Decoder::m_bFailed;
			Token Decoder::m_sToken;
			Token *Decoder::m_pToken;
			size_t Decoder::m_iIndex;
			size_t Decoder::m_iLength;
			ITokenizer *Decoder::m_pTokenizer;
			IErrorListener *Decoder::m_pErrorListener;
			IProgressListener *Decoder::m_pProgressListener;
		#pragma endregion

		#pragma region To Object
			bool Decoder::Decode(const String &source, Variable &target, IErrorListener *error_listener, IProgressListener *progress_listener)
			{
				target.clear();
				if (source.empty())
					return true;
				m_bAbort = false;
				m_bFailed = false;
				m_iIndex = 0;
				m_iLength = source.length();
				CTokenizer tokenizer{ source };
				m_pTokenizer = &tokenizer;
				m_pErrorListener = error_listener;
				m_pProgressListener = progress_listener;
				if (!(m_pToken = Next()))
					return !m_bFailed && !m_bAbort;
				switch (m_pToken->Type)
				{
				case TokenType::Operator:
					if (m_pToken->Op->Name == L"+")
					{
						m_pToken = Next();
						if (!m_pToken)
						{
							if (m_pErrorListener)
								m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
							return false;
						}
						if (m_pToken->Type == TokenType::Integer)
							target = (int64)m_pToken->Integer;
						else if (m_pToken->Type == TokenType::Float)
							target = m_pToken->Float;
						else if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
							target = m_pToken->Value;
						else
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_EXPECTED_NUMBER,
									StringKeyValueArray{
										StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
										StringKeyValue{ L"{token}", m_pToken->Value }
									}
								);
							}
							return false;
						}
						if ((m_pToken = Next()))
							return false;
						return true;
					}
					if (m_pToken->Op->Name == L"-")
					{
						m_pToken = Next();
						if (!m_pToken)
						{
							if (m_pErrorListener)
								m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
							return false;
						}
						if (m_pToken->Type == TokenType::Integer)
							target = -(int64)m_pToken->Integer;
						else if (m_pToken->Type == TokenType::Float)
							target = -m_pToken->Float;
						else if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
							target = L"-" + m_pToken->Value;
						else
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_EXPECTED_NUMBER,
									StringKeyValueArray{
										StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
										StringKeyValue{ L"{token}", m_pToken->Value }
									}
								);
							}
							return false;
						}
						if ((m_pToken = Next()))
							return false;
						return true;
					}
					if (m_pToken->Op->Name == L"{")
						return DecodeObject(target, false);
					if (m_pToken->Op->Name == L"[")
						return DecodeArray(target, false);
					return false;
				case TokenType::String:
					target = Unescape(m_pToken->Value);
					if ((m_pToken = Next()))
						return false;
					return true;
				case TokenType::Integer:
					target = (int64)m_pToken->Integer;
					if ((m_pToken = Next()))
						return false;
					return true;
				case TokenType::Float:
					target = m_pToken->Float;
					if ((m_pToken = Next()))
						return false;
					return true;
				case TokenType::Identifier:
					if (m_pToken->Value == L"true")
						target = true;
					else if (m_pToken->Value == L"false")
						target = false;
					else if (m_pToken->Value == L"null")
						target.type(VariableType::Null);
					else if (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN")
						target = m_pToken->Value;
					else
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNKNOWN_IDENTIFIER,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					}
					if ((m_pToken = Next()))
						return false;
					return true;
				default:
					return false;
				}
			}

			bool Decoder::DecodeObject(Variable &target, const bool allow_comma)
			{
				target.type(VariableType::Object);
				m_pToken = Next(); // Skip {
				if (m_bFailed || m_bAbort)
					return false;
				while (m_pToken)
				{
					// Check member
					if (m_pToken->Type == TokenType::Identifier || m_pToken->Type == TokenType::String)
					{
						if (!DecodeMember(target))
							return false;
						if (m_pToken && m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L",")
						{
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							continue;
						}
					}
					break;
				}
				// Check object close
				if (m_pToken && m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L"}")
				{
					m_pToken = Next();
					if (m_bFailed || m_bAbort)
						return false;
					if (m_pToken && !allow_comma)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_EXPECTED_END,
								StringKeyValueArray{
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
									StringKeyValue{ L"{token}", m_pToken->Value }
								}
							);
						}
						return false;
					}
					return true;
				}
				// Error
				if (m_pErrorListener)
				{
					if (m_pToken)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_JSON_EXPECTED_OBJECT_END,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					else
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
				}
				return false;
			}

			bool Decoder::DecodeArray(Variable &target, const bool allow_comma)
			{
				target.type(VariableType::Array);
				m_pToken = Next(); // Skip [
				if (m_bFailed || m_bAbort)
					return false;
				bool require_next;
				while (m_pToken)
				{
					require_next = true;
					switch (m_pToken->Type)
					{
					case TokenType::String:
						target.push_back(Unescape(m_pToken->Value));
						break;
					case TokenType::Identifier:
						if (m_pToken->Value == L"true")
						{
							target.push_back(true);
							break;
						}
						if (m_pToken->Value == L"false")
						{
							target.push_back(false);
							break;
						}
						if (m_pToken->Value == L"null")
						{
							target.push_back(Variable{ });
							break;
						}
						if (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN")
						{
							target.push_back(m_pToken->Value);
							break;
						}
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNKNOWN_IDENTIFIER,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					case TokenType::Integer:
						target.push_back((int64)m_pToken->Integer);
						break;
					case TokenType::Float:
						target.push_back(m_pToken->Float);
						break;
					case TokenType::Operator:
						if (m_pToken->Op->Name == L"+")
						{
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							if (!m_pToken)
							{
								if (m_pErrorListener)
									m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
								return false;
							}
							if (m_pToken->Type == TokenType::Integer)
							{
								target.push_back((int64)m_pToken->Integer);
								break;
							}
							if (m_pToken->Type == TokenType::Float)
							{
								target.push_back(m_pToken->Float);
								break;
							}
							if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
							{
								target.push_back(m_pToken->Value);
								break;
							}
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_EXPECTED_NUMBER,
									StringKeyValueArray{
										StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
										StringKeyValue{ L"{token}", m_pToken->Value }
									}
								);
							}
							return false;
						}
						if (m_pToken->Op->Name == L"-")
						{
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							if (!m_pToken)
							{
								if (m_pErrorListener)
									m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
								return false;
							}
							if (m_pToken->Type == TokenType::Integer)
							{
								target.push_back(-(int64)m_pToken->Integer);
								break;
							}
							if (m_pToken->Type == TokenType::Float)
							{
								target.push_back(-m_pToken->Float);
								break;
							}
							if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
							{
								target.push_back(L"-" + m_pToken->Value);
								break;
							}
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_EXPECTED_NUMBER,
									StringKeyValueArray{
										StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
										StringKeyValue{ L"{token}", m_pToken->Value }
									}
								);
							}
							return false;
						}
						if (m_pToken->Op->Name == L"{")
						{
							Variable t;
							if (!DecodeObject(t, true))
								return false;
							target.push_back(t);
							require_next = false;
							break;
						}
						if (m_pToken->Op->Name == L"[")
						{
							Variable t;
							if (!DecodeArray(t, true))
								return false;
							target.push_back(t);
							require_next = false;
							break;
						}
						if (m_pToken->Op->Name == L"]")
						{
							require_next = false;
							break;
						}
					default:
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_EXPECTED_NUMBER,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					}
					if (require_next)
					{
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
					}
					if (m_pToken && m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L",")
					{
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						continue;
					}
					break;
				}
				// Check object close
				if (m_pToken && m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L"]")
				{
					m_pToken = Next();
					if (m_bFailed || m_bAbort)
						return false;
					if (m_pToken && !allow_comma)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_EXPECTED_END,
								StringKeyValueArray{
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
									StringKeyValue{ L"{token}", m_pToken->Value }
								}
							);
						}
						return false;
					}
					return true;
				}
				// Error
				if (m_pErrorListener)
				{
					if (m_pToken)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_JSON_EXPECTED_ARRAY_END,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					else
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
				}
				return false;
			}

			bool Decoder::DecodeMember(Variable &target)
			{
				String key{ m_pToken->Value };
				m_pToken = Next();
				if (m_bFailed || m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				if (m_pToken->Type != TokenType::Operator || m_pToken->Op->Name != L":")
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_COLON,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				m_pToken = Next();
				if (m_bFailed || m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				switch (m_pToken->Type)
				{
				case TokenType::String:
					target[key] = Unescape(m_pToken->Value);
					m_pToken = Next();
					if (m_bFailed || m_bAbort)
						return false;
					return true;
				case TokenType::Identifier:
					if (m_pToken->Value == L"true")
					{
						target[key] = true;
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						return true;
					}
					if (m_pToken->Value == L"false")
					{
						target[key] = false;
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						return true;
					}
					if (m_pToken->Value == L"null")
					{
						target[key] = (Pointer)nullptr;
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						return true;
					}
					if (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN")
					{
						target[key] = m_pToken->Value;
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						return true;
					}
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_UNKNOWN_IDENTIFIER,
							StringKeyValueArray{
								StringKeyValue{ L"{token}", m_pToken->Value },
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
							}
						);
					}
					return false;
				case TokenType::Integer:
					target[key] = (int64)m_pToken->Integer;
					m_pToken = Next();
					if (m_bFailed || m_bAbort)
						return false;
					return true;
				case TokenType::Float:
					target[key] = m_pToken->Float;
					m_pToken = Next();
					if (m_bFailed || m_bAbort)
						return false;
					return true;
				case TokenType::Operator:
					if (m_pToken->Op->Name == L"+")
					{
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						if (!m_pToken)
						{
							if (m_pErrorListener)
								m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
							return false;
						}
						if (m_pToken->Type == TokenType::Integer)
						{
							target[key] = (int64)m_pToken->Integer;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pToken->Type == TokenType::Float)
						{
							target[key] = m_pToken->Float;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
						{
							target[key] = m_pToken->Value;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_EXPECTED_NUMBER,
								StringKeyValueArray{
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
									StringKeyValue{ L"{token}", m_pToken->Value }
								}
							);
						}
						return false;
					}
					if (m_pToken->Op->Name == L"-")
					{
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						if (!m_pToken)
						{
							if (m_pErrorListener)
								m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
							return false;
						}
						if (m_pToken->Type == TokenType::Integer)
						{
							target[key] = -(int64)m_pToken->Integer;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pToken->Type == TokenType::Float)
						{
							target[key] = -m_pToken->Float;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
						{
							target[key] = L"-" + m_pToken->Value;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_EXPECTED_NUMBER,
								StringKeyValueArray{
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
									StringKeyValue{ L"{token}", m_pToken->Value }
								}
							);
						}
						return false;
					}
					if (m_pToken->Op->Name == L"{")
					{
						Variable t;
						if (!DecodeObject(t, true))
							return false;
						target[key] = t;
						return true;
					}
					if (m_pToken->Op->Name == L"[")
					{
						Variable t;
						if (!DecodeArray(t, true))
							return false;
						target[key] = t;
						return true;
					}
				default:
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_NUMBER,
							StringKeyValueArray{
								StringKeyValue{ L"{token}", m_pToken->Value },
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
							}
						);
					}
					return false;
				}
			}
		#pragma endregion

		#pragma region To Variant
			bool Decoder::Decode(const String &source, Variant &target, IErrorListener *error_listener, IProgressListener *progress_listener)
			{
				target.Reset();
				m_bAbort = false;
				m_bFailed = false;
				m_iIndex = 0;
				m_iLength = source.length();
				CTokenizer tokenizer{ source };
				m_pTokenizer = &tokenizer;
				m_pErrorListener = error_listener;
				m_pProgressListener = progress_listener;
				if (!(m_pToken = Next()))
					return !m_bFailed && !m_bAbort;
				switch (m_pToken->Type)
				{
				case TokenType::Operator:
					if (m_pToken->Op->Name == L"+")
					{
						m_pToken = Next();
						if (!m_pToken)
						{
							if (m_pErrorListener)
								m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
							return false;
						}
						if (m_pToken->Type == TokenType::Integer)
							target = (int)m_pToken->Integer;
						else if (m_pToken->Type == TokenType::Float)
							target = (float)m_pToken->Float;
						else if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
							target = m_pToken->Value;
						else
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_EXPECTED_NUMBER,
									StringKeyValueArray{
										StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
										StringKeyValue{ L"{token}", m_pToken->Value }
									}
								);
							}
							return false;
						}
						if ((m_pToken = Next()))
							return false;
						return true;
					}
					if (m_pToken->Op->Name == L"-")
					{
						m_pToken = Next();
						if (!m_pToken)
						{
							if (m_pErrorListener)
								m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
							return false;
						}
						if (m_pToken->Type == TokenType::Integer)
							target = -(int)m_pToken->Integer;
						else if (m_pToken->Type == TokenType::Float)
							target = -(float)m_pToken->Float;
						else if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
							target = L"-" + m_pToken->Value;
						else
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_EXPECTED_NUMBER,
									StringKeyValueArray{
										StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
										StringKeyValue{ L"{token}", m_pToken->Value }
									}
								);
							}
							return false;
						}
						if ((m_pToken = Next()))
							return false;
						return true;
					}
					if (m_pToken->Op->Name == L"{")
						return DecodeObject(target, false);
					if (m_pToken->Op->Name == L"[")
						return DecodeArray(target, false);
					return false;
				case TokenType::String:
					target = Unescape(m_pToken->Value);
					if ((m_pToken = Next()))
						return false;
					return true;
				case TokenType::Integer:
					target = (int)m_pToken->Integer;
					if ((m_pToken = Next()))
						return false;
					return true;
				case TokenType::Float:
					target = (float)m_pToken->Float;
					if ((m_pToken = Next()))
						return false;
					return true;
				case TokenType::Identifier:
					if (m_pToken->Value == L"true")
						target = true;
					else if (m_pToken->Value == L"false")
						target = false;
					else if (m_pToken->Value == L"null")
						target = nullptr;
					else if (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN")
						target = m_pToken->Value;
					else
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNKNOWN_IDENTIFIER,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					}
					if ((m_pToken = Next()))
						return false;
					return true;
				default:
					return false;
				}
			}

			bool Decoder::DecodeObject(Variant &target, const bool allow_comma)
			{
				target[L"key"] = L"";
				target.clear();
				m_pToken = Next(); // Skip {
				if (m_bFailed || m_bAbort)
					return false;
				while (m_pToken)
				{
					// Check member
					if (m_pToken->Type == TokenType::Identifier || m_pToken->Type == TokenType::String)
					{
						if (!DecodeMember(target))
							return false;
						if (m_pToken && m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L",")
						{
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							continue;
						}
					}
					break;
				}
				// Check object close
				if (m_pToken && m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L"}")
				{
					m_pToken = Next();
					if (m_bFailed || m_bAbort)
						return false;
					if (m_pToken && !allow_comma)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_EXPECTED_END,
								StringKeyValueArray{
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
									StringKeyValue{ L"{token}", m_pToken->Value }
								}
							);
						}
						return false;
					}
					return true;
				}
				// Error
				if (m_pErrorListener)
				{
					if (m_pToken)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_JSON_EXPECTED_OBJECT_END,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					else
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
				}
				return false;
			}

			bool Decoder::DecodeArray(Variant &target, const bool allow_comma)
			{
				target.push_back(Variant{});
				target.clear();
				m_pToken = Next(); // Skip [
				if (m_bFailed || m_bAbort)
					return false;
				bool require_next;
				while (m_pToken)
				{
					require_next = true;
					switch (m_pToken->Type)
					{
					case TokenType::String:
						target.push_back(Variant{ Unescape(m_pToken->Value) });
						break;
					case TokenType::Identifier:
						if (m_pToken->Value == L"true")
						{
							target.push_back(Variant{ true });
							break;
						}
						if (m_pToken->Value == L"false")
						{
							target.push_back(Variant{ false });
							break;
						}
						if (m_pToken->Value == L"null")
						{
							target.push_back(Variant{});
							break;
						}
						if (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN")
						{
							target.push_back(Variant{ m_pToken->Value });
							break;
						}
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNKNOWN_IDENTIFIER,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					case TokenType::Integer:
						target.push_back(Variant{ (int)m_pToken->Integer });
						break;
					case TokenType::Float:
						target.push_back(Variant{ (float)m_pToken->Float });
						break;
					case TokenType::Operator:
						if (m_pToken->Op->Name == L"+")
						{
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							if (!m_pToken)
							{
								if (m_pErrorListener)
									m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
								return false;
							}
							if (m_pToken->Type == TokenType::Integer)
							{
								target.push_back(Variant{ (int)m_pToken->Integer });
								break;
							}
							if (m_pToken->Type == TokenType::Float)
							{
								target.push_back(Variant{ (float)m_pToken->Float });
								break;
							}
							if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
							{
								target.push_back(Variant{ m_pToken->Value });
								break;
							}
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_EXPECTED_NUMBER,
									StringKeyValueArray{
										StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
										StringKeyValue{ L"{token}", m_pToken->Value }
									}
								);
							}
							return false;
						}
						if (m_pToken->Op->Name == L"-")
						{
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							if (!m_pToken)
							{
								if (m_pErrorListener)
									m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
								return false;
							}
							if (m_pToken->Type == TokenType::Integer)
							{
								target.push_back(Variant{ -(int)m_pToken->Integer });
								break;
							}
							if (m_pToken->Type == TokenType::Float)
							{
								target.push_back(Variant{ -(float)m_pToken->Float });
								break;
							}
							if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
							{
								target.push_back(Variant{ L"-" + m_pToken->Value });
								break;
							}
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ERROR_GENERAL_EXPECTED_NUMBER,
									StringKeyValueArray{
										StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
										StringKeyValue{ L"{token}", m_pToken->Value }
									}
								);
							}
							return false;
						}
						if (m_pToken->Op->Name == L"{")
						{
							Variant t;
							if (!DecodeObject(t, true))
								return false;
							target.push_back(t);
							require_next = false;
							break;
						}
						if (m_pToken->Op->Name == L"[")
						{
							Variant t;
							if (!DecodeArray(t, true))
								return false;
							target.push_back(t);
							require_next = false;
							break;
						}
						if (m_pToken->Op->Name == L"]")
						{
							require_next = false;
							break;
						}
					default:
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_EXPECTED_NUMBER,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					}
					if (require_next)
					{
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
					}
					if (m_pToken && m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L",")
					{
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						continue;
					}
					break;
				}
				// Check object close
				if (m_pToken && m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L"]")
				{
					m_pToken = Next();
					if (m_bFailed || m_bAbort)
						return false;
					if (m_pToken && !allow_comma)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_EXPECTED_END,
								StringKeyValueArray{
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
									StringKeyValue{ L"{token}", m_pToken->Value }
								}
							);
						}
						return false;
					}
					return true;
				}
				// Error
				if (m_pErrorListener)
				{
					if (m_pToken)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_JSON_EXPECTED_ARRAY_END,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					else
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
				}
				return false;
			}

			bool Decoder::DecodeMember(Variant &target)
			{
				String key{ m_pToken->Value };
				m_pToken = Next();
				if (m_bFailed || m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				if (m_pToken->Type != TokenType::Operator || m_pToken->Op->Name != L":")
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_COLON,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				m_pToken = Next();
				if (m_bFailed || m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				switch (m_pToken->Type)
				{
				case TokenType::String:
					target[key.c_str()] = Unescape(m_pToken->Value);
					m_pToken = Next();
					if (m_bFailed || m_bAbort)
						return false;
					return true;
				case TokenType::Identifier:
					if (m_pToken->Value == L"true")
					{
						target[key.c_str()] = true;
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						return true;
					}
					if (m_pToken->Value == L"false")
					{
						target[key.c_str()] = false;
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						return true;
					}
					if (m_pToken->Value == L"null")
					{
						target[key.c_str()] = nullptr;
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						return true;
					}
					if (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN")
					{
						target[key.c_str()] = m_pToken->Value;
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						return true;
					}
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_UNKNOWN_IDENTIFIER,
							StringKeyValueArray{
								StringKeyValue{ L"{token}", m_pToken->Value },
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
							}
						);
					}
					return false;
				case TokenType::Integer:
					target[key.c_str()] = (int)m_pToken->Integer;
					m_pToken = Next();
					if (m_bFailed || m_bAbort)
						return false;
					return true;
				case TokenType::Float:
					target[key.c_str()] = (float)m_pToken->Float;
					m_pToken = Next();
					if (m_bFailed || m_bAbort)
						return false;
					return true;
				case TokenType::Operator:
					if (m_pToken->Op->Name == L"+")
					{
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						if (!m_pToken)
						{
							if (m_pErrorListener)
								m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
							return false;
						}
						if (m_pToken->Type == TokenType::Integer)
						{
							target[key.c_str()] = (int)m_pToken->Integer;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pToken->Type == TokenType::Float)
						{
							target[key.c_str()] = (float)m_pToken->Float;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
						{
							target[key.c_str()] = m_pToken->Value;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_EXPECTED_NUMBER,
								StringKeyValueArray{
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
									StringKeyValue{ L"{token}", m_pToken->Value }
								}
							);
						}
						return false;
					}
					if (m_pToken->Op->Name == L"-")
					{
						m_pToken = Next();
						if (m_bFailed || m_bAbort)
							return false;
						if (!m_pToken)
						{
							if (m_pErrorListener)
								m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
							return false;
						}
						if (m_pToken->Type == TokenType::Integer)
						{
							target[key.c_str()] = -(int)m_pToken->Integer;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pToken->Type == TokenType::Float)
						{
							target[key.c_str()] = -(float)m_pToken->Float;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pToken->Type == TokenType::Identifier && (m_pToken->Value == L"Infinity" || m_pToken->Value == L"NaN"))
						{
							target[key.c_str()] = L"-" + m_pToken->Value;
							m_pToken = Next();
							if (m_bFailed || m_bAbort)
								return false;
							return true;
						}
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_EXPECTED_NUMBER,
								StringKeyValueArray{
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
									StringKeyValue{ L"{token}", m_pToken->Value }
								}
							);
						}
						return false;
					}
					if (m_pToken->Op->Name == L"{")
					{
						Variant t;
						if (!DecodeObject(t, true))
							return false;
						target[key.c_str()] = t;
						return true;
					}
					if (m_pToken->Op->Name == L"[")
					{
						Variant t;
						if (!DecodeArray(t, true))
							return false;
						target[key.c_str()] = t;
						return true;
					}
				default:
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_NUMBER,
							StringKeyValueArray{
								StringKeyValue{ L"{token}", m_pToken->Value },
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
							}
						);
					}
					return false;
				}
			}
		#pragma endregion

		#pragma region Helpers
			String Decoder::Unescape(const String &value)
			{
				if (value.length() < 2)
					return value;
				String result;
				size_t i{ 0 };
				while (i < value.length())
				{
					if (i < value.length() - 1 && value[i] == L'\\')
					{
						if (value[i + 1] == L'"')
						{
							result += L'"';
							i += 2;
							continue;
						}
						if (value[i + 1] == L'\\')
						{
							result += L'\\';
							i += 2;
							continue;
						}
						if (value[i + 1] == L'n')
						{
							result += L'\n';
							i += 2;
							continue;
						}
						if (value[i + 1] == L'r')
						{
							result += L'\r';
							i += 2;
							continue;
						}
						if (value[i + 1] == L't')
						{
							result += L'\t';
							i += 2;
							continue;
						}
					}
					result += value[i++];
				}
				return result;


				/*return ReplaceAll(value, StringKeyValueArray{
					StringKeyValue{ L"\\\\", L"\\" },
					StringKeyValue{ L"\\\"", L"\"" },
					StringKeyValue{ L"\\n", L"\n" },
					StringKeyValue{ L"\\r", L"\r" },
					StringKeyValue{ L"\\t", L"\t" },
				});
				String result{ ReplaceAll(value, L"\\\\", L"\\") };
				ReplaceAllDirect(result, L"\\\"", L"\"");
				ReplaceAllDirect(result, L"\\n", L"\n");
				ReplaceAllDirect(result, L"\\r", L"\r");
				ReplaceAllDirect(result, L"\\t", L"\t");
				return result;*/
			}

			Token *Decoder::Next()
			{
				while (m_pTokenizer->Next(m_iIndex, m_sToken))
				{
					if (m_sToken.Type == TokenType::Unknown)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNKNOWN_TOKEN,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_sToken.Value },
									StringKeyValue{ L"{index}", ToString(m_sToken.Index + 1ull) }
								}
							);
						}
						m_bFailed = true;
						return nullptr;
					}
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ m_sToken.Index, m_iLength }, m_bAbort);
						if (m_bAbort)
							return nullptr;
					}
					if (m_sToken.Op && m_sToken.Op->Group == GROUP_SKIP)
						continue;
					return &m_sToken;
				}
				return nullptr;
			}
		#pragma endregion
		}
	}
}