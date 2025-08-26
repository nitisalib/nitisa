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
		CCheckBoxService::CCheckBoxService(CCheckBox *checkbox) :
			CControlService{ checkbox },
			m_pCheckBox{ checkbox }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CCheckBoxService::CancelMouseDown()
		{
			if (m_pCheckBox->isCaptureMouse())
				m_pCheckBox->getForm()->ReleaseCaptureMouse();
			if (m_pCheckBox->m_bMouseDown)
			{
				m_pCheckBox->m_bMouseDown = false;
				if (m_pCheckBox->m_pCanvas)
					m_pCheckBox->m_pCanvas->setValid(false);
				m_pCheckBox->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Setters
		bool CCheckBoxService::setChecked(const ICheckBox::CheckedState value)
		{
			if (value != m_pCheckBox->m_eChecked)
			{
				m_pCheckBox->m_eChecked = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CCheckBoxService::NotifyOnParentStyleChange()
		{
			if (m_pCheckBox->getStyle())
			{
				m_pCheckBox->UpdateFromStyle(m_pCheckBox->getStyle());
				if (m_pCheckBox->m_pCanvas)
					m_pCheckBox->m_pCanvas->setValid(false);
			}
		}

		void CCheckBoxService::NotifyOnParentFontChange()
		{
			m_pCheckBox->UpdateAutoSize();
			if (m_pCheckBox->m_pCanvas)
				m_pCheckBox->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CCheckBoxService::NotifyOnAttach()
		{
			if (m_pCheckBox->getForm())
			{
				if (!m_pCheckBox->m_bCaptionChanged)
					m_pCheckBox->setCaption(m_pCheckBox->m_sName);
				m_pCheckBox->UpdateAutoSize();
			}
		}

		void CCheckBoxService::NotifyOnFreeResources()
		{
			if (m_pCheckBox->m_pCanvas)
			{
				m_pCheckBox->m_pCanvas->Release();
				m_pCheckBox->m_pCanvas = nullptr;
			}
		}

		void CCheckBoxService::NotifyOnResize()
		{
			if (m_pCheckBox->m_pCanvas)
				m_pCheckBox->m_pCanvas->setValid(false);
		}

		void CCheckBoxService::NotifyOnStyleChange()
		{
			if (m_pCheckBox->getStyle())
			{
				m_pCheckBox->UpdateFromStyle(m_pCheckBox->getStyle());
				if (m_pCheckBox->m_pCanvas)
					m_pCheckBox->m_pCanvas->setValid(false);
			}
		}

		void CCheckBoxService::NotifyOnFontChange()
		{
			m_pCheckBox->UpdateAutoSize();
			if (m_pCheckBox->m_pCanvas)
				m_pCheckBox->m_pCanvas->setValid(false);
		}

		void CCheckBoxService::NotifyOnEnable()
		{
			if (m_pCheckBox->m_pCanvas)
				m_pCheckBox->m_pCanvas->setValid(false);
		}

		void CCheckBoxService::NotifyOnDisable()
		{
			if (m_pCheckBox->m_pCanvas)
				m_pCheckBox->m_pCanvas->setValid(false);
		}

		void CCheckBoxService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pCheckBox->m_pCanvas)
				m_pCheckBox->m_pCanvas->setValid(false);
			m_pCheckBox->Repaint(false);
		}

		void CCheckBoxService::NotifyOnKillFocus()
		{
			if (m_pCheckBox->m_pCanvas)
				m_pCheckBox->m_pCanvas->setValid(false);
			m_pCheckBox->Repaint(false);
		}

		void CCheckBoxService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pCheckBox->m_pCanvas)
				m_pCheckBox->m_pCanvas->setValid(false);
			m_pCheckBox->Repaint(false);
		}

		void CCheckBoxService::NotifyOnMouseLeave()
		{
			if (m_pCheckBox->m_pCanvas)
				m_pCheckBox->m_pCanvas->setValid(false);
			m_pCheckBox->Repaint(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CCheckBoxService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pCheckBox->getWidth(), 0) && ntl::IsGreater<float>(m_pCheckBox->getHeight(), 0))
				m_pCheckBox->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CCheckBoxService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m.Key == Key::Space && m_pCheckBox->isEnabled(true))
			{
				if (m_pCheckBox->m_eChecked == ICheckBox::CheckedState::Checked)
					m_pCheckBox->setChecked(ICheckBox::CheckedState::Unchecked);
				else
					m_pCheckBox->setChecked(ICheckBox::CheckedState::Checked);
				if (m_pCheckBox->OnChange)
					m_pCheckBox->OnChange(m_pCheckBox);
			}
		}

		void CCheckBoxService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pCheckBox->isEnabled(true) && !m_pCheckBox->m_bMouseDown && m.Left && !m.Middle && !m.Right)
			{
				m_pCheckBox->m_bMouseDown = true;
				m_pCheckBox->getForm()->CaptureMouse(m_pCheckBox, true);
				if (m_pCheckBox->m_pCanvas)
					m_pCheckBox->m_pCanvas->setValid(false);
				m_pCheckBox->Repaint(false);
			}
			else
				CancelMouseDown();
		}

		void CCheckBoxService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pCheckBox->isEnabled(true) && m_pCheckBox->m_bMouseDown && m.Left && !m.Middle && !m.Right && m_pCheckBox->isHovered())
			{
				CancelMouseDown();
				if (m_pCheckBox->m_eChecked == ICheckBox::CheckedState::Checked)
					m_pCheckBox->setChecked(ICheckBox::CheckedState::Unchecked);
				else
					m_pCheckBox->setChecked(ICheckBox::CheckedState::Checked);
				if (m_pCheckBox->OnChange)
					m_pCheckBox->OnChange(m_pCheckBox);
			}
			else
				CancelMouseDown();
		}

		void CCheckBoxService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CCheckBoxService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CCheckBoxService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CCheckBoxService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CCheckBoxService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CCheckBoxService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CCheckBoxService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}
	#pragma endregion
	}
}