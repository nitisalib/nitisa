// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Db/DbAsyncMode.h"
#include "Nitisa/Db/DbBatchRowCountSupport.h"
#include "Nitisa/Db/DbBatchSupport.h"
#include "Nitisa/Db/DbBookmarkPersistence.h"
#include "Nitisa/Db/DbCatalogUsage.h"
#include "Nitisa/Db/DbCaseSensitivity.h"
#include "Nitisa/Db/DbConcatenateNullBehaviour.h"
#include "Nitisa/Db/DbConvertTo.h"
#include "Nitisa/Db/DbCursorAttributes.h"
#include "Nitisa/Db/DbCursorBehaviour.h"
#include "Nitisa/Db/DbCursorSensitivity.h"
#include "Nitisa/Db/DbFileUsage.h"
#include "Nitisa/Db/DbGroupByRelation.h"
#include "Nitisa/Db/DbNullCollation.h"
#include "Nitisa/Db/DbOdbcInterfaceConformance.h"
#include "Nitisa/Db/DbSqlConformance.h"
#include "Nitisa/Db/DbStandardCliConformance.h"
#include "Nitisa/Db/DbSupportedAggregateFunctions.h"
#include "Nitisa/Db/DbSupportedAlterDomainClauses.h"
#include "Nitisa/Db/DbSupportedAlterTableClauses.h"
#include "Nitisa/Db/DbSupportedAvailabilityOfResultSetsInParameterizedExecution.h"
#include "Nitisa/Db/DbSupportedConvertFunctions.h"
#include "Nitisa/Db/DbSupportedCreateAssertionClauses.h"
#include "Nitisa/Db/DbSupportedCreateCharacterSetClauses.h"
#include "Nitisa/Db/DbSupportedCreateDomainClauses.h"
#include "Nitisa/Db/DbSupportedCreateIndexKeywords.h"
#include "Nitisa/Db/DbSupportedCreateSchemaClauses.h"
#include "Nitisa/Db/DbSupportedCreateTableClauses.h"
#include "Nitisa/Db/DbSupportedCreateViewClauses.h"
#include "Nitisa/Db/DbSupportedDateTimeFunctions.h"
#include "Nitisa/Db/DbSupportedDateTimeLiterals.h"
#include "Nitisa/Db/DbSupportedDropClauses.h"
#include "Nitisa/Db/DbSupportedForeignKeyRules.h"
#include "Nitisa/Db/DbSupportedGetDataExtensions.h"
#include "Nitisa/Db/DbSupportedGrantClauses.h"
#include "Nitisa/Db/DbSupportedDateTimeIntervals.h"
#include "Nitisa/Db/DbSupportedIndexClauses.h"
#include "Nitisa/Db/DbSupportedInformationSchemaViews.h"
#include "Nitisa/Db/DbSupportedInsertStatements.h"
#include "Nitisa/Db/DbSupportedOuterJoins.h"
#include "Nitisa/Db/DbSupportedPositionOperations.h"
#include "Nitisa/Db/DbSupportedPredicates.h"
#include "Nitisa/Db/DbSupportedRelationJoinOperators.h"
#include "Nitisa/Db/DbSupportedRevokeClauses.h"
#include "Nitisa/Db/DbSupportedRowValueConstructors.h"
#include "Nitisa/Db/DbSupportedNumericFunctions.h"
#include "Nitisa/Db/DbSupportedNumericValueFunctions.h"
#include "Nitisa/Db/DbSupportedScalarStringFunctions.h"
#include "Nitisa/Db/DbSupportedSchemaUsages.h"
#include "Nitisa/Db/DbSupportedScrollOptions.h"
#include "Nitisa/Db/DbSupportedStringFunctions.h"
#include "Nitisa/Db/DbSupportedSubQueryPredicates.h"
#include "Nitisa/Db/DbSupportedSystemFunctions.h"
#include "Nitisa/Db/DbSupportedTimeDateFunctions.h"
#include "Nitisa/Db/DbSupportedTransactionIsolationLevels.h"
#include "Nitisa/Db/DbSupportedUnionClauses.h"
#include "Nitisa/Db/DbSupportedValueExpressions.h"
#include "Nitisa/Db/DbTableCorrelationName.h"
#include "Nitisa/Db/DbTransactionSupport.h"
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IDbConnection.h"
#include "Nitisa/Interfaces/IReleasableListener.h"
#include <vector>

