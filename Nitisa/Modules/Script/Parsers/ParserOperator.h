// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Releasable.h"
#include "../../../Core/Strings.h"
#include "../Core/Operators.h"
#include "../Core/Token.h"
#include "../Interfaces/IParser.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		class ILexic;
		class IReader;

		struct Operator;

		class CParserOperator :public virtual IParser, public CReleasable
		{
		private:
			std::vector<const Operator*> m_aOperators;
			ILexic *m_pLexic;

			Operator m_sSearchOperator;
		protected:
			IReader *m_pReader;

			virtual bool CheckName(const String &name, const size_t index);
		public:
			// IParser methods
			bool Parse(size_t &index, Token &token) override;

			CParserOperator(const Operators &operators, IReader *reader, ILexic *lexic);
		};
	}
}