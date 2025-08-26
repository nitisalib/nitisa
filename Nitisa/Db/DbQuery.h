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
#include "../Interfaces/IDbConnection.h"
#include "../Interfaces/IDbQuery.h"
#include "../Interfaces/IDbQueryBuilder.h"
#include "../Interfaces/IDbStatement.h"
#include "../Interfaces/IErrorListener.h"
#include "DbCondition.h"
#include "DbExceptionBuildQuery.h"
#include "DbExceptionCreateStatement.h"
#include "DbExceptionExecuteStatement.h"
#include "DbExceptionNoConnection.h"
#include "DbExceptionNoQueryBuilder.h"
#include "DbExceptionNoResult.h"
#include "DbOrder.h"
#include "DbOrderByArray.h"
#include "DbResult.h"
#include "DbRow.h"
#include "DbRows.h"
#include "DbValue.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class CDbQuery :public virtual IDbQuery, public CReleasable
	{
	private:
		class CErrorListener :public virtual IErrorListener
		{
		public:
			String Error;

			void NotifyOnError(const AnsiString& function, const int line, const ErrorInfo& info, const StringKeyValueArray& args = EmptyStringKeyValueArray) override;
		};

		class CConnectionErrorListenerLock
		{
		private:
			IDbConnection* m_pConnection;
			IErrorListener* m_pOld;
		public:
			CConnectionErrorListenerLock(IDbConnection* connection, IErrorListener* listener);
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
		IDbConnection* m_pConnection;
		IDbStatement* m_pStatement;
		IDbQueryBuilder* m_pQueryBuilder;
		CErrorListener m_cErrorListener;
	public:
		CDbQuery(const String& table, IDbConnection* connection, IDbStatement *statement, IDbQueryBuilder* qb); // Constructor. "connection" is ignored if "statement" is specified. Either "connection" or "statement" is required. "table" and "qb" are required

		// Query building
		CDbQuery* Select(const String& column); // Add column to be selected from DB
		CDbQuery* Select(const String& column, const String& alias); // Add column with alias to be selected from DB
		CDbQuery* Select(const StringKeyValue& column); // Add column with alias to be selected from DB
		CDbQuery* Select(const StringArray& columns); // Add columns to be selected from DB
		CDbQuery* Select(const StringKeyValueArray& columns); // Add columns with alias to be selected from DB
		CDbQuery* Distinct(const bool& value); // Sets whether only unique values should be selected
		CDbQuery* From(const String& table); // Add table from which data is to be selected
		CDbQuery* From(const String& table, const String& alias); // Add table with alias from which data is to be selected
		CDbQuery* From(const StringArray& tables); // Add tables from which data is to be selected
		CDbQuery* From(const StringKeyValueArray& tables); // Add tables with aliases from which data is to be selected
		CDbQuery* InnerJoin(const String& table, DbCondition on); // Add inner join table condition
		CDbQuery* InnerJoin(const String& table, const String& alias, DbCondition on); // Add inner join table with alias condition
		CDbQuery* InnerJoin(const DbJoin& table); // Add inner join table
		CDbQuery* LeftJoin(const String& table, DbCondition on); // Add left join table condition
		CDbQuery* LeftJoin(const String& table, const String& alias, DbCondition on); // Add left join table with alias condition
		CDbQuery* LeftJoin(const DbJoin& table); // Add left join table
		CDbQuery* RightJoin(const String& table, DbCondition on); // Add right join table condition
		CDbQuery* RightJoin(const String& table, const String& alias, DbCondition on); // Add right join table with alias condition
		CDbQuery* RightJoin(const DbJoin& table); // Add right join table
		CDbQuery* Where(DbCondition condition); // Set query condition
		CDbQuery* Where(const DbConditions &conditions); // Set query conditions joined by AND operator
		CDbQuery* AndWhere(DbCondition condition); // Add query condition joining by AND operator
		CDbQuery* OrWhere(DbCondition condition); // Add query condition joining by OR operator
		CDbQuery* GroupBy(const String& column); // Add grouping by column
		CDbQuery* GroupBy(const StringArray& columns); // Add grouping by columns
		CDbQuery* Having(DbCondition condition); // Set filter condition
		CDbQuery* Having(const DbConditions &conditions); // Set filter conditions joining by AND operator
		CDbQuery* AndHaving(DbCondition condition); // Add filter condition joining by AND operator
		CDbQuery* OrHaving(DbCondition condition); // Add filter condition joining by OR operator
		CDbQuery* OrderBy(const String& column, const DbOrder& order); // Add ordering by column
		CDbQuery* OrderBy(const DbOrderByArray& columns); // Add ordering by columns
		CDbQuery* Limit(const int64& limit = -1); // Set result maximum allowed record count. -1 means no limit or all records will be returned
		CDbQuery* Offset(const int64& offset = -1); // Set result offset or at which record start to get records. -1 means no offset or from the beginning
		CDbQuery* Union(ReleasablePtr<IDbQuery> query, const bool all = false); // Set union query
	
	#pragma region Query result
		DbValue Column(); // Executes the query and returns the first column of the result. Throw exceptions in case of error
		int64 Count(const String& column = L"*"); // Returns the number of records. Throw exceptions in case of error
		DbRows Rows(); // Executes the query and returns all rows of the result. Throw exceptions in case of error
		DbRow Row(); // Executes the query and returns first row of the result. Throw exceptions in case of error
		bool Exists(); // Return whether there is any records in query stored in this object or not. Throw exceptions in case of error

		template<class ScalarType>
		ScalarType Scalar(const String& column) // Returns the query result as a scalar value. Throw exceptions in case of error
		{
			// Check connection
			if (!m_pStatement && !m_pConnection)
				throw DbExceptionNoConnection();

			// Check query builder
			if (!m_pQueryBuilder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(m_sTable);
			String query;
			int64 old_limit{ m_iLimit };
			m_iLimit = 1;
			if (!m_pQueryBuilder->Scalar(this, column, query))
			{
				m_iLimit = old_limit;
				throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);
			}
			m_iLimit = old_limit;

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!m_pStatement)
			{
				CConnectionErrorListenerLock e_lock{ m_pConnection, &m_cErrorListener };
				statement = m_pConnection->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = m_pStatement;
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (ScalarType)result.Rows[0][0];
		}

		template<class ResultType>
		ResultType Sum(const String& column) // Returns the sum of the specified column values. Throw exceptions in case of error
		{
			// Check connection
			if (!m_pStatement && !m_pConnection)
				throw DbExceptionNoConnection();

			// Check query builder
			if (!m_pQueryBuilder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(m_sTable);
			String query;
			if (!m_pQueryBuilder->Sum(this, column, query))
				throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!m_pStatement)
			{
				CConnectionErrorListenerLock e_lock{ m_pConnection, &m_cErrorListener };
				statement = m_pConnection->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = m_pStatement;
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (ResultType)result.Rows[0][0];
		}

		template<class ResultType>
		ResultType Average(const String& column) // Returns the average of the specified column values. Throw exceptions in case of error
		{
			// Check connection
			if (!m_pStatement && !m_pConnection)
				throw DbExceptionNoConnection();

			// Check query builder
			if (!m_pQueryBuilder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(m_sTable);
			String query;
			if (!m_pQueryBuilder->Average(this, column, query))
				throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!m_pStatement)
			{
				CConnectionErrorListenerLock e_lock{ m_pConnection, &m_cErrorListener };
				statement = m_pConnection->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = m_pStatement;
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (ResultType)result.Rows[0][0];
		}

		template<class ResultType>
		ResultType Min(const String& column) // Returns the minimum of the specified column values. Throw exceptions in case of error
		{
			// Check connection
			if (!m_pStatement && !m_pConnection)
				throw DbExceptionNoConnection();

			// Check query builder
			if (!m_pQueryBuilder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(m_sTable);
			String query;
			if (!m_pQueryBuilder->Min(this, column, query))
				throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!m_pStatement)
			{
				CConnectionErrorListenerLock e_lock{ m_pConnection, &m_cErrorListener };
				statement = m_pConnection->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = m_pStatement;
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (ResultType)result.Rows[0][0];
		}

		template<class ResultType>
		ResultType Max(const String& column) // Returns the maximum of the specified column values. Throw exceptions in case of error
		{
			// Check connection
			if (!m_pStatement && !m_pConnection)
				throw DbExceptionNoConnection();

			// Check query builder
			if (!m_pQueryBuilder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(m_sTable);
			String query;
			if (!m_pQueryBuilder->Max(this, column, query))
				throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!m_pStatement)
			{
				CConnectionErrorListenerLock e_lock{ m_pConnection, &m_cErrorListener };
				statement = m_pConnection->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = m_pStatement;
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (ResultType)result.Rows[0][0];
		}
	#pragma endregion
	};
}