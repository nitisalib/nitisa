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
	#pragma region CStatementReleaseListener
		CDbConnection::CStatementReleaseListener::CStatementReleaseListener(CDbConnection *connection) :
			m_pConnection{ connection }
		{

		}

		void CDbConnection::CStatementReleaseListener::NotifyOnRelease(IReleasable *sender)
		{
			IDbStatement *statement{ cast<IDbStatement*>(sender) };
			if (statement)
			{
				for (auto pos = m_pConnection->m_aStatements.begin(); pos != m_pConnection->m_aStatements.end(); pos++)
					if (*pos == statement)
					{
						m_pConnection->m_aStatements.erase(pos);
						return;
					}
				if (m_pConnection->m_pErrorListener)
					m_pConnection->m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_NOT_FOUND);
			}
			else
			{
				if (m_pConnection->m_pErrorListener)
					m_pConnection->m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_GENERAL_INVALID_SENDER, StringKeyValueArray{ StringKeyValue{ L"{type}" , L"IDbStatement" } });
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CDbConnection::CDbConnection(PlatformHandle handle, const String &connection_options, const String &connection_string, CDb *db) :
			CReleasable(),
			m_pWindow{ nullptr },
			m_cStatementReleaseListener{ this }
		{
			m_hHandle = handle;
			m_pDb = db;
			m_sConnectionOptions = connection_options;
			m_sConnectionString = connection_string;
			m_pErrorListener = nullptr;
			m_bAssignErrorListener = true;
		}

		void CDbConnection::BeforeRelease()
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				while (m_aStatements.size() > 0)
					m_aStatements[0]->Release(true);
				CReleasable::BeforeRelease();
				SQLDisconnect(*reinterpret_cast<SQLHDBC*>(&m_hHandle));
				SQLFreeHandle(SQL_HANDLE_DBC, *reinterpret_cast<SQLHANDLE*>(&m_hHandle));
				m_hHandle = nullptr;
			}
		#endif
		}
	#pragma endregion

	#pragma region IDbConnection getters
		bool CDbConnection::isConnected(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_CONNECTION_DEAD, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_CD_FALSE;
				}
				HandleError(__FUNCTION__, "SQLGetConnectAttr", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, true, L"SQL_ATTR_CONNECTION_DEAD", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbConnection::isReadOnly(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_ACCESS_MODE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_MODE_READ_ONLY;
				}
				HandleError(__FUNCTION__, "SQLGetConnectAttr", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, true, L"SQL_ATTR_ACCESS_MODE", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbConnection::isAutoCommit(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_AUTOCOMMIT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_AUTOCOMMIT_ON;
				}
				HandleError(__FUNCTION__, "SQLGetConnectAttr", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, true, L"SQL_ATTR_AUTOCOMMIT", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbConnection::isTrace(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_TRACE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_OPT_TRACE_ON;
				}
				HandleError(__FUNCTION__, "SQLGetConnectAttr", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, true, L"SQL_ATTR_TRACE", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		String CDbConnection::getTraceFilename(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLINTEGER value_len{ 0 };
				SQLRETURN result{ SQLGetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_TRACEFILE, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_TRACEFILE, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetConnectAttr", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, true, L"SQL_ATTR_TRACEFILE", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetConnectAttr", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, true, L"SQL_ATTR_TRACEFILE", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		int CDbConnection::getConnectionTimeout(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_CONNECTION_TIMEOUT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetConnectAttr", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, true, L"SQL_ATTR_CONNECTION_TIMEOUT", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getLoginTimeout(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_LOGIN_TIMEOUT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetConnectAttr", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, true, L"SQL_ATTR_LOGIN_TIMEOUT", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 1;
		}

		DbSupportedTransactionIsolationLevels CDbConnection::getTransactionIsolationLevels(bool *succeeded)
		{
			DbSupportedTransactionIsolationLevels levels{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_TXN_ISOLATION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					levels.Valid = true;
					levels.ReadUncommited = value & SQL_TXN_READ_UNCOMMITTED;
					levels.ReadCommited = value & SQL_TXN_READ_COMMITTED;
					levels.RepeatableRead = value & SQL_TXN_REPEATABLE_READ;
					levels.Serializable = value & SQL_TXN_SERIALIZABLE;
					if (succeeded)
						*succeeded = true;
					return levels;
				}
				HandleError(__FUNCTION__, "SQLGetConnectAttr", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, true, L"SQL_ATTR_TXN_ISOLATION", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return levels;
		}

		IWindow *CDbConnection::getWindow()
		{
			return m_pWindow;
		}

		int CDbConnection::getStatementCount()
		{
			return (int)m_aStatements.size();
		}

		IDbStatement *CDbConnection::getStatement(const int index)
		{
			if (index >= 0 && index < (int)m_aStatements.size())
				return m_aStatements[index];
			return nullptr;
		}
	#pragma endregion

	#pragma region IDbConnection capability getters
		bool CDbConnection::isAllProceduresAccessible(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ACCESSIBLE_PROCEDURES, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbConnection::isAllTablesAccessible(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ACCESSIBLE_TABLES, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		int CDbConnection::getMaximumActiveEnvironmentCount(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ACTIVE_ENVIRONMENTS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		DbSupportedAggregateFunctions CDbConnection::getSupportedAggregateFunctions(bool *succeeded)
		{
			DbSupportedAggregateFunctions data{ false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_AGGREGATE_FUNCTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.All = value & SQL_AF_ALL;
					data.Avg = value & SQL_AF_AVG;
					data.Count = value & SQL_AF_COUNT;
					data.Distinct = value & SQL_AF_DISTINCT;
					data.Max = value & SQL_AF_MAX;
					data.Min = value & SQL_AF_MIN;
					data.Sum = value & SQL_AF_SUM;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedAlterDomainClauses CDbConnection::getSupportedAlterDomainClauses(bool *succeeded)
		{
			DbSupportedAlterDomainClauses data{ false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ALTER_DOMAIN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Add = value & SQL_AD_ADD_DOMAIN_CONSTRAINT;
					data.SetDefault = value & SQL_AD_ADD_DOMAIN_DEFAULT;
					data.NameDefinition = value & SQL_AD_CONSTRAINT_NAME_DEFINITION;
					data.Drop = value & SQL_AD_DROP_DOMAIN_CONSTRAINT;
					data.DropDefault = value & SQL_AD_DROP_DOMAIN_DEFAULT;
					data.Deferrable = value & SQL_AD_ADD_CONSTRAINT_DEFERRABLE;
					data.NonDeferrable = value & SQL_AD_ADD_CONSTRAINT_NON_DEFERRABLE;
					data.InitiallyDeferred = value & SQL_AD_ADD_CONSTRAINT_INITIALLY_DEFERRED;
					data.InitiallyImmediate = value & SQL_AD_ADD_CONSTRAINT_INITIALLY_IMMEDIATE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedAlterTableClauses CDbConnection::getSupportedAlterTableClauses(bool *succeeded)
		{
			DbSupportedAlterTableClauses data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ALTER_TABLE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.AddColumnCollation = value & SQL_AT_ADD_COLUMN_COLLATION;
					data.AddColumnDefault = value & SQL_AT_ADD_COLUMN_DEFAULT;
					data.AddColumnSingle = value & SQL_AT_ADD_COLUMN_SINGLE;
					data.AddConstraint = value & SQL_AT_ADD_CONSTRAINT;
					data.AddTable = value & SQL_AT_ADD_TABLE_CONSTRAINT;
					data.NameDefinition = value & SQL_AT_CONSTRAINT_NAME_DEFINITION;
					data.DropColumnCascade = value & SQL_AT_DROP_COLUMN_CASCADE;
					data.DropColumnDefault = value & SQL_AT_DROP_COLUMN_DEFAULT;
					data.DropColumnRestrict = value & SQL_AT_DROP_COLUMN_RESTRICT;
					data.DropTableCascade = value & SQL_AT_DROP_TABLE_CONSTRAINT_CASCADE;
					data.DropTableRestrict = value & SQL_AT_DROP_TABLE_CONSTRAINT_RESTRICT;
					data.SetDefaultColumn = value & SQL_AT_SET_COLUMN_DEFAULT;
					data.InitiallyDeferred = value & SQL_AT_CONSTRAINT_INITIALLY_DEFERRED;
					data.InitiallyImmediate = value & SQL_AT_CONSTRAINT_INITIALLY_IMMEDIATE;
					data.Deferrable = value & SQL_AT_CONSTRAINT_DEFERRABLE;
					data.NonDeferrable = value & SQL_AT_CONSTRAINT_NON_DEFERRABLE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isAsyncFunctionsSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ASYNC_DBC_FUNCTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_ASYNC_DBC_CAPABLE;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		DbAsyncMode CDbConnection::getAsyncMode(bool *succeeded)
		{
			DbAsyncMode data{ DbAsyncMode::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ASYNC_MODE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_AM_NONE:
						data = DbAsyncMode::None;
						break;
					case SQL_AM_CONNECTION:
						data = DbAsyncMode::Connection;
						break;
					case SQL_AM_STATEMENT:
						data = DbAsyncMode::Statement;
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isAsyncNotificationsSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ASYNC_NOTIFICATION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_ASYNC_NOTIFICATION_CAPABLE;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		DbBatchRowCountSupport CDbConnection::getBatchRowCountSupport(bool *succeeded)
		{
			DbBatchRowCountSupport data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_BATCH_ROW_COUNT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.RolledUp = value & SQL_BRC_ROLLED_UP;
					data.Procedures = value & SQL_BRC_PROCEDURES;
					data.Explicit = value & SQL_BRC_EXPLICIT;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbBatchSupport CDbConnection::getBatchSupport(bool *succeeded)
		{
			DbBatchSupport data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_BATCH_SUPPORT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.SelectExplicit = value & SQL_BS_SELECT_EXPLICIT;
					data.RowCountExplicit = value & SQL_BS_ROW_COUNT_EXPLICIT;
					data.SelectProcedures = value & SQL_BS_SELECT_PROC;
					data.RowCountProcedures = value & SQL_BS_ROW_COUNT_PROC;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbBookmarkPersistence CDbConnection::getBookmarkPersistence(bool *succeeded)
		{
			DbBookmarkPersistence data{ false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_BOOKMARK_PERSISTENCE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Close = value & SQL_BP_CLOSE;
					data.Delete = value & SQL_BP_DELETE;
					data.Drop = value & SQL_BP_DROP;
					data.Transaction = value & SQL_BP_TRANSACTION;
					data.Update = value & SQL_BP_UPDATE;
					data.OtherStatement = value & SQL_BP_OTHER_HSTMT;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isCatalogLocationAtStart(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CATALOG_LOCATION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_CL_START;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		bool CDbConnection::isCatalogNamesSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CATALOG_NAME, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		String CDbConnection::getCatalogNameSeparator(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CATALOG_NAME_SEPARATOR, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CATALOG_NAME_SEPARATOR, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		String CDbConnection::getCatalogVendorName(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CATALOG_TERM, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CATALOG_TERM, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		DbCatalogUsage CDbConnection::getCatalogUsage(bool *succeeded)
		{
			DbCatalogUsage data{ false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CATALOG_USAGE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Statements = value & SQL_CU_DML_STATEMENTS;
					data.Procedures = value & SQL_CU_PROCEDURE_INVOCATION;
					data.Tables = value & SQL_CU_TABLE_DEFINITION;
					data.Indices = value & SQL_CU_INDEX_DEFINITION;
					data.Privileges = value & SQL_CU_PRIVILEGE_DEFINITION;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		String CDbConnection::getCollationSequence(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_COLLATION_SEQ, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_COLLATION_SEQ, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		bool CDbConnection::isColumnAliasSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_COLUMN_ALIAS, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		DbConcatenateNullBehaviour CDbConnection::getConcatenameNullBehaviour(bool *succeeded)
		{
			DbConcatenateNullBehaviour data{ DbConcatenateNullBehaviour::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONCAT_NULL_BEHAVIOR, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_CB_NULL:
						data = DbConcatenateNullBehaviour::Null;
						break;
					case SQL_CB_NON_NULL:
						data = DbConcatenateNullBehaviour::NotNull;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getBigIntConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_BIGINT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getBinaryConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_BINARY, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getBitConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_BIT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getCharConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_CHAR, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getGuidConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_GUID, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getDateConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_DATE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getDecimalConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_DECIMAL, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getDoubleConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_DOUBLE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getFloatConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_FLOAT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getIntegerConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_INTEGER, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getIntervalYearMonthConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_INTERVAL_YEAR_MONTH, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getIntervalDayTimeConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_INTERVAL_DAY_TIME, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getLongVarBinaryConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_LONGVARBINARY, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getLongVarCharConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_LONGVARCHAR, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getNumericConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_NUMERIC, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getRealConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_REAL, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getSmallIntConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_SMALLINT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getTimeConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_TIME, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getTimestampConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_TIMESTAMP, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getTinyIntConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_TINYINT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getVarBinaryConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_VARBINARY, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbConvertTo CDbConnection::getVarCharConvertTo(bool *succeeded)
		{
			DbConvertTo data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_VARCHAR, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BigInt = value & SQL_CVT_BIGINT;
					data.Binary = value & SQL_CVT_BINARY;
					data.Bit = value & SQL_CVT_BIT;
					data.Guid = value & SQL_CVT_GUID;
					data.Char = value & SQL_CVT_CHAR;
					data.Date = value & SQL_CVT_DATE;
					data.Decimal = value & SQL_CVT_DECIMAL;
					data.Double = value & SQL_CVT_DOUBLE;
					data.Float = value & SQL_CVT_FLOAT;
					data.Integer = value & SQL_CVT_INTEGER;
					data.IntervalYearMonth = value & SQL_CVT_INTERVAL_YEAR_MONTH;
					data.IntervalDayTime = value & SQL_CVT_INTERVAL_DAY_TIME;
					data.LongVarBinary = value & SQL_CVT_LONGVARBINARY;
					data.LongVarChar = value & SQL_CVT_LONGVARCHAR;
					data.Numeric = value & SQL_CVT_NUMERIC;
					data.Real = value & SQL_CVT_REAL;
					data.SmallInt = value & SQL_CVT_SMALLINT;
					data.Time = value & SQL_CVT_TIME;
					data.DateTime = value & SQL_CVT_TIMESTAMP;
					data.TinyInt = value & SQL_CVT_TINYINT;
					data.VarBinary = value & SQL_CVT_VARBINARY;
					data.VarChar = value & SQL_CVT_VARCHAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedConvertFunctions CDbConnection::getSupportedConvertFunctions(bool *succeeded)
		{
			DbSupportedConvertFunctions data{ false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CONVERT_FUNCTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Cast = value & SQL_FN_CVT_CAST;
					data.Convert = value & SQL_FN_CVT_CONVERT;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbTableCorrelationName CDbConnection::getTableCorrelationName(bool *succeeded)
		{
			DbTableCorrelationName data{ DbTableCorrelationName::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CORRELATION_NAME, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_CN_NONE:
						data = DbTableCorrelationName::None;
						break;
					case SQL_CN_DIFFERENT:
						data = DbTableCorrelationName::Different;
						break;
					case SQL_CN_ANY:
						data = DbTableCorrelationName::Any;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedCreateAssertionClauses CDbConnection::getSupportedCreateAssertionClauses(bool *succeeded)
		{
			DbSupportedCreateAssertionClauses data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CREATE_ASSERTION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.InitiallyDeferred = value & SQL_CA_CONSTRAINT_INITIALLY_DEFERRED;
					data.InitiallyImmediate = value & SQL_CA_CONSTRAINT_INITIALLY_IMMEDIATE;
					data.Deferrable = value & SQL_CA_CONSTRAINT_DEFERRABLE;
					data.NonDeferrable = value & SQL_CA_CONSTRAINT_NON_DEFERRABLE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedCreateCharacterSetClauses CDbConnection::getSupportedCreateCharacterSetClauses(bool *succeeded)
		{
			DbSupportedCreateCharacterSetClauses data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CREATE_CHARACTER_SET, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{

					data.Valid = true;
					data.Create = value & SQL_CCS_CREATE_CHARACTER_SET;
					data.Collate = value & SQL_CCS_COLLATE_CLAUSE;
					data.LimitedCollation = value & SQL_CCS_LIMITED_COLLATION;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isCreateCollationSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CREATE_COLLATION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value & SQL_CCOL_CREATE_COLLATION;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		DbSupportedCreateDomainClauses CDbConnection::getSupportedCreateDomainClauses(bool *succeeded)
		{
			DbSupportedCreateDomainClauses data{ false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CREATE_DOMAIN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Create = value & SQL_CDO_CREATE_DOMAIN;
					data.ConstraintNameDefinition = value & SQL_CDO_CONSTRAINT_NAME_DEFINITION;
					data.Default = value & SQL_CDO_DEFAULT;
					data.Constraint = value & SQL_CDO_CONSTRAINT;
					data.Collation = value & SQL_CDO_COLLATION;
					data.InitiallyDeferred = value & SQL_CDO_CONSTRAINT_INITIALLY_DEFERRED;
					data.InitiallyImmediate = value & SQL_CDO_CONSTRAINT_INITIALLY_IMMEDIATE;
					data.Deferrable = value & SQL_CDO_CONSTRAINT_DEFERRABLE;
					data.NonDeferrable = value & SQL_CDO_CONSTRAINT_NON_DEFERRABLE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedCreateSchemaClauses CDbConnection::getSupportedCreateSchemaClauses(bool *succeeded)
		{
			DbSupportedCreateSchemaClauses data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CREATE_SCHEMA, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Create = value & SQL_CS_CREATE_SCHEMA;
					data.Authorization = value & SQL_CS_AUTHORIZATION;
					data.DefaultCharacterSet = value & SQL_CS_DEFAULT_CHARACTER_SET;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedCreateTableClauses CDbConnection::getSupportedCreateTableClauses(bool *succeeded)
		{
			DbSupportedCreateTableClauses data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CREATE_TABLE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Create = value & SQL_CT_CREATE_TABLE;
					data.TableConstraint = value & SQL_CT_TABLE_CONSTRAINT;
					data.ConstraintNameDefinition = value & SQL_CT_CONSTRAINT_NAME_DEFINITION;
					data.TemporaryTableCommitPreserve = value & SQL_CT_COMMIT_PRESERVE;
					data.TemporaryTableCommitDelete = value & SQL_CT_COMMIT_DELETE;
					data.TemporaryTableGlobal = value & SQL_CT_GLOBAL_TEMPORARY;
					data.TemporaryTableLocal = value & SQL_CT_LOCAL_TEMPORARY;
					data.ColumnConstraint = value & SQL_CT_COLUMN_CONSTRAINT;
					data.ColumnDefault = value & SQL_CT_COLUMN_DEFAULT;
					data.ColumnCollation = value & SQL_CT_COLUMN_COLLATION;
					data.InitiallyDeferred = value & SQL_CT_CONSTRAINT_INITIALLY_DEFERRED;
					data.InitiallyImmediate = value & SQL_CT_CONSTRAINT_INITIALLY_IMMEDIATE;
					data.Deferrable = value & SQL_CT_CONSTRAINT_DEFERRABLE;
					data.NonDeferrable = value & SQL_CT_CONSTRAINT_NON_DEFERRABLE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isCreateTranslationSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CREATE_TRANSLATION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value & SQL_CTR_CREATE_TRANSLATION;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		DbSupportedCreateViewClauses CDbConnection::getSupportedCreateViewClauses(bool *succeeded)
		{
			DbSupportedCreateViewClauses data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CREATE_VIEW, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Create = value & SQL_CV_CREATE_VIEW;
					data.CheckOption = value & SQL_CV_CHECK_OPTION;
					data.Cascade = value & SQL_CV_CASCADED;
					data.Local = value & SQL_CV_LOCAL;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbCursorBehaviour CDbConnection::getCursorCommitBehaviour(bool *succeeded)
		{
			DbCursorBehaviour data{ DbCursorBehaviour::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CURSOR_COMMIT_BEHAVIOR, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_CB_CLOSE:
						data = DbCursorBehaviour::Close;
						break;
					case SQL_CB_DELETE:
						data = DbCursorBehaviour::Delete;
						break;
					case SQL_CB_PRESERVE:
						data = DbCursorBehaviour::Preserve;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbCursorBehaviour CDbConnection::getCursorRollbackBehaviour(bool *succeeded)
		{
			DbCursorBehaviour data{ DbCursorBehaviour::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CURSOR_ROLLBACK_BEHAVIOR, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_CB_CLOSE:
						data = DbCursorBehaviour::Close;
						break;
					case SQL_CB_DELETE:
						data = DbCursorBehaviour::Delete;
						break;
					case SQL_CB_PRESERVE:
						data = DbCursorBehaviour::Preserve;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbCursorSensitivity CDbConnection::getCursorSensitivity(bool *succeeded)
		{
			DbCursorSensitivity data{ DbCursorSensitivity::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_CURSOR_SENSITIVITY, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_UNSPECIFIED:
						data = DbCursorSensitivity::Unspecified;
						break;
					case SQL_INSENSITIVE:
						data = DbCursorSensitivity::Insensitive;
						break;
					case SQL_SENSITIVE:
						data = DbCursorSensitivity::Sensitive;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		String CDbConnection::getDataSourceName(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DATA_SOURCE_NAME, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DATA_SOURCE_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		bool CDbConnection::isDataSourceReadOnly(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DATA_SOURCE_READ_ONLY, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		String CDbConnection::getDatabaseName(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DATABASE_NAME, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DATABASE_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		DbSupportedDateTimeLiterals CDbConnection::getSupportedDateTimeLiterals(bool *succeeded)
		{
			DbSupportedDateTimeLiterals data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DATETIME_LITERALS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Date = value & SQL_DL_SQL92_DATE;
					data.Time = value & SQL_DL_SQL92_TIME;
					data.Timestamp = value & SQL_DL_SQL92_TIMESTAMP;
					data.IntervalYear = value & SQL_DL_SQL92_INTERVAL_YEAR;
					data.IntervalMonth = value & SQL_DL_SQL92_INTERVAL_MONTH;
					data.IntervalDay = value & SQL_DL_SQL92_INTERVAL_DAY;
					data.IntervalHour = value & SQL_DL_SQL92_INTERVAL_HOUR;
					data.IntervalMinute = value & SQL_DL_SQL92_INTERVAL_MINUTE;
					data.IntervalSecond = value & SQL_DL_SQL92_INTERVAL_SECOND;
					data.IntervalYearToMonth = value & SQL_DL_SQL92_INTERVAL_YEAR_TO_MONTH;
					data.IntervalDayToHour = value & SQL_DL_SQL92_INTERVAL_DAY_TO_HOUR;
					data.IntervalDayToMinute = value & SQL_DL_SQL92_INTERVAL_DAY_TO_MINUTE;
					data.IntervalDayToSecond = value & SQL_DL_SQL92_INTERVAL_DAY_TO_SECOND;
					data.IntervalHourToMinute = value & SQL_DL_SQL92_INTERVAL_HOUR_TO_MINUTE;
					data.IntervalHourToSecond = value & SQL_DL_SQL92_INTERVAL_HOUR_TO_SECOND;
					data.IntervalMinuteToSecond = value & SQL_DL_SQL92_INTERVAL_MINUTE_TO_SECOND;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		String CDbConnection::getDBMSName(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DBMS_NAME, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DBMS_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		String CDbConnection::getDBMSVersion(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DBMS_VER, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DBMS_VER, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		DbSupportedIndexClauses CDbConnection::getSupportedIndexClauses(bool *succeeded)
		{
			DbSupportedIndexClauses data{ false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DDL_INDEX, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Create = value & SQL_DI_CREATE_INDEX;
					data.Drop = value & SQL_DI_DROP_INDEX;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedTransactionIsolationLevels CDbConnection::getDefaultTransactionIsolationLevels(bool *succeeded)
		{
			DbSupportedTransactionIsolationLevels data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DEFAULT_TXN_ISOLATION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.ReadUncommited = value & SQL_TXN_READ_UNCOMMITTED;
					data.ReadCommited = value & SQL_TXN_READ_COMMITTED;
					data.RepeatableRead = value & SQL_TXN_REPEATABLE_READ;
					data.Serializable = value & SQL_TXN_SERIALIZABLE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isDescribeParameterSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DESCRIBE_PARAMETER, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		String CDbConnection::getDriverManagerVersion(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DM_VER, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DM_VER, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		bool CDbConnection::isDriverAwarePoolingSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DRIVER_AWARE_POOLING_SUPPORTED, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_DRIVER_AWARE_POOLING_CAPABLE;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		String CDbConnection::getDriverName(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DRIVER_NAME, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DRIVER_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		String CDbConnection::getDriverOdbcVersion(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DRIVER_ODBC_VER, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DRIVER_ODBC_VER, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		String CDbConnection::getDriverVersion(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DRIVER_VER, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DRIVER_VER, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		bool CDbConnection::isDropAssertionSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DROP_ASSERTION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value & SQL_DA_DROP_ASSERTION;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		bool CDbConnection::isDropCharacterSetSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DROP_CHARACTER_SET, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value & SQL_DCS_DROP_CHARACTER_SET;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		bool CDbConnection::isDropCollationSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DROP_COLLATION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value & SQL_DC_DROP_COLLATION;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		DbSupportedDropClauses CDbConnection::getSupportedDropDomainClauses(bool *succeeded)
		{
			DbSupportedDropClauses data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DROP_DOMAIN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Drop = value & SQL_DD_DROP_DOMAIN;
					data.Cascade = value & SQL_DD_CASCADE;
					data.Restrict = value & SQL_DD_RESTRICT;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedDropClauses CDbConnection::getSupportedDropSchemaClauses(bool *succeeded)
		{
			DbSupportedDropClauses data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DROP_SCHEMA, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Drop = value & SQL_DD_DROP_DOMAIN;
					data.Cascade = value & SQL_DD_CASCADE;
					data.Restrict = value & SQL_DD_RESTRICT;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedDropClauses CDbConnection::getSupportedDropTableClauses(bool *succeeded)
		{
			DbSupportedDropClauses data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DROP_TABLE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Drop = value & SQL_DD_DROP_DOMAIN;
					data.Cascade = value & SQL_DD_CASCADE;
					data.Restrict = value & SQL_DD_RESTRICT;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isDropTranslationSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DROP_TRANSLATION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value & SQL_DTR_DROP_TRANSLATION;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		DbSupportedDropClauses CDbConnection::getSupportedDropViewClauses(bool *succeeded)
		{
			DbSupportedDropClauses data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DROP_VIEW, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Drop = value & SQL_DD_DROP_DOMAIN;
					data.Cascade = value & SQL_DD_CASCADE;
					data.Restrict = value & SQL_DD_RESTRICT;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbCursorAttributes CDbConnection::getDynamicCursorAttributes(bool *succeeded)
		{
			DbCursorAttributes data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DYNAMIC_CURSOR_ATTRIBUTES1, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Next = value & SQL_CA1_NEXT;
					data.Absolute = value & SQL_CA1_ABSOLUTE;
					data.Relative = value & SQL_CA1_RELATIVE;
					data.Bookmark = value & SQL_CA1_BOOKMARK;
					data.LockExclusive = value & SQL_CA1_LOCK_EXCLUSIVE;
					data.LockNoChange = value & SQL_CA1_LOCK_NO_CHANGE;
					data.LockUnlock = value & SQL_CA1_LOCK_UNLOCK;
					data.PosPosition = value & SQL_CA1_POS_POSITION;
					data.PosUpdate = value & SQL_CA1_POS_UPDATE;
					data.PosDelete = value & SQL_CA1_POS_DELETE;
					data.PosRefresh = value & SQL_CA1_POS_REFRESH;
					data.PositionedUpdate = value & SQL_CA1_POSITIONED_UPDATE;
					data.PositionedDelete = value & SQL_CA1_POSITIONED_DELETE;
					data.SelectForUpdate = value & SQL_CA1_SELECT_FOR_UPDATE;
					data.BulkAdd = value & SQL_CA1_BULK_ADD;
					data.BulkUpdateByBookmark = value & SQL_CA1_BULK_UPDATE_BY_BOOKMARK;
					data.BulkDeleteByBookmark = value & SQL_CA1_BULK_DELETE_BY_BOOKMARK;
					data.BulkFetchByBookmark = value & SQL_CA1_BULK_FETCH_BY_BOOKMARK;
					result = SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_DYNAMIC_CURSOR_ATTRIBUTES2, &value, 0, nullptr);
					int result_line{ __LINE__ - 1 };
					if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					{
						data.ReadOnlyConcurrency = value & SQL_CA2_READ_ONLY_CONCURRENCY;
						data.LockConcurrency = value & SQL_CA2_LOCK_CONCURRENCY;
						data.OptimisticRowConcurrency = value & SQL_CA2_OPT_ROWVER_CONCURRENCY;
						data.OptimisticValueConcurrency = value & SQL_CA2_OPT_VALUES_CONCURRENCY;
						data.SensitivityAdditions = value & SQL_CA2_SENSITIVITY_ADDITIONS;
						data.SensitivityDeletions = value & SQL_CA2_SENSITIVITY_DELETIONS;
						data.SensitivityUpdates = value & SQL_CA2_SENSITIVITY_UPDATES;
						data.MaximumRowsSelect = value & SQL_CA2_MAX_ROWS_SELECT;
						data.MaximumRowsInsert = value & SQL_CA2_MAX_ROWS_INSERT;
						data.MaximumRowsDelete = value & SQL_CA2_MAX_ROWS_DELETE;
						data.MaximumRowsUpdate = value & SQL_CA2_MAX_ROWS_UPDATE;
						data.MaximumRowsCatalog = value & SQL_CA2_MAX_ROWS_CATALOG;
						data.MaximumRowsAffectsAll = value & SQL_CA2_MAX_ROWS_AFFECTS_ALL;
						data.ExactRowCount = value & SQL_CA2_CRC_EXACT;
						data.ApproximateRowCount = value & SQL_CA2_CRC_APPROXIMATE;
						data.SimulateNonUnique = value & SQL_CA2_SIMULATE_NON_UNIQUE;
						data.SimulateTryUnique = value & SQL_CA2_SIMULATE_TRY_UNIQUE;
						data.SimulateUnique = value & SQL_CA2_SIMULATE_UNIQUE;
						if (succeeded)
							*succeeded = true;
						return data;
					}
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isExpressionsInOrderBySupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_EXPRESSIONS_IN_ORDERBY, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		DbFileUsage CDbConnection::getFileUsage(bool *succeeded)
		{
			DbFileUsage data{ DbFileUsage::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_FILE_USAGE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_FILE_NOT_SUPPORTED:
						data = DbFileUsage::NotSupported;
						break;
					case SQL_FILE_TABLE:
						data = DbFileUsage::Table;
						break;
					case SQL_FILE_CATALOG:
						data = DbFileUsage::Catalog;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbCursorAttributes CDbConnection::getForwardOnlyCursorAttributes(bool *succeeded)
		{
			DbCursorAttributes data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Next = value & SQL_CA1_NEXT;
					data.Absolute = value & SQL_CA1_ABSOLUTE;
					data.Relative = value & SQL_CA1_RELATIVE;
					data.Bookmark = value & SQL_CA1_BOOKMARK;
					data.LockExclusive = value & SQL_CA1_LOCK_EXCLUSIVE;
					data.LockNoChange = value & SQL_CA1_LOCK_NO_CHANGE;
					data.LockUnlock = value & SQL_CA1_LOCK_UNLOCK;
					data.PosPosition = value & SQL_CA1_POS_POSITION;
					data.PosUpdate = value & SQL_CA1_POS_UPDATE;
					data.PosDelete = value & SQL_CA1_POS_DELETE;
					data.PosRefresh = value & SQL_CA1_POS_REFRESH;
					data.PositionedUpdate = value & SQL_CA1_POSITIONED_UPDATE;
					data.PositionedDelete = value & SQL_CA1_POSITIONED_DELETE;
					data.SelectForUpdate = value & SQL_CA1_SELECT_FOR_UPDATE;
					data.BulkAdd = value & SQL_CA1_BULK_ADD;
					data.BulkUpdateByBookmark = value & SQL_CA1_BULK_UPDATE_BY_BOOKMARK;
					data.BulkDeleteByBookmark = value & SQL_CA1_BULK_DELETE_BY_BOOKMARK;
					data.BulkFetchByBookmark = value & SQL_CA1_BULK_FETCH_BY_BOOKMARK;
					result = SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2, &value, 0, nullptr);
					int result_line{ __LINE__ - 1 };
					if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					{
						data.ReadOnlyConcurrency = value & SQL_CA2_READ_ONLY_CONCURRENCY;
						data.LockConcurrency = value & SQL_CA2_LOCK_CONCURRENCY;
						data.OptimisticRowConcurrency = value & SQL_CA2_OPT_ROWVER_CONCURRENCY;
						data.OptimisticValueConcurrency = value & SQL_CA2_OPT_VALUES_CONCURRENCY;
						data.SensitivityAdditions = value & SQL_CA2_SENSITIVITY_ADDITIONS;
						data.SensitivityDeletions = value & SQL_CA2_SENSITIVITY_DELETIONS;
						data.SensitivityUpdates = value & SQL_CA2_SENSITIVITY_UPDATES;
						data.MaximumRowsSelect = value & SQL_CA2_MAX_ROWS_SELECT;
						data.MaximumRowsInsert = value & SQL_CA2_MAX_ROWS_INSERT;
						data.MaximumRowsDelete = value & SQL_CA2_MAX_ROWS_DELETE;
						data.MaximumRowsUpdate = value & SQL_CA2_MAX_ROWS_UPDATE;
						data.MaximumRowsCatalog = value & SQL_CA2_MAX_ROWS_CATALOG;
						data.MaximumRowsAffectsAll = value & SQL_CA2_MAX_ROWS_AFFECTS_ALL;
						data.ExactRowCount = value & SQL_CA2_CRC_EXACT;
						data.ApproximateRowCount = value & SQL_CA2_CRC_APPROXIMATE;
						data.SimulateNonUnique = value & SQL_CA2_SIMULATE_NON_UNIQUE;
						data.SimulateTryUnique = value & SQL_CA2_SIMULATE_TRY_UNIQUE;
						data.SimulateUnique = value & SQL_CA2_SIMULATE_UNIQUE;
						if (succeeded)
							*succeeded = true;
						return data;
					}
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedGetDataExtensions CDbConnection::getSupportedGetDataExtensions(bool *succeeded)
		{
			DbSupportedGetDataExtensions data{ false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_GETDATA_EXTENSIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.AnyColumn = value & SQL_GD_ANY_COLUMN;
					data.AnyOrder = value & SQL_GD_ANY_ORDER;
					data.Block = value & SQL_GD_BLOCK;
					data.Bound = value & SQL_GD_BOUND;
					data.OutputParams = value & SQL_GD_OUTPUT_PARAMS;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbGroupByRelation CDbConnection::getGroupByRelation(bool *succeeded)
		{
			DbGroupByRelation data{ DbGroupByRelation::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_GROUP_BY, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_GB_NOT_SUPPORTED:
						data = DbGroupByRelation::NotSupported;
						break;
					case SQL_GB_COLLATE:
						data = DbGroupByRelation::Collate;
						break;
					case SQL_GB_GROUP_BY_EQUALS_SELECT:
						data = DbGroupByRelation::EqualsSelect;
						break;
					case SQL_GB_GROUP_BY_CONTAINS_SELECT:
						data = DbGroupByRelation::ContainsSelect;
						break;
					case SQL_GB_NO_RELATION:
						data = DbGroupByRelation::NoRelation;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbCaseSensitivity CDbConnection::getIdentifierCaseSensitivity(bool *succeeded)
		{
			DbCaseSensitivity data{ DbCaseSensitivity::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_IDENTIFIER_CASE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_IC_MIXED:
						data = DbCaseSensitivity::Mixed;
						break;
					case SQL_IC_UPPER:
						data = DbCaseSensitivity::Upper;
						break;
					case SQL_IC_LOWER:
						data = DbCaseSensitivity::Lower;
						break;
					case SQL_IC_SENSITIVE:
						data = DbCaseSensitivity::Sensitive;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		String CDbConnection::getQuotedIdentifierDelimiter(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_IDENTIFIER_QUOTE_CHAR, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_IDENTIFIER_QUOTE_CHAR, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		DbSupportedCreateIndexKeywords CDbConnection::getSupportedCreateIndexKeywords(bool *succeeded)
		{
			DbSupportedCreateIndexKeywords data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_INDEX_KEYWORDS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.None = value & SQL_IK_NONE;
					data.Asc = value & SQL_IK_ASC;
					data.Desc = value & SQL_IK_DESC;
					data.All = value & SQL_IK_ALL;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedInformationSchemaViews CDbConnection::getSupportedInformationSchemaViews(bool *succeeded)
		{
			DbSupportedInformationSchemaViews data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_INFO_SCHEMA_VIEWS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Assertions = value & SQL_ISV_ASSERTIONS;
					data.CharacterSets = value & SQL_ISV_CHARACTER_SETS;
					data.CheckConstraints = value & SQL_ISV_CHECK_CONSTRAINTS;
					data.Collations = value & SQL_ISV_COLLATIONS;
					data.ColumnDomainUsage = value & SQL_ISV_COLUMN_DOMAIN_USAGE;
					data.ColumnPrivileges = value & SQL_ISV_COLUMN_PRIVILEGES;
					data.Columns = value & SQL_ISV_COLUMNS;
					data.ConstraintColumnUsage = value & SQL_ISV_CONSTRAINT_COLUMN_USAGE;
					data.ConstraintTableUsage = value & SQL_ISV_CONSTRAINT_TABLE_USAGE;
					data.DomainConstraints = value & SQL_ISV_DOMAIN_CONSTRAINTS;
					data.Domains = value & SQL_ISV_DOMAINS;
					data.KeyColumnUsage = value & SQL_ISV_KEY_COLUMN_USAGE;
					data.ReferentialConstraints = value & SQL_ISV_REFERENTIAL_CONSTRAINTS;
					data.Schemata = value & SQL_ISV_SCHEMATA;
					data.SQLLanguages = value & SQL_ISV_SQL_LANGUAGES;
					data.TableConstraints = value & SQL_ISV_TABLE_CONSTRAINTS;
					data.TablePrivileges = value & SQL_ISV_TABLE_PRIVILEGES;
					data.Tables = value & SQL_ISV_TABLES;
					data.Translations = value & SQL_ISV_TRANSLATIONS;
					data.UsagePrivileges = value & SQL_ISV_USAGE_PRIVILEGES;
					data.ViewColumnUsage = value & SQL_ISV_VIEW_COLUMN_USAGE;
					data.ViewTableUsage = value & SQL_ISV_VIEW_TABLE_USAGE;
					data.Views = value & SQL_ISV_VIEWS;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedInsertStatements CDbConnection::getSupportedInsertStatements(bool *succeeded)
		{
			DbSupportedInsertStatements data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_INSERT_STATEMENT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.InsertLiterals = value & SQL_IS_INSERT_LITERALS;
					data.InsertSearched = value & SQL_IS_INSERT_SEARCHED;
					data.SelectInto = value & SQL_IS_SELECT_INTO;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isIntegritySupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_INTEGRITY, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		DbCursorAttributes CDbConnection::getKeysetCursorAttributes(bool *succeeded)
		{
			DbCursorAttributes data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_KEYSET_CURSOR_ATTRIBUTES1, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Next = value & SQL_CA1_NEXT;
					data.Absolute = value & SQL_CA1_ABSOLUTE;
					data.Relative = value & SQL_CA1_RELATIVE;
					data.Bookmark = value & SQL_CA1_BOOKMARK;
					data.LockExclusive = value & SQL_CA1_LOCK_EXCLUSIVE;
					data.LockNoChange = value & SQL_CA1_LOCK_NO_CHANGE;
					data.LockUnlock = value & SQL_CA1_LOCK_UNLOCK;
					data.PosPosition = value & SQL_CA1_POS_POSITION;
					data.PosUpdate = value & SQL_CA1_POS_UPDATE;
					data.PosDelete = value & SQL_CA1_POS_DELETE;
					data.PosRefresh = value & SQL_CA1_POS_REFRESH;
					data.PositionedUpdate = value & SQL_CA1_POSITIONED_UPDATE;
					data.PositionedDelete = value & SQL_CA1_POSITIONED_DELETE;
					data.SelectForUpdate = value & SQL_CA1_SELECT_FOR_UPDATE;
					data.BulkAdd = value & SQL_CA1_BULK_ADD;
					data.BulkUpdateByBookmark = value & SQL_CA1_BULK_UPDATE_BY_BOOKMARK;
					data.BulkDeleteByBookmark = value & SQL_CA1_BULK_DELETE_BY_BOOKMARK;
					data.BulkFetchByBookmark = value & SQL_CA1_BULK_FETCH_BY_BOOKMARK;
					result = SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_KEYSET_CURSOR_ATTRIBUTES2, &value, 0, nullptr);
					int result_line{ __LINE__ - 1 };
					if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					{
						data.ReadOnlyConcurrency = value & SQL_CA2_READ_ONLY_CONCURRENCY;
						data.LockConcurrency = value & SQL_CA2_LOCK_CONCURRENCY;
						data.OptimisticRowConcurrency = value & SQL_CA2_OPT_ROWVER_CONCURRENCY;
						data.OptimisticValueConcurrency = value & SQL_CA2_OPT_VALUES_CONCURRENCY;
						data.SensitivityAdditions = value & SQL_CA2_SENSITIVITY_ADDITIONS;
						data.SensitivityDeletions = value & SQL_CA2_SENSITIVITY_DELETIONS;
						data.SensitivityUpdates = value & SQL_CA2_SENSITIVITY_UPDATES;
						data.MaximumRowsSelect = value & SQL_CA2_MAX_ROWS_SELECT;
						data.MaximumRowsInsert = value & SQL_CA2_MAX_ROWS_INSERT;
						data.MaximumRowsDelete = value & SQL_CA2_MAX_ROWS_DELETE;
						data.MaximumRowsUpdate = value & SQL_CA2_MAX_ROWS_UPDATE;
						data.MaximumRowsCatalog = value & SQL_CA2_MAX_ROWS_CATALOG;
						data.MaximumRowsAffectsAll = value & SQL_CA2_MAX_ROWS_AFFECTS_ALL;
						data.ExactRowCount = value & SQL_CA2_CRC_EXACT;
						data.ApproximateRowCount = value & SQL_CA2_CRC_APPROXIMATE;
						data.SimulateNonUnique = value & SQL_CA2_SIMULATE_NON_UNIQUE;
						data.SimulateTryUnique = value & SQL_CA2_SIMULATE_TRY_UNIQUE;
						data.SimulateUnique = value & SQL_CA2_SIMULATE_UNIQUE;
						if (succeeded)
							*succeeded = true;
						return data;
					}
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		String CDbConnection::getSupportedKeywords(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_KEYWORDS, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_KEYWORDS, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		bool CDbConnection::isLikeEscapeSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_LIKE_ESCAPE_CLAUSE, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		int CDbConnection::getMaximumAsyncronousConcurrentStatementCount(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_ASYNC_CONCURRENT_STATEMENTS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumBinaryLiteralLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_BINARY_LITERAL_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumCatalogNameLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_CATALOG_NAME_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumCharacterLiteralLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_CHAR_LITERAL_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumColumnNameLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_COLUMN_NAME_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumColumnsInGroupBy(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_COLUMNS_IN_GROUP_BY, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumColumnsInIndex(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_COLUMNS_IN_INDEX, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumColumnsInOrderBy(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_COLUMNS_IN_ORDER_BY, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumColumnsInSelect(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_COLUMNS_IN_SELECT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumColumnsInTable(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_COLUMNS_IN_TABLE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumConcurrentActivityCount(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_CONCURRENT_ACTIVITIES, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumCursorNameLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_CURSOR_NAME_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumDriverConnectionCount(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_DRIVER_CONNECTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumIdentifierLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_IDENTIFIER_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumIndexSize(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_INDEX_SIZE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumProcedureNameLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_PROCEDURE_NAME_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumRowSize(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_ROW_SIZE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		bool CDbConnection::isMaximumRowSizeIncludesLong(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_ROW_SIZE_INCLUDES_LONG, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		int CDbConnection::getMaximumSchemaNameLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_SCHEMA_NAME_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumStatementLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_STATEMENT_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumTableNameLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_TABLE_NAME_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumTablesInSelect(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_TABLES_IN_SELECT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		int CDbConnection::getMaximumUserNameLength(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MAX_USER_NAME_LEN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		bool CDbConnection::isMultipleResultSetsSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MULT_RESULT_SETS, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbConnection::isMultipleActiveTransactionsSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_MULTIPLE_ACTIVE_TXN, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbConnection::isDataSourceNeedLengthOfLongDataValue(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_NEED_LONG_DATA_LEN, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbConnection::isNonNullableColumnsSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_NON_NULLABLE_COLUMNS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_NNC_NON_NULL;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		DbNullCollation CDbConnection::getNullCollation(bool *succeeded)
		{
			DbNullCollation data{ DbNullCollation::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_NULL_COLLATION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_NC_END:
						data = DbNullCollation::End;
						break;
					case SQL_NC_HIGH:
						data = DbNullCollation::High;
						break;
					case SQL_NC_LOW:
						data = DbNullCollation::Low;
						break;
					case SQL_NC_START:
						data = DbNullCollation::Start;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedNumericFunctions CDbConnection::getSupportedNumericFunctions(bool *succeeded)
		{
			DbSupportedNumericFunctions data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_NUMERIC_FUNCTIONS	, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Abs = value & SQL_FN_NUM_ABS;
					data.Acos = value & SQL_FN_NUM_ACOS;
					data.Asin = value & SQL_FN_NUM_ASIN;
					data.Atan = value & SQL_FN_NUM_ATAN;
					data.Atan2 = value & SQL_FN_NUM_ATAN2;
					data.Ceiling = value & SQL_FN_NUM_CEILING;
					data.Cos = value & SQL_FN_NUM_COS;
					data.Cot = value & SQL_FN_NUM_COT;
					data.Degrees = value & SQL_FN_NUM_DEGREES;
					data.Exp = value & SQL_FN_NUM_EXP;
					data.Floor = value & SQL_FN_NUM_FLOOR;
					data.Log = value & SQL_FN_NUM_LOG;
					data.Log10 = value & SQL_FN_NUM_LOG10;
					data.Mod = value & SQL_FN_NUM_MOD;
					data.Pi = value & SQL_FN_NUM_PI;
					data.Power = value & SQL_FN_NUM_POWER;
					data.Radians = value & SQL_FN_NUM_RADIANS;
					data.Rand = value & SQL_FN_NUM_RAND;
					data.Round = value & SQL_FN_NUM_ROUND;
					data.Sign = value & SQL_FN_NUM_SIGN;
					data.Sin = value & SQL_FN_NUM_SIN;
					data.Sqrt = value & SQL_FN_NUM_SQRT;
					data.Tan = value & SQL_FN_NUM_TAN;
					data.Truncate = value & SQL_FN_NUM_TRUNCATE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbOdbcInterfaceConformance CDbConnection::getOdbcInterfaceConformance(bool *succeeded)
		{
			DbOdbcInterfaceConformance data{ DbOdbcInterfaceConformance::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_BATCH_ROW_COUNT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_OIC_CORE:
						data = DbOdbcInterfaceConformance::Core;
						break;
					case SQL_OIC_LEVEL1:
						data = DbOdbcInterfaceConformance::Level1;
						break;
					case SQL_OIC_LEVEL2:
						data = DbOdbcInterfaceConformance::Level2;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		String CDbConnection::getOdbcVersion(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ODBC_VER, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ODBC_VER, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		DbSupportedOuterJoins CDbConnection::getSupportedOuterJoins(bool *succeeded)
		{
			DbSupportedOuterJoins data{ false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_OJ_CAPABILITIES, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Left = value & SQL_OJ_LEFT;
					data.Right = value & SQL_OJ_RIGHT;
					data.Full = value & SQL_OJ_FULL;
					data.Nested = value & SQL_OJ_NESTED;
					data.NotOrdered = value & SQL_OJ_NOT_ORDERED;
					data.Inner = value & SQL_OJ_INNER;
					data.AllComparisonOperators = value & SQL_OJ_ALL_COMPARISON_OPS;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isOrderByColumnsMustBeInSelect(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ORDER_BY_COLUMNS_IN_SELECT, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbConnection::isIndividualRowCountsAvailableInParametrizedExecution(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_PARAM_ARRAY_ROW_COUNTS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_PARC_BATCH;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return 0;
		}

		DbSupportedAvailabilityOfResultSetsInParameterizedExecution CDbConnection::getSupportedAvailabilityOfResultSetsInParameterizedExecution(bool *succeeded)
		{
			DbSupportedAvailabilityOfResultSetsInParameterizedExecution data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_PARAM_ARRAY_SELECTS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Batch = value & SQL_PAS_BATCH;
					data.NoBatch = value & SQL_PAS_NO_BATCH;
					data.NoSelect = value & SQL_PAS_NO_SELECT;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedPositionOperations CDbConnection::getSupportedPositionOperations(bool *succeeded)
		{
			DbSupportedPositionOperations data{ false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_POS_OPERATIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Position = value & SQL_POS_POSITION;
					data.Refresh = value & SQL_POS_REFRESH;
					data.Update = value & SQL_POS_UPDATE;
					data.Delete = value & SQL_POS_DELETE;
					data.Add = value & SQL_POS_ADD;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		String CDbConnection::getProcedureVendorName(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_PROCEDURE_TERM, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_PROCEDURE_TERM, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		bool CDbConnection::isProceduresSupported(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_PROCEDURES, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		DbCaseSensitivity CDbConnection::getQuotedIdentifierCaseSensitivity(bool *succeeded)
		{
			DbCaseSensitivity data{ DbCaseSensitivity::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_QUOTED_IDENTIFIER_CASE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_IC_MIXED:
						data = DbCaseSensitivity::Mixed;
						break;
					case SQL_IC_UPPER:
						data = DbCaseSensitivity::Upper;
						break;
					case SQL_IC_LOWER:
						data = DbCaseSensitivity::Lower;
						break;
					case SQL_IC_SENSITIVE:
						data = DbCaseSensitivity::Sensitive;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbConnection::isRowUpdatesMaintainRowVersions(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t[2];
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ROW_UPDATES, t, 2 * sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
				#ifdef _WIN32
					return t[0] == L'Y';
				#else
					return t[0] == u'Y';
				#endif
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		String CDbConnection::getSchemaVendorName(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SCHEMA_TERM, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SCHEMA_TERM, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		DbSupportedSchemaUsages CDbConnection::getSupportedSchemaUsages(bool *succeeded)
		{
			DbSupportedSchemaUsages data{ false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SCHEMA_USAGE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.AllDataManipulations = value & SQL_SU_DML_STATEMENTS;
					data.ProcedureInvocation = value & SQL_SU_PROCEDURE_INVOCATION;
					data.TableDefinition = value & SQL_SU_TABLE_DEFINITION;
					data.IndexDefinition = value & SQL_SU_INDEX_DEFINITION;
					data.PrivilegeDefinition = value & SQL_SU_PRIVILEGE_DEFINITION;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedScrollOptions CDbConnection::getSupportedScrollOptions(bool *succeeded)
		{
			DbSupportedScrollOptions data{ false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SCROLL_OPTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.ForwardOnly = value & SQL_SO_FORWARD_ONLY;
					data.Static = value & SQL_SO_STATIC;
					data.KeysetDriven = value & SQL_SO_KEYSET_DRIVEN;
					data.Dynamic = value & SQL_SO_DYNAMIC;
					data.Mixed = value & SQL_SO_MIXED;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		String CDbConnection::getSearchPatternEscape(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SEARCH_PATTERN_ESCAPE, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SEARCH_PATTERN_ESCAPE, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		String CDbConnection::getServerName(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SERVER_NAME, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SERVER_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		String CDbConnection::getSpecialCharacters(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SPECIAL_CHARACTERS, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SPECIAL_CHARACTERS, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		DbSqlConformance CDbConnection::getSqlConformance(bool *succeeded)
		{
			DbSqlConformance data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL_CONFORMANCE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Entry = value & SQL_SC_SQL92_ENTRY;
					data.Transitional = value & SQL_SC_FIPS127_2_TRANSITIONAL;
					data.Full = value & SQL_SC_SQL92_FULL;
					data.Intermediate = value & SQL_SC_SQL92_INTERMEDIATE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedDateTimeFunctions CDbConnection::getSupportedDateTimeFunctions(bool *succeeded)
		{
			DbSupportedDateTimeFunctions data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_DATETIME_FUNCTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.CurrentDate = value & SQL_SDF_CURRENT_DATE;
					data.CurrentTime = value & SQL_SDF_CURRENT_TIME;
					data.CurrentTimestamp = value & SQL_SDF_CURRENT_TIMESTAMP;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedForeignKeyRules CDbConnection::getSupportedForeignKeyDeleteRules(bool *succeeded)
		{
			DbSupportedForeignKeyRules data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_FOREIGN_KEY_DELETE_RULE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Cascade = value & SQL_SFKD_CASCADE;
					data.NoAction = value & SQL_SFKD_NO_ACTION;
					data.SetDefault = value & SQL_SFKD_SET_DEFAULT;
					data.SetNull = value & SQL_SFKD_SET_NULL;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedForeignKeyRules CDbConnection::getSupportedForeignKeyUpdateRules(bool *succeeded)
		{
			DbSupportedForeignKeyRules data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_FOREIGN_KEY_UPDATE_RULE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Cascade = value & SQL_SFKU_CASCADE;
					data.NoAction = value & SQL_SFKU_NO_ACTION;
					data.SetDefault = value & SQL_SFKU_SET_DEFAULT;
					data.SetNull = value & SQL_SFKU_SET_NULL;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedGrantClauses CDbConnection::getSupportedGrantClauses(bool *succeeded)
		{
			DbSupportedGrantClauses data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_GRANT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.DeleteTable = value & SQL_SG_DELETE_TABLE;
					data.InsertColumn = value & SQL_SG_INSERT_COLUMN;
					data.InsertTable = value & SQL_SG_INSERT_TABLE;
					data.ReferenceTable = value & SQL_SG_REFERENCES_TABLE;
					data.ReferenceColumn = value & SQL_SG_REFERENCES_COLUMN;
					data.SelectTable = value & SQL_SG_SELECT_TABLE;
					data.UpdateColumn = value & SQL_SG_UPDATE_COLUMN;
					data.UpdateTable = value & SQL_SG_UPDATE_TABLE;
					data.UsageOnDomain = value & SQL_SG_USAGE_ON_DOMAIN;
					data.UsageOnCharacterSet = value & SQL_SG_USAGE_ON_CHARACTER_SET;
					data.UsageOnCollation = value & SQL_SG_USAGE_ON_COLLATION;
					data.UsageOnTranslation = value & SQL_SG_USAGE_ON_TRANSLATION;
					data.WithGrantOption = value & SQL_SG_WITH_GRANT_OPTION;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedNumericValueFunctions CDbConnection::getSupportedNumericValueFunctions(bool *succeeded)
		{
			DbSupportedNumericValueFunctions data{ false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_NUMERIC_VALUE_FUNCTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.BitLength = value & SQL_SNVF_BIT_LENGTH;
					data.CharLength = value & SQL_SNVF_CHAR_LENGTH;
					data.CharacterLength = value & SQL_SNVF_CHARACTER_LENGTH;
					data.Extract = value & SQL_SNVF_EXTRACT;
					data.OctetLength = value & SQL_SNVF_OCTET_LENGTH;
					data.Position = value & SQL_SNVF_POSITION;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedPredicates CDbConnection::getSupportedPredicates(bool *succeeded)
		{
			DbSupportedPredicates data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_PREDICATES, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Between = value & SQL_SP_BETWEEN;
					data.Comparison = value & SQL_SP_COMPARISON;
					data.Exists = value & SQL_SP_EXISTS;
					data.In = value & SQL_SP_IN;
					data.IsNotNull = value & SQL_SP_ISNOTNULL;
					data.IsNull = value & SQL_SP_ISNULL;
					data.Like = value & SQL_SP_LIKE;
					data.MatchFull = value & SQL_SP_MATCH_FULL;
					data.MatchPartial = value & SQL_SP_MATCH_PARTIAL;
					data.MatchUniqueFull = value & SQL_SP_MATCH_UNIQUE_FULL;
					data.MatchUniquePartial = value & SQL_SP_MATCH_UNIQUE_PARTIAL;
					data.Overlaps = value & SQL_SP_OVERLAPS;
					data.QuantifierComparison = value & SQL_SP_QUANTIFIED_COMPARISON;
					data.Unique = value & SQL_SP_UNIQUE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedRelationJoinOperators CDbConnection::getSupportedRelationJoinOperators(bool *succeeded)
		{
			DbSupportedRelationJoinOperators data{ false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_RELATIONAL_JOIN_OPERATORS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.CorrespondingClause = value & SQL_SRJO_CORRESPONDING_CLAUSE;
					data.CrossJoin = value & SQL_SRJO_CROSS_JOIN;
					data.ExceptJoin = value & SQL_SRJO_EXCEPT_JOIN;
					data.FullOuterJoin = value & SQL_SRJO_FULL_OUTER_JOIN;
					data.InnerJoin = value & SQL_SRJO_INNER_JOIN;
					data.IntersectJoin = value & SQL_SRJO_INTERSECT_JOIN;
					data.LeftOuterJoin = value & SQL_SRJO_LEFT_OUTER_JOIN;
					data.NaturalJoin = value & SQL_SRJO_NATURAL_JOIN;
					data.RightOuterJoin = value & SQL_SRJO_RIGHT_OUTER_JOIN;
					data.UnionJoin = value & SQL_SRJO_UNION_JOIN;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedRevokeClauses CDbConnection::getSupportedRevokeClauses(bool *succeeded)
		{
			DbSupportedRevokeClauses data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_REVOKE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Cascade = value & SQL_SR_CASCADE;
					data.DeleteTable = value & SQL_SR_DELETE_TABLE;
					data.GrantOptionFor = value & SQL_SR_GRANT_OPTION_FOR;
					data.InsertColumn = value & SQL_SR_INSERT_COLUMN;
					data.InsertTable = value & SQL_SR_INSERT_TABLE;
					data.ReferenceColumn = value & SQL_SR_REFERENCES_COLUMN;
					data.ReferenceTable = value & SQL_SR_REFERENCES_TABLE;
					data.Restrict = value & SQL_SR_RESTRICT;
					data.SelectTable = value & SQL_SR_SELECT_TABLE;
					data.UpdateColumn = value & SQL_SR_UPDATE_COLUMN;
					data.UpdateTable = value & SQL_SR_UPDATE_TABLE;
					data.UsageOnDomain = value & SQL_SR_USAGE_ON_DOMAIN;
					data.UsageOnCharacterSet = value & SQL_SR_USAGE_ON_CHARACTER_SET;
					data.UsageOnCollation = value & SQL_SR_USAGE_ON_COLLATION;
					data.UsageOnTranslation = value & SQL_SR_USAGE_ON_TRANSLATION;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedRowValueConstructors CDbConnection::getSupportedRowValueConstructors(bool *succeeded)
		{
			DbSupportedRowValueConstructors data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_ROW_VALUE_CONSTRUCTOR, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.ValueExpression = value & SQL_SRVC_VALUE_EXPRESSION;
					data.Null = value & SQL_SRVC_NULL;
					data.Default = value & SQL_SRVC_DEFAULT;
					data.RowSubQuery = value & SQL_SRVC_ROW_SUBQUERY;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedStringFunctions CDbConnection::getSupportedStringFunctions(bool *succeeded)
		{
			DbSupportedStringFunctions data{ false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_STRING_FUNCTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Convert = value & SQL_SSF_CONVERT;
					data.Lower = value & SQL_SSF_LOWER;
					data.Upper = value & SQL_SSF_UPPER;
					data.SubString = value & SQL_SSF_SUBSTRING;
					data.Translate = value & SQL_SSF_TRANSLATE;
					data.TrimBoth = value & SQL_SSF_TRIM_BOTH;
					data.TrimLeading = value & SQL_SSF_TRIM_LEADING;
					data.TrimTrailing = value & SQL_SSF_TRIM_TRAILING;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedValueExpressions CDbConnection::getSupportedValueExpressions(bool *succeeded)
		{
			DbSupportedValueExpressions data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SQL92_VALUE_EXPRESSIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Case = value & SQL_SVE_CASE;
					data.Cast = value & SQL_SVE_CAST;
					data.Coalesce = value & SQL_SVE_COALESCE;
					data.NullIf = value & SQL_SVE_NULLIF;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbStandardCliConformance CDbConnection::getStandardCliConformance(bool *succeeded)
		{
			DbStandardCliConformance data{ false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_STANDARD_CLI_CONFORMANCE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.XOpenVersion1 = value & SQL_SCC_XOPEN_CLI_VERSION1;
					data.ISO92 = value & SQL_SCC_ISO92_CLI;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbCursorAttributes CDbConnection::getStaticCursorAttributes(bool *succeeded)
		{
			DbCursorAttributes data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_STATIC_CURSOR_ATTRIBUTES1, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Next = value & SQL_CA1_NEXT;
					data.Absolute = value & SQL_CA1_ABSOLUTE;
					data.Relative = value & SQL_CA1_RELATIVE;
					data.Bookmark = value & SQL_CA1_BOOKMARK;
					data.LockExclusive = value & SQL_CA1_LOCK_EXCLUSIVE;
					data.LockNoChange = value & SQL_CA1_LOCK_NO_CHANGE;
					data.LockUnlock = value & SQL_CA1_LOCK_UNLOCK;
					data.PosPosition = value & SQL_CA1_POS_POSITION;
					data.PosUpdate = value & SQL_CA1_POS_UPDATE;
					data.PosDelete = value & SQL_CA1_POS_DELETE;
					data.PosRefresh = value & SQL_CA1_POS_REFRESH;
					data.PositionedUpdate = value & SQL_CA1_POSITIONED_UPDATE;
					data.PositionedDelete = value & SQL_CA1_POSITIONED_DELETE;
					data.SelectForUpdate = value & SQL_CA1_SELECT_FOR_UPDATE;
					data.BulkAdd = value & SQL_CA1_BULK_ADD;
					data.BulkUpdateByBookmark = value & SQL_CA1_BULK_UPDATE_BY_BOOKMARK;
					data.BulkDeleteByBookmark = value & SQL_CA1_BULK_DELETE_BY_BOOKMARK;
					data.BulkFetchByBookmark = value & SQL_CA1_BULK_FETCH_BY_BOOKMARK;
					result = SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_STATIC_CURSOR_ATTRIBUTES2, &value, 0, nullptr);
					int result_line{ __LINE__ - 1 };
					if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					{
						data.ReadOnlyConcurrency = value & SQL_CA2_READ_ONLY_CONCURRENCY;
						data.LockConcurrency = value & SQL_CA2_LOCK_CONCURRENCY;
						data.OptimisticRowConcurrency = value & SQL_CA2_OPT_ROWVER_CONCURRENCY;
						data.OptimisticValueConcurrency = value & SQL_CA2_OPT_VALUES_CONCURRENCY;
						data.SensitivityAdditions = value & SQL_CA2_SENSITIVITY_ADDITIONS;
						data.SensitivityDeletions = value & SQL_CA2_SENSITIVITY_DELETIONS;
						data.SensitivityUpdates = value & SQL_CA2_SENSITIVITY_UPDATES;
						data.MaximumRowsSelect = value & SQL_CA2_MAX_ROWS_SELECT;
						data.MaximumRowsInsert = value & SQL_CA2_MAX_ROWS_INSERT;
						data.MaximumRowsDelete = value & SQL_CA2_MAX_ROWS_DELETE;
						data.MaximumRowsUpdate = value & SQL_CA2_MAX_ROWS_UPDATE;
						data.MaximumRowsCatalog = value & SQL_CA2_MAX_ROWS_CATALOG;
						data.MaximumRowsAffectsAll = value & SQL_CA2_MAX_ROWS_AFFECTS_ALL;
						data.ExactRowCount = value & SQL_CA2_CRC_EXACT;
						data.ApproximateRowCount = value & SQL_CA2_CRC_APPROXIMATE;
						data.SimulateNonUnique = value & SQL_CA2_SIMULATE_NON_UNIQUE;
						data.SimulateTryUnique = value & SQL_CA2_SIMULATE_TRY_UNIQUE;
						data.SimulateUnique = value & SQL_CA2_SIMULATE_UNIQUE;
						if (succeeded)
							*succeeded = true;
						return data;
					}
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedScalarStringFunctions CDbConnection::getSupportedScalarStringFunctions(bool *succeeded)
		{
			DbSupportedScalarStringFunctions data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_STRING_FUNCTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.ASCII = value & SQL_FN_STR_ASCII;
					data.BitLength = value & SQL_FN_STR_BIT_LENGTH;
					data.Char = value & SQL_FN_STR_CHAR;
					data.CharLength = value & SQL_FN_STR_CHAR_LENGTH;
					data.CharacterLength = value & SQL_FN_STR_CHARACTER_LENGTH;
					data.Concat = value & SQL_FN_STR_CONCAT;
					data.Difference = value & SQL_FN_STR_DIFFERENCE;
					data.Insert = value & SQL_FN_STR_INSERT;
					data.LCase = value & SQL_FN_STR_LCASE;
					data.Left = value & SQL_FN_STR_LEFT;
					data.Length = value & SQL_FN_STR_LENGTH;
					data.Locate = value & SQL_FN_STR_LOCATE;
					data.Locate2 = value & SQL_FN_STR_LOCATE_2;
					data.LTrim = value & SQL_FN_STR_LTRIM;
					data.OctetLength = value & SQL_FN_STR_OCTET_LENGTH;
					data.Position = value & SQL_FN_STR_POSITION;
					data.Repeat = value & SQL_FN_STR_REPEAT;
					data.Replace = value & SQL_FN_STR_REPLACE;
					data.Right = value & SQL_FN_STR_RIGHT;
					data.RTrim = value & SQL_FN_STR_RTRIM;
					data.SoundEx = value & SQL_FN_STR_SOUNDEX;
					data.Space = value & SQL_FN_STR_SPACE;
					data.SubString = value & SQL_FN_STR_SUBSTRING;
					data.UCase = value & SQL_FN_STR_UCASE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedSubQueryPredicates CDbConnection::getSupportedSubQueryPredicates(bool *succeeded)
		{
			DbSupportedSubQueryPredicates data{ false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SUBQUERIES, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.CorrelatedSubQueries = value & SQL_SQ_CORRELATED_SUBQUERIES;
					data.Comparison = value & SQL_SQ_COMPARISON;
					data.Exists = value & SQL_SQ_EXISTS;
					data.In = value & SQL_SQ_IN;
					data.Quantified = value & SQL_SQ_QUANTIFIED;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedSystemFunctions CDbConnection::getSupportedSystemFunctions(bool *succeeded)
		{
			DbSupportedSystemFunctions data{ false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_SYSTEM_FUNCTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.DBName = value & SQL_FN_SYS_DBNAME;
					data.IfNull = value & SQL_FN_SYS_IFNULL;
					data.UserName = value & SQL_FN_SYS_USERNAME;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		String CDbConnection::getTableVendorName(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_TABLE_TERM, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_TABLE_TERM, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		DbSupportedDateTimeIntervals CDbConnection::getSupportedDateTimeAddIntervals(bool *succeeded)
		{
			DbSupportedDateTimeIntervals data{ false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_TIMEDATE_ADD_INTERVALS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.SecondFracture = value & SQL_FN_TSI_FRAC_SECOND;
					data.Second = value & SQL_FN_TSI_SECOND;
					data.Minute = value & SQL_FN_TSI_MINUTE;
					data.Hour = value & SQL_FN_TSI_HOUR;
					data.Day = value & SQL_FN_TSI_DAY;
					data.Week = value & SQL_FN_TSI_WEEK;
					data.Month = value & SQL_FN_TSI_MONTH;
					data.Quarter = value & SQL_FN_TSI_QUARTER;
					data.Year = value & SQL_FN_TSI_YEAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedDateTimeIntervals CDbConnection::getSupportedDateTimeDiffIntervals(bool *succeeded)
		{
			DbSupportedDateTimeIntervals data{ false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_TIMEDATE_DIFF_INTERVALS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.SecondFracture = value & SQL_FN_TSI_FRAC_SECOND;
					data.Second = value & SQL_FN_TSI_SECOND;
					data.Minute = value & SQL_FN_TSI_MINUTE;
					data.Hour = value & SQL_FN_TSI_HOUR;
					data.Day = value & SQL_FN_TSI_DAY;
					data.Week = value & SQL_FN_TSI_WEEK;
					data.Month = value & SQL_FN_TSI_MONTH;
					data.Quarter = value & SQL_FN_TSI_QUARTER;
					data.Year = value & SQL_FN_TSI_YEAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedTimeDateFunctions CDbConnection::getSupportedTimeDateFunctions(bool *succeeded)
		{
			DbSupportedTimeDateFunctions data{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_TIMEDATE_FUNCTIONS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.CurrentDate = value & SQL_FN_TD_CURRENT_DATE;
					data.CurrentTime = value & SQL_FN_TD_CURRENT_TIME;
					data.CurrentTimestamp = value & SQL_FN_TD_CURRENT_TIMESTAMP;
					data.CurDate = value & SQL_FN_TD_CURDATE;
					data.CurTime = value & SQL_FN_TD_CURTIME;
					data.DayName = value & SQL_FN_TD_DAYNAME;
					data.DayOfMonth = value & SQL_FN_TD_DAYOFMONTH;
					data.DayOfWeek = value & SQL_FN_TD_DAYOFWEEK;
					data.DayOfYear = value & SQL_FN_TD_DAYOFYEAR;
					data.Extract = value & SQL_FN_TD_EXTRACT;
					data.Hour = value & SQL_FN_TD_HOUR;
					data.Minute = value & SQL_FN_TD_MINUTE;
					data.Month = value & SQL_FN_TD_MONTH;
					data.MonthName = value & SQL_FN_TD_MONTHNAME;
					data.Now = value & SQL_FN_TD_NOW;
					data.Quarter = value & SQL_FN_TD_QUARTER;
					data.Second = value & SQL_FN_TD_SECOND;
					data.TimestampAdd = value & SQL_FN_TD_TIMESTAMPADD;
					data.TimestampDiff = value & SQL_FN_TD_TIMESTAMPDIFF;
					data.Week = value & SQL_FN_TD_WEEK;
					data.Year = value & SQL_FN_TD_YEAR;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbTransactionSupport CDbConnection::getTransactionSupport(bool *succeeded)
		{
			DbTransactionSupport data{ DbTransactionSupport::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUSMALLINT value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_TXN_CAPABLE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_TC_NONE:
						data = DbTransactionSupport::None;
						break;
					case SQL_TC_DML:
						data = DbTransactionSupport::DataManipulation;
						break;
					case SQL_TC_DDL_COMMIT:
						data = DbTransactionSupport::DataDefinitionCommit;
						break;
					case SQL_TC_DDL_IGNORE:
						data = DbTransactionSupport::DataDefinitionIgnore;
						break;
					case SQL_TC_ALL:
						data = DbTransactionSupport::All;
						break;
					default:
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedTransactionIsolationLevels CDbConnection::getSupportedTransactionIsolationLevels(bool *succeeded)
		{
			DbSupportedTransactionIsolationLevels data{ false, false, false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_TXN_ISOLATION_OPTION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.ReadUncommited = value & SQL_TXN_READ_UNCOMMITTED;
					data.ReadCommited = value & SQL_TXN_READ_COMMITTED;
					data.RepeatableRead = value & SQL_TXN_REPEATABLE_READ;
					data.Serializable = value & SQL_TXN_SERIALIZABLE;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbSupportedUnionClauses CDbConnection::getSupportedUnionClauses(bool *succeeded)
		{
			DbSupportedUnionClauses data{ false, false, false };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER value;
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_UNION, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					data.Valid = true;
					data.Union = value & SQL_U_UNION;
					data.All = value & SQL_U_UNION_ALL;
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		String CDbConnection::getUserName(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_USER_NAME, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_USER_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}

		String CDbConnection::getOpenGroupSpecificationPublicationYear(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_XOPEN_CLI_YEAR, &t, sizeof(SQLWCHAR), &value_len) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLGetInfoW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_XOPEN_CLI_YEAR, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							String r{ value };
						#else
							String r{ CDb::UTF16ToString((char16_t*)value) };
						#endif
							delete[] value;
							if (succeeded)
								*succeeded = true;
							return r;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
					}
					else
					{
						if (succeeded)
							*succeeded = true;
						return L"";
					}
				}
				else
					HandleError(__FUNCTION__, "SQLGetInfo", result_line, ERROR_DB_GET_CONNECTION_ATTRIBUTE, result, false, L"", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return L"";
		}
	#pragma endregion

	#pragma region IDbConnection setters
		void CDbConnection::setErrorListener(IErrorListener *value)
		{
			m_pErrorListener = value;
		}

		bool CDbConnection::setAssignErrorListener(const bool value)
		{
			if (value != m_bAssignErrorListener)
			{
				m_bAssignErrorListener = value;
				return true;
			}
			return false;
		}

		bool CDbConnection::setReadOnlyMode(const bool value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER v{ value ? (SQLUINTEGER)SQL_MODE_READ_ONLY : (SQLUINTEGER)SQL_MODE_READ_WRITE };
				SQLRETURN result{ SQLSetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_ACCESS_MODE, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetConnectAttr", result_line, ERROR_DB_SET_CONNECTION_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbConnection::setAutoCommit(const bool value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER v{ value ? (SQLUINTEGER)SQL_AUTOCOMMIT_ON : (SQLUINTEGER)SQL_AUTOCOMMIT_OFF };
				SQLRETURN result{ SQLSetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_AUTOCOMMIT, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetConnectAttr", result_line, ERROR_DB_SET_CONNECTION_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbConnection::setTrace(const bool value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER v{ value ? (SQLUINTEGER)SQL_OPT_TRACE_ON : (SQLUINTEGER)SQL_OPT_TRACE_OFF };
				SQLRETURN result{ SQLSetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_TRACE, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetConnectAttr", result_line, ERROR_DB_SET_CONNECTION_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbConnection::setTraceFilename(const String &value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR *v;
			#ifdef _WIN32
				v = wcsdup(value.c_str());
			#else
				std::u16string value_utf16{ CDb::StringToUTF16(value) };
				v = (SQLWCHAR*)value_utf16.c_str();
			#endif
				SQLRETURN result{ SQLSetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_TRACEFILE, v, (SQLINTEGER)value.length()) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(v);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetConnectAttr", result_line, ERROR_DB_SET_CONNECTION_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbConnection::setConnectionTimeout(const int value)
		{
		#if __has_include(<sqlext.h>)
			if (value >= 0 && m_hHandle)
			{
				SQLUINTEGER v{ (SQLUINTEGER)value };
				SQLRETURN result{ SQLSetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_CONNECTION_TIMEOUT, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetConnectAttr", result_line, ERROR_DB_SET_CONNECTION_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbConnection::setLoginTimeout(const int value)
		{
		#if __has_include(<sqlext.h>)
			if (value >= 0 && m_hHandle)
			{
				SQLUINTEGER v{ (SQLUINTEGER)value };
				SQLRETURN result{ SQLSetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_LOGIN_TIMEOUT, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetConnectAttr", result_line, ERROR_DB_SET_CONNECTION_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbConnection::setTransactionIsolationLevels(const DbSupportedTransactionIsolationLevels value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLUINTEGER v{ 0 };
				if (value.ReadUncommited)
					v |= SQL_TXN_READ_UNCOMMITTED;
				if (value.ReadCommited)
					v |= SQL_TXN_READ_COMMITTED;
				if (value.RepeatableRead)
					v |= SQL_TXN_REPEATABLE_READ;
				if (value.Serializable)
					v |= SQL_TXN_SERIALIZABLE;
				SQLRETURN result{ SQLSetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_TXN_ISOLATION, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetConnectAttr", result_line, ERROR_DB_SET_CONNECTION_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbConnection::setWindow(IWindow *value)
		{
		#if __has_include(<sqlext.h>)
			if (value != m_pWindow && m_hHandle && (!value || value->Handle))
			{
				SQLRETURN result{ SQLSetConnectAttrW(*reinterpret_cast<SQLHDBC*>(&m_hHandle), SQL_ATTR_QUIET_MODE, value ? value->Handle : nullptr, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetConnectAttr", result_line, ERROR_DB_SET_CONNECTION_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}
	#pragma endregion

	#pragma region IDbConnection statements
		IDbStatement *CDbConnection::CreateStatement()
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLHANDLE handle;
				SQLRETURN result{ SQLAllocHandle(SQL_HANDLE_STMT, *reinterpret_cast<SQLHANDLE*>(&m_hHandle), &handle) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					CDbStatement *statement{ new CDbStatement(*reinterpret_cast<PlatformHandle*>(&handle), this) };
					statement->RegisterReleaseListener(&m_cStatementReleaseListener);
					if (m_bAssignErrorListener)
						statement->setErrorListener(m_pErrorListener);
					m_aStatements.push_back(statement);
					return statement;
				}
				HandleError(__FUNCTION__, "SQLAllocHandle", result_line, ERROR_DB_ALLOCATE_STATEMENT_HANDLE, result, false, L"", true);
			}
		#endif
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		void CDbConnection::HandleError(const AnsiString &funcA, const AnsiString &funcB, const int line, const ErrorInfo &error, const short result, const bool has_no_data, const String &attribute, const bool has_busy)
		{
		#if __has_include(<sqlext.h>)
			if (m_pErrorListener)
			{
				if (result == SQL_INVALID_HANDLE)
					m_pErrorListener->NotifyOnError(funcA + "::" + funcB, line, ERROR_GENERAL_INVALID_HANDLE);
				else if (result == SQL_ERROR)
					CDb::HandleDbcError(funcA + "::" + funcB, line, error, m_hHandle, m_pErrorListener);
				else if (has_no_data && result == SQL_NO_DATA)
					m_pErrorListener->NotifyOnError(funcA + "::" + funcB, line, ERROR_DB_ATTRIBUTE_UNDEFINED, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute } });
				else if (has_busy && result == SQL_STILL_EXECUTING)
					m_pErrorListener->NotifyOnError(funcA + "::" + funcB, line, ERROR_DB_BUSY);
				else
					m_pErrorListener->NotifyOnError(funcA + "::" + funcB, line, ERROR_GENERAL_UNKNOWN);
			}
		#endif
		}
	#pragma endregion
	}
}