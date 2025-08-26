// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/INetwork.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	class IClientSocket;
	class IServerSocket;

	namespace platform
	{
		namespace linux
		{
			class CNetwork :public virtual INetwork
			{
			public:
				IClientSocket *TCPConnect(const String &server, const int port, const float timeout) override;
				IServerSocket *TCPListen(const int port) override;
			};
		}
	}
}
#endif