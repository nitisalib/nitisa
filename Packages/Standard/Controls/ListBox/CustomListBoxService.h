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
#include "Nitisa/Interfaces/IComponentItemListService.h"
#include "Nitisa/Interfaces/ITimerListener.h"
#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	class IListItem;

	namespace standard
	{
		class CCustomListBox;

		class CCustomListBoxService :public virtual IComponentItemListService, public virtual ITimerListener, public CControlService
		{
			friend CCustomListBox;
		private:
			enum class Element
			{
				None,
				List,
				HScroll,
				VScroll
			};

			CCustomListBox *m_pListBox;
			PlatformHandle m_hTimer;

			PointF LocalToHScroll(const PointF &position);
			PointF LocalToVScroll(const PointF &position);
			PointF LocalToItem(const PointF &position, const int index);
			Element getElement(const PointF &position);
			bool SelectRange(int from, int to);
			bool InvertRange(int from, int to); // From is not affected
			void ProcessKeyUp(const bool shift);
			void ProcessKeyDown(const bool shift);
			void ProcessKeyPageUp(const bool shift);
			void ProcessKeyPageDown(const bool shift);
			void ProcessKeyHome(const bool ctrl, const bool shift);
			void ProcessKeyEnd(const bool ctrl, const bool shift);
			void ProcessKeyLeft(const bool shift);
			void ProcessKeyRight(const bool shift);
			void ProcessKeySpace();
			void ProcessKeyA();
			void MouseUp();
			void ProcessMove(const PointF &position);
			void PostKey(const int index, const bool shift);
		public:
			CCustomListBoxService(CCustomListBox *listbox);

			bool MoveItem(IListItem *item, const int before) override;

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDetaching() override;
			void NotifyOnFreeResources() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;
			void NotifyOnParentFontChange() override;

			// State change notifications
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnResize() override;
			void NotifyOnStyleChange() override;
			void NotifyOnFontChange() override;
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
			void NotifyOnChar(const MessageChar &m, bool &processed) override;
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

			// Timer notification
			void NotifyOnTimer(const PlatformHandle id) override;
		};
	}
}