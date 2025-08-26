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
	class IComponent;
	class IControl;

	namespace standard
	{
		class IImageList;

		class CSpeedButton;

		class CSpeedButtonService :public CControlService
		{
		private:
			CSpeedButton *m_pSpeedButton;

			bool UpdateImageList(IImageList *list);
			bool RemoveImageList(IImageList *list);
		public:
			CSpeedButtonService(CSpeedButton *speed_button);

			// State change notifications
			void NotifyOnAttach() override; // Set down to false if needed
			void NotifyOnFreeResources() override;

			// Other components/controls/objects change notifications
			void NotifyOnComponentDetach(IComponent *component) override;
			void NotifyOnControlDetach(IControl *control) override;
			void NotifyOnComponentChange(IComponent *component) override;
			void NotifyOnControlChange(IControl *control) override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;

			// State change notifications
			void NotifyOnResize() override;
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnStyleChange() override;
			void NotifyOnSetFocus(const MessageFocus &m) override;
			void NotifyOnKillFocus() override;
			void NotifyOnMouseHover(const MessagePosition &m) override;
			void NotifyOnMouseLeave() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			// Input notifications
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;
			void NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed) override;
		};
	}
}