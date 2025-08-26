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
			ListGuard::ListGuard(List *list) :
				m_pList{ list },
				m_pPList{ nullptr }
			{

			}

			ListGuard::ListGuard(List **plist) :
				m_pList{ nullptr },
				m_pPList{ plist }
			{

			}

			ListGuard::~ListGuard()
			{
				ntl::Free(m_pList);
				if (m_pPList)
					ntl::Free(*m_pPList);
			}

			ListGuard::operator List *()
			{
				if (m_pPList)
					return *m_pPList;
				return m_pList;
			}

			void ListGuard::Free()
			{
				m_pList = nullptr;
				m_pPList = nullptr;
			}
		}
	}
}