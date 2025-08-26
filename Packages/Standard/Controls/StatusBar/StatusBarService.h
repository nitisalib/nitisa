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
#include "Nitisa/Interfaces/IComponentItemList.h"

namespace nitisa
{
	class IListItem;

	namespace standard
	{
		class CStatusBar;

		class CStatusBarService :public virtual IComponentItemListService, public CControlService
		{
			friend CStatusBar;
		private:
			CStatusBar *m_pStatusBar;
		public:
			CStatusBarService(CStatusBar *statusbar);

			bool MoveItem(IListItem *item, const int before) override;

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnFreeResources() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;
			void NotifyOnParentFontChange() override;

			// State change notifications
			void NotifyOnResize() override;
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnStyleChange() override;
			void NotifyOnFontChange() override;
			void NotifyOnMouseHover(const MessagePosition &m) override;
			void NotifyOnMouseLeave() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			// Input notifications
			void NotifyOnMouseMove(const MessageMouse &m, bool &processed) override;
		};
	}
}