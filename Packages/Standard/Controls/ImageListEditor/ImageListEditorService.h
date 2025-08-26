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
	class IComponent;
	class IControl;

	namespace standard
	{
		class CImageListEditor;

		class CImageListEditorService :public CControlService
		{
		private:
			CImageListEditor *m_pEditor;
			bool m_bDown;

			void CancelDown(const bool check_capture);
			PointF FormToScroll(const PointF &position);
		public:
			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDetaching() override;
			void NotifyOnFreeResources() override;

			// Component notifications
			void NotifyOnComponentDetach(IComponent *component) override;
			void NotifyOnComponentChange(IComponent *component) override;

			// Control notifications
			void NotifyOnControlDetach(IControl *control) override;
			void NotifyOnControlChange(IControl *control) override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;
			void NotifyOnParentFontChange() override;

			// State change notifications
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnResize() override;
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
			void NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed) override;
			void NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed) override;

			CImageListEditorService(CImageListEditor *editor);
		};
	}
}