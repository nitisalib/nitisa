// This file is a part of Nitisa L3GameServer
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://l3.nitisa.com
// Download: http://l3.nitisa.com/downloads
// Documentation: http://l3.nitisa.com/documentation
// License: http://l3.nitisa.com/site/license

#pragma once

#include "../../../../Core/Aliases.h"
#include "../../../../Core/Strings.h"
#include "../../../../Db/DbActiveRecord.h"
#include "../../../../Db/DbAttribute.h"
#include "../../../../Db/DbRelation.h"
#include "../ActiveRecord.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			namespace models
			{
				class CEntity;

				class CModule :public TDbActiveRecord<CModule>, public virtual CActiveRecord
				{
				public:
					TDbAttribute<uint> Id;
					TDbAttribute<String> Version;
					TDbAttribute<uint> EntityId;
					TDbAttribute<String> AttributeLists;
					TDbAttribute<String> Name;
					TDbAttribute<String> Partition;
					TDbAttribute<bool> isExported;
					TDbAttribute<bool> isPrivate;

					TDbRelation<CEntity> Entity;

					CModule();
				};
			}
		}
	}
}