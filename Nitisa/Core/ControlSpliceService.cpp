// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CControlSpliceService::CControlSpliceService(IControl *control) :
		m_pControl{ control }
	{
		m_pService = m_pControl->QueryService();
		m_pControl->setService(this, false);
	}

	CControlSpliceService::~CControlSpliceService()
	{
		if (m_pControl->QueryService() == this)
			m_pControl->setService(m_pService, false);
		else
		{
			CControlSpliceService *s{ cast<CControlSpliceService*>(m_pControl->QueryService()) };
			while (s)
			{
				if (s->m_pService == this)
				{
					s->m_pService = m_pService;
					break;
				}
				s = cast<CControlSpliceService*>(s->m_pService);
			}
		}
	}

	void CControlSpliceService::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	PointF CControlSpliceService::getSizeRequested()
	{
		return m_pService->getSizeRequested();
	}
#pragma endregion

#pragma region Setters
	void CControlSpliceService::setName(const String &value)
	{
		m_pService->setName(value);
	}

	void CControlSpliceService::setForm(IForm *value)
	{
		m_pService->setForm(value);
	}

	void CControlSpliceService::setParent(IControl *value)
	{
		m_pService->setParent(value);
	}

	void CControlSpliceService::setTabOrder(const int value)
	{
		m_pService->setTabOrder(value);
	}

	void CControlSpliceService::setSize(const PointF &value)
	{
		m_pService->setSize(value);
	}
#pragma endregion

#pragma region Helpers
	void CControlSpliceService::SendChangeNotification()
	{
		m_pService->SendChangeNotification();
	}

	void CControlSpliceService::AdjustSize()
	{
		m_pService->AdjustSize();
	}

	bool CControlSpliceService::MoveControl(IControl *control, const int before)
	{
		return m_pService->MoveControl(control, before);
	}

	void CControlSpliceService::AlignControls()
	{
		m_pService->AlignControls();
	}

	void CControlSpliceService::InsertControl(IControl *control, const int before)
	{
		m_pService->InsertControl(control, before);
	}
#pragma endregion

#pragma region State change notifications
	void CControlSpliceService::NotifyOnAttach()
	{
		m_pService->NotifyOnAttach();
	}

	void CControlSpliceService::NotifyOnDetaching()
	{
		m_pService->NotifyOnDetaching();
	}

	void CControlSpliceService::NotifyOnDetach()
	{
		m_pService->NotifyOnDetach();
	}

	void CControlSpliceService::NotifyOnFreeResources()
	{
		m_pService->NotifyOnFreeResources();
	}
#pragma endregion

#pragma region Component notifications
	void CControlSpliceService::NotifyOnComponentAttach(IComponent *component)
	{
		m_pService->NotifyOnComponentAttach(component);
	}

	void CControlSpliceService::NotifyOnComponentDetach(IComponent *component)
	{
		m_pService->NotifyOnComponentDetach(component);
	}

	void CControlSpliceService::NotifyOnComponentChange(IComponent *component)
	{
		m_pService->NotifyOnComponentChange(component);
	}
#pragma endregion

#pragma region Control notifications
	void CControlSpliceService::NotifyOnControlAttach(IControl *control)
	{
		m_pService->NotifyOnControlAttach(control);
	}

	void CControlSpliceService::NotifyOnControlDetach(IControl *control)
	{
		m_pService->NotifyOnControlDetach(control);
	}

	void CControlSpliceService::NotifyOnControlChange(IControl *control)
	{
		m_pService->NotifyOnControlChange(control);
	}

	void CControlSpliceService::NotifyOnControlSetFocus(IControl *control, const MessageFocus &m)
	{
		m_pService->NotifyOnControlSetFocus(control, m);
	}

	void CControlSpliceService::NotifyOnControlKillFocus(IControl *control)
	{
		m_pService->NotifyOnControlKillFocus(control);
	}

	void CControlSpliceService::NotifyOnControlSetCaptureKeyboard(IControl *control)
	{
		m_pService->NotifyOnControlSetCaptureKeyboard(control);
	}

	void CControlSpliceService::NotifyOnControlKillCaptureKeyboard(IControl *control)
	{
		m_pService->NotifyOnControlKillCaptureKeyboard(control);
	}

	void CControlSpliceService::NotifyOnControlSetCaptureMouse(IControl *control)
	{
		m_pService->NotifyOnControlSetCaptureMouse(control);
	}

	void CControlSpliceService::NotifyOnControlKillCaptureMouse(IControl *control)
	{
		m_pService->NotifyOnControlKillCaptureMouse(control);
	}

	void CControlSpliceService::NotifyOnControlSetModal(IControl *control)
	{
		m_pService->NotifyOnControlSetModal(control);
	}

	void CControlSpliceService::NotifyOnControlKillModal(IControl *control)
	{
		m_pService->NotifyOnControlKillModal(control);
	}
