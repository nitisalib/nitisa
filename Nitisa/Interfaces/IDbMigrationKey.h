// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "IReleasable.h"

namespace nitisa
{
	class IDbMigrationKey :public virtual IReleasable
	{
	public:
		enum class Type // Key type
		{
			Index,
			Primary,
			Unique,
			Foreign
		};

		enum class RefOption // Foreign key behaviour actions
		{
			None,
			NoAction,
			Restrict,
			Cascade,
			SetNull,
			SetDefault
		};
	protected:
		IDbMigrationKey() = default;
		~IDbMigrationKey() = default;
		IDbMigrationKey(const IDbMigrationKey &other) = delete;
		IDbMigrationKey(IDbMigrationKey &&other) = delete;
		IDbMigrationKey &operator=(const IDbMigrationKey &other) = delete;
		IDbMigrationKey &operator=(IDbMigrationKey &&other) = delete;
	protected:
		Type m_eType;
		String m_sSymbol;
		String m_sName;
		StringArray m_aParts;
		bool m_bFullText;
		String m_sRefTable;
		StringArray m_aRefParts;
		RefOption m_eOnDelete;
		RefOption m_eOnUpdate;
		String m_sComment;
	public:
		// Read-only references to the protected members
		Type const &eType{ m_eType };
		String const &sSymbol{ m_sSymbol };
		String const &sName{ m_sName };
		StringArray const &aParts{ m_aParts };
		bool const &bFullText{ m_bFullText };
		String const &sRefTable{ m_sRefTable };
		StringArray const &aRefParts{ m_aRefParts };
		RefOption const &eOnDelete{ m_eOnDelete };
		RefOption const &eOnUpdate{ m_eOnUpdate };
		String const &sComment{ m_sComment };

		virtual IDbMigrationKey *Comment(const String &comment) = 0;
	};
}