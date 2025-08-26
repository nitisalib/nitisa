// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		CTCPServer::CServerSocketListener::CServerSocketListener(CTCPServer *control) :
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Notifications
		void CTCPServer::CServerSocketListener::NotifyOnError(IServerSocket *sender, const ISocket::ErrorType error)
		{
			if (m_pControl->OnServerError)
				m_pControl->OnServerError(m_pControl, error);
			m_pControl->setActive(false);
		}

		void CTCPServer::CServerSocketListener::NotifyOnConnect(IServerSocket *sender, bool &accept)
		{
			std::lock_guard<std::recursive_mutex> lock{ m_pControl->m_sMutex };
			accept = m_pControl->m_iMaxConnectionCount <= 0 || (int)m_pControl->m_aClients.size() < m_pControl->m_iMaxConnectionCount;
		}

		void CTCPServer::CServerSocketListener::NotifyOnConnect(IServerSocket *sender, const AnsiString &ip, const int port, bool &accept)
		{
			std::lock_guard<std::recursive_mutex> lock{ m_pControl->m_sMutex };
			if (m_pControl->OnConnect)
				m_pControl->OnConnect(m_pControl, ip, port, accept);
		}

		void CTCPServer::CServerSocketListener::NotifyOnConnect(IServerSocket *sender, IClientSocket *socket)
		{
			std::lock_guard<std::recursive_mutex> lock{ m_pControl->m_sMutex };
			socket->setTimeout(m_pControl->m_fTimeout);
			CClient *client{ new CClient(m_pControl, socket) };
			m_pControl->m_aClients.push_back(client);
			if (m_pControl->OnConnected)
				m_pControl->OnConnected(m_pControl, client);
			client->Resume();
		}
	#pragma endregion
	}
}