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
		class CToolBar;

		class CToolBarService :public virtual ITimerListener, public CControlService
		{
		private:
			CToolBar *m_pToolBar;
			bool m_bIgnoreAlign;
			bool m_bDown;
			PlatformHandle m_hTimer;
			bool m_bMaskActive;

			void NotifyResize(IControl *control); // Specified control was resized by this one
			void CancelDown(const bool check_capture);
			void UpdatePositions();
		public:
			CToolBarService(CToolBar *toolbar);

			void AlignControls() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;

			// Notifications from child controls
			void NotifyOnChildTransform(IControl *control) override;
			void NotifyOnChildResize(IControl *control) override;
			void NotifyOnChildShow(IControl *control) override;
			void NotifyOnChildHide(IControl *control) override;
			void NotifyOnChildAttach(IControl *control) override;
			void NotifyOnChildDetach(IControl *control) override;

			// State change notifications
			void NotifyOnFreeResources() override;
			void NotifyOnStyleChange() override;
			void NotifyOnResize() override;
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnMouseHover(const MessagePosition &m) override;
			void NotifyOnMouseLeave() override;
			void NotifyOnKillCaptureMouse() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;
			void NotifyOnPaintEnd(const MessagePaint &m) override;

			// Input notifications
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
			void NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed) override;

			// Timer notification
			void NotifyOnTimer(const PlatformHandle id) override;
		};
	}
}