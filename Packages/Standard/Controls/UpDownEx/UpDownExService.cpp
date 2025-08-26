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
		CUpDownExService::CUpDownExService(CUpDownEx *updown) :
			CControlService(updown),
			m_pUpDown{ updown }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CUpDownExService::CancelDown(const bool check_capture)
		{
			if (m_pUpDown->m_eDownElement != CUpDownEx::Element::None)
			{
				m_pUpDown->m_eDownElement = CUpDownEx::Element::None;
				if (m_pUpDown->m_hTimer)
				{
					m_pUpDown->getForm()->DeleteTimer(m_pUpDown->m_hTimer);
					m_pUpDown->m_hTimer = nullptr;
				}
				if (check_capture && m_pUpDown->isCaptureMouse())
					m_pUpDown->getForm()->ReleaseCaptureMouse();
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
				m_pUpDown->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CUpDownExService::NotifyOnDetaching()
		{
			if (m_pUpDown->m_pAssignedTo)
			{
				m_pUpDown->m_pSpliceService->Release();
				m_pUpDown->m_pSpliceService = nullptr;
				m_pUpDown->m_pAssignedTo = nullptr;
			}
		}

		void CUpDownExService::NotifyOnFreeResources()
		{
			if (m_pUpDown->m_pCanvas)
			{
				m_pUpDown->m_pCanvas->Release();
				m_pUpDown->m_pCanvas = nullptr;
			}
			if (m_pUpDown->m_hTimer && m_pUpDown->getForm())
			{
				m_pUpDown->getForm()->DeleteTimer(m_pUpDown->m_hTimer);
				m_pUpDown->m_hTimer = nullptr;
			}
		}
	#pragma endregion

	#pragma region Control notifications
		void CUpDownExService::NotifyOnControlDetach(IControl *control)
		{
			if (control == m_pUpDown->m_pAssignedTo)
			{
				m_pUpDown->m_pSpliceService->Release();
				m_pUpDown->m_pSpliceService = nullptr;
				m_pUpDown->m_pAssignedTo = nullptr;
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CUpDownExService::NotifyOnParentStyleChange()
		{
			if (m_pUpDown->getStyle())
			{
				m_pUpDown->UpdateFromStyle(m_pUpDown->getStyle());
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CUpDownExService::NotifyOnEnable()
		{
			if (m_pUpDown->m_pCanvas)
				m_pUpDown->m_pCanvas->setValid(false);
		}

		void CUpDownExService::NotifyOnDisable()
		{
			if (m_pUpDown->m_pCanvas)
				m_pUpDown->m_pCanvas->setValid(false);
		}

		void CUpDownExService::NotifyOnResize()
		{
			if (m_pUpDown->m_pCanvas)
				m_pUpDown->m_pCanvas->setValid(false);
		}

		void CUpDownExService::NotifyOnStyleChange()
		{
			if (m_pUpDown->getStyle())
			{
				m_pUpDown->UpdateFromStyle(m_pUpDown->getStyle());
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
			}
		}

		void CUpDownExService::NotifyOnSetCaptureMouse()
		{
			m_pUpDown->m_hTimer = m_pUpDown->getForm()->CreateTimer(this, m_pUpDown->m_fTimerInterval);
		}

		void CUpDownExService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CUpDownExService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pUpDown->getWidth(), 0) && ntl::IsGreater<float>(m_pUpDown->getHeight(), 0))
				m_pUpDown->Render();
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CUpDownExService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pUpDown->isEnabled(true))
			{
				switch (m.Key)
				{
				case Key::Up:
				case Key::Numpad8:
					if (m.Key == Key::Up || (m.Key == Key::Numpad8 && !Application->Keyboard->isToggled(Key::NumLock)))
					{
						if (m_pUpDown->Up() && m_pUpDown->OnChange)
							m_pUpDown->OnChange(m_pUpDown);
						if (m_pUpDown->m_eDownElement != CUpDownEx::Element::UpArrow)
						{
							m_pUpDown->m_eDownElement = CUpDownEx::Element::UpArrow;
							if (m_pUpDown->m_pCanvas)
								m_pUpDown->m_pCanvas->setValid(false);
							m_pUpDown->Repaint(false);
						}
					}
					break;
				case Key::Down:
				case Key::Numpad2:
					if (m.Key == Key::Down || (m.Key == Key::Numpad2 && !Application->Keyboard->isToggled(Key::NumLock)))
					{
						if (m_pUpDown->Down() && m_pUpDown->OnChange)
							m_pUpDown->OnChange(m_pUpDown);
						if (m_pUpDown->m_eDownElement != CUpDownEx::Element::DownArrow)
						{
							m_pUpDown->m_eDownElement = CUpDownEx::Element::DownArrow;
							if (m_pUpDown->m_pCanvas)
								m_pUpDown->m_pCanvas->setValid(false);
							m_pUpDown->Repaint(false);
						}
					}
					break;
				default:
					break;
				}
			}
		}

		void CUpDownExService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			CancelDown(true);
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CUpDownExService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pUpDown->UpdateHoveredElement(m_pUpDown->FormToLocal(m.Position)))
			{
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
				m_pUpDown->Repaint(false);
			}
		}

		void CUpDownExService::NotifyOnMouseLeave()
		{
			if (m_pUpDown->m_eHoveredElement != CUpDownEx::Element::None)
			{
				m_pUpDown->m_eHoveredElement = CUpDownEx::Element::None;
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
				m_pUpDown->Repaint(false);
			}
		}

		void CUpDownExService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pUpDown->m_eDownElement != CUpDownEx::Element::None)
			{
				if (m_pUpDown->m_bChangeByDrag)
				{
					if (m_bDragging)
					{
						float y{ m.Position.Y - m_fLastY };
						bool changed;
						if (y < 0)
							changed = m_pUpDown->setValue(m_pUpDown->m_fValue + m_pUpDown->m_fDragShift + m_pUpDown->m_fDragScale * std::pow(m_pUpDown->m_fDragBase, m_pUpDown->m_fDragBaseShift - m_pUpDown->m_fDragBaseScale * y));
						else
							changed = m_pUpDown->setValue(m_pUpDown->m_fValue - m_pUpDown->m_fDragShift - m_pUpDown->m_fDragScale * std::pow(m_pUpDown->m_fDragBase, m_pUpDown->m_fDragBaseShift + m_pUpDown->m_fDragBaseScale * y));
						if (changed && m_pUpDown->OnChange)
							m_pUpDown->OnChange(m_pUpDown);
					}
					else
					{
						float y{ m_pUpDown->FormToLocal(m.Position).Y };
						if (y < 0 || y > m_pUpDown->getHeight())
						{
							if (m_pUpDown->m_hTimer)
							{
								m_pUpDown->getForm()->DeleteTimer(m_pUpDown->m_hTimer);
								m_pUpDown->m_hTimer = nullptr;
							}
							m_bDragging = true;
							bool changed{ m_pUpDown->setValue(m_fOldValue) };
							if (y < 0)
								changed = m_pUpDown->setValue(m_pUpDown->m_fValue + m_pUpDown->m_fDragShift + m_pUpDown->m_fDragScale * std::pow(m_pUpDown->m_fDragBase, m_pUpDown->m_fDragBaseShift - m_pUpDown->m_fDragBaseScale * y));
							else
								changed = m_pUpDown->setValue(m_pUpDown->m_fValue - m_pUpDown->m_fDragShift - m_pUpDown->m_fDragScale * std::pow(m_pUpDown->m_fDragBase, m_pUpDown->m_fDragBaseShift + m_pUpDown->m_fDragBaseScale * (y - m_pUpDown->getHeight())));
							if (changed && m_pUpDown->OnChange)
								m_pUpDown->OnChange(m_pUpDown);
						}
					}
				}
			}
			else if (m_pUpDown->UpdateHoveredElement(m_pUpDown->FormToLocal(m.Position)))
			{
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
				m_pUpDown->Repaint(false);
			}
			if (m_bDragging)
			{
				Point p{ Application->Mouse->getPosition() };
				if (p.Y == 0)
				{
					p.Y = Application->Screen->getHeight() - 1;
					Application->Mouse->setPosition(p);
					m_fLastY = (float)m_pUpDown->getForm()->ScreenToClient(p).Y;
				}
				else if (p.Y == Application->Screen->getHeight() - 1)
				{
					p.Y = 0;
					Application->Mouse->setPosition(p);
					m_fLastY = (float)m_pUpDown->getForm()->ScreenToClient(p).Y;
				}
				else
					m_fLastY = m.Position.Y;
			}
		}

		void CUpDownExService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pUpDown->isEnabled(true) && m_pUpDown->m_eDownElement == CUpDownEx::Element::None && m_pUpDown->m_eHoveredElement != CUpDownEx::Element::None)
			{
				m_bDragging = false;
				m_fOldValue = m_pUpDown->m_fValue;
				m_fLastY = m.Position.Y;
				m_pUpDown->m_eDownElement = m_pUpDown->m_eHoveredElement;
				if ((m_pUpDown->m_eDownElement == CUpDownEx::Element::UpArrow ? m_pUpDown->Up() : m_pUpDown->Down()) && m_pUpDown->OnChange)
					m_pUpDown->OnChange(m_pUpDown);
				m_pUpDown->getForm()->CaptureMouse(m_pUpDown, true);
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
				m_pUpDown->Repaint(false);
			}
			else
				CancelDown(true);
		}

		void CUpDownExService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true);
		}

		void CUpDownExService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownExService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownExService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownExService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownExService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownExService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownExService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownExService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pUpDown->isEnabled(true))
				if ((m.Delta > 0 ? m_pUpDown->Up() : m_pUpDown->Down()) && m_pUpDown->OnChange)
					m_pUpDown->OnChange(m_pUpDown);
		}
	#pragma endregion

	#pragma region Timer notification
		void CUpDownExService::NotifyOnTimer(const PlatformHandle id)
		{
			switch (m_pUpDown->m_eDownElement)
			{
			case CUpDownEx::Element::UpArrow:
				if (m_pUpDown->m_eHoveredElement == CUpDownEx::Element::UpArrow)
					if (m_pUpDown->setValue(m_pUpDown->getValue() + m_pUpDown->m_fStep))
						if (m_pUpDown->OnChange)
							m_pUpDown->OnChange(m_pUpDown);
				break;
			case CUpDownEx::Element::DownArrow:
				if (m_pUpDown->m_eHoveredElement == CUpDownEx::Element::DownArrow)
					if (m_pUpDown->setValue(m_pUpDown->getValue() - m_pUpDown->m_fStep))
						if (m_pUpDown->OnChange)
							m_pUpDown->OnChange(m_pUpDown);
				break;
			default:
				break;
			}
		}
	#pragma endregion
	}
}