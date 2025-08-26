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
#include "IFunction.h"

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IFunctionFactory :public virtual IReleasable
		{
		protected:
			IFunctionFactory() = default;
			~IFunctionFactory() = default;
			IFunctionFactory(const IFunctionFactory &other) = delete;
			IFunctionFactory(IFunctionFactory &&other) = delete;
			IFunctionFactory &operator=(const IFunctionFactory &other) = delete;
			IFunctionFactory &operator=(IFunctionFactory &&other) = delete;
		public:
			virtual IFunction *Create(const String &name, IErrorListener *error_listener, const IFunction::Arguments &arguments, IFunction *modify) = 0; // Create function. "modify" is only for argument changing operator (like "++" or "="), it points to the function holding operand which actually should be changed
		};
	}
}