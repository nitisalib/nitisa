// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Math/PointF.h"
#include "../DrawGrid/CustomDrawGridService.h"
#include "../IStringGrid.h"

namespace nitisa
{
	class IListItem;

	namespace standard
	{
		class CCustomStringGrid;

		class CCustomStringGridService :public virtual IStringGridService, public CCustomDrawGridService
		{
		private:
			CCustomStringGrid * m_pControl;

			PointF FormToTextInput(const PointF &position);
		public:
			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnFreeResources() override;

			// Notifications from parent control
			void NotifyOnParentFontChange() override;

			// State change notifications
			void NotifyOnFontChange() override;
			void NotifyOnKillFocus() override;

			// Keyboard input notifications
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;
			void NotifyOnKeyUp(const MessageKey &m, bool &processed) override;
			void NotifyOnChar(const MessageChar &m, bool &processed) override;

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
			void NotifyOnSelectCell(const int column, const int row, IListItem *item) override;
			void NotifyOnDeselectCell(const int column, const int row, IListItem *item) override;
			void NotifyOnActivateCell(const int column, const int row, IListItem *item) override;
			void NotifyOnDeactivateCell(const int column, const int row, IListItem *item) override;
			void NotifyOnEnableCell(const int column, const int row, IListItem *item) override;
			void NotifyOnDisableCell(const int column, const int row, IListItem *item) override;
			void NotifyOnMouseDownCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			void NotifyOnMouseUpCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			void NotifyOnMouseDownCancel() override;
			void NotifyOnCellChange(const int column, const int row, const String &value, bool &allowed) override;
			void NotifyOnSetFocusCell(const int column, const int row) override;
			void NotifyOnKillFocusCell(const int column, const int row) override;

			// Clipboard notifications
			void NotifyOnPasteString(const MessagePasteString &m) override;

			CCustomStringGridService(CCustomStringGrid *control);
		};
	}
}