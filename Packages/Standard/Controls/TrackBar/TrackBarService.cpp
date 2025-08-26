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
		CTrackBarService::CTrackBarService(CTrackBar *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CTrackBarService::MouseUp()
		{
			if (m_pControl->isCaptureMouse())
			{
				m_pControl->getForm()->ReleaseCaptureMouse();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CTrackBarService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CTrackBarService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
		}

		void CTrackBarService::NotifyOnEnable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CTrackBarService::NotifyOnDisable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CTrackBarService::NotifyOnResize()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CTrackBarService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CTrackBarService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTrackBarService::NotifyOnKillFocus()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CTrackBarService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CTrackBarService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			switch (m.Key)
			{
			case Key::Left:
			case Key::Numpad4:
				if (m.Key == Key::Left || (m.Key == Key::Numpad4 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (m_pControl->setValue(m_pControl->getValue() - 1) && m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
				}
				break;
			case Key::Right:
			case Key::Numpad6:
				if (m.Key == Key::Right || (m.Key == Key::Numpad6 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (m_pControl->setValue(m_pControl->getValue() + 1) && m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
				}
				break;
			case Key::Prior:
			case Key::Numpad9:
				if (m.Key == Key::Prior || (m.Key == Key::Numpad9 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (m_pControl->setValue(m_pControl->getValue() - ntl::Max<int>(1, m_pControl->m_iTickInterval)) && m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
				}
				break;
			case Key::Next:
			case Key::Numpad3:
				if (m.Key == Key::Next || (m.Key == Key::Numpad4 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (m_pControl->setValue(m_pControl->getValue() + ntl::Max<int>(1, m_pControl->m_iTickInterval)) && m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
				}
				break;
			case Key::Home:
			case Key::Numpad7:
				if (m.Key == Key::Home || (m.Key == Key::Numpad7 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (m_pControl->setValue(m_pControl->getMin()) && m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
				}
				break;
			case Key::End:
			case Key::Numpad1:
				if (m.Key == Key::End || (m.Key == Key::Numpad1 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (m_pControl->setValue(m_pControl->getMax()) && m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
				}
				break;
			default:
				break;
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CTrackBarService::NotifyOnMouseHover(const MessagePosition &m)
		{
			m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position));
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTrackBarService::NotifyOnMouseLeave()
		{
			m_pControl->UpdateHoveredElement(m_pControl->FormToLocal((PointF)m_pControl->getForm()->ScreenToClient(Application->Mouse->getPosition())));
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTrackBarService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isCaptureMouse())
			{
				if (m_pControl->setValue(m_pControl->ClientToValue(m_pControl->FormToLocal(m.Position))) && m_pControl->OnChange)
					m_pControl->OnChange(m_pControl);
			}
			else if (m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CTrackBarService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m.Middle && !m.Right && !m_pControl->isCaptureMouse() && m_pControl->isEnabled(true))
			{
				if (m_pControl->setValue(m_pControl->ClientToValue(m_pControl->FormToLocal(m.Position))))
				{
					if (m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				m_pControl->getForm()->CaptureMouse(m_pControl, true);
			}
			else
				MouseUp();
		}

		void CTrackBarService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp();
		}

		void CTrackBarService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CTrackBarService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CTrackBarService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CTrackBarService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CTrackBarService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CTrackBarService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CTrackBarService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CTrackBarService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->setValue(m_pControl->getValue() + (m.Delta < 0 ? 1 : -1)) && m_pControl->OnChange)
					m_pControl->OnChange(m_pControl);
			}
		}

		void CTrackBarService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->setValue(m_pControl->getValue() + (m.Delta < 0 ? 1 : -1)) && m_pControl->OnChange)
					m_pControl->OnChange(m_pControl);
			}
		}
	#pragma endregion
	}
}