#pragma endregion

#pragma region Other input notifications
	void CControlSpliceService::NotifyOnHotkey(const MessageHotkey &m)
	{
		m_pService->NotifyOnHotkey(m);
	}
#pragma endregion

#pragma region Application notifications
	void CControlSpliceService::NotifyOnApplicationActivate()
	{
		m_pService->NotifyOnApplicationActivate();
	}

	void CControlSpliceService::NotifyOnApplicationDeactivate()
	{
		m_pService->NotifyOnApplicationDeactivate();
	}

	void CControlSpliceService::NotifyOnTimeChange()
	{
		m_pService->NotifyOnTimeChange();
	}

	void CControlSpliceService::NotifyOnInputLanguageChange()
	{
		m_pService->NotifyOnInputLanguageChange();
	}

	void CControlSpliceService::NotifyOnDisplayChange(const MessageSize &m)
	{
		m_pService->NotifyOnDisplayChange(m);
	}

	void CControlSpliceService::NotifyOnThemeChange()
	{
		m_pService->NotifyOnThemeChange();
	}

	void CControlSpliceService::NotifyOnClipboardUpdate()
	{
		m_pService->NotifyOnClipboardUpdate();
	}

	void CControlSpliceService::NotifyOnTranslateChange()
	{
		m_pService->NotifyOnTranslateChange();
	}
#pragma endregion

#pragma region Form/window notifications
	void CControlSpliceService::NotifyOnFormActivate(const MessageWindowActivate &m)
	{
		m_pService->NotifyOnFormActivate(m);
	}

	void CControlSpliceService::NotifyOnFormDeactivate()
	{
		m_pService->NotifyOnFormDeactivate();
	}

	void CControlSpliceService::NotifyOnFormSetFocus()
	{
		m_pService->NotifyOnFormSetFocus();
	}

	void CControlSpliceService::NotifyOnFormKillFocus()
	{
		m_pService->NotifyOnFormKillFocus();
	}

	void CControlSpliceService::NotifyOnFormEnable()
	{
		m_pService->NotifyOnFormEnable();
	}

	void CControlSpliceService::NotifyOnFormDisable()
	{
		m_pService->NotifyOnFormDisable();
	}

	void CControlSpliceService::NotifyOnFormShow()
	{
		m_pService->NotifyOnFormShow();
	}

	void CControlSpliceService::NotifyOnFormHide()
	{
		m_pService->NotifyOnFormHide();
	}

	void CControlSpliceService::NotifyOnFormMove(const MessagePosition &m)
	{
		m_pService->NotifyOnFormMove(m);
	}

	void CControlSpliceService::NotifyOnFormRestore(const MessageSize &m)
	{
		m_pService->NotifyOnFormRestore(m);
	}

	void CControlSpliceService::NotifyOnFormMinimize(const MessageSize &m)
	{
		m_pService->NotifyOnFormMinimize(m);
	}

	void CControlSpliceService::NotifyOnFormMaximize(const MessageSize &m)
	{
		m_pService->NotifyOnFormMaximize(m);
	}

	void CControlSpliceService::NotifyOnFormEnterSizeMove()
	{
		m_pService->NotifyOnFormEnterSizeMove();
	}

	void CControlSpliceService::NotifyOnFormExitSizeMove()
	{
		m_pService->NotifyOnFormExitSizeMove();
	}
#pragma endregion

#pragma region Dialog box notifications
	void CControlSpliceService::NotifyOnDialogBoxActivate(IDialogBox *control)
	{
		m_pService->NotifyOnDialogBoxActivate(control);
	}

	void CControlSpliceService::NotifyOnDialogBoxDeactivate(IDialogBox *control)
	{
		m_pService->NotifyOnDialogBoxDeactivate(control);
	}
#pragma endregion

