// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			CExpression::CExpression() :
				CReleasable(),
				Begin{ nullptr }
			{

			}

			CExpression::CExpression(List *begin) :
				CReleasable(),
				Begin{ begin }
			{

			}

			CExpression::CExpression(List *begin, std::vector<List *> &priors) :
				CReleasable(),
				Begin{ begin },
				Priors{ priors }
			{

			}

			CExpression::CExpression(const String &name) :
				CReleasable(),
				Begin{ nullptr },
				Name{ name }
			{

			}

			void CExpression::BeforeRelease()
			{
				for (auto item : Items)
					item->Release();
				Items.clear();
			}
		}
	}
}