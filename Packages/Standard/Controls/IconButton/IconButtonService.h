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

namespace nitisa
{
	class IControl;
	class IComponent;

	namespace standard
	{
		class CIconButton;

		class CIconButtonService :public CControlService
		{
		private:
			CIconButton *m_pControl;

			void CheckImageListDetach(IComponent *e);
			void CheckImageListChange(IComponent *e);
			void CancelMouseDown();
		public:
			CIconButtonService(CIconButton *button);

			// Other components/controls/objects change notifications
			void NotifyOnComponentDetach(IComponent *component) override;
			void NotifyOnControlDetach(IControl *control) override;
			void NotifyOnComponentChange(IComponent *component) override;
			void NotifyOnControlChange(IControl *control) override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;

			// State change notifications
			void NotifyOnFreeResources() override;
			void NotifyOnResize() override;
			void NotifyOnStyleChange() override;
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnSetFocus(const MessageFocus &m) override;
			void NotifyOnKillFocus() override;
			void NotifyOnMouseHover(const MessagePosition &m) override;
			void NotifyOnMouseLeave() override;
			void NotifyOnKillCaptureMouse() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			// Input notifications
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;
			void NotifyOnKeyUp(const MessageKey &m, bool &processed) override;
			void NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed) override;
			void NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed) override;
			void NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed) override;
			void NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed) override;
			void NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed) override;
			void NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed) override;
			void NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed) override;
			void NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed) override;
			void NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed) override;
		};
	}
}