#pragma region Notifications from parent control
	void CControlSpliceService::NotifyOnParentStyleChange()
	{
		m_pService->NotifyOnParentStyleChange();
	}

	void CControlSpliceService::NotifyOnParentFontChange()
	{
		m_pService->NotifyOnParentFontChange();
	}

	void CControlSpliceService::NotifyOnParentResize()
	{
		m_pService->NotifyOnParentResize();
	}

	void CControlSpliceService::NotifyOnParentTransform()
	{
		m_pService->NotifyOnParentTransform();
	}

	void CControlSpliceService::NotifyOnParentTransformControls()
	{
		m_pService->NotifyOnParentTransformControls();
	}
#pragma endregion

#pragma region Notifications from child controls
	void CControlSpliceService::NotifyOnChildStyleChange(IControl *control)
	{
		m_pService->NotifyOnChildStyleChange(control);
	}

	void CControlSpliceService::NotifyOnChildFontChange(IControl *control)
	{
		m_pService->NotifyOnChildFontChange(control);
	}

	void CControlSpliceService::NotifyOnChildTransform(IControl *control)
	{
		m_pService->NotifyOnChildTransform(control);
	}

	void CControlSpliceService::NotifyOnChildResize(IControl *control)
	{
		m_pService->NotifyOnChildResize(control);
	}

	void CControlSpliceService::NotifyOnChildShow(IControl *control)
	{
		m_pService->NotifyOnChildShow(control);
	}

	void CControlSpliceService::NotifyOnChildHide(IControl *control)
	{
		m_pService->NotifyOnChildHide(control);
	}

	void CControlSpliceService::NotifyOnChildAttach(IControl *control)
	{
		m_pService->NotifyOnChildAttach(control);
	}

	void CControlSpliceService::NotifyOnChildDetach(IControl *control)
	{
		m_pService->NotifyOnChildDetach(control);
	}

	void CControlSpliceService::NotifyOnChildEnable(IControl *control)
	{
		m_pService->NotifyOnChildEnable(control);
	}

	void CControlSpliceService::NotifyOnChildDisable(IControl *control)
	{
		m_pService->NotifyOnChildDisable(control);
	}

	void CControlSpliceService::NotifyOnChildBeforeTransform(IControl *control, bool &allowed)
	{
		m_pService->NotifyOnChildBeforeTransform(control, allowed);
	}

	void CControlSpliceService::NotifyOnChildBeforeResize(IControl *control, bool &allowed)
	{
		m_pService->NotifyOnChildBeforeResize(control, allowed);
	}

	void CControlSpliceService::NotifyOnChildBeforeShow(IControl *control, bool &allowed)
	{
		m_pService->NotifyOnChildBeforeShow(control, allowed);
	}

	void CControlSpliceService::NotifyOnChildBeforeHide(IControl *control, bool &allowed)
	{
		m_pService->NotifyOnChildBeforeHide(control, allowed);
	}

	void CControlSpliceService::NotifyOnChildBeforeEnable(IControl *control, bool &allowed)
	{
		m_pService->NotifyOnChildBeforeEnable(control, allowed);
	}

	void CControlSpliceService::NotifyOnChildBeforeDisable(IControl *control, bool &allowed)
	{
		m_pService->NotifyOnChildBeforeDisable(control, allowed);
	}
#pragma endregion

