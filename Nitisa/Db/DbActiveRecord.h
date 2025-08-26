// This file is a part of Nitisa L3GameServer
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://l3.nitisa.com
// Download: http://l3.nitisa.com/downloads
// Documentation: http://l3.nitisa.com/documentation
// License: http://l3.nitisa.com/site/license

#pragma once

#include "../Core/Releasable.h"
#include "DbActiveQuery.h"
#include "DbBaseActiveRecord.h"
#include "DbCondition.h"
#include "DbDelete.h"
#include "DbSet.h"
#include "DbUpdate.h"

namespace nitisa
{
	class CDbCondition;

	template<class BaseType>
	class TDbActiveRecord :public CDbBaseActiveRecord
	{
	public:
		TDbActiveRecord(const String &table) : // Constructor
			CDbBaseActiveRecord(table)
		{

		}

		static ReleasablePtr<TDbActiveQuery<BaseType>> Find() // Return active query
		{
			return new TDbActiveQuery<BaseType>();
		}

		static ReleasablePtr<BaseType> FindOne() // Return first found record
		{
			TDbActiveQuery<BaseType> query;
			return query.One();
		}

		static ReleasablePtr<BaseType> FindOne(DbCondition condition) // Return first found record by condition
		{
			TDbActiveQuery<BaseType> query;
			return query.Where(condition)->One();
		}

		static ReleasablePtr<BaseType> FindOne(const DbConditions &conditions) // Return first found record by conditions joined by AND operator
		{
			TDbActiveQuery<BaseType> query;
			return query.Where(conditions)->One();
		}

		static std::vector<ReleasablePtr<BaseType>> FindAll() // Return all found records
		{
			TDbActiveQuery<BaseType> query;
			return query.All();
		}

		static std::vector<ReleasablePtr<BaseType>> FindAll(DbCondition condition) // Return all found records by condition
		{
			TDbActiveQuery<BaseType> query;
			return query.Where(condition)->All();
		}

		static std::vector<ReleasablePtr<BaseType>> FindAll(const DbConditions &conditions) // Return all found records by conditions joined by AND operator
		{
			TDbActiveQuery<BaseType> query;
			return query.Where(conditions)->All();
		}

		static void UpdateAll(const DbSet &data) // Update all records with specified key => value (column => value) data
		{
			BaseType ar;
			CDbUpdate query{ ar.getConnection(), ar.getStatement(), ar.getQueryBuilder() };
			query.Table(ar.getTable())->Execute(data);
		}

		static void UpdateAll(const DbSet &data, DbCondition condition) // Update all records corresponding to specified condition with specified key => value (column => value) data
		{
			BaseType ar;
			CDbUpdate query{ ar.getConnection(), ar.getStatement(), ar.getQueryBuilder() };
			query.Table(ar.getTable())->Where(condition)->Execute(data);
		}

		static void UpdateAll(const DbSet &data, const DbConditions &conditions) // Update all records corresponding to specified conditions joined by AND operator with specified key => value (column => value) data
		{
			BaseType ar;
			CDbUpdate query{ ar.getConnection(), ar.getStatement(), ar.getQueryBuilder()};
			query.Table(ar.getTable())->Where(conditions)->Execute(data);
		}

		static void DeleteAll() // Delete all records
		{
			BaseType ar;
			CDbDelete query{ ar.getConnection(), ar.getStatement(), ar.getQueryBuilder() };
			query.From(ar.getTable())->Execute();
		}

		static void DeleteAll(DbCondition condition) // Delete all records corresponding to specified condition
		{
			BaseType ar;
			CDbDelete query{ ar.getConnection(), ar.getStatement(), ar.getQueryBuilder() };
			query.From(ar.getTable())->Where(condition)->Execute();
		}

		static void DeleteAll(const DbConditions &conditions) // Delete all records corresponding to specified conditions joined by AND operator
		{
			BaseType ar;
			CDbDelete query{ ar.getConnection(), ar.getStatement(), ar.getQueryBuilder() };
			query.From(ar.getTable())->Where(conditions)->Execute();
		}
	};
}