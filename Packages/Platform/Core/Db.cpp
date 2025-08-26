// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if __has_include(<sqlext.h>)
	#ifdef _WIN32
		#include <Windows.h>
	#endif
	#include <sql.h>
	#include <sqlext.h>
#endif

namespace nitisa
{
	namespace platform
	{
	#pragma region CConnectionReleaseListener
		CDb::CConnectionReleaseListener::CConnectionReleaseListener(CDb *db) :
			m_pDb{ db }
		{

		}

		void CDb::CConnectionReleaseListener::NotifyOnRelease(IReleasable *sender)
		{
			IDbConnection *connection{ cast<IDbConnection*>(sender) };
			if (connection)
			{
				for (auto pos = m_pDb->m_aConnections.begin(); pos != m_pDb->m_aConnections.end(); pos++)
					if (*pos == connection)
					{
						m_pDb->m_aConnections.erase(pos);
						return;
					}
				if (m_pDb->m_pErrorListener)
					m_pDb->m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_NOT_FOUND);
			}
			else
			{
				if (m_pDb->m_pErrorListener)
					m_pDb->m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_INVALID_SENDER, StringKeyValueArray{ StringKeyValue{ L"{type}" , L"IDbConnection" } });
			}
		}
	#pragma endregion

	#pragma region CMigration
		CDb::CMigrationTable::CMigrationTable(const String& table, IDbConnection* connection, IDbStatement *statement, IDbQueryBuilder* qb) :
			CDbMigration(L"", connection, statement, qb),
			m_sTable{ table }
		{

		}

		void CDb::CMigrationTable::Run()
		{
			CreateTable(
				m_sTable,
				{
					Column(L"name")->VarChar(255)->NotNull()->PrimaryKey(),
					Column(L"applied_at")->DateTime()->NotNull()->Default(L"CURRENT_TIMESTAMP")
				},
				{ },
				true
			);
		}

		void CDb::CMigrationTable::Revert()
		{
			DropTable(m_sTable, true);
		}
	#pragma endregion

	#pragma region CMigrationModel
		CDb::CMigrationModel::CMigrationModel() :
			TDbActiveRecord(L""),
			m_pConnection{ nullptr },
			m_pStatement{ nullptr },
			m_pQueryBuilder{ nullptr },
			Name{ this, L"name" },
			AppliedAt{ this, L"applied_at" }
		{

		}

		IDbConnection *CDb::CMigrationModel::getConnection()
		{
			return m_pConnection;
		}

		IDbStatement *CDb::CMigrationModel::getStatement()
		{
			return m_pStatement;
		}

		IDbQueryBuilder *CDb::CMigrationModel::getQueryBuilder()
		{
			return m_pQueryBuilder;
		}

		void CDb::CMigrationModel::setTable(const String& value)
		{
			m_sTable = value;
		}

		void CDb::CMigrationModel::setConnection(IDbConnection *value)
		{
			m_pConnection = value;
		}

		void CDb::CMigrationModel::setStatement(IDbStatement *value)
		{
			m_pStatement = value;
		}

		void CDb::CMigrationModel::setQueryBuilder(IDbQueryBuilder *value)
		{
			m_pQueryBuilder = value;
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CDb::CDb() :
			CReleasable(),
			m_eOdbcVersion{ DbOdbcVersion::V3_80 },
			m_cConnectionReleaseListener{ this },
			m_bHasDataSources{ false },
			m_bHasDrivers{ false }
		{
			m_iRefCount = 0;
			m_hHandle = nullptr;
			m_eStatus = DbStatus::Uninitialized;
			m_pErrorListener = nullptr;
			m_bAssignErrorListener = true;
		}

		CDb::~CDb()
		{
			for (auto qb : m_aQueryBuilders)
				qb.second->Release();
			if (m_eStatus == DbStatus::Initialized)
				BeforeRelease();
		}
	#pragma endregion

	#pragma region IReleasable methods
		bool CDb::Release(const bool force)
		{
			if (force || --m_iRefCount <= 0)
			{
				if (m_eStatus == DbStatus::Initialized)
					BeforeRelease();
				return true;
			}
			return false;
		}

		void CDb::BeforeRelease()
		{
		#if __has_include(<sqlext.h>)
			while (m_aConnections.size() > 0)
				m_aConnections[0]->Release(true);
			CReleasable::BeforeRelease();
			SQLFreeHandle(SQL_HANDLE_ENV, *reinterpret_cast<SQLHANDLE*>(&m_hHandle));
		#endif
			m_eStatus = DbStatus::Uninitialized;
			m_aDataSources.clear();
			m_aDrivers.clear();
			m_bHasDataSources = false;
			m_bHasDrivers = false;
		}
	#pragma endregion

	#pragma region IDb getters
		DbOdbcVersion CDb::getOdbcVersion()
		{
			return m_eOdbcVersion;
		}

		int CDb::getDataSourceCount()
		{
			if (!m_bHasDataSources && m_eStatus == DbStatus::Initialized)
				LoadDataSources();
			return (int)m_aDataSources.size();
		}

		StringKeyValue CDb::getDataSource(const int index)
		{
			if (!m_bHasDataSources && m_eStatus == DbStatus::Initialized)
				LoadDataSources();
			if (index >= 0 && index < (int)m_aDataSources.size())
				return m_aDataSources[index];
			return EmptyStringKeyValue;
		}

		StringKeyValueArray CDb::getDataSources(const bool force)
		{
			if (m_eStatus != DbStatus::Initialized)
				return EmptyStringKeyValueArray;
			if (m_bHasDataSources && !force)
				return m_aDataSources;
			LoadDataSources();
			return m_aDataSources;
		}

		int CDb::getDriverCount()
		{
			if (!m_bHasDrivers && m_eStatus == DbStatus::Initialized)
				LoadDrivers();
			return (int)m_aDrivers.size();
		}

		StringKeyValue CDb::getDriver(const int index)
		{
			if (!m_bHasDrivers && m_eStatus == DbStatus::Initialized)
				LoadDrivers();
			if (index >= 0 && index < (int)m_aDrivers.size())
				return m_aDrivers[index];
			return EmptyStringKeyValue;
		}

		StringKeyValueArray CDb::getDrivers(const bool force)
		{
			if (m_eStatus != DbStatus::Initialized)
				return EmptyStringKeyValueArray;
			if (m_bHasDrivers && !force)
				return m_aDrivers;
			LoadDrivers();
			return m_aDrivers;
		}

		int CDb::getConnectionCount()
		{
			return (int)m_aConnections.size();
		}

		IDbConnection *CDb::getConnection(const int index)
		{
			if (index >= 0 && index < (int)m_aConnections.size())
				return m_aConnections[index];
			return nullptr;
		}
	#pragma endregion

	#pragma region IDb setters
		void CDb::setErrorListener(IErrorListener *value)
		{
			m_pErrorListener = value;
		}

		bool CDb::setAssignErrorListener(const bool value)
		{
			if (value != m_bAssignErrorListener)
			{
				m_bAssignErrorListener = value;
				return true;
			}
			return false;
		}

		bool CDb::setOdbcVersion(const DbOdbcVersion value)
		{
			if (m_eStatus == DbStatus::Uninitialized && value != m_eOdbcVersion)
			{
				m_eOdbcVersion = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IDb query builders
		bool CDb::RegisterQueryBuilder(const String& name, IDbQueryBuilder* query_builder)
		{
			if (!query_builder || name.empty())
				return false;
			for (auto const& qb : m_aQueryBuilders)
				if (qb.first == name)
					return false;
			m_aQueryBuilders.push_back(std::pair<String, IDbQueryBuilder*>{ name, query_builder });
			return true;
		}

		bool CDb::UnregisterQueryBuilder(const String& name)
		{
			if (name.empty())
				return false;
			for (auto pos = m_aQueryBuilders.begin(); pos != m_aQueryBuilders.end(); pos++)
				if (pos->first == name)
				{
					m_aQueryBuilders.erase(pos);
					return true;
				}
			return false;
		}

		bool CDb::UnregisterQueryBuilder(IDbQueryBuilder* query_builder)
		{
			if (!query_builder)
				return false;
			for (auto pos = m_aQueryBuilders.begin(); pos != m_aQueryBuilders.end(); pos++)
				if (pos->second == query_builder)
				{
					m_aQueryBuilders.erase(pos);
					return true;
				}
			return false;
		}

		bool CDb::UnregisterQueryBuilders()
		{
			if (m_aQueryBuilders.empty())
				return false;
			m_aQueryBuilders.clear();
			return true;
		}

		IDbQueryBuilder* CDb::FindQueryBuilder(const String& name)
		{
			if (!name.empty())
				for (auto db : m_aQueryBuilders)
					if (db.first == name)
						return db.second;
			return nullptr;
		}
	#pragma endregion

	#pragma region IDb migrations
		bool CDb::RunMigrations(const String& migration_table, IDbConnection* connection, IDbQueryBuilder* qb, Migrations& migrations)
		{
			if (migration_table.empty() || !connection || !qb || migrations.empty())
				return false;
			ReleasablePtr<CMigrationTable> def_migration{ new CMigrationTable(migration_table, connection, nullptr, qb) };
			def_migration->Run();
			for (auto migration : migrations)
			{
				CDbQuery query{ migration_table, connection, nullptr, qb };
				if (!query.From(migration_table)->Where(db::Equals(String{ L"name" }, DbValue{ migration->sName }))->Exists())
				{
					migration->setConnection(connection)->setQueryBuilder(qb)->Run();
					ReleasablePtr<CMigrationModel> model{ new CMigrationModel() };
					model->setTable(migration_table);
					model->setConnection(connection);
					model->setQueryBuilder(qb);
					model->Name = migration->sName;
					model->AppliedAt = DbDateTime{ CDateTime{ true } };
					model->Save(false);
				}
			}
			return true;
		}

		bool CDb::RunMigrations(const String &migration_table, IDbStatement *statement, IDbQueryBuilder *qb, Migrations &migrations)
		{
			if (migration_table.empty() || !statement || !qb || migrations.empty())
				return false;
			ReleasablePtr<CMigrationTable> def_migration{ new CMigrationTable(migration_table, nullptr, statement, qb) };
			def_migration->Run();
			for (auto migration : migrations)
			{
				CDbQuery query{ migration_table, nullptr, statement, qb };
				if (!query.From(migration_table)->Where(db::Equals(String{ L"name" }, DbValue{ migration->sName }))->Exists())
				{
					migration->setStatement(statement)->setQueryBuilder(qb)->Run();
					ReleasablePtr<CMigrationModel> model{ new CMigrationModel() };
					model->setTable(migration_table);
					model->setStatement(statement);
					model->setQueryBuilder(qb);
					model->Name = migration->sName;
					model->AppliedAt = DbDateTime{ CDateTime{ true } };
					model->Save(false);
				}
			}
			return true;
		}

		bool CDb::RunMigration(const String& migration_table, IDbConnection* connection, IDbQueryBuilder* qb, ReleasablePtr<IDbMigration>& migration)
		{
			if (migration_table.empty() || !connection || !qb || !migration)
				return false;
			ReleasablePtr<CMigrationTable> def_migration{ new CMigrationTable(migration_table, connection, nullptr, qb) };
			def_migration->Run();
			CDbQuery query{ migration_table, connection, nullptr, qb };
			if (!query.From(migration_table)->Where(db::Equals(String{ L"name" }, DbValue{ migration->sName }))->Exists())
			{
				migration->setConnection(connection)->setQueryBuilder(qb)->Run();
				ReleasablePtr<CMigrationModel> model{ new CMigrationModel() };
				model->setTable(migration_table);
				model->setConnection(connection);
				model->setQueryBuilder(qb);
				model->Name = migration->sName;
				model->AppliedAt = DbDateTime{ CDateTime{ true } };
				model->Save(false);
			}
			return true;
		}

		bool CDb::RunMigration(const String &migration_table, IDbStatement *statement, IDbQueryBuilder *qb, ReleasablePtr<IDbMigration> &migration)
		{
			if (migration_table.empty() || !statement || !qb || !migration)
				return false;
			ReleasablePtr<CMigrationTable> def_migration{ new CMigrationTable(migration_table, nullptr, statement, qb) };
			def_migration->Run();
			CDbQuery query{ migration_table, nullptr, statement, qb };
			if (!query.From(migration_table)->Where(db::Equals(String{ L"name" }, DbValue{ migration->sName }))->Exists())
			{
				migration->setStatement(statement)->setQueryBuilder(qb)->Run();
				ReleasablePtr<CMigrationModel> model{ new CMigrationModel() };
				model->setTable(migration_table);
				model->setStatement(statement);
				model->setQueryBuilder(qb);
				model->Name = migration->sName;
				model->AppliedAt = DbDateTime{ CDateTime{ true } };
				model->Save(false);
			}
			return true;
		}

		bool CDb::RevertMigration(const String& migration_table, IDbConnection* connection, IDbQueryBuilder* qb, ReleasablePtr<IDbMigration>& migration)
		{
			if (migration_table.empty() || !connection || !qb || !migration)
				return false;
			ReleasablePtr<CMigrationTable> def_migration{ new CMigrationTable(migration_table, connection, nullptr, qb) };
			def_migration->Run();
			CDbQuery query{ migration_table, connection, nullptr, qb };
			if (query.Where(db::Equals(String{ L"name" }, DbValue{ migration->sName }))->Exists())
			{
				migration->setConnection(connection)->setQueryBuilder(qb)->Revert();
				CDbDelete del{ connection, nullptr, qb };
				del.From(migration_table)->Where(db::Equals(String{ L"name" }, DbValue{ migration->sName }))->Execute();
			}
			return true;
		}

		bool CDb::RevertMigration(const String &migration_table, IDbStatement *statement, IDbQueryBuilder *qb, ReleasablePtr<IDbMigration> &migration)
		{
			if (migration_table.empty() || !statement || !qb || !migration)
				return false;
			ReleasablePtr<CMigrationTable> def_migration{ new CMigrationTable(migration_table, nullptr, statement, qb) };
			def_migration->Run();
			CDbQuery query{ migration_table, nullptr, statement, qb };
			if (query.Where(db::Equals(String{ L"name" }, DbValue{ migration->sName }))->Exists())
			{
				migration->setStatement(statement)->setQueryBuilder(qb)->Revert();
				CDbDelete del{ nullptr, statement, qb };
				del.From(migration_table)->Where(db::Equals(String{ L"name" }, DbValue{ migration->sName }))->Execute();
			}
			return true;
		}
	#pragma endregion

	#pragma region IDb initialization
		bool CDb::Initialize()
		{
		#if __has_include(<sqlext.h>)
			if (m_eStatus == DbStatus::Initialized)
			{
				m_iRefCount++;
				return true;
			}
			if (m_eStatus == DbStatus::Uninitialized)
			{
				SQLHANDLE handle;
				SQLRETURN result{ SQLAllocHandle(SQL_HANDLE_ENV, nullptr, &handle) };
				int result_line{ __LINE__ - 1 };
				switch (result)
				{
				case SQL_SUCCESS_WITH_INFO:
				case SQL_SUCCESS:
				{
					SQLPOINTER ver{ (m_eOdbcVersion == DbOdbcVersion::V2) ? SQLPOINTER(SQL_OV_ODBC2) : ((m_eOdbcVersion == DbOdbcVersion::V3) ? SQLPOINTER(SQL_OV_ODBC3) : SQLPOINTER(SQL_OV_ODBC3_80)) };
					result = SQLSetEnvAttr(handle, SQL_ATTR_ODBC_VERSION, ver, 0);
					result_line = __LINE__ - 1;
					switch (result)
					{
					case SQL_SUCCESS:
					case SQL_SUCCESS_WITH_INFO:
						*reinterpret_cast<SQLHANDLE*>(&m_hHandle) = handle;
						m_eStatus = DbStatus::Initialized;
						m_iRefCount++;
						return true;
					case SQL_INVALID_HANDLE:
						if (m_pErrorListener)
							m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLSetEnvAttr"), result_line, ERROR_GENERAL_INVALID_HANDLE);
						break;
					case SQL_ERROR:
						if (m_pErrorListener)
							HandleEnvError(MakeFunctionName(__FUNCTION__, "SQLSetEnvAttr"), result_line, ERROR_DB_SET_ENVIRONMENT_ATTRIBUTE, m_hHandle, m_pErrorListener);
						break;
					default:
						if (m_pErrorListener)
							m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLAllocHandle"), result_line, ERROR_GENERAL_UNKNOWN);
						break;
					}
					SQLFreeHandle(SQL_HANDLE_ENV, handle);
					m_eStatus = DbStatus::Error;
					break;
				}
				case SQL_INVALID_HANDLE:
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLAllocHandle"), result_line, ERROR_GENERAL_INVALID_HANDLE);
					m_eStatus = DbStatus::Error;
					break;
				case SQL_ERROR:
					if (m_pErrorListener)
						HandleEnvError(MakeFunctionName(__FUNCTION__, "SQLAllocHandle"), result_line, ERROR_DB_ALLOCATE_ENVIRONMENT_HANDLE, m_hHandle, m_pErrorListener);
					m_eStatus = DbStatus::Error;
					break;
				default:
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLAllocHandle"), result_line, ERROR_GENERAL_UNKNOWN);
					m_eStatus = DbStatus::Error;
					break;
				}
			}
		#else
			m_eStatus = DbStatus::Unsupported;
		#endif
			return false;
		}
	#pragma endregion

	#pragma region IDb connection
		IDbConnection *CDb::Connect(const String &connection_options, const bool prompt, IWindow *window)
		{
			if (m_eStatus != DbStatus::Initialized)
			{
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_DB_UNINITIALIZED);
				return nullptr;
			}
		#if __has_include(<sqlext.h>)
			SQLHANDLE handle;
			SQLRETURN result{ SQLAllocHandle(SQL_HANDLE_DBC, *reinterpret_cast<SQLHANDLE*>(&m_hHandle), &handle) };
			int result_line{ __LINE__ - 1 };
			switch (result)
			{
			case SQL_SUCCESS_WITH_INFO:
			case SQL_SUCCESS:
			{
				SQLWCHAR *t, connection_string[2048];
				SQLSMALLINT connection_string_len;
			#ifdef _WIN32
				t = wcsdup(connection_options.c_str());
				HWND hwnd{ window ? (*reinterpret_cast<const HWND*>(&window->Handle)) : 0 };
				if (!hwnd)
					hwnd = GetDesktopWindow();
			#else
				std::u16string connection_options_utf16{ StringToUTF16(connection_options) };
				t = (SQLWCHAR*)connection_options_utf16.c_str();
				SQLHWND hwnd{ window ? (*reinterpret_cast<const SQLHWND*>(&window->Handle)) : 0 };
			#endif
				result = SQLDriverConnectW(handle, hwnd, t, (SQLSMALLINT)connection_options.length(), connection_string, 2048, &connection_string_len, prompt ? SQL_DRIVER_PROMPT : SQL_DRIVER_NOPROMPT);
				result_line = __LINE__ - 1;
			#ifdef _WIN32
				free(t);
			#endif
				switch (result)
				{
				case SQL_SUCCESS:
				case SQL_SUCCESS_WITH_INFO:
				{
				#ifdef _WIN32
					CDbConnection *connection{ new CDbConnection(*reinterpret_cast<PlatformHandle*>(&handle), connection_options, connection_string, this) };
				#else
					CDbConnection *connection{ new CDbConnection(*reinterpret_cast<PlatformHandle*>(&handle), connection_options, UTF16ToString((char16_t*)connection_string), this) };
				#endif
					connection->RegisterReleaseListener(&m_cConnectionReleaseListener);
					if (m_bAssignErrorListener)
						connection->setErrorListener(m_pErrorListener);
					m_aConnections.push_back(connection);
					return connection;
				}
				case SQL_INVALID_HANDLE:
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLDriverConnect"), result_line, ERROR_GENERAL_INVALID_HANDLE);
					break;
				case SQL_ERROR:
					if (m_pErrorListener)
						HandleDbcError(MakeFunctionName(__FUNCTION__, "SQLDriverConnect"), result_line, ERROR_DB_SET_CONNECTION_ATTRIBUTE, handle, m_pErrorListener);
					break;
				default:
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLDriverConnect"), result_line, ERROR_GENERAL_UNKNOWN);
					break;
				}
				SQLFreeHandle(SQL_HANDLE_DBC, handle);
				break;
			}
			case SQL_INVALID_HANDLE:
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLAllocHandle"), result_line, ERROR_GENERAL_INVALID_HANDLE);
				m_eStatus = DbStatus::Error;
				break;
			case SQL_ERROR:
				if (m_pErrorListener)
					HandleEnvError(MakeFunctionName(__FUNCTION__, "SQLAllocHandle"), result_line, ERROR_DB_ALLOCATE_CONNECTION_HANDLE, m_hHandle, m_pErrorListener);
				m_eStatus = DbStatus::Error;
				break;
			default:
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLAllocHandle"), result_line, ERROR_GENERAL_UNKNOWN);
				m_eStatus = DbStatus::Error;
				break;
			}
		#endif
			return nullptr;
		}

		IDbConnection *CDb::Connect(const String &driver, const String &server, const int port, const String &username, const String &password, const String &database)
		{
			if (m_eStatus != DbStatus::Initialized)
			{
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_DB_UNINITIALIZED);
				return nullptr;
			}
			if (driver.empty())
			{
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_DB_DRIVER_NAME_REQUIRED);
				return nullptr;
			}
		#if __has_include(<sqlext.h>)
			SQLHANDLE handle;
			SQLRETURN result{ SQLAllocHandle(SQL_HANDLE_DBC, *reinterpret_cast<SQLHANDLE*>(&m_hHandle), &handle) };
			int result_line{ __LINE__ - 1 };
			switch (result)
			{
			case SQL_SUCCESS_WITH_INFO:
			case SQL_SUCCESS:
			{
				String options{ L"driver=" + driver };
				if (!server.empty())
				{
					options += L";server=" + server;
					if (port > 0)
						options += L";port=" + ToString(port);
				}
				if (!username.empty())
					options += L";uid=" + username;
				if (!password.empty())
					options += L";pwd=" + password;
				if (!database.empty())
					options += L";database=" + database;
				SQLWCHAR *t, connection_string[2048];
				SQLSMALLINT connection_string_len;
			#ifdef _WIN32
				t = wcsdup(options.c_str());
			#else
				std::u16string options_utf16{ StringToUTF16(options) };
				t = (SQLWCHAR*)options_utf16.c_str();
			#endif
				result = SQLDriverConnectW(handle, nullptr, t, (SQLSMALLINT)options.length(), connection_string, 2048, &connection_string_len, SQL_DRIVER_NOPROMPT);
				result_line = __LINE__ - 1;
			#ifdef _WIN32
				free(t);
			#endif
				switch (result)
				{
				case SQL_SUCCESS:
				case SQL_SUCCESS_WITH_INFO:
				{
				#ifdef _WIN32
					CDbConnection *connection{ new CDbConnection(*reinterpret_cast<PlatformHandle*>(&handle), options, connection_string, this) };
				#else
					CDbConnection *connection{ new CDbConnection(*reinterpret_cast<PlatformHandle*>(&handle), options, UTF16ToString((char16_t*)connection_string), this) };
				#endif
					connection->RegisterReleaseListener(&m_cConnectionReleaseListener);
					if (m_bAssignErrorListener)
						connection->setErrorListener(m_pErrorListener);
					m_aConnections.push_back(connection);
					return connection;
				}
				case SQL_INVALID_HANDLE:
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLDriverConnect"), result_line, ERROR_GENERAL_INVALID_HANDLE);
					break;
				case SQL_ERROR:
					if (m_pErrorListener)
						HandleDbcError(MakeFunctionName(__FUNCTION__, "SQLDriverConnect"), result_line, ERROR_DB_SET_CONNECTION_ATTRIBUTE, handle, m_pErrorListener);
					break;
				default:
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLDriverConnect"), result_line, ERROR_GENERAL_UNKNOWN);
					break;
				}
				SQLFreeHandle(SQL_HANDLE_DBC, handle);
				break;
			}
			case SQL_INVALID_HANDLE:
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLAllocHandle"), result_line, ERROR_GENERAL_INVALID_HANDLE);
				m_eStatus = DbStatus::Error;
				break;
			case SQL_ERROR:
				if (m_pErrorListener)
					HandleEnvError(MakeFunctionName(__FUNCTION__, "SQLAllocHandle"), result_line, ERROR_DB_ALLOCATE_CONNECTION_HANDLE, m_hHandle, m_pErrorListener);
				m_eStatus = DbStatus::Error;
				break;
			default:
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLAllocHandle"), result_line, ERROR_GENERAL_UNKNOWN);
				m_eStatus = DbStatus::Error;
				break;
			}
		#endif
			return nullptr;
		}

		IDbConnection *CDb::ConnectIf(const String &connection_options, const bool prompt, IWindow *window)
		{
			for (auto connection : m_aConnections)
				if (connection->ConnectionOptions == connection_options)
				{
					connection->AddRef();
					return connection;
				}
			return Connect(connection_options, prompt, window);
		}

		IDbConnection *CDb::ConnectIf(const String &driver, const String &server, const int port, const String &username, const String &password, const String &database)
		{
			String options{ L"driver=" + driver };
			if (!server.empty())
			{
				options += L";server=" + server;
				if (port > 0)
					options += L";port=" + ToString(port);
			}
			if (!username.empty())
				options += L";uid=" + username;
			if (!password.empty())
				options += L";pwd=" + password;
			if (!database.empty())
				options += L";database=" + database;
			for (auto connection : m_aConnections)
				if (connection->ConnectionOptions == options)
				{
					connection->AddRef();
					return connection;
				}
			return Connect(driver, server, port, username, password, database);
		}
	#pragma endregion

	#pragma region Helpers
		AnsiString CDb::MakeFunctionName(const AnsiString &a, const AnsiString &b)
		{
			return a + "::" + b;
		}

		void CDb::HandleEnvError(const AnsiString &function, const int line, const ErrorInfo &error, PlatformHandle handle, IErrorListener *listener)
		{
		#if __has_include(<sqlext.h>)
			SQLWCHAR state[SQL_SQLSTATE_SIZE + 1], desc[1024];
			SQLSMALLINT desc_len;
			SQLINTEGER code;
			SQLRETURN result{ SQLGetDiagRecW(SQL_HANDLE_ENV, *reinterpret_cast<SQLHANDLE*>(&handle), 1, state, &code, desc, 1024, &desc_len) };
			int result_line{ __LINE__ - 1 };
			switch (result)
			{
			case SQL_SUCCESS:
			case SQL_SUCCESS_WITH_INFO:
			#ifdef _WIN32
				listener->NotifyOnError(function, line, error, StringKeyValueArray{ StringKeyValue{ L"{state}", state }, StringKeyValue{ L"{code}", ToString(code) }, StringKeyValue{ L"{message}", desc } });
			#else
				listener->NotifyOnError(function, line, error, StringKeyValueArray{ StringKeyValue{ L"{state}", UTF16ToString((char16_t*)state) }, StringKeyValue{ L"{code}", ToString(code) }, StringKeyValue{ L"{message}", UTF16ToString((char16_t*)desc) } });
			#endif
				break;
			case SQL_INVALID_HANDLE:
				listener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLGetDiagRec"), result_line, ERROR_GENERAL_INVALID_HANDLE);
				break;
			case SQL_NO_DATA:
				listener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLGetDiagRec"), result_line, ERROR_DB_NO_DATA);
				break;
			default:
				listener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLGetDiagRec"), result_line, ERROR_GENERAL_UNKNOWN);
			}
		#endif
		}

		void CDb::HandleDbcError(const AnsiString &function, const int line, const ErrorInfo &error, PlatformHandle handle, IErrorListener *listener)
		{
		#if __has_include(<sqlext.h>)
			SQLWCHAR state[SQL_SQLSTATE_SIZE + 1], desc[1024];
			SQLSMALLINT desc_len;
			SQLINTEGER code;
			SQLRETURN result{ SQLGetDiagRecW(SQL_HANDLE_DBC, *reinterpret_cast<SQLHANDLE*>(&handle), 1, state, &code, desc, 1024, &desc_len) };
			int result_line{ __LINE__ - 1 };
			switch (result)
			{
			case SQL_SUCCESS:
			case SQL_SUCCESS_WITH_INFO:
			#ifdef _WIN32
				listener->NotifyOnError(function, line, error, StringKeyValueArray{ StringKeyValue{ L"{state}", state }, StringKeyValue{ L"{code}", ToString(code) }, StringKeyValue{ L"{message}", desc } });
			#else
				listener->NotifyOnError(function, line, error, StringKeyValueArray{ StringKeyValue{ L"{state}", UTF16ToString((char16_t*)state) }, StringKeyValue{ L"{code}", ToString(code) }, StringKeyValue{ L"{message}", UTF16ToString((char16_t*)desc) } });
			#endif
				break;
			case SQL_INVALID_HANDLE:
				listener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLGetDiagRec"), result_line, ERROR_GENERAL_INVALID_HANDLE);
				break;
			case SQL_NO_DATA:
				listener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLGetDiagRec"), result_line, ERROR_DB_NO_DATA);
				break;
			default:
				listener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLGetDiagRec"), result_line, ERROR_GENERAL_UNKNOWN);
			}
		#endif
		}

		void CDb::HandleStmError(const AnsiString &function, const int line, const ErrorInfo &error, PlatformHandle handle, IErrorListener *listener)
		{
		#if __has_include(<sqlext.h>)
			SQLWCHAR state[SQL_SQLSTATE_SIZE + 1], desc[1024];
			SQLSMALLINT desc_len;
			SQLINTEGER code;
			SQLRETURN result{ SQLGetDiagRecW(SQL_HANDLE_STMT, *reinterpret_cast<SQLHANDLE*>(&handle), 1, state, &code, desc, 1024, &desc_len) };
			int result_line{ __LINE__ - 1 };
			switch (result)
			{
			case SQL_SUCCESS:
			case SQL_SUCCESS_WITH_INFO:
			#ifdef _WIN32
				listener->NotifyOnError(function, line, error, StringKeyValueArray{ StringKeyValue{ L"{state}", state }, StringKeyValue{ L"{code}", ToString(code) }, StringKeyValue{ L"{message}", desc } });
			#else
				listener->NotifyOnError(function, line, error, StringKeyValueArray{ StringKeyValue{ L"{state}", UTF16ToString((char16_t*)state) }, StringKeyValue{ L"{code}", ToString(code) }, StringKeyValue{ L"{message}", UTF16ToString((char16_t*)desc) } });
			#endif
				break;
			case SQL_INVALID_HANDLE:
				listener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLGetDiagRec"), result_line, ERROR_GENERAL_INVALID_HANDLE);
				break;
			case SQL_NO_DATA:
				listener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLGetDiagRec"), result_line, ERROR_DB_NO_DATA);
				break;
			default:
				listener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLGetDiagRec"), result_line, ERROR_GENERAL_UNKNOWN);
			}
		#endif
		}

		void CDb::LoadDataSources()
		{
		#if __has_include(<sqlext.h>)
			m_aDataSources.clear();
			SQLWCHAR name[SQL_MAX_DSN_LENGTH], desc[1024];
			SQLSMALLINT name_len, desc_len;
			SQLRETURN result{ SQLDataSourcesW(*reinterpret_cast<SQLHENV*>(&m_hHandle), SQL_FETCH_FIRST, name, SQL_MAX_DSN_LENGTH, &name_len, desc, 1024, &desc_len) };
			int result_line{ __LINE__ - 1 };
			switch (result)
			{
			case SQL_SUCCESS:
			case SQL_SUCCESS_WITH_INFO:
				while (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
				#ifdef _WIN32
					m_aDataSources.push_back(StringKeyValue{ name, desc });
				#else
					m_aDataSources.push_back(StringKeyValue{ UTF16ToString((char16_t*)name), UTF16ToString((char16_t*)desc) });
				#endif
					result = SQLDataSourcesW(*reinterpret_cast<SQLHENV*>(&m_hHandle), SQL_FETCH_NEXT, name, SQL_MAX_DSN_LENGTH, &name_len, desc, 1024, &desc_len);
				}
				break;
			case SQL_NO_DATA:
				break;
			case SQL_INVALID_HANDLE:
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLDataSources"), result_line, ERROR_GENERAL_INVALID_HANDLE);
				break;
			case SQL_ERROR:
				if (m_pErrorListener)
					HandleEnvError(MakeFunctionName(__FUNCTION__, "SQLDataSources"), result_line, ERROR_DB_GET_DATA_SOURCES, m_hHandle, m_pErrorListener);
				break;
			default:
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLDataSources"), result_line, ERROR_GENERAL_UNKNOWN);
				break;
			}
			m_bHasDataSources = true;
		#endif
		}

		void CDb::LoadDrivers()
		{
		#if __has_include(<sqlext.h>)
			m_aDrivers.clear();
			SQLWCHAR desc[1024], attrs[1024];
			SQLSMALLINT desc_len, attrs_len;
			SQLRETURN result{ SQLDriversW(*reinterpret_cast<SQLHENV*>(&m_hHandle), SQL_FETCH_FIRST, desc, 1024, &desc_len, attrs, 1024, &attrs_len) };
			int result_line{ __LINE__ - 1 };
			switch (result)
			{
			case SQL_SUCCESS:
			case SQL_SUCCESS_WITH_INFO:
				while (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
				#ifdef _WIN32
					for (int i = 0; i < attrs_len - 1; i++)
						if (attrs[i] == L'\0')
							attrs[i] = L';';
					m_aDrivers.push_back(StringKeyValue{ desc, attrs });
				#else
					for (int i = 0; i < attrs_len - 1; i++)
						if (attrs[i] == u'\0')
							attrs[i] = u';';
					m_aDrivers.push_back(StringKeyValue{ UTF16ToString((char16_t*)desc), UTF16ToString((char16_t*)attrs) });
				#endif
					result = SQLDriversW(*reinterpret_cast<SQLHENV*>(&m_hHandle), SQL_FETCH_NEXT, desc, 1024, &desc_len, attrs, 1024, &attrs_len);
				}
				break;
			case SQL_NO_DATA:
				break;
			case SQL_INVALID_HANDLE:
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLDrivers"), result_line, ERROR_GENERAL_INVALID_HANDLE);
				break;
			case SQL_ERROR:
				if (m_pErrorListener)
					HandleEnvError(MakeFunctionName(__FUNCTION__, "SQLDrivers"), result_line, ERROR_DB_GET_DRIVERS, m_hHandle, m_pErrorListener);
				break;
			default:
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(MakeFunctionName(__FUNCTION__, "SQLDrivers"), result_line, ERROR_GENERAL_UNKNOWN);
				break;
			}
			m_bHasDrivers = true;
		#endif
		}

	#if __has_include(<sqlext.h>)
	#ifndef _WIN32
		String CDb::UTF16ToString(const std::u16string &str)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf8_utf16;
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utf8_str;
			std::string utf8{ utf8_utf16.to_bytes(str) };
			return utf8_str.from_bytes(utf8);
		}

		std::u16string CDb::StringToUTF16(const String &str)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf8_utf16;
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utf8_str;
			std::string utf8{ utf8_str.to_bytes(str) };
			return utf8_utf16.from_bytes(utf8);
		}
	#endif
	#endif

		void CDb::CreateMigrationTable(const String& name, IDbConnection* connection, IDbQueryBuilder* qb)
		{
			
		}
	#pragma endregion
	}
}