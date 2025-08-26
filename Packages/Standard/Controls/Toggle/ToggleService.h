// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ControlService.h"

namespace nitisa
{
	namespace standard
	{
		class CToggle;

		class CToggleService :public CControlService
		{
		private:
			CToggle *m_pControl;
		public:
			// State change notifications
			void NotifyOnFreeResources() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override; // Repaint is called automatically

			// State change notifications
			void NotifyOnEnable() override; // Repaint is called automatically
			void NotifyOnDisable() override; // Repaint is called automatically
			void NotifyOnResize() override; // Repaint is called automatically
			void NotifyOnStyleChange() override; // Repaint is called automatically

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			// Mouse input notifications
			void NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed) override;

			CToggleService(CToggle *control);
		};
	}
}