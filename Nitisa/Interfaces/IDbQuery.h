// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "../Db/DbActiveRecordPrimaryKey.h"
#include "../Db/DbBaseActiveRecord.h"
#include "../Db/DbCondition.h"
#include "../Db/DbOrderByArray.h"
#include "IDbAttribute.h"
#include "IDbRelation.h"
#include "IReleasable.h"
#include <vector>

namespace nitisa
{
	class IDbQuery : public virtual IReleasable
	{
	public:
		struct DbJoin // Join description
		{
			String Table;
			String Alias;
			DbCondition On;
		};

		using DbJoins = std::vector<DbJoin>;

		struct DbUnion // Union description
		{
			ReleasablePtr<IDbQuery> Query;
			bool All;
		};

		using DbUnions = std::vector<DbUnion>;
	protected:
		IDbQuery() = default;
		~IDbQuery() = default;
		IDbQuery(const IDbQuery &other) = delete;
		IDbQuery(IDbQuery &&other) = delete;
		IDbQuery &operator=(const IDbQuery &other) = delete;
		IDbQuery &operator=(IDbQuery &&other) = delete;
	protected:
		StringKeyValueArray m_aSelect; // [{ column|expression, alias }, ...]
		bool m_bDistinct;
		StringKeyValueArray m_aFrom; // [{ table, alias }, ...]
		DbJoins m_aInnerJoins; // [ { { table, alias }, on_condition }, ...]
		DbJoins m_aLeftJoins; // [ { { table, alias }, on_condition }, ...]
		DbJoins m_aRightJoins; // [ { { table, alias }, on_condition }, ...]
		DbCondition m_pWhere;
		StringArray m_aGroupBy;
		DbCondition m_pHaving;
		DbOrderByArray m_aOrderBy; // [{ column, DbOrderBy }, ...]
		int64 m_iLimit;
		int64 m_iOffset;
		DbUnions m_aUnions;
		String m_sInto;
		String m_sTable;
		StringArray m_aWith;

		// Following helper methods are used to modify Active Record model
		void setActiveRecordNew(CDbBaseActiveRecord *model, const bool value) const
		{
			model->m_bNewRecord = value;
		}

		void setActiveRecordPrimaryKey(CDbBaseActiveRecord *model, const DbActiveRecordPrimaryKey &value) const
		{
			model->m_sPrimaryKey = value;
		}

		void setAttributeValue(IDbAttribute *attr, const DbValue &value)
		{
			attr->SetInternal(value, false);
		}

		void Relation_LoadRelations(IDbRelation *relation, std::vector<CDbBaseActiveRecord *> &parent_models, std::vector<CDbBaseActiveRecord *> &out_models)
		{
			relation->LoadRelations(parent_models, out_models);
		}
	public:
		// Read-only references to the protected members
		StringKeyValueArray const &aSelect{ m_aSelect };
		bool const &bDistinct{ m_bDistinct };
		StringKeyValueArray const &aFrom{ m_aFrom };
		DbJoins const &aInnerJoin{ m_aInnerJoins };
		DbJoins const &aLeftJoin{ m_aLeftJoins };
		DbJoins const &aRightJoin{ m_aRightJoins };
		DbCondition const &pWhere{ m_pWhere };
		StringArray const &aGroupBy{ m_aGroupBy };
		DbCondition const &pHaving{ m_pHaving };
		DbOrderByArray const &aOrderBy{ m_aOrderBy };
		int64 const &iLimit{ m_iLimit };
		int64 const &iOffset{ m_iOffset };
		DbUnions const &aUnion{ m_aUnions };
		String const &sInto{ m_sInto };
		String const &sTable{ m_sTable };
		StringArray const &aWith{ m_aWith };
	};
}