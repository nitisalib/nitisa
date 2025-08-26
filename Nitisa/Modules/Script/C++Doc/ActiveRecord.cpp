// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			IDbConnection *CActiveRecord::m_pConnection{ nullptr };
			IDbStatement *CActiveRecord::m_pStatement{ nullptr };
			IDbQueryBuilder *CActiveRecord::m_pQueryBuilder{ nullptr };

		#pragma region IDbActiveRecord getters
			IDbConnection *CActiveRecord::getConnection()
			{
				return m_pConnection;
			}

			IDbStatement *CActiveRecord::getStatement()
			{
				return m_pStatement;
			}

			IDbQueryBuilder *CActiveRecord::getQueryBuilder()
			{
				return m_pQueryBuilder;
			}
		#pragma endregion

		#pragma region Static setters
			void CActiveRecord::setConnection(IDbConnection *value)
			{
				m_pConnection = value;
			}

			void CActiveRecord::setStatement(IDbStatement *value)
			{
				m_pStatement = value;
			}

			void CActiveRecord::setQueryBuilder(IDbQueryBuilder *value)
			{
				m_pQueryBuilder = value;
			}
		#pragma endregion
		}
	}
}