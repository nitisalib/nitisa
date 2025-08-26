// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ControlService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Key.h"
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

		class CMainMenu;

		class CMainMenuService :public virtual ITimerListener, public CControlService
		{
			friend CMainMenu;
		private:
			CMainMenu *m_pMenu;
			bool m_bIgnoreKeyUp;
			bool m_bIgnoreMouseUp;
			IControl *m_pOldFocusedControl;

			IListItemMenu *FindHotkeyOwner(IListItem *parent);
			void CloseSubmenu(IListItem *parent, const bool deactivate_parent);
			void MouseDown(const MessageMouse &m);
			void MouseUp(const MessageMouse &m);
			bool FindSubmenu(IListItem *parent, const PointF &position, IListItem **item);
			IListItem *FindLastSubmenu(IListItem *parent);
			void ScrollToItem(IListItem *item);
			void Defocus();
			void ProcessKeyUp();
			void ProcessKeyDown();
			void ProcessKeyLeft();
			void ProcessKeyRight();
			void ProcessKeyHome();
			void ProcessKeyEnd();
			void ProcessKeyEsc();
			void ProcessOnKeyDown(const Key key);
			void ProcessOnKeyUp(const Key key);
			void NotifyFreeResources(IListItem *item);
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
		public:
			CMainMenuService(CMainMenu *menu);
			// Application notifications
			void NotifyOnTranslateChange() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;
			void NotifyOnParentFontChange() override;

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDetaching() override;
			void NotifyOnFreeResources() override;
			void NotifyOnResize() override;
			void NotifyOnStyleChange() override;
			void NotifyOnFontChange() override;
			void NotifyOnSetFocus(const MessageFocus &m) override;
			void NotifyOnKillFocus() override;
			void NotifyOnMouseLeave() override;
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