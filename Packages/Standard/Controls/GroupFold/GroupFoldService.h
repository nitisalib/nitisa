// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		class CGroupFold;

		class CGroupFoldService :public CControlService
		{
		private:
			CGroupFold *m_pControl;
			bool m_bMaskActive;
		public:
			// Helpers
			void AlignControls() override;

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDetach() override;

			// State change notifications
			void NotifyOnFreeResources() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override; // Repaint is called automatically
			void NotifyOnParentFontChange() override; // Repaint is called automatically

			// State change notifications
			void NotifyOnEnable() override; // Repaint is called automatically
			void NotifyOnDisable() override; // Repaint is called automatically
			void NotifyOnResize() override; // Repaint is called automatically
			void NotifyOnStyleChange() override; // Repaint is called automatically
			void NotifyOnFontChange() override; // Repaint is called automatically

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;
			void NotifyOnPaintEnd(const MessagePaint &m) override;

			// Mouse input notifications
			void NotifyOnMouseHover(const MessagePosition &m) override;
			void NotifyOnMouseLeave() override;
			void NotifyOnMouseMove(const MessageMouse &m, bool &processed) override;
			void NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed) override;

			CGroupFoldService(CGroupFold *control);
		};
	}
}