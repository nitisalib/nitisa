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
		class CTCPServer;

		class CTCPServerService :public CComponentService
		{
		private:
			CTCPServer * m_pServer;
		public:
			// State change notifications
			void NotifyOnDetaching() override;

			CTCPServerService(CTCPServer *server);
		};
	}
}