namespace nitisa
{
	class IDbStatement;
	class IWindow;

	namespace platform
	{
		class CDb;

		class CDbConnection :public virtual IDbConnection, public CReleasable
		{
		private:
			class CStatementReleaseListener :public virtual IReleasableListener
			{
			private:
				CDbConnection *m_pConnection;
			public:
				void NotifyOnRelease(IReleasable *sender) override;

				CStatementReleaseListener(CDbConnection *connection);
			};
		private:
			IWindow *m_pWindow;
			std::vector<IDbStatement*> m_aStatements;

			CStatementReleaseListener m_cStatementReleaseListener;

			void HandleError(const AnsiString &funcA, const AnsiString &funcB, const int line, const ErrorInfo &error, const short result, const bool has_no_data, const String &attribute, const bool has_busy);
		protected:
			void BeforeRelease() override;
		public:
			// IDbConnection getters
			bool isConnected(bool *succeeded = nullptr) override;
			bool isReadOnly(bool *succeeded = nullptr) override;
			bool isAutoCommit(bool *succeeded = nullptr) override;
			bool isTrace(bool *succeeded = nullptr) override;
			String getTraceFilename(bool *succeeded = nullptr) override;
			int getConnectionTimeout(bool *succeeded = nullptr) override;
			int getLoginTimeout(bool *succeeded = nullptr) override;
			DbSupportedTransactionIsolationLevels getTransactionIsolationLevels(bool *succeeded = nullptr) override;
			IWindow *getWindow() override;
			int getStatementCount() override;
			IDbStatement *getStatement(const int index) override;

