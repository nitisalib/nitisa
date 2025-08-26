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
#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IListItem;

	namespace standard
	{
		class IListItemMenu;

		class CPopupMenu;

		class CPopupMenuService :public virtual ITimerListener, public CControlService
		{
			friend CPopupMenu;
		private:
			CPopupMenu *m_pMenu;
			bool m_bIgnoreKeyUp;
			bool m_bIgnoreMouseUp;

			IListItemMenu *FindHotkeyOwner(IListItem *parent);
			void CloseSubmenu(IListItem *parent, const bool deactivate_parent);
			void MouseDown(const MessageMouse &m);
			void MouseUp(const MessageMouse &m);
			bool FindSubmenu(IListItem *parent, const PointF &position, IListItem **item);
			IListItem *FindLastSubmenu(IListItem *parent);
			void ScrollToItem(IListItem *item);
			void ProcessKeyUp();
			void ProcessKeyDown();
			void ProcessKeyLeft();
			void ProcessKeyRight();
			void ProcessKeyHome();
			void ProcessKeyEnd();
			void ProcessKeyEsc();
			void ProcessOnKeyDown(const MessageKey &m);
			void ProcessOnKeyUp(const MessageKey &m);
			void UpdateHoveredItem(const PointF &position);
			void UnhoverItems(IListItem *parent);
			void ProcessMouseMove(const MessageMouse &m);
			void ProcessMouseDown(const MessageMouse &m);
			void ProcessMouseUp(const MessageMouse &m);
			void ProcessMouseDoubleClick(const MessageMouse &m);
			void ProcessMouseVerticalWheel(const MessageMouseWheel &m);
			void ProcessDropFiles(const MessageDropFiles &m);
			void ProcessChar(const MessageChar &m);
			IListItem *FindLastActiveItem();
			void NotifyFreeResources(IListItem *item);
		public:
			CPopupMenuService(CPopupMenu *menu);

			// Application notifications
			void NotifyOnTranslateChange() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;
			void NotifyOnParentFontChange() override;
			void NotifyOnParentResize() override;

			// State change notifications
			void NotifyOnShow() override; // Capture mouse & keyboard
			void NotifyOnHide() override; // Release captures, hide all submenus, deactive and unhover all items
			void NotifyOnAttach() override;
			void NotifyOnDetaching() override; // Hide
			void NotifyOnFreeResources() override;
			void NotifyOnResize() override;
			void NotifyOnStyleChange() override;
			void NotifyOnFontChange() override;
			void NotifyOnDeactivate() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			// Other components/controls/objects change notifications
			void NotifyOnComponentDetach(IComponent *component) override; // Check if assigned image list
			void NotifyOnControlDetach(IControl *control) override; // Check if assigned image list
			void NotifyOnComponentChange(IComponent *component) override; // Check if assigned image list
			void NotifyOnControlChange(IControl *control) override; // Check if assigned image list
			void NotifyOnHotkey(const MessageHotkey &m) override;

			// Input notifications
			void NotifyOnChar(const MessageChar &m, bool &processed) override;
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;
			void NotifyOnKeyUp(const MessageKey &m, bool &processed) override;
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
			void NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted) override;

			// Timer notification
			void NotifyOnTimer(const PlatformHandle id) override;
		};
	}
}