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
		CTCPServer::CClient::CClient(CTCPServer *server, IClientSocket *socket) :
			m_pServer{ server },
			m_pSocket{ socket },
			m_pUserData{ nullptr }
		{
			m_pThread = Application->CreateThread(true, this);
		}

		CTCPServer::CClient::~CClient()
		{
			if (m_pThread)
				m_pThread->Release();
			if (m_pSocket)
				m_pSocket->Release();
			if (m_pUserData)
				m_pUserData->Release();
		}

		void CTCPServer::CClient::Release(const float timeout)
		{
			if (m_pThread)
			{
				m_pThread->Terminate();
				m_pThread->Wait(timeout);
			}
			if (m_pServer->OnClientDestroy)
				m_pServer->OnClientDestroy(m_pServer, this);
			delete this;
		}
	#pragma endregion

	#pragma region Getters
		IClientSocket *CTCPServer::CClient::getSocket()
		{
			return m_pSocket;
		}

		IThread *CTCPServer::CClient::getThread()
		{
			return m_pThread;
		}

		AnsiString CTCPServer::CClient::getLocalIp()
		{
			if (m_pSocket)
				return m_pSocket->getLocalIp();
			return "";
		}

		AnsiString CTCPServer::CClient::getRemoteIp()
		{
			if (m_pSocket)
				return m_pSocket->getRemoteIp();
			return "";
		}

		int CTCPServer::CClient::getLocalPort()
		{
			if (m_pSocket)
				return m_pSocket->getLocalPort();
			return 0;
		}

		int CTCPServer::CClient::getRemotePort()
		{
			if (m_pSocket)
				return m_pSocket->getRemotePort();
			return 0;
		}

		ITCPServer::IUserData *CTCPServer::CClient::getUserData()
		{
			return m_pUserData;
		}
	#pragma endregion

	#pragma region Setters
		void CTCPServer::CClient::setUserData(IUserData *value)
		{
			if (m_pUserData && m_pUserData != value)
				m_pUserData->Release();
			m_pUserData = value;
		}
	#pragma endregion

	#pragma region Helpers
		bool CTCPServer::CClient::Disconnect()
		{
			if (m_pSocket)
			{
				m_pServer->NotifyOnClientDisconnect(this);
				m_pSocket->Release();
				m_pSocket = nullptr;
				return true;
			}
			return false;
		}

		bool CTCPServer::CClient::Resume()
		{
			if (m_pThread)
				return m_pThread->Resume();
			return false;
		}

		void CTCPServer::CClient::NotifyOnProcess(IThread *sender)
		{
			while (!sender->isTerminated() && m_pSocket)
			{
				ISocket::ErrorType error;
				ISocket::DataExist check{ m_pSocket->isDataExist(error) };
				switch (check)
				{
				case ISocket::DataExist::Error:
					m_pServer->NotifyOnClientError(this, error);
					break;
				case ISocket::DataExist::Disconnected:
					Disconnect();
					break;
				case ISocket::DataExist::Exist:
					if (!m_pServer->NotifyOnClientHaveData(this))
						Disconnect();
					break;
				default:
					break;
				}
			}
		}
	#pragma endregion
	}
}