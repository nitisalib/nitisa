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
		CSpeedButtonService::CSpeedButtonService(CSpeedButton *speed_button) :
			CControlService(speed_button),
			m_pSpeedButton{ speed_button }
		{

		}
	#pragma endregion

	#pragma region Helpers
		bool CSpeedButtonService::UpdateImageList(IImageList *list)
		{
			if (list)
				for (int i = 0; i <= (int)CSpeedButton::State::Disabled; i++)
					if (m_pSpeedButton->m_aImageList[i] == list)
						return true;
			return false;
		}

		bool CSpeedButtonService::RemoveImageList(IImageList *list)
		{
			bool result{ false };
			if (list)
				for (int i = 0; i <= (int)CSpeedButton::State::Disabled; i++)
					if (m_pSpeedButton->m_aImageList[i] == list)
					{
						m_pSpeedButton->m_aImageList[i] = nullptr;
						result = true;
					}
			return result;
		}
	#pragma endregion

	#pragma region State change notifications
		void CSpeedButtonService::NotifyOnAttach()
		{
			if (m_pSpeedButton->m_bDown && m_pSpeedButton->m_iGroupIndex >= 0 && m_pSpeedButton->DownExists())
				m_pSpeedButton->m_bDown = false;
		}

		void CSpeedButtonService::NotifyOnFreeResources()
		{
			if (m_pSpeedButton->m_pCanvas)
			{
				m_pSpeedButton->m_pCanvas->Release();
				m_pSpeedButton->m_pCanvas = nullptr;
			}
		}
	#pragma endregion

	#pragma region Other components/controls/objects change notifications
		void CSpeedButtonService::NotifyOnComponentDetach(IComponent *component)
		{
			if (RemoveImageList(cast<IImageList*>(component)))
			{
				if (m_pSpeedButton->m_pCanvas)
					m_pSpeedButton->m_pCanvas->setValid(false);
				m_pSpeedButton->Repaint(false);
			}
		}

		void CSpeedButtonService::NotifyOnControlDetach(IControl *control)
		{
			if (RemoveImageList(cast<IImageList*>(control)))
			{
				if (m_pSpeedButton->m_pCanvas)
					m_pSpeedButton->m_pCanvas->setValid(false);
				m_pSpeedButton->Repaint(false);
			}
		}

		void CSpeedButtonService::NotifyOnComponentChange(IComponent *component)
		{
			if (UpdateImageList(cast<IImageList*>(component)))
			{
				if (m_pSpeedButton->m_pCanvas)
					m_pSpeedButton->m_pCanvas->setValid(false);
				m_pSpeedButton->Repaint(false);
			}
		}

		void CSpeedButtonService::NotifyOnControlChange(IControl *control)
		{
			if (UpdateImageList(cast<IImageList*>(control)))
			{
				if (m_pSpeedButton->m_pCanvas)
					m_pSpeedButton->m_pCanvas->setValid(false);
				m_pSpeedButton->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CSpeedButtonService::NotifyOnParentStyleChange()
		{
			if (m_pSpeedButton->getStyle())
			{
				m_pSpeedButton->UpdateFromStyle(m_pSpeedButton->getStyle());
				if (m_pSpeedButton->m_pCanvas)
					m_pSpeedButton->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CSpeedButtonService::NotifyOnResize()
		{
			if (m_pSpeedButton->m_pCanvas)
				m_pSpeedButton->m_pCanvas->setValid(false);
		}

		void CSpeedButtonService::NotifyOnEnable()
		{
			if (m_pSpeedButton->m_pCanvas)
				m_pSpeedButton->m_pCanvas->setValid(false);
		}

		void CSpeedButtonService::NotifyOnDisable()
		{
			if (m_pSpeedButton->m_pCanvas)
				m_pSpeedButton->m_pCanvas->setValid(false);
		}

		void CSpeedButtonService::NotifyOnStyleChange()
		{
			if (m_pSpeedButton->getStyle())
			{
				m_pSpeedButton->UpdateFromStyle(m_pSpeedButton->getStyle());
				if (m_pSpeedButton->m_pCanvas)
					m_pSpeedButton->m_pCanvas->setValid(false);
			}
		}

		void CSpeedButtonService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pSpeedButton->m_pCanvas)
				m_pSpeedButton->m_pCanvas->setValid(false);
			m_pSpeedButton->Repaint(false);
		}

		void CSpeedButtonService::NotifyOnKillFocus()
		{
			if (m_pSpeedButton->m_pCanvas)
				m_pSpeedButton->m_pCanvas->setValid(false);
			m_pSpeedButton->Repaint(false);
		}

		void CSpeedButtonService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pSpeedButton->m_pCanvas)
				m_pSpeedButton->m_pCanvas->setValid(false);
			m_pSpeedButton->Repaint(false);
		}

		void CSpeedButtonService::NotifyOnMouseLeave()
		{
			if (m_pSpeedButton->m_pCanvas)
				m_pSpeedButton->m_pCanvas->setValid(false);
			m_pSpeedButton->Repaint(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CSpeedButtonService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pSpeedButton->getWidth(), 0) && ntl::IsGreater<float>(m_pSpeedButton->getHeight(), 0))
				m_pSpeedButton->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CSpeedButtonService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if ((m.Key == Key::Space || m.Key == Key::Return || m.Key == Key::Separator) && !m_pSpeedButton->m_bDown)
				if (m_pSpeedButton->setDown(true) && m_pSpeedButton->OnDown)
					m_pSpeedButton->OnDown(m_pSpeedButton);
		}

		void CSpeedButtonService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pSpeedButton->isEnabled(true) && !m.Middle && !m.Right && !m_pSpeedButton->m_bDown)
				if (m_pSpeedButton->setDown(true) && m_pSpeedButton->OnDown)
					m_pSpeedButton->OnDown(m_pSpeedButton);
		}
	#pragma endregion
	}
}