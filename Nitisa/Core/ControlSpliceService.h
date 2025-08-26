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
#include "FocusedBy.h"
#include "Messages.h"
#include "Strings.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IDialogBox;
	class IForm;

	class CControlSpliceService :public virtual IControlService
	{
	private:
		IControl * m_pControl;
		IControlService * m_pService;
	public:
		// Getters
		PointF getSizeRequested() override;

		// Setters
		void setName(const String &value) override;
		void setForm(IForm *value) override;
		void setParent(IControl *value) override;
		void setTabOrder(const int value) override;
		void setSize(const PointF &value) override;

		// Helpers
		void Release() override;
		void SendChangeNotification() override;
		void AdjustSize() override;
		bool MoveControl(IControl *control, const int before) override;
		void AlignControls() override;
		void InsertControl(IControl *control, const int before) override;

		// State change notifications
		void NotifyOnAttach() override;
		void NotifyOnDetaching() override;
		void NotifyOnDetach() override;
		void NotifyOnFreeResources() override;

		// Component notifications
		void NotifyOnComponentAttach(IComponent *component) override;
		void NotifyOnComponentDetach(IComponent *component) override;
		void NotifyOnComponentChange(IComponent *component) override;

		// Control notifications
		void NotifyOnControlAttach(IControl *control) override;
		void NotifyOnControlDetach(IControl *control) override;
		void NotifyOnControlChange(IControl *control) override;
		void NotifyOnControlSetFocus(IControl *control, const MessageFocus &m) override;
		void NotifyOnControlKillFocus(IControl *control) override;
		void NotifyOnControlSetCaptureKeyboard(IControl *control) override;
		void NotifyOnControlKillCaptureKeyboard(IControl *control) override;
		void NotifyOnControlSetCaptureMouse(IControl *control) override;
		void NotifyOnControlKillCaptureMouse(IControl *control) override;
		void NotifyOnControlSetModal(IControl *control) override;
		void NotifyOnControlKillModal(IControl *control) override;

		// Other input notifications
		void NotifyOnHotkey(const MessageHotkey &m) override;

		// Application notifications
		void NotifyOnApplicationActivate() override;
		void NotifyOnApplicationDeactivate() override;
		void NotifyOnTimeChange() override;
		void NotifyOnInputLanguageChange() override;
		void NotifyOnDisplayChange(const MessageSize &m) override;
		void NotifyOnThemeChange() override;
		void NotifyOnClipboardUpdate() override;
		void NotifyOnTranslateChange() override;

		// Form/window notifications
		void NotifyOnFormActivate(const MessageWindowActivate &m) override;
		void NotifyOnFormDeactivate() override;
		void NotifyOnFormSetFocus() override;
		void NotifyOnFormKillFocus() override;
		void NotifyOnFormEnable() override;
		void NotifyOnFormDisable() override;
		void NotifyOnFormShow() override;
		void NotifyOnFormHide() override;
		void NotifyOnFormMove(const MessagePosition &m) override;
		void NotifyOnFormRestore(const MessageSize &m) override;
		void NotifyOnFormMinimize(const MessageSize &m) override;
		void NotifyOnFormMaximize(const MessageSize &m) override;
		void NotifyOnFormEnterSizeMove() override;
		void NotifyOnFormExitSizeMove() override;

		// Dialog box notifications
		void NotifyOnDialogBoxActivate(IDialogBox *control) override;
		void NotifyOnDialogBoxDeactivate(IDialogBox *control) override;

		// Notifications from parent control
		void NotifyOnParentStyleChange() override;
		void NotifyOnParentFontChange() override;
		void NotifyOnParentResize() override;
		void NotifyOnParentTransform() override;
		void NotifyOnParentTransformControls() override;

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
		void NotifyOnShow() override;
		void NotifyOnHide() override;
		void NotifyOnEnable() override;
		void NotifyOnDisable() override;
		void NotifyOnResize() override;
		void NotifyOnTransform() override;
		void NotifyOnTransformControls() override;
		void NotifyOnStyleChange() override;
		void NotifyOnFontChange() override;
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

		// Interceprors
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

		CControlSpliceService(IControl *control); // Specify control which service should be spliced(replaced) by this one. Control is assumed to be valid, empty value should not be used. Also control should return valid service via QueryService() method. Empty service is unacceptable
		virtual ~CControlSpliceService(); // Restore control original service and destroy itself. If control's service was spliced several times, restore only own splicing changes. It allows to work propertly with multiple splicing
	};
}