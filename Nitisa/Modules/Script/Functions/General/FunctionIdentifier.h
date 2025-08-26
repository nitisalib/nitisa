// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../../Core/Strings.h"
#include "../../Core/Function.h"
#include "../../Core/Variable.h"

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class CFunctionIdentifier :public virtual CFunction
		{
		private:
			Variable m_sValue;
			String m_sStore;
		public:
			// IFunction methods
			bool Run() override;

			CFunctionIdentifier(IErrorListener *error_listener, const String &value);
		};
	}
}