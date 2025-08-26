// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
	#pragma region Constructor & destructor
		CTCPServerService::CTCPServerService(CTCPServer *server) :
			CComponentService(server),
			m_pServer{ server }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CTCPServerService::NotifyOnDetaching()
		{
			m_pServer->setActive(false);
		}
	#pragma endregion
	}
}