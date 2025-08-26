// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Db/DbActiveRecord.h"
#include "Nitisa/Db/DbAttribute.h"
#include "Nitisa/Db/DbMigration.h"
#include "Nitisa/Db/DbOdbcVersion.h"
#include "Nitisa/Db/DbQuery.h"
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/ErrorInfo.h"
#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Core/ReleasablePtr.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IDb.h"
#include "Nitisa/Interfaces/IReleasableListener.h"
#include <utility>
#include <vector>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IDbConnection;
	class IDbMigration;
	class IDbQueryBuilder;
	class IErrorListener;

	class CDbCondition;

	namespace platform
	{
		class CDbConnection;
		class CDbStatement;

		class CDb :public virtual IDb, public CReleasable
		{
			friend CDbConnection;
			friend CDbStatement;
		private:
			class CConnectionReleaseListener :public virtual IReleasableListener
			{
			private:
				CDb *m_pDb;
			public:
				void NotifyOnRelease(IReleasable *sender) override;

				CConnectionReleaseListener(CDb *db);
			};

			class CMigrationTable :public CDbMigration
			{
			private:
				String m_sTable;
			public:
				void Run() override;
				void Revert() override;

				CMigrationTable(const String& table, IDbConnection* connection, IDbStatement *statement, IDbQueryBuilder* qb);
			};

			class CMigrationModel :public TDbActiveRecord<CMigrationModel>
			{
			private:
				IDbConnection *m_pConnection;
				IDbStatement *m_pStatement;
				IDbQueryBuilder *m_pQueryBuilder;
			public:
				TDbAttribute<String> Name;
				TDbAttribute<DbDateTime> AppliedAt;

				IDbConnection *getConnection() override;
				IDbStatement *getStatement() override;
				IDbQueryBuilder *getQueryBuilder() override;
				
				void setTable(const String& value);
				void setConnection(IDbConnection *value);
				void setStatement(IDbStatement *value);
				void setQueryBuilder(IDbQueryBuilder *value);

				CMigrationModel();
			};
		private:
			DbOdbcVersion m_eOdbcVersion;
			std::vector<IDbConnection*> m_aConnections;
			std::vector<std::pair<String, IDbQueryBuilder*>> m_aQueryBuilders;
			StringKeyValueArray m_aDataSources;
			StringKeyValueArray m_aDrivers;

			CConnectionReleaseListener m_cConnectionReleaseListener;
			bool m_bHasDataSources;
			bool m_bHasDrivers;

			static AnsiString MakeFunctionName(const AnsiString &a, const AnsiString &b);
			static void HandleEnvError(const AnsiString &function, const int line, const ErrorInfo &error, PlatformHandle handle, IErrorListener *listener);
			static void HandleDbcError(const AnsiString &function, const int line, const ErrorInfo &error, PlatformHandle handle, IErrorListener *listener);
			static void HandleStmError(const AnsiString &function, const int line, const ErrorInfo &error, PlatformHandle handle, IErrorListener *listener);
		#if __has_include(<sqlext.h>)
		#ifndef _WIN32
			static String UTF16ToString(const std::u16string &str);
			static std::u16string StringToUTF16(const String &str);
		#endif
		#endif

			void LoadDataSources();
			void LoadDrivers();
			void CreateMigrationTable(const String& name, IDbConnection* connection, IDbQueryBuilder* qb);
		protected:
			void BeforeRelease() override;
		public:
			// IReleasable methods
			bool Release(const bool force = false) override;

			// IDb getters
			DbOdbcVersion getOdbcVersion() override;
			int getDataSourceCount() override;
			StringKeyValue getDataSource(const int index) override;
			StringKeyValueArray getDataSources(const bool force = false) override;
			int getDriverCount() override;
			StringKeyValue getDriver(const int index) override;
			StringKeyValueArray getDrivers(const bool force = false) override;
			int getConnectionCount() override;
			IDbConnection *getConnection(const int index) override;

			// IDb setters
			void setErrorListener(IErrorListener *value) override;
			bool setAssignErrorListener(const bool value) override;
			bool setOdbcVersion(const DbOdbcVersion value) override;

			// IDb query builders
			bool RegisterQueryBuilder(const String& name, IDbQueryBuilder* query_builder) override;
			bool UnregisterQueryBuilder(const String& name) override;
			bool UnregisterQueryBuilder(IDbQueryBuilder* query_builder) override;
			bool UnregisterQueryBuilders() override;
			IDbQueryBuilder* FindQueryBuilder(const String& name) override;

			// IDb migrations
			bool RunMigrations(const String& migration_table, IDbConnection* connection, IDbQueryBuilder* qb, Migrations& migrations) override;
			bool RunMigrations(const String& migration_table, IDbStatement* statement, IDbQueryBuilder* qb, Migrations& migrations) override;
			bool RunMigration(const String& migration_table, IDbConnection* connection, IDbQueryBuilder* qb, ReleasablePtr<IDbMigration>& migration) override;
			bool RunMigration(const String& migration_table, IDbStatement* statement, IDbQueryBuilder* qb, ReleasablePtr<IDbMigration>& migration) override;
			bool RevertMigration(const String& migration_table, IDbConnection* connection, IDbQueryBuilder* qb, ReleasablePtr<IDbMigration>& migration) override;
			bool RevertMigration(const String& migration_table, IDbStatement* statement, IDbQueryBuilder* qb, ReleasablePtr<IDbMigration>& migration) override;

			// IDb initialization
			bool Initialize() override;

			// IDb connection
			IDbConnection *Connect(const String &connection_options, const bool prompt, IWindow *window = nullptr) override;
			IDbConnection *Connect(const String &driver, const String &server = L"", const int port = 0, const String &username = L"", const String &password = L"", const String &database = L"") override;
			IDbConnection *ConnectIf(const String &connection_options, const bool prompt, IWindow *window = nullptr) override;
			IDbConnection *ConnectIf(const String &driver, const String &server = L"", const int port = 0, const String &username = L"", const String &password = L"", const String &database = L"") override;

			CDb();
			~CDb() override;
		};
	}
}