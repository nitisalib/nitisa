// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Db/DbCursorConcurrency.h"
#include "../Db/DbCursorSensitivity.h"
#include "../Db/DbCursorType.h"
#include "../Db/DbResult.h"
#include "../Db/DbRow.h"
#include "../Db/DbRows.h"
#include "../Db/DbSpecialColumnScope.h"
#include "../Core/Aliases.h"
#include "../Core/Strings.h"
#include "IReleasable.h"

namespace nitisa
{
	class IDbConnection;
	class IErrorListener;

	class IDbStatement: public virtual IReleasable
	{
	protected:
		IDbStatement() = default;
		~IDbStatement() = default;
		IDbStatement(const IDbStatement &other) = delete;
		IDbStatement(IDbStatement &&other) = delete;
		IDbStatement &operator=(const IDbStatement &other) = delete;
		IDbStatement &operator=(IDbStatement &&other) = delete;
	protected:
		struct RetrieveColumnInformation // Set of flags indicating whether column attributes should be retrieved for query result. By default all of them is set to false
		{
			bool AutoIncrementing;
			bool Name;
			bool BaseTableName;
			bool CaseSensitive;
			bool CatalogName;
			bool ConciseType;
			bool MaximumDisplayLength;
			bool FixedPrecisionScale;
			bool Label;
			bool MaximumLength;
			bool LiteralPrefix;
			bool LiteralSuffix;
			bool LocalTypeName;
			bool Alias;
			bool Nullability;
			bool PrecisionRadix;
			bool Precision;
			bool Scale;
			bool SchemaName;
			bool Searchable;
			bool TableName;
			bool DataTypeName;
			bool Unnamed;
			bool Updatable;

			RetrieveColumnInformation():
				AutoIncrementing{ false },
				Name{ false },
				BaseTableName{ false },
				CaseSensitive{ false },
				CatalogName{ false },
				ConciseType{ false },
				MaximumDisplayLength{ false },
				FixedPrecisionScale{ false },
				Label{ false },
				MaximumLength{ false },
				LiteralPrefix{ false },
				LiteralSuffix{ false },
				LocalTypeName{ false },
				Alias{ false },
				Nullability{ false },
				PrecisionRadix{ false },
				Precision{ false },
				Scale{ false },
				SchemaName{ false },
				Searchable{ false },
				TableName{ false },
				DataTypeName{ false },
				Unnamed{ false },
				Updatable{ false }
			{

			}
		};
	protected:
		PlatformHandle m_hHandle;
		IDbConnection *m_pConnection;
		String m_sPreparedQuery;
		RetrieveColumnInformation m_sRetrieveColumnInformation;
		IErrorListener *m_pErrorListener;
	public:
		PlatformHandle const &Handle{ m_hHandle }; // Platform-dependent statement handle
		IDbConnection* const &Connection{ m_pConnection }; // Parent connection
		String const &PreparedQuery{ m_sPreparedQuery }; // Prepared query this statement works with or empty string
		bool const &RetrieveColumnAutoIncrementing{ m_sRetrieveColumnInformation.AutoIncrementing }; // Whether auto-incrementing information should be retrieved for column information query result. False by default
		bool const &RetrieveColumnName{ m_sRetrieveColumnInformation.Name }; // Whether name should be retrieved for column information query result. False by default
		bool const &RetrieveColumnBaseTableName{ m_sRetrieveColumnInformation.BaseTableName }; // Whether base table name should be retrieved for column information query result. False by default
		bool const &RetrieveColumnCaseSensitive{ m_sRetrieveColumnInformation.CaseSensitive }; // Whether case sensitivity information should be retrieved for column information query result. False by default
		bool const &RetrieveColumnCatalogName{ m_sRetrieveColumnInformation.CatalogName }; // Whether catalog name should be retrieved for column information query result. False by default
		bool const &RetrieveColumnConciseType{ m_sRetrieveColumnInformation.ConciseType }; // Whether concise type should be retrieved for column information query result. False by default
		bool const &RetrieveColumnMaximumDisplayLength{ m_sRetrieveColumnInformation.MaximumDisplayLength }; // Whether maximum display length should be retrieved for column information query result. False by default
		bool const &RetrieveColumnFixedPrecisionScale{ m_sRetrieveColumnInformation.FixedPrecisionScale }; // Whether fixed precision scale should be retrieved for column information query result. False by default
		bool const &RetrieveColumnLabel{ m_sRetrieveColumnInformation.Label }; // Whether label should be retrieved for column information query result. False by default
		bool const &RetrieveColumnMaximumLength{ m_sRetrieveColumnInformation.MaximumLength }; // Whether maximum length should be retrieved for column information query result. False by default
		bool const &RetrieveColumnLiteralPrefix{ m_sRetrieveColumnInformation.LiteralPrefix }; // Whether literal prefix should be retrieved for column information query result. False by default
		bool const &RetrieveColumnLiteralSuffix{ m_sRetrieveColumnInformation.LiteralSuffix }; // Whether literal suffix should be retrieved for column information query result. False by default
		bool const &RetrieveColumnLocalTypeName{ m_sRetrieveColumnInformation.LocalTypeName }; // Whether local type name should be retrieved for column information query result. False by default
		bool const &RetrieveColumnAlias{ m_sRetrieveColumnInformation.Alias }; // Whether alias should be retrieved for column information query result. False by default
		bool const &RetrieveColumnNullability{ m_sRetrieveColumnInformation.Nullability }; // Whether nullability information should be retrieved for column information query result. False by default
		bool const &RetrieveColumnPrecisionRadix{ m_sRetrieveColumnInformation.PrecisionRadix }; // Whether precision radix should be retrieved for column information query result. False by default
		bool const &RetrieveColumnPrecision{ m_sRetrieveColumnInformation.Precision }; // Whether precision should be retrieved for column information query result. False by default
		bool const &RetrieveColumnScale{ m_sRetrieveColumnInformation.Scale }; // Whether scale should be retrieved for column information query result. False by default
		bool const &RetrieveColumnSchemaName{ m_sRetrieveColumnInformation.SchemaName }; // Whether schema name should be retrieved for column information query result. False by default
		bool const &RetrieveColumnSearchable{ m_sRetrieveColumnInformation.Searchable }; // Whether searchability should be retrieved for column information query result. False by default
		bool const &RetrieveColumnTableName{ m_sRetrieveColumnInformation.TableName }; // Whether table name should be retrieved for column information query result. False by default
		bool const &RetrieveColumnDataTypeName{ m_sRetrieveColumnInformation.DataTypeName }; // Whether data type name should be retrieved for column information query result. False by default
		bool const &RetrieveColumnUnnamed{ m_sRetrieveColumnInformation.Unnamed }; // Whether unnamed indicator should be retrieved for column information query result. False by default
		bool const &RetrieveColumnUpdatable{ m_sRetrieveColumnInformation.Updatable }; // Whether updatable indicator should be retrieved for column information query result. False by default
		IErrorListener* const &ErrorListener{ m_pErrorListener }; // Error listener

