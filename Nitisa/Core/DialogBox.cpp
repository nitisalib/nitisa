// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CDialogBox::CDialogBox(const String &class_name, const bool accept_form, const bool accept_control, const bool accept_focus, const bool tab_stop, const Point &design_dpi, IDialogBoxService *service) :
		CControl(class_name, accept_form, accept_control, true, accept_focus, true, tab_stop, design_dpi),
		m_eModalResult{ ModalResult::None },
		m_eWindowPosition{ WindowPosition::Custom },
		m_bTranslated{ false },
		m_pDialogBoxListener{ nullptr }
	{
		OnDestroy = nullptr;
		OnClose = nullptr;
		OnRestore = nullptr;
		OnMinimize = nullptr;
		OnMaximize = nullptr;
		OnSetActive = nullptr;
		OnKillActive = nullptr;
		if (service)
			setService(service, true);
	}

	void CDialogBox::BeforeRelease()
	{
		if (OnDestroy)
			OnDestroy(this);
		CControl::BeforeRelease();
	}
#pragma endregion

#pragma region IDialogBox getters
	IDialogBoxListener *CDialogBox::getDialogBoxListener()
	{
		return m_pDialogBoxListener;
	}

	Point CDialogBox::getClientSize()
	{
		RectF b{ getBorderWidth() };
		return Round(PointF{ ntl::Max<float>(0.0f, getWidth() - b.Left - b.Right), ntl::Max<float>(0.0f, getHeight() - b.Top - b.Bottom) });
	}

	int CDialogBox::getClientWidth()
	{
		RectF b{ getBorderWidth() };
		return ntl::Round<int>(ntl::Max<float>(0.0f, getWidth() - b.Left - b.Right));
	}

	int CDialogBox::getClientHeight()
	{
		RectF b{ getBorderWidth() };
		return ntl::Round<int>(ntl::Max<float>(0.0f, getHeight() - b.Top - b.Bottom));
	}

	WindowPosition CDialogBox::getWindowPosition()
	{
		return m_eWindowPosition;
	}

	ModalResult CDialogBox::getModalResult()
	{
		return m_eModalResult;
	}

	bool CDialogBox::isActiveDialogBox()
	{
		return getForm() && getForm()->getActiveDialogBox() == this;
	}

	bool CDialogBox::hasComponent(IComponent *component)
	{
		return false;
	}
#pragma endregion

#pragma region IDialogBox setters
	void CDialogBox::setDialogBoxListener(IDialogBoxListener *value)
	{
		m_pDialogBoxListener = value;
	}

	bool CDialogBox::setWindowPosition(const WindowPosition value)
	{
		if (value != m_eWindowPosition)
		{
			m_eWindowPosition = value;
			Translate();
			return true;
		}
		return false;
	}

	bool CDialogBox::setModalResult(const ModalResult value)
	{
		if (value != m_eModalResult)
		{
			m_eModalResult = value;
			return Close();
		}
		return false;
	}
#pragma endregion

#pragma region IDialogBox actions
	bool CDialogBox::Show()
	{
		CLockRepaint lock{ this };
		if (!isVisible(false))
			Restore();
		if (!m_bTranslated)
			Translate();
		if (getForm())
			return getForm()->setActiveDialogBox(this);
		return false;
	}

	bool CDialogBox::ShowModal()
	{
		CLockRepaint lock{ this };
		m_eModalResult = ModalResult::None;
		if (!isVisible(false))
			Restore();
		if (!m_bTranslated)
			Translate();
		if (getForm())
			return getForm()->setModalControl(this) && getForm()->setActiveDialogBox(this);
		return false;
	}

	bool CDialogBox::Close()
	{
		if (OnClose)
		{
			CloseAction action{ CloseAction::Hide };
			OnClose(this, action);
			switch (action)
			{
				case CloseAction::None:
					return false;
				case CloseAction::Free:
					if (m_pDialogBoxListener)
						m_pDialogBoxListener->OnClose(this);
					Release();
					return true;
				case CloseAction::Minimize:
					return Minimize();
				default:
					break;
			}
		}
		return Hide();
	}
#pragma endregion

#pragma region Helpers
	void CDialogBox::Translate()
	{
		if ((getParent() || getForm()) && m_eWindowPosition != WindowPosition::Custom && getState() == WindowState::Normal)
		{
			m_bTranslated = true;
			switch (m_eWindowPosition)
			{
			case WindowPosition::ScreenLeftTop:
			case WindowPosition::MainFormLeftTop:
				getTransform()->Translate(0, 0, 0);
				break;
			case WindowPosition::ScreenRightTop:
			case WindowPosition::MainFormRightTop:
				getTransform()->Translate((getParent() ? getParent()->getWidth() : (float)getForm()->getClientWidth()) - getWidth(), 0, 0);
				break;
			case WindowPosition::ScreenLeftBottom:
			case WindowPosition::MainFormLeftBottom:
				getTransform()->Translate(0, (getParent() ? getParent()->getHeight() : (float)getForm()->getClientHeight()) - getHeight(), 0);
				break;
			case WindowPosition::ScreenRightBottom:
			case WindowPosition::MainFormRightBottom:
				getTransform()->Translate(
					(getParent() ? getParent()->getWidth() : (float)getForm()->getClientWidth()) - getWidth(),
					(getParent() ? getParent()->getHeight() : (float)getForm()->getClientHeight()) - getHeight(),
					0);
				break;
			default:
				getTransform()->Translate(
					std::round(((getParent() ? getParent()->getWidth() : (float)getForm()->getClientWidth()) - getWidth()) / 2),
					std::round(((getParent() ? getParent()->getHeight() : (float)getForm()->getClientHeight()) - getHeight()) / 2),
					0);
			}
		}
	}
#pragma endregion
}