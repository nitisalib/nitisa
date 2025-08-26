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
	#pragma region Constructor & destructor
		CDbStatement::CDbStatement(PlatformHandle handle, CDbConnection *connection) :
			CReleasable()
		{
			m_hHandle = handle;
			m_pConnection = connection;
			m_pErrorListener = nullptr;
		}

		void CDbStatement::BeforeRelease()
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				CReleasable::BeforeRelease();
				SQLFreeHandle(SQL_HANDLE_STMT, *reinterpret_cast<SQLHANDLE*>(&m_hHandle));
				m_hHandle = nullptr;
			}
		#endif
		}
	#pragma endregion

	#pragma region IDbStatement getters
		bool CDbStatement::isAsyncEnabled(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN value;
				SQLRETURN result{ SQLGetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_ASYNC_ENABLE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_ASYNC_ENABLE_ON;
				}
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_GET_STATEMENT_ATTRIBUTE, result, true, L"SQL_ATTR_ASYNC_ENABLE", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		DbCursorConcurrency CDbStatement::getCursorConcurrency(bool *succeeded)
		{
			DbCursorConcurrency data{ DbCursorConcurrency::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN value;
				SQLRETURN result{ SQLGetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_CONCURRENCY, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_CONCUR_READ_ONLY:
						data = DbCursorConcurrency::ReadOnly;
						break;
					case SQL_CONCUR_LOCK:
						data = DbCursorConcurrency::Lock;
						break;
					case SQL_CONCUR_ROWVER:
						data = DbCursorConcurrency::Rows;
						break;
					case SQL_CONCUR_VALUES:
						data = DbCursorConcurrency::Values;
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_GET_STATEMENT_ATTRIBUTE, result, true, L"SQL_ATTR_CONCURRENCY", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbStatement::isCursorScrollable(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN value;
				SQLRETURN result{ SQLGetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_CURSOR_SCROLLABLE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_SCROLLABLE;
				}
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_GET_STATEMENT_ATTRIBUTE, result, true, L"SQL_ATTR_CURSOR_SCROLLABLE", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		DbCursorSensitivity CDbStatement::getCursorSensitivity(bool *succeeded)
		{
			DbCursorSensitivity data{ DbCursorSensitivity::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN value;
				SQLRETURN result{ SQLGetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_CURSOR_SENSITIVITY, &value, 0, nullptr) };
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
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_GET_STATEMENT_ATTRIBUTE, result, true, L"SQL_ATTR_CURSOR_SENSITIVITY", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		DbCursorType CDbStatement::getCursorType(bool *succeeded)
		{
			DbCursorType data{ DbCursorType::Unknown };
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN value;
				SQLRETURN result{ SQLGetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_CURSOR_TYPE, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_CURSOR_FORWARD_ONLY:
						data = DbCursorType::ForwardOnly;
						break;
					case SQL_CURSOR_STATIC:
						data = DbCursorType::Static;
						break;
					case SQL_CURSOR_KEYSET_DRIVEN:
						data = DbCursorType::Keyset;
						break;
					case SQL_CURSOR_DYNAMIC:
						data = DbCursorType::Dynamic;
						break;
					}
					if (succeeded)
						*succeeded = true;
					return data;
				}
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_GET_STATEMENT_ATTRIBUTE, result, true, L"SQL_ATTR_CURSOR_TYPE", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return data;
		}

		bool CDbStatement::isAutoIPDEnabled(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN value;
				SQLRETURN result{ SQLGetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_ENABLE_AUTO_IPD, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_TRUE;
				}
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_GET_STATEMENT_ATTRIBUTE, result, true, L"SQL_ATTR_ENABLE_AUTO_IPD", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbStatement::isStringArgumentsOfCatalogFunctionsTreatedAsIdentifiers(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN value;
				SQLRETURN result{ SQLGetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_METADATA_ID, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_TRUE;
				}
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_GET_STATEMENT_ATTRIBUTE, result, true, L"SQL_ATTR_METADATA_ID", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbStatement::isScanEscapeSequences(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN value;
				SQLRETURN result{ SQLGetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_NOSCAN, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_NOSCAN_OFF;
				}
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_GET_STATEMENT_ATTRIBUTE, result, true, L"SQL_ATTR_NOSCAN", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		int CDbStatement::getQueryTimeout(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN value;
				SQLRETURN result{ SQLGetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_QUERY_TIMEOUT, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return (int)value;
				}
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_GET_STATEMENT_ATTRIBUTE, result, true, L"SQL_ATTR_QUERY_TIMEOUT", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}

		bool CDbStatement::isBookmarksEnabled(bool *succeeded)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN value;
				SQLRETURN result{ SQLGetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_USE_BOOKMARKS, &value, 0, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (succeeded)
						*succeeded = true;
					return value == SQL_UB_VARIABLE;
				}
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_GET_STATEMENT_ATTRIBUTE, result, true, L"SQL_ATTR_USE_BOOKMARKS", false);
			}
		#endif
			if (succeeded)
				*succeeded = false;
			return false;
		}
	#pragma endregion

	#pragma region IDbStatement setters
		void CDbStatement::setErrorListener(IErrorListener *value)
		{
			m_pErrorListener = value;
		}

		bool CDbStatement::setAsyncEnabled(const bool value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN v{ value ? SQL_ASYNC_ENABLE_ON : SQL_ASYNC_ENABLE_OFF };
				SQLRETURN result{ SQLSetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_ASYNC_ENABLE, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_SET_STATEMENT_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::setCursorConcurrency(const DbCursorConcurrency value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle && value != DbCursorConcurrency::Unknown)
			{
				SQLULEN v;
				switch (value)
				{
				case DbCursorConcurrency::Lock:
					v = SQL_CONCUR_LOCK;
					break;
				case DbCursorConcurrency::Rows:
					v = SQL_CONCUR_ROWVER;
					break;
				case DbCursorConcurrency::Values:
					v = SQL_CONCUR_VALUES;
					break;
				default:
					v = SQL_CONCUR_READ_ONLY;
					break;
				}
				SQLRETURN result{ SQLSetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_CONCURRENCY, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_SET_STATEMENT_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::setCursorScrollable(const bool value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN v{ value ? SQLULEN(SQL_SCROLLABLE) : SQLULEN(SQL_NONSCROLLABLE) };
				SQLRETURN result{ SQLSetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_CURSOR_SCROLLABLE, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_SET_STATEMENT_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::setCursorSensitivity(const DbCursorSensitivity value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle && value != DbCursorSensitivity::Unknown)
			{
				SQLULEN v;
				switch (value)
				{
				case DbCursorSensitivity::Insensitive:
					v = SQL_INSENSITIVE;
					break;
				case DbCursorSensitivity::Sensitive:
					v = SQL_SENSITIVE;
					break;
				default:
					v = SQL_UNSPECIFIED;
					break;
				}
				SQLRETURN result{ SQLSetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_CURSOR_SENSITIVITY, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_SET_STATEMENT_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::setCursorType(const DbCursorType value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle && value != DbCursorType::Unknown)
			{
				SQLULEN v;
				switch (value)
				{
				case DbCursorType::Static:
					v = SQL_CURSOR_STATIC;
					break;
				case DbCursorType::Keyset:
					v = SQL_CURSOR_KEYSET_DRIVEN;
					break;
				case DbCursorType::Dynamic:
					v = SQL_CURSOR_DYNAMIC;
					break;
				default:
					v = SQL_CURSOR_FORWARD_ONLY;
					break;
				}
				SQLRETURN result{ SQLSetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_CURSOR_TYPE, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_SET_STATEMENT_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::setAutoIPDEnabled(const bool value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN v{ value ? SQLULEN(SQL_TRUE) : SQLULEN(SQL_FALSE) };
				SQLRETURN result{ SQLSetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_ENABLE_AUTO_IPD, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_SET_STATEMENT_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::setStringArgumentsOfCatalogFunctionsTreatedAsIdentifiers(const bool value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN v{ value ? SQLULEN(SQL_TRUE) : SQLULEN(SQL_FALSE) };
				SQLRETURN result{ SQLSetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_METADATA_ID, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_SET_STATEMENT_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::setScanEscapeSequences(const bool value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN v{ value ? SQL_NOSCAN_OFF : SQL_NOSCAN_ON };
				SQLRETURN result{ SQLSetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_NOSCAN, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_SET_STATEMENT_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::setQueryTimeout(const int value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle && value >= 0)
			{
				SQLULEN v{ (SQLULEN)value };
				SQLRETURN result{ SQLSetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_QUERY_TIMEOUT, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_SET_STATEMENT_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::setBookmarksEnabled(const bool value)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLULEN v{ value ? SQL_UB_VARIABLE : SQL_UB_OFF };
				SQLRETURN result{ SQLSetStmtAttrW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_ATTR_USE_BOOKMARKS, &v, 0) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					return true;
				HandleError(__FUNCTION__, "SQLSetStmtAttr", result_line, ERROR_DB_SET_STATEMENT_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::setRetrieveColumnAutoIncrementing(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.AutoIncrementing)
			{
				m_sRetrieveColumnInformation.AutoIncrementing = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnName(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.Name)
			{
				m_sRetrieveColumnInformation.Name = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnBaseTableName(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.BaseTableName)
			{
				m_sRetrieveColumnInformation.BaseTableName = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnCaseSensitive(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.CaseSensitive)
			{
				m_sRetrieveColumnInformation.CaseSensitive = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnCatalogName(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.CatalogName)
			{
				m_sRetrieveColumnInformation.CatalogName = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnConciseType(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.ConciseType)
			{
				m_sRetrieveColumnInformation.ConciseType = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnMaximumDisplayLength(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.MaximumDisplayLength)
			{
				m_sRetrieveColumnInformation.MaximumDisplayLength = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnFixedPrecisionScale(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.FixedPrecisionScale)
			{
				m_sRetrieveColumnInformation.FixedPrecisionScale = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnLabel(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.Label)
			{
				m_sRetrieveColumnInformation.Label = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnMaximumLength(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.MaximumLength)
			{
				m_sRetrieveColumnInformation.MaximumLength = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnLiteralPrefix(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.LiteralPrefix)
			{
				m_sRetrieveColumnInformation.LiteralPrefix = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnLiteralSuffix(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.LiteralSuffix)
			{
				m_sRetrieveColumnInformation.LiteralSuffix = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnLocalTypeName(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.LocalTypeName)
			{
				m_sRetrieveColumnInformation.LocalTypeName = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnAlias(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.Alias)
			{
				m_sRetrieveColumnInformation.Alias = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnNullability(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.Nullability)
			{
				m_sRetrieveColumnInformation.Nullability = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnPrecisionRadix(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.PrecisionRadix)
			{
				m_sRetrieveColumnInformation.PrecisionRadix = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnPrecision(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.Precision)
			{
				m_sRetrieveColumnInformation.Precision = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnScale(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.Scale)
			{
				m_sRetrieveColumnInformation.Scale = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnSchemaName(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.SchemaName)
			{
				m_sRetrieveColumnInformation.SchemaName = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnSearchable(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.Searchable)
			{
				m_sRetrieveColumnInformation.Searchable = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnTableName(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.TableName)
			{
				m_sRetrieveColumnInformation.TableName = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnDataTypeName(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.DataTypeName)
			{
				m_sRetrieveColumnInformation.DataTypeName = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnUnnamed(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.Unnamed)
			{
				m_sRetrieveColumnInformation.Unnamed = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnUpdatable(const bool value)
		{
			if (value != m_sRetrieveColumnInformation.Updatable)
			{
				m_sRetrieveColumnInformation.Updatable = value;
				return true;
			}
			return false;
		}

		bool CDbStatement::setRetrieveColumnAllAttributes(const bool value)
		{
			bool changed{ false };
			if (value != m_sRetrieveColumnInformation.AutoIncrementing)
			{
				m_sRetrieveColumnInformation.AutoIncrementing = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.Name)
			{
				m_sRetrieveColumnInformation.Name = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.BaseTableName)
			{
				m_sRetrieveColumnInformation.BaseTableName = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.CaseSensitive)
			{
				m_sRetrieveColumnInformation.CaseSensitive = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.CatalogName)
			{
				m_sRetrieveColumnInformation.CatalogName = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.ConciseType)
			{
				m_sRetrieveColumnInformation.ConciseType = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.MaximumDisplayLength)
			{
				m_sRetrieveColumnInformation.MaximumDisplayLength = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.FixedPrecisionScale)
			{
				m_sRetrieveColumnInformation.FixedPrecisionScale = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.Label)
			{
				m_sRetrieveColumnInformation.Label = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.MaximumLength)
			{
				m_sRetrieveColumnInformation.MaximumLength = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.LiteralPrefix)
			{
				m_sRetrieveColumnInformation.LiteralPrefix = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.LiteralSuffix)
			{
				m_sRetrieveColumnInformation.LiteralSuffix = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.LocalTypeName)
			{
				m_sRetrieveColumnInformation.LocalTypeName = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.Alias)
			{
				m_sRetrieveColumnInformation.Alias = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.Nullability)
			{
				m_sRetrieveColumnInformation.Nullability = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.PrecisionRadix)
			{
				m_sRetrieveColumnInformation.PrecisionRadix = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.Precision)
			{
				m_sRetrieveColumnInformation.Precision = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.Scale)
			{
				m_sRetrieveColumnInformation.Scale = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.SchemaName)
			{
				m_sRetrieveColumnInformation.SchemaName = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.Searchable)
			{
				m_sRetrieveColumnInformation.Searchable = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.TableName)
			{
				m_sRetrieveColumnInformation.TableName = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.DataTypeName)
			{
				m_sRetrieveColumnInformation.DataTypeName = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.Unnamed)
			{
				m_sRetrieveColumnInformation.Unnamed = value;
				changed = true;
			}
			if (value != m_sRetrieveColumnInformation.Updatable)
			{
				m_sRetrieveColumnInformation.Updatable = value;
				changed = true;
			}
			return changed;
		}
	#pragma endregion

	#pragma region IDbStatement queries
		bool CDbStatement::Prepare(const String &query)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle && query.length() > 0)
			{
				SQLWCHAR *v;
			#ifdef _WIN32
				v = wcsdup(query.c_str());
			#else
				std::u16string query_utf16{ CDb::StringToUTF16(query) };
				v = (SQLWCHAR*)query_utf16.c_str();
			#endif
				SQLRETURN result{ SQLPrepareW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), v, (SQLINTEGER)query.length()) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(v);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					m_sPreparedQuery = query;
					return true;
				}
				HandleError(__FUNCTION__, "SQLPrepare", result_line, ERROR_DB_PREPARE, result, false, L"", true);
			}
		#endif
			return false;
		}

		DbResult CDbStatement::Execute()
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle && m_sPreparedQuery.length() > 0)
			{
				if (Exec(DbRow{}, L""))
					db_result = CreateResult();
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::Execute(const DbRow &row, const bool validate)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle && m_sPreparedQuery.length() > 0 && (!validate || Validate(row)))
			{
				if (Exec(row, L""))
					db_result = CreateResult();
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_RESET_PARAMS);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::Execute(const DbRows &rows, const bool validate)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle && m_sPreparedQuery.length() > 0 && (!validate || Validate(rows)))
			{
				DbResult t;
				for (auto const &row : rows)
				{
					if (Exec(row, L""))
						t = CreateResult();
					SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
					SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_RESET_PARAMS);
					if (!t.Successful)
						return t;
					db_result.AffectedRowCount += t.AffectedRowCount;
					db_result.Rows.insert(db_result.Rows.end(), t.Rows.begin(), t.Rows.end());
					if (db_result.Columns.size() == 0)
						db_result.Columns = t.Columns;
				}
				db_result.Successful = true;
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::Execute(const String &query)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle && query.length() > 0)
			{
				if (Exec(DbRow{}, query))
					db_result = CreateResult();
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::Execute(const String &query, const DbRow &row, const bool validate)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle && query.length() > 0 && (!validate || Validate(row)))
			{
				if (Exec(row, query))
					db_result = CreateResult();
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_RESET_PARAMS);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::Execute(const String &query, const DbRows &rows, const bool validate)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle && query.length() > 0 && (!validate || Validate(rows)))
			{
				DbResult t;
				for (auto const &row : rows)
				{
					if (Exec(row, query))
						t = CreateResult();
					SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
					SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_RESET_PARAMS);
					if (!t.Successful)
						return t;
					db_result.AffectedRowCount += t.AffectedRowCount;
					db_result.Rows.insert(db_result.Rows.end(), t.Rows.begin(), t.Rows.end());
					if (db_result.Columns.size() == 0)
						db_result.Columns = t.Columns;
				}
				db_result.Successful = true;
			}
		#endif
			return db_result;
		}
	#pragma endregion

	#pragma region IDbStatement query objects
		DbResult CDbStatement::QueryAllCatalogs()
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
			#ifdef _WIN32
				SQLRETURN result{ SQLTablesW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), (SQLWCHAR*)SQL_ALL_CATALOGS, SQL_NTS, (SQLWCHAR*)L"", SQL_NTS, (SQLWCHAR*)L"", SQL_NTS, nullptr, 0) };
				int result_line{ __LINE__ - 1 };
			#else
				SQLRETURN result{ SQLTablesW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), (SQLWCHAR*)SQL_ALL_CATALOGS, SQL_NTS, (SQLWCHAR*)u"", SQL_NTS, (SQLWCHAR*)"", SQL_NTS, nullptr, 0) };
				int result_line{ __LINE__ - 1 };
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLTables", result_line, ERROR_DB_GET_TABLES, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryAllTableTypes()
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
			#ifdef _WIN32
				SQLRETURN result{ SQLTablesW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), (SQLWCHAR*)L"", SQL_NTS, (SQLWCHAR*)L"", SQL_NTS, (SQLWCHAR*)L"", SQL_NTS, (SQLWCHAR*)SQL_ALL_TABLE_TYPES, SQL_NTS) };
				int result_line{ __LINE__ - 1 };
			#else
				SQLRETURN result{ SQLTablesW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), (SQLWCHAR*)u"", SQL_NTS, (SQLWCHAR*)u"", SQL_NTS, (SQLWCHAR*)u"", SQL_NTS, (SQLWCHAR*)SQL_ALL_TABLE_TYPES, SQL_NTS) };
				int result_line{ __LINE__ - 1 };
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLTables", result_line, ERROR_DB_GET_TABLES, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryAllSchemes()
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
			#ifdef _WIN32
				SQLRETURN result{ SQLTablesW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), (SQLWCHAR*)L"", SQL_NTS, (SQLWCHAR*)SQL_ALL_SCHEMAS, SQL_NTS, (SQLWCHAR*)L"", SQL_NTS, nullptr, 0) };
				int result_line{ __LINE__ - 1 };
			#else
				SQLRETURN result{ SQLTablesW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), (SQLWCHAR*)u"", SQL_NTS, (SQLWCHAR*)SQL_ALL_SCHEMAS, SQL_NTS, (SQLWCHAR*)u"", SQL_NTS, nullptr, 0) };
				int result_line{ __LINE__ - 1 };
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLTables", result_line, ERROR_DB_GET_TABLES, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryTables(const String &catalog, const String &table, const String &schema, const StringArray &types)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				StringArray types_uppercase;
				for (auto type : types)
					types_uppercase.push_back(ToUpper(type));
				SQLWCHAR *t1, *t2, *t3, *t4;
			#ifdef _WIN32
				t1 = wcsdup(catalog.c_str());
				t2 = wcsdup(schema.c_str());
				t3 = wcsdup(table.c_str());
				t4 = wcsdup(Implode(L",", types_uppercase).c_str());
			#else
				std::u16string t1_utf16{ CDb::StringToUTF16(catalog) };
				std::u16string t2_utf16{ CDb::StringToUTF16(schema) };
				std::u16string t3_utf16{ CDb::StringToUTF16(table) };
				std::u16string t4_utf16{ CDb::StringToUTF16(Implode(L",", types_uppercase)) };
				t1 = (SQLWCHAR*)t1_utf16.c_str();
				t2 = (SQLWCHAR*)t2_utf16.c_str();
				t3 = (SQLWCHAR*)t3_utf16.c_str();
				t4 = (SQLWCHAR*)t4_utf16.c_str();
			#endif
				SQLRETURN result{ SQLTablesW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), t1, SQL_NTS, t2, SQL_NTS, t3, SQL_NTS, t4, SQL_NTS) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(t1);
				free(t2);
				free(t3);
				free(t4);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLTables", result_line, ERROR_DB_GET_TABLES, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryTablePrivileges(const String &catalog, const String &table, const String &schema)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR *t1, *t2, *t3;
			#ifdef _WIN32
				t1 = wcsdup(catalog.c_str());
				t2 = wcsdup(schema.c_str());
				t3 = wcsdup(table.c_str());
			#else
				std::u16string t1_utf16{ CDb::StringToUTF16(catalog) };
				std::u16string t2_utf16{ CDb::StringToUTF16(schema) };
				std::u16string t3_utf16{ CDb::StringToUTF16(table) };
				t1 = (SQLWCHAR*)t1_utf16.c_str();
				t2 = (SQLWCHAR*)t2_utf16.c_str();
				t3 = (SQLWCHAR*)t3_utf16.c_str();
			#endif
				SQLRETURN result{ SQLTablePrivilegesW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), t1, SQL_NTS, t2, SQL_NTS, t3, SQL_NTS) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(t1);
				free(t2);
				free(t3);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLTablePrivileges", result_line, ERROR_DB_GET_TABLE_PRIVILEGES, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryColumns(const String &catalog, const String &table, const String &schema, const String &column)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR *t1, *t2, *t3, *t4;
			#ifdef _WIN32
				t1 = wcsdup(catalog.c_str());
				t2 = wcsdup(schema.c_str());
				t3 = wcsdup(table.c_str());
				t4 = wcsdup(column.c_str());
			#else
				std::u16string t1_utf16{ CDb::StringToUTF16(catalog) };
				std::u16string t2_utf16{ CDb::StringToUTF16(schema) };
				std::u16string t3_utf16{ CDb::StringToUTF16(table) };
				std::u16string t4_utf16{ CDb::StringToUTF16(column) };
				t1 = (SQLWCHAR*)t1_utf16.c_str();
				t2 = (SQLWCHAR*)t2_utf16.c_str();
				t3 = (SQLWCHAR*)t3_utf16.c_str();
				t4 = (SQLWCHAR*)t4_utf16.c_str();
			#endif
				SQLRETURN result{ SQLColumnsW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), t1, SQL_NTS, t2, SQL_NTS, t3, SQL_NTS, t4, SQL_NTS) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(t1);
				free(t2);
				free(t3);
				free(t4);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLColumns", result_line, ERROR_DB_GET_COLUMNS, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryColumnPrivileges(const String &catalog, const String &table, const String &schema, const String &column)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR *t1, *t2, *t3, *t4;
			#ifdef _WIN32
				t1 = wcsdup(catalog.c_str());
				t2 = wcsdup(schema.c_str());
				t3 = wcsdup(table.c_str());
				t4 = wcsdup(column.c_str());
			#else
				std::u16string t1_utf16{ CDb::StringToUTF16(catalog) };
				std::u16string t2_utf16{ CDb::StringToUTF16(schema) };
				std::u16string t3_utf16{ CDb::StringToUTF16(table) };
				std::u16string t4_utf16{ CDb::StringToUTF16(column) };
				t1 = (SQLWCHAR*)t1_utf16.c_str();
				t2 = (SQLWCHAR*)t2_utf16.c_str();
				t3 = (SQLWCHAR*)t3_utf16.c_str();
				t4 = (SQLWCHAR*)t4_utf16.c_str();
			#endif
				SQLRETURN result{ SQLColumnPrivilegesW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), t1, SQL_NTS, t2, SQL_NTS, t3, SQL_NTS, t4, SQL_NTS) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(t1);
				free(t2);
				free(t3);
				free(t4);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLColumnPrivileges", result_line, ERROR_DB_GET_COLUMN_PRIVILEGES, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QuerySpecialColumns(const String &catalog, const String &table, const String &schema, const bool autoupdated, const DbSpecialColumnScope scope, const bool nullable)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR *t1, *t2, *t3;
			#ifdef _WIN32
				t1 = wcsdup(catalog.c_str());
				t2 = wcsdup(schema.c_str());
				t3 = wcsdup(table.c_str());
			#else
				std::u16string t1_utf16{ CDb::StringToUTF16(catalog) };
				std::u16string t2_utf16{ CDb::StringToUTF16(schema) };
				std::u16string t3_utf16{ CDb::StringToUTF16(table) };
				t1 = (SQLWCHAR*)t1_utf16.c_str();
				t2 = (SQLWCHAR*)t2_utf16.c_str();
				t3 = (SQLWCHAR*)t3_utf16.c_str();
			#endif
				SQLRETURN result{ SQLSpecialColumnsW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), autoupdated ? SQL_ROWVER : SQL_BEST_ROWID, t1, SQL_NTS, t2, SQL_NTS, t3, SQL_NTS, (scope == DbSpecialColumnScope::Transaction) ? SQL_SCOPE_TRANSACTION : ((scope == DbSpecialColumnScope::Session) ? SQL_SCOPE_SESSION : SQL_SCOPE_CURROW), nullable ? SQL_NULLABLE : SQL_NO_NULLS) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(t1);
				free(t2);
				free(t3);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLSpecialColumns", result_line, ERROR_DB_GET_SPECIAL_COLUMNS, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryProcedureColumns(const String &catalog, const String &procedure, const String &schema, const String &column)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR *t1, *t2, *t3, *t4;
			#ifdef _WIN32
				t1 = wcsdup(catalog.c_str());
				t2 = wcsdup(schema.c_str());
				t3 = wcsdup(procedure.c_str());
				t4 = wcsdup(column.c_str());
			#else
				std::u16string t1_utf16{ CDb::StringToUTF16(catalog) };
				std::u16string t2_utf16{ CDb::StringToUTF16(schema) };
				std::u16string t3_utf16{ CDb::StringToUTF16(procedure) };
				std::u16string t4_utf16{ CDb::StringToUTF16(column) };
				t1 = (SQLWCHAR*)t1_utf16.c_str();
				t2 = (SQLWCHAR*)t2_utf16.c_str();
				t3 = (SQLWCHAR*)t3_utf16.c_str();
				t4 = (SQLWCHAR*)t4_utf16.c_str();
			#endif
				SQLRETURN result{ SQLProcedureColumnsW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), t1, SQL_NTS, t2, SQL_NTS, t3, SQL_NTS, t4, SQL_NTS) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(t1);
				free(t2);
				free(t3);
				free(t4);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLProcedureColumns", result_line, ERROR_DB_GET_PROCEDURE_COLUMNS, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryForeignKeys(const String &pk_catalog, const String &pk_table, const String &pk_schema, const String &fk_catalog, const String &fk_table, const String &fk_schema)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR *p1, *p2, *p3, *f1, *f2, *f3;
			#ifdef _WIN32
				p1 = wcsdup(pk_catalog.c_str());
				p2 = wcsdup(pk_schema.c_str());
				p3 = wcsdup(pk_table.c_str());
				f1 = wcsdup(fk_catalog.c_str());
				f2 = wcsdup(fk_schema.c_str());
				f3 = wcsdup(fk_table.c_str());
			#else
				std::u16string p1_utf16{ CDb::StringToUTF16(pk_catalog) };
				std::u16string p2_utf16{ CDb::StringToUTF16(pk_schema) };
				std::u16string p3_utf16{ CDb::StringToUTF16(pk_table) };
				std::u16string f1_utf16{ CDb::StringToUTF16(fk_catalog) };
				std::u16string f2_utf16{ CDb::StringToUTF16(fk_schema) };
				std::u16string f3_utf16{ CDb::StringToUTF16(fk_table) };
				p1 = (SQLWCHAR*)p1_utf16.c_str();
				p2 = (SQLWCHAR*)p2_utf16.c_str();
				p3 = (SQLWCHAR*)p3_utf16.c_str();
				f1 = (SQLWCHAR*)f1_utf16.c_str();
				f2 = (SQLWCHAR*)f2_utf16.c_str();
				f3 = (SQLWCHAR*)f3_utf16.c_str();
			#endif
				SQLRETURN result{ SQLForeignKeysW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), p1, SQL_NTS, p2, SQL_NTS, p3, SQL_NTS, f1, SQL_NTS, f2, SQL_NTS, f3, SQL_NTS) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(p1);
				free(p2);
				free(p3);
				free(f1);
				free(f2);
				free(f3);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLForeignKeys", result_line, ERROR_DB_GET_FOREIGN_KEYS, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryPrimaryKeys(const String &catalog, const String &table, const String &schema)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR *t1, *t2, *t3;
			#ifdef _WIN32
				t1 = wcsdup(catalog.c_str());
				t2 = wcsdup(schema.c_str());
				t3 = wcsdup(table.c_str());
			#else
				std::u16string t1_utf16{ CDb::StringToUTF16(catalog) };
				std::u16string t2_utf16{ CDb::StringToUTF16(schema) };
				std::u16string t3_utf16{ CDb::StringToUTF16(table) };
				t1 = (SQLWCHAR*)t1_utf16.c_str();
				t2 = (SQLWCHAR*)t2_utf16.c_str();
				t3 = (SQLWCHAR*)t3_utf16.c_str();
			#endif
				SQLRETURN result{ SQLPrimaryKeysW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), t1, SQL_NTS, t2, SQL_NTS, t3, SQL_NTS) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(t1);
				free(t2);
				free(t3);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLPrimaryKeys", result_line, ERROR_DB_GET_PRIMARY_KEYS, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryProcedures(const String &catalog, const String &procedure, const String &schema)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR *t1, *t2, *t3;
			#ifdef _WIN32
				t1 = wcsdup(catalog.c_str());
				t2 = wcsdup(schema.c_str());
				t3 = wcsdup(procedure.c_str());
			#else
				std::u16string t1_utf16{ CDb::StringToUTF16(catalog) };
				std::u16string t2_utf16{ CDb::StringToUTF16(schema) };
				std::u16string t3_utf16{ CDb::StringToUTF16(procedure) };
				t1 = (SQLWCHAR*)t1_utf16.c_str();
				t2 = (SQLWCHAR*)t2_utf16.c_str();
				t3 = (SQLWCHAR*)t3_utf16.c_str();
			#endif
				SQLRETURN result{ SQLProceduresW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), t1, SQL_NTS, t2, SQL_NTS, t3, SQL_NTS) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(t1);
				free(t2);
				free(t3);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLProcedures", result_line, ERROR_DB_GET_PROCEDURES, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}

		DbResult CDbStatement::QueryStatistic(const String &catalog, const String &table, const String &schema, const bool unique_indexes_only, const bool quick_return)
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR *t1, *t2, *t3;
			#ifdef _WIN32
				t1 = wcsdup(catalog.c_str());
				t2 = wcsdup(schema.c_str());
				t3 = wcsdup(table.c_str());
			#else
				std::u16string t1_utf16{ CDb::StringToUTF16(catalog) };
				std::u16string t2_utf16{ CDb::StringToUTF16(schema) };
				std::u16string t3_utf16{ CDb::StringToUTF16(table) };
				t1 = (SQLWCHAR*)t1_utf16.c_str();
				t2 = (SQLWCHAR*)t2_utf16.c_str();
				t3 = (SQLWCHAR*)t3_utf16.c_str();
			#endif
				SQLRETURN result{ SQLStatisticsW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), t1, SQL_NTS, t2, SQL_NTS, t3, SQL_NTS, unique_indexes_only ? SQL_INDEX_UNIQUE : SQL_INDEX_ALL, quick_return ? SQL_QUICK : SQL_ENSURE) };
				int result_line{ __LINE__ - 1 };
			#ifdef _WIN32
				free(t1);
				free(t2);
				free(t3);
			#endif
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
					db_result = CreateResult();
				else
					HandleError(__FUNCTION__, "SQLStatistics", result_line, ERROR_DB_GET_STATISTICS, result, false, L"", true);
				SQLFreeStmt(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQL_CLOSE);
			}
		#endif
			return db_result;
		}
	#pragma endregion

	#pragma region Helpers
		void CDbStatement::HandleError(const AnsiString &funcA, const AnsiString &funcB, const int line, const ErrorInfo &error, const short result, const bool has_no_data, const String &attribute, const bool has_busy)
		{
		#if __has_include(<sqlext.h>)
			if (m_pErrorListener)
			{
				if (result == SQL_INVALID_HANDLE)
					m_pErrorListener->NotifyOnError(funcA + "::" + funcB, line, ERROR_GENERAL_INVALID_HANDLE);
				else if (result == SQL_ERROR)
					CDb::HandleStmError(funcA + "::" + funcB, line, error, m_hHandle, m_pErrorListener);
				else if (has_no_data && result == SQL_NO_DATA)
					m_pErrorListener->NotifyOnError(funcA + "::" + funcB, line, ERROR_DB_ATTRIBUTE_UNDEFINED, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute } });
				else if (has_busy && result == SQL_STILL_EXECUTING)
					m_pErrorListener->NotifyOnError(funcA + "::" + funcB, line, ERROR_DB_BUSY);
				else
					m_pErrorListener->NotifyOnError(funcA + "::" + funcB, line, ERROR_GENERAL_UNKNOWN);
			}
		#endif
		}

		bool CDbStatement::Validate(const DbRow &row)
		{
			if (row.size() == 0) // There should be at least one value in the row
			{
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_DB_VALIDATE_ROW_EMPTY);
				return false;
			}
			return true;
		}

		bool CDbStatement::Validate(const DbRows &rows)
		{
			if (rows.size() == 0) // There should be at least one row
			{
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_DB_VALIDATE_ROWS_EMPTY);
				return false;
			}
			size_t size{ rows[0].size() };
			if (size == 0) // There should be at least one value in the first row
			{
				if (m_pErrorListener)
					m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_DB_VALIDATE_ROW_EMPTY);
				return false;
			}
			for (size_t row_index = 0; row_index < rows.size(); row_index++)
			{
				if (rows[row_index].size() != size) // All rows should have the same number of values
				{
					if (m_pErrorListener)
						m_pErrorListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_DB_VALIDATE_DIFFERENT_SIZE_ROWS, StringKeyValueArray{
							StringKeyValue{ L"{row}", ToString(uint(row_index + 1)) },
							StringKeyValue{ L"{size}", ToString(uint(rows[row_index].size())) },
							StringKeyValue{ L"{first}", ToString(uint(size)) }
						});
					return false;
				}
			}
			return true;
		}

		DbResult CDbStatement::CreateResult()
		{
			DbResult db_result;
		#if __has_include(<sqlext.h>)
			SQLSMALLINT column_count;
			SQLRETURN result{ SQLNumResultCols(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), &column_count) };
			int result_line{ __LINE__ - 1 };
			if (result != SQL_SUCCESS && result != SQL_SUCCESS_WITH_INFO)
			{
				HandleError(__FUNCTION__, "SQLNumResultCols", result_line, ERROR_DB_GET_RESULT_COLUMN_COUNT, result, false, L"", true);
				return db_result;
			}
			if (column_count > 0)
			{
				DbColumns columns;
				columns.resize(column_count);
				if (RetrieveColumnAttributes(columns))
				{
					DbRows rows;
					char v_char;
					byte v_byte;
					short v_short;
					unsigned short v_ushort;
					int v_int;
					uint v_uint;
					int64 v_int64;
					uint64 v_uint64;
					float v_float;
					double v_double;
					static SQLWCHAR v_string[1024];
					static char v_ansi[1024];
					byte v_buffer[1024];
					SQL_DATE_STRUCT v_date;
					SQL_TIME_STRUCT v_time;
					SQL_TIMESTAMP_STRUCT v_timestamp;
					SQLLEN len;
					while (true)
					{
						result = SQLFetch(*reinterpret_cast<SQLHSTMT*>(&m_hHandle));
						result_line = __LINE__ - 1;
						if (result == SQL_NO_DATA)
							break;
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
							DbRow row;
							row.resize(columns.size());
							for (size_t i = 0; i < columns.size(); i++)
							{
								switch (columns[i].DataType)
								{
									//case SQLDataTypes::Char:
									//case SQLDataTypes::VarChar:
									//case SQLDataTypes::LongVarChar:
								case DbDataType::WChar:
								case DbDataType::WVarChar:
								case DbDataType::WLongChar:
									{
										StringArray parts;
										bool getting{ true };
										while (getting)
										{
											result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_WCHAR, v_string, 1024, &len);
											result_line = __LINE__ - 1;
											switch (result)
											{
											case SQL_SUCCESS:
											case SQL_SUCCESS_WITH_INFO:
												if (len == SQL_NULL_DATA)
													getting = false;
												else
												#ifdef _WIN32
													parts.push_back(v_string);
												#else
													parts.push_back(CDb::UTF16ToString((char16_t*)v_string));
												#endif
												break;
											case SQL_NO_DATA:
												getting = false;
												break;
											default:
												HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
												return db_result;
											}
										}
										if (parts.size() > 0)
											row[i] = Implode(L"", parts);
										break;
									}
								case DbDataType::Decimal:
								case DbDataType::Numeric:
								case DbDataType::Float:
								case DbDataType::Double:
									result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_DOUBLE, &v_double, 0, &len);
									result_line = __LINE__ - 1;
									switch (result)
									{
									case SQL_SUCCESS:
									case SQL_SUCCESS_WITH_INFO:
										if (len != SQL_NULL_DATA)
											row[i] = v_double;
										break;
									case SQL_NO_DATA:
										break;
									default:
										HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
										return db_result;
									}
									break;
								case DbDataType::SmallInt:
									if (columns[i].Unsigned)
									{
										result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_USHORT, &v_ushort, 0, &len);
										result_line = __LINE__ - 1;
										switch (result)
										{
										case SQL_SUCCESS:
										case SQL_SUCCESS_WITH_INFO:
											if (len != SQL_NULL_DATA)
												row[i] = v_ushort;
											break;
										case SQL_NO_DATA:
											break;
										default:
											HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
											return db_result;
										}
									}
									else
									{
										result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_SSHORT, &v_short, 0, &len);
										result_line = __LINE__ - 1;
										switch (result)
										{
										case SQL_SUCCESS:
										case SQL_SUCCESS_WITH_INFO:
											if (len != SQL_NULL_DATA)
												row[i] = v_short;
											break;
										case SQL_NO_DATA:
											break;
										default:
											HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
											return db_result;
										}
									}
									break;
								case DbDataType::Integer:
									if (columns[i].Unsigned)
									{
										result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_ULONG, &v_uint, 0, &len);
										result_line = __LINE__ - 1;
										switch (result)
										{
										case SQL_SUCCESS:
										case SQL_SUCCESS_WITH_INFO:
											if (len != SQL_NULL_DATA)
												row[i] = v_uint;
											break;
										case SQL_NO_DATA:
											break;
										default:
											HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
											return db_result;
										}
									}
									else
									{
										result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_SLONG, &v_int, 0, &len);
										result_line = __LINE__ - 1;
										switch (result)
										{
										case SQL_SUCCESS:
										case SQL_SUCCESS_WITH_INFO:
											if (len != SQL_NULL_DATA)
												row[i] = v_int;
											break;
										case SQL_NO_DATA:
											break;
										default:
											HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
											return db_result;
										}
									}
									break;
								case DbDataType::Real:
									result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_FLOAT, &v_float, 0, &len);
									result_line = __LINE__ - 1;
									switch (result)
									{
									case SQL_SUCCESS:
									case SQL_SUCCESS_WITH_INFO:
										if (len != SQL_NULL_DATA)
											row[i] = v_float;
										break;
									case SQL_NO_DATA:
										break;
									default:
										HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
										return db_result;
									}
									break;
								case DbDataType::Bit:
									result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_BIT, &v_byte, 0, &len);
									result_line = __LINE__ - 1;
									switch (result)
									{
									case SQL_SUCCESS:
									case SQL_SUCCESS_WITH_INFO:
										if (len != SQL_NULL_DATA)
											row[i] = v_byte;
										break;
									case SQL_NO_DATA:
										break;
									default:
										HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
										return db_result;
									}
									break;
								case DbDataType::TinyInt:
									if (columns[i].Unsigned)
									{
										result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_UTINYINT, &v_byte, 0, &len);
										result_line = __LINE__ - 1;
										switch (result)
										{
										case SQL_SUCCESS:
										case SQL_SUCCESS_WITH_INFO:
											if (len != SQL_NULL_DATA)
												row[i] = v_byte;
											break;
										case SQL_NO_DATA:
											break;
										default:
											HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
											return db_result;
										}
									}
									else
									{
										result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_STINYINT, &v_char, 0, &len);
										result_line = __LINE__ - 1;
										switch (result)
										{
										case SQL_SUCCESS:
										case SQL_SUCCESS_WITH_INFO:
											if (len != SQL_NULL_DATA)
												row[i] = v_char;
											break;
										case SQL_NO_DATA:
											break;
										default:
											HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
											return db_result;
										}
									}
									break;
								case DbDataType::BigInt:
									if (columns[i].Unsigned)
									{
										result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_UBIGINT, &v_uint64, 0, &len);
										result_line = __LINE__ - 1;
										switch (result)
										{
										case SQL_SUCCESS:
										case SQL_SUCCESS_WITH_INFO:
											if (len != SQL_NULL_DATA)
												row[i] = v_uint64;
											break;
										case SQL_NO_DATA:
											break;
										default:
											HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
											return db_result;
										}
									}
									else
									{
										result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_SBIGINT, &v_int64, 0, &len);
										result_line = __LINE__ - 1;
										switch (result)
										{
										case SQL_SUCCESS:
										case SQL_SUCCESS_WITH_INFO:
											if (len != SQL_NULL_DATA)
												row[i] = v_int64;
											break;
										case SQL_NO_DATA:
											break;
										default:
											HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
											return db_result;
										}
									}
									break;
								case DbDataType::Binary:
								case DbDataType::VarBinary:
								case DbDataType::LongVarBinary:
									{
										std::vector<ByteArray> parts;
										bool getting{ true };
										while (getting)
										{
											result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_BINARY, v_buffer, 1024, &len);
											result_line = __LINE__ - 1;
											switch (result)
											{
											case SQL_SUCCESS:
											case SQL_SUCCESS_WITH_INFO:
												if (len == SQL_NULL_DATA)
													getting = false;
												else
												{
													ByteArray buffer;
													buffer.resize(len);
													for (SQLLEN j = 0; j < len; j++)
														buffer[j] = v_buffer[j];
													parts.push_back(buffer);
												}
												break;
											case SQL_NO_DATA:
												getting = false;
												break;
											default:
												HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
												return db_result;
											}
										}
										if (parts.size() > 0)
											row[i] = Merge(parts);
										break;
									}
								case DbDataType::Date:
									result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_TYPE_DATE, &v_date, sizeof(SQL_DATE_STRUCT), &len);
									result_line = __LINE__ - 1;
									switch (result)
									{
									case SQL_SUCCESS:
									case SQL_SUCCESS_WITH_INFO:
										if (len != SQL_NULL_DATA)
											row[i] = DbDate{ (short)v_date.year, (unsigned short)v_date.month, (unsigned short)v_date.day };
										break;
									case SQL_NO_DATA:
										break;
									default:
										HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
										return db_result;
									}
									break;
								case DbDataType::Time:
									result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_TYPE_TIME, &v_time, sizeof(SQL_DATE_STRUCT), &len);
									result_line = __LINE__ - 1;
									switch (result)
									{
									case SQL_SUCCESS:
									case SQL_SUCCESS_WITH_INFO:
										if (len != SQL_NULL_DATA)
											row[i] = DbTime{ (unsigned short)v_time.hour, (unsigned short)v_time.minute, (unsigned short)v_time.second };
										break;
									case SQL_NO_DATA:
										break;
									default:
										HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
										return db_result;
									}
									break;
								case DbDataType::DateTime:
									result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_TYPE_TIMESTAMP, &v_timestamp, sizeof(SQL_DATE_STRUCT), &len);
									result_line = __LINE__ - 1;
									switch (result)
									{
									case SQL_SUCCESS:
									case SQL_SUCCESS_WITH_INFO:
										if (len != SQL_NULL_DATA)
											row[i] = DbDateTime{ DbDate{ (short)v_timestamp.year, (unsigned short)v_timestamp.month, (unsigned short)v_timestamp.day },
												DbTime{ (unsigned short)v_timestamp.hour, (unsigned short)v_timestamp.minute, (unsigned short)v_timestamp.second },
												(unsigned int)v_timestamp.fraction };
										break;
									case SQL_NO_DATA:
										break;
									default:
										HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
										return db_result;
									}
									break;
									/*case SQLDataTypes::IntervalMonth:
									case SQLDataTypes::IntervalYear:
									case SQLDataTypes::IntervalYearToMonth:
									case SQLDataTypes::IntervalDay:
									case SQLDataTypes::IntervalHour:
									case SQLDataTypes::IntervalMinute:
									case SQLDataTypes::IntervalSecond:
									case SQLDataTypes::IntervalDayToHour:
									case SQLDataTypes::IntervalDayToMinute:
									case SQLDataTypes::IntervalDayToSecond:
									case SQLDataTypes::IntervalHourToMinute:
									case SQLDataTypes::IntervalHourToSecond:
									case SQLDataTypes::IntervalMinuteToSecond:
									case SQLDataTypes::Guid:*/
								default: // Threat everything else as an ANSI string
									{
										AnsiStringArray parts;
										bool getting{ true };
										while (getting)
										{
											result = SQLGetData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(i + 1), SQL_C_CHAR, v_ansi, 1024, &len);
											result_line = __LINE__ - 1;
											switch (result)
											{
											case SQL_SUCCESS:
											case SQL_SUCCESS_WITH_INFO:
												if (len == SQL_NULL_DATA)
													getting = false;
												else
													parts.push_back(v_ansi);
												break;
											case SQL_NO_DATA:
												getting = false;
												break;
											default:
												HandleError(__FUNCTION__, "SQLGetData", result_line, ERROR_DB_GET_DATA, result, false, L"", true);
												return db_result;
											}
										}
										if (parts.size() > 0)
											row[i] = Implode("", parts);
										break;
									}
								}
							}
							rows.push_back(row);
							continue;
						}
						HandleError(__FUNCTION__, "SQLFetch", result_line, ERROR_DB_FETCH, result, true, L"(none)", true);
					}
					db_result.Successful = true;
					db_result.Rows = rows;
					db_result.Columns = columns;
					return db_result;
				}
			}
			else
			{
				SQLLEN row_count;
				result = SQLRowCount(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), &row_count);
				result_line = __LINE__ - 1;
				if (result != SQL_SUCCESS && result != SQL_SUCCESS_WITH_INFO)
				{
					HandleError(__FUNCTION__, "SQLRowCount", result_line, ERROR_DB_GET_AFFECTED_ROW_COUNT, result, false, L"", false);
					return db_result;
				}
				db_result.Successful = true;
				db_result.AffectedRowCount = (int64)row_count;
			}
		#endif
			return db_result;
		}

		bool CDbStatement::RetrieveColumnAutoIncrementing(const unsigned short index, bool &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_AUTO_UNIQUE_VALUE, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = value == SQL_TRUE;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnName(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_BASE_COLUMN_NAME, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_BASE_COLUMN_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnBaseTableName(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_BASE_TABLE_NAME, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_BASE_TABLE_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnCaseSensitive(const unsigned short index, bool &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_CASE_SENSITIVE, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = value == SQL_TRUE;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnCatalogName(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_CATALOG_NAME, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_CATALOG_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnConciseType(const unsigned short index, DbDataType &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_CONCISE_TYPE, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_CHAR:
						attribute = DbDataType::Char;
						return true;
					case SQL_VARCHAR:
						attribute = DbDataType::VarChar;
						return true;
					case SQL_LONGVARCHAR:
						attribute = DbDataType::LongVarChar;
						return true;
					case SQL_WCHAR:
						attribute = DbDataType::WChar;
						return true;
					case SQL_WVARCHAR:
						attribute = DbDataType::WVarChar;
						return true;
					case SQL_WLONGVARCHAR:
						attribute = DbDataType::WLongChar;
						return true;
					case SQL_DECIMAL:
						attribute = DbDataType::Decimal;
						return true;
					case SQL_NUMERIC:
						attribute = DbDataType::Numeric;
						return true;
					case SQL_SMALLINT:
						attribute = DbDataType::SmallInt;
						return true;
					case SQL_INTEGER:
						attribute = DbDataType::Integer;
						return true;
					case SQL_REAL:
						attribute = DbDataType::Real;
						return true;
					case SQL_FLOAT:
						attribute = DbDataType::Float;
						return true;
					case SQL_DOUBLE:
						attribute = DbDataType::Double;
						return true;
					case SQL_BIT:
						attribute = DbDataType::Bit;
						return true;
					case SQL_TINYINT:
						attribute = DbDataType::TinyInt;
						return true;
					case SQL_BIGINT:
						attribute = DbDataType::BigInt;
						return true;
					case SQL_BINARY:
						attribute = DbDataType::Binary;
						return true;
					case SQL_VARBINARY:
						attribute = DbDataType::VarBinary;
						return true;
					case SQL_LONGVARBINARY:
						attribute = DbDataType::LongVarBinary;
						return true;
					case SQL_TYPE_DATE:
						attribute = DbDataType::Date;
						return true;
					case SQL_TIME:
					case SQL_TYPE_TIME:
						attribute = DbDataType::Time;
						return true;
					case SQL_DATETIME:
					case SQL_TYPE_TIMESTAMP:
						attribute = DbDataType::DateTime;
						return true;
					case SQL_INTERVAL_MONTH:
						attribute = DbDataType::IntervalMonth;
						return true;
					case SQL_INTERVAL_YEAR:
						attribute = DbDataType::IntervalYear;
						return true;
					case SQL_INTERVAL_YEAR_TO_MONTH:
						attribute = DbDataType::IntervalYearToMonth;
						return true;
					case SQL_INTERVAL_DAY:
						attribute = DbDataType::IntervalDay;
						return true;
					case SQL_INTERVAL_HOUR:
						attribute = DbDataType::IntervalHour;
						return true;
					case SQL_INTERVAL_MINUTE:
						attribute = DbDataType::IntervalMinute;
						return true;
					case SQL_INTERVAL_SECOND:
						attribute = DbDataType::IntervalSecond;
						return true;
					case SQL_INTERVAL_DAY_TO_HOUR:
						attribute = DbDataType::IntervalDayToHour;
						return true;
					case SQL_INTERVAL_DAY_TO_MINUTE:
						attribute = DbDataType::IntervalDayToMinute;
						return true;
					case SQL_INTERVAL_DAY_TO_SECOND:
						attribute = DbDataType::IntervalDayToSecond;
						return true;
					case SQL_INTERVAL_HOUR_TO_MINUTE:
						attribute = DbDataType::IntervalHourToMinute;
						return true;
					case SQL_INTERVAL_HOUR_TO_SECOND:
						attribute = DbDataType::IntervalHourToSecond;
						return true;
					case SQL_INTERVAL_MINUTE_TO_SECOND:
						attribute = DbDataType::IntervalMinuteToSecond;
						return true;
					case SQL_GUID:
						attribute = DbDataType::Guid;
						return true;
					default:
						attribute = DbDataType::Unknown;
						return true;
					}
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnMaximumDisplayLength(const unsigned short index, int64 &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_DISPLAY_SIZE, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = (int64)value;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnFixedPrecisionScale(const unsigned short index, bool &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_FIXED_PREC_SCALE, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = value == SQL_TRUE;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnLabel(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_LABEL, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_LABEL, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnMaximumLength(const unsigned short index, int64 &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_LENGTH, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = (int64)value;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnLiteralPrefix(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_LITERAL_PREFIX, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_LITERAL_PREFIX, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnLiteralSuffix(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_LITERAL_SUFFIX, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_LITERAL_SUFFIX, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnLocalTypeName(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_LOCAL_TYPE_NAME, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_LOCAL_TYPE_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnAlias(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_NAME, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnNullability(const unsigned short index, DbNullabilityType &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_NULLABLE, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_NULLABLE:
						attribute = DbNullabilityType::Nullable;
						return true;
					case SQL_NO_NULLS:
						attribute = DbNullabilityType::NoNulls;
						return true;
					default:
						attribute = DbNullabilityType::Unknown;
						return true;
					}
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnPrecisionRadix(const unsigned short index, int &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_NUM_PREC_RADIX, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = (int)value;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnOctetLength(const unsigned short index, int64 &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_OCTET_LENGTH, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = (int64)value;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnPrecision(const unsigned short index, int &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_PRECISION, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = (int)value;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnScale(const unsigned short index, int &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_SCALE, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = (int)value;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnSchemaName(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_SCHEMA_NAME, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_SCHEMA_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnSearchable(const unsigned short index, DbSearchableType &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_SEARCHABLE, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_PRED_NONE:
						attribute = DbSearchableType::None;
						return true;
					case SQL_PRED_CHAR:
						attribute = DbSearchableType::Char;
						return true;
					case SQL_PRED_BASIC:
						attribute = DbSearchableType::Basic;
						return true;
					case SQL_PRED_SEARCHABLE:
						attribute = DbSearchableType::Searchable;
						return true;
					default:
						attribute = DbSearchableType::Unknown;
						return true;
					}
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnTableName(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_TABLE_NAME, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_TABLE_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnDataType(const unsigned short index, DbDataType &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_TYPE, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_CHAR:
						attribute = DbDataType::Char;
						return true;
					case SQL_VARCHAR:
						attribute = DbDataType::VarChar;
						return true;
					case SQL_LONGVARCHAR:
						attribute = DbDataType::LongVarChar;
						return true;
					case SQL_WCHAR:
						attribute = DbDataType::WChar;
						return true;
					case SQL_WVARCHAR:
						attribute = DbDataType::WVarChar;
						return true;
					case SQL_WLONGVARCHAR:
						attribute = DbDataType::WLongChar;
						return true;
					case SQL_DECIMAL:
						attribute = DbDataType::Decimal;
						return true;
					case SQL_NUMERIC:
						attribute = DbDataType::Numeric;
						return true;
					case SQL_SMALLINT:
						attribute = DbDataType::SmallInt;
						return true;
					case SQL_INTEGER:
						attribute = DbDataType::Integer;
						return true;
					case SQL_REAL:
						attribute = DbDataType::Real;
						return true;
					case SQL_FLOAT:
						attribute = DbDataType::Float;
						return true;
					case SQL_DOUBLE:
						attribute = DbDataType::Double;
						return true;
					case SQL_BIT:
						attribute = DbDataType::Bit;
						return true;
					case SQL_TINYINT:
						attribute = DbDataType::TinyInt;
						return true;
					case SQL_BIGINT:
						attribute = DbDataType::BigInt;
						return true;
					case SQL_BINARY:
						attribute = DbDataType::Binary;
						return true;
					case SQL_VARBINARY:
						attribute = DbDataType::VarBinary;
						return true;
					case SQL_LONGVARBINARY:
						attribute = DbDataType::LongVarBinary;
						return true;
					case SQL_TYPE_DATE:
						attribute = DbDataType::Date;
						return true;
					case SQL_TIME:
					case SQL_TYPE_TIME:
						attribute = DbDataType::Time;
						return true;
					case SQL_DATETIME:
					case SQL_TYPE_TIMESTAMP:
						attribute = DbDataType::DateTime;
						return true;
					case SQL_INTERVAL_MONTH:
						attribute = DbDataType::IntervalMonth;
						return true;
					case SQL_INTERVAL_YEAR:
						attribute = DbDataType::IntervalYear;
						return true;
					case SQL_INTERVAL_YEAR_TO_MONTH:
						attribute = DbDataType::IntervalYearToMonth;
						return true;
					case SQL_INTERVAL_DAY:
						attribute = DbDataType::IntervalDay;
						return true;
					case SQL_INTERVAL_HOUR:
						attribute = DbDataType::IntervalHour;
						return true;
					case SQL_INTERVAL_MINUTE:
						attribute = DbDataType::IntervalMinute;
						return true;
					case SQL_INTERVAL_SECOND:
						attribute = DbDataType::IntervalSecond;
						return true;
					case SQL_INTERVAL_DAY_TO_HOUR:
						attribute = DbDataType::IntervalDayToHour;
						return true;
					case SQL_INTERVAL_DAY_TO_MINUTE:
						attribute = DbDataType::IntervalDayToMinute;
						return true;
					case SQL_INTERVAL_DAY_TO_SECOND:
						attribute = DbDataType::IntervalDayToSecond;
						return true;
					case SQL_INTERVAL_HOUR_TO_MINUTE:
						attribute = DbDataType::IntervalHourToMinute;
						return true;
					case SQL_INTERVAL_HOUR_TO_SECOND:
						attribute = DbDataType::IntervalHourToSecond;
						return true;
					case SQL_INTERVAL_MINUTE_TO_SECOND:
						attribute = DbDataType::IntervalMinuteToSecond;
						return true;
					case SQL_GUID:
						attribute = DbDataType::Guid;
						return true;
					default:
						attribute = DbDataType::Unknown;
						return true;
					}
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnDataTypeName(const unsigned short index, String &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLWCHAR t;
				SQLSMALLINT value_len{ 0 };
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_TYPE_NAME, &t, sizeof(SQLWCHAR), &value_len, nullptr) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					if (value_len > 0)
					{
						SQLWCHAR *value{ new SQLWCHAR[value_len / sizeof(SQLWCHAR) + 1] };
						SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_TYPE_NAME, value, SQLSMALLINT(value_len + sizeof(SQLWCHAR)), &value_len, nullptr) };
						int result_line{ __LINE__ - 1 };
						if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
						{
						#ifdef _WIN32
							attribute = value;
						#else
							attribute = CDb::UTF16ToString((char16_t*)value);
						#endif
							delete[] value;
							return true;
						}
						delete[] value;
						HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
					}
					else
					{
						attribute = L"";
						return true;
					}
				}
				else
					HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnUnnamed(const unsigned short index, bool &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_UNNAMED, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = value == SQL_UNNAMED;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnUnsigned(const unsigned short index, bool &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_UNSIGNED, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					attribute = value == SQL_TRUE;
					return true;
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnUpdatable(const unsigned short index, DbUpdatableType &attribute)
		{
		#if __has_include(<sqlext.h>)
			if (m_hHandle)
			{
				SQLLEN value;
				SQLRETURN result{ SQLColAttributeW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), index, SQL_DESC_UPDATABLE, nullptr, 0, nullptr, &value) };
				int result_line{ __LINE__ - 1 };
				if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO)
				{
					switch (value)
					{
					case SQL_ATTR_READONLY:
						attribute = DbUpdatableType::ReadOnly;
						return true;
					case SQL_ATTR_WRITE:
						attribute = DbUpdatableType::Write;
						return true;
					case SQL_ATTR_READWRITE_UNKNOWN:
						attribute = DbUpdatableType::Unspecified;
						return true;
					default:
						attribute = DbUpdatableType::Unknown;
						return true;
					}
				}
				HandleError(__FUNCTION__, "SQLColAttribute", result_line, ERROR_DB_GET_COLUMN_ATTRIBUTE, result, false, L"", true);
			}
		#endif
			return false;
		}

		bool CDbStatement::RetrieveColumnAttributes(DbColumns &columns)
		{
			// Mandatory attributes
			for (size_t i = 0; i < columns.size(); i++)
				if (!RetrieveColumnOctetLength((unsigned short)(i + 1), columns[i].OctetLength))
					return false;
			for (size_t i = 0; i < columns.size(); i++)
				if (!RetrieveColumnDataType((unsigned short)(i + 1), columns[i].DataType))
					return false;
			for (size_t i = 0; i < columns.size(); i++)
				if (!RetrieveColumnUnsigned((unsigned short)(i + 1), columns[i].Unsigned))
					return false;
			// Optional attributes
			if (m_sRetrieveColumnInformation.AutoIncrementing)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnAutoIncrementing((unsigned short)(i + 1), columns[i].AutoIncrementing))
						break;
			if (m_sRetrieveColumnInformation.Name)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnName((unsigned short)(i + 1), columns[i].Name))
						break;
			if (m_sRetrieveColumnInformation.BaseTableName)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnBaseTableName((unsigned short)(i + 1), columns[i].BaseTableName))
						break;
			if (m_sRetrieveColumnInformation.CaseSensitive)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnCaseSensitive((unsigned short)(i + 1), columns[i].CaseSensitive))
						break;
			if (m_sRetrieveColumnInformation.CatalogName)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnCatalogName((unsigned short)(i + 1), columns[i].CatalogName))
						break;
			if (m_sRetrieveColumnInformation.ConciseType)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnConciseType((unsigned short)(i + 1), columns[i].ConciseType))
						break;
			if (m_sRetrieveColumnInformation.MaximumDisplayLength)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnMaximumDisplayLength((unsigned short)(i + 1), columns[i].MaximumDisplayLength))
						break;
			if (m_sRetrieveColumnInformation.FixedPrecisionScale)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnFixedPrecisionScale((unsigned short)(i + 1), columns[i].FixedPrecisionScale))
						break;
			if (m_sRetrieveColumnInformation.Label)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnLabel((unsigned short)(i + 1), columns[i].Label))
						break;
			if (m_sRetrieveColumnInformation.MaximumLength)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnMaximumLength((unsigned short)(i + 1), columns[i].MaximumLength))
						break;
			if (m_sRetrieveColumnInformation.LiteralPrefix)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnLiteralPrefix((unsigned short)(i + 1), columns[i].LiteralPrefix))
						break;
			if (m_sRetrieveColumnInformation.LiteralSuffix)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnLiteralSuffix((unsigned short)(i + 1), columns[i].LiteralSuffix))
						break;
			if (m_sRetrieveColumnInformation.LocalTypeName)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnLocalTypeName((unsigned short)(i + 1), columns[i].LocalTypeName))
						break;
			if (m_sRetrieveColumnInformation.Alias)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnAlias((unsigned short)(i + 1), columns[i].Alias))
						break;
			if (m_sRetrieveColumnInformation.Nullability)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnNullability((unsigned short)(i + 1), columns[i].Nullability))
						break;
			if (m_sRetrieveColumnInformation.PrecisionRadix)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnPrecisionRadix((unsigned short)(i + 1), columns[i].PrecisionRadix))
						break;
			if (m_sRetrieveColumnInformation.Precision)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnPrecision((unsigned short)(i + 1), columns[i].Precision))
						break;
			if (m_sRetrieveColumnInformation.Scale)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnScale((unsigned short)(i + 1), columns[i].Scale))
						break;
			if (m_sRetrieveColumnInformation.SchemaName)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnSchemaName((unsigned short)(i + 1), columns[i].SchemaName))
						break;
			if (m_sRetrieveColumnInformation.Searchable)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnSearchable((unsigned short)(i + 1), columns[i].Searchable))
						break;
			if (m_sRetrieveColumnInformation.TableName)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnTableName((unsigned short)(i + 1), columns[i].TableName))
						break;
			if (m_sRetrieveColumnInformation.DataTypeName)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnDataTypeName((unsigned short)(i + 1), columns[i].DataTypeName))
						break;
			if (m_sRetrieveColumnInformation.Unnamed)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnUnnamed((unsigned short)(i + 1), columns[i].Unnamed))
						break;
			if (m_sRetrieveColumnInformation.Updatable)
				for (size_t i = 0; i < columns.size(); i++)
					if (!RetrieveColumnUpdatable((unsigned short)(i + 1), columns[i].Updatable))
						break;
			return true;
		}

		bool CDbStatement::Exec(const DbRow &row, const String &query)
		{
		#if __has_include(<sqlext.h>)
			SQLRETURN result;
			int result_line;
			std::vector<SQLLEN> value_sizes;
		#ifndef _WIN32
			std::vector<std::u16string> utf16strings;
		#endif
			// Bind columns
			if (row.size() > 0)
			{
				SQLSMALLINT c_type, sql_type;
				SQLULEN column_size;
				SQLLEN buffer_size;
				SQLPOINTER value;
				value_sizes.resize(row.size());
				for (size_t index = 0; index < row.size(); index++)
				{
					switch (row[index].Type)
					{
					case DbValueType::Bool:
						c_type = SQL_C_UTINYINT;
						sql_type = SQL_TINYINT;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(bool);
						break;
					case DbValueType::Char:
						c_type = SQL_C_STINYINT;
						sql_type = SQL_TINYINT;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(char);
						break;
					case DbValueType::Byte:
						c_type = SQL_C_UTINYINT;
						sql_type = SQL_TINYINT;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(byte);
						break;
					case DbValueType::Short:
						c_type = SQL_C_SSHORT;
						sql_type = SQL_SMALLINT;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(short);
						break;
					case DbValueType::UShort:
						c_type = SQL_C_USHORT;
						sql_type = SQL_SMALLINT;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(unsigned short);
						break;
					case DbValueType::Int:
						c_type = SQL_C_SLONG;
						sql_type = SQL_INTEGER;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(int);
						break;
					case DbValueType::UInt:
						c_type = SQL_C_ULONG;
						sql_type = SQL_INTEGER;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(uint);
						break;
					case DbValueType::Int64:
						c_type = SQL_C_SBIGINT;
						sql_type = SQL_BIGINT;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(int64);
						break;
					case DbValueType::UInt64:
						c_type = SQL_C_UBIGINT;
						sql_type = SQL_BIGINT;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(uint64);
						break;
					case DbValueType::Float:
						c_type = SQL_C_FLOAT;
						sql_type = SQL_REAL;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(float);
						break;
					case DbValueType::Double:
						c_type = SQL_C_DOUBLE;
						sql_type = SQL_DOUBLE;
						column_size = 0;
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = sizeof(double);
						break;
					case DbValueType::String:
						c_type = SQL_C_WCHAR;
						column_size = (SQLULEN)row[index].Length();
						if (row[index].Length() >= BATCH_SIZE)
						{
							sql_type = SQL_WLONGVARCHAR;
							value = SQLPOINTER(&row[index]);
							buffer_size = 0;
							value_sizes[index] = SQL_DATA_AT_EXEC;
						}
						else
						{
							sql_type = SQL_WVARCHAR;
						#ifdef _WIN32
							value = (Pointer)row[index];
							buffer_size = (SQLLEN)row[index].Length() * sizeof(wchar_t);
						#else
							utf16strings.push_back(CDb::StringToUTF16((String)row[index]));
							value = (void*)utf16strings[utf16strings.size() - 1].data();
							buffer_size = (SQLLEN)row[index].Length() * sizeof(char16_t);
						#endif
							value_sizes[index] = SQL_NTS;
						}
						break;
					case DbValueType::AnsiString:
						c_type = SQL_C_CHAR;
						column_size = (SQLULEN)row[index].Length();
						if (row[index].Length() >= BATCH_SIZE)
						{
							sql_type = SQL_LONGVARCHAR;
							value = SQLPOINTER(&row[index]);
							buffer_size = 0;
							value_sizes[index] = SQL_DATA_AT_EXEC;
						}
						else
						{
							sql_type = SQL_VARCHAR;
							value = (Pointer)row[index];
							buffer_size = (SQLLEN)row[index].Length() * sizeof(char);
							value_sizes[index] = SQL_NTS;
						}
						break;
					case DbValueType::Buffer:
						c_type = SQL_C_BINARY;
						column_size = (SQLULEN)row[index].Length();
						if (row[index].Length() >= BATCH_SIZE)
						{
							sql_type = SQL_LONGVARBINARY;
							value = SQLPOINTER(&row[index]);
							buffer_size = 0;
							value_sizes[index] = SQL_DATA_AT_EXEC;
						}
						else
						{
							sql_type = SQL_VARBINARY;
							value = (Pointer)row[index];
							buffer_size = (SQLLEN)row[index].Length() * sizeof(byte);
							value_sizes[index] = buffer_size;
						}
						break;
					case DbValueType::Date:
						c_type = SQL_C_DATE;
						sql_type = SQL_DATE;
						column_size = sizeof(DbDate);
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = 0;
						break;
					case DbValueType::Time:
						c_type = SQL_C_TIME;
						sql_type = SQL_TIME;
						column_size = sizeof(DbTime);
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = 0;
						break;
					case DbValueType::DateTime:
						c_type = SQL_C_TIMESTAMP;
						sql_type = SQL_TIMESTAMP;
						column_size = sizeof(DbDateTime);
						value = (Pointer)row[index];
						buffer_size = 0;
						value_sizes[index] = 0;
						break;
					default: // NULL
						c_type = SQL_C_CHAR;
						sql_type = SQL_CHAR;
						column_size = 0;
						value = nullptr;
						buffer_size = 0;
						value_sizes[index] = SQL_NULL_DATA;
						break;
					}
					result = SQLBindParameter(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), SQLUSMALLINT(index + 1), SQL_PARAM_INPUT, c_type, sql_type, column_size, 0, value, buffer_size, &value_sizes[index]);
					result_line = __LINE__ - 1;
					if (result != SQL_SUCCESS && result != SQL_SUCCESS_WITH_INFO)
					{
						HandleError(__FUNCTION__, "SQLBindParameter", result_line, ERROR_DB_BIND_PARAMETER, result, false, L"", false);
						return false;
					}
				}
			}
			// Execute query
			if (query.length() > 0)
			{
				SQLWCHAR *t;
			#ifdef _WIN32
				t = wcsdup(query.c_str());
			#else
				std::u16string query_utf16{ CDb::StringToUTF16(query) };
				t = (SQLWCHAR*)query_utf16.c_str();
			#endif
				result = SQLExecDirectW(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), t, (SQLINTEGER)query.length());
				result_line = __LINE__ - 1;
			#ifdef _WIN32
				free(t);
			#endif
			}
			else
			{
				result = SQLExecute(*reinterpret_cast<SQLHSTMT*>(&m_hHandle));
				result_line = __LINE__ - 1;
			}
			// Send long data if needed
			if (result == SQL_NEED_DATA)
			{
				DbValue *db_value;
			#ifndef _WIN32
				std::u16string utf16string;
			#endif
				while (true)
				{
					result = SQLParamData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), (SQLPOINTER*)&db_value);
					result_line = __LINE__ - 1;
					if (result != SQL_SUCCESS && result != SQL_SUCCESS_WITH_INFO && result != SQL_NO_DATA && result != SQL_NEED_DATA)
					{
						HandleError(__FUNCTION__, "SQLParamData", result_line, ERROR_DB_PARAM_DATA, result, false, L"", true);
						return false;
					}
					if (result == SQL_NEED_DATA)
					{
						byte *buffer{ (byte*)(Pointer)(*db_value) };
					#ifndef _WIN32
						if (db_value->Type == DbValueType::String)
						{
							utf16string = CDb::StringToUTF16((String)(*db_value));
							buffer = (byte*)(Pointer)utf16string.data();
						}
					#endif
						size_t length{ db_value->Length() }, offset{ 0 };
						if (db_value->Type == DbValueType::String)
							length *= 2;
						while (length > BATCH_SIZE)
						{
							result = SQLPutData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), &buffer[offset], (SQLLEN)BATCH_SIZE);
							result_line = __LINE__ - 1;
							offset += BATCH_SIZE;
							length -= BATCH_SIZE;
							if (result != SQL_SUCCESS && result != SQL_SUCCESS_WITH_INFO)
							{
								HandleError(__FUNCTION__, "SQLPutData", result_line, ERROR_DB_PUT_DATA, result, false, L"", true);
								return false;
							}
						}
						result = SQLPutData(*reinterpret_cast<SQLHSTMT*>(&m_hHandle), &buffer[offset], (SQLLEN)length);
						result_line = __LINE__ - 1;
						if (result != SQL_SUCCESS && result != SQL_SUCCESS_WITH_INFO)
						{
							HandleError(__FUNCTION__, "SQLPutData", result_line, ERROR_DB_PUT_DATA, result, false, L"", true);
							return false;
						}
						continue;
					}
					break;
				}
			}
			// Check result
			switch (result)
			{
			case SQL_SUCCESS:
			case SQL_SUCCESS_WITH_INFO:
			case SQL_NO_DATA:
				return true;
			case SQL_PARAM_DATA_AVAILABLE:
				if (m_pErrorListener)
				{
					AnsiString a{ __FUNCTION__ };
					m_pErrorListener->NotifyOnError(a + "::SQLExecute", result_line, ERROR_DB_UNEXPECTED_PARAM_DATA_AVAILABLE);
				}
				return false;
			case SQL_STILL_EXECUTING:
				if (m_pErrorListener)
				{
					AnsiString a{ __FUNCTION__ };
					m_pErrorListener->NotifyOnError(a + "::SQLExecute", result_line, ERROR_DB_BUSY);
				}
				return false;
			case SQL_ERROR:
				if (m_pErrorListener)
				{
					AnsiString a{ __FUNCTION__ };
					CDb::HandleStmError(a + "::SQLExecute", result_line, ERROR_DB_EXECUTE, m_hHandle, m_pErrorListener);
				}
				return false;
			case SQL_INVALID_HANDLE:
				if (m_pErrorListener)
				{
					AnsiString a{ __FUNCTION__ };
					m_pErrorListener->NotifyOnError(a + "::SQLExecute", result_line, ERROR_GENERAL_INVALID_HANDLE);
				}
				return false;
			default:
				if (m_pErrorListener)
				{
					AnsiString a{ __FUNCTION__ };
					m_pErrorListener->NotifyOnError(a + "::SQLExecute", result_line, ERROR_GENERAL_UNKNOWN);
				}
				return false;
			}
		#endif
			return false;
		}
	#pragma endregion
	}
}