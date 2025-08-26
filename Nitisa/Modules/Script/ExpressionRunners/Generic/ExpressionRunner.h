// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../../Core/Strings.h"
#include "../../Core/ExpressionRunner.h"
#include "../../Interfaces/IFunction.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	namespace script
	{
		class IExpression;
		class IFunctionFactory;

		namespace generic
		{
			class CExpressionRunner :public virtual script::CExpressionRunner
			{
			private:
				IFunctionFactory *m_pDefaultFunctionFactory;
				IFunctionFactory *m_pFunctionFactory;

				bool CreateFunction(const String &name, const IFunction::Arguments &arguments, IFunction **target, IFunction *modify);
				void FreeArguments(IFunction::Arguments &arguments);

				bool MakeOperand(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeOperators(IExpression *expression, IFunction **target);
				bool MakeBool(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeNull(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeInteger(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeFloat(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeString(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeVariable(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeIdentifier(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeBrace(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeCall(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeSubscript(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeCast(IExpression *expression, IFunction **target, IFunction **modify);
				bool MakeCast(IExpression *expression, IFunction **target, IFunction **modify, IFunction *operand);
				bool MakeSequence(IExpression *expression, IFunction **target, IFunction **modify);
			protected:
				void BeforeRelease() override;
			public:
				// IExpressionRunner getters
				IFunctionFactory *getFunctionFactory() override;

				// IExpressionRunner setters
				bool setFunctionFactory(IFunctionFactory *factory) override;

				// IExpressionRunner methods
				bool Prepare(IExpression *expression) override;
				bool Run() override;

				CExpressionRunner(const bool with_function_factory = true);

				bool Prepare(const String &source); // Tokenize, build expression and prepare it from specified source. Generic tokenizer and expression builder is used
			};
		}
	}
}