#pragma region State change notifications
	void CControlSpliceService::NotifyOnShow()
	{
		m_pService->NotifyOnShow();
	}

	void CControlSpliceService::NotifyOnHide()
	{
		m_pService->NotifyOnHide();
	}

	void CControlSpliceService::NotifyOnEnable()
	{
		m_pService->NotifyOnEnable();
	}

	void CControlSpliceService::NotifyOnDisable()
	{
		m_pService->NotifyOnDisable();
	}

	void CControlSpliceService::NotifyOnResize()
	{
		m_pService->NotifyOnResize();
	}

	void CControlSpliceService::NotifyOnTransform()
	{
		m_pService->NotifyOnTransform();
	}

	void CControlSpliceService::NotifyOnTransformControls()
	{
		m_pService->NotifyOnTransformControls();
	}

	void CControlSpliceService::NotifyOnStyleChange()
	{
		m_pService->NotifyOnStyleChange();
	}

	void CControlSpliceService::NotifyOnFontChange()
	{
		m_pService->NotifyOnFontChange();
	}

	void CControlSpliceService::NotifyOnSetModal()
	{
		m_pService->NotifyOnSetModal();
	}

	void CControlSpliceService::NotifyOnKillModal()
	{
		m_pService->NotifyOnKillModal();
	}

	void CControlSpliceService::NotifyOnSetFocus(const MessageFocus &m)
	{
		m_pService->NotifyOnSetFocus(m);
	}

	void CControlSpliceService::NotifyOnKillFocus()
	{
		m_pService->NotifyOnKillFocus();
	}

	void CControlSpliceService::NotifyOnSetCaptureKeyboard()
	{
		m_pService->NotifyOnSetCaptureKeyboard();
	}

	void CControlSpliceService::NotifyOnKillCaptureKeyboard()
	{
		m_pService->NotifyOnKillCaptureKeyboard();
	}

	void CControlSpliceService::NotifyOnSetCaptureMouse()
	{
		m_pService->NotifyOnSetCaptureMouse();
	}

	void CControlSpliceService::NotifyOnKillCaptureMouse()
	{
		m_pService->NotifyOnKillCaptureMouse();
	}

	void CControlSpliceService::NotifyOnActivate()
	{
		m_pService->NotifyOnActivate();
	}

	void CControlSpliceService::NotifyOnDeactivate()
	{
		m_pService->NotifyOnDeactivate();
	}
#pragma endregion

#pragma region Paint notifications
	void CControlSpliceService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
	{
		m_pService->NotifyOnPaint(m, draw_children);
	}

	void CControlSpliceService::NotifyOnPaintEnd(const MessagePaint &m)
	{
		m_pService->NotifyOnPaintEnd(m);
	}
#pragma endregion

#pragma region Keyboard input notifications
	void CControlSpliceService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
	{
		m_pService->NotifyOnKeyDown(m, processed);
	}

	void CControlSpliceService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
	{
		m_pService->NotifyOnKeyUp(m, processed);
	}

	void CControlSpliceService::NotifyOnChar(const MessageChar &m, bool &processed)
	{
		m_pService->NotifyOnChar(m, processed);
	}

	void CControlSpliceService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
	{
		m_pService->NotifyOnDeadChar(m, processed);
	}
#pragma endregion

#pragma region Mouse input notifications
	void CControlSpliceService::NotifyOnMouseHover(const MessagePosition &m)
	{
		m_pService->NotifyOnMouseHover(m);
	}

	void CControlSpliceService::NotifyOnMouseLeave()
	{
		m_pService->NotifyOnMouseLeave();
	}

	void CControlSpliceService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
	{
		m_pService->NotifyOnMouseMove(m, processed);
	}

	void CControlSpliceService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
	{
		m_pService->NotifyOnLeftMouseButtonDown(m, processed);
	}

	void CControlSpliceService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
	{
		m_pService->NotifyOnLeftMouseButtonUp(m, processed);
	}

	void CControlSpliceService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
	{
		m_pService->NotifyOnLeftMouseButtonDoubleClick(m, processed);
	}

	void CControlSpliceService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
	{
		m_pService->NotifyOnRightMouseButtonDown(m, processed);
	}

	void CControlSpliceService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
	{
		m_pService->NotifyOnRightMouseButtonUp(m, processed);
	}

	void CControlSpliceService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
	{
		m_pService->NotifyOnRightMouseButtonDoubleClick(m, processed);
	}

	void CControlSpliceService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
	{
		m_pService->NotifyOnMiddleMouseButtonDown(m, processed);
	}

	void CControlSpliceService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
	{
		m_pService->NotifyOnMiddleMouseButtonUp(m, processed);
	}

	void CControlSpliceService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
	{
		m_pService->NotifyOnMiddleMouseButtonDoubleClick(m, processed);
	}

	void CControlSpliceService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
	{
		m_pService->NotifyOnMouseVerticalWheel(m, processed);
	}

	void CControlSpliceService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
	{
		m_pService->NotifyOnMouseHorizontalWheel(m, processed);
	}
#pragma endregion

#pragma region Other input notifications
	void CControlSpliceService::NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted)
	{
		m_pService->NotifyOnDropFiles(m, processed, accepted);
	}
#pragma endregion

