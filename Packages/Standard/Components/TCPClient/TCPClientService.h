// This file is a part of Nitisa framework
// Copyright © 2018 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ComponentService.h"

namespace nitisa
{
	namespace standard
	{
		class CTCPClient;

		class CTCPClientService :public CComponentService
		{
		private:
			CTCPClient * m_pClient;
		public:
			// State change notifications
			void NotifyOnDetaching() override;

			CTCPClientService(CTCPClient *client);
		};
	}
}