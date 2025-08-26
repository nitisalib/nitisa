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
		CCustomListBoxService::CCustomListBoxService(CCustomListBox *listbox) :
			CControlService(listbox),
			m_pListBox{ listbox },
			m_hTimer{ nullptr }
		{

		}
	#pragma endregion

	#pragma region Helpers
		PointF CCustomListBoxService::LocalToHScroll(const PointF &position)
		{
			return PointF{
				position.X - m_pListBox->m_sBorderWidth.Left,
				position.Y - (m_pListBox->getHeight() - m_pListBox->m_sBorderWidth.Bottom - m_pListBox->getHScroll()->getSize().Y)
			};
		}

		PointF CCustomListBoxService::LocalToVScroll(const PointF &position)
		{
			return PointF{
				position.X - (m_pListBox->getWidth() - m_pListBox->m_sBorderWidth.Right - m_pListBox->getVScroll()->getSize().X),
				position.Y - m_pListBox->m_sBorderWidth.Top };
		}

		PointF CCustomListBoxService::LocalToItem(const PointF &position, const int index)
		{
			PointF p{ m_pListBox->m_aItems[index]->getPosition() };
			if (m_pListBox->getHScroll()->isEnabled())
				p.X -= m_pListBox->getHScroll()->getScroll();
			if (m_pListBox->getVScroll()->isEnabled())
				p.Y -= m_pListBox->getVScroll()->getScroll();
			return PointF{ position.X - p.X, position.Y - p.Y };
		}

		CCustomListBoxService::Element CCustomListBoxService::getElement(const PointF &position)
		{
			if (position.X >= 0 && position.X < m_pListBox->getWidth() && position.Y >= 0 && position.Y < m_pListBox->getHeight())
			{
				if (m_pListBox->m_bHScroll)
				{
					RectF client{
						m_pListBox->m_sBorderWidth.Left,
						m_pListBox->getHeight() - m_pListBox->m_sBorderWidth.Bottom - m_pListBox->getHScroll()->getSize().Y,
						m_pListBox->m_sBorderWidth.Left + m_pListBox->getHScroll()->getSize().X,
						m_pListBox->getHeight() - m_pListBox->m_sBorderWidth.Bottom };
					if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
						return Element::HScroll;
				}
				if (m_pListBox->m_bVScroll)
				{
					RectF client{
						m_pListBox->getWidth() - m_pListBox->m_sBorderWidth.Right - m_pListBox->getVScroll()->getSize().X,
						m_pListBox->m_sBorderWidth.Top,
						m_pListBox->getWidth() - m_pListBox->m_sBorderWidth.Right,
						m_pListBox->m_sBorderWidth.Top + m_pListBox->getVScroll()->getSize().Y };
					if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
						return Element::VScroll;
				}
				RectF client{ m_pListBox->getRealClientRect() };
				if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
					return Element::List;
			}
			return Element::None;
		}

		bool CCustomListBoxService::SelectRange(int from, int to)
		{
			from = ntl::Max<int>(0, from);
			if (from > to)
				ntl::Swap<int>(from, to);
			m_pListBox->QueryListItemOwner()->setIgnoreSelect(true);
			int index{ 0 };
			bool result{ false };
			for (auto pos = m_pListBox->m_aItems.begin(); pos != m_pListBox->m_aItems.end(); pos++, index++)
				if ((!(*pos)->isEnabled() || index < from || index > to) && (*pos)->isSelected())
					result = (*pos)->setSelected(false) || result;
				else if ((*pos)->isEnabled() && index >= from && index <= to && !(*pos)->isSelected())
					result = (*pos)->setSelected(true) || result;
			m_pListBox->QueryListItemOwner()->setIgnoreSelect(false);
			return result;
		}

		bool CCustomListBoxService::InvertRange(int from, int to)
		{
			if (from > to)
			{
				ntl::Swap<int>(from, to);
				to--;
			}
			else
				from++;
			m_pListBox->QueryListItemOwner()->setIgnoreSelect(true);
			bool result{ false };
			for (int i = from; i <= to; i++)
				if (m_pListBox->m_aItems[i]->isEnabled())
					result = m_pListBox->m_aItems[i]->setSelected(!m_pListBox->m_aItems[i]->isSelected()) || result;
			m_pListBox->QueryListItemOwner()->setIgnoreSelect(false);
			return result;
		}

		void CCustomListBoxService::MouseUp()
		{
			if (m_pListBox->m_pDownItem)
			{
				m_pListBox->m_pDownItem->QueryService()->NotifyOnMouseDownCancel();
				m_pListBox->m_pDownItem = nullptr;
			}
			m_pListBox->m_eDownElement = Element::None;
			if (m_pListBox->isCaptureMouse())
				m_pListBox->getForm()->ReleaseCaptureMouse();
			if (m_hTimer)
			{
				m_pListBox->getForm()->DeleteTimer(m_hTimer);
				m_hTimer = nullptr;
			}
		}

		void CCustomListBoxService::ProcessMove(const PointF &position)
		{
			RectF client{ m_pListBox->getRealClientRect() };
			Point p{ m_pListBox->getGridCell(client, position) };
			// Scroll if required
			if (position.X < client.Left && m_pListBox->getHScroll()->isEnabled() && m_pListBox->getHScroll()->setScroll(m_pListBox->getHScroll()->getScroll() - m_pListBox->m_sItemSize.X))
			{
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
			if (position.X > client.Right && m_pListBox->getHScroll()->isEnabled() && m_pListBox->getHScroll()->setScroll(m_pListBox->getHScroll()->getScroll() + m_pListBox->m_sItemSize.X))
			{
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
			if (position.Y < client.Top && m_pListBox->getVScroll()->isEnabled() && m_pListBox->getVScroll()->setScroll(m_pListBox->getVScroll()->getScroll() - m_pListBox->m_sItemSize.Y))
			{
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
			if (position.Y > client.Bottom && m_pListBox->getVScroll()->isEnabled() && m_pListBox->getVScroll()->setScroll(m_pListBox->getVScroll()->getScroll() + m_pListBox->m_sItemSize.Y))
			{
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
			// Selection
			int index{ ntl::Clamp<int>(p.Y * m_pListBox->m_iColumns + p.X, 0, (int)m_pListBox->m_aItems.size() - 1) };
			if (m_pListBox->m_bMultiselect)
			{
				if (SelectRange(m_pListBox->m_iDownIndex, index))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
			}
			else
			{
				m_pListBox->m_iDownIndex = index;
				if (SelectRange(index, index))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
			}
			m_pListBox->setActiveIndex(index);
		}

		void CCustomListBoxService::PostKey(const int index, const bool shift)
		{
			if (m_pListBox->m_bMultiselect && shift && m_pListBox->m_iActiveIndex >= 0)
				SelectRange(m_pListBox->m_iDownIndex, index);
			else
			{
				SelectRange(index, index);
				m_pListBox->m_iDownIndex = index;
			}
			m_pListBox->setActiveIndex(index);
			m_pListBox->ScrollToItem(index);
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
			m_pListBox->Repaint(false);
		}

		bool CCustomListBoxService::MoveItem(IListItem *item, const int before)
		{
			return MoveListItem(m_pListBox->m_aItems, m_pListBox, item, before);
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomListBoxService::NotifyOnAttach()
		{
			if (m_pListBox->getForm())
			{
				if (m_pListBox->m_pHScroll)
					m_pListBox->m_pHScroll->NotifyOnAttach();
				if (m_pListBox->m_pVScroll)
					m_pListBox->m_pVScroll->NotifyOnAttach();
				m_pListBox->UpdateList();
				m_pListBox->UpdateHoveredItem();
			}
		}

		void CCustomListBoxService::NotifyOnDetaching()
		{
			MouseUp();
			if (m_pListBox->m_pHScroll)
				m_pListBox->m_pHScroll->NotifyOnMouseDownCancel();
			if (m_pListBox->m_pVScroll)
				m_pListBox->m_pVScroll->NotifyOnMouseDownCancel();
		}
	#pragma endregion

	#pragma region Other components/controls/objects change notifications
		void CCustomListBoxService::NotifyOnFreeResources()
		{
			if (m_pListBox->m_pHScroll)
				m_pListBox->m_pHScroll->NotifyOnFreeResources();
			if (m_pListBox->m_pVScroll)
				m_pListBox->m_pVScroll->NotifyOnFreeResources();
			for (auto pos = m_pListBox->m_aItems.begin(); pos != m_pListBox->m_aItems.end(); pos++)
				(*pos)->QueryService()->NotifyOnFreeResources();
			if (m_pListBox->m_pCanvas)
			{
				m_pListBox->m_pCanvas->Release();
				m_pListBox->m_pCanvas = nullptr;
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CCustomListBoxService::NotifyOnParentStyleChange()
		{
			if (m_pListBox->getStyle())
			{
				m_pListBox->UpdateFromStyle(m_pListBox->getStyle());
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
			}
		}

		void CCustomListBoxService::NotifyOnParentFontChange()
		{
			m_pListBox->UpdateList();
			m_pListBox->UpdateHoveredItem();
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomListBoxService::NotifyOnEnable()
		{
			m_pListBox->UpdateList();
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
		}

		void CCustomListBoxService::NotifyOnDisable()
		{
			MouseUp();
			m_pListBox->UpdateList();
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
		}

		void CCustomListBoxService::NotifyOnResize()
		{
			m_pListBox->UpdateList();
			m_pListBox->UpdateHoveredItem();
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
		}

		void CCustomListBoxService::NotifyOnStyleChange()
		{
			if (m_pListBox->getStyle())
			{
				m_pListBox->UpdateFromStyle(m_pListBox->getStyle());
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
			}
		}

		void CCustomListBoxService::NotifyOnFontChange()
		{
			m_pListBox->UpdateList();
			m_pListBox->UpdateHoveredItem();
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
		}

		void CCustomListBoxService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
			m_pListBox->Repaint(false);
		}

		void CCustomListBoxService::NotifyOnKillFocus()
		{
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
			m_pListBox->Repaint(false);
		}

		void CCustomListBoxService::NotifyOnMouseHover(const MessagePosition &m)
		{
			PointF position{ m_pListBox->FormToLocal(m.Position) };
			Element el{ getElement(position) };
			if (el != m_pListBox->m_eHoveredElement)
			{
				switch (m_pListBox->m_eHoveredElement)
				{
				case Element::HScroll:
					m_pListBox->getHScroll()->NotifyOnMouseLeave();
					break;
				case Element::VScroll:
					m_pListBox->getVScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
			}
			m_pListBox->m_eHoveredElement = el;
			switch (m_pListBox->m_eHoveredElement)
			{
			case Element::HScroll:
				m_pListBox->getHScroll()->NotifyOnMouseHover(LocalToHScroll(position));
				break;
			case Element::VScroll:
				m_pListBox->getVScroll()->NotifyOnMouseHover(LocalToVScroll(position));
				break;
			default:
				break;
			}
			m_pListBox->UpdateHoveredItem(position);
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
			m_pListBox->Repaint(false);
		}

		void CCustomListBoxService::NotifyOnMouseLeave()
		{
			if (m_pListBox->m_eHoveredElement != Element::None)
			{
				switch (m_pListBox->m_eHoveredElement)
				{
				case Element::HScroll:
					m_pListBox->getHScroll()->NotifyOnMouseLeave();
					break;
				case Element::VScroll:
					m_pListBox->getVScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_pListBox->m_eHoveredElement = Element::None;
			}
			m_pListBox->UpdateHoveredItem();
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
			m_pListBox->Repaint(false);
		}

		void CCustomListBoxService::NotifyOnKillCaptureMouse()
		{
			m_pListBox->m_eDownElement = Element::None;
			if (m_hTimer)
			{
				m_pListBox->getForm()->DeleteTimer(m_hTimer);
				m_hTimer = nullptr;
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CCustomListBoxService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pListBox->getWidth(), 0) && ntl::IsGreater<float>(m_pListBox->getHeight(), 0))
				m_pListBox->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CCustomListBoxService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			IListItem *item{ m_pListBox->getItem(m_pListBox->m_iActiveIndex) };
			if (item && item->QueryService()->NotifyOnKeyDown(m.Key, ctrl, alt, shift))
			{
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
			if (!alt)
			{
				switch (m.Key)
				{
				case Key::Up:
				case Key::Numpad8:
					if (!ctrl && (m.Key == Key::Up || (m.Key == Key::Numpad8 && !numlock)))
						ProcessKeyUp(shift);
					break;
				case Key::Down:
				case Key::Numpad2:
					if (!ctrl && (m.Key == Key::Down || (m.Key == Key::Numpad2 && !numlock)))
						ProcessKeyDown(shift);
					break;
				case Key::Prior:
				case Key::Numpad9:
					if (!ctrl && (m.Key == Key::Prior || (m.Key == Key::Numpad9 && !numlock)))
						ProcessKeyPageUp(shift);
					break;
				case Key::Next:
				case Key::Numpad3:
					if (!ctrl && (m.Key == Key::Next || (m.Key == Key::Numpad3 && !numlock)))
						ProcessKeyPageDown(shift);
					break;
				case Key::Home:
				case Key::Numpad7:
					if (m.Key == Key::Home || (m.Key == Key::Numpad7 && !numlock))
						ProcessKeyHome(ctrl, shift);
					break;
				case Key::End:
				case Key::Numpad1:
					if (m.Key == Key::End || (m.Key == Key::Numpad1 && !numlock))
						ProcessKeyEnd(ctrl, shift);
					break;
				case Key::Left:
				case Key::Numpad4:
					if (!ctrl && (m.Key == Key::Left || (m.Key == Key::Numpad4 && !numlock)))
						ProcessKeyLeft(shift);
					break;
				case Key::Right:
				case Key::Numpad6:
					if (!ctrl && (m.Key == Key::Right || (m.Key == Key::Numpad6 && !numlock)))
						ProcessKeyRight(shift);
					break;
				case Key::Space:
					ProcessKeySpace();
					break;
				case Key::A:
					if (ctrl)
						ProcessKeyA();
					break;
				default:
					break;
				}
			}
		}

		void CCustomListBoxService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			IListItem *item{ m_pListBox->getItem(m_pListBox->m_iActiveIndex) };
			if (item && item->QueryService()->NotifyOnKeyUp(m.Key, ctrl, alt, shift))
			{
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
		}

		void CCustomListBoxService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_pListBox->m_sLastSearch) };
			if ((float)duration.count() * 0.001f > m_pListBox->m_fSearchResetInterval)
				m_pListBox->m_sSearch.clear();
			m_pListBox->m_sLastSearch = std::chrono::steady_clock::now();
			m_pListBox->m_sSearch += m.Char;
			int index{ m_pListBox->Search(ToLower(m_pListBox->m_sSearch)) };
			if (index >= 0 && index != m_pListBox->m_iActiveIndex && m_pListBox->m_aItems[index]->isEnabled())
				PostKey(index, false);
		}

		void CCustomListBoxService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			PointF position{ m_pListBox->FormToLocal(m.Position) };
			Element el{ getElement(position) };
			if (el != m_pListBox->m_eHoveredElement)
			{
				switch (m_pListBox->m_eHoveredElement)
				{
				case Element::HScroll:
					m_pListBox->getHScroll()->NotifyOnMouseLeave();
					break;
				case Element::VScroll:
					m_pListBox->getVScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_pListBox->m_eHoveredElement = el;
				switch (m_pListBox->m_eHoveredElement)
				{
				case Element::HScroll:
					m_pListBox->getHScroll()->NotifyOnMouseHover(LocalToHScroll(position));
					break;
				case Element::VScroll:
					m_pListBox->getVScroll()->NotifyOnMouseHover(LocalToVScroll(position));
					break;
				default:
					break;
				}
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
			switch (m_pListBox->m_eDownElement)
			{
			case Element::HScroll:
				if (m_pListBox->getHScroll()->NotifyOnMouseMove(LocalToHScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
				break;
			case Element::VScroll:
				if (m_pListBox->getVScroll()->NotifyOnMouseMove(LocalToVScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
				break;
			case Element::List:
				if (m_pListBox->m_aItems.size() > 0)
					ProcessMove(position);
				break;
			default:
				switch (m_pListBox->m_eHoveredElement)
				{
				case Element::HScroll:
					if (m_pListBox->getHScroll()->NotifyOnMouseMove(LocalToHScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pListBox->m_pCanvas)
							m_pListBox->m_pCanvas->setValid(false);
						m_pListBox->Repaint(false);
					}
					break;
				case Element::VScroll:
					if (m_pListBox->getVScroll()->NotifyOnMouseMove(LocalToVScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pListBox->m_pCanvas)
							m_pListBox->m_pCanvas->setValid(false);
						m_pListBox->Repaint(false);
					}
					break;
				default:
					break;
				}
			}
			if (m_pListBox->UpdateHoveredItem(position))
			{
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
		}

		void CCustomListBoxService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_pListBox->isCaptureMouse())
				m_pListBox->getForm()->CaptureMouse(m_pListBox, true);
			if (!m_hTimer && (m_pListBox->getHScroll()->isEnabled() || m_pListBox->getVScroll()->isEnabled()))
				m_hTimer = m_pListBox->getForm()->CreateTimer(this, m_pListBox->m_fScrollInterval);
			PointF position{ m_pListBox->FormToLocal(m.Position) };
			switch (m_pListBox->m_eHoveredElement)
			{
			case Element::HScroll:
				if (m_pListBox->getHScroll()->NotifyOnMouseLeftDown(LocalToHScroll(position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
				break;
			case Element::VScroll:
				if (m_pListBox->getVScroll()->NotifyOnMouseLeftDown(LocalToVScroll(position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
				break;
			case Element::List:
			{
				IListItem *item{ m_pListBox->getItemAtPoint(position) };
				m_pListBox->m_pDownItem = item;
				if (item)
				{
					int index{ m_pListBox->getItemIndex(item) };
					if (item->isEnabled())
					{
						item->QueryService()->NotifyOnMouseDown(LocalToItem(position, index), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift);
						if (m_pListBox->m_bMultiselect && m.Shift && !m.Ctrl)
						{
							if (SelectRange(m_pListBox->m_iDownIndex, index))
							{
								if (m_pListBox->m_pCanvas)
									m_pListBox->m_pCanvas->setValid(false);
								m_pListBox->Repaint(false);
							}
						}
						else if (m_pListBox->m_bMultiselect && !m.Shift && m.Ctrl)
						{
							item->setSelected(!item->isSelected());
							m_pListBox->m_iDownIndex = index;
						}
						else
						{
							m_pListBox->m_iDownIndex = index;
							if (SelectRange(index, index))
							{
								if (m_pListBox->m_pCanvas)
									m_pListBox->m_pCanvas->setValid(false);
								m_pListBox->Repaint(false);
							}
						}
						m_pListBox->setActiveIndex(index);
					}
				}
			}
			break;
			default:
				break;
			}
			m_pListBox->m_eDownElement = m_pListBox->m_eHoveredElement;
		}

		void CCustomListBoxService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			PointF position{ m_pListBox->FormToLocal(m.Position) };
			switch (m_pListBox->m_eDownElement)
			{
			case Element::HScroll:
				if (m_pListBox->getHScroll()->NotifyOnMouseLeftUp(LocalToHScroll(position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
				break;
			case Element::VScroll:
				if (m_pListBox->getVScroll()->NotifyOnMouseLeftUp(LocalToVScroll(position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
				break;
			default:
				break;
			}
			if (m_pListBox->m_pDownItem)
				m_pListBox->m_pDownItem->QueryService()->NotifyOnMouseUp(LocalToItem(position, m_pListBox->getItemIndex(m_pListBox->m_pDownItem)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift);
			MouseUp();
		}

		void CCustomListBoxService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CCustomListBoxService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CCustomListBoxService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CCustomListBoxService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CCustomListBoxService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CCustomListBoxService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CCustomListBoxService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CCustomListBoxService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			PointF position{ m_pListBox->FormToLocal(m.Position) };
			switch (m_pListBox->m_eHoveredElement)
			{
			case Element::HScroll:
				if (m_pListBox->getHScroll()->NotifyOnMouseVerticalWheel(LocalToHScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
				break;
			case Element::VScroll:
				if (m_pListBox->getVScroll()->NotifyOnMouseVerticalWheel(LocalToVScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
				break;
			default:
				if (m_pListBox->getVScroll()->isEnabled() && m_pListBox->getVScroll()->setScroll(m_pListBox->getVScroll()->getScroll() + m_pListBox->getVScroll()->getDeltaMedium() * (m.Delta > 0 ? -1 : 1)))
				{
					m_pListBox->UpdateHoveredItem();
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
			}
		}

		void CCustomListBoxService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			PointF position{ m_pListBox->FormToLocal(m.Position) };
			switch (m_pListBox->m_eHoveredElement)
			{
			case Element::HScroll:
				if (m_pListBox->getHScroll()->NotifyOnMouseHorizontalWheel(LocalToHScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
				break;
			case Element::VScroll:
				if (m_pListBox->getVScroll()->NotifyOnMouseHorizontalWheel(LocalToVScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
				{
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
				break;
			default:
				if (m_pListBox->getHScroll()->isEnabled() && m_pListBox->getHScroll()->setScroll(m_pListBox->getHScroll()->getScroll() + m_pListBox->getHScroll()->getDeltaMedium() * (m.Delta > 0 ? -1 : 1)))
				{
					m_pListBox->UpdateHoveredItem();
					if (m_pListBox->m_pCanvas)
						m_pListBox->m_pCanvas->setValid(false);
					m_pListBox->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region Process keys
		void CCustomListBoxService::ProcessKeyUp(const bool shift)
		{
			if (m_pListBox->m_aItems.size() > 0)
			{
				Point p;
				if (m_pListBox->m_iActiveIndex >= 0)
				{
					p = m_pListBox->IndexToGrid(m_pListBox->m_iActiveIndex);
					if (p.Y > 0)
						p.Y--;
				}
				else
					p = m_pListBox->IndexToGrid((int)m_pListBox->m_aItems.size() - 1);
				while (p.Y >= 0 && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
					p.Y--;
				if (p.Y >= 0)
					PostKey(m_pListBox->GridToIndex(p), shift);
			}
		}

		void CCustomListBoxService::ProcessKeyDown(const bool shift)
		{
			if (m_pListBox->m_aItems.size() > 0)
			{
				Point p;
				if (m_pListBox->m_iActiveIndex >= 0)
				{
					p = m_pListBox->IndexToGrid(m_pListBox->m_iActiveIndex);
					if (p.Y < m_pListBox->m_sGrid.Y)
						p.Y++;
				}
				else
					p = { 0, 0 };
				while (p.Y < m_pListBox->m_sGrid.Y && m_pListBox->GridToIndex(p) < (int)m_pListBox->m_aItems.size() && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
					p.Y++;
				if (p.Y < m_pListBox->m_sGrid.Y)
				{
					int index{ m_pListBox->GridToIndex(p) };
					if (index < (int)m_pListBox->m_aItems.size())
						PostKey(index, shift);
				}
			}
		}

		void CCustomListBoxService::ProcessKeyPageUp(const bool shift)
		{
			if (m_pListBox->m_aItems.size() > 0)
			{
				Point p;
				if (m_pListBox->m_iActiveIndex >= 0)
				{
					int count{ ntl::Max<int>(1, int(m_pListBox->getRealClientRect().height() / m_pListBox->m_sItemSize.Y)) };
					p = m_pListBox->IndexToGrid(m_pListBox->m_iActiveIndex);
					p.Y = ntl::Max<int>(0, p.Y - count);
					while (p.Y >= 0 && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
						p.Y--;
					if (p.Y < 0)
					{
						p.Y = 0;
						while (p.Y < m_pListBox->m_sGrid.Y && m_pListBox->GridToIndex(p) < m_pListBox->m_iActiveIndex && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
							p.Y++;
					}
				}
				else
				{
					p = m_pListBox->IndexToGrid((int)m_pListBox->m_aItems.size() - 1);
					while (p.Y >= 0 && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
						p.Y--;
				}
				if (p.Y >= 0)
					PostKey(m_pListBox->GridToIndex(p), shift);
			}
		}

		void CCustomListBoxService::ProcessKeyPageDown(const bool shift)
		{
			if (m_pListBox->m_aItems.size() > 0)
			{
				Point p;
				if (m_pListBox->m_iActiveIndex >= 0)
				{
					int count{ ntl::Max<int>(1, int(m_pListBox->getRealClientRect().height() / m_pListBox->m_sItemSize.Y)) };
					p = m_pListBox->IndexToGrid(m_pListBox->m_iActiveIndex);
					p.Y = ntl::Min<int>(m_pListBox->m_sGrid.Y - 1, p.Y + count);
					if (m_pListBox->GridToIndex(p) >= (int)m_pListBox->m_aItems.size())
						p = m_pListBox->IndexToGrid((int)m_pListBox->m_aItems.size() - 1);
					while (p.Y < m_pListBox->m_sGrid.Y && m_pListBox->GridToIndex(p) < (int)m_pListBox->m_aItems.size() && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
						p.Y++;
					if (p.Y >= (int)m_pListBox->m_aItems.size() || m_pListBox->GridToIndex(p) >= (int)m_pListBox->m_aItems.size())
					{
						p = m_pListBox->IndexToGrid((int)m_pListBox->m_aItems.size() - 1);
						while (p.Y >= 0 && m_pListBox->GridToIndex(p) > m_pListBox->m_iActiveIndex && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
							p.Y--;
					}
				}
				else
				{
					p = { 0, 0 };
					while (p.Y < m_pListBox->m_sGrid.Y && m_pListBox->GridToIndex(p) < (int)m_pListBox->m_aItems.size() && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
						p.Y++;
				}
				if (p.Y < m_pListBox->m_sGrid.Y)
				{
					int index{ m_pListBox->GridToIndex(p) };
					if (index < (int)m_pListBox->m_aItems.size())
						PostKey(index, shift);
				}
			}
		}

		void CCustomListBoxService::ProcessKeyHome(const bool ctrl, const bool shift)
		{
			if (m_pListBox->m_aItems.size() > 0)
			{
				Point p;
				if (m_pListBox->m_iActiveIndex >= 0)
					p = ctrl ? Point{ 0, 0 } : Point{ m_pListBox->IndexToGrid(m_pListBox->m_iActiveIndex).X, 0 };
				else
					p = Point{ 0, 0 };
				if (ctrl)
				{
					int index{ m_pListBox->GridToIndex(p) };
					while (index < (int)m_pListBox->m_aItems.size() && !m_pListBox->m_aItems[index]->isEnabled())
						index++;
					if (index < (int)m_pListBox->m_aItems.size())
						PostKey(index, shift);
				}
				else
				{
					while (p.Y < m_pListBox->m_sGrid.Y && m_pListBox->GridToIndex(p) < (int)m_pListBox->m_aItems.size() && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled() && (m_pListBox->m_iActiveIndex < 0 || m_pListBox->GridToIndex(p) < m_pListBox->m_iActiveIndex))
						p.Y++;
					if (p.Y < m_pListBox->m_sGrid.Y)
					{
						int index{ m_pListBox->GridToIndex(p) };
						if (index < (int)m_pListBox->m_aItems.size())
							PostKey(index, shift);
					}
				}
			}
		}

		void CCustomListBoxService::ProcessKeyEnd(const bool ctrl, const bool shift)
		{
			if (m_pListBox->m_aItems.size() > 0)
			{
				Point p;
				if (m_pListBox->m_iActiveIndex >= 0)
				{
					p = ctrl ? m_pListBox->IndexToGrid((int)m_pListBox->m_aItems.size() - 1) : Point{ m_pListBox->IndexToGrid(m_pListBox->m_iActiveIndex).X, m_pListBox->m_sGrid.Y - 1 };
					while (p.Y > 0 && m_pListBox->GridToIndex(p) >= (int)m_pListBox->m_aItems.size())
						p.Y--;
				}
				else
					p = m_pListBox->IndexToGrid((int)m_pListBox->m_aItems.size() - 1);
				if (ctrl)
				{
					int index{ m_pListBox->GridToIndex(p) };
					while (index >= 0 && !m_pListBox->m_aItems[index]->isEnabled())
						index--;
					if (index >= 0)
						PostKey(index, shift);
				}
				else
				{
					while (p.Y >= 0 && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled() && (m_pListBox->m_iActiveIndex < 0 || m_pListBox->GridToIndex(p) > m_pListBox->m_iActiveIndex))
						p.Y--;
					if (p.Y >= 0)
						PostKey(m_pListBox->GridToIndex(p), shift);
				}
			}
		}

		void CCustomListBoxService::ProcessKeyLeft(const bool shift)
		{
			if (m_pListBox->m_aItems.size() > 0)
			{
				Point p;
				if (m_pListBox->m_iActiveIndex >= 0)
				{
					p = m_pListBox->IndexToGrid(m_pListBox->m_iActiveIndex);
					p.X = ntl::Max<int>(0, p.X - 1);
				}
				else
					p = m_pListBox->IndexToGrid((int)m_pListBox->m_aItems.size() - 1);
				while (p.Y >= 0 && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
					p.Y--;
				if (p.Y < 0)
				{
					p.Y = 0;
					while (p.Y < m_pListBox->m_sGrid.Y && m_pListBox->GridToIndex(p) < (int)m_pListBox->m_aItems.size() && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
						p.Y++;
				}
				if (p.Y < m_pListBox->m_sGrid.Y)
				{
					int index{ m_pListBox->GridToIndex(p) };
					if (index < (int)m_pListBox->m_aItems.size())
						PostKey(index, shift);
				}
			}
		}

		void CCustomListBoxService::ProcessKeyRight(const bool shift)
		{
			if (m_pListBox->m_aItems.size() > 0)
			{
				Point p;
				if (m_pListBox->m_iActiveIndex >= 0)
				{
					p = m_pListBox->IndexToGrid(m_pListBox->m_iActiveIndex);
					p.X = ntl::Min<int>(m_pListBox->m_sGrid.X - 1, p.X + 1);
					while (p.Y > 0 && m_pListBox->GridToIndex(p) >= (int)m_pListBox->m_aItems.size())
						p.Y--;
				}
				else
					p = Point{ 0, 0 };
				while (p.Y >= 0 && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
					p.Y--;
				if (p.Y < 0)
				{
					p.Y = 0;
					while (p.Y < m_pListBox->m_sGrid.Y && m_pListBox->GridToIndex(p) < (int)m_pListBox->m_aItems.size() && !m_pListBox->m_aItems[m_pListBox->GridToIndex(p)]->isEnabled())
						p.Y++;
				}
				if (p.Y < m_pListBox->m_sGrid.Y)
				{
					int index{ m_pListBox->GridToIndex(p) };
					if (index < (int)m_pListBox->m_aItems.size())
						PostKey(index, shift);
				}
			}
		}

		void CCustomListBoxService::ProcessKeySpace()
		{
			if (m_pListBox->m_iActiveIndex >= 0 && m_pListBox->m_aItems[m_pListBox->m_iActiveIndex]->isEnabled())
				PostKey(m_pListBox->m_iActiveIndex, false);
		}

		void CCustomListBoxService::ProcessKeyA()
		{
			if (m_pListBox->m_aItems.size() > 0)
			{
				SelectRange(0, (int)m_pListBox->m_aItems.size() - 1);
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Timer notification
		void CCustomListBoxService::NotifyOnTimer(const PlatformHandle id)
		{
			if (m_pListBox->m_eDownElement == Element::List)
			{
				CLockRepaint lock{ m_pListBox };
				ProcessMove(m_pListBox->FormToLocal((PointF)m_pListBox->getForm()->ScreenToClient(Application->Mouse->getPosition())));
			}
		}
	#pragma endregion
	}
}