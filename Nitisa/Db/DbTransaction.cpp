// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region CErrorListener
	void CDbTransaction::CErrorListener::NotifyOnError(const AnsiString& function, const int line, const ErrorInfo& info, const StringKeyValueArray& args)
	{
		Error = L"ERROR " + ToString(info.Code) + L" in " + AnsiToString(function) + L":" + ToString(line) + L": " + ReplaceAll(info.Message, args);
	}
#pragma endregion

#pragma region CConnectionErrorListenerLock
	CDbTransaction::CConnectionErrorListenerLock::CConnectionErrorListenerLock(IDbConnection* connection, IErrorListener* listener) :
		m_pConnection{ connection },
		m_pOld{ connection->ErrorListener }
	{
		m_pConnection->setErrorListener(listener);
	}

	CDbTransaction::CConnectionErrorListenerLock::~CConnectionErrorListenerLock()
	{
		m_pConnection->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region CStatementErrorListenerLock
	CDbTransaction::CStatementErrorListenerLock::CStatementErrorListenerLock(IDbStatement *statement, IErrorListener *listener) :
		m_pStatement{ statement },
		m_pOld{ statement->ErrorListener }
	{
		m_pStatement->setErrorListener(listener);
	}

	CDbTransaction::CStatementErrorListenerLock::~CStatementErrorListenerLock()
	{
		m_pStatement->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region Constructor & destructor
	CDbTransaction::CDbTransaction(IDbConnection* connection, IDbStatement *statement, IDbQueryBuilder* qb, const String& options) :
		m_pConnection{ connection },
		m_pStatement{ statement },
		m_pQueryBuilder{ qb },
		m_bFinished{ false }
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();
		
		String sql;
		if (!m_pQueryBuilder->StartTransaction(options, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

		// Prepare statement
		ReleasablePtr<IDbStatement> st;
		if (!m_pStatement)
		{
			CConnectionErrorListenerLock e_lock{ m_pConnection, &m_cErrorListener };
			st = m_pConnection->CreateStatement();
			if (!st)
				throw DbExceptionCreateStatement(m_cErrorListener.Error);
		}
		else
		{
			st = m_pStatement;
			st->AddRef();
		}
		CStatementErrorListenerLock e_lock{ st, &m_cErrorListener };

		// Execute statement
		DbResult result{ st->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	CDbTransaction::~CDbTransaction()
	{
		if (!m_bFinished)
		{
			String sql;
			if (m_pQueryBuilder->RollBack(sql))
			{
				if (!m_pStatement)
				{
					ReleasablePtr<IDbStatement> statement{ m_pConnection->CreateStatement() };
					if (statement)
						statement->Execute(sql);
				}
				else
					m_pStatement->Execute(sql);
			}
		}
	}
#pragma endregion

#pragma region Methods
	void CDbTransaction::Commit()
	{
		if (!m_bFinished)
		{
			String sql;
			if (!m_pQueryBuilder->Commit(sql))
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
			DbResult result{ statement->Execute(sql) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);

			m_bFinished = true;
		}
	}

	void CDbTransaction::RollBack()
	{
		if (!m_bFinished)
		{
			String sql;
			if (!m_pQueryBuilder->RollBack(sql))
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
			DbResult result{ statement->Execute(sql) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);

			m_bFinished = true;
		}
	}
#pragma endregion
}