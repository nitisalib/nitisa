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
		CIconButtonService::CIconButtonService(CIconButton *button) :
			CControlService{ button },
			m_pControl{ button }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CIconButtonService::CheckImageListDetach(IComponent *e)
		{
			IImageList *image_list{ cast<IImageList*>(e) };
			if (image_list)
			{
				bool changed{ false };
				for (int i = 0; i <= (int)CButton::State::Disabled; i++)
					if (m_pControl->m_aImageList[i] == image_list)
					{
						m_pControl->m_aImageList[i] = nullptr;
						changed = true;
					}
				if (changed)
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CIconButtonService::CheckImageListChange(IComponent *e)
		{
			IImageList *image_list{ cast<IImageList*>(e) };
			if (image_list)
				for (int i = 0; i <= (int)CButton::State::Disabled; i++)
					if (m_pControl->m_aImageList[i] == image_list)
					{
						if (m_pControl->m_pCanvas)
							m_pControl->m_pCanvas->setValid(false);
						m_pControl->Repaint(false);
						break;
					}
		}

		void CIconButtonService::CancelMouseDown()
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
			if (m_pControl->m_bMouseDown)
			{
				m_pControl->m_bMouseDown = false;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Other components/controls/objects change notifications
		void CIconButtonService::NotifyOnComponentDetach(IComponent *component)
		{
			CheckImageListDetach(component);
		}

		void CIconButtonService::NotifyOnControlDetach(IControl *control)
		{
			CheckImageListDetach(control);
		}

		void CIconButtonService::NotifyOnComponentChange(IComponent *component)
		{
			CheckImageListChange(component);
		}

		void CIconButtonService::NotifyOnControlChange(IControl *control)
		{
			CheckImageListChange(control);
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CIconButtonService::NotifyOnParentStyleChange()
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
		void CIconButtonService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
		}

		void CIconButtonService::NotifyOnResize()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CIconButtonService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CIconButtonService::NotifyOnEnable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CIconButtonService::NotifyOnDisable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CIconButtonService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CIconButtonService::NotifyOnKillFocus()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CIconButtonService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CIconButtonService::NotifyOnMouseLeave()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CIconButtonService::NotifyOnKillCaptureMouse()
		{
			if (m_pControl->m_bMouseDown)
			{
				m_pControl->m_bMouseDown = false;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CIconButtonService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CIconButtonService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && !m_pControl->m_bKeyDown && (m.Key == Key::Return || m.Key == Key::Separator))
			{
				bool ctrl, alt, shift;
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (!ctrl && !alt && !shift)
				{
					m_pControl->m_bKeyDown = true;
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CIconButtonService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_bKeyDown)
			{
				if (m_pControl->isEnabled(true) && (m.Key == Key::Return || m.Key == Key::Separator))
				{
					m_pControl->m_bKeyDown = false;
					if (m_pControl->OnClick)
						m_pControl->OnClick(m_pControl);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				else
				{
					m_pControl->m_bKeyDown = false;
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CIconButtonService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && !m_pControl->m_bMouseDown && m.Left && !m.Middle && !m.Right)
			{
				m_pControl->m_bMouseDown = true;
				m_pControl->getForm()->CaptureMouse(m_pControl, true);
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
			else
				CancelMouseDown();
		}

		void CIconButtonService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && m_pControl->m_bMouseDown && m.Left && !m.Middle && !m.Right && m_pControl->isHovered())
			{
				CancelMouseDown();
				if (m_pControl->OnClick)
					m_pControl->OnClick(m_pControl);
			}
			else
				CancelMouseDown();
		}

		void CIconButtonService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CIconButtonService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CIconButtonService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CIconButtonService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CIconButtonService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CIconButtonService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CIconButtonService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}
	#pragma endregion
	}
}