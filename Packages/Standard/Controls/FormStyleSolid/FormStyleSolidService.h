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
#include "Nitisa/Math/Point.h"

namespace nitisa
{
	namespace standard
	{
		class CFormStyleSolid;

		class CFormStyleSolidService :public CControlService
		{
		private:
			CFormStyleSolid * m_pControl;
			Point m_sDownPosition;
			Point m_sFormSize;
			Point m_sFormPosition;

			bool ResizeLeft(const Point &position);
			bool ResizeTop(const Point &position);
			bool ResizeRight(const Point &position);
			bool ResizeBottom(const Point &position);
			bool ResizeLeftTop(const Point &position);
			bool ResizeRightTop(const Point &position);
			bool ResizeLeftBottom(const Point &position);
			bool ResizeRightBottom(const Point &position);
			void Move(const Point &position);
			void CancelDown(const bool check_capture);
		public:
			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnFreeResources() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;
			void NotifyOnParentFontChange() override;
			void NotifyOnParentResize() override;

			// State change notifications
			void NotifyOnStyleChange() override;
			void NotifyOnFontChange() override;
			void NotifyOnKillCaptureMouse() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

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

			CFormStyleSolidService(CFormStyleSolid *control);
		};
	}
}