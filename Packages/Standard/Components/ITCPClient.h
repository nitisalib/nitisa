// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IComponent.h"

namespace nitisa
{
	class IClientSocket;

	namespace standard
	{
		class ITCPClient :public virtual IComponent
		{
		protected:
			ITCPClient() = default;
			~ITCPClient() = default;
			ITCPClient(const ITCPClient &other) = delete;
			ITCPClient(ITCPClient &&other) = delete;
			ITCPClient &operator=(const ITCPClient &other) = delete;
			ITCPClient &operator=(ITCPClient &&other) = delete;
		public:
			virtual bool isActive() = 0; // Return whether client is active or not
			virtual float getConnectTimeout() = 0; // Return connection timeout in seconds
			virtual float getTimeout() = 0; // Return IO timeout in seconds
			virtual String getServer() = 0; // Return server address
			virtual int getPort() = 0; // Return server port
			virtual IClientSocket *getSocket() = 0; // Return handler or nullptr if not connected

			virtual bool setActive(const bool value) = 0; // Activate(connect)/deactivate(disconnect)
			virtual bool setConnectTimeout(const float value) = 0;  // Set connect timeout
			virtual bool setTimeout(const float value) = 0; // Set IO operations timeout
			virtual bool setServer(const String &value) = 0; // Set server address. Disconnect from current one if connected and new address differs from old one
			virtual bool setPort(const int value) = 0; // Set port to be connected to. Disconnect from current server if connected and new port differs from old one
		};
	}
}