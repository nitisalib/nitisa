// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CControlService::CControlService(CControl *control) :
		CComponentService{ control },
		m_pControl{ control }
	{

	}
#pragma endregion

#pragma region Getters
	PointF CControlService::getSizeRequested()
	{
		return m_pControl->m_sSizeRequested;
	}
#pragma endregion

#pragma region Setters
	void CControlService::setParent(IControl *value)
	{
		m_pControl->m_pParent = value;
	}

	void CControlService::setTabOrder(const int value)
	{
		m_pControl->m_iTabOrder = value;
	}

	void CControlService::setSize(const PointF &value)
	{
		m_pControl->m_sSize = value;
	}
#pragma endregion

#pragma region Helpers
	void CControlService::AdjustSize()
	{
		m_pControl->AdjustSize();
	}

	bool CControlService::MoveControl(IControl *control, const int before)
	{
		if (nitisa::MoveControl(m_pControl->m_aControls, m_pControl, control, before))
		{
			AlignControls();
			return true;
		}
		return false;
	}

	void CControlService::SendChangeNotification()
	{
		if (m_pControl->getForm())
		{
			for (int i = 0; i < m_pControl->getForm()->getComponentCount(); i++)
			{
				m_pControl->getForm()->getComponent(i)->QueryService()->NotifyOnControlChange(m_pControl);
				if (m_pControl->getForm()->getComponent(i)->OnControlChange)
					m_pControl->getForm()->getComponent(i)->OnControlChange(m_pControl->getForm()->getComponent(i), m_pControl);
			}
			for (int i = 0; i < m_pControl->getForm()->getControlCount(); i++)
				SendChangeNotification(m_pControl->getForm()->getControl(i));
		}
	}

	void CControlService::SendChangeNotification(IControl *control)
	{
		if (control != m_pControl)
		{
			control->QueryService()->NotifyOnControlChange(m_pControl);
			if (control->OnControlChange)
				control->OnControlChange(control, m_pControl);
		}
		for (int i = 0; i < control->getControlCount(); i++)
			SendChangeNotification(control->getControl(i));
	}

	void CControlService::AlignControls()
	{
		CLockRepaint lock{ m_pControl };
		RectF client{ m_pControl->getClientRect() };
		for (auto control : m_pControl->m_aControls)
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
				size = PointF{ size.X, ntl::Max<float>(client.height(), 0) };
				new_pos = PointF{ client.Left, client.Top };
				client.Left += size.X;
				break;
			case Align::Top:
				size = PointF{ ntl::Max<float>(client.width(), 0), size.Y };
				new_pos = PointF{ client.Left, client.Top };
				client.Top += size.Y;
				break;
			case Align::Right:
				size = PointF{ size.X, ntl::Max<float>(client.height(), 0) };
				new_pos = PointF{ client.Right - size.X, client.Top };
				client.Right -= size.X;
				break;
			case Align::Bottom:
				size = PointF{ ntl::Max<float>(client.width(), 0), size.Y };
				new_pos = PointF{ client.Left, client.Bottom - size.Y };
				client.Bottom -= size.Y;
				break;
			default: //alClient
				size = PointF{ ntl::Max<float>(client.width(), 0), ntl::Max<float>(client.height(), 0) };
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

	void CControlService::InsertControl(IControl *control, const int before)
	{
		if (before <= (int)m_pControl->m_aControls.size() - 1)
			m_pControl->m_aControls.insert(m_pControl->m_aControls.begin() + before, control);
		else
			m_pControl->m_aControls.push_back(control);
	}
#pragma endregion

#pragma region State change notifications
	void CControlService::NotifyOnFreeResources()
	{
		
	}
#pragma endregion

#pragma region Notifications from parent control
	void CControlService::NotifyOnParentStyleChange()
	{

	}

	void CControlService::NotifyOnParentFontChange()
	{

	}

	void CControlService::NotifyOnParentResize()
	{

	}

	void CControlService::NotifyOnParentTransform()
	{

	}

	void CControlService::NotifyOnParentTransformControls()
	{

	}
#pragma endregion

#pragma region Notifications from child controls
	void CControlService::NotifyOnChildStyleChange(IControl *control)
	{

	}

	void CControlService::NotifyOnChildFontChange(IControl *control)
	{

	}

	void CControlService::NotifyOnChildTransform(IControl *control)
	{

	}

	void CControlService::NotifyOnChildResize(IControl *control)
	{

	}

	void CControlService::NotifyOnChildShow(IControl *control)
	{

	}

	void CControlService::NotifyOnChildHide(IControl *control)
	{

	}

	void CControlService::NotifyOnChildAttach(IControl *control)
	{

	}

	void CControlService::NotifyOnChildDetach(IControl *control)
	{

	}

	void CControlService::NotifyOnChildEnable(IControl *control)
	{

	}

	void CControlService::NotifyOnChildDisable(IControl *control)
	{

	}

	void CControlService::NotifyOnChildBeforeTransform(IControl *control, bool &allowed)
	{

	}

	void CControlService::NotifyOnChildBeforeResize(IControl *control, bool &allowed)
	{

	}

	void CControlService::NotifyOnChildBeforeShow(IControl *control, bool &allowed)
	{

	}

	void CControlService::NotifyOnChildBeforeHide(IControl *control, bool &allowed)
	{

	}

	void CControlService::NotifyOnChildBeforeEnable(IControl *control, bool &allowed)
	{

	}

	void CControlService::NotifyOnChildBeforeDisable(IControl *control, bool &allowed)
	{

	}
#pragma endregion

#pragma region State change notifications
	void CControlService::NotifyOnShow()
	{

	}

	void CControlService::NotifyOnHide()
	{

	}

	void CControlService::NotifyOnEnable()
	{

	}

	void CControlService::NotifyOnDisable()
	{

	}

	void CControlService::NotifyOnResize()
	{

	}

	void CControlService::NotifyOnTransform()
	{

	}

	void CControlService::NotifyOnTransformControls()
	{

	}

	void CControlService::NotifyOnStyleChange()
	{

	}

	void CControlService::NotifyOnFontChange()
	{

	}

	void CControlService::NotifyOnSetModal()
	{

	}

	void CControlService::NotifyOnKillModal()
	{

	}

	void CControlService::NotifyOnSetFocus(const MessageFocus &m)
	{

	}

	void CControlService::NotifyOnKillFocus()
	{

	}

	void CControlService::NotifyOnSetCaptureKeyboard()
	{

	}

	void CControlService::NotifyOnKillCaptureKeyboard()
	{

	}

	void CControlService::NotifyOnSetCaptureMouse()
	{

	}

	void CControlService::NotifyOnKillCaptureMouse()
	{

	}

	void CControlService::NotifyOnActivate()
	{

	}

	void CControlService::NotifyOnDeactivate()
	{

	}
#pragma endregion

#pragma region Paint notifications
	void CControlService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
	{

	}

	void CControlService::NotifyOnPaintEnd(const MessagePaint &m)
	{

	}
#pragma endregion

#pragma region Keyboard input notifications
	void CControlService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
	{

	}

	void CControlService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
	{

	}

	void CControlService::NotifyOnChar(const MessageChar &m, bool &processed)
	{

	}

	void CControlService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
	{

	}
#pragma endregion

#pragma region Mouse input notifications
	void CControlService::NotifyOnMouseHover(const MessagePosition &m)
	{

	}

	void CControlService::NotifyOnMouseLeave()
	{

	}

	void CControlService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
	{

	}

	void CControlService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
	{

	}

	void CControlService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
	{

	}

	void CControlService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
	{

	}

	void CControlService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
	{

	}

	void CControlService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
	{

	}

	void CControlService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
	{

	}

	void CControlService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
	{

	}

	void CControlService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
	{

	}

	void CControlService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
	{

	}

	void CControlService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
	{

	}

	void CControlService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
	{

	}
#pragma endregion

#pragma region Other input notifications
	void CControlService::NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted)
	{

	}
