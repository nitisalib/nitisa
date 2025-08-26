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
				class CComment;
				class CFile;
				class CTag;

				class CEntity :public TDbActiveRecord<CEntity>, public virtual CActiveRecord
				{
				public:
					TDbAttribute<uint> Id;
					TDbAttribute<String> Version;
					TDbAttribute<uint> ParentId;
					TDbAttribute<String> Name;
					TDbAttribute<String> Qualified;
					TDbAttribute<String> Path;
					TDbAttribute<String> Type;
					TDbAttribute<String> Access;
					TDbAttribute<String> Language;
					TDbAttribute<bool> isExported;
					TDbAttribute<uint> FileId;

					TDbRelation<CEntity> Parent;
					TDbRelation<CTag> Tags;
					TDbRelation<CComment> Comments;
					TDbRelation<CEntity> Entities;
					TDbRelation<CFile> File;

					CEntity();
				};
			}
		}
	}
}