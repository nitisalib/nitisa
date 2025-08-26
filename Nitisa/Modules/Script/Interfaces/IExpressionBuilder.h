// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Interfaces/IReleasable.h"
#include "../Core/Tokens.h"

namespace nitisa
{
	namespace script
	{
		class IExpression;
		class ITokenizer;

		class IExpressionBuilder :public virtual IReleasable
		{
		protected:
			IExpressionBuilder() = default;
			~IExpressionBuilder() = default;
			IExpressionBuilder(const IExpressionBuilder &other) = delete;
			IExpressionBuilder(IExpressionBuilder &&other) = delete;
			IExpressionBuilder &operator=(const IExpressionBuilder &other) = delete;
			IExpressionBuilder &operator=(IExpressionBuilder &&other) = delete;
		public:
			virtual bool Build(ITokenizer *tokenizer, IExpression **target) = 0; // Build expression into "target" using specified tokenizer
			virtual bool Build(const Tokens &tokens, IExpression **target) = 0; // Build expression into "target" from specified token list
			virtual bool Build(const Tokens &tokens, const size_t first, const size_t last, IExpression **target) = 0; // Build expression into "target" from specified token list using only tokens from specified range
		};
	}
}