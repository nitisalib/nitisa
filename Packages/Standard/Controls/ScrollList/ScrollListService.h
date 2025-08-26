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
		class CScrollList;

		class CScrollListService :public CControlService
		{
		private:
			CScrollList *m_pControl;
			bool m_bAligning;
			bool m_bDown;
			bool m_bMaskActive;

			void CancelDown(const bool check_capture);
			PointF FormToScroll(const PointF &position);
			bool HitTest(const PointF &position);
		public:
			// Helpers
			void AlignControls() override;

			// State change notifications
			void NotifyOnFreeResources() override;

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

			// State change notifications
			void NotifyOnEnable() override; // Repaint is called automatically
			void NotifyOnDisable() override; // Repaint is called automatically
			void NotifyOnResize() override; // Repaint is called automatically
			void NotifyOnStyleChange() override; // Repaint is called automatically
			void NotifyOnKillCaptureMouse() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;
			void NotifyOnPaintEnd(const MessagePaint &m) override;

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
			void NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed) override;

			CScrollListService(CScrollList *control);
		};
	}
}