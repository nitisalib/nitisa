// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Interfaces/INetwork.h"
#include "Nitisa/Core/Strings.h"

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			class CSocket :public virtual ISocket
			{
			protected:
				void *m_pSocket;
			private:
				AnsiString m_sLocalIp;
				AnsiString m_sRemoteIp;
				int m_iLocalPort;
				int m_iRemotePort;
			public:
				AnsiString getLocalIp() override;
				AnsiString getRemoteIp() override;
				int getLocalPort() override;
				int getRemotePort() override;

				void Release() override;

				CSocket(void *socket, const AnsiString &local_ip, const AnsiString &remote_ip, const int local_port, const int remote_port);
				virtual ~CSocket();
			};
		}
	}
}
#endif