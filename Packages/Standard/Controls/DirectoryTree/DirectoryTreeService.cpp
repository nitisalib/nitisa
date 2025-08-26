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
		CDirectoryTreeService::CDirectoryTreeService(CDirectoryTree *directory_tree) :
			CControlService(directory_tree),
			m_pDirectoryTree{ directory_tree },
			m_hTimer{ nullptr }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CDirectoryTreeService::CancelDown(const bool check_capture)
		{
			m_pDirectoryTree->m_eDownElement = CDirectoryTree::Element::None;
			if (m_hTimer)
			{
				m_pDirectoryTree->getForm()->DeleteTimer(m_hTimer);
				m_hTimer = nullptr;
			}
			if (check_capture && m_pDirectoryTree->isCaptureMouse())
				m_pDirectoryTree->getForm()->ReleaseCaptureMouse();
		}

		PointF CDirectoryTreeService::FormToHScroll(const PointF &pos)
		{
			PointF p{ (PointF)m_pDirectoryTree->FormToLocal(pos) };
			return PointF{ p.X - m_pDirectoryTree->m_sBorderWidth.Left, p.Y - (m_pDirectoryTree->getHeight() - m_pDirectoryTree->m_sBorderWidth.Bottom - m_pDirectoryTree->getHScroll()->getHeight()) };
		}

		PointF CDirectoryTreeService::FormToVScroll(const PointF &pos)
		{
			PointF p{ m_pDirectoryTree->FormToLocal(pos) };
			return PointF{ p.X - (m_pDirectoryTree->getWidth() - m_pDirectoryTree->m_sBorderWidth.Right - m_pDirectoryTree->getVScroll()->getWidth()), p.Y - m_pDirectoryTree->m_sBorderWidth.Top };
		}

		bool CDirectoryTreeService::FindActiveItem(IListItem *parent, PointF &current, PointF &item_size, const float line_height)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->QueryService()->getRequiredSize() };
					float height{ ntl::IsGreater<float>(m_pDirectoryTree->m_fItemHeight, 0) ? m_pDirectoryTree->m_fItemHeight : (ntl::IsEqual<float>(m_pDirectoryTree->m_fItemHeight, 0) ? line_height : size.Y) };
					if (parent->getItem(i)->isActive())
					{
						item_size = PointF{ size.X, height };
						return true;
					}

					current.Y += height;
					if (parent->getItem(i)->getItemCount() > 0 && !m_pDirectoryTree->m_aItems[m_pDirectoryTree->FindItemIndex(parent->getItem(i))].Folded)
					{
						current.X += height;
						bool b{ FindActiveItem(parent->getItem(i), current, item_size, line_height) };
						if (b)
							return true;
						current.X -= height;
					}
				}
			return false;
		}

		void CDirectoryTreeService::ScrollToActiveItem()
		{
			PointF current{
				m_pDirectoryTree->m_sBorderWidth.Left + m_pDirectoryTree->m_sPadding.Left - (m_pDirectoryTree->getHScroll()->isEnabled() ? m_pDirectoryTree->getHScroll()->getScroll() : 0),
				m_pDirectoryTree->m_sBorderWidth.Top + m_pDirectoryTree->m_sPadding.Top - (m_pDirectoryTree->getVScroll()->isEnabled() ? m_pDirectoryTree->getVScroll()->getScroll() : 0)
			}, size;
			if (FindActiveItem(&m_pDirectoryTree->m_cRootItem, current, size, m_pDirectoryTree->getFont()->getPlatformFont(m_pDirectoryTree->getForm()->getRenderer())->getStringSize(L"Wy", m_pDirectoryTree->getFont()->Distance).Y))
			{
				RectF client{ m_pDirectoryTree->getClientRect() };
				if (current.X + size.X >= client.Right)
					m_pDirectoryTree->getHScroll()->setScroll(m_pDirectoryTree->getHScroll()->getScroll() + (current.X + size.X - client.Right));
				if (current.X < client.Left)
					m_pDirectoryTree->getHScroll()->setScroll(m_pDirectoryTree->getHScroll()->getScroll() - (client.Left - current.X));

				if (current.Y + size.Y >= client.Bottom)
					m_pDirectoryTree->getVScroll()->setScroll(m_pDirectoryTree->getVScroll()->getScroll() + (current.Y + size.Y - client.Bottom));
				if (current.Y < client.Top)
					m_pDirectoryTree->getVScroll()->setScroll(m_pDirectoryTree->getVScroll()->getScroll() - (client.Top - current.Y));
			}
		}

		IListItem *CDirectoryTreeService::FindActiveItem(IListItem *parent)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					if (parent->getItem(i)->isActive())
						return parent->getItem(i);
					IListItem *result{ FindActiveItem(parent->getItem(i)) };
					if (result)
						return result;
				}
			return nullptr;
		}
	#pragma endregion

	#pragma region State change notifications
		void CDirectoryTreeService::NotifyOnAttach()
		{
			if (m_pDirectoryTree->m_pVScroll)
				m_pDirectoryTree->m_pVScroll->NotifyOnAttach();
			if (m_pDirectoryTree->m_pHScroll)
				m_pDirectoryTree->m_pHScroll->NotifyOnAttach();
			m_pDirectoryTree->Update();
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
		}

		void CDirectoryTreeService::NotifyOnDetaching()
		{
			if (m_pDirectoryTree->m_pVScroll)
				m_pDirectoryTree->m_pVScroll->NotifyOnDeactivate();
			if (m_pDirectoryTree->m_pHScroll)
				m_pDirectoryTree->m_pHScroll->NotifyOnDeactivate();
		}

		void CDirectoryTreeService::NotifyOnDetach()
		{
			m_pDirectoryTree->m_pFileList = nullptr;
		}

		void CDirectoryTreeService::NotifyOnFreeResources()
		{
			if (m_pDirectoryTree->m_pCanvas)
			{
				m_pDirectoryTree->m_pCanvas->Release();
				m_pDirectoryTree->m_pCanvas = nullptr;
			}
		}
	#pragma endregion

	#pragma region Component notifications
		void CDirectoryTreeService::NotifyOnComponentDetach(IComponent *component)
		{
			if (m_pDirectoryTree->m_pFileList && cast<IFileList*>(component) == m_pDirectoryTree->m_pFileList)
				m_pDirectoryTree->m_pFileList = nullptr;
		}
	#pragma endregion

	#pragma region Control notifications
		void CDirectoryTreeService::NotifyOnControlDetach(IControl *control)
		{
			if (m_pDirectoryTree->m_pFileList && cast<IFileList*>(control) == m_pDirectoryTree->m_pFileList)
				m_pDirectoryTree->m_pFileList = nullptr;
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CDirectoryTreeService::NotifyOnParentStyleChange()
		{
			if (m_pDirectoryTree->getStyle())
			{
				m_pDirectoryTree->UpdateFromStyle(m_pDirectoryTree->getStyle());
				if (m_pDirectoryTree->m_pCanvas)
					m_pDirectoryTree->m_pCanvas->setValid(false);
			}
		}

		void CDirectoryTreeService::NotifyOnParentFontChange()
		{
			m_pDirectoryTree->Update();
			m_pDirectoryTree->UpdateHoveredElement();
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CDirectoryTreeService::NotifyOnEnable()
		{
			m_pDirectoryTree->getHScroll()->setEnabled(true);
			m_pDirectoryTree->getVScroll()->setEnabled(true);
			m_pDirectoryTree->Update();
			m_pDirectoryTree->UpdateHoveredElement();
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
		}

		void CDirectoryTreeService::NotifyOnDisable()
		{
			m_pDirectoryTree->getHScroll()->setEnabled(false);
			m_pDirectoryTree->getVScroll()->setEnabled(false);
			m_pDirectoryTree->UpdateHoveredElement();
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
		}

		void CDirectoryTreeService::NotifyOnResize()
		{
			m_pDirectoryTree->Update();
			m_pDirectoryTree->UpdateHoveredElement();
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
		}

		void CDirectoryTreeService::NotifyOnStyleChange()
		{
			if (m_pDirectoryTree->getStyle())
			{
				m_pDirectoryTree->UpdateFromStyle(m_pDirectoryTree->getStyle());
				if (m_pDirectoryTree->m_pCanvas)
					m_pDirectoryTree->m_pCanvas->setValid(false);
			}
		}

		void CDirectoryTreeService::NotifyOnFontChange()
		{
			m_pDirectoryTree->Update();
			m_pDirectoryTree->UpdateHoveredElement();
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
		}

		void CDirectoryTreeService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
			m_pDirectoryTree->Repaint(false);
		}

		void CDirectoryTreeService::NotifyOnKillFocus()
		{
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
			m_pDirectoryTree->Repaint(false);
		}

		void CDirectoryTreeService::NotifyOnSetCaptureMouse()
		{
			m_hTimer = m_pDirectoryTree->getForm()->CreateTimer(this, m_pDirectoryTree->m_fScrollInterval);
		}

		void CDirectoryTreeService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CDirectoryTreeService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pDirectoryTree->getWidth(), 0) && ntl::IsGreater<float>(m_pDirectoryTree->getHeight(), 0))
				m_pDirectoryTree->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CDirectoryTreeService::NotifyOnMouseHover(const MessagePosition &m)
		{
			m_pDirectoryTree->UpdateHoveredElement(m_pDirectoryTree->FormToLocal(m.Position));
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
			m_pDirectoryTree->Repaint(false);
		}

		void CDirectoryTreeService::NotifyOnMouseLeave()
		{
			m_pDirectoryTree->UpdateHoveredElement();
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
			m_pDirectoryTree->Repaint(false);
		}

		void CDirectoryTreeService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			switch (m_pDirectoryTree->m_eDownElement)
			{
			case CDirectoryTree::Element::HScroll:
				if (m_pDirectoryTree->getHScroll()->NotifyOnMouseMove(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pDirectoryTree->m_pCanvas)
						m_pDirectoryTree->m_pCanvas->setValid(false);
					m_pDirectoryTree->Repaint(false);
				}
				return;
			case CDirectoryTree::Element::VScroll:
				if (m_pDirectoryTree->getVScroll()->NotifyOnMouseMove(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pDirectoryTree->m_pCanvas)
						m_pDirectoryTree->m_pCanvas->setValid(false);
					m_pDirectoryTree->Repaint(false);
				}
				return;
			default:
				break;
			}
			if (m_pDirectoryTree->isEnabled(true))
			{
				PointF p{ m_pDirectoryTree->FormToLocal(m.Position) };
				bool changed{ m_pDirectoryTree->UpdateHoveredElement(p) };
				if (changed)
				{
					if (m_pDirectoryTree->m_pCanvas)
						m_pDirectoryTree->m_pCanvas->setValid(false);
					m_pDirectoryTree->Repaint(false);
				}
				else
				{
					switch (m_pDirectoryTree->m_eHoveredElement)
					{
					case CDirectoryTree::Element::HScroll:
						if (m_pDirectoryTree->getHScroll()->NotifyOnMouseMove(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						{
							if (m_pDirectoryTree->m_pCanvas)
								m_pDirectoryTree->m_pCanvas->setValid(false);
							m_pDirectoryTree->Repaint(false);
						}
						break;
					case CDirectoryTree::Element::VScroll:
						if (m_pDirectoryTree->getVScroll()->NotifyOnMouseMove(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						{
							if (m_pDirectoryTree->m_pCanvas)
								m_pDirectoryTree->m_pCanvas->setValid(false);
							m_pDirectoryTree->Repaint(false);
						}
						break;
					default:
						break;
					}
				}
			}
		}

		void CDirectoryTreeService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pDirectoryTree->m_eDownElement = CDirectoryTree::Element::None;
			if (m_pDirectoryTree->isEnabled(true))
			{
				if (!m_pDirectoryTree->isCaptureMouse() && !m.Middle && !m.Right)
				{
					switch (m_pDirectoryTree->m_eHoveredElement)
					{
					case CDirectoryTree::Element::Folder:
					{
						int index{ m_pDirectoryTree->FindItemIndex(m_pDirectoryTree->m_pHoveredItem) };
						m_pDirectoryTree->m_aItems[index].Folded = !m_pDirectoryTree->m_aItems[index].Folded;
						if (!m_pDirectoryTree->m_aItems[index].Folded)
							m_pDirectoryTree->Rescan(index);
						m_pDirectoryTree->Update();
						if (m_pDirectoryTree->m_pCanvas)
							m_pDirectoryTree->m_pCanvas->setValid(false);
						m_pDirectoryTree->Repaint(false);
					}
					break;
					case CDirectoryTree::Element::HScroll:
						if (m_pDirectoryTree->getHScroll()->NotifyOnMouseLeftDown(FormToHScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						{
							m_pDirectoryTree->m_eDownElement = CDirectoryTree::Element::HScroll;
							m_pDirectoryTree->getForm()->CaptureMouse(m_pDirectoryTree, true);
							if (m_pDirectoryTree->m_pCanvas)
								m_pDirectoryTree->m_pCanvas->setValid(false);
							m_pDirectoryTree->Repaint(false);
						}
						break;
					case CDirectoryTree::Element::VScroll:
						if (m_pDirectoryTree->getVScroll()->NotifyOnMouseLeftDown(FormToVScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						{
							m_pDirectoryTree->m_eDownElement = CDirectoryTree::Element::VScroll;
							m_pDirectoryTree->getForm()->CaptureMouse(m_pDirectoryTree, true);
							if (m_pDirectoryTree->m_pCanvas)
								m_pDirectoryTree->m_pCanvas->setValid(false);
							m_pDirectoryTree->Repaint(false);
						}
						break;
					case CDirectoryTree::Element::Item:
						if (m.Shift)
						{
							IListItem *active{ m_pDirectoryTree->FindActiveItem(&m_pDirectoryTree->m_cRootItem) };
							if (active && m_pDirectoryTree->m_pHoveredItem->getParent() == active->getParent())
							{
								int active_index{ -1 }, hovered_index{ -1 };
								for (int i = 0; i < active->getParent()->getItemCount(); i++)
								{
									if (active->getParent()->getItem(i) == active)
										active_index = i;
									if (active->getParent()->getItem(i) == m_pDirectoryTree->m_pHoveredItem)
										hovered_index = i;
								}
								bool changed{ m_pDirectoryTree->DeselectAllExceptParent(active->getParent()) };
								if (active_index > hovered_index)
									ntl::Swap<int>(active_index, hovered_index);
								for (int i = 0; i < active->getParent()->getItemCount(); i++)
								{
									if ((i < active_index || i > hovered_index) && active->getParent()->getItem(i)->isSelected())
										changed = active->getParent()->getItem(i)->setSelected(false) || changed;
									if (i >= active_index && i <= hovered_index && !active->getParent()->getItem(i)->isSelected())
										changed = active->getParent()->getItem(i)->setSelected(true) || changed;
								}
								if (changed)
								{
									if (m_pDirectoryTree->m_pCanvas)
										m_pDirectoryTree->m_pCanvas->setValid(false);
									m_pDirectoryTree->Repaint(false);
								}
							}
						}
						else
						{
							bool changed;
							if (m.Ctrl)
								changed = m_pDirectoryTree->m_pHoveredItem->setSelected(!m_pDirectoryTree->m_pHoveredItem->isSelected());
							else
							{
								changed = m_pDirectoryTree->m_pHoveredItem->setSelected(true);
								m_pDirectoryTree->DeselectAllExceptItem(&m_pDirectoryTree->m_cRootItem, m_pDirectoryTree->m_pHoveredItem);
							}
							if (m_pDirectoryTree->m_pHoveredItem->setActive(true))
							{
								m_pDirectoryTree->DeactivateAllExceptItem(&m_pDirectoryTree->m_cRootItem, m_pDirectoryTree->m_pHoveredItem);
								changed = true;
							}
							if (changed)
							{
								if (m_pDirectoryTree->m_pCanvas)
									m_pDirectoryTree->m_pCanvas->setValid(false);
								m_pDirectoryTree->Repaint(false);
							}
						}
						break;
					default:
						break;
					}
				}
				else
					CancelDown(true);
			}
		}

		void CDirectoryTreeService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pDirectoryTree->isCaptureMouse())
			{
				switch (m_pDirectoryTree->m_eDownElement)
				{
				case CDirectoryTree::Element::HScroll:
					if (m_pDirectoryTree->getHScroll()->NotifyOnMouseLeftUp(FormToHScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pDirectoryTree->m_pCanvas)
							m_pDirectoryTree->m_pCanvas->setValid(false);
						m_pDirectoryTree->Repaint(false);
					}
					break;
				case CDirectoryTree::Element::VScroll:
					if (m_pDirectoryTree->getVScroll()->NotifyOnMouseLeftUp(FormToVScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pDirectoryTree->m_pCanvas)
							m_pDirectoryTree->m_pCanvas->setValid(false);
						m_pDirectoryTree->Repaint(false);
					}
					break;
				default:
					if (!m.Ctrl && m_pDirectoryTree->DeselectAllExceptItem(&m_pDirectoryTree->m_cRootItem, m_pDirectoryTree->m_pHoveredItem))
					{
						if (m_pDirectoryTree->m_pCanvas)
							m_pDirectoryTree->m_pCanvas->setValid(false);
						m_pDirectoryTree->Repaint(false);
					}
				}
			}
			CancelDown(true);
		}

		void CDirectoryTreeService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDirectoryTreeService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDirectoryTreeService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDirectoryTreeService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDirectoryTreeService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDirectoryTreeService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDirectoryTreeService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDirectoryTreeService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pDirectoryTree->isEnabled(true) && !m_pDirectoryTree->isCaptureMouse())
				switch (m_pDirectoryTree->m_eHoveredElement)
				{
				case CDirectoryTree::Element::VScroll:
					if (m_pDirectoryTree->getVScroll()->isEnabled() && m_pDirectoryTree->getVScroll()->NotifyOnMouseVerticalWheel(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
					{
						m_pDirectoryTree->UpdateHoveredElement(m_pDirectoryTree->FormToLocal(m.Position));
						if (m_pDirectoryTree->m_pCanvas)
							m_pDirectoryTree->m_pCanvas->setValid(false);
						m_pDirectoryTree->Repaint(false);
					}
					break;
				case CDirectoryTree::Element::HScroll:
					if (m_pDirectoryTree->getHScroll()->isEnabled() && m_pDirectoryTree->getHScroll()->NotifyOnMouseVerticalWheel(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
					{
						m_pDirectoryTree->UpdateHoveredElement(m_pDirectoryTree->FormToLocal(m.Position));
						if (m_pDirectoryTree->m_pCanvas)
							m_pDirectoryTree->m_pCanvas->setValid(false);
						m_pDirectoryTree->Repaint(false);
					}
					break;
				default:
					if (m_pDirectoryTree->getVScroll()->isEnabled() && m_pDirectoryTree->getVScroll()->setScroll(m_pDirectoryTree->getVScroll()->getScroll() + m_pDirectoryTree->getVScroll()->getDeltaMedium() * (m.Delta > 0 ? -1 : 1)))
					{
						m_pDirectoryTree->UpdateHoveredElement(m_pDirectoryTree->FormToLocal(m.Position));
						if (m_pDirectoryTree->m_pCanvas)
							m_pDirectoryTree->m_pCanvas->setValid(false);
						m_pDirectoryTree->Repaint(false);
					}
				}
		}

		void CDirectoryTreeService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pDirectoryTree->isEnabled(true) && !m_pDirectoryTree->isCaptureMouse())
				switch (m_pDirectoryTree->m_eHoveredElement)
				{
				case CDirectoryTree::Element::VScroll:
					if (m_pDirectoryTree->getVScroll()->isEnabled() && m_pDirectoryTree->getVScroll()->NotifyOnMouseHorizontalWheel(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
					{
						m_pDirectoryTree->UpdateHoveredElement(m_pDirectoryTree->FormToLocal(m.Position));
						if (m_pDirectoryTree->m_pCanvas)
							m_pDirectoryTree->m_pCanvas->setValid(false);
						m_pDirectoryTree->Repaint(false);
					}
					break;
				case CDirectoryTree::Element::HScroll:
					if (m_pDirectoryTree->getHScroll()->isEnabled() && m_pDirectoryTree->getHScroll()->NotifyOnMouseHorizontalWheel(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
					{
						m_pDirectoryTree->UpdateHoveredElement(m_pDirectoryTree->FormToLocal(m.Position));
						if (m_pDirectoryTree->m_pCanvas)
							m_pDirectoryTree->m_pCanvas->setValid(false);
						m_pDirectoryTree->Repaint(false);
					}
					break;
				default:
					if (m_pDirectoryTree->getHScroll()->isEnabled() && m_pDirectoryTree->getHScroll()->setScroll(m_pDirectoryTree->getHScroll()->getScroll() + m_pDirectoryTree->getHScroll()->getDeltaMedium() * (m.Delta > 0 ? -1 : 1)))
					{
						m_pDirectoryTree->UpdateHoveredElement(m_pDirectoryTree->FormToLocal(m.Position));
						if (m_pDirectoryTree->m_pCanvas)
							m_pDirectoryTree->m_pCanvas->setValid(false);
						m_pDirectoryTree->Repaint(false);
					}
				}
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CDirectoryTreeService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pDirectoryTree->isEnabled(true))
			{
				bool numlock{ Application->Keyboard->isToggled(Key::NumLock) }, changed{ false };
				switch (m.Key)
				{
				case Key::Up:
				case Key::Numpad8:
					if (m.Key == Key::Up || !numlock)
						changed = ProcessKeyUp();
					break;
				case Key::Down:
				case Key::Numpad2:
					if (m.Key == Key::Down || !numlock)
						changed = ProcessKeyDown();
					break;
				case Key::Left:
				case Key::Numpad4:
					if (m.Key == Key::Left || !numlock)
						changed = ProcessKeyLeft();
					break;
				case Key::Right:
				case Key::Numpad6:
					if (m.Key == Key::Right || !numlock)
						changed = ProcessKeyRight();
					break;
				case Key::Home:
				case Key::Numpad7:
					if (m.Key == Key::Home || !numlock)
						changed = ProcessKeyHome();
					break;
				case Key::End:
				case Key::Numpad1:
					if (m.Key == Key::End || !numlock)
						changed = ProcessKeyEnd();
					break;
				default:
					break;
				}
				if (changed)
				{
					ScrollToActiveItem();
					m_pDirectoryTree->UpdateHoveredElement();
					if (m_pDirectoryTree->m_pCanvas)
						m_pDirectoryTree->m_pCanvas->setValid(false);
					m_pDirectoryTree->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region Process keys
		bool CDirectoryTreeService::ProcessKeyUp()
		{
			IListItem *active{ FindActiveItem(&m_pDirectoryTree->m_cRootItem) };
			if (active)
			{
				int active_index{ -1 };
				for (int i = 0; i < active->getParent()->getItemCount(); i++)
					if (active->getParent()->getItem(i) == active)
					{
						active_index = i;
						break;
					}
				active_index--;
				if (active_index >= 0)
				{
					active->getParent()->getItem(active_index)->setActive(true);
					active->getParent()->getItem(active_index)->setSelected(true);
					m_pDirectoryTree->DeselectAllExceptItem(&m_pDirectoryTree->m_cRootItem, active->getParent()->getItem(active_index));
					return true;
				}
			}
			else if (m_pDirectoryTree->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ m_pDirectoryTree->m_cRootItem.getItemCount() - 1 };
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setActive(true);
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setSelected(true);
				return true;
			}
			return false;
		}

		bool CDirectoryTreeService::ProcessKeyDown()
		{
			IListItem *active{ FindActiveItem(&m_pDirectoryTree->m_cRootItem) };
			if (active)
			{
				int active_index{ -1 };
				for (int i = 0; i < active->getParent()->getItemCount(); i++)
					if (active->getParent()->getItem(i) == active)
					{
						active_index = i;
						break;
					}
				active_index++;
				if (active_index < active->getParent()->getItemCount())
				{
					active->getParent()->getItem(active_index)->setActive(true);
					active->getParent()->getItem(active_index)->setSelected(true);
					m_pDirectoryTree->DeselectAllExceptItem(&m_pDirectoryTree->m_cRootItem, active->getParent()->getItem(active_index));
					return true;
				}
			}
			else if (m_pDirectoryTree->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ 0 };
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setActive(true);
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setSelected(true);
				return true;
			}
			return false;
		}

		bool CDirectoryTreeService::ProcessKeyLeft()
		{
			IListItem *active{ FindActiveItem(&m_pDirectoryTree->m_cRootItem) };
			if (active)
			{
				if (active->getParent() != &m_pDirectoryTree->m_cRootItem)
				{
					active->getParent()->setActive(true);
					active->getParent()->setSelected(true);
					m_pDirectoryTree->DeselectAllExceptItem(&m_pDirectoryTree->m_cRootItem, active->getParent());
					return true;
				}
			}
			else if (m_pDirectoryTree->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ 0 };
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setActive(true);
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setSelected(true);
				return true;
			}
			return false;
		}

		bool CDirectoryTreeService::ProcessKeyRight()
		{
			IListItem *active{ FindActiveItem(&m_pDirectoryTree->m_cRootItem) };
			if (active)
			{
				if (active->getItemCount() > 0)
				{
					int active_index{ 0 };
					active->getItem(active_index)->setActive(true);
					active->getItem(active_index)->setSelected(true);
					m_pDirectoryTree->DeselectAllExceptItem(&m_pDirectoryTree->m_cRootItem, active->getItem(active_index));
					int index{ m_pDirectoryTree->FindItemIndex(active) };
					if (m_pDirectoryTree->m_aItems[index].Folded)
					{
						m_pDirectoryTree->m_aItems[index].Folded = false;
						m_pDirectoryTree->Rescan(index);
						m_pDirectoryTree->Update();
					}
					return true;
				}
			}
			else if (m_pDirectoryTree->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ 0 };
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setActive(true);
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setSelected(true);
				return true;
			}
			return false;
		}

		bool CDirectoryTreeService::ProcessKeyHome()
		{
			IListItem *active{ FindActiveItem(&m_pDirectoryTree->m_cRootItem) };
			if (active)
			{
				int active_index{ 0 };
				if (active_index < active->getParent()->getItemCount() && active->getParent()->getItem(active_index) != active)
				{
					active->getParent()->getItem(active_index)->setActive(true);
					active->getParent()->getItem(active_index)->setSelected(true);
					m_pDirectoryTree->DeselectAllExceptItem(&m_pDirectoryTree->m_cRootItem, active->getParent()->getItem(active_index));
					return true;
				}
			}
			else if (m_pDirectoryTree->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ 0 };
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setActive(true);
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setSelected(true);
				return true;
			}
			return false;
		}

		bool CDirectoryTreeService::ProcessKeyEnd()
		{
			IListItem *active{ FindActiveItem(&m_pDirectoryTree->m_cRootItem) };
			if (active)
			{
				int active_index{ active->getParent()->getItemCount() - 1 };
				if (active_index >= 0 && active->getParent()->getItem(active_index) != active)
				{
					active->getParent()->getItem(active_index)->setActive(true);
					active->getParent()->getItem(active_index)->setSelected(true);
					m_pDirectoryTree->DeselectAllExceptItem(&m_pDirectoryTree->m_cRootItem, active->getParent()->getItem(active_index));
					return true;
				}
			}
			else if (m_pDirectoryTree->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ m_pDirectoryTree->m_cRootItem.getItemCount() - 1 };
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setActive(true);
				m_pDirectoryTree->m_cRootItem.getItem(active_index)->setSelected(true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Timer notification
		void CDirectoryTreeService::NotifyOnTimer(const PlatformHandle id)
		{
			if (m_pDirectoryTree->m_eDownElement != CDirectoryTree::Element::HScroll && m_pDirectoryTree->m_eDownElement != CDirectoryTree::Element::VScroll)
			{
				PointF p{ m_pDirectoryTree->FormToLocal((PointF)m_pDirectoryTree->getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				RectF client{ m_pDirectoryTree->getClientRect() };
				float delta;
				bool changed{ false };
				if (p.X < client.Left || p.X >= client.Right)
				{
					if (m_pDirectoryTree->getHScroll()->isEnabled())
					{
						delta = m_pDirectoryTree->m_fScrollDelta * (p.X < client.Left ? -1 : 1);
						changed = m_pDirectoryTree->getHScroll()->setScroll(m_pDirectoryTree->getHScroll()->getScroll() + delta) || changed;
					}
				}
				if (p.Y < client.Top || p.Y >= client.Bottom)
				{
					if (m_pDirectoryTree->getVScroll()->isEnabled())
					{
						delta = m_pDirectoryTree->m_fScrollDelta * (p.Y < client.Top ? -1 : 1);
						changed = m_pDirectoryTree->getVScroll()->setScroll(m_pDirectoryTree->getVScroll()->getScroll() + delta) || changed;
					}
				}
				if (changed)
				{
					m_pDirectoryTree->UpdateHoveredElement(p);
					if (m_pDirectoryTree->m_pCanvas)
						m_pDirectoryTree->m_pCanvas->setValid(false);
					m_pDirectoryTree->Repaint(false);
				}
			}
		}
	#pragma endregion
	}
}