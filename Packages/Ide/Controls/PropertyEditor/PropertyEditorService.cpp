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
		CPropertyEditorService::CPropertyEditorService(CPropertyEditor *editor) :
			CControlService(editor),
			m_pEditor{ editor }
		{

		}
	#pragma endregion

	#pragma region Helpers
		PointF CPropertyEditorService::FormToScroll(const PointF &position)
		{
			PointF p{ m_pEditor->FormToLocal((PointF)position) };
			return PointF{ p.X - m_pEditor->getWidth() + m_pEditor->m_sBorderWidth.Right + m_pEditor->getScroll()->getSize().X, p.Y - m_pEditor->m_sBorderWidth.Top };
		}

		void CPropertyEditorService::CancelDown(const bool check_capture)
		{
			if (m_pEditor->m_eDownElement != CPropertyEditor::Element::None)
			{
				if (m_pEditor->m_pHandler)
					m_pEditor->m_pHandler->NotifyOnMouseDownCancel();
				switch (m_pEditor->m_eDownElement)
				{
				case CPropertyEditor::Element::Scroll:
					m_pEditor->getScroll()->NotifyOnMouseDownCancel();
					break;
				default:
					break;
				}
				m_pEditor->m_eDownElement = CPropertyEditor::Element::None;
			}
			if (check_capture && m_pEditor->isCaptureMouse() && (!m_pEditor->m_pHandler || !m_pEditor->isActive()))
				m_pEditor->getForm()->ReleaseCaptureMouse();
		}

		void CPropertyEditorService::ProcessMoveCaptionSeparator(const PointF &position)
		{
			PointF range;
			range.X = m_pEditor->m_sBorderWidth.Left + m_pEditor->m_fFolderWidth + m_pEditor->m_fFolderSeparatorWidth;
			range.Y = m_pEditor->getWidth() - m_pEditor->m_sBorderWidth.Right - m_pEditor->getScroll()->getSize().X;
			if (ntl::IsGreater<float>(range.Y, range.X))
			{
				float x{ position.X - m_fDownCaptionSeparatorDisp - range.X };
				x = ntl::Clamp<float>(x / (range.Y - range.X), 0.0f, 1.0f);
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

		bool CPropertyEditorService::FocusHandler(const int index, const int state_index)
		{
			if (index != m_pEditor->m_iFocusedPropertyIndex || state_index != m_pEditor->m_iFocusedPropertyStateIndex)
			{
				m_pEditor->FreeHandler();
				if (Application->Editor && (!m_pEditor->m_aProperties[index].PropertyState || state_index >= 0))
				{
					m_pEditor->m_iFocusedPropertyIndex = index;
					m_pEditor->m_iFocusedPropertyStateIndex = state_index;
					m_pEditor->m_pHandler = m_pEditor->getPropertyHandler(m_pEditor->m_aProperties[m_pEditor->m_iFocusedPropertyIndex].Property->PropertyHandlerName);
					m_pEditor->m_pHandler->setControl(m_pEditor);
					m_pEditor->m_pHandler->setProperty(m_pEditor->m_aProperties[m_pEditor->m_iFocusedPropertyIndex].Property);
					m_pEditor->m_pHandler->setPropertyState(m_pEditor->m_aProperties[m_pEditor->m_iFocusedPropertyIndex].PropertyState ? m_pEditor->m_aProperties[m_pEditor->m_iFocusedPropertyIndex].PropertyState->getState(m_pEditor->m_iFocusedPropertyStateIndex) : L"");
					m_pEditor->m_pHandler->setSize(PointF{ m_pEditor->CalculateHandlerWidth(), m_pEditor->m_fRowHeight });
					m_pEditor->m_pHandler->setListener(&m_pEditor->m_cListener);
					m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerY();
					m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
					m_pEditor->m_pHandler->setFocused(true);
					return true;
				}
			}
			return false;
		}

		bool CPropertyEditorService::ScrollToHandler()
		{
			if (m_pEditor->m_pHandler && m_pEditor->getScroll()->isEnabled())
			{
				if (ntl::IsLess<float>(m_pEditor->m_fHandlerY, m_pEditor->m_sBorderWidth.Top))
				{
					if (m_pEditor->getScroll()->setScroll(m_pEditor->getScroll()->getScroll() - m_pEditor->m_sBorderWidth.Top - m_pEditor->m_fHandlerY))
					{
						m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerY();
						m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
						return true;
					}
				}
				else if (ntl::IsGreaterOrEqual<float>(m_pEditor->m_fHandlerY + m_pEditor->m_fRowHeight, m_pEditor->getHeight() - m_pEditor->m_sBorderWidth.Bottom))
					if (m_pEditor->getScroll()->setScroll(m_pEditor->getScroll()->getScroll() + m_pEditor->m_fHandlerY + m_pEditor->m_fRowHeight - m_pEditor->getHeight() + m_pEditor->m_sBorderWidth.Bottom))
					{
						m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerY();
						m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
						return true;
					}
			}
			return false;
		}
	#pragma endregion

	#pragma region Process keys
		void CPropertyEditorService::ProcessKeyUp()
		{
			if (m_pEditor->m_aProperties.size() > 0)
			{
				int new_index, new_state_index{ -1 };
				bool found{ false };
				if (!m_pEditor->m_pHandler)
				{
					new_index = (int)m_pEditor->m_aProperties.size() - 1;
					new_state_index = -1;
				}
				else
				{
					new_index = m_pEditor->m_iFocusedPropertyIndex;
					if (m_pEditor->m_aProperties[new_index].PropertyState)
					{
						new_state_index = m_pEditor->m_iFocusedPropertyStateIndex;
						if (new_state_index < 0)
							new_index--;
					}
					else
						new_index--;
				}
				while (!found && new_index >= 0)
				{
					while (new_index >= 0 && m_pEditor->m_aProperties[new_index].PropertyState && m_pEditor->m_aProperties[new_index].Folded)
						new_index--;
					if (new_index >= 0)
					{
						if (m_pEditor->m_aProperties[new_index].PropertyState)
						{
							if (new_state_index < 0)
								new_state_index = m_pEditor->m_aProperties[new_index].PropertyState->getStateCount() - 1;
							else
								new_state_index--;
							if (new_state_index >= 0)
								found = true;
							else
								new_index--;
						}
						else
						{
							new_state_index = -1;
							found = true;
						}
					}
				}
				if (found && (new_index != m_pEditor->m_iFocusedPropertyIndex || new_state_index != m_pEditor->m_iFocusedPropertyStateIndex))
				{
					FocusHandler(new_index, new_state_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CPropertyEditorService::ProcessKeyDown()
		{
			if (m_pEditor->m_aProperties.size() > 0)
			{
				int new_index, new_state_index{ -1 };
				bool found{ false };
				if (!m_pEditor->m_pHandler)
				{
					new_index = 0;
					new_state_index = -1;
				}
				else
				{
					new_index = m_pEditor->m_iFocusedPropertyIndex;
					if (m_pEditor->m_aProperties[new_index].PropertyState)
					{
						new_state_index = m_pEditor->m_iFocusedPropertyStateIndex;
						if (new_state_index >= m_pEditor->m_aProperties[new_index].PropertyState->getStateCount())
							new_index++;
					}
					else
						new_index++;
				}
				while (!found && new_index < (int)m_pEditor->m_aProperties.size())
				{
					while (new_index < (int)m_pEditor->m_aProperties.size() && m_pEditor->m_aProperties[new_index].PropertyState && m_pEditor->m_aProperties[new_index].Folded)
						new_index++;
					if (new_index < (int)m_pEditor->m_aProperties.size())
					{
						if (m_pEditor->m_aProperties[new_index].PropertyState)
						{
							if (new_state_index >= m_pEditor->m_aProperties[new_index].PropertyState->getStateCount())
								new_state_index = -1;
							else
								new_state_index++;
							if (new_state_index >= 0 && new_state_index < m_pEditor->m_aProperties[new_index].PropertyState->getStateCount())
								found = true;
							else
								new_index++;
						}
						else
						{
							new_state_index = -1;
							found = true;
						}
					}
				}
				if (found && (new_index != m_pEditor->m_iFocusedPropertyIndex || new_state_index != m_pEditor->m_iFocusedPropertyStateIndex))
				{
					FocusHandler(new_index, new_state_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CPropertyEditorService::ProcessKeyPageUp()
		{
			if (m_pEditor->m_aProperties.size() > 0)
			{
				int new_index, new_state_index{ -1 }, processed{ 1 };
				int page_size{ ntl::Max<int>(1, ntl::Round<int>((m_pEditor->getHeight() - m_pEditor->m_sBorderWidth.Top - m_pEditor->m_sBorderWidth.Bottom) / m_pEditor->m_fRowHeight) - 1) };
				bool found{ false };
				if (!m_pEditor->m_pHandler)
				{
					new_index = (int)m_pEditor->m_aProperties.size() - 1;
					new_state_index = -1;
					processed = page_size;
				}
				else
				{
					new_index = m_pEditor->m_iFocusedPropertyIndex;
					if (m_pEditor->m_aProperties[new_index].PropertyState)
					{
						new_state_index = m_pEditor->m_iFocusedPropertyStateIndex - 1;
						if (new_state_index < 0)
							new_index--;
					}
					else
						new_index--;
				}
				while (!found && new_index >= 0)
				{
					while (new_index >= 0 && m_pEditor->m_aProperties[new_index].PropertyState && m_pEditor->m_aProperties[new_index].Folded)
					{
						new_index--;
						processed++;
					}
					if (new_index >= 0)
					{
						processed++;
						if (m_pEditor->m_aProperties[new_index].PropertyState)
						{
							if (new_state_index < 0)
								new_state_index = m_pEditor->m_aProperties[new_index].PropertyState->getStateCount() - 1;
							else
								new_state_index--;
							if (new_state_index >= 0)
							{
								if (processed >= page_size)
									found = true;
							}
							else
								new_index--;
						}
						else
						{
							new_state_index = -1;
							if (processed >= page_size)
								found = true;
							else
								new_index--;
						}
					}
				}
				if (!found)
				{
					new_index = 0;
					new_state_index = -1;
					while (!found && new_index < (int)m_pEditor->m_aProperties.size())
					{
						while (new_index < (int)m_pEditor->m_aProperties.size() && m_pEditor->m_aProperties[new_index].PropertyState && m_pEditor->m_aProperties[new_index].Folded)
							new_index++;
						if (new_index < (int)m_pEditor->m_aProperties.size())
						{
							if (m_pEditor->m_aProperties[new_index].PropertyState)
							{
								if (new_state_index >= m_pEditor->m_aProperties[new_index].PropertyState->getStateCount())
									new_state_index = -1;
								else
									new_state_index++;
								if (new_state_index >= 0 && new_state_index < m_pEditor->m_aProperties[new_index].PropertyState->getStateCount())
									found = true;
								else
									new_index++;
							}
							else
							{
								new_state_index = -1;
								found = true;
							}
						}
					}
					if (found && (new_index > m_pEditor->m_iFocusedPropertyIndex || (new_index == m_pEditor->m_iFocusedPropertyIndex && new_state_index >= m_pEditor->m_iFocusedPropertyStateIndex)))
						found = false;
				}
				if (found && (new_index != m_pEditor->m_iFocusedPropertyIndex || new_state_index != m_pEditor->m_iFocusedPropertyStateIndex))
				{
					FocusHandler(new_index, new_state_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CPropertyEditorService::ProcessKeyPageDown()
		{
			if (m_pEditor->m_aProperties.size() > 0)
			{
				int new_index, new_state_index{ -1 }, processed{ 1 };
				int page_size{ ntl::Max<int>(1, ntl::Round<int>((m_pEditor->getHeight() - m_pEditor->m_sBorderWidth.Top - m_pEditor->m_sBorderWidth.Bottom) / m_pEditor->m_fRowHeight) - 1) };
				bool found{ false };
				if (!m_pEditor->m_pHandler)
				{
					new_index = 0;
					new_state_index = -1;
					processed = page_size;
				}
				else
				{
					new_index = m_pEditor->m_iFocusedPropertyIndex;
					if (m_pEditor->m_aProperties[new_index].PropertyState)
					{
						new_state_index = m_pEditor->m_iFocusedPropertyStateIndex + 1;
						if (new_state_index >= m_pEditor->m_aProperties[new_index].PropertyState->getStateCount())
						{
							new_index++;
							new_state_index = -1;
						}
					}
					else
						new_index++;
				}
				while (!found && new_index < (int)m_pEditor->m_aProperties.size())
				{
					while (new_index < (int)m_pEditor->m_aProperties.size() && m_pEditor->m_aProperties[new_index].PropertyState && m_pEditor->m_aProperties[new_index].Folded)
					{
						new_index++;
						processed++;
					}
					if (new_index < (int)m_pEditor->m_aProperties.size())
					{
						processed++;
						if (m_pEditor->m_aProperties[new_index].PropertyState)
						{
							if (new_state_index >= m_pEditor->m_aProperties[new_index].PropertyState->getStateCount() - 1)
								new_state_index = -1;
							else
								new_state_index++;
							if (new_state_index >= 0)
							{
								if (processed >= page_size)
									found = true;
							}
							else
								new_index++;
						}
						else
						{
							new_state_index = -1;
							if (processed >= page_size)
								found = true;
							else
								new_index++;
						}
					}
				}
				if (!found)
				{
					new_index = (int)m_pEditor->m_aProperties.size() - 1;
					new_state_index = -1;
					while (!found && new_index >= 0)
					{
						while (new_index >= 0 && m_pEditor->m_aProperties[new_index].PropertyState && m_pEditor->m_aProperties[new_index].Folded)
							new_index--;
						if (new_index >= 0)
						{
							if (m_pEditor->m_aProperties[new_index].PropertyState)
							{
								if (new_state_index < 0)
									new_state_index = m_pEditor->m_aProperties[new_index].PropertyState->getStateCount() - 1;
								else
									new_state_index--;
								if (new_state_index >= 0)
									found = true;
								else
									new_index--;
							}
							else
							{
								new_state_index = -1;
								found = true;
							}
						}
					}
					if (found && (new_index < m_pEditor->m_iFocusedPropertyIndex || (new_index == m_pEditor->m_iFocusedPropertyIndex && new_state_index <= m_pEditor->m_iFocusedPropertyStateIndex)))
						found = false;
				}
				if (found && (new_index != m_pEditor->m_iFocusedPropertyIndex || new_state_index != m_pEditor->m_iFocusedPropertyStateIndex))
				{
					FocusHandler(new_index, new_state_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CPropertyEditorService::ProcessKeyHome()
		{
			if (m_pEditor->m_aProperties.size() > 0)
			{
				int new_index, new_state_index;
				bool found{ false };
				new_index = 0;
				new_state_index = -1;
				while (!found && new_index < (int)m_pEditor->m_aProperties.size())
				{
					while (new_index < (int)m_pEditor->m_aProperties.size() && m_pEditor->m_aProperties[new_index].PropertyState && m_pEditor->m_aProperties[new_index].Folded)
						new_index++;
					if (new_index < (int)m_pEditor->m_aProperties.size())
					{
						if (m_pEditor->m_aProperties[new_index].PropertyState)
						{
							if (new_state_index < 0 || new_state_index >= m_pEditor->m_aProperties[new_index].PropertyState->getStateCount())
								new_state_index = -1;
							else
								new_state_index++;
							if (new_state_index >= 0 && new_state_index < m_pEditor->m_aProperties[new_index].PropertyState->getStateCount())
								found = true;
							else
								new_index++;
						}
						else
						{
							new_state_index = -1;
							found = true;
						}
					}
				}
				if (found && (new_index != m_pEditor->m_iFocusedPropertyIndex || new_state_index != m_pEditor->m_iFocusedPropertyStateIndex))
				{
					FocusHandler(new_index, new_state_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CPropertyEditorService::ProcessKeyEnd()
		{
			if (m_pEditor->m_aProperties.size() > 0)
			{
				int new_index, new_state_index;
				bool found{ false };
				new_index = (int)m_pEditor->m_aProperties.size() - 1;
				new_state_index = -1;
				while (!found && new_index >= 0)
				{
					while (new_index >= 0 && m_pEditor->m_aProperties[new_index].PropertyState && m_pEditor->m_aProperties[new_index].Folded)
						new_index--;
					if (new_index >= 0)
					{
						if (m_pEditor->m_aProperties[new_index].PropertyState)
						{
							if (new_state_index < 0)
								new_state_index = m_pEditor->m_aProperties[new_index].PropertyState->getStateCount() - 1;
							else
								new_state_index--;
							if (new_state_index >= 0)
								found = true;
							else
								new_index--;
						}
						else
						{
							new_state_index = -1;
							found = true;
						}
					}
				}
				if (found && (new_index != m_pEditor->m_iFocusedPropertyIndex || new_state_index != m_pEditor->m_iFocusedPropertyStateIndex))
				{
					FocusHandler(new_index, new_state_index);
					ScrollToHandler();
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CPropertyEditorService::NotifyOnAttach()
		{
			if (m_pEditor->getForm())
				m_pEditor->getScroll()->NotifyOnAttach();
		}

		void CPropertyEditorService::NotifyOnDetaching()
		{
			m_pEditor->FreeHandler();
		}

		void CPropertyEditorService::NotifyOnFreeResources()
		{
			if (m_pEditor->m_pHandler)
				m_pEditor->m_pHandler->NotifyOnFreeResources();
			if (m_pEditor->m_pDefaultPropertyHandler && m_pEditor->m_pDefaultPropertyHandler != m_pEditor->m_pHandler)
				m_pEditor->m_pDefaultPropertyHandler->NotifyOnFreeResources();
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
		void CPropertyEditorService::NotifyOnParentStyleChange()
		{
			if (m_pEditor->getStyle())
			{
				m_pEditor->UpdateFormStyle(m_pEditor->getStyle());
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
			}
		}

		void CPropertyEditorService::NotifyOnParentFontChange()
		{
			m_pEditor->m_bUpdateRequired = true;
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CPropertyEditorService::NotifyOnResize()
		{
			m_pEditor->m_bUpdateRequired = true;
			m_pEditor->Update();
			if (m_pEditor->m_pHandler)
			{
				m_pEditor->m_pHandler->setSize(PointF{ m_pEditor->CalculateHandlerWidth(), m_pEditor->m_fRowHeight });
				m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerY();
				m_pEditor->m_pHandler->setPosition({ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
			}
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CPropertyEditorService::NotifyOnStyleChange()
		{
			if (m_pEditor->getStyle())
			{
				m_pEditor->UpdateFormStyle(m_pEditor->getStyle());
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
			}
		}

		void CPropertyEditorService::NotifyOnFontChange()
		{
			m_pEditor->m_bUpdateRequired = true;
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CPropertyEditorService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pEditor->m_pHandler)
			{
				m_pEditor->m_pHandler->setFocused(true);
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CPropertyEditorService::NotifyOnKillFocus()
		{
			if (m_pEditor->m_pHandler)
			{
				m_pEditor->m_pHandler->setFocused(false);
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CPropertyEditorService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}

		void CPropertyEditorService::NotifyOnDeactivate()
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
		void CPropertyEditorService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
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
		void CPropertyEditorService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
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

		void CPropertyEditorService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEditor->m_pHandler && m_pEditor->isActive())
			{
				if (m_pEditor->m_pHandler->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				return;
			}
			if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CPropertyEditorService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEditor->m_pHandler && m_pEditor->isActive())
			{
				if (m_pEditor->m_pHandler->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				return;
			}
			if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CPropertyEditorService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEditor->m_pHandler && m_pEditor->isActive())
			{
				if (m_pEditor->m_pHandler->NotifyOnDeadChar(m.Char, ctrl, alt, shift, numlock))
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				return;
			}
			if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnDeadChar(m.Char, ctrl, alt, shift, numlock))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CPropertyEditorService::NotifyOnMouseHover(const MessagePosition &m)
		{
			m_pEditor->Update();
			if (m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position)))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CPropertyEditorService::NotifyOnMouseLeave()
		{
			m_pEditor->Update();
			if (m_pEditor->m_eHoveredElement != CPropertyEditor::Element::None)
			{
				switch (m_pEditor->m_eHoveredElement)
				{
				case CPropertyEditor::Element::Scroll:
					m_pEditor->getScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_pEditor->m_eHoveredElement = CPropertyEditor::Element::None;
				m_pEditor->m_iHoveredPropertyIndex = m_pEditor->m_iHoveredPropertyStateIndex = -1;
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CPropertyEditorService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
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
			case CPropertyEditor::Element::CaptionSeparator:
				ProcessMoveCaptionSeparator(m_pEditor->FormToLocal(m.Position));
				break;
			case CPropertyEditor::Element::Scroll:
				if (m_pEditor->getScroll()->NotifyOnMouseMove(FormToScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pEditor->m_pHandler)
					{
						m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerY();
						m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
					}
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				break;
			case CPropertyEditor::Element::Property:
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

		void CPropertyEditorService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			if (m_pEditor->m_pHandler && m_pEditor->isActive())
			{
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
			if (!m.Middle && !m.Right && m_pEditor->m_eHoveredElement != CPropertyEditor::Element::None)
			{
				m_pEditor->m_eDownElement = CPropertyEditor::Element::None;
				switch (m_pEditor->m_eHoveredElement)
				{
				case CPropertyEditor::Element::Folder:
					if (m_pEditor->m_iFocusedPropertyIndex == m_pEditor->m_iHoveredPropertyIndex && m_pEditor->m_pHandler)
						m_pEditor->FreeHandler();
					m_pEditor->m_aProperties[m_pEditor->m_iHoveredPropertyIndex].Folded = !m_pEditor->m_aProperties[m_pEditor->m_iHoveredPropertyIndex].Folded;
					m_pEditor->UpdateScroll();
					if (m_pEditor->m_pHandler)
					{
						m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerY();
						m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
					}
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
					break;
				case CPropertyEditor::Element::CaptionSeparator:
					m_fDownCaptionSeparatorDisp = m_pEditor->FormToLocal(m.Position).X - m_pEditor->m_sBorderWidth.Left - m_pEditor->m_fFolderWidth - m_pEditor->m_fFolderSeparatorWidth
						- m_pEditor->CalculateCaptionWidth();
					m_pEditor->m_eDownElement = CPropertyEditor::Element::CaptionSeparator;
					break;
				case CPropertyEditor::Element::Scroll:
					if (m_pEditor->getScroll()->NotifyOnMouseLeftDown(FormToScroll(m.Position), false, false, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pEditor->m_pHandler)
						{
							m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerY();
							m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
						}
						if (m_pEditor->m_pCanvas)
							m_pEditor->m_pCanvas->setValid(false);
						m_pEditor->Repaint(false);
						m_pEditor->m_eDownElement = CPropertyEditor::Element::Scroll;
					}
					break;
				case CPropertyEditor::Element::Property:
					if (FocusHandler(m_pEditor->m_iHoveredPropertyIndex, m_pEditor->m_iHoveredPropertyStateIndex))
						m_pEditor->m_pHandler->NotifyOnMouseMove(m_pEditor->FormToHandler(m.Position), true, false, false, m.Ctrl, m.Alt, m.Shift);
					if (m_pEditor->m_pHandler)
					{
						m_pEditor->m_pHandler->NotifyOnMouseLeftDown(m_pEditor->FormToHandler(m.Position), false, false, m.Ctrl, m.Alt, m.Shift);
						m_pEditor->m_eDownElement = CPropertyEditor::Element::Property;
					}
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

		void CPropertyEditorService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
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
			case CPropertyEditor::Element::Scroll:
				if (m_pEditor->getScroll()->NotifyOnMouseLeftUp(FormToScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position));
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				break;
			case CPropertyEditor::Element::CaptionSeparator:
				m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position));
				break;
			case CPropertyEditor::Element::Property:
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

		void CPropertyEditorService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pEditor->Update();
			switch (m_pEditor->m_eHoveredElement)
			{
			case CPropertyEditor::Element::Property:
				if (m_pEditor->m_pHandler && m_pEditor->m_pHandler->NotifyOnMouseLeftDoubleClick(m_pEditor->FormToHandler(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				break;
			case CPropertyEditor::Element::CaptionSeparator:
				m_pEditor->setCaptionWidth(0.5);
				break;
			default:
				break;
			}
			CancelDown(true);
		}

		void CPropertyEditorService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CPropertyEditorService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CPropertyEditorService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CPropertyEditorService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CPropertyEditorService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CPropertyEditorService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CPropertyEditorService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
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
						m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerY();
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
		void CPropertyEditorService::NotifyOnPasteString(const MessagePasteString &m)
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