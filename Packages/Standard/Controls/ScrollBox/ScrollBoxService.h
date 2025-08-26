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
#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	class IControl;

	namespace standard
	{
		class CScrollBox;

		class CScrollBoxService :public CControlService
		{
		private:
			CScrollBox *m_pScrollBox;
			bool m_bMaskActive;

			void CancelDown(const bool check_capture);
			PointF FormToVScroll(const PointF &pos);
			PointF FormToHScroll(const PointF &pos);
		public:
			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDetaching() override;
			void NotifyOnFreeResources() override;

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
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnResize() override;
			void NotifyOnStyleChange() override;
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

			CScrollBoxService(CScrollBox *scrollbox);
		};
	}
}