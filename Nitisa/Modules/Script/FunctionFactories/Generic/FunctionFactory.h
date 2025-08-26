// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../../Core/Releasable.h"
#include "../../../../Core/Strings.h"
#include "../../Interfaces/IFunction.h"
#include "../../Interfaces/IFunctionFactory.h"

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		namespace generic
		{
			class CFunctionFactory :public virtual IFunctionFactory, public virtual CReleasable
			{
			public:
				IFunction *Create(const String &name, IErrorListener *error_listener, const IFunction::Arguments &arguments, IFunction *modify) override;

				CFunctionFactory();
			};
		}
	}
}