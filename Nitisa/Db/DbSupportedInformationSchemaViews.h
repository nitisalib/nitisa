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
	struct DbSupportedInformationSchemaViews
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool Assertions;
		bool CharacterSets;
		bool CheckConstraints;
		bool Collations;
		bool ColumnDomainUsage;
		bool ColumnPrivileges;
		bool Columns;
		bool ConstraintColumnUsage;
		bool ConstraintTableUsage;
		bool DomainConstraints;
		bool Domains;
		bool KeyColumnUsage;
		bool ReferentialConstraints;
		bool Schemata;
		bool SQLLanguages;
		bool TableConstraints;
		bool TablePrivileges;
		bool Tables;
		bool Translations;
		bool UsagePrivileges;
		bool ViewColumnUsage;
		bool ViewTableUsage;
		bool Views;

		explicit operator String() const;
	};
}