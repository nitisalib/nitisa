// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IServerSocket.h"
#include "Nitisa/Interfaces/IServerSocketListener.h"
#include "Nitisa/Interfaces/ISocket.h"
#include "Socket.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			class CClientSocket;

			class CServerSocket :public virtual IServerSocket, public CSocket
			{
				friend CClientSocket;
			private:
				IServerSocketListener *m_pListener;
				bool m_bTerminated;

				static ErrorType DecodeError(const int error);
			public:
				IServerSocketListener *getListener() override;

				void setListener(IServerSocketListener *value) override;

				void Terminate() override;
				bool Listen() override;

				CServerSocket(PlatformHandle handle, const AnsiString &local_ip, const AnsiString &remote_ip, const int local_port, const int remote_port);
			};
		}
	}
}
#endif