// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/ErrorInfo.h"
#include "../Core/Releasable.h"
#include "../Core/Strings.h"
#include "../Interfaces/IDbQuery.h"
#include "../Interfaces/IErrorListener.h"
#include "DbRow.h"
#include "DbRows.h"
#include "DbSet.h"
#include "DbValue.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IDbConnection;
	class IDbQueryBuilder;
	class IDbStatement;

	class CDbInsert :public virtual IDbQuery, public CReleasable
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
		CDbInsert(IDbConnection *connection, IDbStatement *statement, IDbQueryBuilder *qb); // Constructor. "connection" is ignored if "statement" is specified. Either "connection" or "statement" is required. "qb" is required

		// Query building
		CDbInsert *Into(const String &table); // Set table where data should be inserted into

		// Execute
		CDbInsert *Execute(const StringArray &columns, const DbRow &row, const String &on_duplicate_update = L""); // Insert one row. Throw exceptions in case of error
		CDbInsert *Execute(const StringArray &columns, const DbRows &rows, const String &on_duplicate_update = L""); // Insert multiple rows. Throw exceptions in case of error
		CDbInsert *Execute(const DbSet &data, const String &on_duplicate_update = L""); // Insert row data specified as array of key => value pairs. Throw exceptions in case of error
		DbValue Id(); // Return last inserted Id. Throw exceptions in case of error
	};
}