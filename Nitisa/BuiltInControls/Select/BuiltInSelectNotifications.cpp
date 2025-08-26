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
#pragma region State change notifications
	void CBuiltInSelect::NotifyOnFreeResources()
	{
		if (m_pCanvasControl)
		{
			m_pCanvasControl->Release();
			m_pCanvasControl = nullptr;
		}
		if (m_pCanvasList)
		{
			m_pCanvasList->Release();
			m_pCanvasList = nullptr;
		}
		NotifyOnMouseDownCancel();
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			(*pos)->QueryService()->NotifyOnFreeResources();
		if (m_pTextInput)
			m_pTextInput->NotifyOnFreeResources();
		if (m_pScroll)
			m_pScroll->NotifyOnFreeResources();
	}

	void CBuiltInSelect::NotifyOnAttach()
	{
		if (m_pTextInput)
			m_pTextInput->NotifyOnAttach();
		if (m_pScroll)
			m_pScroll->NotifyOnAttach();
	}

	void CBuiltInSelect::NotifyOnDeactivate()
	{
		if (Close() && m_pSelectListener)
			m_pSelectListener->NotifyOnClose(this);
	}
#pragma endregion

#pragma region Mouse input notifications
	bool CBuiltInSelect::NotifyOnMouseHover(const PointF &position)
	{
		ElementType el{ getElement(position) };
		if (el != m_eHoveredElement)
		{
			switch (m_eHoveredElement)
			{
			case ElementType::Input:
				getTextInput()->NotifyOnMouseLeave();
				break;
			case ElementType::ListScroll:
				getScroll()->NotifyOnMouseLeave();
				break;
			default:
				break;
			}
		}
		m_eHoveredElement = el;
		switch (m_eHoveredElement)
		{
		case ElementType::Input:
			getTextInput()->NotifyOnMouseHover(LocalToInput(position));
			break;
		case ElementType::ListScroll:
			getScroll()->NotifyOnMouseHover(LocalToScroll(position));
			break;
		default:
			break;
		}
		UpdateHoveredItem(position);
		if (m_pCanvasControl)
			m_pCanvasControl->setValid(false);
		if (m_pCanvasList)
			m_pCanvasList->setValid(false);
		return true;
	}

	bool CBuiltInSelect::NotifyOnMouseLeave()
	{
		switch (m_eHoveredElement)
		{
		case ElementType::Input:
			getTextInput()->NotifyOnMouseLeave();
			break;
		case ElementType::ListScroll:
			getScroll()->NotifyOnMouseLeave();
			break;
		default:
			break;
		}
		m_eHoveredElement = ElementType::None;
		UpdateHoveredItem();
		if (m_pCanvasControl)
			m_pCanvasControl->setValid(false);
		if (m_pCanvasList)
			m_pCanvasList->setValid(false);
		return true;
	}

	bool CBuiltInSelect::NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		bool result{ false };
		ElementType el{ getElement(position) };
		if (el != m_eHoveredElement)
		{
			switch (m_eHoveredElement)
			{
			case ElementType::Input:
				if (getTextInput()->NotifyOnMouseLeave())
				{
					if (m_pCanvasControl)
						m_pCanvasControl->setValid(false);
					result = true;
				}
				break;
			case ElementType::ListScroll:
				if (getScroll()->NotifyOnMouseLeave())
				{
					if (m_pCanvasList)
						m_pCanvasList->setValid(false);
					result = true;
				}
				break;
			default:
				break;
			}
			m_eHoveredElement = el;
			switch (m_eHoveredElement)
			{
			case ElementType::Input:
				if (getTextInput()->NotifyOnMouseHover(LocalToInput(position)))
				{
					if (m_pCanvasControl)
						m_pCanvasControl->setValid(false);
					result = true;
				}
				break;
			case ElementType::ListScroll:
				if (getScroll()->NotifyOnMouseHover(LocalToScroll(position)))
				{
					if (m_pCanvasList)
						m_pCanvasList->setValid(false);
					result = true;
				}
				break;
			default:
				break;
			}
		}
		switch (m_eDownElement)
		{
		case ElementType::Input:
			if (getTextInput()->NotifyOnMouseMove(LocalToInput(position), left, middle, right, ctrl, alt, shift))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvasControl)
					m_pCanvasControl->setValid(false);
				result = true;
			}
			break;
		case ElementType::ListScroll:
			if (getScroll()->NotifyOnMouseMove(LocalToScroll(position), left, middle, right, ctrl, alt, shift))
			{
				m_fListScroll = getScroll()->getScroll();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
				result = true;
			}
			break;
		default:
			switch (m_eHoveredElement)
			{
			case ElementType::Input:
				if (getTextInput()->NotifyOnMouseMove(LocalToInput(position), left, middle, right, ctrl, alt, shift))
				{
					if (m_pCanvasControl)
						m_pCanvasControl->setValid(false);
					result = true;
				}
				break;
			case ElementType::ListScroll:
				if (getScroll()->NotifyOnMouseMove(LocalToScroll(position), left, middle, right, ctrl, alt, shift))
				{
					if (m_pCanvasList)
						m_pCanvasList->setValid(false);
					result = true;
				}
				break;
			default:
				break;
			}
		}
		if (UpdateHoveredItem(position))
		{
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			result = true;
		}
		return result;
	}

	bool CBuiltInSelect::NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		bool result{ false };
		if (isEnabled() && !middle && !right && m_eDownElement == ElementType::None)
		{
			switch (m_eHoveredElement)
			{
			case ElementType::Input:
				if (getTextInput()->NotifyOnMouseLeftDown(LocalToInput(position), false, false, ctrl, alt, shift))
				{
					if (m_pCanvasControl)
						m_pCanvasControl->setValid(false);
					result = true;
				}
				m_eDownElement = ElementType::Input;
				break;
			case ElementType::ListScroll:
				if (getScroll()->NotifyOnMouseLeftDown(LocalToScroll(position), false, false, ctrl, alt, shift))
				{
					m_fListScroll = getScroll()->getScroll();
					if (m_pCanvasList)
						m_pCanvasList->setValid(false);
					m_eDownElement = ElementType::ListScroll;
					result = true;
				}
				break;
			case ElementType::Arrow:
				if (m_bOpened)
				{
					if (Close())
					{
						if (m_pSelectListener)
							m_pSelectListener->NotifyOnClose(this);
						result = true;
					}
				}
				else
				{
					if (Open())
					{
						if (m_pSelectListener)
							m_pSelectListener->NotifyOnOpen(this);
						result = true;
					}
				}
				break;
			case ElementType::List:
				m_eDownElement = ElementType::List;
				break;
			case ElementType::None:
				if (Close())
				{
					if (m_pSelectListener)
						m_pSelectListener->NotifyOnClose(this);
					result = true;
				}
				break;
			}
		}
		else
		{
			NotifyOnMouseDownCancel();
			if (Close())
			{
				if (m_pSelectListener)
					m_pSelectListener->NotifyOnClose(this);
				result = true;
			}
		}
		return result;
	}

	bool CBuiltInSelect::NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		bool result{ false };
		if (isEnabled() && !middle && !right)
		{
			switch (m_eDownElement)
			{
			case ElementType::Input:
				if (getTextInput()->NotifyOnMouseLeftUp(LocalToInput(position), false, false, ctrl, alt, shift))
				{
					if (m_pCanvasControl)
						m_pCanvasControl->setValid(false);
					result = true;
				}
				break;
			case ElementType::ListScroll:
				if (getScroll()->NotifyOnMouseLeftUp(LocalToScroll(position), false, false, ctrl, alt, shift))
				{
					m_fListScroll = getScroll()->getScroll();
					if (m_pCanvasList)
						m_pCanvasList->setValid(false);
					result = true;
				}
				break;
			case ElementType::List:
			{
				IListItem *item{ getItem(position) };
				if (item && item->isEnabled() && !item->isActive())
					if (setActiveIndex(getItemIndex(item)))
					{
						if (m_pSelectListener)
							m_pSelectListener->NotifyOnSelect(this, m_iActiveIndex);
						result = true;
					}
				if (Close())
				{
					if (m_pSelectListener)
						m_pSelectListener->NotifyOnClose(this);
					result = true;
				}
				break;
			}
			default:
				break;
			}
			m_eDownElement = ElementType::None;
		}
		else
		{
			NotifyOnMouseDownCancel();
			if (Close())
			{
				if (m_pSelectListener)
					m_pSelectListener->NotifyOnClose(this);
				result = true;
			}
		}
		return result;
	}

	bool CBuiltInSelect::NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		bool result{ false };
		if (isEnabled() && !middle && !right && m_eHoveredElement == ElementType::Input && m_bOpened)
			result = getTextInput()->NotifyOnMouseLeftDoubleClick(LocalToInput(position), middle, right, ctrl, alt, shift);
		NotifyOnMouseDownCancel();
		if (Close())
		{
			if (m_pSelectListener)
				m_pSelectListener->NotifyOnClose(this);
			result = true;
		}
		return result;
	}

	bool CBuiltInSelect::NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		if (Close())
		{
			if (m_pSelectListener)
				m_pSelectListener->NotifyOnClose(this);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		if (Close())
		{
			if (m_pSelectListener)
				m_pSelectListener->NotifyOnClose(this);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		if (Close())
		{
			if (m_pSelectListener)
				m_pSelectListener->NotifyOnClose(this);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		if (Close())
		{
			if (m_pSelectListener)
				m_pSelectListener->NotifyOnClose(this);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		if (Close())
		{
			if (m_pSelectListener)
				m_pSelectListener->NotifyOnClose(this);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		if (Close())
		{
			if (m_pSelectListener)
				m_pSelectListener->NotifyOnClose(this);
			return true;
		}
		return false;
	}

	void CBuiltInSelect::NotifyOnMouseDownCancel()
	{
		if (m_eDownElement != ElementType::None)
		{
			switch (m_eDownElement)
			{
			case ElementType::Input:
				getTextInput()->NotifyOnMouseDownCancel();
				break;
			case ElementType::ListScroll:
				getScroll()->NotifyOnMouseDownCancel();
				break;
			default:
				break;
			}
			m_eDownElement = ElementType::None;
		}
	}

	bool CBuiltInSelect::NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		bool result{ false };
		if (isEnabled() && m_bOpened && ntl::IsGreater<float>(m_fListScrollMax, 0) && getScroll()->setScroll(getScroll()->getScroll() + getScroll()->getDeltaMedium() * (delta > 0 ? -1 : 1)))
		{
			m_fListScroll = getScroll()->getScroll();
			UpdateHoveredItem();
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			result = true;
		}
		return result;
	}

	bool CBuiltInSelect::NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		return false;
	}
#pragma endregion

#pragma region Keyboard input notifications
	bool CBuiltInSelect::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		bool processed{ false }, result{ false };
		if (m_bOpened && !ctrl && !alt && !shift && ((key == Key::Home || (key == Key::Numpad7 && !numlock)) || (key == Key::End || (key == Key::Numpad1 && !numlock))))
		{
			switch (key)
			{
			case Key::Home:
			case Key::Numpad7:
				result = ProcessKeyHome() || result;
				break;
			case Key::End:
			case Key::Numpad1:
				result = ProcessKeyEnd() || result;
				break;
			default:
				break;
			}
			processed = true;
		}
		if (!processed && m_bOpened && getTextInput()->NotifyOnKeyDown(key, ctrl, alt, shift, numlock))
		{
			getTextInput()->ScrollToCaret();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			result = true;
		}
		else if (!processed && !ctrl && !alt && !shift)
		{
			switch (key)
			{
			case Key::Up:
			case Key::Numpad8:
				if (key == Key::Up || (key == Key::Numpad8 && !numlock))
					result = ProcessKeyUp() || result;
				break;
			case Key::Down:
			case Key::Numpad2:
				if (key == Key::Down || (key == Key::Numpad2 && !numlock))
					result = ProcessKeyDown() || result;
				break;
			case Key::Prior:
			case Key::Numpad9:
				if (key == Key::Prior || (key == Key::Numpad9 && !numlock))
					result = ProcessKeyPageUp() || result;
				break;
			case Key::Next:
			case Key::Numpad3:
				if (key == Key::Next || (key == Key::Numpad3 && !numlock))
					result = ProcessKeyPageDown() || result;
				break;
			case Key::Home:
			case Key::Numpad7:
				if (key == Key::Home || (key == Key::Numpad7 && !numlock))
					result = ProcessKeyHome() || result;
				break;
			case Key::End:
			case Key::Numpad1:
				if (key == Key::End || (key == Key::Numpad1 && !numlock))
					result = ProcessKeyEnd() || result;
				break;
			case Key::Return:
			case Key::Separator:
			case Key::Escape:
				if (Close())
				{
					if (m_pSelectListener)
						m_pSelectListener->NotifyOnClose(this);
					result = true;
				}
				break;
			case Key::F4:
				if (m_bOpened)
				{
					if (Close())
					{
						if (m_pSelectListener)
							m_pSelectListener->NotifyOnClose(this);
						result = true;
					}
				}
				else
				{
					if (Open())
					{
						if (m_pSelectListener)
							m_pSelectListener->NotifyOnOpen(this);
						result = true;
					}
				}
				break;
			default:
				break;
			}
		}
		return result;
	}

	bool CBuiltInSelect::NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		if (m_bOpened && getTextInput()->NotifyOnKeyUp(key, ctrl, alt, shift, numlock))
		{
			getTextInput()->ScrollToCaret();
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		if (m_bOpened && getTextInput()->NotifyOnChar(chr, ctrl, alt, shift, numlock))
		{
			getTextInput()->ScrollToCaret();
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		if (m_bOpened && getTextInput()->NotifyOnDeadChar(chr, ctrl, alt, shift, numlock))
		{
			getTextInput()->ScrollToCaret();
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Other input notifications
	bool CBuiltInSelect::NotifyOnDropFiles(const PointF &position, const StringArray &filenames)
	{
		return false;
	}
#pragma endregion

#pragma region Clipboard notifications
	bool CBuiltInSelect::NotifyOnPasteString(const String &text)
	{
		if (m_bOpened && getTextInput()->NotifyOnPasteString(text))
		{
			getTextInput()->ScrollToCaret();
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}
#pragma endregion
}