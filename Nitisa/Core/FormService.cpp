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
#pragma region Constructor & destructor
	CFormService::CFormService(CForm *form) :m_pForm{ form }
	{

	}

	void CFormService::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	IWindow *CFormService::getWindow()
	{
		return m_pForm->m_pWindow;
	}
#pragma endregion

#pragma region Setters
	void CFormService::setWindow(IWindow *value)
	{
		m_pForm->m_pWindow = value;
		m_pForm->InitializeWindow();
	}

	void CFormService::setRenderer(IRenderer *value)
	{
		m_pForm->m_pRenderer = value;
	}
#pragma endregion

#pragma region Helpers
	IControl *CFormService::FindControlByTabOrder(const int tab_order)
	{
		for (auto control : m_pForm->m_aControls)
		{
			if (control->getTabOrder() == tab_order)
				return control;
			IControl *result{ FindControlByTabOrder(control, tab_order) };
			if (result)
				return result;
		}
		return nullptr;
	}

	IControl *CFormService::FindControlByTabOrder(IControl *parent, const int tab_order)
	{
		for (int i = 0; i < parent->getControlCount(); i++)
		{
			if (parent->getControl(i)->getTabOrder() == tab_order)
				return parent->getControl(i);
			IControl *result{ FindControlByTabOrder(parent->getControl(i), tab_order) };
			if (result)
				return result;
		}
		return nullptr;
	}

	void CFormService::UpdateTabOrders(const int old_tab_order, const int new_tab_order)
	{
		IControl *control1{ FindControlByTabOrder(old_tab_order) };
		IControl *control2{ FindControlByTabOrder(new_tab_order) };
		control1->QueryService()->setTabOrder(new_tab_order);
		if (control2)
			control2->QueryService()->setTabOrder(old_tab_order);
	}

	void CFormService::EnumControls(StringArray &names, IControl *control, IControl *exclude)
	{
		if (control != exclude)
			names.push_back(control->Name);
		for (int i = 0; i < control->getControlCount(); i++)
			EnumControls(names, control->getControl(i), exclude);
	}

	void CFormService::EnumTabOrders(IntegerArray &orders, IControl *control, IControl *exclude)
	{
		if (control != exclude)
			orders.push_back(control->getTabOrder());
		for (int i = 0; i < control->getControlCount(); i++)
			EnumTabOrders(orders, control->getControl(i), exclude);
	}

	String CFormService::GenerateComponentName(IComponent *component)
	{
		StringArray names;
		for (auto pos = m_pForm->m_aComponents.begin(); pos != m_pForm->m_aComponents.end(); pos++)
			if (*pos != component)
				names.push_back((*pos)->Name);
		std::sort(names.begin(), names.end());
		String name{ component->Name };
		int index{ 0 };
		if (name.empty())
		{
			index++;
			name = component->ClassName + ToString(index);
		}
		while (true)
		{
			auto pos = std::lower_bound(names.begin(), names.end(), name);
			if (pos == names.end() || *pos != name)
				break;
			index++;
			name = component->ClassName + ToString(index);
		}
		return name;
	}

	String CFormService::GenerateControlName(IControl *control)
	{
		StringArray names;
		for (auto pos = m_pForm->m_aControls.begin(); pos != m_pForm->m_aControls.end(); pos++)
			EnumControls(names, *pos, control);
		std::sort(names.begin(), names.end());
		String name{ control->Name };
		int index{ 0 };
		if (name.empty())
		{
			index++;
			name = control->ClassName + ToString(index);
		}
		while (true)
		{
			auto pos = std::lower_bound(names.begin(), names.end(), name);
			if (pos == names.end() || *pos != name)
				break;
			index++;
			name = control->ClassName + ToString(index);
		}
		return name;
	}

	bool CFormService::MoveControl(IControl *control, const int before)
	{
		if (nitisa::MoveControl(m_pForm->m_aControls, m_pForm, control, before))
		{
			AlignControls();
			return true;
		}
		return false;
	}

	bool CFormService::RegisterHotkey(IComponent *component, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
	{
		if (!component || component->getForm() != m_pForm)
			return false;
		for (auto pos = m_pForm->m_aHotkeys.begin(); pos != m_pForm->m_aHotkeys.end(); pos++)
			if (pos->Component == component && pos->Key == key && pos->Ctrl == ctrl && pos->Alt == alt && pos->Shift == shift && pos->Down == is_down)
			{
				pos->RefCount++;
				return true;
			}
		m_pForm->m_aHotkeys.push_back({ key, ctrl, alt, shift, is_down, component, nullptr });
		return true;
	}

	bool CFormService::UnregisterHotkey(IComponent *component, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
	{
		if (!component)
			return false;
		for (auto pos = m_pForm->m_aHotkeys.begin(); pos != m_pForm->m_aHotkeys.end(); pos++)
			if (pos->Component == component && pos->Key == key && pos->Ctrl == ctrl && pos->Alt == alt && pos->Shift == shift && pos->Down == is_down)
			{
				if (--pos->RefCount <= 0)
					m_pForm->m_aHotkeys.erase(pos);
				return true;
			}
		return false;
	}

	bool CFormService::UnregisterHotkeys(IComponent *component)
	{
		if (!component)
			return false;
		bool result{ false };
		auto pos{ m_pForm->m_aHotkeys.begin() };
		while (pos != m_pForm->m_aHotkeys.end())
			if (pos->Component == component)
			{
				pos = m_pForm->m_aHotkeys.erase(pos);
				result = true;
			}
			else
				pos++;
		return result;
	}

	bool CFormService::RegisterHotkey(IControl *control, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
	{
		if (!control || control->getForm() != m_pForm)
			return false;
		for (auto pos = m_pForm->m_aHotkeys.begin(); pos != m_pForm->m_aHotkeys.end(); pos++)
			if (pos->Control == control && pos->Key == key && pos->Ctrl == ctrl && pos->Alt == alt && pos->Shift == shift && pos->Down == is_down)
			{
				pos->RefCount++;
				return true;
			}
		m_pForm->m_aHotkeys.push_back({ key, ctrl, alt, shift, is_down, nullptr, control });
		return true;
	}

	bool CFormService::UnregisterHotkey(IControl *control, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
	{
		if (!control)
			return false;
		for (auto pos = m_pForm->m_aHotkeys.begin(); pos != m_pForm->m_aHotkeys.end(); pos++)
			if (pos->Control == control && pos->Key == key && pos->Ctrl == ctrl && pos->Alt == alt && pos->Shift == shift && pos->Down == is_down)
			{
				if (--pos->RefCount <= 0)
					m_pForm->m_aHotkeys.erase(pos);
				return true;
			}
		return false;
	}

	bool CFormService::UnregisterHotkeys(IControl *control)
	{
		if (!control)
			return false;
		bool result{ false };
		auto pos{ m_pForm->m_aHotkeys.begin() };
		while (pos != m_pForm->m_aHotkeys.end())
			if (pos->Control == control)
			{
				pos = m_pForm->m_aHotkeys.erase(pos);
				result = true;
			}
			else
				pos++;
		return result;
	}

	void CFormService::AlignControls()
	{
		if (m_pForm->m_pWindow && m_pForm->m_pWindow->isCreated())
		{
			CLockRepaint lock{ m_pForm };
			RectF client{ (RectF)m_pForm->m_pWindow->getClientRect() };
			client.Left += m_pForm->m_sBorderWidth.Left + m_pForm->m_sPadding.Left;
			client.Top += m_pForm->m_sBorderWidth.Top + m_pForm->m_sPadding.Top;
			client.Right -= m_pForm->m_sBorderWidth.Right + m_pForm->m_sPadding.Right;
			client.Bottom -= m_pForm->m_sBorderWidth.Bottom + m_pForm->m_sPadding.Bottom;
			client.validate();
			for (auto control : m_pForm->m_aControls)
			{
				if (!control->isVisible(false) || control->getAlign() == Align::None)
					continue;
				// Calculate new size
				PointF size{ AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints()) };
				PointF new_pos;
				// Deal with coordinates relative to client area(control is transformed)
				switch (control->getAlign())
				{
				case Align::Left:
					size = PointF{ size.X, client.height() };
					new_pos = PointF{ client.Left, client.Top };
					client.Left += size.X;
					break;
				case Align::Top:
					size = PointF{ client.width(), size.Y };
					new_pos = PointF{ client.Left, client.Top };
					client.Top += size.Y;
					break;
				case Align::Right:
					size = PointF{ size.X, client.height() };
					new_pos = PointF{ client.Right - size.X, client.Top };
					client.Right -= size.X;
					break;
				case Align::Bottom:
					size = PointF{ client.width(), size.Y };
					new_pos = PointF{ client.Left, client.Bottom - size.Y };
					client.Bottom -= size.Y;
					break;
				default: //alClient
					size = PointF{ client.width(), client.height() };
					new_pos = PointF{ client.Left, client.Top };
					client.Right = client.Left;
					client.Bottom = client.Top;
					break;
				}
				control->getTransform()->QueryService()->Transform(new_pos.X, new_pos.Y, 0, 1, 1, 1, 0, 0, 0);
				if (IsNotEqual(size, control->getSize()))
				{
					control->Repaint(false);
					control->QueryService()->setSize(size);
					control->QueryService()->AlignControls();
					CNotifier::Resize(control);
					control->Repaint(false);
				}
			}
		}
	}

	int CFormService::GenerateTabOrder(IControl *control)
	{
		IntegerArray orders;
		for (auto pos : m_pForm->m_aControls)
			EnumTabOrders(orders, pos, control);
		std::sort(orders.begin(), orders.end());
		int result{ ntl::Max<int>(0, control->getTabOrder()) };
		auto p{ std::lower_bound(orders.begin(), orders.end(), result) };
		if (p == orders.end() || (*p) != result)
			return result;
		result = -1;
		do
		{
			result++;
			p = std::find(orders.begin(), orders.end(), result);
		} while (p != orders.end() && (*p) == result);
		return result;
	}

	bool CFormService::RegisterMessageListener(IComponent *component, IWindowListenerOnMessage *listener)
	{
		if (component && listener && component->getForm() == m_pForm)
		{
			m_pForm->m_aMessageListeners.push_back({ component, listener });
			return true;
		}
		return false;
	}

	bool CFormService::UnregisterMessageListener(IComponent *component, IWindowListenerOnMessage *listener)
	{
		bool result{ false };
		auto pos{ m_pForm->m_aMessageListeners.begin() };
		while (pos != m_pForm->m_aMessageListeners.end())
			if (pos->Component == component && pos->Listener == listener)
			{
				pos = m_pForm->m_aMessageListeners.erase(pos);
				result = true;
			}
			else
				pos++;
		return result;
	}

	bool CFormService::UnregisterMessageListeners(IComponent *component)
	{
		bool result{ false };
		auto pos{ m_pForm->m_aMessageListeners.begin() };
		while (pos != m_pForm->m_aMessageListeners.end())
			if (pos->Component == component)
			{
				pos = m_pForm->m_aMessageListeners.erase(pos);
				result = true;
			}
			else
				pos++;
		return result;
	}

	void CFormService::ProcessControlDisable(IControl *control)
	{
		// Capture keyboard
		if (m_pForm->m_aCaptureKeyboardControls.size() > 0)
		{
			IControl *old_control{ m_pForm->m_aCaptureKeyboardControls[m_pForm->m_aCaptureKeyboardControls.size() - 1] };
			auto pos{ m_pForm->m_aCaptureKeyboardControls.begin() };
			while (pos != m_pForm->m_aCaptureKeyboardControls.end())
				if (*pos == control || control->hasChild(*pos))
					pos = m_pForm->m_aCaptureKeyboardControls.erase(pos);
				else
					pos++;
			IControl *new_control{ (m_pForm->m_aCaptureKeyboardControls.size() > 0) ? m_pForm->m_aCaptureKeyboardControls[m_pForm->m_aCaptureKeyboardControls.size() - 1] : nullptr };
			if (old_control != new_control)
			{
				CNotifier::ControlKillCaptureKeyboard(m_pForm, old_control);
				if (new_control)
					CNotifier::ControlSetCaptureKeyboard(m_pForm, new_control);
			}
		}
		// Capture mouse
		if (m_pForm->m_aCaptureMouseControls.size() > 0)
		{
			CForm::CAPTURE_MOUSE old_control{ m_pForm->m_aCaptureMouseControls[m_pForm->m_aCaptureMouseControls.size() - 1] };
			auto pos{ m_pForm->m_aCaptureMouseControls.begin() };
			while (pos != m_pForm->m_aCaptureMouseControls.end())
				if (pos->Control == control || control->hasChild(pos->Control))
					pos = m_pForm->m_aCaptureMouseControls.erase(pos);
				else
					pos++;
			CForm::CAPTURE_MOUSE *new_control{ (m_pForm->m_aCaptureMouseControls.size() > 0) ? &m_pForm->m_aCaptureMouseControls[m_pForm->m_aCaptureMouseControls.size() - 1] : nullptr };
			if (!new_control || new_control->Control != old_control.Control)
			{
				if (m_pForm->m_pWindow && old_control.System)
					m_pForm->m_pWindow->ReleaseMouseCapture();
				CNotifier::ControlKillCaptureMouse(m_pForm, old_control.Control);
				if (new_control)
				{
					if (m_pForm->m_pWindow && new_control->System)
						new_control->System = m_pForm->m_pWindow->CaptureMouse();
					CNotifier::ControlSetCaptureMouse(m_pForm, new_control->Control);
				}
			}
		}
		// Focused
		if (m_pForm->m_pFocusedControl && (m_pForm->m_pFocusedControl == control || control->hasChild(m_pForm->m_pFocusedControl)))
		{
			CNotifier::ControlKillFocus(m_pForm, m_pForm->m_pFocusedControl);
			m_pForm->m_pFocusedControl = m_pForm->m_pFocusedControlOld = nullptr;
		}
		// Active
		if (m_pForm->m_pActiveControl && (m_pForm->m_pActiveControl == control || control->hasChild(m_pForm->m_pActiveControl)))
		{
			CNotifier::ControlDeactivate(m_pForm, m_pForm->m_pActiveControl);
			m_pForm->m_pActiveControl = nullptr;
		}
	}

	void CFormService::ProcessControlHide(IControl *control)
	{
		ProcessControlDisable(control);
		// Hovered
		if (m_pForm->m_pHoveredControl && (m_pForm->m_pHoveredControl == control || control->hasChild(m_pForm->m_pHoveredControl)))
		{
			CNotifier::MouseLeaveControl(m_pForm, m_pForm->m_pHoveredControl);
			m_pForm->m_pHoveredControl = nullptr;
		}
		// Modal
		if (m_pForm->m_aModalControls.size() > 0)
		{
			IControl *old_control{ m_pForm->m_aModalControls[m_pForm->m_aModalControls.size() - 1] };
			auto pos{ m_pForm->m_aModalControls.begin() };
			while (pos != m_pForm->m_aModalControls.end())
				if (*pos == control || control->hasChild(*pos))
					pos = m_pForm->m_aModalControls.erase(pos);
				else
					pos++;
			IControl *new_control{ (m_pForm->m_aModalControls.size() > 0) ? m_pForm->m_aModalControls[m_pForm->m_aModalControls.size() - 1] : nullptr };
			if (old_control != new_control)
			{
				CNotifier::ControlKillModal(m_pForm, old_control);
				if (new_control)
					CNotifier::ControlSetModal(m_pForm, new_control);
			}
		}
		// Dialog box
		if (m_pForm->m_aActiveDialogBoxes.size() > 0)
		{
			IDialogBox *old_control{ m_pForm->m_aActiveDialogBoxes[m_pForm->m_aActiveDialogBoxes.size() - 1] };
			auto pos{ m_pForm->m_aActiveDialogBoxes.begin() };
			while (pos != m_pForm->m_aActiveDialogBoxes.end())
				if (*pos == control || control->hasChild(*pos))
					pos = m_pForm->m_aActiveDialogBoxes.erase(pos);
				else
					pos++;
			IDialogBox *new_control{ (m_pForm->m_aActiveDialogBoxes.size() > 0) ? m_pForm->m_aActiveDialogBoxes[m_pForm->m_aActiveDialogBoxes.size() - 1] : nullptr };
			if (old_control != new_control)
			{
				CNotifier::ControlDeactivateDialogBox(m_pForm, old_control);
				if (new_control)
					CNotifier::ControlActivateDialogBox(m_pForm, new_control);
			}
		}
	}

	void CFormService::ProcessControlDetach(IControl *control)
	{
		// Hint
		if (m_pForm->m_hTimerHintDelay)
		{
			m_pForm->m_pWindow->DeleteTimer(m_pForm->m_hTimerHintDelay);
			m_pForm->m_hTimerHintDelay = nullptr;
		}
		if (m_pForm->m_pHint)
			m_pForm->m_pHint->Hide(true);
		ProcessControlHide(control);
		// HotKeys
		if (m_pForm->m_aHotkeys.size() > 0)
		{
			auto pos{ m_pForm->m_aHotkeys.begin() };
			while (pos != m_pForm->m_aHotkeys.end())
				if (pos->Control == control || control->hasChild(pos->Control))
					pos = m_pForm->m_aHotkeys.erase(pos);
				else
					pos++;
		}
		// Message listeners
		if (m_pForm->m_aMessageListeners.size() > 0)
		{
			IControl *ctrl;
			auto pos{ m_pForm->m_aMessageListeners.begin() };
			while (pos != m_pForm->m_aMessageListeners.end())
				if (pos->Component == control || ((ctrl = cast<IControl*>(pos->Component)) && control->hasChild(ctrl)))
					pos = m_pForm->m_aMessageListeners.erase(pos);
				else
					pos++;
		}
		// Input control
		if (m_pForm->m_pInputControl && (control == m_pForm->m_pInputControl || control->hasChild(m_pForm->m_pInputControl)))
			m_pForm->m_pInputControl = nullptr;
	}
#pragma endregion

#pragma region Notifications from child controls
	void CFormService::NotifyOnChildStyleChange(IControl *control)
	{

	}

	void CFormService::NotifyOnChildFontChange(IControl *control)
	{

	}

	void CFormService::NotifyOnChildTransform(IControl *control)
	{

	}

	void CFormService::NotifyOnChildResize(IControl *control)
	{

	}

	void CFormService::NotifyOnChildShow(IControl *control)
	{

	}

	void CFormService::NotifyOnChildHide(IControl *control)
	{

	}

	void CFormService::NotifyOnChildEnable(IControl *control)
	{

	}

	void CFormService::NotifyOnChildDisable(IControl *control)
	{

	}

	void CFormService::NotifyOnChildBeforeTransform(IControl *control, bool &allowed)
	{

	}

	void CFormService::NotifyOnChildBeforeResize(IControl *control, bool &allowed)
	{

	}

	void CFormService::NotifyOnChildBeforeShow(IControl *control, bool &allowed)
	{

	}

	void CFormService::NotifyOnChildBeforeHide(IControl *control, bool &allowed)
	{

	}

	void CFormService::NotifyOnChildBeforeEnable(IControl *control, bool &allowed)
	{

	}

	void CFormService::NotifyOnChildBeforeDisable(IControl *control, bool &allowed)
	{

	}
#pragma endregion

#pragma region State change notifications
	void CFormService::NotifyOnResize()
	{

	}

	void CFormService::NotifyOnTransform()
	{

	}

	void CFormService::NotifyOnTransformControls()
	{

	}

	void CFormService::NotifyOnStyleChange()
	{

	}

	void CFormService::NotifyOnFontChange()
	{

	}

	void CFormService::NotifyOnFreeResources()
	{
		if (m_pForm->m_hTimerHintDelay)
		{
			m_pForm->m_pWindow->DeleteTimer(m_pForm->m_hTimerHintDelay);
			m_pForm->m_hTimerHintDelay = nullptr;
		}
		if (m_pForm->m_pCaret)
			m_pForm->m_pCaret->setRenderer(nullptr);
		if (m_pForm->m_pHint)
			m_pForm->m_pHint->QueryService()->setForm(nullptr);
		if (m_pForm->m_pFont)
			m_pForm->m_pFont->NotifyOnFreeResources();
	}
#pragma endregion

#pragma region Component notifications
	void CFormService::NotifyOnComponentAttach(IComponent *component)
	{

	}

	void CFormService::NotifyOnComponentDetach(IComponent *component)
	{

	}
#pragma endregion

#pragma region Control notifications
	void CFormService::NotifyOnControlAttach(IControl *control)
	{

	}

	void CFormService::NotifyOnControlDetach(IControl *control)
	{

	}

	void CFormService::NotifyOnControlSetModal(IControl *control)
	{

	}

	void CFormService::NotifyOnControlKillModal(IControl *control)
	{

	}

	void CFormService::NotifyOnControlSetFocus(IControl *control, const MessageFocus &m)
	{

	}

	void CFormService::NotifyOnControlKillFocus(IControl *control)
	{

	}

	void CFormService::NotifyOnControlMouseHover(IControl *control, const MessagePosition &m)
	{

	}

	void CFormService::NotifyOnControlMouseLeave(IControl *control)
	{

	}

	void CFormService::NotifyOnControlSetCaptureKeyboard(IControl *control)
	{

	}

	void CFormService::NotifyOnControlKillCaptureKeyboard(IControl *control)
	{

	}

	void CFormService::NotifyOnControlSetCaptureMouse(IControl *control)
	{

	}

	void CFormService::NotifyOnControlKillCaptureMouse(IControl *control)
	{

	}

	void CFormService::NotifyOnControlActivate(IControl *control)
	{

	}

	void CFormService::NotifyOnControlDeactivate(IControl *control)
	{

	}
#pragma endregion

#pragma region Paint notifications
	void CFormService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
	{
		if (!m.LastPass && m_pForm->m_sBackgroundColor.A > 0)
			m_pForm->m_pRenderer->Clear(m_pForm->m_sBackgroundColor);
	}

	void CFormService::NotifyOnPaintEnd(const MessagePaint &m)
	{
		
	}
#pragma endregion

#pragma region Keyboard input notifications
	void CFormService::NotifyOnKeyDown(const MessageKey &m)
	{

	}

	void CFormService::NotifyOnKeyUp(const MessageKey &m)
	{

	}

	void CFormService::NotifyOnChar(const MessageChar &m)
	{

	}

	void CFormService::NotifyOnDeadChar(const MessageChar &m)
	{

	}
#pragma endregion

#pragma region Mouse input notifications
	void CFormService::NotifyOnMouseHover(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnMouseLeave()
	{

	}

	void CFormService::NotifyOnMouseMove(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnLeftMouseButtonDown(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnLeftMouseButtonUp(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnRightMouseButtonDown(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnRightMouseButtonUp(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m)
	{

	}

	void CFormService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m)
	{

	}

	void CFormService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m)
	{

	}
#pragma endregion

#pragma region Other input notifications
	void CFormService::NotifyOnDropFiles(const MessageDropFiles &m, bool &accepted)
	{

	}

	void CFormService::NotifyOnHotkey(const MessageHotkey &m)
	{

	}

	void CFormService::NotifyOnGestureZoom(const MessagePosition &m)
	{

	}

	void CFormService::NotifyOnGesturePan(const MessagePosition &m)
	{

	}

	void CFormService::NotifyOnGestureRotate(const MessagePosition &m)
	{

	}

	void CFormService::NotifyOnGestureTwoFingerTap(const MessagePosition &m)
	{

	}

	void CFormService::NotifyOnGesturePressAndTap(const MessagePosition &m)
	{

	}

	void CFormService::NotifyOnGestureNotify()
	{

	}

	void CFormService::NotifyOnTouch(const MessageTouch &m)
	{

	}
#pragma endregion

#pragma region Application notifications
	void CFormService::NotifyOnApplicationActivate()
	{

	}

	void CFormService::NotifyOnApplicationDeactivate()
	{

	}

	void CFormService::NotifyOnQueryEndSession(bool &restricted)
	{

	}

	void CFormService::NotifyOnQueryOpen(bool &restricted)
	{

	}

	void CFormService::NotifyOnEndSession(const MessageEndSession &m)
	{

	}

	void CFormService::NotifyOnDeviceModeChange()
	{

	}

	void CFormService::NotifyOnTimeChange()
	{

	}

	void CFormService::NotifyOnInputLanguageChangeRequest(bool &restricted)
	{

	}

	void CFormService::NotifyOnInputLanguageChange()
	{

	}

	void CFormService::NotifyOnDisplayChange(const MessageSize &m)
	{

	}

	void CFormService::NotifyOnThemeChange()
	{

	}

	void CFormService::NotifyOnClipboardUpdate()
	{

	}

	void CFormService::NotifyOnTranslateChange()
	{

	}
#pragma endregion

#pragma region Window notifications
	void CFormService::NotifyOnCreate()
	{

	}

	void CFormService::NotifyOnDestroy()
	{

	}

	void CFormService::NotifyOnActivate(const MessageWindowActivate &m)
	{

	}

	void CFormService::NotifyOnDeactivate()
	{

	}

	void CFormService::NotifyOnSetFocus()
	{

	}

	void CFormService::NotifyOnKillFocus()
	{

	}

	void CFormService::NotifyOnEnable()
	{

	}

	void CFormService::NotifyOnDisable()
	{

	}

	void CFormService::NotifyOnClose(CloseAction &action)
	{

	}

	void CFormService::NotifyOnShow()
	{

	}

	void CFormService::NotifyOnHide()
	{

	}

	void CFormService::NotifyOnMove(const MessagePosition &m)
	{

	}

	void CFormService::NotifyOnRestore(const MessageSize &m)
	{

	}

	void CFormService::NotifyOnMinimize(const MessageSize &m)
	{

	}

	void CFormService::NotifyOnMaximize(const MessageSize &m)
	{

	}

	void CFormService::NotifyOnResizing(const MessageWindowResizing &m)
	{

	}

	void CFormService::NotifyOnMoving(const MessageRect &m)
	{

	}

	void CFormService::NotifyOnEnterSizeMove()
	{

	}

	void CFormService::NotifyOnExitSizeMove()
	{

	}

	void CFormService::NotifyOnHScroll(const MessageWindowScroll &m)
	{

	}

	void CFormService::NotifyOnVScroll(const MessageWindowScroll &m)
	{

	}

	void CFormService::NotifyOnLoseCapture()
	{

	}
#pragma endregion

#pragma region Dialog box notifications
	void CFormService::NotifyOnDialogBoxActivate(IDialogBox *control)
	{

	}

	void CFormService::NotifyOnDialogBoxDeactivate(IDialogBox *control)
	{

	}
#pragma endregion

#pragma region Clipboard notifications
	void CFormService::NotifyOnPasteString(const MessagePasteString &m)
	{

	}
#pragma endregion
}