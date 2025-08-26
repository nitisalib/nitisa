// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Helpers
	CBuiltInDropDown::ElementType CBuiltInDropDown::getElement(const PointF &position)
	{
		if (m_bEditable || m_bLoopActiveItemOnDoubleClick)
		{
			RectF client{ getClientRect() };
			if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
				return ElementType::Input;
			client = getArrowAreaRect();
			if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
				return ElementType::Arrow;
		}
		else
		{
			RectF client{ 0, 0, getWidth(), getHeight() };
			if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
				return ElementType::Arrow;
		}
		if (m_bOpened && position.X >= m_sListRect.Left && position.X < m_sListRect.Right && position.Y >= m_sListRect.Top && position.Y < m_sListRect.Bottom)
		{
			if (ntl::IsGreater<float>(m_fListScrollMax, 0))
			{
				RectF client{
					m_sListRect.Right - m_sListBorderWidth.Right - m_sListPadding.Right - getScroll()->getSize().X,
					m_sListRect.Top + m_sListBorderWidth.Top + m_sListPadding.Top,
					m_sListRect.Right - m_sListBorderWidth.Right - m_sListPadding.Right,
					m_sListRect.Bottom - m_sListBorderWidth.Bottom - m_sListPadding.Bottom
				};
				if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
					return ElementType::ListScroll;
			}
			return ElementType::List;
		}
		return ElementType::None;
	}

	PointF CBuiltInDropDown::LocalToInput(const PointF &position)
	{
		RectF client{ getClientRect() };
		return PointF{ position.X - client.Left, position.Y - client.Top };
	}

	PointF CBuiltInDropDown::LocalToScroll(const PointF &position)
	{
		return PointF{
			position.X - (m_sListRect.Right - m_sListBorderWidth.Right - getScroll()->getSize().X),
			position.Y - (m_sListRect.Top + m_sListBorderWidth.Top) };
	}

	bool CBuiltInDropDown::UpdateHoveredItem()
	{
		return UpdateHoveredItem(getMousePosition());
	}

	bool CBuiltInDropDown::UpdateHoveredItem(const PointF &position)
	{
		if (!m_bOpened)
			return false;
		SortItems();
		// Find new hovered items
		IListItem *hovered{ nullptr };
		if (m_bOpened)
			hovered = getItem(position);
		// Change hovered item
		bool result{ false };
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if (*pos == hovered)
			{
				if (!hovered->isHovered())
				{
					hovered->QueryService()->setHovered(true);
					result = true;
				}
			}
			else if ((*pos)->isHovered())
			{
				(*pos)->QueryService()->setHovered(false);
				result = true;
			}
		return result;
	}
#pragma endregion

#pragma region Process keys
	bool CBuiltInDropDown::ProcessKeyUp()
	{
		if (m_aItems.size() > 0)
		{
			int new_index{ m_iActiveIndex > 0 ? (m_iActiveIndex - 1) : ((int)m_aItems.size() - 1) };
			while (new_index >= 0 && !m_aItems[new_index]->isEnabled())
				new_index--;
			if (new_index >= 0 && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index))
				{
					IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pListener) };
					if (listener)
						listener->NotifyOnSelect(this, m_iActiveIndex);
				}
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInDropDown::ProcessKeyDown()
	{
		if (m_aItems.size() > 0)
		{
			int new_index{ m_iActiveIndex < ((int)m_aItems.size() - 1) ? (m_iActiveIndex + 1) : 0 };
			while (new_index < (int)m_aItems.size() && !m_aItems[new_index]->isEnabled())
				new_index++;
			if (new_index < (int)m_aItems.size() && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index))
				{
					IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pListener) };
					if (listener)
						listener->NotifyOnSelect(this, m_iActiveIndex);
				}
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInDropDown::ProcessKeyPageUp()
	{
		if (m_aItems.size() > 0 && m_bOpened)
		{
			float item_height{ m_aItems[0]->getSize().Y };
			int count{ ntl::Round<int>((m_sListRect.height() - m_sListBorderWidth.Top - m_sListBorderWidth.Bottom - m_sListPadding.Top - m_sListPadding.Bottom) / item_height) };
			if (count == 0)
				count++;
			int new_index{ m_iActiveIndex >= 0 ? ntl::Max<int>(0, m_iActiveIndex - count) : ((int)m_aItems.size() - 1) };
			while (new_index >= 0 && !m_aItems[new_index]->isEnabled())
				new_index--;
			if (new_index < 0)
			{
				new_index = 0;
				while (new_index < (int)m_aItems.size() && (m_iActiveIndex < 0 || new_index < m_iActiveIndex) && !m_aItems[new_index]->isEnabled())
					new_index++;
			}
			if (new_index >= 0 && new_index < (int)m_aItems.size() && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index))
				{
					IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pListener) };
					if (listener)
						listener->NotifyOnSelect(this, m_iActiveIndex);
				}
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInDropDown::ProcessKeyPageDown()
	{
		if (m_aItems.size() > 0 && m_bOpened)
		{
			float item_height{ m_aItems[0]->getSize().Y };
			int count{ ntl::Round<int>((m_sListRect.height() - m_sListBorderWidth.Top - m_sListBorderWidth.Bottom - m_sListPadding.Top - m_sListPadding.Bottom) / item_height) };
			if (count == 0)
				count++;
			int new_index{ m_iActiveIndex >= 0 ? ntl::Min<int>((int)m_aItems.size() - 1, m_iActiveIndex + count) : 0 };
			while (new_index < (int)m_aItems.size() && !m_aItems[new_index]->isEnabled())
				new_index++;
			if (new_index >= (int)m_aItems.size())
			{
				new_index = (int)m_aItems.size() - 1;
				while (new_index >= 0 && (m_iActiveIndex < 0 || new_index > m_iActiveIndex) && !m_aItems[new_index]->isEnabled())
					new_index--;
			}
			if (new_index >= 0 && new_index < (int)m_aItems.size() && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index))
				{
					IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pListener) };
					if (listener)
						listener->NotifyOnSelect(this, m_iActiveIndex);
				}
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInDropDown::ProcessKeyHome()
	{
		if (m_aItems.size() > 0 && m_bOpened)
		{
			int new_index{ 0 };
			while (new_index < (int)m_aItems.size() && (m_iActiveIndex < 0 || new_index < m_iActiveIndex) && !m_aItems[new_index]->isEnabled())
				new_index++;
			if (new_index < (int)m_aItems.size() && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index))
				{
					IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pListener) };
					if (listener)
						listener->NotifyOnSelect(this, m_iActiveIndex);
				}
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInDropDown::ProcessKeyEnd()
	{
		if (m_aItems.size() > 0 && m_bOpened)
		{
			int new_index{ (int)m_aItems.size() - 1 };
			while (new_index >= 0 && (m_iActiveIndex < 0 || new_index > m_iActiveIndex) && !m_aItems[new_index]->isEnabled())
				new_index--;
			if (new_index >= 0 && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index))
				{
					IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pListener) };
					if (listener)
						listener->NotifyOnSelect(this, m_iActiveIndex);
				}
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}
#pragma endregion

