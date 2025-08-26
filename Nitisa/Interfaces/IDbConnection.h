// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Db/DbAsyncMode.h"
#include "../Db/DbBatchRowCountSupport.h"
#include "../Db/DbBatchSupport.h"
#include "../Db/DbBookmarkPersistence.h"
#include "../Db/DbCatalogUsage.h"
#include "../Db/DbCaseSensitivity.h"
#include "../Db/DbConcatenateNullBehaviour.h"
#include "../Db/DbConvertTo.h"
#include "../Db/DbCursorAttributes.h"
#include "../Db/DbCursorBehaviour.h"
#include "../Db/DbCursorSensitivity.h"
#include "../Db/DbFileUsage.h"
#include "../Db/DbGroupByRelation.h"
#include "../Db/DbNullCollation.h"
#include "../Db/DbOdbcInterfaceConformance.h"
#include "../Db/DbSqlConformance.h"
#include "../Db/DbStandardCliConformance.h"
#include "../Db/DbSupportedAggregateFunctions.h"
#include "../Db/DbSupportedAlterDomainClauses.h"
#include "../Db/DbSupportedAlterTableClauses.h"
#include "../Db/DbSupportedAvailabilityOfResultSetsInParameterizedExecution.h"
#include "../Db/DbSupportedConvertFunctions.h"
#include "../Db/DbSupportedCreateAssertionClauses.h"
#include "../Db/DbSupportedCreateCharacterSetClauses.h"
#include "../Db/DbSupportedCreateDomainClauses.h"
#include "../Db/DbSupportedCreateIndexKeywords.h"
#include "../Db/DbSupportedCreateSchemaClauses.h"
#include "../Db/DbSupportedCreateTableClauses.h"
#include "../Db/DbSupportedCreateViewClauses.h"
#include "../Db/DbSupportedDateTimeFunctions.h"
#include "../Db/DbSupportedDateTimeLiterals.h"
#include "../Db/DbSupportedDropClauses.h"
#include "../Db/DbSupportedForeignKeyRules.h"
#include "../Db/DbSupportedGetDataExtensions.h"
#include "../Db/DbSupportedGrantClauses.h"
#include "../Db/DbSupportedDateTimeIntervals.h"
#include "../Db/DbSupportedIndexClauses.h"
#include "../Db/DbSupportedInformationSchemaViews.h"
#include "../Db/DbSupportedInsertStatements.h"
#include "../Db/DbSupportedOuterJoins.h"
#include "../Db/DbSupportedPositionOperations.h"
#include "../Db/DbSupportedPredicates.h"
#include "../Db/DbSupportedRelationJoinOperators.h"
#include "../Db/DbSupportedRevokeClauses.h"
#include "../Db/DbSupportedRowValueConstructors.h"
#include "../Db/DbSupportedNumericFunctions.h"
#include "../Db/DbSupportedNumericValueFunctions.h"
#include "../Db/DbSupportedScalarStringFunctions.h"
#include "../Db/DbSupportedSchemaUsages.h"
#include "../Db/DbSupportedScrollOptions.h"
#include "../Db/DbSupportedStringFunctions.h"
#include "../Db/DbSupportedSubQueryPredicates.h"
#include "../Db/DbSupportedSystemFunctions.h"
#include "../Db/DbSupportedTimeDateFunctions.h"
#include "../Db/DbSupportedTransactionIsolationLevels.h"
#include "../Db/DbSupportedUnionClauses.h"
#include "../Db/DbSupportedValueExpressions.h"
#include "../Db/DbTableCorrelationName.h"
#include "../Db/DbTransactionSupport.h"
#include "../Core/Aliases.h"
#include "../Core/Strings.h"
#include "IReleasable.h"

namespace nitisa
{
	class IDb;
	class IDbStatement;
	class IErrorListener;
	class IWindow;

	class IDbConnection :public virtual IReleasable
	{
	protected:
		IDbConnection() = default;
		~IDbConnection() = default;
		IDbConnection(const IDbConnection &other) = delete;
		IDbConnection(IDbConnection &&other) = delete;
		IDbConnection &operator=(const IDbConnection &other) = delete;
		IDbConnection &operator=(IDbConnection &&other) = delete;
	protected:
		PlatformHandle m_hHandle;
		IDb *m_pDb;
		String m_sConnectionOptions;
		String m_sConnectionString;
		IErrorListener *m_pErrorListener;
		bool m_bAssignErrorListener;
	public:
		PlatformHandle const &Handle{ m_hHandle }; // Platform-dependent connection handle
		IDb* const &Db{ m_pDb }; // Parent database manager
		String const &ConnectionOptions{ m_sConnectionOptions }; // Connection options supplied during connection
		String const &ConnectionString{ m_sConnectionString }; // Connection string (might be equal to connection options or be a modified variant of connection options)
		IErrorListener* const &ErrorListener{ m_pErrorListener }; // Error listener
		bool const &AssignErrorListener{ m_bAssignErrorListener }; // Whether error listener should be also automatically assigned to created statements

