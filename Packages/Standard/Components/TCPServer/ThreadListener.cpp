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
		CTCPServer::CThreadListener::CThreadListener(CTCPServer *control) :
			m_pControl{ control }
		{

		}

		void CTCPServer::CThreadListener::NotifyOnProcess(IThread *sender)
		{
			m_pControl->m_pSocket->Listen();
		}
	}
}