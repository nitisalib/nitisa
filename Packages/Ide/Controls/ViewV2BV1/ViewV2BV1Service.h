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
	namespace ide
	{
		class CViewV2BV1;

		class CViewV2BV1Service :public CControlService
		{
		private:
			CViewV2BV1 *m_pControl;
			float m_fOldSeparator;
			float m_fDistance;

			void CancelDown(const bool check_capture_mouse, const bool check_capture_keyboard);
		public:
			// Helpers
			void AlignControls() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override; // Repaint is called automatically

			// Notifications from child controls
			void NotifyOnChildTransform(IControl *control) override;
			void NotifyOnChildResize(IControl *control) override;
			void NotifyOnChildShow(IControl *control) override;
			void NotifyOnChildHide(IControl *control) override;
			void NotifyOnChildAttach(IControl *control) override;
			void NotifyOnChildDetach(IControl *control) override;
			void NotifyOnChildBeforeTransform(IControl *control, bool &allowed) override;
			void NotifyOnChildBeforeResize(IControl *control, bool &allowed) override;
			void NotifyOnChildBeforeHide(IControl *control, bool &allowed) override;

			// State change notifications
			void NotifyOnStyleChange() override; // Repaint is called automatically
			void NotifyOnKillCaptureKeyboard() override;
			void NotifyOnKillCaptureMouse() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			// Keyboard input notifications
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;

			// Mouse input notifications
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

			CViewV2BV1Service(CViewV2BV1 *control);
		};
	}
}