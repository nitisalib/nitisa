// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IServerSocket.h"
#include "Nitisa/Interfaces/ISocket.h"
#include "Socket.h"
#include <atomic>

namespace nitisa
{
	class IServerSocketListener;

	namespace platform
	{
		namespace windows
		{
			class CClientSocket;

			class CServerSocket :public virtual IServerSocket, public CSocket
			{
				friend CClientSocket;
			private:
				IServerSocketListener *m_pListener;
				std::atomic<bool> m_bTerminated;

				static ISocket::ErrorType DecodeError(const int error);
			public:
				IServerSocketListener *getListener() override;

				void setListener(IServerSocketListener *value) override;

				void Terminate() override;
				bool Listen() override;

				CServerSocket(void *socket, const AnsiString &local_ip, const AnsiString &remote_ip, const int local_port, const int remote_port);
			};
		}
	}
}
#endif