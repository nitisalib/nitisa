// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Core/Strings.h"
#include "../ITCPClient.h"

namespace nitisa
{
	class IClientSocket;
	class IForm;

	namespace standard
	{
		class CTCPClientService;

		class CTCPClient :public virtual ITCPClient, public CComponent
		{
			friend CTCPClientService;
		private:
			String m_sServer;
			int m_iPort;
			float m_fConnectTimeout;
			float m_fTimeout;
			IClientSocket *m_pSocket;
		public:
			bool isActive() override;
			float getConnectTimeout() override; // Default 5 seconds
			float getTimeout() override; // Default 5 seconds
			String getServer() override;
			int getPort() override;
			IClientSocket *getSocket() override;

			bool setActive(const bool value) override;
			bool setConnectTimeout(const float value) override;
			bool setTimeout(const float value) override;
			bool setServer(const String &value) override;
			bool setPort(const int value) override;

			CTCPClient();
			CTCPClient(IForm *parent);
			~CTCPClient() override;
		};
	}
}