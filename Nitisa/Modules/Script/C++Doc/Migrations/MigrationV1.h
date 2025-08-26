// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../../Db/DbMigration.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			namespace migrations
			{
				class CMigrationV1 :public CDbMigration
				{
				public:
					void Run() override;

					CMigrationV1();
				};
			}
		}
	}
}