#pragma region Clipboard notifications
	void CControlSpliceService::NotifyOnPasteString(const MessagePasteString &m)
	{
		m_pService->NotifyOnPasteString(m);
	}
#pragma endregion

#pragma region Interceprors
	bool CControlSpliceService::InterceptSetCursor(IControl *control)
	{
		return m_pService->InterceptSetCursor(control);
	}

	bool CControlSpliceService::InterceptMouseHover(IControl *control)
	{
		return m_pService->InterceptMouseHover(control);
	}

	bool CControlSpliceService::InterceptShowHint(IControl *control, String &hint)
	{
		return m_pService->InterceptShowHint(control, hint);
	}

	bool CControlSpliceService::InterceptTabOrder()
	{
		return m_pService->InterceptTabOrder();
	}

	bool CControlSpliceService::InterceptHotkeys(IControl *control, const MessageHotkey &m)
	{
		return m_pService->InterceptHotkeys(control, m);
	}

	bool CControlSpliceService::InterceptKeyDown(IControl *control, const MessageKey &m)
	{
		return m_pService->InterceptKeyDown(control, m);
	}

	bool CControlSpliceService::InterceptKeyUp(IControl *control, const MessageKey &m)
	{
		return m_pService->InterceptKeyUp(control, m);
	}

	bool CControlSpliceService::InterceptChar(IControl *control, const MessageChar &m)
	{
		return m_pService->InterceptChar(control, m);
	}

	bool CControlSpliceService::InterceptDeadChar(IControl *control, const MessageChar &m)
	{
		return m_pService->InterceptDeadChar(control, m);
	}

	bool CControlSpliceService::InterceptMouseMove(IControl *control, const MessageMouse &m)
	{
		return m_pService->InterceptMouseMove(control, m);
	}

	bool CControlSpliceService::InterceptLeftMouseButtonDown(IControl *control, const MessageMouse &m)
	{
		return m_pService->InterceptLeftMouseButtonDown(control, m);
	}

	bool CControlSpliceService::InterceptLeftMouseButtonUp(IControl *control, const MessageMouse &m)
	{
		return m_pService->InterceptLeftMouseButtonUp(control, m);
	}

	bool CControlSpliceService::InterceptLeftMouseButtonDoubleClick(IControl *control, const MessageMouse &m)
	{
		return m_pService->InterceptLeftMouseButtonDoubleClick(control, m);
	}

	bool CControlSpliceService::InterceptMiddleMouseButtonDown(IControl *control, const MessageMouse &m)
	{
		return m_pService->InterceptMiddleMouseButtonDown(control, m);
	}

	bool CControlSpliceService::InterceptMiddleMouseButtonUp(IControl *control, const MessageMouse &m)
	{
		return m_pService->InterceptMiddleMouseButtonUp(control, m);
	}

	bool CControlSpliceService::InterceptMiddleMouseButtonDoubleClick(IControl *control, const MessageMouse &m)
	{
		return m_pService->InterceptMiddleMouseButtonDoubleClick(control, m);
	}

	bool CControlSpliceService::InterceptRightMouseButtonDown(IControl *control, const MessageMouse &m)
	{
		return m_pService->InterceptRightMouseButtonDown(control, m);
	}

	bool CControlSpliceService::InterceptRightMouseButtonUp(IControl *control, const MessageMouse &m)
	{
		return m_pService->InterceptRightMouseButtonUp(control, m);
	}

	bool CControlSpliceService::InterceptRightMouseButtonDoubleClick(IControl *control, const MessageMouse &m)
	{
		return m_pService->InterceptRightMouseButtonDoubleClick(control, m);
	}

	bool CControlSpliceService::InterceptMouseVerticalWheel(IControl *control, const MessageMouseWheel &m)
	{
		return m_pService->InterceptMouseVerticalWheel(control, m);
	}

	bool CControlSpliceService::InterceptMouseHorizontalWheel(IControl *control, const MessageMouseWheel &m)
	{
		return m_pService->InterceptMouseHorizontalWheel(control, m);
	}

	bool CControlSpliceService::InterceptDropFiles(IControl *control, const MessageDropFiles &m)
	{
		return m_pService->InterceptDropFiles(control, m);
	}

	bool CControlSpliceService::InterceptFocus(IControl *control, const FocusedBy focused_by)
	{
		return m_pService->InterceptFocus(control, focused_by);
	}
#pragma endregion
}