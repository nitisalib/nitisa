// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IServerSocket.h"
#include "Socket.h"

namespace nitisa
{
	class IServerSocketListener;

	namespace platform
	{
		namespace android
		{
			class CClientSocket;

			// http://beej.us/guide/bgnet/html/single/bgnet.html
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