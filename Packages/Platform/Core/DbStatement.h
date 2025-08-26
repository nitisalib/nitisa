// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Db/DbColumns.h"
#include "Nitisa/Db/DbCursorConcurrency.h"
#include "Nitisa/Db/DbCursorSensitivity.h"
#include "Nitisa/Db/DbCursorType.h"
#include "Nitisa/Db/DbResult.h"
#include "Nitisa/Db/DbRow.h"
#include "Nitisa/Db/DbRows.h"
#include "Nitisa/Db/DbSpecialColumnScope.h"
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/ErrorInfo.h"
#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IDbStatement.h"

namespace nitisa
{
	class IErrorListener;

	namespace platform
	{
		class CDbConnection;

		class CDbStatement :public virtual IDbStatement, public CReleasable
		{
		private:
			static const size_t BATCH_SIZE{ 255 };

			void HandleError(const AnsiString &funcA, const AnsiString &funcB, const int line, const ErrorInfo &error, const short result, const bool has_no_data, const String &attribute, const bool has_busy);
			bool Validate(const DbRow &row);
			bool Validate(const DbRows &rows);
			DbResult CreateResult();
			bool Exec(const DbRow &row, const String &query);

			bool RetrieveColumnAutoIncrementing(const unsigned short index, bool &attribute);
			bool RetrieveColumnName(const unsigned short index, String &attribute);
			bool RetrieveColumnBaseTableName(const unsigned short index, String &attribute);
			bool RetrieveColumnCaseSensitive(const unsigned short index, bool &attribute);
			bool RetrieveColumnCatalogName(const unsigned short index, String &attribute);
			bool RetrieveColumnConciseType(const unsigned short index, DbDataType &attribute);
			bool RetrieveColumnMaximumDisplayLength(const unsigned short index, int64 &attribute);
			bool RetrieveColumnFixedPrecisionScale(const unsigned short index, bool &attribute);
			bool RetrieveColumnLabel(const unsigned short index, String &attribute);
			bool RetrieveColumnMaximumLength(const unsigned short index, int64 &attribute);
			bool RetrieveColumnLiteralPrefix(const unsigned short index, String &attribute);
			bool RetrieveColumnLiteralSuffix(const unsigned short index, String &attribute);
			bool RetrieveColumnLocalTypeName(const unsigned short index, String &attribute);
			bool RetrieveColumnAlias(const unsigned short index, String &attribute);
			bool RetrieveColumnNullability(const unsigned short index, DbNullabilityType &attribute);
			bool RetrieveColumnPrecisionRadix(const unsigned short index, int &attribute);
			bool RetrieveColumnOctetLength(const unsigned short index, int64 &attribute);
			bool RetrieveColumnPrecision(const unsigned short index, int &attribute);
			bool RetrieveColumnScale(const unsigned short index, int &attribute);
			bool RetrieveColumnSchemaName(const unsigned short index, String &attribute);
			bool RetrieveColumnSearchable(const unsigned short index, DbSearchableType &attribute);
			bool RetrieveColumnTableName(const unsigned short index, String &attribute);
			bool RetrieveColumnDataType(const unsigned short index, DbDataType &attribute);
			bool RetrieveColumnDataTypeName(const unsigned short index, String &attribute);
			bool RetrieveColumnUnnamed(const unsigned short index, bool &attribute);
			bool RetrieveColumnUnsigned(const unsigned short index, bool &attribute);
			bool RetrieveColumnUpdatable(const unsigned short index, DbUpdatableType &attribute);
			bool RetrieveColumnAttributes(DbColumns &columns);
		protected:
			void BeforeRelease() override;
		public:
			// IDbStatement getters
			bool isAsyncEnabled(bool *succeeded = nullptr) override;
			DbCursorConcurrency getCursorConcurrency(bool *succeeded = nullptr) override;
			bool isCursorScrollable(bool *succeeded = nullptr) override;
			DbCursorSensitivity getCursorSensitivity(bool *succeeded = nullptr) override;
			DbCursorType getCursorType(bool *succeeded = nullptr) override;
			bool isAutoIPDEnabled(bool *succeeded = nullptr) override;
			bool isStringArgumentsOfCatalogFunctionsTreatedAsIdentifiers(bool *succeeded = nullptr) override;
			bool isScanEscapeSequences(bool *succeeded = nullptr) override;
			int getQueryTimeout(bool *succeeded = nullptr) override;
			bool isBookmarksEnabled(bool *succeeded = nullptr) override;

