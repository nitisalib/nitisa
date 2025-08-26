// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IControlService.h"
#include "../Math/PointF.h"
#include "ComponentService.h"
#include "FocusedBy.h"
#include "Messages.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IControl;

	class CControl;

	class CControlService :public virtual IControlService, public CComponentService
	{
	private:
		CControl *m_pControl;

		void SendChangeNotification(IControl *control);
	public:
		// Getters
		PointF getSizeRequested() override;

		// Setters
		void setParent(IControl *value) override;
		void setTabOrder(const int value) override;
		void setSize(const PointF &value) override;

		// Helpers
		void AdjustSize() override;
		bool MoveControl(IControl *control, const int before) override;
		void SendChangeNotification() override;
		void AlignControls() override;
		void InsertControl(IControl *control, const int before) override;

		// State change notifications
		void NotifyOnFreeResources() override;

		// Notifications from parent control
		void NotifyOnParentStyleChange() override; // Repaint is called automatically
		void NotifyOnParentFontChange() override; // Repaint is called automatically
		void NotifyOnParentResize() override; // Repaint is called automatically
		void NotifyOnParentTransform() override; // Repaint is called automatically
		void NotifyOnParentTransformControls() override; // Repaint is called automatically

		// Notifications from child controls
		void NotifyOnChildStyleChange(IControl *control) override;
		void NotifyOnChildFontChange(IControl *control) override;
		void NotifyOnChildTransform(IControl *control) override;
		void NotifyOnChildResize(IControl *control) override;
		void NotifyOnChildShow(IControl *control) override;
		void NotifyOnChildHide(IControl *control) override;
		void NotifyOnChildAttach(IControl *control) override;
		void NotifyOnChildDetach(IControl *control) override;
		void NotifyOnChildEnable(IControl *control) override;
		void NotifyOnChildDisable(IControl *control) override;
		void NotifyOnChildBeforeTransform(IControl *control, bool &allowed) override;
		void NotifyOnChildBeforeResize(IControl *control, bool &allowed) override;
		void NotifyOnChildBeforeShow(IControl *control, bool &allowed) override;
		void NotifyOnChildBeforeHide(IControl *control, bool &allowed) override;
		void NotifyOnChildBeforeEnable(IControl *control, bool &allowed) override;
		void NotifyOnChildBeforeDisable(IControl *control, bool &allowed) override;

		// State change notifications
		void NotifyOnShow() override; // Repaint is called automatically
		void NotifyOnHide() override; // Repaint is called automatically
		void NotifyOnEnable() override; // Repaint is called automatically
		void NotifyOnDisable() override; // Repaint is called automatically
		void NotifyOnResize() override; // Repaint is called automatically
		void NotifyOnTransform() override; // Repaint is called automatically
		void NotifyOnTransformControls() override; // Repaint is called automatically
		void NotifyOnStyleChange() override; // Repaint is called automatically
		void NotifyOnFontChange() override; // Repaint is called automatically
		void NotifyOnSetModal() override;
		void NotifyOnKillModal() override;
		void NotifyOnSetFocus(const MessageFocus &m) override;
		void NotifyOnKillFocus() override;
		void NotifyOnSetCaptureKeyboard() override;
		void NotifyOnKillCaptureKeyboard() override;
		void NotifyOnSetCaptureMouse() override;
		void NotifyOnKillCaptureMouse() override;
		void NotifyOnActivate() override;
		void NotifyOnDeactivate() override;

		// Paint notifications
		void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;
		void NotifyOnPaintEnd(const MessagePaint &m) override;

		// Keyboard input notifications
		void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;
		void NotifyOnKeyUp(const MessageKey &m, bool &processed) override;
		void NotifyOnChar(const MessageChar &m, bool &processed) override;
		void NotifyOnDeadChar(const MessageChar &m, bool &processed) override;

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

		// Other input notifications
		void NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted) override;

		// Clipboard notifications
		void NotifyOnPasteString(const MessagePasteString &m) override;

		// Interceptors
		bool InterceptSetCursor(IControl *control) override;
		bool InterceptMouseHover(IControl *control) override;
		bool InterceptShowHint(IControl *control, String &hint) override;
		bool InterceptTabOrder() override;
		bool InterceptHotkeys(IControl *control, const MessageHotkey &m) override;
		bool InterceptKeyDown(IControl *control, const MessageKey &m) override;
		bool InterceptKeyUp(IControl *control, const MessageKey &m) override;
		bool InterceptChar(IControl *control, const MessageChar &m) override;
		bool InterceptDeadChar(IControl *control, const MessageChar &m) override;
		bool InterceptMouseMove(IControl *control, const MessageMouse &m) override;
		bool InterceptLeftMouseButtonDown(IControl *control, const MessageMouse &m) override;
		bool InterceptLeftMouseButtonUp(IControl *control, const MessageMouse &m) override;
		bool InterceptLeftMouseButtonDoubleClick(IControl *control, const MessageMouse &m) override;
		bool InterceptMiddleMouseButtonDown(IControl *control, const MessageMouse &m) override;
		bool InterceptMiddleMouseButtonUp(IControl *control, const MessageMouse &m) override;
		bool InterceptMiddleMouseButtonDoubleClick(IControl *control, const MessageMouse &m) override;
		bool InterceptRightMouseButtonDown(IControl *control, const MessageMouse &m) override;
		bool InterceptRightMouseButtonUp(IControl *control, const MessageMouse &m) override;
		bool InterceptRightMouseButtonDoubleClick(IControl *control, const MessageMouse &m) override;
		bool InterceptMouseVerticalWheel(IControl *control, const MessageMouseWheel &m) override;
		bool InterceptMouseHorizontalWheel(IControl *control, const MessageMouseWheel &m) override;
		bool InterceptDropFiles(IControl *control, const MessageDropFiles &m) override;
		bool InterceptFocus(IControl *control, const FocusedBy focused_by) override;

		CControlService(CControl *control);
	};
}