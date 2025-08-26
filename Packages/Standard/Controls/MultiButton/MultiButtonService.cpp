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
		CMultiButtonService::CMultiButtonService(CMultiButton *control):
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CMultiButtonService::CancelDown(const bool release_capture)
		{
			bool repainted{ false };
			if (m_pControl->m_hTimer)
			{
				m_pControl->getForm()->DeleteTimer(m_pControl->m_hTimer);
				m_pControl->m_hTimer = nullptr;
			}
			if (m_pControl->m_bHasExtra)
			{
				m_pControl->Repaint(false);
				m_pControl->m_bHasExtra = false;
				repainted = false;
			}
			if (m_pControl->m_bEnterDown)
			{
				m_pControl->m_bEnterDown = false;
				if (!repainted)
					m_pControl->Repaint(false);
			}
			if (release_capture && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion

	#pragma region State change notifications
		void CMultiButtonService::NotifyOnFreeResources()
		{
			if (m_pControl->m_hTimer)
			{
				m_pControl->getForm()->DeleteTimer(m_pControl->m_hTimer);
				m_pControl->m_hTimer = nullptr;
			}
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			if (m_pControl->m_pCanvasExtra)
			{
				m_pControl->m_pCanvasExtra->Release();
				m_pControl->m_pCanvasExtra = nullptr;
			}
			m_pControl->m_bHasExtra = false;
		}
	#pragma endregion

	#pragma region Component notifications
		void CMultiButtonService::NotifyOnComponentDetach(IComponent *component)
		{
			if (component == m_pControl->m_pImageList)
			{
				m_pControl->m_pImageList = nullptr;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
					m_pControl->m_pCanvasExtra->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMultiButtonService::NotifyOnComponentChange(IComponent *component)
		{
			if (component == m_pControl->m_pImageList)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
					m_pControl->m_pCanvasExtra->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Control notifications
		void CMultiButtonService::NotifyOnControlDetach(IControl *control)
		{
			if (control == cast<IControl*>(m_pControl->m_pImageList))
			{
				m_pControl->m_pImageList = nullptr;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
					m_pControl->m_pCanvasExtra->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMultiButtonService::NotifyOnControlChange(IControl *control)
		{
			if (control == cast<IControl*>(m_pControl->m_pImageList))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
					m_pControl->m_pCanvasExtra->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CMultiButtonService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
					m_pControl->m_pCanvasExtra->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMultiButtonService::NotifyOnParentFontChange()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
				m_pControl->m_pCanvasExtra->setValid(false);
			m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CMultiButtonService::NotifyOnEnable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
				m_pControl->m_pCanvasExtra->setValid(false);
		}

		void CMultiButtonService::NotifyOnDisable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
				m_pControl->m_pCanvasExtra->setValid(false);
		}

		void CMultiButtonService::NotifyOnResize()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
				m_pControl->m_pCanvasExtra->setValid(false);
		}

		void CMultiButtonService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
					m_pControl->m_pCanvasExtra->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMultiButtonService::NotifyOnFontChange()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
				m_pControl->m_pCanvasExtra->setValid(false);
			m_pControl->Repaint(false);
		}

		void CMultiButtonService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
				m_pControl->m_pCanvasExtra->setValid(false);
			m_pControl->Repaint(false);
		}

		void CMultiButtonService::NotifyOnKillFocus()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
				m_pControl->m_pCanvasExtra->setValid(false);
			m_pControl->Repaint(false);
		}

		void CMultiButtonService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CMultiButtonService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
			{
				if (m.LastPass)
				{
					if (m_pControl->m_bHasExtra)
						m_pControl->RenderExtra();
				}
				else
					m_pControl->Render();
			}
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CMultiButtonService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			if (!m_pControl->m_bHasExtra && !m_pControl->m_hTimer && !m_pControl->m_bEnterDown && m_pControl->m_aButtons.size() > 0 && m_pControl->isEnabled(true))
			{
				bool ctrl, alt, shift;
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (!ctrl && !alt && !shift)
				{
					switch (m.Key)
					{
					case Key::Return:
					case Key::Separator:
						if (ntl::IsBetween<int>(m_pControl->m_iActiveButtonIndex, 0, (int)m_pControl->m_aButtons.size() - 1))
						{
							m_pControl->m_bEnterDown = true;
							if (m_pControl->m_pCanvas)
								m_pControl->m_pCanvas->setValid(false);
							m_pControl->Repaint(false);
						}
						break;
					case Key::Up:
					case Key::Numpad8:
						if (m.Key == Key::Up || !Application->Keyboard->isToggled(Key::NumLock))
						{
							switch (m_pControl->m_eOpenDirection)
							{
							case CMultiButton::OpenDirection::Top:
								m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex + 1, 0, (int)m_pControl->m_aButtons.size() - 1));
								break;
							case CMultiButton::OpenDirection::Bottom:
								m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex - 1, 0, (int)m_pControl->m_aButtons.size() - 1));
								break;
							default:
								break;
							}
						}
						break;
					case Key::Down:
					case Key::Numpad2:
						if (m.Key == Key::Down || !Application->Keyboard->isToggled(Key::NumLock))
						{
							switch (m_pControl->m_eOpenDirection)
							{
							case CMultiButton::OpenDirection::Top:
								m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex - 1, 0, (int)m_pControl->m_aButtons.size() - 1));
								break;
							case CMultiButton::OpenDirection::Bottom:
								m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex + 1, 0, (int)m_pControl->m_aButtons.size() - 1));
								break;
							default:
								break;
							}
						}
						break;
					case Key::Left:
					case Key::Numpad4:
						if (m.Key == Key::Left || !Application->Keyboard->isToggled(Key::NumLock))
						{
							switch (m_pControl->m_eOpenDirection)
							{
							case CMultiButton::OpenDirection::Left:
								m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex + 1, 0, (int)m_pControl->m_aButtons.size() - 1));
								break;
							case CMultiButton::OpenDirection::Right:
								m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex - 1, 0, (int)m_pControl->m_aButtons.size() - 1));
								break;
							default:
								break;
							}
						}
						break;
					case Key::Right:
					case Key::Numpad6:
						if (m.Key == Key::Right || !Application->Keyboard->isToggled(Key::NumLock))
						{
							switch (m_pControl->m_eOpenDirection)
							{
							case CMultiButton::OpenDirection::Left:
								m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex - 1, 0, (int)m_pControl->m_aButtons.size() - 1));
								break;
							case CMultiButton::OpenDirection::Right:
								m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex + 1, 0, (int)m_pControl->m_aButtons.size() - 1));
								break;
							default:
								break;
							}
						}
						break;
					default:
						break;
					}
				}
			}
			processed = true;
		}

		void CMultiButtonService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			if (!m_pControl->m_bHasExtra && !m_pControl->m_hTimer && m_pControl->m_bEnterDown && m_pControl->m_aButtons.size() > 0 && m_pControl->isEnabled(true))
			{
				if (m.Key == Key::Return || m.Key == Key::Separator)
				{
					bool ctrl, alt, shift;
					Application->Keyboard->getControlKeys(ctrl, alt, shift);
					if (m_pControl->OnClick)
						m_pControl->OnClick(m_pControl);
				}
				m_pControl->m_bEnterDown = false;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
			processed = true;
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CMultiButtonService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->UpdateHoveredButtonIndex(m_pControl->FormToLocal(m.Position)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
					m_pControl->m_pCanvasExtra->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMultiButtonService::NotifyOnMouseLeave()
		{
			if (m_pControl->UpdateHoveredButtonIndex())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
					m_pControl->m_pCanvasExtra->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMultiButtonService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->UpdateHoveredButtonIndex(m_pControl->FormToLocal(m.Position)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
					m_pControl->m_pCanvasExtra->setValid(false);
				m_pControl->Repaint(false);
			}
			processed = true;
		}

		void CMultiButtonService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (!m_pControl->m_bHasExtra && !m_pControl->m_hTimer && !m_pControl->m_bEnterDown && !m.Middle && !m.Right && !m.Ctrl && !m.Alt && !m.Shift && m_pControl->m_aButtons.size() > 0 && m_pControl->isEnabled(true))
			{
				m_pControl->m_hTimer = m_pControl->getForm()->CreateTimer(&m_pControl->m_cTimerListener, m_pControl->m_fDelay);
				m_pControl->getForm()->CaptureMouse(m_pControl, true);
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
			else
				CancelDown(true);
			processed = true;
		}

		void CMultiButtonService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (!m.Middle && !m.Right && !m.Ctrl && !m.Alt && !m.Shift)
			{
				if (m_pControl->m_hTimer)
				{
					CancelDown(true);
					if (m_pControl->getRect().is_inside(m_pControl->FormToLocal(m.Position)) && ntl::IsBetween<int>(m_pControl->m_iActiveButtonIndex, 0, (int)m_pControl->m_aButtons.size() - 1) && m_pControl->OnClick)
						m_pControl->OnClick(m_pControl);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				else if (m_pControl->m_bHasExtra)
				{
					CancelDown(true);
					if (m_pControl->m_iHoveredButtonIndex >= 0)
						m_pControl->m_iActiveButtonIndex = m_pControl->m_iHoveredButtonIndex;
					m_pControl->UpdateHoveredButtonIndex(m_pControl->FormToLocal(m.Position));
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
				}
				else
					CancelDown(true);
			}
			else
				CancelDown(true);
			processed = true;
		}

		void CMultiButtonService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CMultiButtonService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CMultiButtonService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CMultiButtonService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CMultiButtonService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CMultiButtonService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CMultiButtonService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CMultiButtonService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			if (!m_pControl->m_bHasExtra && !m_pControl->m_hTimer && !m_pControl->m_bEnterDown && !m.Left && !m.Middle && !m.Right && !m.Ctrl && !m.Alt && !m.Shift && m_pControl->m_aButtons.size() > 0 && m_pControl->isEnabled(true))
			{
				switch (m_pControl->m_eOpenDirection)
				{
				case CMultiButton::OpenDirection::Top:
					m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex + ntl::Sign<int>(m.Delta), 0, (int)m_pControl->m_aButtons.size() - 1));
					break;
				case CMultiButton::OpenDirection::Right:
					m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex - ntl::Sign<int>(m.Delta), 0, (int)m_pControl->m_aButtons.size() - 1));
					break;
				case CMultiButton::OpenDirection::Bottom:
					m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex - ntl::Sign<int>(m.Delta), 0, (int)m_pControl->m_aButtons.size() - 1));
					break;
				default:
					m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex + ntl::Sign<int>(m.Delta), 0, (int)m_pControl->m_aButtons.size() - 1));
					break;
				}
			}
			processed = true;
		}

		void CMultiButtonService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			if (!m_pControl->m_bHasExtra && !m_pControl->m_hTimer && !m_pControl->m_bEnterDown && !m.Left && !m.Middle && !m.Right && !m.Ctrl && !m.Alt && !m.Shift && m_pControl->m_aButtons.size() > 0 && m_pControl->isEnabled(true))
			{
				switch (m_pControl->m_eOpenDirection)
				{
				case CMultiButton::OpenDirection::Top:
					m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex - ntl::Sign<int>(m.Delta), 0, (int)m_pControl->m_aButtons.size() - 1));
					break;
				case CMultiButton::OpenDirection::Right:
					m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex + ntl::Sign<int>(m.Delta), 0, (int)m_pControl->m_aButtons.size() - 1));
					break;
				case CMultiButton::OpenDirection::Bottom:
					m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex + ntl::Sign<int>(m.Delta), 0, (int)m_pControl->m_aButtons.size() - 1));
					break;
				default:
					m_pControl->setActiveButtonIndex(ntl::Clamp<int>(m_pControl->m_iActiveButtonIndex - ntl::Sign<int>(m.Delta), 0, (int)m_pControl->m_aButtons.size() - 1));
					break;
				}
			}
			processed = true;
		}
	#pragma endregion

	#pragma region IComponentItemListService methods
		bool CMultiButtonService::MoveItem(IListItem *item, const int before)
		{
			return MoveListItem(m_pControl->m_aButtons, m_pControl, item, before);
		}
	#pragma endregion
	}
}