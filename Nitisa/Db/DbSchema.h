// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/ErrorInfo.h"
#include "../Core/Strings.h"
#include "../Interfaces/IErrorListener.h"
#include "DbValue.h"
#include <map>

namespace nitisa
{
	class IDbConnection;
	class IDbQueryBuilder;
	class IDbStatement;

	class DbSchema final
	{
	public:
		struct PrimaryKey // Primary key information
		{
			String Name; // Primary key name
			StringArray Columns; // Columns forming primary key
		};

		struct Column // Column information
		{
			DbValue DefaultValue; // Default value
		};
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
		DbSchema() = delete;
		~DbSchema() = delete;
		DbSchema(const DbSchema& other) = delete;
		DbSchema(DbSchema&& other) = delete;
		DbSchema& operator=(const DbSchema& other) = delete;
		DbSchema& operator=(DbSchema&& other) = delete;
	private:
		static CErrorListener m_cErrorListener;
		static std::map<String, PrimaryKey> m_aPrimaryKeys;
		static std::map<String, String> m_aAutoIncrementColumns;
		static std::map<String, std::map<String, Column>> m_aColumns;
	public:
		static bool getPrimaryKey(const String& table, IDbStatement* statement, IDbQueryBuilder* qb, PrimaryKey& target, const bool& refresh = false); // Query table primary key information. Throw exceptions in case of error
		static bool getPrimaryKey(const String& table, IDbConnection* connection, IDbQueryBuilder* qb, PrimaryKey& target, const bool& refresh = false); // Query table primary key information. Throw exceptions in case of error
		static bool getAutoIncrementColumn(const String& table, IDbStatement* statement, IDbQueryBuilder* qb, String& target, const bool& refresh = false); // Query table autoincrement column information. Throw exceptions in case of error
		static bool getAutoIncrementColumn(const String& table, IDbConnection* connection, IDbQueryBuilder* qb, String& target, const bool& refresh = false); // Query table autoincrement column information. Throw exceptions in case of error
		static bool getColumn(const String& table, const String& column, IDbStatement* statement, Column& target, const bool& refresh = false); // Query table column information (default value). Throw exceptions in case of error
		static bool getColumn(const String& table, const String& column, IDbConnection* connection, Column& target, const bool& refresh = false); // Query table column information (default value). Throw exceptions in case of error
	};
}