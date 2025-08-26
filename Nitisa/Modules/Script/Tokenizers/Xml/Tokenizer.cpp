// This file is a part of Nitisa framework
// Copyright © 2024 Nitisa. All rights reserved.
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
			const Operators CTokenizer::Ops{
				// Name Close Replace RequireSpace Block Multiline Normal Block Prior Posterior AllowPrior AllowPosterior Priority
				Operator{ L"\n", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // \n
				Operator{ L"\r", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // \r
				Operator{ L" ", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // space
				Operator{ L"\t", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // tab
				Operator{ L"\v", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // vertical 1tab
				Operator{ L"\f", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // form feed
				Operator{ L"\"", L"\"", StringKeyValueArray{ { L"\\\"", L"\"" } }, false, true, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // "
				Operator{ L"'", L"'", StringKeyValueArray{ { L"\\'", L"'" } }, false, true, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // '
				Operator{ L"<", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // <
				Operator{ L"=", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // =
				Operator{ L">", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // >
				Operator{ L"</", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // </
				Operator{ L"/>", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // />
				Operator{ L"<?", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // <?
				Operator{ L"?>", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // ?>
				Operator{ L"<!", EmptyString, EmptyStringKeyValueArray, false, false, false, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // <!
				Operator{ L"<!--", L"-->", EmptyStringKeyValueArray, false, true, true, GROUP_SKIP, false, false, false, false, false, false, 0 }, // <!-- -->
				Operator{ L"<![CDATA[", L"]]>", EmptyStringKeyValueArray, false, true, true, GROUP_NO_SKIP, false, false, false, false, false, false, 0 }, // <![CDATA[ ]]>
			};

		#pragma region Constructor & destructor
			CTokenizer::CTokenizer(const String &source) :
				script::CTokenizer(),
				m_cReader{ source },
				m_cLexic{ &m_cReader },
				m_cParserOperator{ Ops, &m_cReader, &m_cLexic },
				m_cParserString{ &m_cReader, &m_cLexic },
				m_cParserIdentifier{ &m_cReader, &m_cLexic }
			{
				m_pReader = &m_cReader;
				m_pParserOperator = &m_cParserOperator;
				m_pParserString = &m_cParserString;
				m_pParserIdentifier = &m_cParserIdentifier;
			}

			CTokenizer::CTokenizer(const String &source, const size_t min, const size_t max) :
				script::CTokenizer(),
				m_cReader{ source, min, max },
				m_cLexic{ &m_cReader },
				m_cParserOperator{ Ops, &m_cReader, &m_cLexic },
				m_cParserString{ &m_cReader, &m_cLexic },
				m_cParserIdentifier{ &m_cReader, &m_cLexic }
			{
				m_pReader = &m_cReader;
				m_pParserOperator = &m_cParserOperator;
				m_pParserString = &m_cParserString;
				m_pParserIdentifier = &m_cParserIdentifier;
			}
		#pragma endregion
		}
	}
}