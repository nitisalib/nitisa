// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/INetwork.h"

namespace nitisa
{
	class IClientSocket;
	class IServerSocket;

	namespace platform
	{
		namespace windows
		{
			class CNetwork :public virtual INetwork
			{
			private:
				bool m_bInitialized;
			public:
				IClientSocket *TCPConnect(const String &server, const int port, const float timeout) override;
				IServerSocket *TCPListen(const int port) override;

				CNetwork();
				~CNetwork();
			};
		}
	}
}
#endif