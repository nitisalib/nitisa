// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Interfaces/IDbActiveRecord.h"

namespace nitisa
{
	class IDbConnection;
	class IDbStatement;
	class IDbQueryBuilder;

	namespace script
	{
		namespace cppdoc
		{
			class CActiveRecord :public virtual IDbActiveRecord
			{
			private:
				static IDbConnection *m_pConnection;
				static IDbStatement *m_pStatement;
				static IDbQueryBuilder *m_pQueryBuilder;
			public:
				// IDbActiveRecord getters
				IDbConnection *getConnection() override;
				IDbStatement *getStatement() override;
				IDbQueryBuilder *getQueryBuilder() override;

				// Static setters
				static void setConnection(IDbConnection *value);
				static void setStatement(IDbStatement *value);
				static void setQueryBuilder(IDbQueryBuilder *value);
			};
		}
	}
}