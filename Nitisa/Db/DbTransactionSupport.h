// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	enum class DbTransactionSupport
	{
		Unknown,
		None, // Transactions not supported.
		DataManipulation, // Transactions can contain only Data Manipulation Language (DML) statements (SELECT, INSERT, UPDATE, DELETE). Data Definition Language (DDL) statements encountered in a transaction cause an error.
		DataDefinitionCommit, // Transactions can contain only DML statements. DDL statements (CREATE TABLE, DROP INDEX, and so on) encountered in a transaction cause the transaction to be committed.
		DataDefinitionIgnore, // Transactions can contain only DML statements. DDL statements encountered in a transaction are ignored.
		All // Transactions can contain DDL statements and DML statements in any order.
	};

	String ToString(const DbTransactionSupport value);
}