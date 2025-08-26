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
		namespace cpp
		{
		#pragma region Constructor & destructor
			CParserOperator::CParserOperator(const Operators & operators, IReader * reader, ILexic * lexic):
				script::CParserOperator(operators, reader, lexic)
			{

			}
		#pragma endregion

		#pragma region Helpers
			bool CParserOperator::CheckName(const String &name, const size_t index)
			{
				if (name == L"<:" && m_pReader->Read(index + 2) == L':' && m_pReader->Read(index + 3) != L':')
					return false;
				return script::CParserOperator::CheckName(name, index);
			}
		#pragma endregion
		}
	}
}