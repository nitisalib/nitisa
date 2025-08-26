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
		class CFunctionLiteral :public virtual CFunction
		{
		private:
			Variable m_sValue;
			Variable m_sStore;
		public:
			// IFunction methods
			bool Run() override;

			CFunctionLiteral(IErrorListener *error_listener, const Variable &value);
		};
	}
}