		// Return options
		virtual bool isAsyncEnabled(bool *succeeded = nullptr) = 0;
		virtual DbCursorConcurrency getCursorConcurrency(bool *succeeded = nullptr) = 0;
		virtual bool isCursorScrollable(bool *succeeded = nullptr) = 0;
		virtual DbCursorSensitivity getCursorSensitivity(bool *succeeded = nullptr) = 0;
		virtual DbCursorType getCursorType(bool *succeeded = nullptr) = 0;
		virtual bool isAutoIPDEnabled(bool *succeeded = nullptr) = 0;
		virtual bool isStringArgumentsOfCatalogFunctionsTreatedAsIdentifiers(bool *succeeded = nullptr) = 0;
		virtual bool isScanEscapeSequences(bool *succeeded = nullptr) = 0;
		virtual int getQueryTimeout(bool *succeeded = nullptr) = 0;
		virtual bool isBookmarksEnabled(bool *succeeded = nullptr) = 0;

		virtual void setErrorListener(IErrorListener *value) = 0; // Assign new error listener. nullptr value if also accepted
		virtual bool setRetrieveColumnAutoIncrementing(const bool value) = 0; // Set whether auto-incrementing information should be retrieved for column information query result
		virtual bool setRetrieveColumnName(const bool value) = 0; // Set whether name should be retrieved for column information query result
		virtual bool setRetrieveColumnBaseTableName(const bool value) = 0; // Set whether base table name should be retrieved for column information query result
		virtual bool setRetrieveColumnCaseSensitive(const bool value) = 0; // Set whether case sensitivity information should be retrieved for column information query result
		virtual bool setRetrieveColumnCatalogName(const bool value) = 0; // Set whether catalog name should be retrieved for column information query result
		virtual bool setRetrieveColumnConciseType(const bool value) = 0; // Set whether concise type should be retrieved for column information query result
		virtual bool setRetrieveColumnMaximumDisplayLength(const bool value) = 0; // Set whether maximum display length should be retrieved for column information query result
		virtual bool setRetrieveColumnFixedPrecisionScale(const bool value) = 0; // Set whether fixed precision scale should be retrieved for column information query result
		virtual bool setRetrieveColumnLabel(const bool value) = 0; // Set whether label should be retrieved for column information query result
		virtual bool setRetrieveColumnMaximumLength(const bool value) = 0; // Set whether maximum length should be retrieved for column information query result
		virtual bool setRetrieveColumnLiteralPrefix(const bool value) = 0; // Set whether literal prefix should be retrieved for column information query result
		virtual bool setRetrieveColumnLiteralSuffix(const bool value) = 0; // Set whether literal suffix should be retrieved for column information query result
		virtual bool setRetrieveColumnLocalTypeName(const bool value) = 0; // Set whether local type name should be retrieved for column information query result
		virtual bool setRetrieveColumnAlias(const bool value) = 0; // Set whether alias should be retrieved for column information query result
		virtual bool setRetrieveColumnNullability(const bool value) = 0; // Set whether nullability information should be retrieved for column information query result
		virtual bool setRetrieveColumnPrecisionRadix(const bool value) = 0; // Set whether precision radix should be retrieved for column information query result
		virtual bool setRetrieveColumnPrecision(const bool value) = 0; // Set whether precision should be retrieved for column information query result
		virtual bool setRetrieveColumnScale(const bool value) = 0; // Set whether scale should be retrieved for column information query result
		virtual bool setRetrieveColumnSchemaName(const bool value) = 0; // Set whether schema name should be retrieved for column information query result
		virtual bool setRetrieveColumnSearchable(const bool value) = 0; // Set whether searchability should be retrieved for column information query result
		virtual bool setRetrieveColumnTableName(const bool value) = 0; // Set whether table name should be retrieved for column information query result
		virtual bool setRetrieveColumnDataTypeName(const bool value) = 0; // Set whether data type name should be retrieved for column information query result
		virtual bool setRetrieveColumnUnnamed(const bool value) = 0; // Set whether unnamed indicator should be retrieved for column information query result
		virtual bool setRetrieveColumnUpdatable(const bool value) = 0; // Set whether updatable indicator should be retrieved for column information query result
		virtual bool setRetrieveColumnAllAttributes(const bool value) = 0; // Set whether all column attributes should be retrieved for query result

