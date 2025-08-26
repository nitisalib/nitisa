// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IServerSocketListener.h"
#include "Nitisa/Interfaces/ISocket.h"
#include "Nitisa/Interfaces/IThreadListener.h"
#include "../ITCPServer.h"
#include <mutex>
#include <vector>

namespace nitisa
{
	class IClient;
	class IClientSocket;
	class IForm;
	class IServerSocket;
	class IThread;

	namespace standard
	{
		class CTCPServerService;

		class CTCPServer :public virtual ITCPServer, public CComponent
		{
			friend CTCPServerService;
		private:
			class CClient :public virtual IClient, public IThreadListener
			{
				friend CTCPServer;
			private:
				CTCPServer * m_pServer;
				IClientSocket *m_pSocket;
				IThread *m_pThread;
				IUserData *m_pUserData;
			public:
				IClientSocket *getSocket() override;
				IThread *getThread() override;
				AnsiString getLocalIp() override;
				AnsiString getRemoteIp() override;
				int getLocalPort() override;
				int getRemotePort() override;
				IUserData *getUserData() override;

				void setUserData(IUserData *value) override;

				bool Disconnect() override;
				bool Resume();
				
				void NotifyOnProcess(IThread *sender) override;

				CClient(CTCPServer *server, IClientSocket *socket);
				virtual ~CClient();

				void Release(const float timeout);
			};

			class CServerSocketListener :public virtual IServerSocketListener
			{
			private:
				CTCPServer *m_pControl;
			public:
				void NotifyOnError(IServerSocket *sender, ISocket::ErrorType error) override;
				void NotifyOnConnect(IServerSocket *sender, bool &accept) override;
				void NotifyOnConnect(IServerSocket *sender, const AnsiString &ip, const int port, bool &accept) override;
				void NotifyOnConnect(IServerSocket *sender, IClientSocket *socket) override;

				CServerSocketListener(CTCPServer *control);
			};

			class CThreadListener :public virtual IThreadListener
			{
			private:
				CTCPServer *m_pControl;
			public:
				void NotifyOnProcess(IThread *sender) override;

				CThreadListener(CTCPServer *control);
			};
		private:
			int m_iPort;
			int m_iMaxConnectionCount;
			float m_fTimeout;
			float m_fStopTimeout;
			std::vector<CClient*> m_aClients;
			IServerSocket *m_pSocket;
			std::recursive_mutex m_sMutex;

			IThread *m_pThread;
			CServerSocketListener m_cServerSocketListener;
			CThreadListener m_cThreadListener;

			void NotifyOnClientError(CClient *client, const ISocket::ErrorType error);
			void NotifyOnClientDisconnect(CClient *client);
			bool NotifyOnClientHaveData(CClient *client);
		protected:
			void BeforeRelease() override;
		public:
			bool isActive() override;
			int getPort() override; // Default 0
			float getTimeout() override; // Default 5 seconds
			float getStopTimeout() override; // Default 5 seconds
			int getMaxConnectionCount() override; // Default 0
			int getClientCount() override;
			IClient *getClient(const int index) override;

			bool setActive(const bool value) override;
			bool setPort(const int value) override;
			bool setTimeout(const float value) override;
			bool setStopTimeout(const float value) override;
			bool setMaxConnectionCount(const int value) override;

			CTCPServer(); // Create
			CTCPServer(IForm *parent); // Create and place onto a form
		};
	}
}