			// IDbStatement setters
			void setErrorListener(IErrorListener *value) override;
			bool setAsyncEnabled(const bool value) override;
			bool setCursorConcurrency(const DbCursorConcurrency value) override;
			bool setCursorScrollable(const bool value) override;
			bool setCursorSensitivity(const DbCursorSensitivity value) override;
			bool setCursorType(const DbCursorType value) override;
			bool setAutoIPDEnabled(const bool value) override;
			bool setStringArgumentsOfCatalogFunctionsTreatedAsIdentifiers(const bool value) override;
			bool setScanEscapeSequences(const bool value) override;
			bool setQueryTimeout(const int value) override;
			bool setBookmarksEnabled(const bool value) override;
			bool setRetrieveColumnAutoIncrementing(const bool value) override;
			bool setRetrieveColumnName(const bool value) override;
			bool setRetrieveColumnBaseTableName(const bool value) override;
			bool setRetrieveColumnCaseSensitive(const bool value) override;
			bool setRetrieveColumnCatalogName(const bool value) override;
			bool setRetrieveColumnConciseType(const bool value) override;
			bool setRetrieveColumnMaximumDisplayLength(const bool value) override;
			bool setRetrieveColumnFixedPrecisionScale(const bool value) override;
			bool setRetrieveColumnLabel(const bool value) override;
			bool setRetrieveColumnMaximumLength(const bool value) override;
			bool setRetrieveColumnLiteralPrefix(const bool value) override;
			bool setRetrieveColumnLiteralSuffix(const bool value) override;
			bool setRetrieveColumnLocalTypeName(const bool value) override;
			bool setRetrieveColumnAlias(const bool value) override;
			bool setRetrieveColumnNullability(const bool value) override;
			bool setRetrieveColumnPrecisionRadix(const bool value) override;
			bool setRetrieveColumnPrecision(const bool value) override;
			bool setRetrieveColumnScale(const bool value) override;
			bool setRetrieveColumnSchemaName(const bool value) override;
			bool setRetrieveColumnSearchable(const bool value) override;
			bool setRetrieveColumnTableName(const bool value) override;
			bool setRetrieveColumnDataTypeName(const bool value) override;
			bool setRetrieveColumnUnnamed(const bool value) override;
			bool setRetrieveColumnUpdatable(const bool value) override;
			bool setRetrieveColumnAllAttributes(const bool value) override;

			// IDbStatement queries
			bool Prepare(const String &query) override;
			DbResult Execute() override;
			DbResult Execute(const DbRow &row, const bool validate = false) override;
			DbResult Execute(const DbRows &rows, const bool validate = false) override;
			DbResult Execute(const String &query) override;
			DbResult Execute(const String &query, const DbRow &row, const bool validate = false) override;
			DbResult Execute(const String &query, const DbRows &rows, const bool validate = false) override;

			// IDbStatement query objects
			DbResult QueryAllCatalogs() override;
			DbResult QueryAllTableTypes() override;
			DbResult QueryAllSchemes() override;
			DbResult QueryTables(const String &catalog, const String &table, const String &schema, const StringArray &types) override;
			DbResult QueryTablePrivileges(const String &catalog, const String &table, const String &schema) override;
			DbResult QueryColumns(const String &catalog, const String &table, const String &schema, const String &column) override;
			DbResult QueryColumnPrivileges(const String &catalog, const String &table, const String &schema, const String &column) override;
			DbResult QuerySpecialColumns(const String &catalog, const String &table, const String &schema, const bool autoupdated, const DbSpecialColumnScope scope, const bool nullable) override;
			DbResult QueryProcedureColumns(const String &catalog, const String &procedure, const String &schema, const String &column) override;
			DbResult QueryForeignKeys(const String &pk_catalog, const String &pk_table, const String &pk_schema, const String &fk_catalog, const String &fk_table, const String &fk_schema) override;
			DbResult QueryPrimaryKeys(const String &catalog, const String &table, const String &schema) override;
			DbResult QueryProcedures(const String &catalog, const String &procedure, const String &schema) override;
			DbResult QueryStatistic(const String &catalog, const String &table, const String &schema, const bool unique_indexes_only, const bool quick_return) override;

			CDbStatement(PlatformHandle handle, CDbConnection *connection);
		};
	}
}