// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/ControlService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Interfaces/ITimerListener.h"

namespace nitisa
{
	class IControl;

	namespace standard
	{
		class CUpDownEx;

		class CUpDownExService :public virtual ITimerListener, public CControlService
		{
		private:
			CUpDownEx * m_pUpDown;
			bool m_bDragging;
			float m_fOldValue;
			float m_fLastY;

			void CancelDown(const bool check_capture);
		public:
			// State change notifications
			void NotifyOnDetaching() override;
			void NotifyOnFreeResources() override;

			// Control notifications
			void NotifyOnControlDetach(IControl *control) override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;

			// State change notifications
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnResize() override;
			void NotifyOnStyleChange() override;
			void NotifyOnSetCaptureMouse() override;
			void NotifyOnKillCaptureMouse() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			// Keyboard input notifications
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;
			void NotifyOnKeyUp(const MessageKey &m, bool &processed) override;

			// Mouse input notifications
			void NotifyOnMouseHover(const MessagePosition &m) override;
			void NotifyOnMouseLeave() override;
			void NotifyOnMouseMove(const MessageMouse &m, bool &processed) override;
			void NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed) override;
			void NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed) override;
			void NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed) override;
			void NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed) override;
			void NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed) override;
			void NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed) override;
			void NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed) override;
			void NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed) override;
			void NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed) override;
			void NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed) override;

			// Timer notification
			void NotifyOnTimer(const PlatformHandle id) override;

			CUpDownExService(CUpDownEx *updown);
		};
	}
}