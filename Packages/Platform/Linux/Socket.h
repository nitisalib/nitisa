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
#include "Nitisa/Interfaces/ISocket.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			class CSocket :public virtual ISocket
			{
			protected:
				PlatformHandle m_hHandle;
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

				CSocket(PlatformHandle handle, const AnsiString &local_ip, const AnsiString &remote_ip, const int local_port, const int remote_port);
				virtual ~CSocket();
			};
		}
	}
}
#endif