		// Set options
		virtual bool setAsyncEnabled(const bool value) = 0;
		virtual bool setCursorConcurrency(const DbCursorConcurrency value) = 0;
		virtual bool setCursorScrollable(const bool value) = 0;
		virtual bool setCursorSensitivity(const DbCursorSensitivity value) = 0;
		virtual bool setCursorType(const DbCursorType value) = 0;
		virtual bool setAutoIPDEnabled(const bool value) = 0;
		virtual bool setStringArgumentsOfCatalogFunctionsTreatedAsIdentifiers(const bool value) = 0;
		virtual bool setScanEscapeSequences(const bool value) = 0;
		virtual bool setQueryTimeout(const int value) = 0;
		virtual bool setBookmarksEnabled(const bool value) = 0;

		virtual bool Prepare(const String &query) = 0; // Prepare specified query
		virtual DbResult Execute() = 0; // Execute prepared query
		virtual DbResult Execute(const DbRow &row, const bool validate = false) = 0; // Execute prepared query with one row of arguments
		virtual DbResult Execute(const DbRows &rows, const bool validate = false) = 0; // Execute prepared query with multiple rows
		virtual DbResult Execute(const String &query) = 0; // Execute query directly
		virtual DbResult Execute(const String &query, const DbRow &row, const bool validate = false) = 0; // Execute query directly with one row of arguments
		virtual DbResult Execute(const String &query, const DbRows &rows, const bool validate = false) = 0; // Execute query directly with multiple rows

		// Query objects. There can be search patterns("_" - single character, "%" - any sequence of zero or more characters) in "catalog", "table", "procedure", "schema" and "column" arguments
		virtual DbResult QueryAllCatalogs() = 0; // Query all catalogs/databases
		virtual DbResult QueryAllTableTypes() = 0; // Query all supported table types
		virtual DbResult QueryAllSchemes() = 0; // Query all data source schemes
		virtual DbResult QueryTables(const String &catalog, const String &table, const String &schema, const StringArray &types) = 0; // Query catalog/database table list of specified types with filtering
		virtual DbResult QueryTablePrivileges(const String &catalog, const String &table, const String &schema) = 0; // Query table privileges
		virtual DbResult QueryColumns(const String &catalog, const String &table, const String &schema, const String &column) = 0; // Query columns
		virtual DbResult QueryColumnPrivileges(const String &catalog, const String &table, const String &schema, const String &column) = 0; // Query column privileges
		virtual DbResult QuerySpecialColumns(const String &catalog, const String &table, const String &schema, const bool autoupdated, const DbSpecialColumnScope scope, const bool nullable) = 0; // Query special columns
		virtual DbResult QueryProcedureColumns(const String &catalog, const String &procedure, const String &schema, const String &column) = 0; // Query procedure columns
		virtual DbResult QueryForeignKeys(const String &pk_catalog, const String &pk_table, const String &pk_schema, const String &fk_catalog, const String &fk_table, const String &fk_schema) = 0; // Query foreign key list
		virtual DbResult QueryPrimaryKeys(const String &catalog, const String &table, const String &schema) = 0; // Query primary key list
		virtual DbResult QueryProcedures(const String &catalog, const String &procedure, const String &schema) = 0; // Query procedure list
		virtual DbResult QueryStatistic(const String &catalog, const String &table, const String &schema, const bool unique_indexes_only, const bool quick_return) = 0; // Query table statistic
	};
}