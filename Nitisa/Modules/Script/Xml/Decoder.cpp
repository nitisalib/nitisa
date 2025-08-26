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
		namespace xml
		{
		#pragma region Members
			bool Decoder::m_bAbort;
			Token Decoder::m_sToken;
			Token *Decoder::m_pToken;
			size_t Decoder::m_iIndex;
			size_t Decoder::m_iLength;
			ITokenizer *Decoder::m_pTokenizer;
			IErrorListener *Decoder::m_pErrorListener;
			IProgressListener *Decoder::m_pProgressListener;

			const StringArray Decoder::SNOperators{  L" ", L"\t", L"\n", L"\r", L"\v", L"\f" };
		#pragma endregion

		#pragma region Decode
			bool Decoder::Decode(const String &source, Entity &target, IErrorListener *error_listener, IProgressListener *progress_listener)
			{
				target.clear(true, true);
				target.name(L"");
				target.value(L"");
				target.type(EntityType::Array);
				if (source.empty())
					return true;
				m_bAbort = false;
				m_iIndex = 0;
				m_iLength = source.length();
				CTokenizer tokenizer{ source };
				m_pTokenizer = &tokenizer;
				m_pErrorListener = error_listener;
				m_pProgressListener = progress_listener;
				if (!(m_pToken = Next()))
					return !m_bAbort;
				if (!(m_pToken = SkipSN()))
					return !m_bAbort;
				bool prolog_allowed{ true }, doctype_allowed{ true }, element_allowed{ true };
				while (m_pToken)
				{
					switch (m_pToken->Type)
					{
					case TokenType::Operator:
						if (m_pToken->Op->Name == L"<?") // Prolog
						{
							if (!prolog_allowed)
							{
								if (m_pErrorListener)
								{
									m_pErrorListener->NotifyOnError(
										__FUNCTION__,
										__LINE__,
										ERROR_XML_PROLOG_NOT_ALLOWED,
										StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) } }
									);
								}
								return false;
							}
							Entity entity;
							if (!DecodeProlog(entity))
								return false;
							target.push_back(entity);
							m_pToken = SkipSN();
							continue;
						}
						if (m_pToken->Op->Name == L"<!") // DOCTYPE
						{
							if (!doctype_allowed)
							{
								if (m_pErrorListener)
								{
									m_pErrorListener->NotifyOnError(
										__FUNCTION__,
										__LINE__,
										ERROR_XML_DOCTYPE_NOT_ALLOWED,
										StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) } }
									);
								}
								return false;
							}
							Entity entity;
							if (!DecodeDoctype(entity))
								return false;
							target.push_back(entity);
							prolog_allowed = false;
							doctype_allowed = false;
							m_pToken = SkipSN();
							continue;
						}
						if (m_pToken->Op->Name == L"<") // Element
						{
							if (!element_allowed)
							{
								if (m_pErrorListener)
								{
									m_pErrorListener->NotifyOnError(
										__FUNCTION__,
										__LINE__,
										ERROR_XML_ELEMENT_NOT_ALLOWED,
										StringKeyValueArray{ StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) } }
									);
								}
								return false;
							}
							Entity entity;
							if (!DecodeElement(entity))
								return false;
							target.push_back(entity);
							prolog_allowed = false;
							doctype_allowed = false;
							element_allowed = false;
							m_pToken = SkipSN();
							continue;
						}
					default:
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNEXPECTED_TOKEN,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					}
				}
				return true;
			}

			bool Decoder::DecodeProlog(Entity &target)
			{
				m_pToken = Next();
				if (m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				if (m_pToken->Type != TokenType::Identifier)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_IDENTIFIER,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				target.type(EntityType::Prolog);
				target.name(m_pToken->Value);
				m_pToken = SkipSN(true);
				if (m_bAbort)
					return false;
				while (m_pToken)
				{
					switch (m_pToken->Type)
					{
					case TokenType::Identifier:
						if (!DecodeAttribute(target))
							return false;
						break;
					case TokenType::Operator:
						if (m_pToken->Op->Name == L"?>")
						{
							m_pToken = Next();
							if (m_bAbort)
								return false;
							return true;
						}
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNEXPECTED_OPERATOR,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					default:
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNEXPECTED_TOKEN,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					}
					m_pToken = SkipSN();
					if (m_bAbort)
						return false;
				}
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
				return false;
			}

			bool Decoder::DecodeDoctype(Entity &target)
			{
				m_pToken = Next();
				if (m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				if (m_pToken->Type != TokenType::Identifier)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_IDENTIFIER,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				if (m_pToken->Value != L"DOCTYPE")
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_XML_EXPECTED_DOCTYPE,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				target.type(EntityType::Doctype);
				target.name(m_pToken->Value);
				String value;
				m_pToken = Next();
				if (m_bAbort)
					return false;
				while (m_pToken)
				{
					switch (m_pToken->Type)
					{
					case TokenType::Operator:
						if (m_pToken->Op->Name == L">")
						{
							target.value(value);
							m_pToken = Next();
							if (m_bAbort)
								return false;
							return true;
						}
						if (m_pToken->Op->Name == L"<!")
						{
							if (!SkipDoctype(value))
								return false;
							continue;
						}
					default:
						value += m_pToken->Value;
						break;
					}
					m_pToken = Next();
					if (m_bAbort)
						return false;
				}
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
				return false;
			}

			bool Decoder::DecodeElement(Entity &target)
			{
				m_pToken = Next();
				if (m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				if (m_pToken->Type != TokenType::Identifier)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_IDENTIFIER,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				target.name(m_pToken->Value);
				m_pToken = SkipSN(true);
				if (m_bAbort)
					return false;
				while (m_pToken)
				{
					switch (m_pToken->Type)
					{
					case TokenType::Identifier:
						if (!DecodeAttribute(target))
							return false;
						break;
					case TokenType::Operator:
						if (m_pToken->Op->Name == L">")
						{
							m_pToken = SkipSN(true);
							if (m_bAbort)
								return false;
							if (!m_pToken)
							{
								if (m_pErrorListener)
									m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
								return false;
							}
							if (m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L"</")
							{
								if (!DecodeElementClose(target.name()))
									return false;
								target.type(EntityType::Element);
								return true;
							}
							if (m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L"<")
							{
								target.type(EntityType::Array);
								while (m_pToken && m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L"<")
								{
									Entity entity;
									if (!DecodeElement(entity))
										return false;
									target.push_back(entity);
									m_pToken = SkipSN();
									if (m_bAbort)
										return false;
								}
								if (!DecodeElementClose(target.name()))
									return false;
								return true;
							}
							if (m_pToken->Type == TokenType::String && m_pToken->Op->Name == L"<![CDATA[")
							{
								target.type(EntityType::Data);
								target.value(m_pToken->Value);
								m_pToken = SkipSN(true);
								if (m_bAbort)
									return false;
								if (!DecodeElementClose(target.name()))
									return false;
								return true;
							}
							// Value
							String value{ m_pToken->Value };
							while ((m_pToken = Next()))
							{
								if (m_bAbort)
									return false;
								if (m_pToken->Type == TokenType::Operator && m_pToken->Op->Name == L"</")
									break;
								value += m_pToken->Value;
							}
							if (m_bAbort)
								return false;
							if (!DecodeElementClose(target.name()))
								return false;
							target.type(EntityType::Element);
							target.value(TrimRight(value));
							return true;
						}
						if (m_pToken->Op->Name == L"/>")
						{
							target.type(EntityType::Element);
							m_pToken = Next();
							if (m_bAbort)
								return false;
							return true;
						}
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNEXPECTED_OPERATOR,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					default:
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ERROR_GENERAL_UNEXPECTED_TOKEN,
								StringKeyValueArray{
									StringKeyValue{ L"{token}", m_pToken->Value },
									StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) }
								}
							);
						}
						return false;
					}
					m_pToken = SkipSN();
					if (m_bAbort)
						return false;
				}
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
				return false;
			}

			bool Decoder::DecodeAttribute(Entity &target)
			{
				String name{ m_pToken->Value };
				m_pToken = SkipSN(true);
				if (m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				if (m_pToken->Type != TokenType::Operator)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_EQUAL,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				if (m_pToken->Op->Name != L"=")
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_EQUAL,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				m_pToken = SkipSN(true);
				if (m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				if (m_pToken->Type != TokenType::String)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_STRING,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				target[name] = m_pToken->Value;
				m_pToken = Next();
				if (m_bAbort)
					return false;
				return true;
			}

			bool Decoder::DecodeElementClose(const String &name)
			{
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				if (m_pToken->Type != TokenType::Operator)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_XML_EXPECTED_ELEMENT_CLOSE_OPERATOR,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				if (m_pToken->Op->Name != L"</")
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_XML_EXPECTED_ELEMENT_CLOSE_OPERATOR,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				m_pToken = Next();
				if (m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				if (m_pToken->Type != TokenType::Identifier)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_IDENTIFIER,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				if (m_pToken->Value != name)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_NAME,
							StringKeyValueArray{
								StringKeyValue{ L"{name}", name },
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				m_pToken = SkipSN(true);
				if (m_bAbort)
					return false;
				if (!m_pToken)
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
					return false;
				}
				if (m_pToken->Type != TokenType::Operator)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_LESS,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				if (m_pToken->Op->Name != L">")
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_GENERAL_EXPECTED_LESS,
							StringKeyValueArray{
								StringKeyValue{ L"{index}", ToString(m_pToken->Index + 1ull) },
								StringKeyValue{ L"{token}", m_pToken->Value }
							}
						);
					}
					return false;
				}
				m_pToken = Next();
				if (m_bAbort)
					return false;
				return true;
			}
		#pragma endregion

		#pragma region Helpers
			Token *Decoder::Next()
			{
				while (m_pTokenizer->Next(m_iIndex, m_sToken))
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ m_iIndex, m_iLength }, m_bAbort);
						if (m_bAbort)
							return nullptr;
					}
					if (m_sToken.Op && m_sToken.Op->Group == GROUP_SKIP)
						continue;
					return &m_sToken;
				}
				return nullptr;
			}

			Token *Decoder::SkipSN(const bool next)
			{
				if (next)
					m_pToken = Next();
				while (m_pToken && m_pToken->Type == TokenType::Operator && in(m_pToken->Op->Name, SNOperators))
					m_pToken = Next();
				return m_pToken;
			}

			bool Decoder::SkipDoctype(String &value)
			{
				value += m_pToken->Value;
				m_pToken = Next();
				if (m_bAbort)
					return false;
				while (m_pToken)
				{
					switch (m_pToken->Type)
					{
					case TokenType::Operator:
						if (m_pToken->Op->Name == L">")
						{
							value += m_pToken->Value;
							m_pToken = Next();
							if (m_bAbort)
								return false;
							return true;
						}
						if (m_pToken->Op->Name == L"<!")
						{
							if (!SkipDoctype(value))
								return false;
							continue;
						}
					default:
						value += m_pToken->Value;
						break;
					}
					m_pToken = Next();
					if (m_bAbort)
						return false;
				}
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_UNEXPECTED_END);
				return false;
			}
		}
	}
}