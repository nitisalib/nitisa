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
		CTCPServer::CTCPServer() :
			CComponent(L"TCPServer"),
			m_iPort{ 0 },
			m_iMaxConnectionCount{ 0 },
			m_fTimeout{ 5 },
			m_fStopTimeout{ 5 },
			m_pSocket{ nullptr },
			m_pThread{ nullptr },
			m_cServerSocketListener{ this },
			m_cThreadListener{ this }
		{
			OnConnect = nullptr;
			OnConnected = nullptr;
			OnServerError = nullptr;
			OnClientError = nullptr;
			OnClientDisconnect = nullptr;
			OnClientDestroy = nullptr;
			OnClientHaveData = nullptr;

			setService(new CTCPServerService(this), true);
		}

		CTCPServer::CTCPServer(IForm *parent) :CTCPServer()
		{
			setForm(parent);
		}

		void CTCPServer::BeforeRelease()
		{
			setActive(false);
			CComponent::BeforeRelease();
		}
	#pragma endregion

	#pragma region Getters
		bool CTCPServer::isActive()
		{
			return m_pSocket != nullptr;
		}

		int CTCPServer::getPort()
		{
			return m_iPort;
		}

		float CTCPServer::getTimeout()
		{
			return m_fTimeout;
		}

		float CTCPServer::getStopTimeout()
		{
			return m_fStopTimeout;
		}

		int CTCPServer::getMaxConnectionCount()
		{
			return m_iMaxConnectionCount;
		}

		int CTCPServer::getClientCount()
		{
			std::lock_guard<std::recursive_mutex> lock{ m_sMutex };
			return (int)m_aClients.size();
		}

		ITCPServer::IClient *CTCPServer::getClient(const int index)
		{
			std::lock_guard<std::recursive_mutex> lock{ m_sMutex };
			if (index >= 0 && index < (int)m_aClients.size())
				return m_aClients[index];
			return nullptr;
		}
	#pragma endregion

	#pragma region Setters
		bool CTCPServer::setActive(const bool value)
		{
			// Start
			if (value)
			{
				// Check if initialized
				if (m_iPort <= 0 || m_pSocket)
					return false;
				if ((m_pSocket = Application->Network->TCPListen(m_iPort)))
				{
					m_pSocket->setListener(&m_cServerSocketListener);
					if (!(m_pThread = Application->CreateThread(false, &m_cThreadListener)))
					{
						m_pSocket->Release();
						m_pSocket = nullptr;
						return false;
					}
					return true;
				}
				return false;
			}

			// Stop
			if (m_pSocket)
			{
				// Terminate listen thread. No more clients can connect
				m_pThread->Terminate();
				m_pThread->Wait(m_fStopTimeout);
				m_pThread->Release();
				m_pThread = nullptr;
				m_pSocket->Release();
				m_pSocket = nullptr;
				// Stop existing client threads
				for (auto client : m_aClients)
					client->Release(m_fStopTimeout);
				m_aClients.clear();
				return true;
			}
			return false;
		}

		bool CTCPServer::setPort(const int value)
		{
			if (value != m_iPort)
			{
				m_iPort = value;
				setActive(false);
				return true;
			}
			return false;
		}

		bool CTCPServer::setTimeout(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fTimeout))
			{
				m_fTimeout = value;
				return true;
			}
			return false;
		}

		bool CTCPServer::setStopTimeout(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fStopTimeout))
			{
				m_fStopTimeout = value;
				return true;
			}
			return false;
		}

		bool CTCPServer::setMaxConnectionCount(const int value)
		{
			if (value != m_iMaxConnectionCount)
			{
				m_iMaxConnectionCount = value < 0 ? 0 : value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Notifications
		void CTCPServer::NotifyOnClientError(CClient *client, const ISocket::ErrorType error)
		{
			if (OnClientError)
				OnClientError(this, client, error);
			client->Disconnect();
		}

		void CTCPServer::NotifyOnClientDisconnect(CClient *client)
		{
			if (OnClientDisconnect)
				OnClientDisconnect(this, client);
			{
				std::lock_guard<std::recursive_mutex> lock{ m_sMutex };
				auto pos{ std::find(m_aClients.begin(), m_aClients.end(), client) };
				if (pos != m_aClients.end())
					m_aClients.erase(pos);
			}
			client->Release(m_fStopTimeout);
		}

		bool CTCPServer::NotifyOnClientHaveData(CClient *client)
		{
			if (OnClientHaveData)
			{
				bool disconnect{ false };
				OnClientHaveData(this, client, disconnect);
				return !disconnect;
			}
			return false;
		}
	#pragma endregion
	}
}