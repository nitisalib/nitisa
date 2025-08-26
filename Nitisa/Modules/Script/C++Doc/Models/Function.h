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
				class CParameter;

				class CFunction :public TDbActiveRecord<CFunction>, public virtual CActiveRecord
				{
				public:
					TDbAttribute<uint> Id;
					TDbAttribute<String> Version;
					TDbAttribute<uint> EntityId;
					TDbAttribute<String> AttributeLists;
					TDbAttribute<bool> isTemplate;
					TDbAttribute<String> TemplateParameters;
					TDbAttribute<String> TemplateRequires;
					TDbAttribute<String> Specifiers;
					TDbAttribute<uint> SpecifierId;
					TDbAttribute<String> Contracts;
					TDbAttribute<bool> isThrow;
					TDbAttribute<String> Throw;
					TDbAttribute<bool> isNoexcept;
					TDbAttribute<String> Noexcept;
					TDbAttribute<String> Trailing;
					TDbAttribute<String> Requires;
					TDbAttribute<bool> isAbstract;
					TDbAttribute<bool> isDefault;
					TDbAttribute<bool> isDeleted;
					TDbAttribute<String> DeleteReason;

					TDbRelation<CEntity> Entity;
					TDbRelation<CEntity> Specifier;
					TDbRelation<CParameter> Parameters;

					CFunction();
				};
			}
		}
	}
}