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
	namespace ide
	{
	#pragma region Constructor & destructor
		CEventEditorService::CEventEditorService(CEventEditor *editor) :
			CControlService(editor),
			m_pEditor{ editor }
		{

		}
	#pragma endregion

	#pragma region Helpers
		PointF CEventEditorService::FormToScroll(const PointF &position)
		{
			PointF p{ m_pEditor->FormToLocal(position) };
			return PointF{ p.X - m_pEditor->getWidth() + m_pEditor->m_sBorderWidth.Right + m_pEditor->getScroll()->getSize().X, p.Y - m_pEditor->m_sBorderWidth.Top };
		}

		void CEventEditorService::CancelDown(const bool check_capture)
		{
			if (m_pEditor->m_eDownElement != CEventEditor::Element::None)
			{
				if (m_pEditor->m_pHandler)
					m_pEditor->m_pHandler->NotifyOnMouseDownCancel();
				switch (m_pEditor->m_eDownElement)
				{
				case CEventEditor::Element::Scroll:
					m_pEditor->getScroll()->NotifyOnMouseDownCancel();
					break;
				default:
					break;
				}
				m_pEditor->m_eDownElement = CEventEditor::Element::None;
			}
			if (check_capture && m_pEditor->isCaptureMouse() && (!m_pEditor->m_pHandler || !m_pEditor->isActive()))
				m_pEditor->getForm()->ReleaseCaptureMouse();
		}

		void CEventEditorService::ProcessMoveCaptionSeparator(const PointF &position)
		{
			PointF range;
			range.X = m_pEditor->m_sBorderWidth.Left;
			range.Y = m_pEditor->getWidth() - m_pEditor->m_sBorderWidth.Right - m_pEditor->getScroll()->getSize().X;
			if (ntl::IsGreater<float>(range.Y, range.X))
			{
				float x{ position.X - m_fDownCaptionSeparatorDisp - range.X };
				x = ntl::Clamp<float>(x / (range.Y - range.X), 0, 1);
				if (ntl::IsNotEqual<float>(x, m_pEditor->m_fCaptionWidth))
				{
					m_pEditor->m_fCaptionWidth = x;
					if (m_pEditor->m_pHandler)
						m_pEditor->m_pHandler->setSize(PointF{ m_pEditor->CalculateHandlerWidth(), m_pEditor->m_fRowHeight });
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		bool CEventEditorService::FocusHandler(const int index)
		{
			if (index != m_pEditor->m_iFocusedEventIndex)
			{
				m_pEditor->FreeHandler();
				m_pEditor->m_iFocusedEventIndex = index;
				m_pEditor->m_pHandler = &m_pEditor->m_cDropDown;
				UpdateHandlerItems(m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]);
				m_pEditor->m_pHandler->setText(m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]->getValue());
				m_pEditor->m_pHandler->setSize(PointF{ m_pEditor->CalculateHandlerWidth(), m_pEditor->m_fRowHeight });
				m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerAndSetOpenDirectionY();
				m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
				m_pEditor->m_pHandler->setFocused(true);
				return true;
			}
			return false;
		}

		bool CEventEditorService::ScrollToHandler()
		{
			if (m_pEditor->m_pHandler && m_pEditor->getScroll()->isEnabled())
			{
				if (ntl::IsLess<float>(m_pEditor->m_fHandlerY, m_pEditor->m_sBorderWidth.Top))
				{
					if (m_pEditor->getScroll()->setScroll(m_pEditor->getScroll()->getScroll() - m_pEditor->m_sBorderWidth.Top - m_pEditor->m_fHandlerY))
					{
						m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerAndSetOpenDirectionY();
						m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
						return true;
					}
				}
				else if (ntl::IsGreaterOrEqual<float>(m_pEditor->m_fHandlerY + m_pEditor->m_fRowHeight, m_pEditor->getHeight() - m_pEditor->m_sBorderWidth.Bottom))
					if (m_pEditor->getScroll()->setScroll(m_pEditor->getScroll()->getScroll() + m_pEditor->m_fHandlerY + m_pEditor->m_fRowHeight - m_pEditor->getHeight() + m_pEditor->m_sBorderWidth.Bottom))
					{
						m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerAndSetOpenDirectionY();
						m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
						return true;
					}
			}
			return false;
		}

		void CEventEditorService::UpdateHandlerItems(IEvent *event)
		{
			m_pEditor->m_pHandler->DeleteItems();
			IEditor *editor{ Application->Editor };
			if (editor)
			{
				StringArray items;
				for (int i = 0; i < editor->getPackageCount(); i++)
				{
					for (int j = 0; j < editor->getPackage(i)->getCreatedComponentCount(); j++)
					{
						IComponent *component;
						IPackageComponent *package_component;
						IPropertyList *properties;
						IEventList *events;
						if (editor->getPackage(i)->getCreatedComponent(j, &component, &package_component, &properties, &events))
						{
							if (events)
								for (int k = 0; k < events->getCount(); k++)
								{
									if (!events->getEvent(k)->getValue().empty() && events->getEvent(k)->getSignature() == event->getSignature())
										items.push_back(events->getEvent(k)->getValue());
								}
						}
					}
					for (int j = 0; j < editor->getPackage(i)->getCreatedControlCount(); j++)
					{
						IControl *control;
						IPackageControl *package_control;
						IPropertyList *properties;
						IEventList *events;
						if (editor->getPackage(i)->getCreatedControl(j, &control, &package_control, &properties, &events))
						{
							if (events)
								for (int k = 0; k < events->getCount(); k++)
								{
									if (!events->getEvent(k)->getValue().empty() && events->getEvent(k)->getSignature() == event->getSignature())
										items.push_back(events->getEvent(k)->getValue());
								}
						}
					}
				}
				for (auto pos : m_pEditor->m_aEventLists)
					for (int i = 0; i < pos->getCount(); i++)
						if (!pos->getEvent(i)->getValue().empty() && pos->getEvent(i)->getSignature() == event->getSignature())
							items.push_back(pos->getEvent(i)->getValue());
				std::sort(items.begin(), items.end());
				String last;
				for (auto item : items)
					if (last != item)
					{
						m_pEditor->m_pHandler->AddItem(new standard::CListItemLabel(item));
						last = item;
					}
			}
		}
	#pragma endregion

	#pragma region Process keys
		void CEventEditorService::ProcessKeyUp()
		{
			if (m_pEditor->m_aEvents.size() > 0)
			{
				int new_index;
				if (!m_pEditor->m_pHandler)
					new_index = (int)m_pEditor->m_aEvents.size() - 1;
				else
					new_index = m_pEditor->m_iFocusedEventIndex - 1;
				if (new_index != m_pEditor->m_iFocusedEventIndex)
				{
					FocusHandler(new_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CEventEditorService::ProcessKeyDown()
		{
			if (m_pEditor->m_aEvents.size() > 0)
			{
				int new_index;
				if (!m_pEditor->m_pHandler)
					new_index = 0;
				else
					new_index = m_pEditor->m_iFocusedEventIndex + 1;
				if (new_index != m_pEditor->m_iFocusedEventIndex)
				{
					FocusHandler(new_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CEventEditorService::ProcessKeyPageUp()
		{
			if (m_pEditor->m_aEvents.size() > 0)
			{
				int new_index;
				int page_size{ ntl::Max<int>(1, ntl::Round<int>((m_pEditor->getHeight() - m_pEditor->m_sBorderWidth.Top - m_pEditor->m_sBorderWidth.Bottom) / m_pEditor->m_fRowHeight) - 1) };
				if (!m_pEditor->m_pHandler)
					new_index = (int)m_pEditor->m_aEvents.size() - 1;
				else
					new_index = ntl::Max<int>(0, m_pEditor->m_iFocusedEventIndex - page_size);
				if (new_index != m_pEditor->m_iFocusedEventIndex)
				{
					FocusHandler(new_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CEventEditorService::ProcessKeyPageDown()
		{
			if (m_pEditor->m_aEvents.size() > 0)
			{
				int new_index;
				int page_size{ ntl::Max<int>(1, ntl::Round<int>((m_pEditor->getHeight() - m_pEditor->m_sBorderWidth.Top - m_pEditor->m_sBorderWidth.Bottom) / m_pEditor->m_fRowHeight) - 1) };
				if (!m_pEditor->m_pHandler)
					new_index = 0;
				else
					new_index = ntl::Min<int>((int)m_pEditor->m_aEvents.size() - 1, m_pEditor->m_iFocusedEventIndex - page_size);
				if (new_index != m_pEditor->m_iFocusedEventIndex)
				{
					FocusHandler(new_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CEventEditorService::ProcessKeyHome()
		{
			if (m_pEditor->m_aEvents.size() > 0)
			{
				int new_index{ 0 };
				if (new_index != m_pEditor->m_iFocusedEventIndex)
				{
					FocusHandler(new_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CEventEditorService::ProcessKeyEnd()
		{
			if (m_pEditor->m_aEvents.size() > 0)
			{
				int new_index{ (int)m_pEditor->m_aEvents.size() - 1 };
				if (new_index != m_pEditor->m_iFocusedEventIndex)
				{
					FocusHandler(new_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CEventEditorService::NotifyOnAttach()
		{
			if (m_pEditor->getForm())
			{
				m_pEditor->getScroll()->NotifyOnAttach();
				m_pEditor->m_cDropDown.NotifyOnAttach();
			}
		}

		void CEventEditorService::NotifyOnDetaching()
		{
			m_pEditor->FreeHandler();
		}

		void CEventEditorService::NotifyOnFreeResources()
		{
			m_pEditor->m_cDropDown.NotifyOnFreeResources();
			if (m_pEditor->m_pScroll)
				m_pEditor->m_pScroll->NotifyOnFreeResources();
			if (m_pEditor->m_pCanvas)
			{
				m_pEditor->m_pCanvas->Release();
				m_pEditor->m_pCanvas = nullptr;
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CEventEditorService::NotifyOnParentStyleChange()
		{
			if (m_pEditor->getStyle())
			{
				m_pEditor->UpdateFormStyle(m_pEditor->getStyle());
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
			}
		}

		void CEventEditorService::NotifyOnParentFontChange()
		{
			m_pEditor->m_bUpdateRequired = true;
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CEventEditorService::NotifyOnResize()
		{
			m_pEditor->m_bUpdateRequired = true;
			m_pEditor->Update();
			if (m_pEditor->m_pHandler)
			{
				m_pEditor->m_pHandler->setSize(PointF{ m_pEditor->CalculateHandlerWidth(), m_pEditor->m_fRowHeight });
				m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerAndSetOpenDirectionY();
				m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
			}
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CEventEditorService::NotifyOnStyleChange()
		{
			if (m_pEditor->getStyle())
			{
				m_pEditor->UpdateFormStyle(m_pEditor->getStyle());
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
			}
		}

		void CEventEditorService::NotifyOnFontChange()
		{
			m_pEditor->m_bUpdateRequired = true;
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CEventEditorService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pEditor->m_pHandler)
			{
				m_pEditor->m_pHandler->setFocused(true);
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CEventEditorService::NotifyOnKillFocus()
		{
			if (m_pEditor->m_pHandler)
			{
				m_pEditor->m_pHandler->setFocused(false);
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CEventEditorService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}

		void CEventEditorService::NotifyOnDeactivate()
		{
			if (m_pEditor->m_pHandler)
			{
				m_pEditor->m_pHandler->NotifyOnDeactivate();
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CEventEditorService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (ntl::IsGreater<float>(m_pEditor->getWidth(), 0) && ntl::IsGreater<float>(m_pEditor->getHeight(), 0))
			{
				if (!m.LastPass)
					m_pEditor->Render();
				else
					m_pEditor->RenderHandler();
			}
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CEventEditorService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEditor->m_pHandler)
			{
				if (m_pEditor->m_pHandler->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				return;
			}
			if (!ctrl && !alt && !shift)
			{
				switch (m.Key)
				{
				case Key::Up:
				case Key::Numpad8:
					if (m.Key == Key::Up || (m.Key == Key::Numpad8 && !numlock))
						ProcessKeyUp();
					return;
				case Key::Down:
				case Key::Numpad2:
					if (m.Key == Key::Down || (m.Key == Key::Numpad2 && !numlock))
						ProcessKeyDown();
					return;
				case Key::Prior:
				case Key::Numpad9:
					if (m.Key == Key::Prior || (m.Key == Key::Numpad9 && !numlock))
						ProcessKeyPageUp();
					return;
				case Key::Next:
				case Key::Numpad3:
					if (m.Key == Key::Next || (m.Key == Key::Numpad3 && !numlock))
						ProcessKeyPageDown();
					return;
				case Key::Home:
				case Key::Numpad7:
					if (m.Key == Key::Home || (m.Key == Key::Numpad7 && !numlock))
						ProcessKeyHome();
					return;
				case Key::End:
				case Key::Numpad1:
					if (m.Key == Key::End || (m.Key == Key::Numpad1 && !numlock))
						ProcessKeyEnd();
					return;
				default:
					break;
				}
			}
			if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CEventEditorService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CEventEditorService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CEventEditorService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnDeadChar(m.Char, ctrl, alt, shift, numlock))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CEventEditorService::NotifyOnMouseHover(const MessagePosition &m)
		{
			m_pEditor->Update();
			if (m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position)))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CEventEditorService::NotifyOnMouseLeave()
		{
			m_pEditor->Update();
			if (m_pEditor->m_eHoveredElement != CEventEditor::Element::None)
			{
				switch (m_pEditor->m_eHoveredElement)
				{
				case CEventEditor::Element::Scroll:
					m_pEditor->getScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_pEditor->m_eHoveredElement = CEventEditor::Element::None;
				m_pEditor->m_iHoveredEventIndex = -1;
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CEventEditorService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			if (m_pEditor->m_pHandler && m_pEditor->isActive())
			{
				if (m_pEditor->m_pHandler->NotifyOnMouseMove(m_pEditor->FormToHandler(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Shift, m.Alt))
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				return;
			}
			switch (m_pEditor->m_eDownElement)
			{
			case CEventEditor::Element::CaptionSeparator:
				ProcessMoveCaptionSeparator(m_pEditor->FormToLocal(m.Position));
				break;
			case CEventEditor::Element::Scroll:
				if (m_pEditor->getScroll()->NotifyOnMouseMove(FormToScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pEditor->m_pHandler)
					{
						m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerAndSetOpenDirectionY();
						m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
					}
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				break;
			case CEventEditor::Element::Event:
				if (m_pEditor->m_pHandler->NotifyOnMouseMove(m_pEditor->FormToHandler(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				break;
			default:
				if (m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position)))
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				else
				{
					if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnMouseMove(m_pEditor->FormToHandler(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pEditor->m_pCanvas)
							m_pEditor->m_pCanvas->setValid(false);
						m_pEditor->Repaint(false);
					}
					if (m_pEditor->getScroll()->isEnabled() && m_pEditor->getScroll()->NotifyOnMouseMove(FormToScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pEditor->m_pCanvas)
							m_pEditor->m_pCanvas->setValid(false);
						m_pEditor->Repaint(false);
					}
				}
			}
		}

		void CEventEditorService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			if (m_pEditor->m_pHandler && m_pEditor->isActive())
			{
				processed = true;
				PointF p{ m_pEditor->FormToHandler(m.Position) };
				m_pEditor->m_pHandler->NotifyOnMouseLeftDown(p, m.Middle, m.Right, m.Ctrl, m.Shift, m.Alt);
				m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position));
				if (!m_pEditor->isActive() && !m_pEditor->m_pHandler->isInside(p))
					CancelDown(true);
				else
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
					return;
				}
			}
			if (!m.Middle && !m.Right && m_pEditor->m_eHoveredElement != CEventEditor::Element::None)
			{
				m_pEditor->m_eDownElement = CEventEditor::Element::None;
				switch (m_pEditor->m_eHoveredElement)
				{
				case CEventEditor::Element::CaptionSeparator:
					m_fDownCaptionSeparatorDisp = m_pEditor->FormToLocal(m.Position).X - m_pEditor->m_sBorderWidth.Left - m_pEditor->CalculateCaptionWidth();
					m_pEditor->m_eDownElement = CEventEditor::Element::CaptionSeparator;
					break;
				case CEventEditor::Element::Scroll:
					if (m_pEditor->getScroll()->NotifyOnMouseLeftDown(FormToScroll(m.Position), false, false, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pEditor->m_pHandler)
						{
							m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerAndSetOpenDirectionY();
							m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
						}
						if (m_pEditor->m_pCanvas)
							m_pEditor->m_pCanvas->setValid(false);
						m_pEditor->Repaint(false);
						m_pEditor->m_eDownElement = CEventEditor::Element::Scroll;
					}
					break;
				case CEventEditor::Element::Event:
					if (FocusHandler(m_pEditor->m_iHoveredEventIndex))
						m_pEditor->m_pHandler->NotifyOnMouseMove(m_pEditor->FormToHandler(m.Position), true, false, false, m.Ctrl, m.Alt, m.Shift);
					if (m_pEditor->m_pHandler)
						m_pEditor->m_pHandler->NotifyOnMouseLeftDown(m_pEditor->FormToHandler(m.Position), false, false, m.Ctrl, m.Alt, m.Shift);
					m_pEditor->m_eDownElement = CEventEditor::Element::Event;
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
					break;
				default:
					break;
				}
				m_pEditor->getForm()->CaptureMouse(m_pEditor, true);
			}
			else
				CancelDown(true);
		}

		void CEventEditorService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			if (m_pEditor->m_pHandler && m_pEditor->isActive())
			{
				m_pEditor->m_pHandler->NotifyOnMouseLeftUp(m_pEditor->FormToHandler(m.Position), m.Middle, m.Right, m.Ctrl, m.Shift, m.Alt);
				if (!m_pEditor->isActive())
					m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position));
				CancelDown(true);
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
				return;
			}
			switch (m_pEditor->m_eDownElement)
			{
			case CEventEditor::Element::Scroll:
				if (m_pEditor->getScroll()->NotifyOnMouseLeftUp(FormToScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position));
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				break;
			case CEventEditor::Element::CaptionSeparator:
				m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position));
				break;
			case CEventEditor::Element::Event:
				if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnMouseLeftUp(m_pEditor->FormToHandler(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				break;
			default:
				break;
			}
			CancelDown(true);
		}

		void CEventEditorService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			switch (m_pEditor->m_eHoveredElement)
			{
			case CEventEditor::Element::Event:
				if (m_pEditor->m_pHandler && m_pEditor->m_iFocusedEventIndex >= 0)
				{
					if (m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]->getValue().empty())
					{
						IComponent *component{ cast<IComponent*>(m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]->getParent()) };
						IForm *form{ cast<IForm*>(m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]->getParent()) };
						if (component || form)
						{
							String name{ component ? component->Name : form->Name };
							if (m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]->setValue(name + L"_" + m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]->getName()))
							{
								m_pEditor->m_pHandler->setText(m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]->getValue());
								m_pEditor->NotifyOnEventChange(m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]);
								if (m_pEditor->m_pCanvas)
									m_pEditor->m_pCanvas->setValid(false);
								m_pEditor->Repaint(false);
							}
						}
					}
					else
					{
						if (m_pEditor->m_pHandler->NotifyOnMouseLeftDoubleClick(m_pEditor->FormToHandler(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						{
							if (m_pEditor->m_pCanvas)
								m_pEditor->m_pCanvas->setValid(false);
							m_pEditor->Repaint(false);
						}
					}
				}
				break;
			case CEventEditor::Element::CaptionSeparator:
				m_pEditor->setCaptionWidth(0.5f);
				break;
			default:
				break;
			}
			CancelDown(true);
		}

		void CEventEditorService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CEventEditorService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CEventEditorService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CEventEditorService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CEventEditorService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CEventEditorService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CEventEditorService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			m_pEditor->Update();
			if (m_pEditor->m_pHandler && m_pEditor->isActive())
			{
				PointF p{ m_pEditor->FormToHandler(m.Position) };
				if (m_pEditor->m_pHandler->isInside(p))
				{
					processed = true;
					if (m_pEditor->m_pHandler->NotifyOnMouseVerticalWheel(p, m.Left, m.Middle, m.Right, m.Ctrl, m.Shift, m.Alt, m.Delta))
					{
						if (m_pEditor->m_pCanvas)
							m_pEditor->m_pCanvas->setValid(false);
						m_pEditor->Repaint(false);
					}
					return;
				}
			}
			if (m_pEditor->getScroll()->isEnabled())
			{
				processed = true;
				if (m_pEditor->getScroll()->NotifyOnMouseVerticalWheel(PointF{ 1, 1 }, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					if (m_pEditor->m_pHandler)
					{
						m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerAndSetOpenDirectionY();
						m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
					}
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region Clipboard notifications
		void CEventEditorService::NotifyOnPasteString(const MessagePasteString &m)
		{
			if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnPasteString(m.Text))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}
	#pragma endregion
	}
}