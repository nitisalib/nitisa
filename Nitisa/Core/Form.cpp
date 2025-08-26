// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CForm::FormHotkey::FormHotkey(const nitisa::Key key, const bool ctrl, const bool alt, const bool shift, const bool down, IComponent *component, IControl *control) :
		Hotkey{ key, ctrl, alt, shift, down },
		Component{ component },
		Control{ control },
		RefCount{ 1 }
	{

	}

#pragma region CWindowListener
	CForm::CWindowListener::CWindowListener(CForm *form) :
		m_pForm{ form }
	{

	}

	void CForm::CWindowListener::OnCreate()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnCreate();
	}

	void CForm::CWindowListener::OnDestroy()
	{
		m_pForm->LockRepaint();
		if (m_pForm->m_pRenderer)
		{
			if (m_pForm->m_pRenderer->Window != m_pForm->m_pWindow)
			{
				bool found{ false };
				for (int i = 0; i < Application->getWindowCount(); i++)
					if (Application->getWindow(i) == m_pForm->m_pRenderer->Window)
					{
						found = true;
						break;
					}
				m_pForm->m_pRenderer->setWindow(m_pForm->m_pWindow, true, !found);
			}
			m_pForm->m_pRenderer->Activate();
		}
		m_pForm->QueryService()->NotifyOnDestroy();
		if (m_pForm->OnDestroy)
			m_pForm->OnDestroy(m_pForm);
		m_pForm->DeleteControls();
		m_pForm->DeleteComponents();
		CNotifier::FreeResources(m_pForm);
		if (m_pForm->m_pRenderer && m_pForm->m_pRenderer->RefCount <= 1)
			m_pForm->m_pRenderer->setWindow(nullptr, false, false);
		m_pForm->m_pWindow = nullptr;
	}

	void CForm::CWindowListener::OnActivate(const MessageWindowActivate &m)
	{
		CLockRepaint lock{ m_pForm };
		CNotifier::FormActivate(m_pForm, m);
	}

	void CForm::CWindowListener::OnDeactivate()
	{
		CLockRepaint lock{ m_pForm };
		if (m_pForm->m_hTimerHintDelay)
		{
			m_pForm->m_pWindow->DeleteTimer(m_pForm->m_hTimerHintDelay);
			m_pForm->m_hTimerHintDelay = nullptr;
		}
		m_pForm->getHint()->Hide(true);
		m_pForm->setActiveControl(nullptr);
		CNotifier::FormDeactivate(m_pForm);
	}

	void CForm::CWindowListener::OnSetFocus()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->m_pFocusedControl = m_pForm->m_pFocusedControlOld;
		m_pForm->m_pFocusedControlOld = nullptr;
		if (m_pForm->m_pFocusedControl)
			CNotifier::ControlSetFocus(m_pForm, m_pForm->m_pFocusedControl, nullptr, FocusedBy::Refocus);
		CNotifier::FormSetFocus(m_pForm);
	}

	void CForm::CWindowListener::OnKillFocus()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		if (m_pForm->m_pFocusedControl)
		{
			CNotifier::ControlKillFocus(m_pForm, m_pForm->m_pFocusedControl);
			m_pForm->m_pFocusedControlOld = m_pForm->m_pFocusedControl;
			m_pForm->m_pFocusedControl = nullptr;
		}
		CNotifier::FormKillFocus(m_pForm);
	}

	void CForm::CWindowListener::OnEnable()
	{
		CLockRepaint lock{ m_pForm };
		CNotifier::FormEnable(m_pForm);
	}

	void CForm::CWindowListener::OnDisable()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		CNotifier::FormDisable(m_pForm);
	}

	void CForm::CWindowListener::OnClose(CloseAction &action)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnClose(action);
		if (m_pForm->OnClose)
			m_pForm->OnClose(m_pForm, action);
		if (action == CloseAction::Free && m_pForm->m_pListener)
			m_pForm->m_pListener->OnClose(m_pForm);
	}

	void CForm::CWindowListener::OnShow()
	{
		CLockRepaint lock{ m_pForm };
		CNotifier::FormShow(m_pForm);
	}

	void CForm::CWindowListener::OnHide()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		CNotifier::FormHide(m_pForm);
	}

	void CForm::CWindowListener::OnActivateApp()
	{
		CLockRepaint lock{ m_pForm };
		CNotifier::ApplicationActivate(m_pForm);
	}

	void CForm::CWindowListener::OnDeactivateApp()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		CNotifier::ApplicationDeactivate(m_pForm);
	}

	void CForm::CWindowListener::OnMove(const MessagePosition &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		CNotifier::FormMove(m_pForm, m);
	}

	void CForm::CWindowListener::OnRestore(const MessageSize &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		m_pForm->QueryService()->AlignControls();
		CNotifier::ParentResize(m_pForm);
		CNotifier::FormRestore(m_pForm, m);
		if (m_pForm->m_pListener)
			m_pForm->m_pListener->OnRestore(m_pForm);
	}

	void CForm::CWindowListener::OnMinimize(const MessageSize &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		CNotifier::FormMinimize(m_pForm, m);
		if (m_pForm->m_pListener)
			m_pForm->m_pListener->OnMinimize(m_pForm);
	}

	void CForm::CWindowListener::OnMaximize(const MessageSize &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		m_pForm->QueryService()->AlignControls();
		CNotifier::ParentResize(m_pForm);
		CNotifier::FormMaximize(m_pForm, m);
		if (m_pForm->m_pListener)
			m_pForm->m_pListener->OnMaximize(m_pForm);
	}

	void CForm::CWindowListener::OnResizing(const MessageWindowResizing &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		m_pForm->QueryService()->AlignControls();
		CNotifier::ParentResize(m_pForm);
		m_pForm->QueryService()->NotifyOnResizing(m);
		if (m_pForm->OnResizing)
			m_pForm->OnResizing(m_pForm, m);
	}

	void CForm::CWindowListener::OnMoving(const MessageRect &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		m_pForm->QueryService()->NotifyOnMoving(m);
		if (m_pForm->OnMoving)
			m_pForm->OnMoving(m_pForm, m);
	}

	void CForm::CWindowListener::OnEnterSizeMove()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->setActiveControl(nullptr);
		m_pForm->m_sOldClientRect = m_pForm->m_pWindow->getClientRect();
		CNotifier::FormEnterSizeMove(m_pForm);
	}

	void CForm::CWindowListener::OnExitSizeMove()
	{
		CLockRepaint lock{ m_pForm };
		Rect client{ m_pForm->m_pWindow->getClientRect() };
		if (m_pForm->m_sOldClientRect != client)
		{
			m_pForm->QueryService()->AlignControls();
			CNotifier::ParentResize(m_pForm);
		}
		CNotifier::FormExitSizeMove(m_pForm);
	}

	void CForm::CWindowListener::OnKeyDown(const MessageKey &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->m_bTabDownProcessed = false;
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		// Captured control
		IControl *capture{ m_pForm->getCaptureKeyboardControl() }, *modal{ m_pForm->getModalControl() };
		MessageKey msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnKeyDown(msg, processed);
			if (capture->OnKeyDown)
				capture->OnKeyDown(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		if (!processed && (!m_pForm->m_pFocusedControl || !m_pForm->m_pFocusedControl->isWantTabs()) && m_pForm->m_bFocusByTab && m_pForm->ProcessTabDown(msg.Key))
			m_pForm->m_bTabDownProcessed = true;
		// Focused control (if no modal on)
		else if (!processed && m_pForm->m_pFocusedControl && m_pForm->m_pFocusedControl != capture && (!modal || m_pForm->m_pFocusedControl == modal || modal->hasChild(m_pForm->m_pFocusedControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptKeyDown(m_pForm->m_pFocusedControl->getParent(), m_pForm->m_pFocusedControl, msg))
			{
				IControl *control{ m_pForm->m_pFocusedControl };
				msg.Target = control;
				control->QueryService()->NotifyOnKeyDown(msg, processed);
				if (control->OnKeyDown)
					control->OnKeyDown(m_pForm->m_pFocusedControl, msg, processed);
				// Event bubbling
				while (!processed && (control = control->getParent()))
					if (control->isAcceptBubbledEvents())
					{
						control->QueryService()->NotifyOnKeyDown(msg, processed);
						if (control->OnKeyDown)
							control->OnKeyDown(control, msg, processed);
					}
			}
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pFocusedControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnKeyDown(msg, processed);
			if (modal->OnKeyDown)
				modal->OnKeyDown(modal, msg, processed);
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnKeyDown(msg, processed);
			if (m_pForm->m_pInputControl->OnKeyDown)
				m_pForm->m_pInputControl->OnKeyDown(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->ProcessDownHotkeys(msg.Key);
		m_pForm->QueryService()->NotifyOnKeyDown(msg);
		if (m_pForm->OnKeyDown)
			m_pForm->OnKeyDown(m_pForm, msg);
	}

	void CForm::CWindowListener::OnKeyUp(const MessageKey &m)
	{
		CLockRepaint lock{ m_pForm };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageKey msg{ m };
		if (!m_pForm->m_bTabDownProcessed)
		{
			// Captured control
			IControl *capture{ m_pForm->getCaptureKeyboardControl() }, *modal{ m_pForm->getModalControl() };
			if (capture)
			{
				msg.Target = capture;
				capture->QueryService()->NotifyOnKeyUp(msg, processed);
				if (capture->OnKeyUp)
					capture->OnKeyUp(capture, msg, processed);
				send_to_input = send_to_input && !processed;
			}
			// Focused control
			if (!processed && m_pForm->m_pFocusedControl && m_pForm->m_pFocusedControl != capture && (!modal || m_pForm->m_pFocusedControl == modal || modal->hasChild(m_pForm->m_pFocusedControl)))
			{
				if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptKeyUp(m_pForm->m_pFocusedControl->getParent(), m_pForm->m_pFocusedControl, msg))
				{
					IControl *control{ m_pForm->m_pFocusedControl };
					msg.Target = control;
					control->QueryService()->NotifyOnKeyUp(msg, processed);
					if (control->OnKeyUp)
						control->OnKeyUp(m_pForm->m_pFocusedControl, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnKeyUp(msg, processed);
							if (control->OnKeyUp)
								control->OnKeyUp(control, msg, processed);
						}
				}
			}
			// Modal control
			if (!processed && modal && modal != capture && modal != m_pForm->m_pFocusedControl)
			{
				msg.Target = modal;
				modal->QueryService()->NotifyOnKeyUp(msg, processed);
				if (modal->OnKeyUp)
					modal->OnKeyUp(modal, msg, processed);
			}
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnKeyUp(msg, processed);
			if (m_pForm->m_pInputControl->OnKeyUp)
				m_pForm->m_pInputControl->OnKeyUp(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->ProcessUpHotkeys(msg.Key);
		m_pForm->QueryService()->NotifyOnKeyUp(msg);
		if (m_pForm->OnKeyUp)
			m_pForm->OnKeyUp(m_pForm, msg);
	}

	void CForm::CWindowListener::OnChar(const MessageChar &m)
	{
		CLockRepaint lock{ m_pForm };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageChar msg{ m };
		if (!m_pForm->m_bTabDownProcessed)
		{
			// Captured control
			IControl *capture{ m_pForm->getCaptureKeyboardControl() }, *modal{ m_pForm->getModalControl() };
			if (capture)
			{
				msg.Target = capture;
				capture->QueryService()->NotifyOnChar(msg, processed);
				if (capture->OnChar)
					capture->OnChar(capture, msg, processed);
				send_to_input = send_to_input && !processed;
			}
			// Focused control
			if (!processed && m_pForm->m_pFocusedControl && m_pForm->m_pFocusedControl != capture && (!modal || m_pForm->m_pFocusedControl == modal || modal->hasChild(m_pForm->m_pFocusedControl)))
			{
				if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptChar(m_pForm->m_pFocusedControl->getParent(), m_pForm->m_pFocusedControl, msg))
				{
					IControl *control{ m_pForm->m_pFocusedControl };
					msg.Target = control;
					control->QueryService()->NotifyOnChar(msg, processed);
					if (control->OnChar)
						control->OnChar(m_pForm->m_pFocusedControl, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnChar(msg, processed);
							if (control->OnChar)
								control->OnChar(control, msg, processed);
						}
				}
			}
			// Modal control
			if (!processed && modal && modal != capture && modal != m_pForm->m_pFocusedControl)
			{
				msg.Target = modal;
				modal->QueryService()->NotifyOnChar(msg, processed);
				if (modal->OnChar)
					modal->OnChar(modal, msg, processed);
			}
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnChar(msg, processed);
			if (m_pForm->m_pInputControl->OnChar)
				m_pForm->m_pInputControl->OnChar(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnChar(msg);
		if (m_pForm->OnChar)
			m_pForm->OnChar(m_pForm, msg);
	}

	void CForm::CWindowListener::OnDeadChar(const MessageChar &m)
	{
		CLockRepaint lock{ m_pForm };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageChar msg{ m };
		if (!m_pForm->m_bTabDownProcessed)
		{
			// Captured control
			IControl *capture{ m_pForm->getCaptureKeyboardControl() }, *modal{ m_pForm->getModalControl() };
			if (capture)
			{
				msg.Target = capture;
				capture->QueryService()->NotifyOnDeadChar(msg, processed);
				if (capture->OnDeadChar)
					capture->OnDeadChar(capture, msg, processed);
				send_to_input = send_to_input && !processed;
			}
			// Focused control
			if (!processed && m_pForm->m_pFocusedControl && m_pForm->m_pFocusedControl != capture && (!modal || m_pForm->m_pFocusedControl == modal || modal->hasChild(m_pForm->m_pFocusedControl)))
			{
				if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptDeadChar(m_pForm->m_pFocusedControl->getParent(), m_pForm->m_pFocusedControl, msg))
				{
					IControl *control{ m_pForm->m_pFocusedControl };
					msg.Target = control;
					control->QueryService()->NotifyOnDeadChar(msg, processed);
					if (control->OnDeadChar)
						control->OnDeadChar(m_pForm->m_pFocusedControl, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnDeadChar(msg, processed);
							if (control->OnDeadChar)
								control->OnDeadChar(control, msg, processed);
						}
				}
			}
			// Modal control
			if (!processed && modal && modal != capture && modal != m_pForm->m_pFocusedControl)
			{
				msg.Target = modal;
				modal->QueryService()->NotifyOnDeadChar(msg, processed);
				if (modal->OnDeadChar)
					modal->OnDeadChar(modal, msg, processed);
			}
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnDeadChar(msg, processed);
			if (m_pForm->m_pInputControl->OnDeadChar)
				m_pForm->m_pInputControl->OnDeadChar(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnDeadChar(msg);
		if (m_pForm->OnDeadChar)
			m_pForm->OnDeadChar(m_pForm, msg);
	}

	void CForm::CWindowListener::OnHScroll(const MessageWindowScroll &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnHScroll(m);
		if (m_pForm->OnHScroll)
			m_pForm->OnHScroll(m_pForm, m);
	}

	void CForm::CWindowListener::OnVScroll(const MessageWindowScroll &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnVScroll(m);
		if (m_pForm->OnVScroll)
			m_pForm->OnVScroll(m_pForm, m);
	}

	void CForm::CWindowListener::OnGestureZoom(const MessagePosition &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnGestureZoom(m);
		if (m_pForm->OnGestureZoom)
			m_pForm->OnGestureZoom(m_pForm, m);
	}

	void CForm::CWindowListener::OnGesturePan(const MessagePosition &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnGesturePan(m);
		if (m_pForm->OnGesturePan)
			m_pForm->OnGesturePan(m_pForm, m);
	}

	void CForm::CWindowListener::OnGestureRotate(const MessagePosition &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnGestureRotate(m);
		if (m_pForm->OnGestureRotate)
			m_pForm->OnGestureRotate(m_pForm, m);
	}

	void CForm::CWindowListener::OnGestureTwoFingerTap(const MessagePosition &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnGestureTwoFingerTap(m);
		if (m_pForm->OnGestureTwoFingerTap)
			m_pForm->OnGestureTwoFingerTap(m_pForm, m);
	}

	void CForm::CWindowListener::OnGesturePressAndTap(const MessagePosition &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnGesturePressAndTap(m);
		if (m_pForm->OnGesturePressAndTap)
			m_pForm->OnGesturePressAndTap(m_pForm, m);
	}

	void CForm::CWindowListener::OnGestureNotify()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnGestureNotify();
		if (m_pForm->OnGestureNotify)
			m_pForm->OnGestureNotify(m_pForm);
	}

	void CForm::CWindowListener::OnMouseMove(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		if (!m_pForm->m_bIsTrackingMouseLeave)
		{
			m_pForm->m_pWindow->QueryService()->StartTrackMouseLeave();
			m_pForm->m_bIsTrackingMouseLeave = true;
		}
		m_pForm->UpdateHoveredControl();
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouse msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnMouseMove(msg, processed);
			if (capture->OnMouseMove)
				capture->OnMouseMove(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture && (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptMouseMove(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
			{
				IControl *control{ m_pForm->m_pHoveredControl };
				msg.Target = control;
				control->QueryService()->NotifyOnMouseMove(msg, processed);
				if (control->OnMouseMove)
					control->OnMouseMove(control, msg, processed);
				// Event bubbling
				while (!processed && (control = control->getParent()))
					if (control->isAcceptBubbledEvents())
					{
						control->QueryService()->NotifyOnMouseMove(msg, processed);
						if (control->OnMouseMove)
							control->OnMouseMove(control, msg, processed);
					}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnMouseMove(msg, processed);
			if (modal->OnMouseMove)
				modal->OnMouseMove(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnMouseMove(msg, processed);
			if (m_pForm->m_pInputControl->OnMouseMove)
				m_pForm->m_pInputControl->OnMouseMove(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnMouseMove(msg);
		if (m_pForm->OnMouseMove)
			m_pForm->OnMouseMove(m_pForm, msg);
	}

	void CForm::CWindowListener::OnLeftMouseButtonDown(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouse msg{ m };
		if (m_pForm->getCaptureMouseControl())
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnLeftMouseButtonDown(msg, processed);
			if (capture->OnLeftMouseButtonDown)
				capture->OnLeftMouseButtonDown(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Dialog box
		if (!processed)
			ActivateDialogBox(m_pForm->m_pHoveredControl);
		// Active control
		if (!processed && m_pForm->m_pActiveControl && m_pForm->m_pActiveControl != m_pForm->m_pHoveredControl)
			m_pForm->setActiveControl(nullptr);
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture)
		{
			if (m_pForm->m_bFocusByLMB && m_pForm->m_pHoveredControl->isFocusByMouse())
			{
				IControl *new_focused_control{ m_pForm->InterceptFocus(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, FocusedBy::LeftMouse) };
				m_pForm->setFocusedControl(new_focused_control, FocusedBy::LeftMouse, false);
			}
			if (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl))
			{
				if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptLeftMouseButtonDown(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
				{
					IControl *control{ m_pForm->m_pHoveredControl };
					if (control)
					{
						msg.Target = control;
						control->QueryService()->NotifyOnLeftMouseButtonDown(msg, processed);
						if (control->OnLeftMouseButtonDown)
							control->OnLeftMouseButtonDown(control, msg, processed);
						// Event bubbling
						while (!processed && (control = control->getParent()))
							if (control->isAcceptBubbledEvents())
							{
								control->QueryService()->NotifyOnLeftMouseButtonDown(msg, processed);
								if (control->OnLeftMouseButtonDown)
									control->OnLeftMouseButtonDown(control, msg, processed);
							}
					}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnLeftMouseButtonDown(msg, processed);
			if (modal->OnLeftMouseButtonDown)
				modal->OnLeftMouseButtonDown(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnLeftMouseButtonDown(msg, processed);
			if (m_pForm->m_pInputControl->OnLeftMouseButtonDown)
				m_pForm->m_pInputControl->OnLeftMouseButtonDown(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnLeftMouseButtonDown(msg);
		if (m_pForm->OnLeftMouseButtonDown)
			m_pForm->OnLeftMouseButtonDown(m_pForm, msg);
	}

	void CForm::CWindowListener::OnLeftMouseButtonUp(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouse msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnLeftMouseButtonUp(msg, processed);
			if (capture->OnLeftMouseButtonUp)
				capture->OnLeftMouseButtonUp(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture && (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptLeftMouseButtonUp(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
			{
				IControl *control{ m_pForm->m_pHoveredControl };
				if (control)
				{
					msg.Target = control;
					control->QueryService()->NotifyOnLeftMouseButtonUp(msg, processed);
					if (control->OnLeftMouseButtonUp)
						control->OnLeftMouseButtonUp(control, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnLeftMouseButtonUp(msg, processed);
							if (control->OnLeftMouseButtonUp)
								control->OnLeftMouseButtonUp(control, msg, processed);
						}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnLeftMouseButtonUp(msg, processed);
			if (modal->OnLeftMouseButtonUp)
				modal->OnLeftMouseButtonUp(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnLeftMouseButtonUp(msg, processed);
			if (m_pForm->m_pInputControl->OnLeftMouseButtonUp)
				m_pForm->m_pInputControl->OnLeftMouseButtonUp(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnLeftMouseButtonUp(msg);
		if (m_pForm->OnLeftMouseButtonUp)
			m_pForm->OnLeftMouseButtonUp(m_pForm, msg);
	}

	void CForm::CWindowListener::OnLeftMouseButtonDoubleClick(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouse msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnLeftMouseButtonDoubleClick(msg, processed);
			if (capture->OnLeftMouseButtonDoubleClick)
				capture->OnLeftMouseButtonDoubleClick(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture && (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptLeftMouseButtonDoubleClick(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
			{
				IControl *control{ m_pForm->m_pHoveredControl };
				if (control)
				{
					msg.Target = control;
					control->QueryService()->NotifyOnLeftMouseButtonDoubleClick(msg, processed);
					if (control->OnLeftMouseButtonDoubleClick)
						control->OnLeftMouseButtonDoubleClick(control, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnLeftMouseButtonDoubleClick(msg, processed);
							if (control->OnLeftMouseButtonDoubleClick)
								control->OnLeftMouseButtonDoubleClick(control, msg, processed);
						}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnLeftMouseButtonDoubleClick(msg, processed);
			if (modal->OnLeftMouseButtonDoubleClick)
				modal->OnLeftMouseButtonDoubleClick(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnLeftMouseButtonDoubleClick(msg, processed);
			if (m_pForm->m_pInputControl->OnLeftMouseButtonDoubleClick)
				m_pForm->m_pInputControl->OnLeftMouseButtonDoubleClick(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnLeftMouseButtonDoubleClick(msg);
		if (m_pForm->OnLeftMouseButtonDoubleClick)
			m_pForm->OnLeftMouseButtonDoubleClick(m_pForm, msg);
	}

	void CForm::CWindowListener::OnRightMouseButtonDown(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouse msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnRightMouseButtonDown(msg, processed);
			if (capture->OnRightMouseButtonDown)
				capture->OnRightMouseButtonDown(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Dialog box
		if (!processed)
			ActivateDialogBox(m_pForm->m_pHoveredControl);
		// Active control
		if (!processed && m_pForm->m_pActiveControl && m_pForm->m_pActiveControl != m_pForm->m_pHoveredControl)
			m_pForm->setActiveControl(nullptr);
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture)
		{
			if (m_pForm->m_bFocusByRMB && m_pForm->m_pHoveredControl->isFocusByMouse())
			{
				IControl *new_focused_control{ m_pForm->InterceptFocus(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, FocusedBy::RightMouse) };
				m_pForm->setFocusedControl(new_focused_control, FocusedBy::RightMouse, false);
			}
			if (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl))
			{
				if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptRightMouseButtonDown(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
				{
					IControl *control{ m_pForm->m_pHoveredControl };
					if (control)
					{
						msg.Target = control;
						control->QueryService()->NotifyOnRightMouseButtonDown(msg, processed);
						if (control->OnRightMouseButtonDown)
							control->OnRightMouseButtonDown(control, msg, processed);
						// Event bubbling
						while (!processed && (control = control->getParent()))
							if (control->isAcceptBubbledEvents())
							{
								control->QueryService()->NotifyOnRightMouseButtonDown(msg, processed);
								if (control->OnRightMouseButtonDown)
									control->OnRightMouseButtonDown(control, msg, processed);
							}
					}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnRightMouseButtonDown(msg, processed);
			if (modal->OnRightMouseButtonDown)
				modal->OnRightMouseButtonDown(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnRightMouseButtonDown(msg, processed);
			if (m_pForm->m_pInputControl->OnRightMouseButtonDown)
				m_pForm->m_pInputControl->OnRightMouseButtonDown(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnRightMouseButtonDown(msg);
		if (m_pForm->OnRightMouseButtonDown)
			m_pForm->OnRightMouseButtonDown(m_pForm, msg);
	}

	void CForm::CWindowListener::OnRightMouseButtonUp(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouse msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnRightMouseButtonUp(msg, processed);
			if (capture->OnRightMouseButtonUp)
				capture->OnRightMouseButtonUp(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture && (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptRightMouseButtonUp(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
			{
				IControl *control{ m_pForm->m_pHoveredControl };
				if (control)
				{
					msg.Target = control;
					control->QueryService()->NotifyOnRightMouseButtonUp(msg, processed);
					if (control->OnRightMouseButtonUp)
						control->OnRightMouseButtonUp(control, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnRightMouseButtonUp(msg, processed);
							if (control->OnRightMouseButtonUp)
								control->OnRightMouseButtonUp(control, msg, processed);
						}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnRightMouseButtonUp(msg, processed);
			if (modal->OnRightMouseButtonUp)
				modal->OnRightMouseButtonUp(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnRightMouseButtonUp(msg, processed);
			if (m_pForm->m_pInputControl->OnRightMouseButtonUp)
				m_pForm->m_pInputControl->OnRightMouseButtonUp(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnRightMouseButtonUp(msg);
		if (m_pForm->OnRightMouseButtonUp)
			m_pForm->OnRightMouseButtonUp(m_pForm, msg);
	}

	void CForm::CWindowListener::OnRightMouseButtonDoubleClick(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouse msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnRightMouseButtonDoubleClick(msg, processed);
			if (capture->OnRightMouseButtonDoubleClick)
				capture->OnRightMouseButtonDoubleClick(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture && (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptRightMouseButtonDoubleClick(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
			{
				IControl *control{ m_pForm->m_pHoveredControl };
				if (control)
				{
					msg.Target = control;
					control->QueryService()->NotifyOnRightMouseButtonDoubleClick(msg, processed);
					if (control->OnRightMouseButtonDoubleClick)
						control->OnRightMouseButtonDoubleClick(control, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnRightMouseButtonDoubleClick(msg, processed);
							if (control->OnRightMouseButtonDoubleClick)
								control->OnRightMouseButtonDoubleClick(control, msg, processed);
						}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnRightMouseButtonDoubleClick(msg, processed);
			if (modal->OnRightMouseButtonDoubleClick)
				modal->OnRightMouseButtonDoubleClick(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnRightMouseButtonDoubleClick(msg, processed);
			if (m_pForm->m_pInputControl->OnRightMouseButtonDoubleClick)
				m_pForm->m_pInputControl->OnRightMouseButtonDoubleClick(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnRightMouseButtonDoubleClick(msg);
		if (m_pForm->OnRightMouseButtonDoubleClick)
			m_pForm->OnRightMouseButtonDoubleClick(m_pForm, msg);
	}

	void CForm::CWindowListener::OnMiddleMouseButtonDown(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouse msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnMiddleMouseButtonDown(msg, processed);
			if (capture->OnMiddleMouseButtonDown)
				capture->OnMiddleMouseButtonDown(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Dialog box
		if (!processed)
			ActivateDialogBox(m_pForm->m_pHoveredControl);
		// Active control
		if (!processed && m_pForm->m_pActiveControl && m_pForm->m_pActiveControl != m_pForm->m_pHoveredControl)
			m_pForm->setActiveControl(nullptr);
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture)
		{
			if (m_pForm->m_bFocusByMMB && m_pForm->m_pHoveredControl->isFocusByMouse())
			{
				IControl *new_focused_control{ m_pForm->InterceptFocus(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, FocusedBy::MiddleMouse) };
				m_pForm->setFocusedControl(new_focused_control, FocusedBy::MiddleMouse, false);
			}
			if (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl))
			{
				if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptMiddleMouseButtonDown(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
				{
					IControl *control{ m_pForm->m_pHoveredControl };
					if (control)
					{
						msg.Target = control;
						control->QueryService()->NotifyOnMiddleMouseButtonDown(msg, processed);
						if (control->OnMiddleMouseButtonDown)
							control->OnMiddleMouseButtonDown(control, msg, processed);
						// Event bubbling
						while (!processed && (control = control->getParent()))
							if (control->isAcceptBubbledEvents())
							{
								control->QueryService()->NotifyOnMiddleMouseButtonDown(msg, processed);
								if (control->OnMiddleMouseButtonDown)
									control->OnMiddleMouseButtonDown(control, msg, processed);
							}
					}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnMiddleMouseButtonDown(msg, processed);
			if (modal->OnMiddleMouseButtonDown)
				modal->OnMiddleMouseButtonDown(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnMiddleMouseButtonDown(msg, processed);
			if (m_pForm->m_pInputControl->OnMiddleMouseButtonDown)
				m_pForm->m_pInputControl->OnMiddleMouseButtonDown(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnMiddleMouseButtonDown(msg);
		if (m_pForm->OnMiddleMouseButtonDown)
			m_pForm->OnMiddleMouseButtonDown(m_pForm, msg);
	}

	void CForm::CWindowListener::OnMiddleMouseButtonUp(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouse msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnMiddleMouseButtonUp(msg, processed);
			if (capture->OnMiddleMouseButtonUp)
				capture->OnMiddleMouseButtonUp(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture && (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptMiddleMouseButtonUp(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
			{
				IControl *control{ m_pForm->m_pHoveredControl };
				if (control)
				{
					msg.Target = control;
					control->QueryService()->NotifyOnMiddleMouseButtonUp(msg, processed);
					if (control->OnMiddleMouseButtonUp)
						control->OnMiddleMouseButtonUp(control, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnMiddleMouseButtonUp(msg, processed);
							if (control->OnMiddleMouseButtonUp)
								control->OnMiddleMouseButtonUp(control, msg, processed);
						}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnMiddleMouseButtonUp(msg, processed);
			if (modal->OnMiddleMouseButtonUp)
				modal->OnMiddleMouseButtonUp(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnMiddleMouseButtonUp(msg, processed);
			if (m_pForm->m_pInputControl->OnMiddleMouseButtonUp)
				m_pForm->m_pInputControl->OnMiddleMouseButtonUp(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnMiddleMouseButtonUp(msg);
		if (m_pForm->OnMiddleMouseButtonUp)
			m_pForm->OnMiddleMouseButtonUp(m_pForm, msg);
	}

	void CForm::CWindowListener::OnMiddleMouseButtonDoubleClick(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouse msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnMiddleMouseButtonDoubleClick(msg, processed);
			if (capture->OnMiddleMouseButtonDoubleClick)
				capture->OnMiddleMouseButtonDoubleClick(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture && (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptMiddleMouseButtonDoubleClick(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
			{
				IControl *control{ m_pForm->m_pHoveredControl };
				if (control)
				{
					msg.Target = control;
					control->QueryService()->NotifyOnMiddleMouseButtonDoubleClick(msg, processed);
					if (control->OnMiddleMouseButtonDoubleClick)
						control->OnMiddleMouseButtonDoubleClick(control, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnMiddleMouseButtonDoubleClick(msg, processed);
							if (control->OnMiddleMouseButtonDoubleClick)
								control->OnMiddleMouseButtonDoubleClick(control, msg, processed);
						}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnMiddleMouseButtonDoubleClick(msg, processed);
			if (modal->OnMiddleMouseButtonDoubleClick)
				modal->OnMiddleMouseButtonDoubleClick(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnMiddleMouseButtonDoubleClick(msg, processed);
			if (m_pForm->m_pInputControl->OnMiddleMouseButtonDoubleClick)
				m_pForm->m_pInputControl->OnMiddleMouseButtonDoubleClick(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnMiddleMouseButtonDoubleClick(msg);
		if (m_pForm->OnMiddleMouseButtonDoubleClick)
			m_pForm->OnMiddleMouseButtonDoubleClick(m_pForm, msg);
	}

	void CForm::CWindowListener::OnMouseVerticalWheel(const MessageMouseWheel &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouseWheel msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnMouseVerticalWheel(msg, processed);
			if (capture->OnMouseVerticalWheel)
				capture->OnMouseVerticalWheel(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture && (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptMouseVerticalWheel(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
			{
				IControl *control{ m_pForm->m_pHoveredControl };
				if (control)
				{
					msg.Target = control;
					control->QueryService()->NotifyOnMouseVerticalWheel(msg, processed);
					if (control->OnMouseVerticalWheel)
						control->OnMouseVerticalWheel(control, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnMouseVerticalWheel(msg, processed);
							if (control->OnMouseVerticalWheel)
								control->OnMouseVerticalWheel(control, msg, processed);
						}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnMouseVerticalWheel(msg, processed);
			if (modal->OnMouseVerticalWheel)
				modal->OnMouseVerticalWheel(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnMouseVerticalWheel(msg, processed);
			if (m_pForm->m_pInputControl->OnMouseVerticalWheel)
				m_pForm->m_pInputControl->OnMouseVerticalWheel(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnMouseVerticalWheel(msg);
		if (m_pForm->OnMouseVerticalWheel)
			m_pForm->OnMouseVerticalWheel(m_pForm, msg);
	}

	void CForm::CWindowListener::OnMouseHorizontalWheel(const MessageMouseWheel &m)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageMouseWheel msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnMouseHorizontalWheel(msg, processed);
			if (capture->OnMouseHorizontalWheel)
				capture->OnMouseHorizontalWheel(capture, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture && (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptMouseHorizontalWheel(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
			{
				IControl *control{ m_pForm->m_pHoveredControl };
				if (control)
				{
					msg.Target = control;
					control->QueryService()->NotifyOnMouseHorizontalWheel(msg, processed);
					if (control->OnMouseHorizontalWheel)
						control->OnMouseHorizontalWheel(control, msg, processed);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnMouseHorizontalWheel(msg, processed);
							if (control->OnMouseHorizontalWheel)
								control->OnMouseHorizontalWheel(control, msg, processed);
						}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnMouseHorizontalWheel(msg, processed);
			if (modal->OnMouseHorizontalWheel)
				modal->OnMouseHorizontalWheel(modal, msg, processed);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnMouseHorizontalWheel(msg, processed);
			if (m_pForm->m_pInputControl->OnMouseHorizontalWheel)
				m_pForm->m_pInputControl->OnMouseHorizontalWheel(m_pForm->m_pInputControl, msg, processed);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnMouseHorizontalWheel(msg);
		if (m_pForm->OnMouseHorizontalWheel)
			m_pForm->OnMouseHorizontalWheel(m_pForm, msg);
	}

	void CForm::CWindowListener::OnMouseHover(const MessageMouse &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnMouseHover(m);
		if (m_pForm->OnMouseHover)
			m_pForm->OnMouseHover(m_pForm, m);
	}

	void CForm::CWindowListener::OnMouseLeave()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->UpdateHoveredControl();
		if (m_pForm->m_pHint)
			m_pForm->m_pHint->Hide(false);
		m_pForm->m_bHintShown = false;
		m_pForm->m_bIsTrackingMouseLeave = false;
		m_pForm->QueryService()->NotifyOnMouseLeave();
		if (m_pForm->OnMouseLeave)
			m_pForm->OnMouseLeave(m_pForm);
	}

	void CForm::CWindowListener::OnLoseCapture()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnLoseCapture();
		if (m_pForm->OnLoseCapture)
			m_pForm->OnLoseCapture(m_pForm);
	}

	void CForm::CWindowListener::OnPaint(const MessageRect &m)
	{
		m_pForm->Repaint(m.Rect);
	}

	void CForm::CWindowListener::OnQueryEndSession(bool &restricted)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnQueryEndSession(restricted);
		if (m_pForm->OnQueryEndSession)
			m_pForm->OnQueryEndSession(m_pForm, restricted);
	}

	void CForm::CWindowListener::OnQueryOpen(bool &restricted)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnQueryOpen(restricted);
		if (m_pForm->OnQueryOpen)
			m_pForm->OnQueryOpen(m_pForm, restricted);
	}

	void CForm::CWindowListener::OnEndSession(const MessageEndSession &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnEndSession(m);
		if (m_pForm->OnEndSession)
			m_pForm->OnEndSession(m_pForm, m);
	}

	void CForm::CWindowListener::OnDeviceModeChange()
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnDeviceModeChange();
		if (m_pForm->OnDeviceModeChange)
			m_pForm->OnDeviceModeChange(m_pForm);
	}

	void CForm::CWindowListener::OnTimeChange()
	{
		CLockRepaint lock{ m_pForm };
		CNotifier::TimeChange(m_pForm);
	}

	void CForm::CWindowListener::OnInputLanguageChangeRequest(bool &restricted)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnInputLanguageChangeRequest(restricted);
		if (m_pForm->OnInputLanguageChangeRequest)
			m_pForm->OnInputLanguageChangeRequest(m_pForm, restricted);
	}

	void CForm::CWindowListener::OnInputLanguageChange()
	{
		CLockRepaint lock{ m_pForm };
		CNotifier::InputLanguageChange(m_pForm);
	}

	void CForm::CWindowListener::OnDisplayChange(const MessageSize &m)
	{
		CLockRepaint lock{ m_pForm };
		CNotifier::DisplayChange(m_pForm, m);
	}

	void CForm::CWindowListener::OnThemeChanged()
	{
		CLockRepaint lock{ m_pForm };
		CNotifier::ThemeChange(m_pForm);
	}

	void CForm::CWindowListener::OnClipboardUpdate()
	{
		CLockRepaint lock{ m_pForm };
		CNotifier::ClipboardUpdate(m_pForm);
	}

	void CForm::CWindowListener::OnDropFiles(const MessageDropFiles &m, bool accepted)
	{
		CLockRepaint lock{ m_pForm };
		// Captured control
		IControl *capture{ m_pForm->getCaptureMouseControl() }, *modal{ m_pForm->getModalControl() };
		bool processed{ false }, send_to_input{ m_pForm->m_pInputControl ? true : false };
		MessageDropFiles msg{ m };
		if (capture)
		{
			msg.Target = capture;
			capture->QueryService()->NotifyOnDropFiles(msg, processed, accepted);
			if (capture->OnDropFiles)
				capture->OnDropFiles(capture, msg, processed, accepted);
			send_to_input = send_to_input && !processed;
		}
		// Hovered control
		if (!processed && m_pForm->m_pHoveredControl && m_pForm->m_pHoveredControl != capture && (!modal || m_pForm->m_pHoveredControl == modal || modal->hasChild(m_pForm->m_pHoveredControl)))
		{
			if (!m_pForm->m_bInterceptEnabled || !m_pForm->InterceptDropFiles(m_pForm->m_pHoveredControl->getParent(), m_pForm->m_pHoveredControl, msg))
			{
				IControl *control{ m_pForm->m_pHoveredControl };
				if (control)
				{
					msg.Target = control;
					control->QueryService()->NotifyOnDropFiles(msg, processed, accepted);
					if (control->OnDropFiles)
						control->OnDropFiles(control, msg, processed, accepted);
					// Event bubbling
					while (!processed && (control = control->getParent()))
						if (control->isAcceptBubbledEvents())
						{
							control->QueryService()->NotifyOnDropFiles(msg, processed, accepted);
							if (control->OnDropFiles)
								control->OnDropFiles(control, msg, processed, accepted);
						}
				}
			}
			send_to_input = false;
		}
		// Modal control
		if (!processed && modal && modal != capture && modal != m_pForm->m_pHoveredControl)
		{
			msg.Target = modal;
			modal->QueryService()->NotifyOnDropFiles(msg, processed, accepted);
			if (modal->OnDropFiles)
				modal->OnDropFiles(modal, msg, processed, accepted);
			send_to_input = send_to_input && !processed;
		}
		// Input control
		if (send_to_input)
		{
			msg.Target = m_pForm->m_pInputControl;
			m_pForm->m_pInputControl->QueryService()->NotifyOnDropFiles(msg, processed, accepted);
			if (m_pForm->m_pInputControl->OnDropFiles)
				m_pForm->m_pInputControl->OnDropFiles(m_pForm->m_pInputControl, msg, processed, accepted);
		}
		// m_pForm
		m_pForm->QueryService()->NotifyOnDropFiles(msg, accepted);
		if (m_pForm->OnDropFiles)
			m_pForm->OnDropFiles(m_pForm, msg, accepted);
	}

	void CForm::CWindowListener::OnTouch(const MessageTouch &m)
	{
		CLockRepaint lock{ m_pForm };
		m_pForm->QueryService()->NotifyOnTouch(m);
		if (m_pForm->OnTouch)
			m_pForm->OnTouch(m_pForm, m);
	}

	bool CForm::CWindowListener::OnMessage(const unsigned int uMsg, const unsigned long long wParam, const long long lParam, long long &result)
	{
		CLockRepaint lock{ m_pForm };
		for (auto ml : m_pForm->m_aMessageListeners)
			if (ml.Listener->OnMessage(uMsg, wParam, lParam, result))
				return true;
		return false;
	}

	void CForm::CWindowListener::OnPasteString(const MessagePasteString &m)
	{
		CLockRepaint lock{ m_pForm };
		if (m_pForm->m_pFocusedControl)
		{
			m_pForm->m_pFocusedControl->QueryService()->NotifyOnPasteString(m);
			if (m_pForm->m_pFocusedControl->OnPasteString)
				m_pForm->m_pFocusedControl->OnPasteString(m_pForm->m_pFocusedControl, m);
		}
		m_pForm->QueryService()->NotifyOnPasteString(m);
		if (m_pForm->OnPasteString)
			m_pForm->OnPasteString(m_pForm, m);
	}

	void CForm::CWindowListener::ActivateDialogBox(IControl *control)
	{
		IDialogBox *dialog_box{ parent<IDialogBox*, true>(control) };
		if (dialog_box)
			m_pForm->setActiveDialogBox(dialog_box);
		else if (!m_pForm->getModalControl() || m_pForm->getModalControl() != m_pForm->getActiveDialogBox())
			m_pForm->setActiveDialogBox(nullptr);
	}
#pragma endregion

#pragma region CFormTransform
	CForm::CFormTransform::CFormTransform(IForm *form) :
		CTransform(nullptr),
		m_pForm{ form }
	{
		m_sTransform = nitisa::Transform{ 0, 0, 0, 1, 1, 1, 0, 0, 0, RotateOrder::ZYX, TransformOrder::TSR };
	}

	void CForm::CFormTransform::Release()
	{
		// Do nothing
	}

	float CForm::CFormTransform::getTx() const
	{
		return (float)m_pForm->getLeft();
	}

	float CForm::CFormTransform::getTy() const
	{
		return (float)m_pForm->getTop();
	}

	const Mat4f &CForm::CFormTransform::getMatrix()
	{
		return Identity;
	}

	const Mat4f &CForm::CFormTransform::getMatrixInversed()
	{
		return Identity;
	}

	const Mat4f &CForm::CFormTransform::getMatrixTranslate()
	{
		return Identity;
	}

	const Mat4f &CForm::CFormTransform::getMatrixScale()
	{
		return Identity;
	}

	const Mat4f &CForm::CFormTransform::getMatrixRotate()
	{
		return Identity;
	}

	const nitisa::Transform &CForm::CFormTransform::getTransform()
	{
		m_sTransform.Tx = (float)m_pForm->getLeft();
		m_sTransform.Ty = (float)m_pForm->getTop();
		return m_sTransform;
	}

	bool CForm::CFormTransform::isTranslateIdentity() const
	{
		return m_pForm->getLeft() == 0 && m_pForm->getTop() == 0;
	}

	bool CForm::CFormTransform::isScaleIdentity() const
	{
		return true;
	}

	bool CForm::CFormTransform::isRotateIdentity() const
	{
		return true;
	}

	bool CForm::CFormTransform::isIdentity() const
	{
		return m_pForm->getLeft() == 0 && m_pForm->getTop() == 0;
	}

	bool CForm::CFormTransform::setTx(const float value)
	{
		return m_pForm->setLeft(ntl::Round<int>(value));
	}

	bool CForm::CFormTransform::setTy(const float value)
	{
		return m_pForm->setTop(ntl::Round<int>(value));
	}

	bool CForm::CFormTransform::setTz(const float value)
	{
		return false;
	}

	bool CForm::CFormTransform::setSx(const float value)
	{
		return false;
	}

	bool CForm::CFormTransform::setSy(const float value)
	{
		return false;
	}

	bool CForm::CFormTransform::setSz(const float value)
	{
		return false;
	}

	bool CForm::CFormTransform::setRx(const float value)
	{
		return false;
	}

	bool CForm::CFormTransform::setRy(const float value)
	{
		return false;
	}

	bool CForm::CFormTransform::setRz(const float value)
	{
		return false;
	}

	bool CForm::CFormTransform::setTransformOrder(const TransformOrder value)
	{
		return false;
	}

	bool CForm::CFormTransform::setRotateOrder(const RotateOrder value)
	{
		return false;
	}

	bool CForm::CFormTransform::setTransform(const nitisa::Transform &value)
	{
		return m_pForm->setPosition(Point{ ntl::Round<int>(value.Tx), ntl::Round<int>(value.Ty) });
	}

	bool CForm::CFormTransform::Translate(const float tx, const float ty, const float tz)
	{
		return m_pForm->setPosition(Point{ ntl::Round<int>(tx), ntl::Round<int>(ty) });
	}

	bool CForm::CFormTransform::Scale(const float sx, const float sy, const float sz)
	{
		return false;
	}

	bool CForm::CFormTransform::Rotate(const float rx, const float ry, const float rz)
	{
		return false;
	}

	bool CForm::CFormTransform::Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz)
	{
		return m_pForm->setPosition(Point{ ntl::Round<int>(tx), ntl::Round<int>(ty) });
	}
#pragma endregion

#pragma region CTimerListener
	CForm::CTimerListener::CTimerListener(CForm *form) :
		m_pForm{ form }
	{

	}

	void CForm::CTimerListener::NotifyOnTimer(const PlatformHandle id)
	{
		m_pForm->m_pWindow->DeleteTimer(m_pForm->m_hTimerHintDelay);
		m_pForm->m_hTimerHintDelay = nullptr;
		CLockRepaint lock{ m_pForm };
		Point pos{ m_pForm->m_pWindow->ScreenToClient(Application->Mouse->getPosition()) };
		if (m_pForm->m_pHoveredControl)
		{
			if (!m_pForm->m_pHoveredControl->getHintText().empty() && m_pForm->m_pHoveredControl->isShowHint())
			{
				PointF shift{ m_pForm->m_pHoveredControl->getHintShift() };
				m_pForm->getHint()->Show(m_pForm->m_pHoveredControl->getHintText(), Point{ ntl::Round<int>((float)pos.X + shift.X), ntl::Round<int>((float)pos.Y + shift.Y) }, m_pForm->m_pWindow->getClientRect());
			}
		}
		else
		{
			m_pForm->m_bHintShown = true;
			if (!m_pForm->m_sHintText.empty() && m_pForm->m_bShowHint)
			{
				Point pos{ m_pForm->m_pWindow->ScreenToClient(Application->Mouse->getPosition()) };
				Rect client{ m_pForm->m_pWindow->getClientRect() };
				if (pos.X >= client.Left && pos.X < client.Right && pos.Y >= client.Top && pos.Y < client.Bottom)
				{
					PointF shift{ m_pForm->m_sHintShift };
					m_pForm->getHint()->Show(m_pForm->m_sHintText, Point{ ntl::Round<int>((float)pos.X + shift.X), ntl::Round<int>((float)pos.Y + shift.Y) }, m_pForm->m_pWindow->getClientRect());
				}
			}
		}
	}
#pragma endregion

#pragma region CTransformControlsListener
	CForm::CTransformControlsListener::CTransformControlsListener(CForm *form) :
		m_pForm{ form }
	{

	}

	void CForm::CTransformControlsListener::NotifyOnBeforeChange()
	{
		if (!m_pForm->m_bIgnoreTransformControls)
			m_pForm->LockRepaint();
	}

	void CForm::CTransformControlsListener::NotifyOnBeforeChange(bool &allowed)
	{
		if (!m_pForm->m_bIgnoreTransformControls)
			m_pForm->LockRepaint();
	}

	void CForm::CTransformControlsListener::NotifyOnAfterChange()
	{
		if (!m_pForm->m_bIgnoreTransformControls)
		{
			CNotifier::TransformControls(m_pForm);
			m_pForm->Repaint();
			m_pForm->UpdateHoveredControl();
			m_pForm->UnlockRepaint();
		}
	}
#pragma endregion

#pragma region CFontListener
	CForm::CFontListener::CFontListener(CForm *form) :
		m_pForm{ form }
	{

	}

	void CForm::CFontListener::NotifyOnBeforeChange()
	{
		if (!m_pForm->m_bIgnoreFont)
			m_pForm->LockRepaint();
	}

	void CForm::CFontListener::NotifyOnBeforeChange(bool &allowed)
	{
		if (!m_pForm->m_bIgnoreFont)
			m_pForm->LockRepaint();
	}

	void CForm::CFontListener::NotifyOnAfterChange()
	{
		if (!m_pForm->m_bIgnoreFont)
		{
			CNotifier::FontChange(m_pForm);
			m_pForm->Repaint();
			m_pForm->UpdateHoveredControl();
			m_pForm->UnlockRepaint();
		}
	}
#pragma endregion

#pragma region Constructor & destructor
	CForm::CForm(const String &class_name, IWindow *window, IRenderer *renderer, const CreateParams *params) :
		CClass(class_name),
		m_pWindow{ window },
		m_pRenderer{ renderer },
		m_pHint{ nullptr },
		m_pStyle{ nullptr },
		m_pFont{ nullptr },
		m_pCaret{ nullptr },
		m_pFocusedControl{ nullptr },
		m_pFocusedControlOld{ nullptr },
		m_pHoveredControl{ nullptr },
		m_pActiveControl{ nullptr },
		m_pTransform{ new CFormTransform(this) },
		m_pTransformControls{ nullptr },
		m_eCursor{ CursorType::Arrow },
		m_fHintDelay{ 0.5f },
		m_sHintShift{ 0, 20 },
		m_sBackgroundColor{ 240, 240, 240, 255 },
		m_bShowHint{ true },
		m_bFocusByLMB{ true },
		m_bFocusByMMB{ true },
		m_bFocusByRMB{ true },
		m_bFocusByTab{ true },
		m_bInterceptEnabled{ false },
		m_sBorderWidth{ 0, 0, 0, 0 },
		m_sPadding{ 0, 0, 0, 0 },
		m_pInputControl{ nullptr },
		m_sDPI{ DesignDPI },
		m_pListener{ nullptr },
		m_pService{ nullptr },
		m_iRepaintLockCount{ 0 },
		m_sRepaintRect{ 0, 0, 0, 0 },
		m_bRepaintRequired{ false },
		m_bIsTrackingMouseLeave{ false },
		m_sOldClientRect{ 0, 0, 0, 0 },
		m_bTabDownProcessed{ false },
		m_bIgnoreTransformControls{ false },
		m_bIgnoreCaret{ false },
		m_bIgnoreFont{ false },
		m_hTimerHintDelay{ nullptr },
		m_bDestroying{ false },
		m_bHintShown{ false },
		m_bAcceptDragAndDrop{ false },
		m_pWindowListener{ new CWindowListener(this) },
		m_bTasksRunning{ false },
		m_bRendering{ false },
		m_cTimerListener{ this },
		m_cTransformControlsListener{ this },
		m_cFontListener{ this }
	{
	#ifdef _DEBUG
		OnRender = nullptr;
	#endif

		// Events from child controls
		OnChildStyleChange = nullptr;
		OnChildFontChange = nullptr;
		OnChildTransform = nullptr;
		OnChildResize = nullptr;
		OnChildShow = nullptr;
		OnChildHide = nullptr;
		OnChildEnable = nullptr;
		OnChildDisable = nullptr;
		OnChildBeforeTransform = nullptr;
		OnChildBeforeResize = nullptr;
		OnChildBeforeShow = nullptr;
		OnChildBeforeHide = nullptr;
		OnChildBeforeEnable = nullptr;
		OnChildBeforeDisable = nullptr;

		// State change events
		OnResize = nullptr;
		OnTransform = nullptr;
		OnTransformControls = nullptr;
		OnStyleChange = nullptr;
		OnFontChange = nullptr;

		// Component events
		OnComponentAttach = nullptr;
		OnComponentDetach = nullptr;

		// Control events
		OnControlAttach = nullptr;
		OnControlDetach = nullptr;
		OnControlSetModal = nullptr;
		OnControlKillModal = nullptr;
		OnControlSetFocus = nullptr;
		OnControlKillFocus = nullptr;
		OnControlMouseHover = nullptr;
		OnControlMouseLeave = nullptr;
		OnControlSetCaptureKeyboard = nullptr;
		OnControlKillCaptureKeyboard = nullptr;
		OnControlSetCaptureMouse = nullptr;
		OnControlKillCaptureMouse = nullptr;
		OnControlActivate = nullptr;
		OnControlDeactivate = nullptr;

		// Paint events
		OnPaint = nullptr;
		OnPaintEnd = nullptr;

		// Keyboard input events
		OnKeyDown = nullptr;
		OnKeyUp = nullptr;
		OnChar = nullptr;
		OnDeadChar = nullptr;

		// Mouse input events
		OnMouseHover = nullptr;
		OnMouseLeave = nullptr;
		OnMouseMove = nullptr;
		OnLeftMouseButtonDown = nullptr;
		OnLeftMouseButtonUp = nullptr;
		OnLeftMouseButtonDoubleClick = nullptr;
		OnRightMouseButtonDown = nullptr;
		OnRightMouseButtonUp = nullptr;
		OnRightMouseButtonDoubleClick = nullptr;
		OnMiddleMouseButtonDown = nullptr;
		OnMiddleMouseButtonUp = nullptr;
		OnMiddleMouseButtonDoubleClick = nullptr;
		OnMouseVerticalWheel = nullptr;
		OnMouseHorizontalWheel = nullptr;

		// Other input events
		OnDropFiles = nullptr;
		OnHotkey = nullptr;
		OnGestureZoom = nullptr;
		OnGesturePan = nullptr;
		OnGestureRotate = nullptr;
		OnGestureTwoFingerTap = nullptr;
		OnGesturePressAndTap = nullptr;
		OnGestureNotify = nullptr;
		OnTouch = nullptr;

		// Application events
		OnApplicationActivate = nullptr;
		OnApplicationDeactivate = nullptr;
		OnQueryEndSession = nullptr;
		OnQueryOpen = nullptr;
		OnEndSession = nullptr;
		OnDeviceModeChange = nullptr;
		OnTimeChange = nullptr;
		OnInputLanguageChangeRequest = nullptr;
		OnInputLanguageChange = nullptr;
		OnDisplayChange = nullptr;
		OnThemeChange = nullptr;
		OnClipboardUpdate = nullptr;
		OnTranslateChange = nullptr;

		// Window events
		OnDestroy = nullptr;
		OnActivate = nullptr;
		OnDeactivate = nullptr;
		OnSetFocus = nullptr;
		OnKillFocus = nullptr;
		OnEnable = nullptr;
		OnDisable = nullptr;
		OnClose = nullptr;
		OnShow = nullptr;
		OnHide = nullptr;
		OnMove = nullptr;
		OnRestore = nullptr;
		OnMinimize = nullptr;
		OnMaximize = nullptr;
		OnResizing = nullptr;
		OnMoving = nullptr;
		OnEnterSizeMove = nullptr;
		OnExitSizeMove = nullptr;
		OnHScroll = nullptr;
		OnVScroll = nullptr;
		OnLoseCapture = nullptr;

		// Dialog box events
		OnDialogBoxActivate = nullptr;
		OnDialogBoxDeactivate = nullptr;

		// Clipboard events
		OnPasteString = nullptr;

		if (params)
			m_sCreateParams = *params;

		if (window)
		{
			CLockRepaint lock{ this };
			InitializeWindow();
			Application->QueryService()->Add(this);
		}
	}

	CForm::~CForm()
	{
		DeleteTasks();
		if (m_pCaret)
			m_pCaret->Release();
		if (m_pHint)
			m_pHint->Release();
		if (m_pFont)
			m_pFont->Release();
		if (m_pRenderer)
			m_pRenderer->Release();
		if (m_pTransformControls)
			m_pTransformControls->Release();
		if (m_pService)
			m_pService->Release();
		delete m_pTransform;
		delete m_pWindowListener;
		Application->QueryService()->Remove(this);
	}

	void CForm::Release()
	{
		if (m_pWindow)
			m_pWindow->Release();
		else
		{
			LockRepaint();
			delete this;
		}
	}

	void CForm::InitializeWindow()
	{
		m_pWindow->QueryService()->setListener(m_pWindowListener);
		if (!m_pWindow->isCreated())
		{
			m_pWindow->setCreateParams(m_sCreateParams);
			if (m_pRenderer)
				m_pRenderer->isWindowSupported(m_pWindow);
			if (Application->MainForm && Application->MainForm->QueryService()->getWindow())
			{
				if (!m_pWindow->Create(Application->MainForm->QueryService()->getWindow()))
					return;
			}
			else
			{
				if (!m_pWindow->Create())
					return;
			}
		}
		else
			m_sCreateParams = m_pWindow->getCreateParams();
		m_pWindow->setCursor(m_eCursor);
		if (m_pRenderer)
		{
			if (m_pRenderer->InitializationStatus == IRenderer::InitializationStatus::Initialized)
				m_pRenderer->AddRef();
			else if (!m_pRenderer->setWindow(m_pWindow, false, false))
				return;
		}
		Repaint();
	}

	void CForm::DoOnChangeModalControl()
	{
		// Capture keyboard
		if (m_aCaptureKeyboardControls.size() > 0)
		{
			IControl *old_control{ m_aCaptureKeyboardControls[m_aCaptureKeyboardControls.size() - 1] };
			auto pos{ m_aCaptureKeyboardControls.begin() };
			while (pos != m_aCaptureKeyboardControls.end())
				if (*pos != getModalControl() && !getModalControl()->hasChild(*pos))
					pos = m_aCaptureKeyboardControls.erase(pos);
				else
					pos++;
			IControl *new_control{ (m_aCaptureKeyboardControls.size() > 0) ? m_aCaptureKeyboardControls[m_aCaptureKeyboardControls.size() - 1] : nullptr };
			if (old_control != new_control)
			{
				CNotifier::ControlKillCaptureKeyboard(this, old_control);
				if (new_control)
					CNotifier::ControlSetCaptureKeyboard(this, new_control);
			}
		}
		// Capture mouse
		if (m_aCaptureMouseControls.size() > 0)
		{
			CAPTURE_MOUSE old_control{ m_aCaptureMouseControls[m_aCaptureMouseControls.size() - 1] };
			auto pos{ m_aCaptureMouseControls.begin() };
			while (pos != m_aCaptureMouseControls.end())
				if (pos->Control != getModalControl() && !getModalControl()->hasChild(pos->Control))
					pos = m_aCaptureMouseControls.erase(pos);
				else
					pos++;
			CAPTURE_MOUSE *new_control{ (m_aCaptureMouseControls.size() > 0) ? &m_aCaptureMouseControls[m_aCaptureMouseControls.size() - 1] : nullptr };
			if (!new_control || new_control->Control != old_control.Control)
			{
				if (m_pWindow && old_control.System)
					m_pWindow->ReleaseMouseCapture();
				CNotifier::ControlKillCaptureMouse(this, old_control.Control);
				if (new_control)
				{
					if (m_pWindow && new_control->System)
						new_control->System = m_pWindow->CaptureMouse();
					CNotifier::ControlSetCaptureMouse(this, new_control->Control);
				}
			}
		}
		// Focused
		if (m_pFocusedControl && m_pFocusedControl != getModalControl() && !getModalControl()->hasChild(m_pFocusedControl))
		{
			CNotifier::ControlKillFocus(this, m_pFocusedControl);
			m_pFocusedControl = m_pFocusedControlOld = nullptr;
		}
		// Active
		if (m_pActiveControl && m_pActiveControl != getModalControl() && !getModalControl()->hasChild(m_pActiveControl))
		{
			CNotifier::ControlDeactivate(this, m_pActiveControl);
			m_pActiveControl = nullptr;
		}
		// Dialog box
		if (m_aActiveDialogBoxes.size() > 0)
		{
			IDialogBox *old_control{ m_aActiveDialogBoxes[m_aActiveDialogBoxes.size() - 1] };
			auto pos{ m_aActiveDialogBoxes.begin() };
			while (pos != m_aActiveDialogBoxes.end())
				if (*pos != getModalControl() && !getModalControl()->hasChild(*pos))
					pos = m_aActiveDialogBoxes.erase(pos);
				else
					pos++;
			IDialogBox *new_control{ (m_aActiveDialogBoxes.size() > 0) ? m_aActiveDialogBoxes[m_aActiveDialogBoxes.size() - 1] : nullptr };
			if (old_control != new_control)
			{
				CNotifier::ControlDeactivateDialogBox(this, old_control);
				if (new_control)
					CNotifier::ControlActivateDialogBox(this, new_control);
			}
		}
	}
#pragma endregion

#pragma region Getters
	IRenderer *CForm::getRenderer()
	{
		return m_pRenderer;
	}

	IHint *CForm::getHint()
	{
		if (!m_pHint)
		{
			m_pHint = new CHint();
			m_pHint->QueryService()->setForm(this);
		}
		return m_pHint;
	}

	IStyle *CForm::getStyle()
	{
		return m_pStyle;
	}

	IFont *CForm::getFont()
	{
		if (!m_pFont)
			m_pFont = new CFont(&m_cFontListener);
		return m_pFont;
	}

	ICaret *CForm::getCaret()
	{
		if (!m_pCaret)
		{
			m_pCaret = new CCaret(nullptr);
			if (m_pRenderer)
				m_pCaret->setRenderer(m_pRenderer);
		}
		return m_pCaret;
	}

	IControl *CForm::getModalControl()
	{
		if (m_aModalControls.size() > 0)
			return m_aModalControls[m_aModalControls.size() - 1];
		return nullptr;
	}

	IControl *CForm::getFocusedControl()
	{
		return m_pFocusedControl;
	}

	IControl *CForm::getCaptureKeyboardControl()
	{
		if (m_aCaptureKeyboardControls.size() > 0)
			return m_aCaptureKeyboardControls[m_aCaptureKeyboardControls.size() - 1];
		return nullptr;
	}

	IControl *CForm::getCaptureMouseControl()
	{
		if (m_aCaptureMouseControls.size() > 0)
			return m_aCaptureMouseControls[m_aCaptureMouseControls.size() - 1].Control;
		return nullptr;
	}

	IControl *CForm::getHoveredControl()
	{
		return m_pHoveredControl;
	}

	IControl *CForm::getActiveControl()
	{
		return m_pActiveControl;
	}

	int CForm::getControlCount(const bool total)
	{
		int result{ (int)m_aControls.size() };
		if (total)
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				result += (*pos)->getControlCount(true);
		return result;
	}

	IControl *CForm::getControl(const int index)
	{
		if (index >= 0 && index < (int)m_aControls.size())
			return m_aControls[(size_t)index];
		return nullptr;
	}

	IControl *CForm::getControl(const String &name)
	{
		for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
			if ((*pos)->Name == name)
				return *pos;
		return nullptr;
	}

	IControl *CForm::getControl(const PointF &position)
	{
		if (getCaptureMouseControl())
		{
			IControl *control{ getCaptureMouseControl()->getControl(position) };
			if (control)
				return control;
		}
		std::vector<IControl*> controls{ m_aControls };
		std::sort(controls.begin(), controls.end(), [](IControl *a, IControl *b) { return a->getZIndex() < b->getZIndex(); });
		for (auto pos = controls.rbegin(); pos != controls.rend(); pos++)
		{
			IControl *control{ (*pos)->getControl(position) };
			if (control)
				return control;
		}
		return nullptr;
	}

	int CForm::getControlIndex(IControl *control)
	{
		int result{ 0 };
		for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++, result++)
			if (*pos == control)
				return result;
		return -1;
	}

	int CForm::getComponentCount()
	{
		return (int)m_aComponents.size();
	}

	IComponent *CForm::getComponent(const int index)
	{
		if (index >= 0 && index < (int)m_aComponents.size())
			return m_aComponents[(size_t)index];
		return nullptr;
	}

	IComponent *CForm::getComponent(const String &name)
	{
		for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
			if ((*pos)->Name == name)
				return *pos;
		return nullptr;
	}

	int CForm::getComponentIndex(IComponent *component)
	{
		int result{ 0 };
		for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++, result++)
			if (*pos == component)
				return result;
		return -1;
	}

	ITransform *CForm::getTransform()
	{
		return m_pTransform;
	}

	ITransform *CForm::getTransformControls()
	{
		if (!m_pTransformControls)
			m_pTransformControls = new CTransform(&m_cTransformControlsListener);
		return m_pTransformControls;
	}

	CursorType CForm::getCursor()
	{
		return m_eCursor;
	}

	String CForm::getHintText()
	{
		return m_sHintText;
	}

	float CForm::getHintDelay()
	{
		return m_fHintDelay;
	}

	PointF CForm::getHintShift()
	{
		return m_sHintShift;
	}

	Color CForm::getBackgroundColor()
	{
		return m_sBackgroundColor;
	}

	RectF CForm::getBorderWidth()
	{
		return m_sBorderWidth;
	}

	RectF CForm::getPadding()
	{
		return m_sPadding;
	}

	bool CForm::isShowHint()
	{
		return m_bShowHint;
	}

	bool CForm::isFocusByLMB()
	{
		return m_bFocusByLMB;
	}

	bool CForm::isFocusByMMB()
	{
		return m_bFocusByMMB;
	}

	bool CForm::isFocusByRMB()
	{
		return m_bFocusByRMB;
	}

	bool CForm::isFocusByTab()
	{
		return m_bFocusByTab;
	}

	bool CForm::isInterceptEnable()
	{
		return m_bInterceptEnabled;
	}

	int CForm::getTaskCount()
	{
		return (int)m_aTasks.size();
	}

	ITask *CForm::getTask(const int index)
	{
		if (index >= 0 && index < (int)m_aTasks.size())
			return m_aTasks[index];
		return nullptr;
	}

	IControl *CForm::getInputControl()
	{
		return m_pInputControl;
	}

	Point CForm::getDPI()
	{
		return m_sDPI;
	}

	IDialogBox *CForm::getActiveDialogBox()
	{
		if (m_aActiveDialogBoxes.size() > 0)
			return m_aActiveDialogBoxes[m_aActiveDialogBoxes.size() - 1];
		return nullptr;
	}

	IFormListener *CForm::getListener()
	{
		return m_pListener;
	}
#pragma endregion

#pragma region Window getters
	bool CForm::isVisible()
	{
		if (m_pWindow)
			return m_pWindow->isVisible();
		return m_sCreateParams.State != WindowState::Hidden;
	}

	bool CForm::isEnabled()
	{
		if (m_pWindow)
			return m_pWindow->isEnabled();
		return m_sCreateParams.IsEnabled;
	}

	bool CForm::isAcceptDragAndDrop()
	{
		if (m_pWindow)
			return m_pWindow->isAcceptDragAndDrop();
		return m_bAcceptDragAndDrop;
	}

	bool CForm::isAcceptDropFiles()
	{
		if (m_pWindow)
			return m_pWindow->isAcceptDropFiles();
		return m_sCreateParams.IsAcceptFiles;
	}

	String CForm::getCaption()
	{
		if (m_pWindow)
			return m_pWindow->getCaption();
		return m_sCreateParams.Caption;
	}

	Rect CForm::getRect()
	{
		if (m_pWindow)
			return m_pWindow->getRect();
		return Rect{ m_sCreateParams.Position.X, m_sCreateParams.Position.Y, m_sCreateParams.Position.X + m_sCreateParams.Size.X, m_sCreateParams.Position.Y + m_sCreateParams.Size.Y };
	}

	Point CForm::getSize()
	{
		if (m_pWindow)
			return m_pWindow->getSize();
		return m_sCreateParams.Size;
	}

	Point CForm::getPosition()
	{
		if (m_pWindow)
			return m_pWindow->getPosition();
		return m_sCreateParams.Position;
	}

	int CForm::getLeft()
	{
		if (m_pWindow)
			return m_pWindow->getLeft();
		return m_sCreateParams.Position.X;
	}

	int CForm::getTop()
	{
		if (m_pWindow)
			return m_pWindow->getTop();
		return m_sCreateParams.Position.Y;
	}

	int CForm::getWidth()
	{
		if (m_pWindow)
			return m_pWindow->getWidth();
		return m_sCreateParams.Size.X;
	}

	int CForm::getHeight()
	{
		if (m_pWindow)
			return m_pWindow->getHeight();
		return m_sCreateParams.Size.Y;
	}

	Rect CForm::getClientRect()
	{
		if (m_pWindow)
			return m_pWindow->getClientRect();
		return Rect{ 0, 0, m_sCreateParams.Size.X, m_sCreateParams.Size.Y };
	}

	Point CForm::getClientSize()
	{
		if (m_pWindow)
			return m_pWindow->getClientSize();
		return m_sCreateParams.Size;
	}

	int CForm::getClientWidth()
	{
		if (m_pWindow)
			return m_pWindow->getClientWidth();
		return m_sCreateParams.Size.X;
	}

	int CForm::getClientHeight()
	{
		if (m_pWindow)
			return m_pWindow->getClientHeight();
		return m_sCreateParams.Size.Y;
	}

	WindowState CForm::getState()
	{
		if (m_pWindow)
			return m_pWindow->getState();
		return m_sCreateParams.State;
	}

	CreateParams CForm::getCreateParams()
	{
		return m_sCreateParams;
	}

	bool CForm::hasBorder()
	{
		return m_sCreateParams.HasBorder;
	}

	bool CForm::hasCaption()
	{
		return m_sCreateParams.HasCaption;
	}

	bool CForm::hasDialogFrame()
	{
		return m_sCreateParams.HasDialogFrame;
	}

	bool CForm::hasHorizontalScroll()
	{
		return m_sCreateParams.HasHorizontalScroll;
	}

	bool CForm::hasVerticalScroll()
	{
		return m_sCreateParams.HasVerticalScroll;
	}

	bool CForm::hasMaximizeBox()
	{
		return m_sCreateParams.HasMaximizeBox;
	}

	bool CForm::hasMinimizeBox()
	{
		return m_sCreateParams.HasMinimizeBox;
	}

	bool CForm::hasSizeBox()
	{
		return m_sCreateParams.HasSizeBox;
	}

	bool CForm::hasSystemMenu()
	{
		return m_sCreateParams.HasSystemMenu;
	}

	bool CForm::hasClientEdge()
	{
		return m_sCreateParams.HasClientEdge;
	}

	bool CForm::hasContextHelp()
	{
		return m_sCreateParams.HasContextHelp;
	}

	bool CForm::hasDialogModalFrame()
	{
		return m_sCreateParams.HasDialogModalFrame;
	}

	bool CForm::hasStaticEdge()
	{
		return m_sCreateParams.HasStaticEdge;
	}

	bool CForm::hasWindowEdge()
	{
		return m_sCreateParams.HasWindowEdge;
	}

	bool CForm::isPopup()
	{
		return m_sCreateParams.IsPopup;
	}

	bool CForm::isTabStop()
	{
		return m_sCreateParams.IsTabStop;
	}

	bool CForm::isMDIChild()
	{
		return m_sCreateParams.IsMDIChild;
	}

	bool CForm::isToolWindow()
	{
		return m_sCreateParams.IsToolWindow;
	}

	bool CForm::isTopMost()
	{
		return m_sCreateParams.IsTopMost;
	}

	void CForm::setListener(IFormListener *value)
	{
		m_pListener = value;
	}
#pragma endregion

#pragma region Setters
	bool CForm::setName(const String &value)
	{
		if (value != m_sName)
		{
			m_sName = value;
			return true;
		}
		return false;
	}

	bool CForm::setCaret(ICaret *value)
	{
		if (!value || value == m_pCaret)
			return false;
		CopyCaret(value, m_pCaret);
		if (m_pCaret)
			m_pCaret->Release();
		m_pCaret = value;
		if (m_pRenderer != m_pCaret->getRenderer())
			return m_pCaret->setRenderer(m_pRenderer);
		return true;
	}

	bool CForm::setHint(IHint *value)
	{
		if (!value || value == m_pHint)
			return false;
		if (m_hTimerHintDelay)
		{
			m_pWindow->DeleteTimer(m_hTimerHintDelay);
			m_hTimerHintDelay = nullptr;
		}
		if (m_pHint)
			m_pHint->Release();
		m_pHint = value;
		m_pHint->QueryService()->setForm(this);
		return true;
	}

	bool CForm::setStyle(IStyle *value)
	{
		if (value == m_pStyle)
			return false;
		m_pStyle = value;
		if (m_pStyle)
		{
			CLockRepaint lock{ this };
			CopyFont(getFont(), m_pStyle->getFont(m_sClassName));
			m_pStyle->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			CNotifier::StyleChange(this);
			Repaint();
		}
		return true;
	}

	bool CForm::setFont(IFont *value, const bool copy)
	{
		if (!value || value == m_pFont)
			return false;
		CLockRepaint lock{ this };
		if (!copy)
		{
			if (m_pFont)
				m_pFont->Release();
			m_pFont = value;
			m_pFont->setListener(&m_cFontListener);
		}
		else
			CopyFont(getFont(), value);
		CNotifier::FontChange(this);
		Repaint();
		return true;
	}

	bool CForm::setModalControl(IControl *value)
	{
		IControl *old_modal{ getModalControl() };
		if (value == old_modal)
			return false;
		if (value && (value->getForm() != this || !value->isAcceptModal() || !value->isVisible(true)))
			return false;
		CLockRepaint lock{ this };
		if (old_modal)
			CNotifier::ControlKillModal(this, old_modal);
		if (value)
		{
			auto pos{ m_aModalControls.begin() };
			while (pos != m_aModalControls.end())
				if (*pos == value)
					pos = m_aModalControls.erase(pos);
				else
					pos++;
			m_aModalControls.push_back(value);
			DoOnChangeModalControl();
			CNotifier::ControlSetModal(this, value);
		}
		else if (m_aModalControls.size() > 0)
			m_aModalControls.clear();
		UpdateHoveredControl();
		Repaint();
		return true;
	}

	bool CForm::setFocusedControl(IControl *value)
	{
		return setFocusedControl(value, FocusedBy::Other, true);
	}

	bool CForm::setActiveControl(IControl *value)
	{
		if (value == m_pActiveControl) // Already set
			return false;
		if (value)
		{
			if (value->getForm() != this || !value->isVisible(true) || !value->isEnabled(true)) // Should be on form, visible and enabled
				return false;
			if (getModalControl() && value != getModalControl() && !getModalControl()->hasChild(value)) // Should be on modal if there is one
				return false;
		}
		CLockRepaint lock{ this };
		if (m_pActiveControl)
			CNotifier::ControlDeactivate(this, m_pActiveControl);
		m_pActiveControl = value;
		if (m_pActiveControl)
			CNotifier::ControlActivate(this, m_pActiveControl);
		return true;
	}

	bool CForm::setTransformControls(ITransform *value)
	{
		if (!value || value == m_pTransformControls)
			return false;
		CLockRepaint lock{ this };
		CopyTransform(value, m_pTransformControls);
		value->setListener(&m_cTransformControlsListener);
		if (m_pTransformControls)
			m_pTransformControls->Release();
		m_pTransformControls = value;
		QueryService()->AlignControls();
		CNotifier::TransformControls(this);
		Repaint();
		return true;
	}

	bool CForm::setCursor(const CursorType value)
	{
		if (value != m_eCursor)
		{
			m_eCursor = value;
			if (!m_pHoveredControl && m_pWindow)
				return m_pWindow->setCursor(m_eCursor);
			return true;
		}
		return false;
	}

	bool CForm::setHintText(const String &value)
	{
		if (value != m_sHintText)
		{
			m_sHintText = value;
			return true;
		}
		return false;
	}

	bool CForm::setHintDelay(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fHintDelay))
		{
			m_fHintDelay = value;
			return true;
		}
		return false;
	}

	bool CForm::setHintShift(const PointF &value)
	{
		if (IsNotEqual(value, m_sHintShift))
		{
			m_sHintShift = value;
			return true;
		}
		return false;
	}

	bool CForm::setBackgroundColor(const Color &value)
	{
		if (value != m_sBackgroundColor)
		{
			m_sBackgroundColor = value;
			if (m_pRenderer)
				Repaint();
			return true;
		}
		return false;
	}

	bool CForm::setBorderWidth(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
		{
			m_sBorderWidth = value;
			QueryService()->AlignControls();
			return true;
		}
		return false;
	}

	bool CForm::setPadding(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sPadding))
		{
			m_sPadding = value;
			QueryService()->AlignControls();
			return true;
		}
		return false;
	}

	bool CForm::setShowHint(const bool value)
	{
		if (value != m_bShowHint)
		{
			m_bShowHint = value;
			return true;
		}
		return false;
	}

	bool CForm::setFocusByLMB(const bool value)
	{
		if (value != m_bFocusByLMB)
		{
			m_bFocusByLMB = value;
			return true;
		}
		return false;
	}

	bool CForm::setFocusByMMB(const bool value)
	{
		if (value != m_bFocusByMMB)
		{
			m_bFocusByMMB = value;
			return true;
		}
		return false;
	}

	bool CForm::setFocusByRMB(const bool value)
	{
		if (value != m_bFocusByRMB)
		{
			m_bFocusByRMB = value;
			return true;
		}
		return false;
	}

	bool CForm::setFocusByTab(const bool value)
	{
		if (value != m_bFocusByTab)
		{
			m_bFocusByTab = value;
			return true;
		}
		return false;
	}

	bool CForm::setInterceptEnable(const bool value)
	{
		if (value != m_bInterceptEnabled)
		{
			m_bInterceptEnabled = value;
			return true;
		}
		return false;
	}

	bool CForm::setInputControl(IControl *value)
	{
		if (value != m_pInputControl)
		{
			m_pInputControl = value;
			Repaint();
			return true;
		}
		return false;
	}

	void CForm::setService(IFormService *value, const bool release_prev)
	{
		if (m_pService && m_pService != value && release_prev)
			m_pService->Release();
		m_pService = value;
	}

	bool CForm::setDPI(const Point &value)
	{
		if (value.X > 0 && value.Y > 0 && value != m_sDPI)
		{
			CLockRepaint lock{ this };
			m_sDPI = value;
			for (auto control : m_aControls)
				control->setDPI(m_sDPI);
			return true;
		}
		return false;
	}

	bool CForm::setActiveDialogBox(IDialogBox *value)
	{
		IDialogBox *active{ getActiveDialogBox() };
		if (value == active) // Already set
			return false;
		if (value)
		{
			if (value->getForm() != this || !value->isVisible(true)) //Should be on this form and visible
				return false;
			if (getModalControl() && getModalControl() != value && !getModalControl()->hasChild(value)) // Should be on modal if there is one
				return false;
		}
		if (active)
			CNotifier::ControlDeactivateDialogBox(this, active);
		if (value)
		{
			for (auto pos = m_aActiveDialogBoxes.begin(); pos != m_aActiveDialogBoxes.end(); pos++)
				if (*pos == value)
				{
					m_aActiveDialogBoxes.erase(pos);
					break;
				}
			m_aActiveDialogBoxes.push_back(value);
			CNotifier::ControlActivateDialogBox(this, value);
		}
		else
			m_aActiveDialogBoxes.clear();
		return true;
	}
#pragma endregion

#pragma region Window setters
	bool CForm::setVisible(const bool value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setVisible(value))
			{
				m_sCreateParams.State = value ? WindowState::Normal : WindowState::Hidden;
				return true;
			}
			return false;
		}
		if ((value && m_sCreateParams.State != WindowState::Normal) || (!value && m_sCreateParams.State != WindowState::Hidden))
		{
			m_sCreateParams.State = value ? WindowState::Normal : WindowState::Hidden;
			return true;
		}
		return false;
	}

	bool CForm::setEnabled(const bool value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setEnabled(value))
			{
				m_sCreateParams.IsEnabled = value;
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.IsEnabled)
		{
			m_sCreateParams.IsEnabled = value;
			return true;
		}
		return false;
	}

	bool CForm::setAcceptDrawAndDrop(const bool value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setAcceptDrawAndDrop(value))
			{
				m_bAcceptDragAndDrop = value;
				return true;
			}
			return false;
		}
		if (value != m_bAcceptDragAndDrop)
		{
			m_bAcceptDragAndDrop = value;
			return true;
		}
		return false;
	}

	bool CForm::setAcceptDropFiles(const bool value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setAcceptDropFiles(value))
			{
				m_sCreateParams.IsAcceptFiles = value;
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.IsAcceptFiles)
		{
			m_sCreateParams.IsAcceptFiles = value;
			return true;
		}
		return false;
	}

	bool CForm::setCaption(const String &value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setCaption(value))
			{
				m_sCreateParams.Caption = value;
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.Caption)
		{
			m_sCreateParams.Caption = value;
			return true;
		}
		return false;
	}

	bool CForm::setRect(const Rect &value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setRect(value))
			{
				m_sCreateParams.Position = value.LeftTop;
				m_sCreateParams.Size = m_pWindow->getClientSize();
				return true;
			}
			return false;
		}
		if (value.LeftTop != m_sCreateParams.Position || value.width() != m_sCreateParams.Size.X || value.height() != m_sCreateParams.Size.Y)
		{
			m_sCreateParams.Position = value.LeftTop;
			m_sCreateParams.Size.X = value.width();
			m_sCreateParams.Size.Y = value.height();
			return true;
		}
		return false;
	}

	bool CForm::setSize(const Point &value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setSize(value))
			{
				m_sCreateParams.Size = m_pWindow->getClientSize();
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.Size)
		{
			m_sCreateParams.Size = value;
			return true;
		}
		return false;
	}

	bool CForm::setPosition(const Point &value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setPosition(value))
			{
				m_sCreateParams.Position = value;
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.Position)
		{
			m_sCreateParams.Position = value;
			return true;
		}
		return false;
	}

	bool CForm::setLeft(const int value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setLeft(value))
			{
				m_sCreateParams.Position.X = value;
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.Position.X)
		{
			m_sCreateParams.Position.X = value;
			return true;
		}
		return false;
	}

	bool CForm::setTop(const int value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setTop(value))
			{
				m_sCreateParams.Position.Y = value;
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.Position.Y)
		{
			m_sCreateParams.Position.Y = value;
			return true;
		}
		return false;
	}

	bool CForm::setWidth(const int value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setWidth(value))
			{
				m_sCreateParams.Size.X = m_pWindow->getClientWidth();
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.Size.X)
		{
			m_sCreateParams.Size.X = value;
			return true;
		}
		return false;
	}

	bool CForm::setHeight(const int value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setHeight(value))
			{
				m_sCreateParams.Size.Y = m_pWindow->getClientHeight();
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.Size.Y)
		{
			m_sCreateParams.Size.Y = value;
			return true;
		}
		return false;
	}

	bool CForm::setClientSize(const Point &value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setClientSize(value))
			{
				m_sCreateParams.Size = value;
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.Size)
		{
			m_sCreateParams.Size = value;
			return true;
		}
		return false;
	}

	bool CForm::setState(const WindowState value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setState(value))
			{
				m_sCreateParams.State = value;
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.State)
		{
			m_sCreateParams.State = value;
			return true;
		}
		return false;
	}

	bool CForm::setModalResult(const ModalResult value)
	{
		if (m_pWindow)
			return m_pWindow->setModalResult(value);
		return false;
	}

	bool CForm::setWindowPosition(const WindowPosition value)
	{
		if (m_pWindow)
		{
			if (m_pWindow->setWindowPosition(value))
			{
				m_sCreateParams.WindowPosition = value;
				return true;
			}
			return false;
		}
		if (value != m_sCreateParams.WindowPosition)
		{
			m_sCreateParams.WindowPosition = value;
			return true;
		}
		return false;
	}

	void CForm::setCreateParams(const CreateParams &value)
	{
		m_sCreateParams = value;
	}

	bool CForm::setHasBorder(const bool value)
	{
		if (m_sCreateParams.HasBorder != value)
		{
			m_sCreateParams.HasBorder = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasCaption(const bool value)
	{
		if (m_sCreateParams.HasCaption != value)
		{
			m_sCreateParams.HasCaption = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasDialogFrame(const bool value)
	{
		if (m_sCreateParams.HasDialogFrame != value)
		{
			m_sCreateParams.HasDialogFrame = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasHorizontalScroll(const bool value)
	{
		if (m_sCreateParams.HasHorizontalScroll != value)
		{
			m_sCreateParams.HasHorizontalScroll = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasVerticalScroll(const bool value)
	{
		if (m_sCreateParams.HasVerticalScroll != value)
		{
			m_sCreateParams.HasVerticalScroll = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasMaximizeBox(const bool value)
	{
		if (m_sCreateParams.HasMaximizeBox != value)
		{
			m_sCreateParams.HasMaximizeBox = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasMinimizeBox(const bool value)
	{
		if (m_sCreateParams.HasMinimizeBox != value)
		{
			m_sCreateParams.HasMinimizeBox = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasSizeBox(const bool value)
	{
		if (m_sCreateParams.HasSizeBox != value)
		{
			m_sCreateParams.HasSizeBox = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasSystemMenu(const bool value)
	{
		if (m_sCreateParams.HasSystemMenu != value)
		{
			m_sCreateParams.HasSystemMenu = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasClientEdge(const bool value)
	{
		if (m_sCreateParams.HasClientEdge != value)
		{
			m_sCreateParams.HasClientEdge = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasContextHelp(const bool value)
	{
		if (m_sCreateParams.HasContextHelp != value)
		{
			m_sCreateParams.HasContextHelp = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasDialogModalFrame(const bool value)
	{
		if (m_sCreateParams.HasDialogModalFrame != value)
		{
			m_sCreateParams.HasDialogModalFrame = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasStaticEdge(const bool value)
	{
		if (m_sCreateParams.HasStaticEdge != value)
		{
			m_sCreateParams.HasStaticEdge = value;
			return true;
		}
		return false;
	}

	bool CForm::setHasWindowEdge(const bool value)
	{
		if (m_sCreateParams.HasWindowEdge != value)
		{
			m_sCreateParams.HasWindowEdge = value;
			return true;
		}
		return false;
	}

	bool CForm::setIsPopup(const bool value)
	{
		if (m_sCreateParams.IsPopup != value)
		{
			m_sCreateParams.IsPopup = value;
			return true;
		}
		return false;
	}

	bool CForm::setIsTabStop(const bool value)
	{
		if (m_sCreateParams.IsTabStop != value)
		{
			m_sCreateParams.IsTabStop = value;
			return true;
		}
		return false;
	}

	bool CForm::setIsMDIChild(const bool value)
	{
		if (m_sCreateParams.IsMDIChild != value)
		{
			m_sCreateParams.IsMDIChild = value;
			return true;
		}
		return false;
	}

	bool CForm::setIsToolWindow(const bool value)
	{
		if (m_sCreateParams.IsToolWindow != value)
		{
			m_sCreateParams.IsToolWindow = value;
			return true;
		}
		return false;
	}

	bool CForm::setIsTopMost(const bool value)
	{
		if (m_sCreateParams.IsTopMost != value)
		{
			m_sCreateParams.IsTopMost = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Components
	bool CForm::AttachComponent(IComponent *component)
	{
		if (!component || component->getForm() == this)
			return false;
		CLockRepaint lock{ this };
		bool result{ true };
		if (component->getForm())
			result = component->getForm()->DetachComponent(component);
		if (result)
		{
			GenerateComponentName(component);
			m_aComponents.push_back(component);
			component->QueryService()->setForm(this);
			CNotifier::ComponentAttach(this, component);
		}
		return true;
	}

	bool CForm::DeleteComponent(const int index)
	{
		if (getComponent(index))
		{
			getComponent(index)->Release();
			return true;
		}
		return false;
	}

	bool CForm::DeleteComponent(IComponent *component)
	{
		if (component && component->getForm() == this)
		{
			component->Release();
			return true;
		}
		return false;
	}

	bool CForm::DeleteComponents()
	{
		if (getComponentCount() == 0)
			return false;
		CLockRepaint lock{ this };
		while (getComponentCount() > 0)
			getComponent(0)->Release();
		return true;
	}

	bool CForm::DetachComponent(IComponent *component)
	{
		if (!component || component->getForm() != this)
			return false;
		CLockRepaint lock{ this };
		CNotifier::Detaching(component);
		for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
			if (*pos == component)
			{
				m_aComponents.erase(pos);
				break;
			}
		component->QueryService()->setForm(nullptr);
		QueryService()->UnregisterHotkeys(component);
		QueryService()->UnregisterMessageListeners(component);
		CNotifier::ComponentDetach(this, component);
		return true;
	}
#pragma endregion

#pragma region Controls
	bool CForm::AttachControl(IControl *control)
	{
		return InsertControl(control, getControlCount());
	}

	bool CForm::InsertControl(IControl *control, const int before)
	{
		if (!control || !control->isAcceptForm() || !control->isAcceptForm(this))
			return false;
		CLockRepaint lock{ this }, lock2{ control };
		// Detach control from parent
		if (control->getParent())
			control->getParent()->DetachControl(control);
		else if (control->getForm())
			control->getForm()->DetachControl(control);
		// Add control to list
		int b{ ntl::Max<int>(0, before) };
		if (b < getControlCount())
			m_aControls.insert(m_aControls.begin() + before, control);
		else
			m_aControls.push_back(control);
		// Set parent, form, names, tab indices
		SetFormRecursively(control, this, control->isStaticTabOrder());
		GenerateNameRecursively(control);
		// Align controls if attached control is aligned
		if (control->getAlign() != Align::None)
			QueryService()->AlignControls();
		CNotifier::ControlAttach(this, control);
		control->setDPI(m_sDPI);
		Repaint();
		return true;
	}

	bool CForm::DeleteControl(const int index)
	{
		IControl *control{ getControl(index) };
		if (control)
		{
			control->Release();
			return true;
		}
		return false;
	}

	bool CForm::DeleteControl(IControl *control)
	{
		if (control && !control->getParent() && control->getForm() == this)
		{
			control->Release();
			return true;
		}
		return false;
	}

	bool CForm::DeleteControls()
	{
		if (getControlCount() == 0)
			return false;
		CLockRepaint lock{ this };
		while (getControlCount() > 0)
			getControl(0)->Release();
		return true;
	}

	bool CForm::DetachControl(IControl *control)
	{
		if (!control || control->getParent() || control->getForm() != this)
			return false;
		CLockRepaint lock{ this };
		CNotifier::Detaching(control);
		QueryService()->ProcessControlDetach(control);
		// Remove connections
		for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
			if (*pos == control)
			{
				m_aControls.erase(pos);
				break;
			}
		SetFormRecursively(control, nullptr, control->isStaticTabOrder());
		if (control->getAlign() != Align::None)
			control->QueryService()->AdjustSize();
		// Align controls if detached control was visible and aligned
		if (control->isVisible(false) && control->getAlign() != Align::None)
			QueryService()->AlignControls();
		CNotifier::ControlDetach(this, control);
		UpdateHoveredControl();
		Repaint();
		return true;
	}

	IControl *CForm::FindControl(const String &name, IControl *exclude)
	{
		for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
		{
			if (*pos != exclude && (*pos)->Name == name)
				return *pos;
			IControl *control{ (*pos)->FindControl(name, exclude) };
			if (control)
				return control;
		}
		return nullptr;
	}

	bool CForm::FocusPrevControl()
	{
		IControl *control{ SearchPrevControl(m_pFocusedControl, false) };
		if (control)
			return setFocusedControl(control, FocusedBy::Other, true);
		return false;
	}

	bool CForm::FocusNextControl()
	{
		IControl *control{ SearchNextControl(m_pFocusedControl, false) };
		if (control)
			return setFocusedControl(control, FocusedBy::Other, true);
		return false;
	}

	bool CForm::CaptureKeyboard(IControl *control)
	{
		IControl *capture{ getCaptureKeyboardControl() };
		if (control == capture) // No change is required
			return false;
		if (control)
		{
			if (control->getForm() != this || !control->isEnabled(true) || !control->isVisible(true)) // Should be on this form, should be enabled and visible
				return false;
			if (getModalControl() && control != getModalControl() && !getModalControl()->hasChild(control)) // Should be modal or on modal if there is one
				return false;
		}
		// Change control
		CLockRepaint lock{ this };
		if (capture)
		{
			CNotifier::ControlKillCaptureKeyboard(this, capture);
			auto pos{ m_aCaptureKeyboardControls.begin() };
			while (pos != m_aCaptureKeyboardControls.end())
				if (*pos == capture)
					pos = m_aCaptureKeyboardControls.erase(pos);
				else
					pos++;
		}
		if (control)
		{
			m_aCaptureKeyboardControls.push_back(control);
			CNotifier::ControlSetCaptureKeyboard(this, control);
		}
		else
			m_aCaptureKeyboardControls.clear();
		return true;
	}

	bool CForm::CaptureMouse(IControl *control, const bool system_capture)
	{
		IControl *capture{ getCaptureMouseControl() };
		if (control == capture) // No change is required
			return false;
		if (control)
		{
			if (control->getForm() != this || !control->isEnabled(true) || !control->isVisible(true)) // Control should be on this form, should be enabled and visible
				return false;
			if (getModalControl() && control != getModalControl() && !getModalControl()->hasChild(control)) // Control should be modal or on modal if there is one
				return false;
		}
		// Change control
		CLockRepaint lock{ this };
		if (capture)
		{
			CNotifier::ControlKillCaptureMouse(this, capture);
			if (m_pWindow && m_aCaptureMouseControls[m_aCaptureMouseControls.size() - 1].System)
				m_pWindow->ReleaseMouseCapture();
		}
		if (control)
		{
			auto pos{ m_aCaptureMouseControls.begin() };
			while (pos != m_aCaptureMouseControls.end())
				if (pos->Control == capture)
					pos = m_aCaptureMouseControls.erase(pos);
				else
					pos++;
			m_aCaptureMouseControls.push_back(CAPTURE_MOUSE{ control, system_capture });
			if (system_capture && m_pWindow)
				m_pWindow->CaptureMouse();
			CNotifier::ControlSetCaptureMouse(this, control);
		}
		else
			m_aCaptureMouseControls.clear();
		return true;
	}

	void CForm::ReleaseCaptureKeyboard()
	{
		if (m_aCaptureKeyboardControls.size() > 0)
		{
			CLockRepaint lock{ this };
			CNotifier::ControlKillCaptureKeyboard(this, m_aCaptureKeyboardControls[m_aCaptureKeyboardControls.size() - 1]);
			m_aCaptureKeyboardControls.erase(m_aCaptureKeyboardControls.end() - 1);
			if (m_aCaptureKeyboardControls.size() > 0)
				CNotifier::ControlSetCaptureKeyboard(this, m_aCaptureKeyboardControls[m_aCaptureKeyboardControls.size() - 1]);
		}
	}

	void CForm::ReleaseCaptureMouse()
	{
		if (m_aCaptureMouseControls.size() > 0)
		{
			CLockRepaint lock{ this };
			if (m_aCaptureMouseControls[m_aCaptureMouseControls.size() - 1].System && m_pWindow)
				m_pWindow->ReleaseMouseCapture();
			CNotifier::ControlKillCaptureMouse(this, m_aCaptureMouseControls[m_aCaptureMouseControls.size() - 1].Control);
			m_aCaptureMouseControls.erase(m_aCaptureMouseControls.end() - 1);
			if (m_aCaptureMouseControls.size() > 0)
			{
				if (m_aCaptureMouseControls[m_aCaptureMouseControls.size() - 1].System && m_pWindow)
					m_pWindow->CaptureMouse();
				CNotifier::ControlSetCaptureMouse(this, m_aCaptureMouseControls[m_aCaptureMouseControls.size() - 1].Control);
			}
		}
	}

	void CForm::UpdateHoveredControl()
	{
		if (!m_pWindow)
			return;
		IControl *control{ nullptr };
		PointF position{ -1, -1 };
		if (m_pWindow->isCreated())
		{
			Point t{ m_pWindow->ScreenToClient(Application->Mouse->getPosition()) };
			position = PointF{ (float)t.X, (float)t.Y };
			Rect client{ m_pWindow->getClientRect() };
			if (t.X >= client.Left && t.X < client.Right && t.Y >= client.Top && t.Y < client.Bottom)
			{
				if (getModalControl())
					control = getModalControl()->getControl(position);
				if (!control && getActiveDialogBox())
					control = getActiveDialogBox()->getControl(position);
				if (!control)
					control = getControl(position);
			}
		}
		if (control)
			control = InterceptMouseHover(control->getParent(), control);
		if (control != m_pHoveredControl)
		{
			m_bHintShown = false;
			if (m_hTimerHintDelay)
			{
				m_pWindow->DeleteTimer(m_hTimerHintDelay);
				m_hTimerHintDelay = nullptr;
			}
			CLockRepaint lock{ this };
			if (m_pHoveredControl)
				CNotifier::MouseLeaveControl(this, m_pHoveredControl);
			m_pHoveredControl = control;
			getHint()->Hide(false);
			if (m_pHoveredControl)
			{
				CNotifier::MouseHoverControl(this, m_pHoveredControl, position);
				if (!m_pHoveredControl->getHintText().empty() && m_pHoveredControl->isShowHint() && m_pHoveredControl->isEnabled(false))
				{
					String hint{ m_pHoveredControl->getHintText() };
					if (!m_bInterceptEnabled || !InterceptShowHint(m_pHoveredControl->getParent(), m_pHoveredControl, hint))
						if (!hint.empty())
							m_hTimerHintDelay = m_pWindow->CreateTimer(&m_cTimerListener, m_pHoveredControl->getHintDelay());
				}
				if (!m_bInterceptEnabled || !InterceptSetCursor(m_pHoveredControl->getParent(), m_pHoveredControl))
					m_pWindow->setCursor(m_pHoveredControl->getCursor());
			}
			else
			{
				if (m_pHint)
					m_pHint->Hide(false);
				if (m_bShowHint && !m_sHintText.empty())
					m_hTimerHintDelay = m_pWindow->CreateTimer(&m_cTimerListener, m_fHintDelay);
				m_pWindow->setCursor(m_eCursor);
			}
		}
		else
		{
			if (m_pHoveredControl && (!m_bInterceptEnabled || !InterceptSetCursor(m_pHoveredControl->getParent(), m_pHoveredControl)))
				m_pWindow->setCursor(m_pHoveredControl->getCursor());
			if (!m_pHoveredControl && !m_bHintShown && m_bShowHint && !m_sHintText.empty() && !m_hTimerHintDelay)
				m_hTimerHintDelay = m_pWindow->CreateTimer(&m_cTimerListener, m_fHintDelay);
		}
	}

	void CForm::ReleaseModal()
	{
		if (m_aModalControls.size() > 0)
		{
			CLockRepaint lock{ this };
			CNotifier::ControlKillModal(this, m_aModalControls[m_aModalControls.size() - 1]);
			m_aModalControls.erase(m_aModalControls.end() - 1);
			if (m_aModalControls.size() > 0)
			{
				CNotifier::ControlSetModal(this, m_aModalControls[m_aModalControls.size() - 1]);
				DoOnChangeModalControl();
			}
			UpdateHoveredControl();
		}
	}
#pragma endregion

#pragma region Repaint
	void CForm::LockRepaint()
	{
		if (m_iRepaintLockCount == 0)
		{
			m_sRepaintRect = Rect{ 0, 0, 0, 0 }; // Repaint area is empty
			m_bRepaintRequired = false;
		}
		m_iRepaintLockCount++;
	}

	void CForm::UnlockRepaint()
	{
		if (m_iRepaintLockCount == 0)
			return;
		if (m_iRepaintLockCount == 1)
		{
			m_iRepaintLockCount++;
			UpdateHoveredControl();
			m_iRepaintLockCount = 0;
			if (m_bRepaintRequired)
				Repaint(m_sRepaintRect);
			RunTasks();
		}
		else
			m_iRepaintLockCount--;
	}

	void CForm::Repaint()
	{
		Repaint(Rect{ 0, 0, -1, 1 });
	}

	void CForm::Repaint(const Rect &rect, const bool force)
	{
		if (force || m_sRepaintRect.is_valid()) // If repaint area is not valid, it means all client area should be repainter. Otherwise perform another checks
		{
			if (!rect.is_valid()) // Repaint all client area if clip rectangle is not valid
				m_sRepaintRect = Rect{ 0, 0, -1, -1 };
			else if (force || m_sRepaintRect.is_zero()) // If current clip rectangle is empty, use specified clip rectangle
				m_sRepaintRect = rect;
			else // Extend current clip rectangle to include specified clip rectangle
				m_sRepaintRect += rect;
		}
		if (m_iRepaintLockCount)
		{
			m_bRepaintRequired = true;
			return;
		}
		Render();
	}

	void CForm::Repaint(const RectF &rect, const bool force)
	{
		Repaint(Rect{
				rect.Left < 0 ? ntl::Round<int>(rect.Left - 0.5f) : int(rect.Left),
				rect.Top < 0 ? ntl::Round<int>(rect.Top - 0.5f) : int(rect.Top),
				rect.Right > 0 ? ntl::Round<int>(rect.Right + 0.5f) : int(rect.Right),
				rect.Bottom > 0 ? ntl::Round<int>(rect.Bottom + 0.5f) : int(rect.Bottom)
			}, force);
	}

	void CForm::Render()
	{
		if (m_bRendering || !m_pWindow || !m_pWindow->isCreated() || !m_pRenderer || !m_pWindow->isVisible())
			return;
		Rect rect{ m_pWindow->getClientRect() };
		// Calculate repaint rectangle
		Rect client{ 0, 0, rect.width(), rect.height() }, clip{ client };
		if (m_sRepaintRect.is_valid())
		{
			if (m_sRepaintRect.is_zero()) // Repaint is not required
				return;
			else
				clip *= m_sRepaintRect; // Repaint rectangle is intersection of repaint rectangle and actual buffer size
		}
		m_bRendering = true;
		// Clear
	/*#ifdef _DEBUG
		auto start{ std::chrono::high_resolution_clock::now() };
		std::cout << __FUNCTION__ << "...";
	#endif*/
		if (m_pRenderer->DrawBegin(clip, m_pWindow))
		{
			// Find control which should be drawn last
			IControl *draw_last{ getModalControl() };
			if (!draw_last)
				draw_last = getActiveDialogBox();
			IControl *draw_last_parent{ draw_last };
			if (draw_last_parent)
			{
				while (draw_last_parent->getParent())
					draw_last_parent = draw_last_parent->getParent();
			}
			// Build ordered control list
			std::vector<IControl*> controls;
			for (auto pos : m_aControls)
				if (pos->isVisible(false) && pos != draw_last_parent)
					controls.push_back(pos);
			std::sort(controls.begin(), controls.end(), [](IControl *a, IControl *b) { return a->getZIndex() < b->getZIndex(); });
			// Draw in two steps
			for (int i = 0; i < 2; i++)
			{
				MessagePaint m{ clip, i > 0 };
				bool draw_children{ true };
				QueryService()->NotifyOnPaint(m, draw_children);
				if (OnPaint)
					OnPaint(this, m, draw_children);
				if (draw_children)
					for (auto pos : controls)
						CNotifier::Render(pos, m, nullptr);
				if (draw_last_parent)
					CNotifier::Render(draw_last_parent, m, draw_last);
				QueryService()->NotifyOnPaintEnd(m);
				if (OnPaintEnd)
					OnPaintEnd(this, m);
			}
			if (m_pHint)
				m_pHint->Render();
			m_pRenderer->DrawEnd();
			m_pRenderer->Present();
		}
		// Reset repaint area
		m_sRepaintRect = Rect{ 0, 0, 0, 0 };
	/*#ifdef _DEBUG
		std::chrono::microseconds duration{ std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start) };
		float fps{ 1000000 / (float)duration.count() };
		std::cout << std::fixed << std::setprecision(3) << fps << " FPS" << std::endl;
		if (OnRender)
			OnRender(this, fps);
	#endif*/
		m_bRendering = false;
	}

	void CForm::Refresh()
	{
		for (auto control : m_aControls)
			control->Refresh(true);
	}
#pragma endregion

#pragma region Hotkeys
	bool CForm::RegisterHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
	{
		for (auto pos = m_aHotkeys.begin(); pos != m_aHotkeys.end(); pos++)
			if (!pos->Component && !pos->Control && pos->Key == key && pos->Ctrl == ctrl && pos->Alt == alt && pos->Shift == shift && pos->Down == is_down)
				return false;
		m_aHotkeys.push_back({ key, ctrl, alt, shift, is_down, nullptr, nullptr });
		return true;
	}

	bool CForm::UnregisterHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
	{
		for (auto pos = m_aHotkeys.begin(); pos != m_aHotkeys.end(); pos++)
			if (!pos->Component && !pos->Control && pos->Key == key && pos->Ctrl == ctrl && pos->Alt == alt && pos->Shift == shift && pos->Down == is_down)
			{
				m_aHotkeys.erase(pos);
				return true;
			}
		return false;
	}

	bool CForm::UnregisterHotkeys()
	{
		bool result{ false };
		auto pos{ m_aHotkeys.begin() };
		while (pos != m_aHotkeys.end())
			if (!pos->Component && !pos->Control)
			{
				pos = m_aHotkeys.erase(pos);
				result = true;
			}
			else
				pos++;
		return result;
	}
#pragma endregion

#pragma region Helpers
	IFormService *CForm::QueryService()
	{
		if (!m_pService)
			m_pService = new CFormService(this);
		return m_pService;
	}

	void CForm::CopyFont(IFont *dest, IFontProperties *src)
	{
		if (dest && src)
		{
			m_bIgnoreFont = true;
			dest->Copy(src);
			m_bIgnoreFont = false;
		}
	}

	void CForm::CopyTransform(ITransform *dest, ITransform *src)
	{
		if (dest && src)
		{
			m_bIgnoreTransformControls = true;
			dest->setRotateOrder(src->getRotateOrder());
			dest->setTransformOrder(src->getTransformOrder());
			dest->Transform(src->getTx(), src->getTy(), src->getTz(), src->getSx(), src->getSy(), src->getSz(), src->getRx(), src->getRy(), src->getRz());
			m_bIgnoreTransformControls = false;
		}
	}

	void CForm::CopyCaret(ICaret *dest, ICaret *src)
	{
		if (dest && src)
		{
			m_bIgnoreCaret = true;
			dest->setIntervalVisible(src->getIntervalVisible());
			dest->setIntervalHidden(src->getIntervalHidden());
			dest->setSize(src->getSize());
			dest->setVisible(src->isVisible());
			m_bIgnoreCaret = false;
		}
	}

	void CForm::GenerateComponentName(IComponent *component)
	{
		component->QueryService()->setName(QueryService()->GenerateComponentName(component));
	}

	void CForm::SetFormRecursively(IControl *control, IForm *form, const bool static_tab_order)
	{
		control->QueryService()->setForm(form);
		if (form && !static_tab_order && !control->isStaticTabOrder())
			control->QueryService()->setTabOrder(form->QueryService()->GenerateTabOrder(control));
		for (int i = 0; i < control->getControlCount(); i++)
			SetFormRecursively(control->getControl(i), form, static_tab_order || control->isStaticTabOrder());
	}

	void CForm::GenerateNameRecursively(IControl *control)
	{
		control->QueryService()->setName(QueryService()->GenerateControlName(control));
		for (int i = 0; i < control->getControlCount(); i++)
			GenerateNameRecursively(control->getControl(i));
	}

	IControl *CForm::SearchPrevControl(IControl *control, const bool tab_stop_only)
	{
		std::vector<IControl *> controls;
		if (control)
			controls.push_back(control);
		if (!getModalControl())
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				EnumControls(controls, *pos, control, tab_stop_only);
		}
		else
			EnumControls(controls, getModalControl(), control, tab_stop_only);
		std::sort(controls.begin(), controls.end(), [](IControl *a, IControl *b) {
			return a->getTabOrder() < b->getTabOrder();
		});
		int index{ -1 };
		for (auto pos = controls.begin(); pos != controls.end(); pos++)
			if (*pos == control)
			{
				index = int(pos - controls.begin());
				break;
			}
		if (index > 0)
			return controls[index - 1];
		if (index < (int)controls.size() - 1)
			return controls[controls.size() - 1];
		return nullptr;
	}

	IControl *CForm::SearchNextControl(IControl *control, const bool tab_stop_only)
	{
		std::vector<IControl *> controls;
		if (control)
			controls.push_back(control);
		if (!getModalControl())
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				EnumControls(controls, *pos, control, tab_stop_only);
		}
		else
			EnumControls(controls, getModalControl(), control, tab_stop_only);
		std::sort(controls.begin(), controls.end(), [](IControl *a, IControl *b) {
			return a->getTabOrder() < b->getTabOrder();
		});
		int index{ -1 };
		for (auto pos = controls.begin(); pos != controls.end(); pos++)
			if (*pos == control)
			{
				index = int(pos - controls.begin());
				break;
			}
		if (index < (int)controls.size() - 1)
			return controls[index + 1];
		if (index > 0)
			return controls[0];
		return nullptr;
	}

	void CForm::EnumControls(std::vector<IControl*> &controls, IControl *control, IControl *exclude, const bool tab_stop_only)
	{
		if (control->isVisible(false) && control->isEnabled(false))
		{
			if (control != exclude && control->isAcceptFocus() && (!tab_stop_only || control->isTabStop()))
				controls.push_back(control);
			if (!m_bInterceptEnabled || !control->QueryService()->InterceptTabOrder())
				for (int i = 0; i < control->getControlCount(); i++)
					EnumControls(controls, control->getControl(i), exclude, tab_stop_only);
		}
	}

	bool CForm::ProcessTabDown(const Key key)
	{
		if (key == Key::Tab)
		{
			bool ctrl, shift, alt;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (!ctrl && !alt)
			{
				if (shift)
				{
					IControl *control{ SearchPrevControl(m_pFocusedControl, true) };
					if (control && control != m_pFocusedControl)
						setFocusedControl(control, FocusedBy::ShiftTab, true);
				}
				else
				{
					IControl *control{ SearchNextControl(m_pFocusedControl, true) };
					if (control && control != m_pFocusedControl)
						setFocusedControl(control, FocusedBy::Tab, true);
				}
				return true;
			}
		}
		return false;
	}

	void CForm::ProcessDownHotkeys(const Key key)
	{
		if (m_aHotkeys.size() > 0)
		{
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			for (auto pos : m_aHotkeys)
				if (pos.Down && pos.Key == key && pos.Ctrl == ctrl && pos.Alt == alt && pos.Shift == shift)
				{
					MessageHotkey m{ pos.Key, pos.Ctrl, pos.Alt, pos.Shift, pos.Down };
					if (pos.Component)
					{
						pos.Component->QueryService()->NotifyOnHotkey(m);
						if (pos.Component->OnHotkey)
							pos.Component->OnHotkey(pos.Component, m);
					}
					else if (pos.Control)
					{
						if (!m_bInterceptEnabled || !InterceptHotkeys(pos.Control->getParent(), pos.Control, m))
						{
							pos.Control->QueryService()->NotifyOnHotkey(m);
							if (pos.Control->OnHotkey)
								pos.Control->OnHotkey(pos.Control, m);
						}
					}
					else
					{
						QueryService()->NotifyOnHotkey(m);
						if (OnHotkey)
							OnHotkey(this, m);
					}
				}
		}
	}

	void CForm::ProcessUpHotkeys(const Key key)
	{
		if (m_aHotkeys.size() > 0)
		{
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			for (auto pos : m_aHotkeys)
				if (!pos.Down && pos.Key == key && pos.Ctrl == ctrl && pos.Alt == alt && pos.Shift == shift)
				{
					MessageHotkey m{ pos.Key, pos.Ctrl, pos.Alt, pos.Shift, pos.Down };
					if (pos.Component)
					{
						pos.Component->QueryService()->NotifyOnHotkey(m);
						if (pos.Component->OnHotkey)
							pos.Component->OnHotkey(pos.Component, m);
					}
					else if (pos.Control)
					{
						if (!m_bInterceptEnabled || !InterceptHotkeys(pos.Control->getParent(), pos.Control, m))
						{
							pos.Control->QueryService()->NotifyOnHotkey(m);
							if (pos.Control->OnHotkey)
								pos.Control->OnHotkey(pos.Control, m);
						}
					}
					else
					{
						QueryService()->NotifyOnHotkey(m);
						if (OnHotkey)
							OnHotkey(this, m);
					}
				}
		}
	}

	bool CForm::setFocusedControl(IControl *value, const FocusedBy focused_by, const bool activate_dialog_box)
	{
		if (value == m_pFocusedControl) // Already focused
			return false;
		if (value)
		{
			if (value->getForm() != this || !value->isAcceptFocus() || !value->isVisible(true) || !value->isEnabled(true)) // Should be on form, accept focus, be visible and enabled globally
				return false;
			if (getModalControl() && value != getModalControl() && !getModalControl()->hasChild(value)) // Should be on modal if there is one
				return false;
		}
		CLockRepaint lock{ this };
		if (m_pFocusedControl)
			CNotifier::ControlKillFocus(this, m_pFocusedControl);
		IControl *old_focused_control{ m_pFocusedControl };
		m_pFocusedControl = value;
		m_pFocusedControlOld = nullptr;
		if (m_pActiveControl && m_pActiveControl != m_pFocusedControl)
			setActiveControl(nullptr);
		if (m_pFocusedControl)
		{
			if (activate_dialog_box && !getModalControl())
			{
				IControl *control{ m_pFocusedControl };
				IDialogBox *dialog_box;
				while (control)
				{
					if ((dialog_box = cast<IDialogBox*>(control)))
					{
						setActiveDialogBox(dialog_box);
						break;
					}
					control = control->getParent();
				}
			}
			CNotifier::ControlSetFocus(this, m_pFocusedControl, old_focused_control, focused_by);
		}
		return true;
	}
#pragma endregion

#pragma region Window actions
	bool CForm::Show()
	{
		if (m_pWindow)
			return m_pWindow->Show();
		return false;
	}

	ModalResult CForm::ShowModal()
	{
		if (m_pWindow)
			return m_pWindow->ShowModal();
		return ModalResult::None;
	}

	bool CForm::Hide()
	{
		if (m_pWindow)
			return m_pWindow->Hide();
		return false;
	}

	PlatformHandle CForm::CreateTimer(ITimerListener *listener, const float interval)
	{
		if (m_pWindow)
			return m_pWindow->CreateTimer(listener, interval);
		return 0;
	}

	bool CForm::DeleteTimer(const PlatformHandle id)
	{
		if (m_pWindow)
			return m_pWindow->DeleteTimer(id);
		return false;
	}

	void CForm::DeleteTimers()
	{
		if (m_pWindow)
			m_pWindow->DeleteTimers();
	}

	bool CForm::ResetTimer(const PlatformHandle id, const float interval)
	{
		if (m_pWindow)
			return m_pWindow->ResetTimer(id, interval);
		return false;
	}

	bool CForm::Maximize()
	{
		if (m_pWindow)
			return m_pWindow->Maximize();
		return false;
	}

	bool CForm::Minimize()
	{
		if (m_pWindow)
			return m_pWindow->Minimize();
		return false;
	}

	bool CForm::Restore()
	{
		if (m_pWindow)
			return m_pWindow->Restore();
		return false;
	}

	bool CForm::Close()
	{
		if (m_pWindow)
			return m_pWindow->Close();
		return false;
	}

	bool CForm::CopyStringToClipboard(const String &str)
	{
		if (m_pWindow)
			return m_pWindow->CopyStringToClipboard(str);
		return false;
	}

	bool CForm::CopyStringFromClipboard()
	{
		if (m_pWindow)
			return m_pWindow->CopyStringFromClipboard();
		return false;
	}

	Rect CForm::ScreenToClient(const Rect &rect)
	{
		if (m_pWindow)
			return m_pWindow->ScreenToClient(rect);
		return rect;
	}

	Point CForm::ScreenToClient(const Point &pos)
	{
		if (m_pWindow)
			return m_pWindow->ScreenToClient(pos);
		return pos;
	}

	Rect CForm::ClientToScreen(const Rect &rect)
	{
		if (m_pWindow)
			return m_pWindow->ClientToScreen(rect);
		return rect;
	}

	Point CForm::ClientToScreen(const Point &pos)
	{
		if (m_pWindow)
			return m_pWindow->ClientToScreen(pos);
		return pos;
	}
#pragma endregion

#pragma region Interceptors
	bool CForm::InterceptSetCursor(IControl *parent, IControl *control)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptSetCursor(control))
			return true;
		return InterceptSetCursor(parent->getParent(), control);
	}

	IControl *CForm::InterceptMouseHover(IControl *parent, IControl *control)
	{
		if (!m_bInterceptEnabled || !parent)
			return control;
		if (parent->QueryService()->InterceptMouseHover(control))
			return parent;
		return InterceptMouseHover(parent->getParent(), control);
	}

	bool CForm::InterceptShowHint(IControl *parent, IControl *control, String &hint)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptShowHint(control, hint))
			return true;
		return InterceptShowHint(parent->getParent(), control, hint);
	}

	bool CForm::InterceptHotkeys(IControl *parent, IControl *control, const MessageHotkey &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptHotkeys(control, m))
			return true;
		return InterceptHotkeys(parent->getParent(), control, m);
	}

	bool CForm::InterceptKeyDown(IControl *parent, IControl *control, const MessageKey &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptKeyDown(control, m))
			return true;
		return InterceptKeyDown(parent->getParent(), control, m);
	}

	bool CForm::InterceptKeyUp(IControl *parent, IControl *control, const MessageKey &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptKeyUp(control, m))
			return true;
		return InterceptKeyUp(parent->getParent(), control, m);
	}

	bool CForm::InterceptChar(IControl *parent, IControl *control, const MessageChar &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptChar(control, m))
			return true;
		return InterceptChar(parent->getParent(), control, m);
	}

	bool CForm::InterceptDeadChar(IControl *parent, IControl *control, const MessageChar &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptDeadChar(control, m))
			return true;
		return InterceptDeadChar(parent->getParent(), control, m);
	}

	bool CForm::InterceptMouseMove(IControl *parent, IControl *control, const MessageMouse &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptMouseMove(control, m))
			return true;
		return InterceptMouseMove(parent->getParent(), control, m);
	}

	bool CForm::InterceptLeftMouseButtonDown(IControl *parent, IControl *control, const MessageMouse &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptLeftMouseButtonDown(control, m))
			return true;
		return InterceptLeftMouseButtonDown(parent->getParent(), control, m);
	}

	bool CForm::InterceptLeftMouseButtonUp(IControl *parent, IControl *control, const MessageMouse &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptLeftMouseButtonUp(control, m))
			return true;
		return InterceptLeftMouseButtonUp(parent->getParent(), control, m);
	}

	bool CForm::InterceptLeftMouseButtonDoubleClick(IControl *parent, IControl *control, const MessageMouse &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptLeftMouseButtonDoubleClick(control, m))
			return true;
		return InterceptLeftMouseButtonDoubleClick(parent->getParent(), control, m);
	}

	bool CForm::InterceptMiddleMouseButtonDown(IControl *parent, IControl *control, const MessageMouse &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptMiddleMouseButtonDown(control, m))
			return true;
		return InterceptMiddleMouseButtonDown(parent->getParent(), control, m);
	}

	bool CForm::InterceptMiddleMouseButtonUp(IControl *parent, IControl *control, const MessageMouse &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptMiddleMouseButtonUp(control, m))
			return true;
		return InterceptMiddleMouseButtonUp(parent->getParent(), control, m);
	}

	bool CForm::InterceptMiddleMouseButtonDoubleClick(IControl *parent, IControl *control, const MessageMouse &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptMiddleMouseButtonDoubleClick(control, m))
			return true;
		return InterceptMiddleMouseButtonDoubleClick(parent->getParent(), control, m);
	}

	bool CForm::InterceptRightMouseButtonDown(IControl *parent, IControl *control, const MessageMouse &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptRightMouseButtonDown(control, m))
			return true;
		return InterceptRightMouseButtonDown(parent->getParent(), control, m);
	}

	bool CForm::InterceptRightMouseButtonUp(IControl *parent, IControl *control, const MessageMouse &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptRightMouseButtonUp(control, m))
			return true;
		return InterceptRightMouseButtonUp(parent->getParent(), control, m);
	}

	bool CForm::InterceptRightMouseButtonDoubleClick(IControl *parent, IControl *control, const MessageMouse &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptRightMouseButtonDoubleClick(control, m))
			return true;
		return InterceptRightMouseButtonDoubleClick(parent->getParent(), control, m);
	}

	bool CForm::InterceptMouseVerticalWheel(IControl *parent, IControl *control, const MessageMouseWheel &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptMouseVerticalWheel(control, m))
			return true;
		return InterceptMouseVerticalWheel(parent->getParent(), control, m);
	}

	bool CForm::InterceptMouseHorizontalWheel(IControl *parent, IControl *control, const MessageMouseWheel &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptMouseHorizontalWheel(control, m))
			return true;
		return InterceptMouseHorizontalWheel(parent->getParent(), control, m);
	}

	bool CForm::InterceptDropFiles(IControl *parent, IControl *control, const MessageDropFiles &m)
	{
		if (!parent)
			return false;
		if (parent->QueryService()->InterceptDropFiles(control, m))
			return true;
		return InterceptDropFiles(parent->getParent(), control, m);
	}

	IControl *CForm::InterceptFocus(IControl *parent, IControl *control, const FocusedBy focused_by)
	{
		if (!m_bInterceptEnabled || !parent)
			return control;
		if (parent->QueryService()->InterceptFocus(control, focused_by))
			return parent;
		return InterceptFocus(parent->getParent(), control, focused_by);
	}
#pragma endregion

#pragma region Tasks
	bool CForm::AddTask(ITask *task)
	{
		if (task && std::find(m_aTasks.begin(), m_aTasks.end(), task) == m_aTasks.end())
		{
			m_aTasks.push_back(task);
			return true;
		}
		return false;
	}

	bool CForm::DeleteTask(const int index)
	{
		if (index >= 0 && index < (int)m_aTasks.size())
		{
			m_aTasks[index]->Release();
			m_aTasks.erase(m_aTasks.begin() + index);
			return true;
		}
		return false;
	}

	bool CForm::DeleteTask(ITask *task)
	{
		if (task)
		{
			auto pos{ std::find(m_aTasks.begin(), m_aTasks.end(), task) };
			if (pos != m_aTasks.end())
			{
				task->Release();
				m_aTasks.erase(pos);
				return true;
			}
		}
		return false;
	}

	void CForm::DeleteTasks()
	{
		for (auto task : m_aTasks)
			task->Release();
		m_aTasks.clear();
	}

	void CForm::RunTasks()
	{
		if (!m_bTasksRunning)
		{
			m_bTasksRunning = true;
			while (m_aTasks.size() > 0)
			{
				ITask *task{ m_aTasks[0] };
				m_aTasks.erase(m_aTasks.begin());
				task->Run();
				task->Release();
			}
			m_bTasksRunning = false;
		}
	}
#pragma endregion

#pragma region Hint actions
	bool CForm::ShowHint(const String &text, const Point &position)
	{
		if (text.length() > 0 && m_pHint && m_pWindow && m_pWindow->isCreated())
		{
			m_pHint->Hide(false);
			if (m_hTimerHintDelay)
			{
				m_pWindow->DeleteTimer(m_hTimerHintDelay);
				m_hTimerHintDelay = nullptr;
			}
			m_pHint->Show(text, position, m_pWindow->getClientRect());
			return true;
		}
		return false;
	}

	bool CForm::ShowHint(IControl *control, const PointF &position)
	{
		if (control && control->getForm() == this && control->isVisible(true))
			return ShowHint(control->getHintText(), Round(control->LocalToForm(position)));
		return false;
	}
#pragma endregion
}