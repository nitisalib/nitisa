// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../../../Interfaces/IReleasable.h"
#include "../Core/Variable.h"

namespace nitisa
{
	namespace script
	{
		class IExpression;
		class IFunctionFactory;

		class IExpressionRunner :public virtual IReleasable
		{
		protected:
			IExpressionRunner() = default;
			~IExpressionRunner() = default;
			IExpressionRunner(const IExpressionRunner &other) = delete;
			IExpressionRunner(IExpressionRunner &&other) = delete;
			IExpressionRunner &operator=(const IExpressionRunner &other) = delete;
			IExpressionRunner &operator=(IExpressionRunner &&other) = delete;
		protected:
			Variable m_sResult;
		public:
			Variable &Result{ m_sResult }; // Variable storing result of expression execution

			virtual IFunctionFactory *getFunctionFactory() = 0; // Return function factory
			virtual size_t getVariableCount() const = 0; // Return variable count
			virtual Variable *getVariable(const size_t index) = 0; // Return variable by index
			virtual Variable *getVariable(const String &name) = 0; // Return variable by name

			virtual bool setFunctionFactory(IFunctionFactory *factory) = 0; // Assign function factory

			virtual bool AddVariable(const String &name, const Variable &variable) = 0; // Add variable
			virtual bool DeleteVariable(const size_t index) = 0; // Delete variable by index
			virtual bool DeleteVariable(const String &name) = 0; // Delete variable by name
			virtual bool DeleteVariables() = 0; // Delete all variables

			virtual bool Prepare(IExpression *expression) = 0; // Prepare expression
			virtual bool Run() = 0; // Run previously successfully prepared expression
		};
	}
}