// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IComponent.h"
#include "Nitisa/Interfaces/ISocket.h"

namespace nitisa
{
	class IClient;
	class IClientSocket;
	class IThread;

	namespace standard
	{
		class ITCPServer :public virtual IComponent
		{
		protected:
			ITCPServer() = default;
			~ITCPServer() = default;
			ITCPServer(const ITCPServer &other) = delete;
			ITCPServer(ITCPServer &&other) = delete;
			ITCPServer &operator=(const ITCPServer &other) = delete;
			ITCPServer &operator=(ITCPServer &&other) = delete;
		public:
			class IUserData // User data
			{
			protected:
				IUserData() = default;
				~IUserData() = default;
				IUserData(const IUserData &other) = delete;
				IUserData(IUserData &&other) = delete;
				IUserData &operator=(const IUserData &other) = delete;
				IUserData &operator=(IUserData &&other) = delete;
			public:
				virtual void Release() = 0; // Delete itself
			};

			class IClient // Connected client information
			{
			protected:
				IClient() = default;
				~IClient() = default;
				IClient(const IClient &other) = delete;
				IClient(IClient &&other) = delete;
				IClient &operator=(const IClient &other) = delete;
				IClient &operator=(IClient &&other) = delete;
			public:
				virtual IClientSocket *getSocket() = 0; // Return IO handler
				virtual IThread *getThread() = 0; // Return thread
				virtual AnsiString getLocalIp() = 0; // Return local IP address
				virtual AnsiString getRemoteIp() = 0; // Return remote IP address
				virtual int getLocalPort() = 0; // Return local port
				virtual int getRemotePort() = 0; // Return remote port
				virtual IUserData * getUserData() = 0; // Return user data

				virtual void setUserData(IUserData *value) = 0; // Set user data. Destroyed automatically

				virtual bool Disconnect() = 0; // Disconnect
			};
		public:
			// Please note that all events are called NOT in main thread. You have to take care of synchronous access to resources
			void(*OnConnect)(ITCPServer *sender, const AnsiString &ip, const int port, bool &accept); // Event called when client is about to be connected. To prevent connection you may set accept to false
			void(*OnConnected)(ITCPServer *sender, IClient *client); // Event called when new client has just been connected
			void(*OnServerError)(ITCPServer *sender, const ISocket::ErrorType error); // Event called when any error at server happened
			void(*OnClientError)(ITCPServer *sender, IClient *client, const ISocket::ErrorType error); // Event called when any error at particular client happened
			void(*OnClientDisconnect)(ITCPServer *sender, IClient *client); // Event called when client is disconnected
			void(*OnClientDestroy)(ITCPServer *sender, IClient *client); // Event called when client is being destroyed
			void(*OnClientHaveData)(ITCPServer *sender, IClient *client, bool &disconnect); // Event called when client has got data. Use it to perform IO operations. Set disconnect to true to disconnect client

			virtual bool isActive() = 0; // Return whether the server is active or not
			virtual int getPort() = 0; // Return server listening port
			virtual float getTimeout() = 0; // Return IO operations timeout in seconds
			virtual float getStopTimeout() = 0; // Return client waiting time when stopping the server. In seconds
			virtual int getMaxConnectionCount() = 0; // Return maximum allowed connections to the TCP server. <=0 means no limits
			virtual int getClientCount() = 0; // Return connected client count
			virtual IClient *getClient(const int index) = 0; // Return client data by index

			virtual bool setActive(const bool value) = 0; // Activate or deactivate server
			virtual bool setPort(const int value) = 0; // Set listening port. If differs from current one, the server will be automatically stopped
			virtual bool setTimeout(const float value) = 0; // Set IO operations timeout. Applies to new connections only
			virtual bool setStopTimeout(const float value) = 0; // Set client stop waiting time on server stop
			virtual bool setMaxConnectionCount(const int value) = 0; // Set maximum allowed connections. <=0 means no limits
		};
	}
}