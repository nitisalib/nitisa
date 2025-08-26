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
		CButtonService::CButtonService(CButton *button) :
			CControlService{ button },
			m_pButton{ button }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CButtonService::CheckImageListDetach(IComponent *e)
		{
			IImageList *image_list{ cast<IImageList*>(e) };
			if (image_list)
			{
				bool changed{ false };
				for (int i = 0; i <= (int)CButton::State::Disabled; i++)
					if (m_pButton->m_aImageList[i] == image_list)
					{
						m_pButton->m_aImageList[i] = nullptr;
						changed = true;
					}
				if (changed)
				{
					if (m_pButton->m_pCanvas)
						m_pButton->m_pCanvas->setValid(false);
					m_pButton->Repaint(false);
				}
			}
		}

		void CButtonService::CheckImageListChange(IComponent *e)
		{
			IImageList *image_list{ cast<IImageList*>(e) };
			if (image_list)
				for (int i = 0; i <= (int)CButton::State::Disabled; i++)
					if (m_pButton->m_aImageList[i] == image_list)
					{
						if (m_pButton->m_pCanvas)
							m_pButton->m_pCanvas->setValid(false);
						m_pButton->Repaint(false);
						break;
					}
		}

		void CButtonService::CancelMouseDown()
		{
			if (m_pButton->isCaptureMouse())
				m_pButton->getForm()->ReleaseCaptureMouse();
			if (m_pButton->m_bMouseDown)
			{
				m_pButton->m_bMouseDown = false;
				if (m_pButton->m_pCanvas)
					m_pButton->m_pCanvas->setValid(false);
				m_pButton->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CButtonService::NotifyOnAttach()
		{
			if (!m_pButton->m_bCaptionChanged && m_pButton->getForm())
				m_pButton->setCaption(m_pButton->Name);
		}

		void CButtonService::NotifyOnFreeResources()
		{
			if (m_pButton->m_pCanvas)
			{
				m_pButton->m_pCanvas->Release();
				m_pButton->m_pCanvas = nullptr;
			}
		}
	#pragma endregion

	#pragma region Other components/controls/objects change notifications
		void CButtonService::NotifyOnComponentDetach(IComponent *component)
		{
			CheckImageListDetach(component);
		}

		void CButtonService::NotifyOnControlDetach(IControl *control)
		{
			CheckImageListDetach(control);
		}

		void CButtonService::NotifyOnComponentChange(IComponent *component)
		{
			CheckImageListChange(component);
		}

		void CButtonService::NotifyOnControlChange(IControl *control)
		{
			CheckImageListChange(control);
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CButtonService::NotifyOnParentStyleChange()
		{
			if (m_pButton->getStyle())
			{
				m_pButton->UpdateFromStyle(m_pButton->getStyle());
				if (m_pButton->m_pCanvas)
					m_pButton->m_pCanvas->setValid(false);
			}
		}

		void CButtonService::NotifyOnParentFontChange()
		{
			if (m_pButton->m_pCanvas)
				m_pButton->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CButtonService::NotifyOnResize()
		{
			if (m_pButton->m_pCanvas)
				m_pButton->m_pCanvas->setValid(false);
		}

		void CButtonService::NotifyOnStyleChange()
		{
			if (m_pButton->getStyle())
			{
				m_pButton->UpdateFromStyle(m_pButton->getStyle());
				if (m_pButton->m_pCanvas)
					m_pButton->m_pCanvas->setValid(false);
			}
		}

		void CButtonService::NotifyOnFontChange()
		{
			if (m_pButton->m_pCanvas)
				m_pButton->m_pCanvas->setValid(false);
		}

		void CButtonService::NotifyOnEnable()
		{
			if (m_pButton->m_pCanvas)
				m_pButton->m_pCanvas->setValid(false);
		}

		void CButtonService::NotifyOnDisable()
		{
			if (m_pButton->m_pCanvas)
				m_pButton->m_pCanvas->setValid(false);
		}

		void CButtonService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pButton->m_pCanvas)
				m_pButton->m_pCanvas->setValid(false);
			m_pButton->Repaint(false);
		}

		void CButtonService::NotifyOnKillFocus()
		{
			if (m_pButton->m_pCanvas)
				m_pButton->m_pCanvas->setValid(false);
			m_pButton->Repaint(false);
		}

		void CButtonService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pButton->m_pCanvas)
				m_pButton->m_pCanvas->setValid(false);
			m_pButton->Repaint(false);
		}

		void CButtonService::NotifyOnMouseLeave()
		{
			if (m_pButton->m_pCanvas)
				m_pButton->m_pCanvas->setValid(false);
			m_pButton->Repaint(false);
		}

		void CButtonService::NotifyOnKillCaptureMouse()
		{
			if (m_pButton->m_bMouseDown)
			{
				m_pButton->m_bMouseDown = false;
				if (m_pButton->m_pCanvas)
					m_pButton->m_pCanvas->setValid(false);
				m_pButton->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CButtonService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pButton->getWidth(), 0) && ntl::IsGreater<float>(m_pButton->getHeight(), 0))
				m_pButton->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CButtonService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pButton->isEnabled(true) && !m_pButton->m_bKeyDown && (m.Key == Key::Return || m.Key == Key::Separator))
			{
				bool ctrl, alt, shift;
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (!ctrl && !alt && !shift)
				{
					m_pButton->m_bKeyDown = true;
					if (m_pButton->m_pCanvas)
						m_pButton->m_pCanvas->setValid(false);
					m_pButton->Repaint(false);
				}
			}
		}

		void CButtonService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pButton->m_bKeyDown)
			{
				if (m_pButton->isEnabled(true) && (m.Key == Key::Return || m.Key == Key::Separator))
				{
					m_pButton->m_bKeyDown = false;
					if (m_pButton->OnClick)
						m_pButton->OnClick(m_pButton);
					if (m_pButton->m_pCanvas)
						m_pButton->m_pCanvas->setValid(false);
					m_pButton->Repaint(false);
				}
				else
				{
					m_pButton->m_bKeyDown = false;
					if (m_pButton->m_pCanvas)
						m_pButton->m_pCanvas->setValid(false);
					m_pButton->Repaint(false);
				}
			}
		}

		void CButtonService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pButton->isEnabled(true) && !m_pButton->m_bMouseDown && m.Left && !m.Middle && !m.Right)
			{
				m_pButton->m_bMouseDown = true;
				m_pButton->getForm()->CaptureMouse(m_pButton, true);
				if (m_pButton->m_pCanvas)
					m_pButton->m_pCanvas->setValid(false);
				m_pButton->Repaint(false);
			}
			else
				CancelMouseDown();
		}

		void CButtonService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pButton->isEnabled(true) && m_pButton->m_bMouseDown && m.Left && !m.Middle && !m.Right && m_pButton->isHovered())
			{
				CancelMouseDown();
				if (m_pButton->OnClick)
					m_pButton->OnClick(m_pButton);
			}
			else
				CancelMouseDown();
		}

		void CButtonService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CButtonService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CButtonService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CButtonService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CButtonService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CButtonService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CButtonService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}
	#pragma endregion
	}
}