			// IDbConnection capability getters
			bool isAllProceduresAccessible(bool *succeeded = nullptr) override;
			bool isAllTablesAccessible(bool *succeeded = nullptr) override;
			int getMaximumActiveEnvironmentCount(bool *succeeded = nullptr) override;
			DbSupportedAggregateFunctions getSupportedAggregateFunctions(bool *succeeded = nullptr) override;
			DbSupportedAlterDomainClauses getSupportedAlterDomainClauses(bool *succeeded = nullptr) override;
			DbSupportedAlterTableClauses getSupportedAlterTableClauses(bool *succeeded = nullptr) override;
			bool isAsyncFunctionsSupported(bool *succeeded = nullptr) override;
			DbAsyncMode getAsyncMode(bool *succeeded = nullptr) override;
			bool isAsyncNotificationsSupported(bool *succeeded = nullptr) override;
			DbBatchRowCountSupport getBatchRowCountSupport(bool *succeeded = nullptr) override;
			DbBatchSupport getBatchSupport(bool *succeeded = nullptr) override;
			DbBookmarkPersistence getBookmarkPersistence(bool *succeeded = nullptr) override;
			bool isCatalogLocationAtStart(bool *succeeded = nullptr) override;
			bool isCatalogNamesSupported(bool *succeeded = nullptr) override;
			String getCatalogNameSeparator(bool *succeeded = nullptr) override;
			String getCatalogVendorName(bool *succeeded = nullptr) override;
			DbCatalogUsage getCatalogUsage(bool *succeeded = nullptr) override;
			String getCollationSequence(bool *succeeded = nullptr) override;
			bool isColumnAliasSupported(bool *succeeded = nullptr) override;
			DbConcatenateNullBehaviour getConcatenameNullBehaviour(bool *succeeded = nullptr) override;
			DbConvertTo getBigIntConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getBinaryConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getBitConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getCharConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getGuidConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getDateConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getDecimalConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getDoubleConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getFloatConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getIntegerConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getIntervalYearMonthConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getIntervalDayTimeConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getLongVarBinaryConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getLongVarCharConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getNumericConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getRealConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getSmallIntConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getTimeConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getTimestampConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getTinyIntConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getVarBinaryConvertTo(bool *succeeded = nullptr) override;
			DbConvertTo getVarCharConvertTo(bool *succeeded = nullptr) override;
			DbSupportedConvertFunctions getSupportedConvertFunctions(bool *succeeded = nullptr) override;
			DbTableCorrelationName getTableCorrelationName(bool *succeeded = nullptr) override;
			DbSupportedCreateAssertionClauses getSupportedCreateAssertionClauses(bool *succeeded = nullptr) override;
			DbSupportedCreateCharacterSetClauses getSupportedCreateCharacterSetClauses(bool *succeeded = nullptr) override;
			bool isCreateCollationSupported(bool *succeeded = nullptr) override;
			DbSupportedCreateDomainClauses getSupportedCreateDomainClauses(bool *succeeded = nullptr) override;
			DbSupportedCreateSchemaClauses getSupportedCreateSchemaClauses(bool *succeeded = nullptr) override;
			DbSupportedCreateTableClauses getSupportedCreateTableClauses(bool *succeeded = nullptr) override;
			bool isCreateTranslationSupported(bool *succeeded = nullptr) override;
			DbSupportedCreateViewClauses getSupportedCreateViewClauses(bool *succeeded = nullptr) override;
			DbCursorBehaviour getCursorCommitBehaviour(bool *succeeded = nullptr) override;
			DbCursorBehaviour getCursorRollbackBehaviour(bool *succeeded = nullptr) override;
			DbCursorSensitivity getCursorSensitivity(bool *succeeded = nullptr) override;
			String getDataSourceName(bool *succeeded = nullptr) override;
			bool isDataSourceReadOnly(bool *succeeded = nullptr) override;
			String getDatabaseName(bool *succeeded = nullptr) override;
			DbSupportedDateTimeLiterals getSupportedDateTimeLiterals(bool *succeeded = nullptr) override;
			String getDBMSName(bool *succeeded = nullptr) override;
			String getDBMSVersion(bool *succeeded = nullptr) override;
			DbSupportedIndexClauses getSupportedIndexClauses(bool *succeeded = nullptr) override;
			DbSupportedTransactionIsolationLevels getDefaultTransactionIsolationLevels(bool *succeeded = nullptr) override;
			bool isDescribeParameterSupported(bool *succeeded = nullptr) override;
			String getDriverManagerVersion(bool *succeeded = nullptr) override;
			bool isDriverAwarePoolingSupported(bool *succeeded = nullptr) override;
			String getDriverName(bool *succeeded = nullptr) override;
			String getDriverOdbcVersion(bool *succeeded = nullptr) override;
			String getDriverVersion(bool *succeeded = nullptr) override;
			bool isDropAssertionSupported(bool *succeeded = nullptr) override;
			bool isDropCharacterSetSupported(bool *succeeded = nullptr) override;
			bool isDropCollationSupported(bool *succeeded = nullptr) override;
			DbSupportedDropClauses getSupportedDropDomainClauses(bool *succeeded = nullptr) override;
			DbSupportedDropClauses getSupportedDropSchemaClauses(bool *succeeded = nullptr) override;
			DbSupportedDropClauses getSupportedDropTableClauses(bool *succeeded = nullptr) override;
			bool isDropTranslationSupported(bool *succeeded = nullptr) override;
			DbSupportedDropClauses getSupportedDropViewClauses(bool *succeeded = nullptr) override;
			DbCursorAttributes getDynamicCursorAttributes(bool *succeeded = nullptr) override;
			bool isExpressionsInOrderBySupported(bool *succeeded = nullptr) override;
			DbFileUsage getFileUsage(bool *succeeded = nullptr) override;
			DbCursorAttributes getForwardOnlyCursorAttributes(bool *succeeded = nullptr) override;
			DbSupportedGetDataExtensions getSupportedGetDataExtensions(bool *succeeded = nullptr) override;
			DbGroupByRelation getGroupByRelation(bool *succeeded = nullptr) override;
			DbCaseSensitivity getIdentifierCaseSensitivity(bool *succeeded = nullptr) override;
			String getQuotedIdentifierDelimiter(bool *succeeded = nullptr) override;
			DbSupportedCreateIndexKeywords getSupportedCreateIndexKeywords(bool *succeeded = nullptr) override;
			DbSupportedInformationSchemaViews getSupportedInformationSchemaViews(bool *succeeded = nullptr) override;
			DbSupportedInsertStatements getSupportedInsertStatements(bool *succeeded = nullptr) override;
			bool isIntegritySupported(bool *succeeded = nullptr) override;
			DbCursorAttributes getKeysetCursorAttributes(bool *succeeded = nullptr) override;
			String getSupportedKeywords(bool *succeeded = nullptr) override;
			bool isLikeEscapeSupported(bool *succeeded = nullptr) override;
			int getMaximumAsyncronousConcurrentStatementCount(bool *succeeded = nullptr) override;
			int getMaximumBinaryLiteralLength(bool *succeeded = nullptr) override;
			int getMaximumCatalogNameLength(bool *succeeded = nullptr) override;
			int getMaximumCharacterLiteralLength(bool *succeeded = nullptr) override;
			int getMaximumColumnNameLength(bool *succeeded = nullptr) override;
			int getMaximumColumnsInGroupBy(bool *succeeded = nullptr) override;
			int getMaximumColumnsInIndex(bool *succeeded = nullptr) override;
			int getMaximumColumnsInOrderBy(bool *succeeded = nullptr) override;
			int getMaximumColumnsInSelect(bool *succeeded = nullptr) override;
			int getMaximumColumnsInTable(bool *succeeded = nullptr) override;
			int getMaximumConcurrentActivityCount(bool *succeeded = nullptr) override;
			int getMaximumCursorNameLength(bool *succeeded = nullptr) override;
			int getMaximumDriverConnectionCount(bool *succeeded = nullptr) override;
			int getMaximumIdentifierLength(bool *succeeded = nullptr) override;
			int getMaximumIndexSize(bool *succeeded = nullptr) override;
			int getMaximumProcedureNameLength(bool *succeeded = nullptr) override;
			int getMaximumRowSize(bool *succeeded = nullptr) override;
			bool isMaximumRowSizeIncludesLong(bool *succeeded = nullptr) override;
			int getMaximumSchemaNameLength(bool *succeeded = nullptr) override;
			int getMaximumStatementLength(bool *succeeded = nullptr) override;
			int getMaximumTableNameLength(bool *succeeded = nullptr) override;
			int getMaximumTablesInSelect(bool *succeeded = nullptr) override;
			int getMaximumUserNameLength(bool *succeeded = nullptr) override;
			bool isMultipleResultSetsSupported(bool *succeeded = nullptr) override;
			bool isMultipleActiveTransactionsSupported(bool *succeeded = nullptr) override;
			bool isDataSourceNeedLengthOfLongDataValue(bool *succeeded = nullptr) override;
			bool isNonNullableColumnsSupported(bool *succeeded = nullptr) override;
			DbNullCollation getNullCollation(bool *succeeded = nullptr) override;
			DbSupportedNumericFunctions getSupportedNumericFunctions(bool *succeeded = nullptr) override;
			DbOdbcInterfaceConformance getOdbcInterfaceConformance(bool *succeeded = nullptr) override;
			String getOdbcVersion(bool *succeeded = nullptr) override;
			DbSupportedOuterJoins getSupportedOuterJoins(bool *succeeded = nullptr) override;
			bool isOrderByColumnsMustBeInSelect(bool *succeeded = nullptr) override;
			bool isIndividualRowCountsAvailableInParametrizedExecution(bool *succeeded = nullptr) override;
			DbSupportedAvailabilityOfResultSetsInParameterizedExecution getSupportedAvailabilityOfResultSetsInParameterizedExecution(bool *succeeded = nullptr) override;
			DbSupportedPositionOperations getSupportedPositionOperations(bool *succeeded = nullptr) override;
			String getProcedureVendorName(bool *succeeded = nullptr) override;
			bool isProceduresSupported(bool *succeeded = nullptr) override;
			DbCaseSensitivity getQuotedIdentifierCaseSensitivity(bool *succeeded = nullptr) override;
			bool isRowUpdatesMaintainRowVersions(bool *succeeded = nullptr) override;
			String getSchemaVendorName(bool *succeeded = nullptr) override;
			DbSupportedSchemaUsages getSupportedSchemaUsages(bool *succeeded = nullptr) override;
			DbSupportedScrollOptions getSupportedScrollOptions(bool *succeeded = nullptr) override;
			String getSearchPatternEscape(bool *succeeded = nullptr) override;
			String getServerName(bool *succeeded = nullptr) override;
			String getSpecialCharacters(bool *succeeded = nullptr) override;
			DbSqlConformance getSqlConformance(bool *succeeded = nullptr) override;
			DbSupportedDateTimeFunctions getSupportedDateTimeFunctions(bool *succeeded = nullptr) override;
			DbSupportedForeignKeyRules getSupportedForeignKeyDeleteRules(bool *succeeded = nullptr) override;
			DbSupportedForeignKeyRules getSupportedForeignKeyUpdateRules(bool *succeeded = nullptr) override;
			DbSupportedGrantClauses getSupportedGrantClauses(bool *succeeded = nullptr) override;
			DbSupportedNumericValueFunctions getSupportedNumericValueFunctions(bool *succeeded = nullptr) override;
			DbSupportedPredicates getSupportedPredicates(bool *succeeded = nullptr) override;
			DbSupportedRelationJoinOperators getSupportedRelationJoinOperators(bool *succeeded = nullptr) override;
			DbSupportedRevokeClauses getSupportedRevokeClauses(bool *succeeded = nullptr) override;
			DbSupportedRowValueConstructors getSupportedRowValueConstructors(bool *succeeded = nullptr) override;
			DbSupportedStringFunctions getSupportedStringFunctions(bool *succeeded = nullptr) override;
			DbSupportedValueExpressions getSupportedValueExpressions(bool *succeeded = nullptr) override;
			DbStandardCliConformance getStandardCliConformance(bool *succeeded = nullptr) override;
			DbCursorAttributes getStaticCursorAttributes(bool *succeeded = nullptr) override;
			DbSupportedScalarStringFunctions getSupportedScalarStringFunctions(bool *succeeded = nullptr) override;
			DbSupportedSubQueryPredicates getSupportedSubQueryPredicates(bool *succeeded = nullptr) override;
			DbSupportedSystemFunctions getSupportedSystemFunctions(bool *succeeded = nullptr) override;
			String getTableVendorName(bool *succeeded = nullptr) override;
			DbSupportedDateTimeIntervals getSupportedDateTimeAddIntervals(bool *succeeded = nullptr) override;
			DbSupportedDateTimeIntervals getSupportedDateTimeDiffIntervals(bool *succeeded = nullptr) override;
			DbSupportedTimeDateFunctions getSupportedTimeDateFunctions(bool *succeeded = nullptr) override;
			DbTransactionSupport getTransactionSupport(bool *succeeded = nullptr) override;
			DbSupportedTransactionIsolationLevels getSupportedTransactionIsolationLevels(bool *succeeded = nullptr) override;
			DbSupportedUnionClauses getSupportedUnionClauses(bool *succeeded = nullptr) override;
			String getUserName(bool *succeeded = nullptr) override;
			String getOpenGroupSpecificationPublicationYear(bool *succeeded = nullptr) override;

			// IDbConnection setters
			void setErrorListener(IErrorListener *value) override;
			bool setAssignErrorListener(const bool value) override;
			bool setReadOnlyMode(const bool value) override;
			bool setAutoCommit(const bool value) override;
			bool setTrace(const bool value) override;
			bool setTraceFilename(const String &value) override;
			bool setConnectionTimeout(const int value) override;
			bool setLoginTimeout(const int value) override;
			bool setTransactionIsolationLevels(const DbSupportedTransactionIsolationLevels value) override;
			bool setWindow(IWindow *value) override;

			// IDbConnection statements
			IDbStatement *CreateStatement() override;

			CDbConnection(PlatformHandle handle, const String &connection_options, const String &connection_string, CDb *db);
		};
	}
}