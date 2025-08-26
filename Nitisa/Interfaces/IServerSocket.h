// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "ISocket.h"

namespace nitisa
{
	class IServerSocketListener;

	class IServerSocket :public virtual ISocket
	{
	protected:
		IServerSocket() = default;
		~IServerSocket() = default;
		IServerSocket(const IServerSocket &other) = delete;
		IServerSocket(IServerSocket &&other) = delete;
		IServerSocket &operator=(const IServerSocket &other) = delete;
		IServerSocket &operator=(IServerSocket &&other) = delete;
	public:
		virtual IServerSocketListener *getListener() = 0; // Return associated listener

		virtual void setListener(IServerSocketListener *value) = 0; // Set listener

		virtual void Terminate() = 0; // Stop listening
		virtual bool Listen() = 0; // Start listening loop. Would block until Terminate() call or error happened. Should be run in separate thread. Return false in case of error
	};
}