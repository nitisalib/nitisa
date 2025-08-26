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

	namespace ide
	{
		class CFormView;

		class CFormViewService :public CControlService
		{
		private:
			enum class Element
			{
				Right,
				Bottom,
				Corner,
				None
			};
		private:
			CFormView *m_pFormView;
			bool m_bDown;
			Element m_eDownElement;
			PointF m_sDownPosition;
			PointF m_sDownSize;

			void CancelDown(const bool check_capture);
			Element ElementAtCursor(const PointF &position);
		public:
			// Control notifications
			void NotifyOnControlSetFocus(IControl *control, const MessageFocus &m) override;
			void NotifyOnControlKillFocus(IControl *control) override;

			// Notifications from parent control
			void NotifyOnParentFontChange() override;

			// State change notifications
			void NotifyOnFreeResources() override;
			void NotifyOnResize() override;
			void NotifyOnFontChange() override;
			void NotifyOnKillCaptureMouse() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

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

			CFormViewService(CFormView *formview);
		};
	}
}