		virtual bool isConnected(bool *succeeded = nullptr) = 0; // Check whether connection is alive
		virtual bool isReadOnly(bool *succeeded = nullptr) = 0; // Return whether connection is read-only one
		virtual bool isAutoCommit(bool *succeeded = nullptr) = 0; // Return whether auto commit is active
		virtual bool isTrace(bool *succeeded = nullptr) = 0; // Return whether tracing is active
		virtual String getTraceFilename(bool *succeeded = nullptr) = 0; // Return trace file name
		virtual int getConnectionTimeout(bool *succeeded = nullptr) = 0; // Return connection timeout
		virtual int getLoginTimeout(bool *succeeded = nullptr) = 0; // Return login timeout
		virtual DbSupportedTransactionIsolationLevels getTransactionIsolationLevels(bool *succeeded = nullptr) = 0; // Return transaction isolation levels
		virtual IWindow *getWindow() = 0; // Return window to be used in confirmations as parent one
		virtual int getStatementCount() = 0; // Return number of created and not yet released statement
		virtual IDbStatement *getStatement(const int index) = 0; // Return statement by index
		
		// Return features availability and their options
		virtual bool isAllProceduresAccessible(bool *succeeded = nullptr) = 0;
		virtual bool isAllTablesAccessible(bool *succeeded = nullptr) = 0;
		virtual int getMaximumActiveEnvironmentCount(bool *succeeded = nullptr) = 0;
		virtual DbSupportedAggregateFunctions getSupportedAggregateFunctions(bool *succeeded = nullptr) = 0;
		virtual DbSupportedAlterDomainClauses getSupportedAlterDomainClauses(bool *succeeded = nullptr) = 0;
		virtual DbSupportedAlterTableClauses getSupportedAlterTableClauses(bool *succeeded = nullptr) = 0;
		virtual bool isAsyncFunctionsSupported(bool *succeeded = nullptr) = 0;
		virtual DbAsyncMode getAsyncMode(bool *succeeded = nullptr) = 0;
		virtual bool isAsyncNotificationsSupported(bool *succeeded = nullptr) = 0;
		virtual DbBatchRowCountSupport getBatchRowCountSupport(bool *succeeded = nullptr) = 0;
		virtual DbBatchSupport getBatchSupport(bool *succeeded = nullptr) = 0;
		virtual DbBookmarkPersistence getBookmarkPersistence(bool *succeeded = nullptr) = 0;
		virtual bool isCatalogLocationAtStart(bool *succeeded = nullptr) = 0;
		virtual bool isCatalogNamesSupported(bool *succeeded = nullptr) = 0;
		virtual String getCatalogNameSeparator(bool *succeeded = nullptr) = 0;
		virtual String getCatalogVendorName(bool *succeeded = nullptr) = 0;
		virtual DbCatalogUsage getCatalogUsage(bool *succeeded = nullptr) = 0;
		virtual String getCollationSequence(bool *succeeded = nullptr) = 0;
		virtual bool isColumnAliasSupported(bool *succeeded = nullptr) = 0;
		virtual DbConcatenateNullBehaviour getConcatenameNullBehaviour(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getBigIntConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getBinaryConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getBitConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getCharConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getGuidConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getDateConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getDecimalConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getDoubleConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getFloatConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getIntegerConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getIntervalYearMonthConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getIntervalDayTimeConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getLongVarBinaryConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getLongVarCharConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getNumericConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getRealConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getSmallIntConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getTimeConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getTimestampConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getTinyIntConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getVarBinaryConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbConvertTo getVarCharConvertTo(bool *succeeded = nullptr) = 0;
		virtual DbSupportedConvertFunctions getSupportedConvertFunctions(bool *succeeded = nullptr) = 0;
		virtual DbTableCorrelationName getTableCorrelationName(bool *succeeded = nullptr) = 0;
		virtual DbSupportedCreateAssertionClauses getSupportedCreateAssertionClauses(bool *succeeded = nullptr) = 0;
		virtual DbSupportedCreateCharacterSetClauses getSupportedCreateCharacterSetClauses(bool *succeeded = nullptr) = 0;
		virtual bool isCreateCollationSupported(bool *succeeded = nullptr) = 0;
		virtual DbSupportedCreateDomainClauses getSupportedCreateDomainClauses(bool *succeeded = nullptr) = 0;
		virtual DbSupportedCreateSchemaClauses getSupportedCreateSchemaClauses(bool *succeeded = nullptr) = 0;
		virtual DbSupportedCreateTableClauses getSupportedCreateTableClauses(bool *succeeded = nullptr) = 0;
		virtual bool isCreateTranslationSupported(bool *succeeded = nullptr) = 0;
		virtual DbSupportedCreateViewClauses getSupportedCreateViewClauses(bool *succeeded = nullptr) = 0;
		virtual DbCursorBehaviour getCursorCommitBehaviour(bool *succeeded = nullptr) = 0;
		virtual DbCursorBehaviour getCursorRollbackBehaviour(bool *succeeded = nullptr) = 0;
		virtual DbCursorSensitivity getCursorSensitivity(bool *succeeded = nullptr) = 0;
		virtual String getDataSourceName(bool *succeeded = nullptr) = 0;
		virtual bool isDataSourceReadOnly(bool *succeeded = nullptr) = 0;
		virtual String getDatabaseName(bool *succeeded = nullptr) = 0;
		virtual DbSupportedDateTimeLiterals getSupportedDateTimeLiterals(bool *succeeded = nullptr) = 0;
		virtual String getDBMSName(bool *succeeded = nullptr) = 0;
		virtual String getDBMSVersion(bool *succeeded = nullptr) = 0;
		virtual DbSupportedIndexClauses getSupportedIndexClauses(bool *succeeded = nullptr) = 0;
		virtual DbSupportedTransactionIsolationLevels getDefaultTransactionIsolationLevels(bool *succeeded = nullptr) = 0;
		virtual bool isDescribeParameterSupported(bool *succeeded = nullptr) = 0;
		virtual String getDriverManagerVersion(bool *succeeded = nullptr) = 0;
		virtual bool isDriverAwarePoolingSupported(bool *succeeded = nullptr) = 0;
		virtual String getDriverName(bool *succeeded = nullptr) = 0;
		virtual String getDriverOdbcVersion(bool *succeeded = nullptr) = 0;
		virtual String getDriverVersion(bool *succeeded = nullptr) = 0;
		virtual bool isDropAssertionSupported(bool *succeeded = nullptr) = 0;
		virtual bool isDropCharacterSetSupported(bool *succeeded = nullptr) = 0;
		virtual bool isDropCollationSupported(bool *succeeded = nullptr) = 0;
		virtual DbSupportedDropClauses getSupportedDropDomainClauses(bool *succeeded = nullptr) = 0;
		virtual DbSupportedDropClauses getSupportedDropSchemaClauses(bool *succeeded = nullptr) = 0;
		virtual DbSupportedDropClauses getSupportedDropTableClauses(bool *succeeded = nullptr) = 0;
		virtual bool isDropTranslationSupported(bool *succeeded = nullptr) = 0;
		virtual DbSupportedDropClauses getSupportedDropViewClauses(bool *succeeded = nullptr) = 0;
		virtual DbCursorAttributes getDynamicCursorAttributes(bool *succeeded = nullptr) = 0;
		virtual bool isExpressionsInOrderBySupported(bool *succeeded = nullptr) = 0;
		virtual DbFileUsage getFileUsage(bool *succeeded = nullptr) = 0;
		virtual DbCursorAttributes getForwardOnlyCursorAttributes(bool *succeeded = nullptr) = 0;
		virtual DbSupportedGetDataExtensions getSupportedGetDataExtensions(bool *succeeded = nullptr) = 0;
		virtual DbGroupByRelation getGroupByRelation(bool *succeeded = nullptr) = 0;
		virtual DbCaseSensitivity getIdentifierCaseSensitivity(bool *succeeded = nullptr) = 0;
		virtual String getQuotedIdentifierDelimiter(bool *succeeded = nullptr) = 0;
		virtual DbSupportedCreateIndexKeywords getSupportedCreateIndexKeywords(bool *succeeded = nullptr) = 0;
		virtual DbSupportedInformationSchemaViews getSupportedInformationSchemaViews(bool *succeeded = nullptr) = 0;
		virtual DbSupportedInsertStatements getSupportedInsertStatements(bool *succeeded = nullptr) = 0;
		virtual bool isIntegritySupported(bool *succeeded = nullptr) = 0;
		virtual DbCursorAttributes getKeysetCursorAttributes(bool *succeeded = nullptr) = 0;
		virtual String getSupportedKeywords(bool *succeeded = nullptr) = 0;
		virtual bool isLikeEscapeSupported(bool *succeeded = nullptr) = 0;
		virtual int getMaximumAsyncronousConcurrentStatementCount(bool *succeeded = nullptr) = 0;
		virtual int getMaximumBinaryLiteralLength(bool *succeeded = nullptr) = 0;
		virtual int getMaximumCatalogNameLength(bool *succeeded = nullptr) = 0;
		virtual int getMaximumCharacterLiteralLength(bool *succeeded = nullptr) = 0;
		virtual int getMaximumColumnNameLength(bool *succeeded = nullptr) = 0;
		virtual int getMaximumColumnsInGroupBy(bool *succeeded = nullptr) = 0;
		virtual int getMaximumColumnsInIndex(bool *succeeded = nullptr) = 0;
		virtual int getMaximumColumnsInOrderBy(bool *succeeded = nullptr) = 0;
		virtual int getMaximumColumnsInSelect(bool *succeeded = nullptr) = 0;
		virtual int getMaximumColumnsInTable(bool *succeeded = nullptr) = 0;
		virtual int getMaximumConcurrentActivityCount(bool *succeeded = nullptr) = 0;
		virtual int getMaximumCursorNameLength(bool *succeeded = nullptr) = 0;
		virtual int getMaximumDriverConnectionCount(bool *succeeded = nullptr) = 0;
		virtual int getMaximumIdentifierLength(bool *succeeded = nullptr) = 0;
		virtual int getMaximumIndexSize(bool *succeeded = nullptr) = 0;
		virtual int getMaximumProcedureNameLength(bool *succeeded = nullptr) = 0;
		virtual int getMaximumRowSize(bool *succeeded = nullptr) = 0;
		virtual bool isMaximumRowSizeIncludesLong(bool *succeeded = nullptr) = 0;
		virtual int getMaximumSchemaNameLength(bool *succeeded = nullptr) = 0;
		virtual int getMaximumStatementLength(bool *succeeded = nullptr) = 0;
		virtual int getMaximumTableNameLength(bool *succeeded = nullptr) = 0;
		virtual int getMaximumTablesInSelect(bool *succeeded = nullptr) = 0;
		virtual int getMaximumUserNameLength(bool *succeeded = nullptr) = 0;
		virtual bool isMultipleResultSetsSupported(bool *succeeded = nullptr) = 0;
		virtual bool isMultipleActiveTransactionsSupported(bool *succeeded = nullptr) = 0;
		virtual bool isDataSourceNeedLengthOfLongDataValue(bool *succeeded = nullptr) = 0;
		virtual bool isNonNullableColumnsSupported(bool *succeeded = nullptr) = 0;
		virtual DbNullCollation getNullCollation(bool *succeeded = nullptr) = 0;
		virtual DbSupportedNumericFunctions getSupportedNumericFunctions(bool *succeeded = nullptr) = 0;
		virtual DbOdbcInterfaceConformance getOdbcInterfaceConformance(bool *succeeded = nullptr) = 0;
		virtual String getOdbcVersion(bool *succeeded = nullptr) = 0;
		virtual DbSupportedOuterJoins getSupportedOuterJoins(bool *succeeded = nullptr) = 0;
		virtual bool isOrderByColumnsMustBeInSelect(bool *succeeded = nullptr) = 0;
		virtual bool isIndividualRowCountsAvailableInParametrizedExecution(bool *succeeded = nullptr) = 0;
		virtual DbSupportedAvailabilityOfResultSetsInParameterizedExecution getSupportedAvailabilityOfResultSetsInParameterizedExecution(bool *succeeded = nullptr) = 0;
		virtual DbSupportedPositionOperations getSupportedPositionOperations(bool *succeeded = nullptr) = 0;
		virtual String getProcedureVendorName(bool *succeeded = nullptr) = 0;
		virtual bool isProceduresSupported(bool *succeeded = nullptr) = 0;
		virtual DbCaseSensitivity getQuotedIdentifierCaseSensitivity(bool *succeeded = nullptr) = 0;
		virtual bool isRowUpdatesMaintainRowVersions(bool *succeeded = nullptr) = 0;
		virtual String getSchemaVendorName(bool *succeeded = nullptr) = 0;
		virtual DbSupportedSchemaUsages getSupportedSchemaUsages(bool *succeeded = nullptr) = 0;
		virtual DbSupportedScrollOptions getSupportedScrollOptions(bool *succeeded = nullptr) = 0;
		virtual String getSearchPatternEscape(bool *succeeded = nullptr) = 0;
		virtual String getServerName(bool *succeeded = nullptr) = 0;
		virtual String getSpecialCharacters(bool *succeeded = nullptr) = 0;
		virtual DbSqlConformance getSqlConformance(bool *succeeded = nullptr) = 0;
		virtual DbSupportedDateTimeFunctions getSupportedDateTimeFunctions(bool *succeeded = nullptr) = 0;
		virtual DbSupportedForeignKeyRules getSupportedForeignKeyDeleteRules(bool *succeeded = nullptr) = 0;
		virtual DbSupportedForeignKeyRules getSupportedForeignKeyUpdateRules(bool *succeeded = nullptr) = 0;
		virtual DbSupportedGrantClauses getSupportedGrantClauses(bool *succeeded = nullptr) = 0;
		virtual DbSupportedNumericValueFunctions getSupportedNumericValueFunctions(bool *succeeded = nullptr) = 0;
		virtual DbSupportedPredicates getSupportedPredicates(bool *succeeded = nullptr) = 0;
		virtual DbSupportedRelationJoinOperators getSupportedRelationJoinOperators(bool *succeeded = nullptr) = 0;
		virtual DbSupportedRevokeClauses getSupportedRevokeClauses(bool *succeeded = nullptr) = 0;
		virtual DbSupportedRowValueConstructors getSupportedRowValueConstructors(bool *succeeded = nullptr) = 0;
		virtual DbSupportedStringFunctions getSupportedStringFunctions(bool *succeeded = nullptr) = 0;
		virtual DbSupportedValueExpressions getSupportedValueExpressions(bool *succeeded = nullptr) = 0;
		virtual DbStandardCliConformance getStandardCliConformance(bool *succeeded = nullptr) = 0;
		virtual DbCursorAttributes getStaticCursorAttributes(bool *succeeded = nullptr) = 0;
		virtual DbSupportedScalarStringFunctions getSupportedScalarStringFunctions(bool *succeeded = nullptr) = 0;
		virtual DbSupportedSubQueryPredicates getSupportedSubQueryPredicates(bool *succeeded = nullptr) = 0;
		virtual DbSupportedSystemFunctions getSupportedSystemFunctions(bool *succeeded = nullptr) = 0;
		virtual String getTableVendorName(bool *succeeded = nullptr) = 0;
		virtual DbSupportedDateTimeIntervals getSupportedDateTimeAddIntervals(bool *succeeded = nullptr) = 0;
		virtual DbSupportedDateTimeIntervals getSupportedDateTimeDiffIntervals(bool *succeeded = nullptr) = 0;
		virtual DbSupportedTimeDateFunctions getSupportedTimeDateFunctions(bool *succeeded = nullptr) = 0;
		virtual DbTransactionSupport getTransactionSupport(bool *succeeded = nullptr) = 0;
		virtual DbSupportedTransactionIsolationLevels getSupportedTransactionIsolationLevels(bool *succeeded = nullptr) = 0;
		virtual DbSupportedUnionClauses getSupportedUnionClauses(bool *succeeded = nullptr) = 0;
		virtual String getUserName(bool *succeeded = nullptr) = 0;
		virtual String getOpenGroupSpecificationPublicationYear(bool *succeeded = nullptr) = 0;

		virtual void setErrorListener(IErrorListener *value) = 0; // Assign new error listener. nullptr value if also accepted
		virtual bool setAssignErrorListener(const bool value) = 0; // Set whether error listener should or should not be also automatically assigned to all new statements
		virtual bool setReadOnlyMode(const bool value) = 0; // Set read-only mode
		virtual bool setAutoCommit(const bool value) = 0; // Enable or disable auto-commit
		virtual bool setTrace(const bool value) = 0; // Enable or disable tracing
		virtual bool setTraceFilename(const String &value) = 0; // Set trace file name
		virtual bool setConnectionTimeout(const int value) = 0; // Set connection timeout
		virtual bool setLoginTimeout(const int value) = 0; // Set login timeout
		virtual bool setTransactionIsolationLevels(const DbSupportedTransactionIsolationLevels value) = 0; // Set transaction isolation levels
		virtual bool setWindow(IWindow *value) = 0; // Set window to be used in confirmations as parent one

		virtual IDbStatement *CreateStatement() = 0; // Create new statement
	};
}