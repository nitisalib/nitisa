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
		CUpDownService::CUpDownService(CUpDown *updown) :
			CControlService(updown),
			m_pUpDown{ updown }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CUpDownService::CancelDown(const bool check_capture)
		{
			if (m_pUpDown->m_eDownElement != CUpDown::Element::None)
			{
				m_pUpDown->m_eDownElement = CUpDown::Element::None;
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
		void CUpDownService::NotifyOnDetaching()
		{
			if (m_pUpDown->m_pAssignedTo)
			{
				m_pUpDown->m_pSpliceService->Release();
				m_pUpDown->m_pSpliceService = nullptr;
				m_pUpDown->m_pAssignedTo = nullptr;
			}
		}

		void CUpDownService::NotifyOnFreeResources()
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
		void CUpDownService::NotifyOnControlDetach(IControl *control)
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
		void CUpDownService::NotifyOnParentStyleChange()
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
		void CUpDownService::NotifyOnEnable()
		{
			if (m_pUpDown->m_pCanvas)
				m_pUpDown->m_pCanvas->setValid(false);
		}

		void CUpDownService::NotifyOnDisable()
		{
			if (m_pUpDown->m_pCanvas)
				m_pUpDown->m_pCanvas->setValid(false);
		}

		void CUpDownService::NotifyOnResize()
		{
			if (m_pUpDown->m_pCanvas)
				m_pUpDown->m_pCanvas->setValid(false);
		}

		void CUpDownService::NotifyOnStyleChange()
		{
			if (m_pUpDown->getStyle())
			{
				m_pUpDown->UpdateFromStyle(m_pUpDown->getStyle());
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
			}
		}

		void CUpDownService::NotifyOnSetCaptureMouse()
		{
			m_pUpDown->m_hTimer = m_pUpDown->getForm()->CreateTimer(this, m_pUpDown->m_fTimerInterval);
		}

		void CUpDownService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CUpDownService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pUpDown->getWidth(), 0) && ntl::IsGreater<float>(m_pUpDown->getHeight(), 0))
				m_pUpDown->Render();
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CUpDownService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
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
						if (m_pUpDown->m_eDownElement != CUpDown::Element::UpArrow)
						{
							m_pUpDown->m_eDownElement = CUpDown::Element::UpArrow;
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
						if (m_pUpDown->m_eDownElement != CUpDown::Element::DownArrow)
						{
							m_pUpDown->m_eDownElement = CUpDown::Element::DownArrow;
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

		void CUpDownService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			CancelDown(true);
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CUpDownService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pUpDown->UpdateHoveredElement(m_pUpDown->FormToLocal(m.Position)))
			{
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
				m_pUpDown->Repaint(false);
			}
		}

		void CUpDownService::NotifyOnMouseLeave()
		{
			if (m_pUpDown->m_eHoveredElement != CUpDown::Element::None)
			{
				m_pUpDown->m_eHoveredElement = CUpDown::Element::None;
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
				m_pUpDown->Repaint(false);
			}
		}

		void CUpDownService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pUpDown->m_eDownElement != CUpDown::Element::None)
			{
				if (m_pUpDown->m_bChangeByDrag)
				{
					if (m_bDragging)
					{
						float y{ m.Position.Y - m_fLastY };
						bool changed;
						if (y < 0)
							changed = m_pUpDown->setValue(m_pUpDown->m_iValue + ntl::Round<int>(m_pUpDown->m_fDragShift + m_pUpDown->m_fDragScale * std::pow(m_pUpDown->m_fDragBase, m_pUpDown->m_fDragBaseShift - m_pUpDown->m_fDragBaseScale * y)));
						else
							changed = m_pUpDown->setValue(m_pUpDown->m_iValue - ntl::Round<int>(m_pUpDown->m_fDragShift + m_pUpDown->m_fDragScale * std::pow(m_pUpDown->m_fDragBase, m_pUpDown->m_fDragBaseShift + m_pUpDown->m_fDragBaseScale * y)));
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
							bool changed{ m_pUpDown->setValue(m_iOldValue) };
							if (y < 0)
								changed = m_pUpDown->setValue(m_pUpDown->m_iValue + ntl::Round<int>(m_pUpDown->m_fDragShift + m_pUpDown->m_fDragScale * std::pow(m_pUpDown->m_fDragBase, m_pUpDown->m_fDragBaseShift - m_pUpDown->m_fDragBaseScale * y)));
							else
								changed = m_pUpDown->setValue(m_pUpDown->m_iValue - ntl::Round<int>(m_pUpDown->m_fDragShift + m_pUpDown->m_fDragScale * std::pow(m_pUpDown->m_fDragBase, m_pUpDown->m_fDragBaseShift + m_pUpDown->m_fDragBaseScale * (y - m_pUpDown->getHeight()))));
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

		void CUpDownService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pUpDown->isEnabled(true) && m_pUpDown->m_eDownElement == CUpDown::Element::None && m_pUpDown->m_eHoveredElement != CUpDown::Element::None)
			{
				m_bDragging = false;
				m_iOldValue = m_pUpDown->m_iValue;
				m_fLastY = m.Position.Y;
				m_pUpDown->m_eDownElement = m_pUpDown->m_eHoveredElement;
				if ((m_pUpDown->m_eDownElement == CUpDown::Element::UpArrow ? m_pUpDown->Up() : m_pUpDown->Down()) && m_pUpDown->OnChange)
					m_pUpDown->OnChange(m_pUpDown);
				m_pUpDown->getForm()->CaptureMouse(m_pUpDown, true);
				if (m_pUpDown->m_pCanvas)
					m_pUpDown->m_pCanvas->setValid(false);
				m_pUpDown->Repaint(false);
			}
			else
				CancelDown(true);
		}

		void CUpDownService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true);
		}

		void CUpDownService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CUpDownService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pUpDown->isEnabled(true))
				if ((m.Delta > 0 ? m_pUpDown->Up() : m_pUpDown->Down()) && m_pUpDown->OnChange)
					m_pUpDown->OnChange(m_pUpDown);
		}
	#pragma endregion

	#pragma region Timer notification
		void CUpDownService::NotifyOnTimer(const PlatformHandle id)
		{
			switch (m_pUpDown->m_eDownElement)
			{
			case CUpDown::Element::UpArrow:
				if (m_pUpDown->m_eHoveredElement == CUpDown::Element::UpArrow)
					if (m_pUpDown->setValue(m_pUpDown->getValue() + m_pUpDown->m_iStep))
						if (m_pUpDown->OnChange)
							m_pUpDown->OnChange(m_pUpDown);
				break;
			case CUpDown::Element::DownArrow:
				if (m_pUpDown->m_eHoveredElement == CUpDown::Element::DownArrow)
					if (m_pUpDown->setValue(m_pUpDown->getValue() - m_pUpDown->m_iStep))
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