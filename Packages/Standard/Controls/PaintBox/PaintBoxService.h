// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ControlService.h"
#include "Nitisa/Core/Messages.h"

namespace nitisa
{
	namespace standard
	{
		class CPaintBox;

		class CPaintBoxService :public CControlService
		{
		private:
			CPaintBox * m_pPaintBox;
		public:
			// State change notifications
			void NotifyOnFreeResources() override;
			void NotifyOnResize() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			CPaintBoxService(CPaintBox *paintbox);
		};
	}
}