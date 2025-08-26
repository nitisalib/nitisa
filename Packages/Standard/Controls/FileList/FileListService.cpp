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
		CFileListService::CFileListService(CFileList *filelist) :
			CControlService(filelist),
			m_pFileList{ filelist },
			m_hTimer{ nullptr }
		{

		}
	#pragma endregion

	#pragma region Helpers
		PointF CFileListService::LocalToHScroll(const PointF &position)
		{
			return PointF{
				position.X - m_pFileList->m_sBorderWidth.Left,
				position.Y - (m_pFileList->getHeight() - m_pFileList->m_sBorderWidth.Bottom - m_pFileList->getHScroll()->getSize().Y)
			};
		}

		PointF CFileListService::LocalToVScroll(const PointF &position)
		{
			return PointF{
				position.X - (m_pFileList->getWidth() - m_pFileList->m_sBorderWidth.Right - m_pFileList->getVScroll()->getSize().X),
				position.Y - m_pFileList->m_sBorderWidth.Top };
		}

		PointF CFileListService::LocalToItem(const PointF &position, const int index)
		{
			PointF p{ m_pFileList->m_aItems[index]->getPosition() };
			if (m_pFileList->getHScroll()->isEnabled())
				p.X -= m_pFileList->getHScroll()->getScroll();
			if (m_pFileList->getVScroll()->isEnabled())
				p.Y -= m_pFileList->getVScroll()->getScroll();
			return PointF{ position.X - p.X, position.Y - p.Y };
		}

		bool CFileListService::SelectRange(int from, int to)
		{
			from = ntl::Max<int>(0, from);
			if (from > to)
				ntl::Swap<int>(from, to);
			m_pFileList->m_cOwner.setIgnoreSelect(true);
			int index{ 0 };
			bool result{ false };
			for (auto pos = m_pFileList->m_aItems.begin(); pos != m_pFileList->m_aItems.end(); pos++, index++)
				if ((index < from || index > to) && (*pos)->isSelected())
					result = (*pos)->setSelected(false) || result;
				else if (index >= from && index <= to && !(*pos)->isSelected())
					result = (*pos)->setSelected(true) || result;
			m_pFileList->m_cOwner.setIgnoreSelect(false);
			return result;
		}

		bool CFileListService::InvertRange(int from, int to)
		{
			if (from > to)
			{
				ntl::Swap<int>(from, to);
				to--;
			}
			else
				from++;
			m_pFileList->m_cOwner.setIgnoreSelect(true);
			bool result{ false };
			for (int i = from; i <= to; i++)
				if (m_pFileList->m_aItems[i]->isEnabled())
					result = m_pFileList->m_aItems[i]->setSelected(!m_pFileList->m_aItems[i]->isSelected()) || result;
			m_pFileList->m_cOwner.setIgnoreSelect(false);
			return result;
		}

		void CFileListService::MouseUp()
		{
			if (m_pFileList->m_pDownItem)
			{
				m_pFileList->m_pDownItem->QueryService()->NotifyOnMouseDownCancel();
				m_pFileList->m_pDownItem = nullptr;
			}
			m_pFileList->m_eDownElement = CFileList::Element::None;
			if (m_pFileList->isCaptureMouse())
				m_pFileList->getForm()->ReleaseCaptureMouse();
			if (m_hTimer)
			{
				m_pFileList->getForm()->DeleteTimer(m_hTimer);
				m_hTimer = nullptr;
			}
		}

		void CFileListService::ProcessMove(const PointF &position)
		{
			RectF client{ m_pFileList->getRealClientRect() };
			Point p{ m_pFileList->getGridCell(client, position) };
			// Scroll if required
			if (position.X < client.Left && m_pFileList->getHScroll()->isEnabled() && m_pFileList->getHScroll()->setScroll(m_pFileList->getHScroll()->getScroll() - m_pFileList->m_sItemSize.X))
			{
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
			if (position.X > client.Right && m_pFileList->getHScroll()->isEnabled() && m_pFileList->getHScroll()->setScroll(m_pFileList->getHScroll()->getScroll() + m_pFileList->m_sItemSize.X))
			{
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
			if (position.Y < client.Top && m_pFileList->getVScroll()->isEnabled() && m_pFileList->getVScroll()->setScroll(m_pFileList->getVScroll()->getScroll() - m_pFileList->m_sItemSize.Y))
			{
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
			if (position.Y > client.Bottom && m_pFileList->getVScroll()->isEnabled() && m_pFileList->getVScroll()->setScroll(m_pFileList->getVScroll()->getScroll() + m_pFileList->m_sItemSize.Y))
			{
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
			// Selection
			int index{ ntl::Clamp<int>(p.Y * m_pFileList->m_iColumns + p.X, 0, (int)m_pFileList->m_aItems.size() - 1) };
			if (m_pFileList->m_bMultiselect)
			{
				if (SelectRange(m_pFileList->m_iDownIndex, index))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
			}
			else
			{
				m_pFileList->m_iDownIndex = index;
				if (SelectRange(index, index))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
			}
			m_pFileList->setActiveIndex(index);
		}

		void CFileListService::PostKey(const int index, const bool shift)
		{
			if (m_pFileList->m_bMultiselect && shift && m_pFileList->m_iActiveIndex >= 0)
				SelectRange(m_pFileList->m_iDownIndex, index);
			else
			{
				SelectRange(index, index);
				m_pFileList->m_iDownIndex = index;
			}
			m_pFileList->setActiveIndex(index);
			m_pFileList->ScrollToItem(index);
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
			m_pFileList->Repaint(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CFileListService::NotifyOnAttach()
		{
			if (m_pFileList->getForm())
			{
				if (m_pFileList->m_pHScroll)
					m_pFileList->m_pHScroll->NotifyOnAttach();
				if (m_pFileList->m_pVScroll)
					m_pFileList->m_pVScroll->NotifyOnAttach();
				m_pFileList->UpdateList();
				m_pFileList->UpdateHoveredItem();
			}
		}

		void CFileListService::NotifyOnDetaching()
		{
			MouseUp();
			if (m_pFileList->m_pHScroll)
				m_pFileList->m_pHScroll->NotifyOnMouseDownCancel();
			if (m_pFileList->m_pVScroll)
				m_pFileList->m_pVScroll->NotifyOnMouseDownCancel();
		}

		void CFileListService::NotifyOnFreeResources()
		{
			if (m_pFileList->m_pHScroll)
				m_pFileList->m_pHScroll->NotifyOnFreeResources();
			if (m_pFileList->m_pVScroll)
				m_pFileList->m_pVScroll->NotifyOnFreeResources();
			for (auto pos = m_pFileList->m_aItems.begin(); pos != m_pFileList->m_aItems.end(); pos++)
				(*pos)->QueryService()->NotifyOnFreeResources();
			if (m_pFileList->m_pCanvas)
			{
				m_pFileList->m_pCanvas->Release();
				m_pFileList->m_pCanvas = nullptr;
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CFileListService::NotifyOnParentStyleChange()
		{
			if (m_pFileList->getStyle())
			{
				m_pFileList->UpdateFromStyle(m_pFileList->getStyle());
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
			}
		}

		void CFileListService::NotifyOnParentFontChange()
		{
			m_pFileList->UpdateList();
			m_pFileList->UpdateHoveredItem();
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CFileListService::NotifyOnEnable()
		{
			m_pFileList->UpdateList();
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
		}

		void CFileListService::NotifyOnDisable()
		{
			MouseUp();
			m_pFileList->UpdateList();
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
		}

		void CFileListService::NotifyOnResize()
		{
			m_pFileList->UpdateList();
			m_pFileList->UpdateHoveredItem();
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
		}

		void CFileListService::NotifyOnStyleChange()
		{
			if (m_pFileList->getStyle())
			{
				m_pFileList->UpdateFromStyle(m_pFileList->getStyle());
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
			}
		}

		void CFileListService::NotifyOnFontChange()
		{
			m_pFileList->UpdateList();
			m_pFileList->UpdateHoveredItem();
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
		}

		void CFileListService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
			m_pFileList->Repaint(false);
		}

		void CFileListService::NotifyOnKillFocus()
		{
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
			m_pFileList->Repaint(false);
		}

		void CFileListService::NotifyOnKillCaptureMouse()
		{
			m_pFileList->m_eDownElement = CFileList::Element::None;
			if (m_hTimer)
			{
				m_pFileList->getForm()->DeleteTimer(m_hTimer);
				m_hTimer = nullptr;
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CFileListService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pFileList->getWidth(), 0) && ntl::IsGreater<float>(m_pFileList->getHeight(), 0))
				m_pFileList->Render();
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CFileListService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			IListItem *item{ m_pFileList->getActiveItem() };
			if (item && item->QueryService()->NotifyOnKeyDown(m.Key, ctrl, alt, shift))
			{
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
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

		void CFileListService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			IListItem *item{ m_pFileList->getActiveItem() };
			if (item && item->QueryService()->NotifyOnKeyUp(m.Key, ctrl, alt, shift))
			{
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
		}

		void CFileListService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_pFileList->m_sLastSearch) };
			if ((float)duration.count() * 0.001f > m_pFileList->m_fSearchResetInterval)
				m_pFileList->m_sSearch.clear();
			m_pFileList->m_sLastSearch = std::chrono::steady_clock::now();
			m_pFileList->m_sSearch += m.Char;
			int index{ m_pFileList->Search(ToLower(m_pFileList->m_sSearch)) };
			if (index >= 0 && index != m_pFileList->m_iActiveIndex)
				PostKey(index, false);
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CFileListService::NotifyOnMouseHover(const MessagePosition &m)
		{
			PointF position{ m_pFileList->FormToLocal(m.Position) };
			CFileList::Element el{ m_pFileList->getElement(position) };
			if (el != m_pFileList->m_eHoveredElement)
			{
				switch (m_pFileList->m_eHoveredElement)
				{
				case CFileList::Element::HScroll:
					m_pFileList->getHScroll()->NotifyOnMouseLeave();
					break;
				case CFileList::Element::VScroll:
					m_pFileList->getVScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
			}
			m_pFileList->m_eHoveredElement = el;
			switch (m_pFileList->m_eHoveredElement)
			{
			case CFileList::Element::HScroll:
				m_pFileList->getHScroll()->NotifyOnMouseHover(LocalToHScroll(position));
				break;
			case CFileList::Element::VScroll:
				m_pFileList->getVScroll()->NotifyOnMouseHover(LocalToVScroll(position));
				break;
			default:
				break;
			}
			m_pFileList->UpdateHoveredItem(position);
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
			m_pFileList->Repaint(false);
		}

		void CFileListService::NotifyOnMouseLeave()
		{
			if (m_pFileList->m_eHoveredElement != CFileList::Element::None)
			{
				switch (m_pFileList->m_eHoveredElement)
				{
				case CFileList::Element::HScroll:
					m_pFileList->getHScroll()->NotifyOnMouseLeave();
					break;
				case CFileList::Element::VScroll:
					m_pFileList->getVScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_pFileList->m_eHoveredElement = CFileList::Element::None;
			}
			m_pFileList->UpdateHoveredItem();
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
			m_pFileList->Repaint(false);
		}

		void CFileListService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			PointF position{ m_pFileList->FormToLocal(m.Position) };
			CFileList::Element el{ m_pFileList->getElement(position) };
			if (el != m_pFileList->m_eHoveredElement)
			{
				switch (m_pFileList->m_eHoveredElement)
				{
				case CFileList::Element::HScroll:
					m_pFileList->getHScroll()->NotifyOnMouseLeave();
					break;
				case CFileList::Element::VScroll:
					m_pFileList->getVScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_pFileList->m_eHoveredElement = el;
				switch (m_pFileList->m_eHoveredElement)
				{
				case CFileList::Element::HScroll:
					m_pFileList->getHScroll()->NotifyOnMouseHover(LocalToHScroll(position));
					break;
				case CFileList::Element::VScroll:
					m_pFileList->getVScroll()->NotifyOnMouseHover(LocalToVScroll(position));
					break;
				default:
					break;
				}
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
			switch (m_pFileList->m_eDownElement)
			{
			case CFileList::Element::HScroll:
				if (m_pFileList->getHScroll()->NotifyOnMouseMove(LocalToHScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
				break;
			case CFileList::Element::VScroll:
				if (m_pFileList->getVScroll()->NotifyOnMouseMove(LocalToVScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
				break;
			case CFileList::Element::List:
				if (m_pFileList->m_aItems.size() > 0)
					ProcessMove(position);
				break;
			default:
				switch (m_pFileList->m_eHoveredElement)
				{
				case CFileList::Element::HScroll:
					if (m_pFileList->getHScroll()->NotifyOnMouseMove(LocalToHScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pFileList->m_pCanvas)
							m_pFileList->m_pCanvas->setValid(false);
						m_pFileList->Repaint(false);
					}
					break;
				case CFileList::Element::VScroll:
					if (m_pFileList->getVScroll()->NotifyOnMouseMove(LocalToVScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pFileList->m_pCanvas)
							m_pFileList->m_pCanvas->setValid(false);
						m_pFileList->Repaint(false);
					}
					break;
				default:
					break;
				}
			}
			if (m_pFileList->UpdateHoveredItem(position))
			{
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
		}

		void CFileListService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_pFileList->isCaptureMouse())
				m_pFileList->getForm()->CaptureMouse(m_pFileList, true);
			if (!m_hTimer && (m_pFileList->getHScroll()->isEnabled() || m_pFileList->getVScroll()->isEnabled()))
				m_hTimer = m_pFileList->getForm()->CreateTimer(this, m_pFileList->m_fScrollInterval);
			PointF position{ m_pFileList->FormToLocal(m.Position) };
			switch (m_pFileList->m_eHoveredElement)
			{
			case CFileList::Element::HScroll:
				if (m_pFileList->getHScroll()->NotifyOnMouseLeftDown(LocalToHScroll(position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
				break;
			case CFileList::Element::VScroll:
				if (m_pFileList->getVScroll()->NotifyOnMouseLeftDown(LocalToVScroll(position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
				break;
			case CFileList::Element::List:
			{
				IListItem *item{ m_pFileList->getItemAtPoint(position) };
				m_pFileList->m_pDownItem = item;
				if (item)
				{
					int index{ m_pFileList->getItemIndex(item) };
					item->QueryService()->NotifyOnMouseDown(LocalToItem(position, index), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift);
					if (m_pFileList->m_bMultiselect && m.Shift && !m.Ctrl)
					{
						if (SelectRange(m_pFileList->m_iDownIndex, index))
						{
							if (m_pFileList->m_pCanvas)
								m_pFileList->m_pCanvas->setValid(false);
							m_pFileList->Repaint(false);
						}
					}
					else if (m_pFileList->m_bMultiselect && !m.Shift && m.Ctrl)
					{
						item->setSelected(!item->isSelected());
						m_pFileList->m_iDownIndex = index;
					}
					else
					{
						m_pFileList->m_iDownIndex = index;
						if (SelectRange(index, index))
						{
							if (m_pFileList->m_pCanvas)
								m_pFileList->m_pCanvas->setValid(false);
							m_pFileList->Repaint(false);
						}
					}
					m_pFileList->setActiveIndex(index);
				}
			}
			break;
			default:
				break;
			}
			m_pFileList->m_eDownElement = m_pFileList->m_eHoveredElement;
		}

		void CFileListService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			PointF position{ m_pFileList->FormToLocal(m.Position) };
			switch (m_pFileList->m_eDownElement)
			{
			case CFileList::Element::HScroll:
				if (m_pFileList->getHScroll()->NotifyOnMouseLeftUp(LocalToHScroll(position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
				break;
			case CFileList::Element::VScroll:
				if (m_pFileList->getVScroll()->NotifyOnMouseLeftUp(LocalToVScroll(position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
				break;
			default:
				break;
			}
			if (m_pFileList->m_pDownItem)
				m_pFileList->m_pDownItem->QueryService()->NotifyOnMouseUp(LocalToItem(position, m_pFileList->getItemIndex(m_pFileList->m_pDownItem)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift);
			MouseUp();
		}

		void CFileListService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CFileListService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CFileListService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CFileListService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CFileListService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CFileListService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CFileListService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp();
		}

		void CFileListService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			PointF position{ m_pFileList->FormToLocal(m.Position) };
			switch (m_pFileList->m_eHoveredElement)
			{
			case CFileList::Element::HScroll:
				if (m_pFileList->getHScroll()->NotifyOnMouseVerticalWheel(LocalToHScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
				break;
			case CFileList::Element::VScroll:
				if (m_pFileList->getVScroll()->NotifyOnMouseVerticalWheel(LocalToVScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
				break;
			default:
				if (m_pFileList->getVScroll()->isEnabled() && m_pFileList->getVScroll()->setScroll(m_pFileList->getVScroll()->getScroll() + m_pFileList->getVScroll()->getDeltaMedium() * (m.Delta > 0 ? -1 : 1)))
				{
					m_pFileList->UpdateHoveredItem();
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
			}
		}

		void CFileListService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			PointF position{ m_pFileList->FormToLocal(m.Position) };
			switch (m_pFileList->m_eHoveredElement)
			{
			case CFileList::Element::HScroll:
				if (m_pFileList->getHScroll()->NotifyOnMouseHorizontalWheel(LocalToHScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
				break;
			case CFileList::Element::VScroll:
				if (m_pFileList->getVScroll()->NotifyOnMouseHorizontalWheel(LocalToVScroll(position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
				{
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
				break;
			default:
				if (m_pFileList->getHScroll()->isEnabled() && m_pFileList->getHScroll()->setScroll(m_pFileList->getHScroll()->getScroll() + m_pFileList->getHScroll()->getDeltaMedium() * (m.Delta > 0 ? -1 : 1)))
				{
					m_pFileList->UpdateHoveredItem();
					if (m_pFileList->m_pCanvas)
						m_pFileList->m_pCanvas->setValid(false);
					m_pFileList->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region Process keys
		void CFileListService::ProcessKeyUp(const bool shift)
		{
			if (m_pFileList->m_aItems.size() > 0)
			{
				Point p;
				if (m_pFileList->m_iActiveIndex >= 0)
				{
					p = m_pFileList->IndexToGrid(m_pFileList->m_iActiveIndex);
					if (p.Y > 0)
						p.Y--;
				}
				else
					p = m_pFileList->IndexToGrid((int)m_pFileList->m_aItems.size() - 1);
				if (p.Y >= 0)
					PostKey(m_pFileList->GridToIndex(p), shift);
			}
		}

		void CFileListService::ProcessKeyDown(const bool shift)
		{
			if (m_pFileList->m_aItems.size() > 0)
			{
				Point p;
				if (m_pFileList->m_iActiveIndex >= 0)
				{
					p = m_pFileList->IndexToGrid(m_pFileList->m_iActiveIndex);
					if (p.Y < m_pFileList->m_sGrid.Y)
						p.Y++;
				}
				else
					p = { 0, 0 };
				if (p.Y < m_pFileList->m_sGrid.Y)
				{
					int index{ m_pFileList->GridToIndex(p) };
					if (index < (int)m_pFileList->m_aItems.size())
						PostKey(index, shift);
				}
			}
		}

		void CFileListService::ProcessKeyPageUp(const bool shift)
		{
			if (m_pFileList->m_aItems.size() > 0)
			{
				Point p;
				if (m_pFileList->m_iActiveIndex >= 0)
				{
					int count{ ntl::Max<int>(1, int(m_pFileList->getRealClientRect().height() / m_pFileList->m_sItemSize.Y)) };
					p = m_pFileList->IndexToGrid(m_pFileList->m_iActiveIndex);
					p.Y = ntl::Max<int>(0, p.Y - count);
				}
				else
					p = m_pFileList->IndexToGrid((int)m_pFileList->m_aItems.size() - 1);
				if (p.Y >= 0)
					PostKey(m_pFileList->GridToIndex(p), shift);
			}
		}

		void CFileListService::ProcessKeyPageDown(const bool shift)
		{
			if (m_pFileList->m_aItems.size() > 0)
			{
				Point p;
				if (m_pFileList->m_iActiveIndex >= 0)
				{
					int count{ ntl::Max<int>(1, int(m_pFileList->getRealClientRect().height() / m_pFileList->m_sItemSize.Y)) };
					p = m_pFileList->IndexToGrid(m_pFileList->m_iActiveIndex);
					p.Y = ntl::Min<int>(m_pFileList->m_sGrid.Y - 1, p.Y + count);
					if (m_pFileList->GridToIndex(p) >= (int)m_pFileList->m_aItems.size())
						p = m_pFileList->IndexToGrid((int)m_pFileList->m_aItems.size() - 1);
					if (p.Y >= (int)m_pFileList->m_aItems.size() || m_pFileList->GridToIndex(p) >= (int)m_pFileList->m_aItems.size())
						p = m_pFileList->IndexToGrid((int)m_pFileList->m_aItems.size() - 1);
				}
				else
					p = Point{ 0, 0 };
				if (p.Y < m_pFileList->m_sGrid.Y)
				{
					int index{ m_pFileList->GridToIndex(p) };
					if (index < (int)m_pFileList->m_aItems.size())
						PostKey(index, shift);
				}
			}
		}

		void CFileListService::ProcessKeyHome(const bool ctrl, const bool shift)
		{
			if (m_pFileList->m_aItems.size() > 0)
			{
				Point p;
				if (m_pFileList->m_iActiveIndex >= 0)
					p = ctrl ? Point{ 0, 0 } : Point{ m_pFileList->IndexToGrid(m_pFileList->m_iActiveIndex).X, 0 };
				else
					p = Point{ 0, 0 };
				if (ctrl)
				{
					int index{ m_pFileList->GridToIndex(p) };
					if (index < (int)m_pFileList->m_aItems.size())
						PostKey(index, shift);
				}
				else
				{
					if (p.Y < m_pFileList->m_sGrid.Y)
					{
						int index{ m_pFileList->GridToIndex(p) };
						if (index < (int)m_pFileList->m_aItems.size())
							PostKey(index, shift);
					}
				}
			}
		}

		void CFileListService::ProcessKeyEnd(const bool ctrl, const bool shift)
		{
			if (m_pFileList->m_aItems.size() > 0)
			{
				Point p;
				if (m_pFileList->m_iActiveIndex >= 0)
				{
					p = ctrl ? m_pFileList->IndexToGrid((int)m_pFileList->m_aItems.size() - 1) : Point{ m_pFileList->IndexToGrid(m_pFileList->m_iActiveIndex).X, m_pFileList->m_sGrid.Y - 1 };
					while (p.Y > 0 && m_pFileList->GridToIndex(p) >= (int)m_pFileList->m_aItems.size())
						p.Y--;
				}
				else
					p = m_pFileList->IndexToGrid((int)m_pFileList->m_aItems.size() - 1);
				if (ctrl)
				{
					int index{ m_pFileList->GridToIndex(p) };
					if (index >= 0)
						PostKey(index, shift);
				}
				else
				{
					if (p.Y >= 0)
						PostKey(m_pFileList->GridToIndex(p), shift);
				}
			}
		}

		void CFileListService::ProcessKeyLeft(const bool shift)
		{
			if (m_pFileList->m_aItems.size() > 0)
			{
				Point p;
				if (m_pFileList->m_iActiveIndex >= 0)
				{
					p = m_pFileList->IndexToGrid(m_pFileList->m_iActiveIndex);
					p.X = ntl::Max<int>(0, p.X - 1);
				}
				else
					p = m_pFileList->IndexToGrid((int)m_pFileList->m_aItems.size() - 1);
				if (p.Y < 0)
					p.Y = 0;
				if (p.Y < m_pFileList->m_sGrid.Y)
				{
					int index{ m_pFileList->GridToIndex(p) };
					if (index < (int)m_pFileList->m_aItems.size())
						PostKey(index, shift);
				}
			}
		}

		void CFileListService::ProcessKeyRight(const bool shift)
		{
			if (m_pFileList->m_aItems.size() > 0)
			{
				Point p;
				if (m_pFileList->m_iActiveIndex >= 0)
				{
					p = m_pFileList->IndexToGrid(m_pFileList->m_iActiveIndex);
					p.X = ntl::Min<int>(m_pFileList->m_sGrid.X - 1, p.X + 1);
					while (p.Y > 0 && m_pFileList->GridToIndex(p) >= (int)m_pFileList->m_aItems.size())
						p.Y--;
				}
				else
					p = { 0, 0 };
				if (p.Y < 0)
					p.Y = 0;
				if (p.Y < m_pFileList->m_sGrid.Y)
				{
					int index{ m_pFileList->GridToIndex(p) };
					if (index < (int)m_pFileList->m_aItems.size())
						PostKey(index, shift);
				}
			}
		}

		void CFileListService::ProcessKeySpace()
		{
			if (m_pFileList->m_iActiveIndex >= 0)
				PostKey(m_pFileList->m_iActiveIndex, false);
		}

		void CFileListService::ProcessKeyA()
		{
			if (m_pFileList->m_aItems.size() > 0)
			{
				SelectRange(0, (int)m_pFileList->m_aItems.size() - 1);
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Timer notification
		void CFileListService::NotifyOnTimer(const PlatformHandle id)
		{
			if (m_pFileList->m_eDownElement == CFileList::Element::List)
			{
				CLockRepaint lock{ m_pFileList };
				ProcessMove(m_pFileList->FormToLocal((PointF)m_pFileList->getForm()->ScreenToClient(Application->Mouse->getPosition())));
			}
		}
	#pragma endregion
	}
}