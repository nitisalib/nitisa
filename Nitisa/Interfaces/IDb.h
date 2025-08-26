// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "../Db/DbOdbcVersion.h"
#include "../Db/DbStatus.h"
#include "IReleasable.h"
#include <vector>

namespace nitisa
{
	class IDbConnection;
	class IDbMigration;
	class IDbStatement;
	class IDbQueryBuilder;
	class IErrorListener;
	class IWindow;

	class IDb :public virtual IReleasable
	{
	public:
		using Migrations = std::vector<ReleasablePtr<IDbMigration>>;
	protected:
		IDb() = default;
		~IDb() = default;
		IDb(const IDb &other) = delete;
		IDb(IDb &&other) = delete;
		IDb &operator=(const IDb &other) = delete;
		IDb &operator=(IDb &&other) = delete;
	protected:
		PlatformHandle m_hHandle;
		DbStatus m_eStatus;
		IErrorListener *m_pErrorListener;
		bool m_bAssignErrorListener;
	public:
		PlatformHandle const &Handle{ m_hHandle }; // Platform-dependent environment handle
		DbStatus const &Status{ m_eStatus }; // Manager status
		IErrorListener* const &ErrorListener{ m_pErrorListener }; // Assigned error listener
		bool const &AssignErrorListener{ m_bAssignErrorListener }; // Whether error listener should be also automatically assigned to created connections

		virtual DbOdbcVersion getOdbcVersion() = 0; // Return ODBC version which will be used in initialization
		virtual int getDataSourceCount() = 0; // Return count of found data sources. Works only after successful initialization
		virtual StringKeyValue getDataSource(const int index) = 0; // Return data source description by index or empty value if index is out of bounds. Works only after successful initialization
		virtual StringKeyValueArray getDataSources(const bool force = false) = 0; // Return available data sources. Result is cached after the first call. To refresh the cache use force = true. Works only after successful initialization
		virtual int getDriverCount() = 0; // Return count of found data drivers. Works only after successful initialization
		virtual StringKeyValue getDriver(const int index) = 0; // Return data driver name by index. Works only after successful initialization
		virtual StringKeyValueArray getDrivers(const bool force = false) = 0; // Return all found data drivers. Works only after successful initialization
		virtual int getConnectionCount() = 0; // Return number of created and not yet released connections
		virtual IDbConnection *getConnection(const int index) = 0; // Return connection by index

		virtual void setErrorListener(IErrorListener *value) = 0; // Assign new error listener. nullptr value if also accepted
		virtual bool setAssignErrorListener(const bool value) = 0; // Set whether error listener should or should not be also automatically assigned to all new connections
		virtual bool setOdbcVersion(const DbOdbcVersion value) = 0; // Set ODBC version to be used at initialization process. Can be called only on uninitialized object

		// Query builders (all registered ones are automatically released on shutdown; unregistering keeps query builder untouched, it isn't released)
		virtual bool RegisterQueryBuilder(const String& name, IDbQueryBuilder* query_builder) = 0; // Register query builder with specified name. Return false if query_builder is empty or a one with the same name is already registered
		virtual bool UnregisterQueryBuilder(const String& name) = 0; // Unregister query builder by name. Return false if query builder with specified name is not found
		virtual bool UnregisterQueryBuilder(IDbQueryBuilder *query_builder) = 0; // Unregister query builder. Return false if query builder with specified name is not found
		virtual bool UnregisterQueryBuilders() = 0; // Unregister all query builders. Return false if there was no query builders registered
		virtual IDbQueryBuilder* FindQueryBuilder(const String& name) = 0; // Find query builder by specified name

		// Migrations
		virtual bool RunMigrations(const String& migration_table, IDbConnection* connection, IDbQueryBuilder* qb, Migrations& migrations) = 0;
		virtual bool RunMigrations(const String &migration_table, IDbStatement *statement, IDbQueryBuilder *qb, Migrations &migrations) = 0;
		virtual bool RunMigration(const String& migration_table, IDbConnection* connection, IDbQueryBuilder* qb, ReleasablePtr<IDbMigration>& migration) = 0;
		virtual bool RunMigration(const String &migration_table, IDbStatement *statement, IDbQueryBuilder *qb, ReleasablePtr<IDbMigration> &migration) = 0;
		virtual bool RevertMigration(const String& migration_table, IDbConnection* connection, IDbQueryBuilder* qb, ReleasablePtr<IDbMigration>& migration) = 0;
		virtual bool RevertMigration(const String &migration_table, IDbStatement *statement, IDbQueryBuilder *qb, ReleasablePtr<IDbMigration> &migration) = 0;

		// Initialization
		virtual bool Initialize() = 0; // Try to initialize the manager. If success or it was initialized before, increase reference counter and return true. If fails or failed before do not increase reference counter, just returns false

		// Connection
		virtual IDbConnection *Connect(const String &connection_options, const bool prompt, IWindow *window = nullptr) = 0; // Connect using connection string
		virtual IDbConnection *Connect(const String &driver, const String &server = L"", const int port = 0, const String &username = L"", const String &password = L"", const String &database = L"") = 0; // Connect using parameters
		virtual IDbConnection *ConnectIf(const String &connection_options, const bool prompt, IWindow *window = nullptr) = 0; // Connect using connection string. If connection with the same connection options already exists, increase its reference counter and return that connection instead of creation a new one. If such connection doesn't exist, create a new one
		virtual IDbConnection *ConnectIf(const String &driver, const String &server = L"", const int port = 0, const String &username = L"", const String &password = L"", const String &database = L"") = 0; // Connect using parameters. If connection with the same connection options already exists, increase its reference counter and return that connection instead of creation a new one. If such connection doesn't exist, create a new one
	};
}