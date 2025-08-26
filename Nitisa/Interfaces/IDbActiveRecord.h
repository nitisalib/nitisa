// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	class IDbConnection;
	class IDbQueryBuilder;
	class IDbStatement;

	class IDbActiveRecord
	{
	protected:
		IDbActiveRecord() = default;
		~IDbActiveRecord() = default;
		IDbActiveRecord(const IDbActiveRecord &other) = delete;
		IDbActiveRecord(IDbActiveRecord &&other) = delete;
		IDbActiveRecord &operator=(const IDbActiveRecord &other) = delete;
		IDbActiveRecord &operator=(IDbActiveRecord &&other) = delete;
	public:
		virtual IDbConnection *getConnection() = 0; // Should return connection instance. Used only when statement is empty
		virtual IDbStatement *getStatement() = 0; // Should return statement instance. If specified, connection is not used
		virtual IDbQueryBuilder *getQueryBuilder() = 0; // Should return query builder instance
	};
}