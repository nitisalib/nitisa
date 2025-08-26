// This file is a part of Nitisa framework
// Copyright © 2024 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/ErrorInfo.h"
#include "../Core/Strings.h"
#include "../Interfaces/IErrorListener.h"

namespace nitisa
{
	class IDbConnection;
	class IDbQueryBuilder;
	class IDbStatement;

	class CDbTransaction
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
		bool m_bFinished;
		CErrorListener m_cErrorListener;
	public:
		CDbTransaction(IDbConnection* connection, IDbStatement *statement, IDbQueryBuilder* qb, const String& options = L""); // Constructor. "connection" is ignored if "statement" is specified. Either "connection" or "statement" is required. "qb" is required
		~CDbTransaction(); // Destructor. Automatically rolls back transaction if it was not committed

		void Commit(); // Commit transaction
		void RollBack(); // Roll back transaction
	};
}