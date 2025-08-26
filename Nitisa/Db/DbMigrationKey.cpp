// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CDbMigrationKey::CDbMigrationKey(const String& name, const StringArray& parts, const bool& fulltext) :
		CReleasable()
	{
		m_eType = Type::Index;
		m_sName = name;
		m_aParts = parts;
		m_bFullText = fulltext;
	}

	CDbMigrationKey::CDbMigrationKey(const String& symbol, const StringArray& parts) :
		CReleasable()
	{
		m_eType = Type::Primary;
		m_sSymbol = symbol;
		m_aParts = parts;
	}

	CDbMigrationKey::CDbMigrationKey(const String& symbol, const String& name, const StringArray& parts) :
		CReleasable()
	{
		m_eType = Type::Unique;
		m_sSymbol = symbol;
		m_sName = name;
		m_aParts = parts;
	}

	CDbMigrationKey::CDbMigrationKey(
		const String& symbol,
		const String& name,
		const StringArray& columns,
		const String& ref_table,
		const StringArray& ref_parts,
		const IDbMigrationKey::RefOption& on_delete,
		const IDbMigrationKey::RefOption& on_update) :
		CReleasable()
	{
		m_eType = Type::Foreign;
		m_sSymbol = symbol;
		m_sName = name;
		m_aParts = columns;
		m_sRefTable = ref_table;
		m_aRefParts = ref_parts;
		m_eOnDelete = on_delete;
		m_eOnUpdate = on_update;
	}
#pragma endregion

#pragma region IDbMigrationKey methods
	IDbMigrationKey* CDbMigrationKey::Comment(const String& comment)
	{
		m_sComment = comment;
		return this;
	}
#pragma endregion
}