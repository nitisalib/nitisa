// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "ISocket.h"

namespace nitisa
{
	class IClientSocket;
	class IServerSocket;

	class IServerSocketListener
	{
	protected:
		IServerSocketListener() = default;
		~IServerSocketListener() = default;
		IServerSocketListener(const IServerSocketListener &other) = delete;
		IServerSocketListener(IServerSocketListener &&other) = delete;
		IServerSocketListener &operator=(const IServerSocketListener &other) = delete;
		IServerSocketListener &operator=(IServerSocketListener &&other) = delete;
	public:
		virtual void NotifyOnError(IServerSocket *sender, const ISocket::ErrorType error) = 0; // Called when error happened during listen process. Listen stops after error
		virtual void NotifyOnConnect(IServerSocket *sender, bool &accept) = 0; // Called at first stage of client connection. Set accept = false to prevent connection. accept = false by default. It is a good place to check whether the maximum connections are already exists
		virtual void NotifyOnConnect(IServerSocket *sender, const AnsiString &ip, const int port, bool &accept) = 0; // Called at second stage of client connection. Set accept = false to prevent connection. accept = true by default. This is a good place to check whether connection is allowed for the client with specified ip address
		virtual void NotifyOnConnect(IServerSocket *sender, IClientSocket *socket) = 0; // Called at third, final, stage of client connection. The client is already connected and a new socket, responsible for communication with it, is provided
	};
}