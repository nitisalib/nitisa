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
#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	namespace standard
	{
		class CEditCalc;

		class CEditCalcService :public CControlService
		{
		private:
			CEditCalc *m_pControl;

			void MouseUp(const PointF &pos);
			PointF LocalToTextInput(const PointF &pos);
		public:
			// Notifications from parent control
			void NotifyOnParentStyleChange() override;
			void NotifyOnParentFontChange() override;

			// State change notifications
			void NotifyOnFreeResources() override;
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnAttach() override;
			void NotifyOnResize() override;
			void NotifyOnStyleChange() override;
			void NotifyOnFontChange() override;
			void NotifyOnSetFocus(const MessageFocus &m) override;
			void NotifyOnKillFocus() override;
			void NotifyOnMouseHover(const MessagePosition &m) override;
			void NotifyOnMouseLeave() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			// Input notifications
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;
			void NotifyOnKeyUp(const MessageKey &m, bool &processed) override;
			void NotifyOnChar(const MessageChar &m, bool &processed) override;
			void NotifyOnDeadChar(const MessageChar &m, bool &processed) override;
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
			void NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted) override;

			// Clipboard notifications
			void NotifyOnPasteString(const MessagePasteString &m) override;

			CEditCalcService(CEditCalc *control);
		};
	}
}