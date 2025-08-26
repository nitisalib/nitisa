// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	class IClientSocket;
	class IServerSocket;

	class INetwork
	{
	protected:
		INetwork() = default;
		~INetwork() = default;
		INetwork(const INetwork &other) = delete;
		INetwork(INetwork &&other) = delete;
		INetwork &operator=(const INetwork &other) = delete;
		INetwork &operator=(INetwork &&other) = delete;
	public:
		virtual IClientSocket *TCPConnect(const String &server, const int port, const float timeout) = 0; // Create client connection to specified address and port
		virtual IServerSocket *TCPListen(const int port) = 0; // Create server connection on specified port
	};
}