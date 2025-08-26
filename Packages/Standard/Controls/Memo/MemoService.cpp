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
	namespace standard
	{
	#pragma region Constructor & destructor
		CMemoService::CMemoService(CMemo *memo) :
			CControlService(memo),
			m_pMemo{ memo }
		{

		}
	#pragma endregion

	#pragma region Helpers
		CMemoService::Element CMemoService::ElementAtPos(const PointF &pos)
		{
			RectF r{
				m_pMemo->m_sTextAreaPosition.X,
				m_pMemo->m_sTextAreaPosition.Y,
				m_pMemo->m_sTextAreaPosition.X + m_pMemo->getTextArea()->getSize().X,
				m_pMemo->m_sTextAreaPosition.Y + m_pMemo->getTextArea()->getSize().Y };
			if (pos.X >= r.Left && pos.X < r.Right && pos.Y >= r.Top && pos.Y < r.Bottom)
				return Element::Text;
			if (m_pMemo->m_bVScrollVisible)
			{
				r = RectF{
					m_pMemo->m_sVScrollPosition.X,
					m_pMemo->m_sVScrollPosition.Y,
					m_pMemo->m_sVScrollPosition.X + m_pMemo->getVScroll()->getSize().X,
					m_pMemo->m_sVScrollPosition.Y + m_pMemo->getVScroll()->getSize().Y };
				if (pos.X >= r.Left && pos.X < r.Right && pos.Y >= r.Top && pos.Y < r.Bottom)
					return Element::VScroll;
			}
			if (m_pMemo->m_bHScrollVisible)
			{
				r = RectF{
					m_pMemo->m_sHScrollPosition.X,
					m_pMemo->m_sHScrollPosition.Y,
					m_pMemo->m_sHScrollPosition.X + m_pMemo->getHScroll()->getSize().X,
					m_pMemo->m_sHScrollPosition.Y + m_pMemo->getHScroll()->getSize().Y };
				if (pos.X >= r.Left && pos.X < r.Right && pos.Y >= r.Top && pos.Y < r.Bottom)
					return Element::HScroll;
			}
			return Element::None;
		}

		void CMemoService::MouseUp(const PointF &pos)
		{
			switch (m_pMemo->m_eMouseDownElement)
			{
			case Element::Text:
			{
				bool ctrl, alt, shift;
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (m_pMemo->getTextArea()->NotifyOnMouseLeftUp(LocalToTextArea(m_pMemo->FormToLocal(pos)), false, false, ctrl, alt, shift))
				{
					m_pMemo->getTextArea()->ScrollToCaret();
					m_pMemo->UpdateScrollPositions();
					if (m_pMemo->m_pCanvas)
						m_pMemo->m_pCanvas->setValid(false);
					m_pMemo->Repaint(false);
				}
			}
			break;
			case Element::VScroll:
				if (m_pMemo->getVScroll()->NotifyOnMouseLeftUp(LocalToVScroll(m_pMemo->FormToLocal(pos)), false, false, false, false, false))
				{
					if (m_pMemo->m_pCanvas)
						m_pMemo->m_pCanvas->setValid(false);
					m_pMemo->Repaint(false);
				}
				break;
			case Element::HScroll:
				if (m_pMemo->getHScroll()->NotifyOnMouseLeftUp(LocalToHScroll(m_pMemo->FormToLocal(pos)), false, false, false, false, false))
				{
					if (m_pMemo->m_pCanvas)
						m_pMemo->m_pCanvas->setValid(false);
					m_pMemo->Repaint(false);
				}
				break;
			default:
				break;
			}
			m_pMemo->m_eMouseDownElement = Element::None;
			if (m_pMemo->isCaptureMouse())
				m_pMemo->getForm()->ReleaseCaptureMouse();
		}

		PointF CMemoService::LocalToTextArea(const PointF &pos)
		{
			return PointF{ pos.X - m_pMemo->m_sTextAreaPosition.X, pos.Y - m_pMemo->m_sTextAreaPosition.Y };
		}

		PointF CMemoService::LocalToVScroll(const PointF &pos)
		{
			return PointF{ pos.X - m_pMemo->m_sVScrollPosition.X, pos.Y - m_pMemo->m_sVScrollPosition.Y };
		}

		PointF CMemoService::LocalToHScroll(const PointF &pos)
		{
			return PointF{ pos.X - m_pMemo->m_sHScrollPosition.X, pos.Y - m_pMemo->m_sHScrollPosition.Y };
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CMemoService::NotifyOnParentStyleChange()
		{
			if (m_pMemo->getStyle())
			{
				m_pMemo->UpdateFromStyle();
				if (m_pMemo->m_pCanvas)
					m_pMemo->m_pCanvas->setValid(false);
			}
		}

		void CMemoService::NotifyOnParentFontChange()
		{
			m_pMemo->getTextArea()->Update();
			m_pMemo->AdjustElements();
			m_pMemo->getTextArea()->ScrollToCaret();
			m_pMemo->UpdateScrollPositions();
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CMemoService::NotifyOnEnable()
		{
			m_pMemo->getTextArea()->setEnabled(true);
			m_pMemo->getVScroll()->setEnabled(true);
			m_pMemo->getHScroll()->setEnabled(true);
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
		}

		void CMemoService::NotifyOnDisable()
		{
			m_pMemo->getTextArea()->setEnabled(false);
			m_pMemo->getVScroll()->setEnabled(false);
			m_pMemo->getHScroll()->setEnabled(false);
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
		}

		void CMemoService::NotifyOnAttach()
		{
			if (m_pMemo->getForm())
			{
				if (!m_pMemo->m_bTextChanged)
					m_pMemo->setText(m_pMemo->m_sName);
				m_pMemo->getTextArea()->NotifyOnAttach();
				m_pMemo->getVScroll()->NotifyOnAttach();
				m_pMemo->getHScroll()->NotifyOnAttach();
				m_pMemo->AdjustElements();
				m_pMemo->getTextArea()->ScrollToCaret();
				m_pMemo->UpdateScrollPositions();
			}
		}

		void CMemoService::NotifyOnDetaching()
		{
			MouseUp(PointF{ 0, 0 });
		}

		void CMemoService::NotifyOnFreeResources()
		{
			if (m_pMemo->m_pTextArea)
				m_pMemo->m_pTextArea->NotifyOnFreeResources();
			if (m_pMemo->m_pVScroll)
				m_pMemo->m_pVScroll->NotifyOnFreeResources();
			if (m_pMemo->m_pHScroll)
				m_pMemo->m_pHScroll->NotifyOnFreeResources();
			if (m_pMemo->m_pCanvas)
			{
				m_pMemo->m_pCanvas->Release();
				m_pMemo->m_pCanvas = nullptr;
			}
		}

		void CMemoService::NotifyOnResize()
		{
			m_pMemo->AdjustElements();
			m_pMemo->getTextArea()->ScrollToCaret();
			m_pMemo->UpdateScrollPositions();
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
		}

		void CMemoService::NotifyOnStyleChange()
		{
			if (m_pMemo->getStyle())
			{
				m_pMemo->UpdateFromStyle();
				if (m_pMemo->m_pCanvas)
					m_pMemo->m_pCanvas->setValid(false);
			}
		}

		void CMemoService::NotifyOnFontChange()
		{
			m_pMemo->getTextArea()->Update();
			m_pMemo->AdjustElements();
			m_pMemo->getTextArea()->ScrollToCaret();
			m_pMemo->UpdateScrollPositions();
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
		}

		void CMemoService::NotifyOnSetFocus(const MessageFocus &m)
		{
			m_pMemo->getTextArea()->setFocused(true);
			if ((m.FocusedBy == FocusedBy::Tab || m.FocusedBy == FocusedBy::ShiftTab) && !m_pMemo->getTextArea()->hasSelection())
				m_pMemo->getTextArea()->SelectAll();
			m_pMemo->getForm()->getCaret()->setListener(this);
			m_pMemo->getForm()->getCaret()->setVisible(true);
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
			m_pMemo->Repaint(false);
		}

		void CMemoService::NotifyOnKillFocus()
		{
			m_pMemo->getTextArea()->setFocused(false);
			m_pMemo->getForm()->getCaret()->setListener(nullptr);
			m_pMemo->getForm()->getCaret()->setVisible(false);
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
			m_pMemo->Repaint(false);
		}

		void CMemoService::NotifyOnMouseHover(const MessagePosition &m)
		{
			PointF pos{ m_pMemo->FormToLocal(m.Position) };
			Element el{ ElementAtPos(pos) };
			if (m_pMemo->m_eHoveredElement != el)
			{
				switch (m_pMemo->m_eHoveredElement)
				{
				case Element::Text:
					m_pMemo->getTextArea()->NotifyOnMouseLeave();
					break;
				case Element::VScroll:
					m_pMemo->getVScroll()->NotifyOnMouseLeave();
					break;
				case Element::HScroll:
					m_pMemo->getHScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_pMemo->m_eHoveredElement = Element::None;
			}
			switch (el)
			{
			case Element::Text:
				if (m_pMemo->m_eHoveredElement != Element::Text)
					m_pMemo->getTextArea()->NotifyOnMouseHover(LocalToTextArea(pos));
				break;
			case Element::VScroll:
				if (m_pMemo->m_eHoveredElement != Element::VScroll)
					m_pMemo->getVScroll()->NotifyOnMouseHover(LocalToVScroll(pos));
				break;
			case Element::HScroll:
				if (m_pMemo->m_eHoveredElement != Element::HScroll)
					m_pMemo->getHScroll()->NotifyOnMouseHover(LocalToHScroll(pos));
				break;
			default:
				break;
			}
			m_pMemo->m_eHoveredElement = el;
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
			m_pMemo->Repaint(false);
		}

		void CMemoService::NotifyOnMouseLeave()
		{
			if (m_pMemo->m_eHoveredElement != Element::None)
			{
				switch (m_pMemo->m_eHoveredElement)
				{
				case Element::Text:
					m_pMemo->getTextArea()->NotifyOnMouseLeave();
					break;
				case Element::VScroll:
					m_pMemo->getVScroll()->NotifyOnMouseLeave();
					break;
				case Element::HScroll:
					m_pMemo->getHScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_pMemo->m_eHoveredElement = Element::None;
			}
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
			m_pMemo->Repaint(false);
		}

		void CMemoService::NotifyOnKillCaptureMouse()
		{
			if (m_pMemo->m_pTextArea)
				m_pMemo->m_pTextArea->NotifyOnMouseDownCancel();
			if (m_pMemo->m_pVScroll)
				m_pMemo->m_pVScroll->NotifyOnMouseDownCancel();
			if (m_pMemo->m_pHScroll)
				m_pMemo->m_pHScroll->NotifyOnMouseDownCancel();
		}
	#pragma endregion

	#pragma region Paint notifications
		void CMemoService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pMemo->getWidth(), 0) && ntl::IsGreater<float>(m_pMemo->getHeight(), 0))
				m_pMemo->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CMemoService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pMemo->getTextArea()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				m_pMemo->getTextArea()->ScrollToCaret();
				m_pMemo->UpdateScrollPositions();
				if (m_pMemo->m_pCanvas)
					m_pMemo->m_pCanvas->setValid(false);
				m_pMemo->Repaint(false);
			}
		}

		void CMemoService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pMemo->getTextArea()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				m_pMemo->getTextArea()->ScrollToCaret();
				m_pMemo->UpdateScrollPositions();
				if (m_pMemo->m_pCanvas)
					m_pMemo->m_pCanvas->setValid(false);
				m_pMemo->Repaint(false);
			}
		}

		void CMemoService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pMemo->getTextArea()->NotifyOnChar(m.Char, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				m_pMemo->getTextArea()->ScrollToCaret();
				m_pMemo->UpdateScrollPositions();
				if (m_pMemo->m_pCanvas)
					m_pMemo->m_pCanvas->setValid(false);
				m_pMemo->Repaint(false);
			}
		}

		void CMemoService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pMemo->getTextArea()->NotifyOnDeadChar(m.Char, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				m_pMemo->getTextArea()->ScrollToCaret();
				m_pMemo->UpdateScrollPositions();
				if (m_pMemo->m_pCanvas)
					m_pMemo->m_pCanvas->setValid(false);
				m_pMemo->Repaint(false);
			}
		}

		void CMemoService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			PointF pos{ m_pMemo->FormToLocal(m.Position) };
			Element el{ ElementAtPos(pos) };
			bool repaint_required{ false };
			if (m_pMemo->m_eHoveredElement != el)
			{
				switch (m_pMemo->m_eHoveredElement)
				{
				case Element::Text:
					if (m_pMemo->getTextArea()->NotifyOnMouseLeave())
						repaint_required = true;
					break;
				case Element::VScroll:
					if (m_pMemo->getVScroll()->NotifyOnMouseLeave())
						repaint_required = true;
					break;
				case Element::HScroll:
					if (m_pMemo->getHScroll()->NotifyOnMouseLeave())
						repaint_required = true;
					break;
				default:
					break;
				}
				m_pMemo->m_eHoveredElement = Element::None;
			}
			if (el != m_pMemo->m_eHoveredElement)
			{
				switch (el)
				{
				case Element::Text:
					if (m_pMemo->m_eHoveredElement != Element::Text && m_pMemo->getTextArea()->NotifyOnMouseHover(LocalToTextArea(pos)))
						repaint_required = true;
					break;
				case Element::VScroll:
					if (m_pMemo->m_eHoveredElement != Element::VScroll && m_pMemo->getVScroll()->NotifyOnMouseHover(LocalToVScroll(pos)))
						repaint_required = true;
					break;
				case Element::HScroll:
					if (m_pMemo->m_eHoveredElement != Element::HScroll && m_pMemo->getHScroll()->NotifyOnMouseHover(LocalToHScroll(pos)))
						repaint_required = true;
					break;
				default:
					break;
				}
				m_pMemo->m_eHoveredElement = el;
			}
			switch (m_pMemo->m_eMouseDownElement)
			{
			case Element::Text:
				if (m_pMemo->getTextArea()->NotifyOnMouseMove(LocalToTextArea(pos), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					m_pMemo->getTextArea()->ScrollToCaret();
					m_pMemo->UpdateScrollPositions();
					repaint_required = true;
				}
				break;
			case Element::VScroll:
				if (m_pMemo->getVScroll()->NotifyOnMouseMove(LocalToVScroll(pos), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					m_pMemo->getTextArea()->setScroll(PointF{ m_pMemo->getTextArea()->getScroll().X, -m_pMemo->getVScroll()->getScroll() });
					repaint_required = true;
				}
				break;
			case Element::HScroll:
				if (m_pMemo->getHScroll()->NotifyOnMouseMove(LocalToHScroll(pos), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					m_pMemo->getTextArea()->setScroll(PointF{ -m_pMemo->getHScroll()->getScroll(), m_pMemo->getTextArea()->getScroll().Y });
					repaint_required = true;
				}
				break;
			default:
				switch (m_pMemo->m_eHoveredElement)
				{
				case Element::Text:
					if (m_pMemo->getTextArea()->NotifyOnMouseMove(LocalToTextArea(pos), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						repaint_required = true;
					break;
				case Element::VScroll:
					if (m_pMemo->getVScroll()->NotifyOnMouseMove(LocalToVScroll(pos), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						repaint_required = true;
					break;
				case Element::HScroll:
					if (m_pMemo->getHScroll()->NotifyOnMouseMove(LocalToHScroll(pos), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						repaint_required = true;
					break;
				default:
					break;
				}
			}
			if (repaint_required)
			{
				if (m_pMemo->m_pCanvas)
					m_pMemo->m_pCanvas->setValid(false);
				m_pMemo->Repaint(false);
			}
		}

		void CMemoService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pMemo->getForm()->CaptureMouse(m_pMemo, true);
			if (!m.Middle && !m.Right)
			{
				bool repaint_required{ false };
				switch (m_pMemo->m_eHoveredElement)
				{
				case Element::Text:
					if (m_pMemo->getTextArea()->NotifyOnMouseLeftDown(LocalToTextArea(m_pMemo->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						repaint_required = true;
					break;
				case Element::VScroll:
					if (m_pMemo->getVScroll()->NotifyOnMouseLeftDown(LocalToVScroll(m_pMemo->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						m_pMemo->getTextArea()->setScroll(PointF{ m_pMemo->getTextArea()->getScroll().X, -m_pMemo->getVScroll()->getScroll() });
						repaint_required = true;
					}
					break;
				case Element::HScroll:
					if (m_pMemo->getHScroll()->NotifyOnMouseLeftDown(LocalToHScroll(m_pMemo->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						m_pMemo->getTextArea()->setScroll(PointF{ -m_pMemo->getHScroll()->getScroll(), m_pMemo->getTextArea()->getScroll().Y });
						repaint_required = true;
					}
					break;
				default:
					break;
				}
				m_pMemo->m_eMouseDownElement = m_pMemo->m_eHoveredElement;
				if (repaint_required)
				{
					if (m_pMemo->m_pCanvas)
						m_pMemo->m_pCanvas->setValid(false);
					m_pMemo->Repaint(false);
				}
			}
		}

		void CMemoService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(m.Position);
		}

		void CMemoService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m.Middle && !m.Right && m_pMemo->m_eHoveredElement == Element::Text && m_pMemo->getTextArea()->NotifyOnMouseLeftDoubleClick(
				LocalToTextArea(m_pMemo->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pMemo->m_pCanvas)
					m_pMemo->m_pCanvas->setValid(false);
				m_pMemo->Repaint(false);
			}
		}

		void CMemoService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMemoService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMemoService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMemoService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMemoService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMemoService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMemoService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			switch (m_pMemo->m_eHoveredElement)
			{
			case Element::Text:
				if (m_pMemo->getTextArea()->NotifyOnMouseVerticalWheel(LocalToTextArea(m_pMemo->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					m_pMemo->UpdateScrollPositions();
					if (m_pMemo->m_pCanvas)
						m_pMemo->m_pCanvas->setValid(false);
					m_pMemo->Repaint(false);
				}
				break;
			case Element::VScroll:
				if (m_pMemo->getVScroll()->NotifyOnMouseVerticalWheel(LocalToVScroll(m_pMemo->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					m_pMemo->getTextArea()->setScroll(PointF{ m_pMemo->getTextArea()->getScroll().X, -m_pMemo->getVScroll()->getScroll() });
					if (m_pMemo->m_pCanvas)
						m_pMemo->m_pCanvas->setValid(false);
					m_pMemo->Repaint(false);
				}
				break;
			case Element::HScroll:
				if (m_pMemo->getHScroll()->NotifyOnMouseVerticalWheel(LocalToHScroll(m_pMemo->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					m_pMemo->getTextArea()->setScroll(PointF{ -m_pMemo->getHScroll()->getScroll(), m_pMemo->getTextArea()->getScroll().Y });
					if (m_pMemo->m_pCanvas)
						m_pMemo->m_pCanvas->setValid(false);
					m_pMemo->Repaint(false);
				}
				break;
			default:
				break;
			}
		}

		void CMemoService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			switch (m_pMemo->m_eHoveredElement)
			{
			case Element::Text:
				if (m_pMemo->getTextArea()->NotifyOnMouseHorizontalWheel(LocalToTextArea(m_pMemo->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					m_pMemo->UpdateScrollPositions();
					if (m_pMemo->m_pCanvas)
						m_pMemo->m_pCanvas->setValid(false);
					m_pMemo->Repaint(false);
				}
				break;
			case Element::VScroll:
				if (m_pMemo->getVScroll()->NotifyOnMouseHorizontalWheel(LocalToVScroll(m_pMemo->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					m_pMemo->getTextArea()->setScroll(PointF{ m_pMemo->getTextArea()->getScroll().X, -m_pMemo->getVScroll()->getScroll() });
					if (m_pMemo->m_pCanvas)
						m_pMemo->m_pCanvas->setValid(false);
					m_pMemo->Repaint(false);
				}
				break;
			case Element::HScroll:
				if (m_pMemo->getHScroll()->NotifyOnMouseHorizontalWheel(LocalToHScroll(m_pMemo->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					m_pMemo->getTextArea()->setScroll(PointF{ -m_pMemo->getHScroll()->getScroll(), m_pMemo->getTextArea()->getScroll().Y });
					if (m_pMemo->m_pCanvas)
						m_pMemo->m_pCanvas->setValid(false);
					m_pMemo->Repaint(false);
				}
				break;
			default:
				break;
			}
		}

		void CMemoService::NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted)
		{
			processed = true;
			if (m_pMemo->getTextArea()->NotifyOnDropFiles(LocalToTextArea(m_pMemo->FormToLocal(m.Position)), m.FileNames))
			{
				m_pMemo->AdjustElements();
				m_pMemo->getTextArea()->ScrollToCaret();
				m_pMemo->UpdateScrollPositions();
				if (m_pMemo->m_pCanvas)
					m_pMemo->m_pCanvas->setValid(false);
				m_pMemo->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Clipboard notifications
		void CMemoService::NotifyOnPasteString(const MessagePasteString &m)
		{
			if (m_pMemo->getTextArea()->NotifyOnPasteString(m.Text))
			{
				m_pMemo->AdjustElements();
				m_pMemo->getTextArea()->ScrollToCaret();
				m_pMemo->UpdateScrollPositions();
				if (m_pMemo->m_pCanvas)
					m_pMemo->m_pCanvas->setValid(false);
				m_pMemo->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Caret notification
		void CMemoService::NotifyOnChange()
		{
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
			m_pMemo->Repaint(false);
		}
	#pragma endregion
	}
}