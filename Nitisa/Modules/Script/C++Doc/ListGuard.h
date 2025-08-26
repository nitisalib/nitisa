// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "List.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			class ListGuard
			{
			private:
				List *m_pList;
				List **m_pPList;
			public:
				ListGuard(List *list);
				ListGuard(List **plist);
				~ListGuard();

				operator List *();

				void Free();
			};
		}
	}
}