#pragma region State change notifications
	void CBuiltInDropDown::NotifyOnFreeResources()
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

	void CBuiltInDropDown::NotifyOnAttach()
	{
		if (m_pTextInput)
			m_pTextInput->NotifyOnAttach();
		if (m_pScroll)
			m_pScroll->NotifyOnAttach();
	}

	void CBuiltInDropDown::NotifyOnDeactivate()
	{
		Close();
	}
#pragma endregion

#pragma region Mouse input notifications
	bool CBuiltInDropDown::NotifyOnMouseHover(const PointF &position)
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

	bool CBuiltInDropDown::NotifyOnMouseLeave()
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

	bool CBuiltInDropDown::NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
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

	bool CBuiltInDropDown::NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
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
				result = m_bOpened ? Close() : Open();
				break;
			case ElementType::List:
				m_eDownElement = ElementType::List;
				break;
			case ElementType::None:
				result = Close() || result;
				break;
			}
		}
		else
		{
			NotifyOnMouseDownCancel();
			result = Close() || result;
		}
		return result;
	}

	bool CBuiltInDropDown::NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
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
						result = true;
						IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pListener) };
						if (listener)
							listener->NotifyOnSelect(this, m_iActiveIndex);
					}
				result = Close() || result;
			}
			break;
			default:
				break;
			}
			m_eDownElement = ElementType::None;
		}
		else
		{
			NotifyOnMouseDownCancel();
			result = Close() || result;
		}
		return result;
	}

	bool CBuiltInDropDown::NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		bool result{ false };
		if (isEnabled() && !middle && !right && m_eHoveredElement == ElementType::Input)
		{
			if (m_bEditable)
				result = getTextInput()->NotifyOnMouseLeftDoubleClick(LocalToInput(position), middle, right, ctrl, alt, shift);
			else if (m_bLoopActiveItemOnDoubleClick && m_aItems.size() > 0)
			{
				result = setActiveIndex((m_iActiveIndex < 0) ? 0 : ((m_iActiveIndex + 1) % (int)m_aItems.size()));
				if (result)
				{
					IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pListener) };
					if (listener)
						listener->NotifyOnSelect(this, m_iActiveIndex);
				}
			}
		}
		NotifyOnMouseDownCancel();
		result = Close() | result;
		return result;
	}

	bool CBuiltInDropDown::NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return Close();
	}

	bool CBuiltInDropDown::NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return Close();
	}

	bool CBuiltInDropDown::NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return Close();
	}

	bool CBuiltInDropDown::NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return Close();
	}

	bool CBuiltInDropDown::NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return Close();
	}

	bool CBuiltInDropDown::NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return Close();
	}

	void CBuiltInDropDown::NotifyOnMouseDownCancel()
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

	bool CBuiltInDropDown::NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		bool result{ false };
		if (isEnabled())
		{
			if (m_bOpened && ntl::IsGreater<float>(m_fListScrollMax, 0))
			{
				if (getScroll()->setScroll(getScroll()->getScroll() + getScroll()->getDeltaMedium() * (delta > 0 ? -1 : 1)))
				{
					m_fListScroll = getScroll()->getScroll();
					UpdateHoveredItem();
					if (m_pCanvasList)
						m_pCanvasList->setValid(false);
					result = true;
				}
			}
			else
				if (m_aItems.size() > 0)
				{
					int new_index;
					if (delta < 0)
					{
						new_index = m_iActiveIndex < ((int)m_aItems.size() - 1) ? (m_iActiveIndex + 1) : m_iActiveIndex;
						while (new_index < (int)m_aItems.size() && !m_aItems[new_index]->isEnabled())
							new_index++;
					}
					else
					{
						new_index = m_iActiveIndex > 0 ? (m_iActiveIndex - 1) : (m_iActiveIndex < 0 ? ((int)m_aItems.size() - 1) : 0);
						while (new_index >= 0 && !m_aItems[new_index]->isEnabled())
							new_index--;
					}
					if (new_index >= 0 && new_index < (int)m_aItems.size() && new_index != m_iActiveIndex && setActiveIndex(new_index))
					{
						IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pListener) };
						if (listener)
							listener->NotifyOnSelect(this, m_iActiveIndex);
						ScrollToActiveItem();
						UpdateHoveredItem();
						result = true;
					}
				}
		}
		return result;
	}

	bool CBuiltInDropDown::NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		return false;
	}
