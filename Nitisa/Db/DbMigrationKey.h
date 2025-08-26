// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Releasable.h"
#include "../Core/Strings.h"
#include "../Interfaces/IDbMigrationKey.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class CDbMigrationKey :public virtual IDbMigrationKey, public CReleasable
	{
	public:
		// IDbMigrationKey methods
		IDbMigrationKey *Comment(const String &comment) override;

		CDbMigrationKey(const String &name, const StringArray &parts, const bool &fulltext); // [FULLTEXT] INDEX [name] (part,...)
		CDbMigrationKey(const String &symbol, const StringArray &parts); // [CONSTRAINT [symbol]] PRIMARY KEY (part,...)
		CDbMigrationKey(const String &symbol, const String &name, const StringArray &parts); // [CONSTRAINT [symbol]] UNIQUE [name] (part,...)
		CDbMigrationKey(
			const String &symbol,
			const String &name,
			const StringArray &columns,
			const String &ref_table,
			const StringArray &ref_parts,
			const IDbMigrationKey::RefOption &on_delete,
			const IDbMigrationKey::RefOption &on_update); // [CONSTRAINT [symbol]] FOREIGN KEY [name] (column,...) reference_definition
	};
}