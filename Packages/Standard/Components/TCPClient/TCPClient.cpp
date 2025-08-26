// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CTCPClient::CTCPClient() :
			CComponent(L"TCPClient"),
			m_iPort{ 0 },
			m_fConnectTimeout{ 5 },
			m_fTimeout{ 5 },
			m_pSocket{ nullptr }
		{
			setService(new CTCPClientService(this), true);
		}

		CTCPClient::CTCPClient(IForm *parent) :CTCPClient()
		{
			setForm(parent);
		}

		CTCPClient::~CTCPClient()
		{
			if (m_pSocket)
				m_pSocket->Release();
		}
	#pragma endregion

	#pragma region Getters
		bool CTCPClient::isActive()
		{
			return m_pSocket != nullptr;
		}

		float CTCPClient::getConnectTimeout()
		{
			return m_fConnectTimeout;
		}

		float CTCPClient::getTimeout()
		{
			return m_fTimeout;
		}

		String CTCPClient::getServer()
		{
			return m_sServer;
		}

		int CTCPClient::getPort()
		{
			return m_iPort;
		}

		IClientSocket *CTCPClient::getSocket()
		{
			return m_pSocket;
		}
	#pragma endregion

	#pragma region Setters
		bool CTCPClient::setActive(const bool value)
		{
			// Connect
			if (value)
			{
				// Check wsa is initialized & server name is specified
				if (m_sServer.empty()  || m_iPort <= 0 || m_pSocket)
					return false;
				if (!(m_pSocket = Application->Network->TCPConnect(m_sServer, m_iPort, m_fConnectTimeout)))
					return false;
				m_pSocket->setTimeout(m_fTimeout);
				return true;
			}
			// Disconnect
			if (m_pSocket)
			{
				m_pSocket->Release();
				m_pSocket = nullptr;
				return true;
			}
			return false;
		}

		bool CTCPClient::setConnectTimeout(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fConnectTimeout))
			{
				m_fConnectTimeout = value;
				return true;
			}
			return false;
		}

		bool CTCPClient::setTimeout(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fTimeout))
			{
				m_fTimeout = value;
				if (m_pSocket)
					m_pSocket->setTimeout(m_fTimeout);
				return true;
			}
			return false;
		}

		bool CTCPClient::setServer(const String &value)
		{
			if (value != m_sServer)
			{
				m_sServer = value;
				setActive(false);
				return true;
			}
			return false;
		}

		bool CTCPClient::setPort(const int value)
		{
			if (value != m_iPort)
			{
				m_iPort = value;
				setActive(false);
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}