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
		CRadioButtonService::CRadioButtonService(CRadioButton *radiobutton) :
			CControlService{ radiobutton },
			m_pRadioButton{ radiobutton }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CRadioButtonService::CancelMouseDown()
		{
			if (m_pRadioButton->isCaptureMouse())
				m_pRadioButton->getForm()->ReleaseCaptureMouse();
			if (m_pRadioButton->m_bMouseDown)
			{
				m_pRadioButton->m_bMouseDown = false;
				if (m_pRadioButton->m_pCanvas)
					m_pRadioButton->m_pCanvas->setValid(false);
				m_pRadioButton->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CRadioButtonService::NotifyOnParentStyleChange()
		{
			if (m_pRadioButton->getStyle())
			{
				m_pRadioButton->UpdateFromStyle(m_pRadioButton->getStyle());
				if (m_pRadioButton->m_pCanvas)
					m_pRadioButton->m_pCanvas->setValid(false);
			}
		}

		void CRadioButtonService::NotifyOnParentFontChange()
		{
			m_pRadioButton->UpdateAutoSize();
			if (m_pRadioButton->m_pCanvas)
				m_pRadioButton->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CRadioButtonService::NotifyOnAttach()
		{
			if (m_pRadioButton->getForm())
			{
				if (!m_pRadioButton->m_bCaptionChanged)
					m_pRadioButton->setCaption(m_pRadioButton->m_sName);
				m_pRadioButton->UpdateAutoSize();
			}
			if (m_pRadioButton->m_bChecked && m_pRadioButton->m_iGroupIndex >= 0 && m_pRadioButton->HaveCheckedOnParent())
			{
				m_pRadioButton->m_bChecked = false;
				if (m_pRadioButton->OnChange)
					m_pRadioButton->OnChange(m_pRadioButton);
			}
		}

		void CRadioButtonService::NotifyOnFreeResources()
		{
			if (m_pRadioButton->m_pCanvas)
			{
				m_pRadioButton->m_pCanvas->Release();
				m_pRadioButton->m_pCanvas = nullptr;
			}
		}

		void CRadioButtonService::NotifyOnStyleChange()
		{
			if (m_pRadioButton->getStyle())
			{
				m_pRadioButton->UpdateFromStyle(m_pRadioButton->getStyle());
				if (m_pRadioButton->m_pCanvas)
					m_pRadioButton->m_pCanvas->setValid(false);
			}
		}

		void CRadioButtonService::NotifyOnFontChange()
		{
			m_pRadioButton->UpdateAutoSize();
			if (m_pRadioButton->m_pCanvas)
				m_pRadioButton->m_pCanvas->setValid(false);
		}

		void CRadioButtonService::NotifyOnResize()
		{
			if (m_pRadioButton->m_pCanvas)
				m_pRadioButton->m_pCanvas->setValid(false);
		}

		void CRadioButtonService::NotifyOnEnable()
		{
			if (m_pRadioButton->m_pCanvas)
				m_pRadioButton->m_pCanvas->setValid(false);
		}

		void CRadioButtonService::NotifyOnDisable()
		{
			if (m_pRadioButton->m_pCanvas)
				m_pRadioButton->m_pCanvas->setValid(false);
		}

		void CRadioButtonService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pRadioButton->m_pCanvas)
				m_pRadioButton->m_pCanvas->setValid(false);
			m_pRadioButton->Repaint(false);
		}

		void CRadioButtonService::NotifyOnKillFocus()
		{
			if (m_pRadioButton->m_pCanvas)
				m_pRadioButton->m_pCanvas->setValid(false);
			m_pRadioButton->Repaint(false);
		}

		void CRadioButtonService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pRadioButton->m_pCanvas)
				m_pRadioButton->m_pCanvas->setValid(false);
			m_pRadioButton->Repaint(false);
		}

		void CRadioButtonService::NotifyOnMouseLeave()
		{
			if (m_pRadioButton->m_pCanvas)
				m_pRadioButton->m_pCanvas->setValid(false);
			m_pRadioButton->Repaint(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CRadioButtonService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pRadioButton->getWidth(), 0) && ntl::IsGreater<float>(m_pRadioButton->getHeight(), 0))
				m_pRadioButton->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CRadioButtonService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m.Key == Key::Space && m_pRadioButton->isEnabled(true))
				if (m_pRadioButton->setChecked(true) && m_pRadioButton->OnChange)
					m_pRadioButton->OnChange(m_pRadioButton);
		}

		void CRadioButtonService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pRadioButton->isEnabled(true) && !m_pRadioButton->m_bMouseDown && m.Left && !m.Middle && !m.Right)
			{
				m_pRadioButton->m_bMouseDown = true;
				m_pRadioButton->getForm()->CaptureMouse(m_pRadioButton, true);
				if (m_pRadioButton->m_pCanvas)
					m_pRadioButton->m_pCanvas->setValid(false);
				m_pRadioButton->Repaint(false);
			}
			else
				CancelMouseDown();
		}

		void CRadioButtonService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pRadioButton->isEnabled(true) && m_pRadioButton->m_bMouseDown && m.Left && !m.Middle && !m.Right && m_pRadioButton->isHovered())
			{
				CancelMouseDown();
				if (m_pRadioButton->setChecked(true) && m_pRadioButton->OnChange)
					m_pRadioButton->OnChange(m_pRadioButton);
			}
			else
				CancelMouseDown();
		}

		void CRadioButtonService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CRadioButtonService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CRadioButtonService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CRadioButtonService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CRadioButtonService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CRadioButtonService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CRadioButtonService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}
	#pragma endregion
	}
}