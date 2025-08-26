// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/ErrorInfo.h"
#include "../Core/Releasable.h"
#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "../Interfaces/IDbQuery.h"
#include "../Interfaces/IErrorListener.h"
#include "DbCondition.h"
#include "DbOrder.h"
#include "DbOrderByArray.h"
#include "DbRow.h"
#include "DbSet.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IDbConnection;
	class IDbQueryBuilder;
	class IDbStatement;

	class CDbUpdate :public virtual IDbQuery, public CReleasable
	{
	private:
		class CErrorListener :public virtual IErrorListener
		{
		public:
			String Error;

			void NotifyOnError(const AnsiString &function, const int line, const ErrorInfo &info, const StringKeyValueArray &args = EmptyStringKeyValueArray) override;
		};

		class CConnectionErrorListenerLock
		{
		private:
			IDbConnection *m_pConnection;
			IErrorListener *m_pOld;
		public:
			CConnectionErrorListenerLock(IDbConnection *connection, IErrorListener *listener);
			~CConnectionErrorListenerLock();
		};

		class CStatementErrorListenerLock
		{
		private:
			IDbStatement *m_pStatement;
			IErrorListener *m_pOld;
		public:
			CStatementErrorListenerLock(IDbStatement *statement, IErrorListener *listener);
			~CStatementErrorListenerLock();
		};
	private:
		IDbConnection *m_pConnection;
		IDbStatement *m_pStatement;
		IDbQueryBuilder *m_pQueryBuilder;
		CErrorListener m_cErrorListener;
	public:
		CDbUpdate(IDbConnection *connection, IDbStatement *statement, IDbQueryBuilder *qb); // Constructor. "connection" is ignored if "statement" is specified. Either "connection" or "statement" is required. "qb" is required

		// Query building
		CDbUpdate *Table(const String &table); // Set table to be updated
		CDbUpdate *Where(DbCondition condition); // Set delete condition
		CDbUpdate *Where(const DbConditions &conditions); // Set delete conditions joined by AND operator
		CDbUpdate *AndWhere(DbCondition condition); // Add delete condition joined by AND operator
		CDbUpdate *OrWhere(DbCondition condition); // Add delete condition joined by OR operator
		CDbUpdate *OrderBy(const String &column, const DbOrder &order); // Add ordering column
		CDbUpdate *OrderBy(const DbOrderByArray &columns); // Add ordering columns
		CDbUpdate *Limit(const int64 &limit = -1); // Set how many record maximum to be deleted. -1 means no limit

		// Execute
		void Execute(const StringArray &columns, const DbRow &row); // Execute update of specified columns with specified data. Throw exceptions in case of error
		void Execute(const DbSet &data); // Execute update of specified columns with specified data. Throw exceptions in case of error
	};
}