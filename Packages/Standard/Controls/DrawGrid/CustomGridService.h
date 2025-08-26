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
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/Rect.h"
#include "../IDrawGrid.h"

namespace nitisa
{
	class IListItem;

	namespace standard
	{
		class CCustomGrid;

		class CCustomGridService :public virtual ICustomGridService, public virtual ITimerListener, public CControlService
		{
		private:
			CCustomGrid * m_pControl;
			float m_fBorderDownShift; // Shift from border start when downed on border

			bool ProcessKeyLeft(const bool shift);
			bool ProcessKeyRight(const bool shift);
			bool ProcessKeyUp(const bool shift);
			bool ProcessKeyDown(const bool shift);
			bool ProcessKeyHome(const bool ctrl, const bool shift);
			bool ProcessKeyEnd(const bool ctrl, const bool shift);
			bool ProcessKeyPageUp(const bool shift);
			bool ProcessKeyPageDown(const bool shift);
			bool ProcessKeySelectAll();
			bool ProcessMouseMove(const PointF &p, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift);
			bool ProcessMouseMoveDownCell(const PointF &p);
			bool ProcessMouseMoveDownRightBorder(const PointF &p);
			bool ProcessMouseMoveDownBottomBorder(const PointF &p);
			bool isHoveredCellEnabled();
			bool SelectRange(const Rect &range);
			Point FindFirstActivatableCell();
			bool isCellActivatable(const int column, const int row);
			bool ActivateFirstCell();
		public:
			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDetaching() override;
			void NotifyOnFreeResources() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;

			// State change notifications
			void NotifyOnDisable() override;
			void NotifyOnResize() override;
			void NotifyOnStyleChange() override;
			void NotifyOnSetFocus(const MessageFocus &m) override;
			void NotifyOnKillFocus() override;
			void NotifyOnSetCaptureMouse() override;
			void NotifyOnKillCaptureMouse() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			// Keyboard input notifications
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;

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

			// Cell status change notifications
			void NotifyOnHoverCell(const int column, const int row, IListItem *item) override;
			void NotifyOnLeaveCell(const int column, const int row, IListItem *item) override;
			void NotifyOnSelectCell(const int column, const int row, IListItem *item) override;
			void NotifyOnDeselectCell(const int column, const int row, IListItem *item) override;
			void NotifyOnActivateCell(const int column, const int row, IListItem *item) override;
			void NotifyOnDeactivateCell(const int column, const int row, IListItem *item) override;
			void NotifyOnEnableCell(const int column, const int row, IListItem *item) override;
			void NotifyOnDisableCell(const int column, const int row, IListItem *item) override;
			void NotifyOnMouseDownCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			void NotifyOnMouseUpCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseMoveCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			void NotifyOnMouseDownCancel() override;

			// Timer notification
			void NotifyOnTimer(const PlatformHandle id) override;

			CCustomGridService(CCustomGrid *control);
		};
	}
}