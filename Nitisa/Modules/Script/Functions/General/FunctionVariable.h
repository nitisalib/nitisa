// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Function.h"
#include "../../Core/Variable.h"

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class CFunctionVariable :public virtual CFunction
		{
		public:
			// IFunction methods
			bool Run() override;

			CFunctionVariable(IErrorListener *error_listener, Variable &value);
		};
	}
}