#pragma endregion

#pragma region Clipboard notifications
	void CControlService::NotifyOnPasteString(const MessagePasteString &m)
	{

	}
#pragma endregion

#pragma region Interceprors
	bool CControlService::InterceptSetCursor(IControl *control)
	{
		return false;
	}

	bool CControlService::InterceptMouseHover(IControl *control)
	{
		return false;
	}

	bool CControlService::InterceptShowHint(IControl *control, String &hint)
	{
		return false;
	}

	bool CControlService::InterceptTabOrder()
	{
		return false;
	}

	bool CControlService::InterceptHotkeys(IControl *control, const MessageHotkey &m)
	{
		return false;
	}

	bool CControlService::InterceptKeyDown(IControl *control, const MessageKey &m)
	{
		return false;
	}

	bool CControlService::InterceptKeyUp(IControl *control, const MessageKey &m)
	{
		return false;
	}

	bool CControlService::InterceptChar(IControl *control, const MessageChar &m)
	{
		return false;
	}

	bool CControlService::InterceptDeadChar(IControl *control, const MessageChar &m)
	{
		return false;
	}

	bool CControlService::InterceptMouseMove(IControl *control, const MessageMouse &m)
	{
		return false;
	}

	bool CControlService::InterceptLeftMouseButtonDown(IControl *control, const MessageMouse &m)
	{
		return false;
	}

	bool CControlService::InterceptLeftMouseButtonUp(IControl *control, const MessageMouse &m)
	{
		return false;
	}

	bool CControlService::InterceptLeftMouseButtonDoubleClick(IControl *control, const MessageMouse &m)
	{
		return false;
	}

	bool CControlService::InterceptMiddleMouseButtonDown(IControl *control, const MessageMouse &m)
	{
		return false;
	}

	bool CControlService::InterceptMiddleMouseButtonUp(IControl *control, const MessageMouse &m)
	{
		return false;
	}

	bool CControlService::InterceptMiddleMouseButtonDoubleClick(IControl *control, const MessageMouse &m)
	{
		return false;
	}

	bool CControlService::InterceptRightMouseButtonDown(IControl *control, const MessageMouse &m)
	{
		return false;
	}

	bool CControlService::InterceptRightMouseButtonUp(IControl *control, const MessageMouse &m)
	{
		return false;
	}

	bool CControlService::InterceptRightMouseButtonDoubleClick(IControl *control, const MessageMouse &m)
	{
		return false;
	}

	bool CControlService::InterceptMouseVerticalWheel(IControl *control, const MessageMouseWheel &m)
	{
		return false;
	}

	bool CControlService::InterceptMouseHorizontalWheel(IControl *control, const MessageMouseWheel &m)
	{
		return false;
	}

	bool CControlService::InterceptDropFiles(IControl *control, const MessageDropFiles &m)
	{
		return false;
	}

	bool CControlService::InterceptFocus(IControl *control, const FocusedBy focused_by)
	{
		return false;
	}
#pragma endregion
}