#pragma endregion

#pragma region Keyboard input notifications
	bool CBuiltInDropDown::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
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
		String old_text{ getTextInput()->getText() };
		if (!processed && m_bEditable && getTextInput()->NotifyOnKeyDown(key, ctrl, alt, shift, numlock))
		{
			getTextInput()->ScrollToCaret();
			if (getTextInput()->getText() != old_text && m_iActiveIndex >= 0)
			{
				QueryListItemOwner()->setIgnoreActivate(true);
				m_aItems[m_iActiveIndex]->setActive(false);
				QueryListItemOwner()->setIgnoreActivate(false);
				m_iActiveIndex = -1;
			}
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
				result = Close() || result;
				break;
			case Key::F4:
				result = (m_bOpened ? Close() : Open()) || result;
				break;
			default:
				break;
			}
		}
		return result;
	}

	bool CBuiltInDropDown::NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		String old_text{ getTextInput()->getText() };
		if (m_bEditable && getTextInput()->NotifyOnKeyUp(key, ctrl, alt, shift, numlock))
		{
			getTextInput()->ScrollToCaret();
			if (getTextInput()->getText() != old_text && m_iActiveIndex >= 0)
			{
				QueryListItemOwner()->setIgnoreActivate(true);
				m_aItems[m_iActiveIndex]->setActive(false);
				QueryListItemOwner()->setIgnoreActivate(false);
				m_iActiveIndex = -1;
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		if (m_bEditable && getTextInput()->NotifyOnChar(chr, ctrl, alt, shift, numlock))
		{
			getTextInput()->ScrollToCaret();
			if (m_iActiveIndex >= 0)
			{
				QueryListItemOwner()->setIgnoreActivate(true);
				m_aItems[m_iActiveIndex]->setActive(false);
				QueryListItemOwner()->setIgnoreActivate(false);
				m_iActiveIndex = -1;
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		if (!m_bEditable && m_fSearch)
		{
			std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_sLastSearch) };
			if ((float)duration.count() * 0.001f > m_fSearchResetInterval)
				m_sSearch.clear();
			m_sLastSearch = std::chrono::steady_clock::now();
			m_sSearch += chr;
			int index{ m_fSearch(this, ToLower(m_sSearch)) };
			if (index >= 0 && index != m_iActiveIndex && m_aItems[index]->isEnabled())
			{
				if (setActiveIndex(index))
				{
					IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pListener) };
					if (listener)
						listener->NotifyOnSelect(this, m_iActiveIndex);
				}
				if (m_bOpened)
					ScrollToActiveItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInDropDown::NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		String old_text{ getTextInput()->getText() };
		if (m_bEditable && getTextInput()->NotifyOnDeadChar(chr, ctrl, alt, shift, numlock))
		{
			getTextInput()->ScrollToCaret();
			if (getTextInput()->getText() != old_text && m_iActiveIndex >= 0)
			{
				QueryListItemOwner()->setIgnoreActivate(true);
				m_aItems[m_iActiveIndex]->setActive(false);
				QueryListItemOwner()->setIgnoreActivate(false);
				m_iActiveIndex = -1;
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Other input notifications
	bool CBuiltInDropDown::NotifyOnDropFiles(const PointF &position, const StringArray &filenames)
	{
		return false;
	}
#pragma endregion

#pragma region Clipboard notifications
	bool CBuiltInDropDown::NotifyOnPasteString(const String &text)
	{
		if (m_bEditable && getTextInput()->NotifyOnPasteString(text))
		{
			getTextInput()->ScrollToCaret();
			if (m_iActiveIndex >= 0)
			{
				QueryListItemOwner()->setIgnoreActivate(true);
				m_aItems[m_iActiveIndex]->setActive(false);
				QueryListItemOwner()->setIgnoreActivate(false);
				m_iActiveIndex = -1;
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}
#pragma endregion
}