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
	namespace ide
	{
	#pragma region CGradientListener
		CEventEditor::CGradientListener::CGradientListener(CEventEditor *control) :
			m_pControl{ control }
		{

		}

		void CEventEditor::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CEventEditor::CEventEditor() :
			CControl(L"EventEditor", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_sBorderWidth{ 0, 0, 0, 0 },
			m_sBorderColor{ Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
			m_sBackgroundColor{ 255, 255, 255, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_fCaptionWidth{ 0.5f },
			m_fCaptionPadding{ 1 },
			m_aCaptionColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_aCaptionBorderWidth{ 0, 0, 0 },
			m_aCaptionBorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_aCaptionBackgroundColor{ Color{ 0, 0, 0, 0 }, Color{ 240, 240, 240, 255 }, Color{ 224, 224, 224, 255 } },
			m_aCaptionBackgroundGradient{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } },
			m_fCaptionSeparatorWidth{ 1 },
			m_sCaptionSeparatorColor{ 160, 160, 160, 255 },
			m_cCaptionSeparatorGradient{ &m_cGradientListener },
			m_pCanvas{ nullptr },
			m_pScroll{ nullptr },
			m_bIgnoreGradient{ false },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None },
			m_iHoveredEventIndex{ -1 },
			m_iFocusedEventIndex{ -1 },
			m_fRowHeight{ 0 },
			m_fHandlerY{ 0 },
			m_pHandler{ nullptr },
			m_cDropDown{ this },
			m_cDropDownListener{ this },
			m_cScrollListener{ this },
			m_bUpdateRequired{ true }
		{
			setService(new CEventEditorService(this), true);
			OnEventChange = nullptr;
			m_cDropDown.setListener(&m_cDropDownListener);
			m_cDropDown.setListMaxHeight(180);
			setSize(PointF{ 234, 328 });
		}

		CEventEditor::CEventEditor(IForm *parent) :CEventEditor()
		{
			setForm(parent);
		}

		CEventEditor::CEventEditor(IControl *parent) : CEventEditor()
		{
			setParent(parent);
		}

		CEventEditor::~CEventEditor()
		{
			if (m_pScroll)
				m_pScroll->Release();
		}
	#pragma endregion

	#pragma region Interface getters
		CursorType CEventEditor::getCursor()
		{
			Update();
			if (m_fCaptionSeparatorWidth > 0 && getForm() && isPointOverCaptionSeparator(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition()))))
				return CursorType::SizeWestEast;
			if (m_pHandler && getForm())
			{
				PointF p{ FormToHandler((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				return m_pHandler->getCursor(p, CControl::getCursor());
			}
			return CControl::getCursor();
		}

		int CEventEditor::getEventListCount()
		{
			return (int)m_aEventLists.size();
		}

		IEventList *CEventEditor::getEventList(const int index)
		{
			if (index >= 0 && index < (int)m_aEventLists.size())
				return m_aEventLists[index];
			return nullptr;
		}

		int CEventEditor::getEventCount()
		{
			return (int)m_aEvents.size();
		}

		IEvent *CEventEditor::getEvent(const int index)
		{
			if (index >= 0 && index < (int)m_aEvents.size())
				return m_aEvents[index];
			return nullptr;
		}

		int CEventEditor::getActiveEventIndex()
		{
			return m_iFocusedEventIndex;
		}
	#pragma endregion

	#pragma region Getters
		IBuiltInScroll *CEventEditor::getScroll()
		{
			if (!m_pScroll)
			{
				m_pScroll = new CScroll(this);
				m_pScroll->setListener(&m_cScrollListener);
				cast<CScroll*>(m_pScroll)->SwitchDirection(true);

			}
			return m_pScroll;
		}

		RectF CEventEditor::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		BorderColor CEventEditor::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CEventEditor::getLeftBorderColor() const
		{
			return m_sBorderColor.Left;
		}

		Color CEventEditor::getTopBorderColor() const
		{
			return m_sBorderColor.Top;
		}

		Color CEventEditor::getRightBorderColor() const
		{
			return m_sBorderColor.Right;
		}

		Color CEventEditor::getBottomBorderColor() const
		{
			return m_sBorderColor.Bottom;
		}

		Color CEventEditor::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CEventEditor::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		float CEventEditor::getCaptionWidth() const
		{
			return m_fCaptionWidth;
		}

		float CEventEditor::getCaptionPadding() const
		{
			return m_fCaptionPadding;
		}

		Color CEventEditor::getCaptionColor(const EventState state) const
		{
			return m_aCaptionColor[(int)state];
		}

		float CEventEditor::getCaptionBorderWidth(const EventState state) const
		{
			return m_aCaptionBorderWidth[(int)state];
		}

		Color CEventEditor::getCaptionBorderColor(const EventState state) const
		{
			return m_aCaptionBorderColor[(int)state];
		}

		Color CEventEditor::getCaptionBackgroundColor(const EventState state) const
		{
			return m_aCaptionBackgroundColor[(int)state];
		}

		Gradient *CEventEditor::getCaptionBackgroundGradient(const EventState state)
		{
			return &m_aCaptionBackgroundGradient[(int)state];
		}

		float CEventEditor::getCaptionSeparatorWidth() const
		{
			return m_fCaptionSeparatorWidth;
		}

		Color CEventEditor::getCaptionSeparatorColor() const
		{
			return m_sCaptionSeparatorColor;
		}

		Gradient *CEventEditor::getCaptionSeparatorGradient()
		{
			return &m_cCaptionSeparatorGradient;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CEventEditor::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			if (CControl::setDPI(value))
			{
				getScroll()->setDPI(value);
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_sBorderWidth *= s;
				m_fCaptionPadding *= s.X;
				for (int i = 0; i <= (int)EventState::Focused; i++)
					m_aCaptionBorderWidth[i] *= s.X;
				m_fCaptionSeparatorWidth *= s.X;
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CEventEditor::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		bool CEventEditor::AttachEventList(IEventList *list)
		{
			if (list && std::find(m_aEventLists.begin(), m_aEventLists.end(), list) == m_aEventLists.end())
			{
				FreeHandler();
				m_aEventLists.push_back(list);
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEventEditor::DetachEventList(const int index)
		{
			if (index >= 0 && index < (int)m_aEventLists.size())
			{
				FreeHandler();
				m_aEventLists.erase(m_aEventLists.begin() + index);
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEventEditor::DetachEventList(IEventList *list)
		{
			if (list)
			{
				auto pos{ std::find(m_aEventLists.begin(), m_aEventLists.end(), list) };
				if (pos != m_aEventLists.end())
				{
					FreeHandler();
					m_aEventLists.erase(pos);
					m_bUpdateRequired = true;
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			}
			return false;
		}

		bool CEventEditor::DetachEventLists()
		{
			if (m_aEventLists.size() > 0)
			{
				FreeHandler();
				m_aEventLists.clear();
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CEventEditor::setScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pScroll)
			{
				value->setListener(&m_cScrollListener);
				value->NotifyOnFreeResources();
				value->setVertical(true);
				if (m_pScroll)
					m_pScroll->Release();
				m_pScroll = value;
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CEventEditor::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CEventEditor::setBorderColor(const BorderColor &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
				if (m_sBorderWidth.has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CEventEditor::setLeftBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ value, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CEventEditor::setTopBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, value, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CEventEditor::setRightBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, value, m_sBorderColor.Bottom });
		}

		bool CEventEditor::setBottomBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, value });
		}

		bool CEventEditor::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_cBackgroundGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CEventEditor::setCaptionWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsLess<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fCaptionWidth))
			{
				m_fCaptionWidth = value;
				if (m_pHandler)
					m_pHandler->setSize(PointF{ CalculateHandlerWidth(), m_fRowHeight });
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEventEditor::setCaptionPadding(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCaptionPadding))
			{
				m_fCaptionPadding = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEventEditor::setCaptionColor(const EventState state, const Color &value)
		{
			if (value != m_aCaptionColor[(int)state])
			{
				m_aCaptionColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEventEditor::setCaptionBorderWidth(const EventState state, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aCaptionBorderWidth[(int)state]))
			{
				m_aCaptionBorderWidth[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEventEditor::setCaptionBorderColor(const EventState state, const Color &value)
		{
			if (value != m_aCaptionBorderColor[(int)state])
			{
				m_aCaptionBorderColor[(int)state] = value;
				if (m_aCaptionBorderWidth[(int)state] > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CEventEditor::setCaptionBackgroundColor(const EventState state, const Color &value)
		{
			if (value != m_aCaptionBackgroundColor[(int)state])
			{
				m_aCaptionBackgroundColor[(int)state] = value;
				if (m_aCaptionBackgroundGradient[(int)state].getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CEventEditor::setCaptionSeparatorWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCaptionSeparatorWidth))
			{
				m_fCaptionSeparatorWidth = value;
				if (m_sCaptionSeparatorColor.A > 0 || m_cCaptionSeparatorGradient.getPointCount() >= 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CEventEditor::setCaptionSeparatorColor(const Color &value)
		{
			if (value != m_sCaptionSeparatorColor)
			{
				m_sCaptionSeparatorColor = value;
				if (ntl::IsGreater<float>(m_fCaptionSeparatorWidth, 0) && m_cCaptionSeparatorGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		bool CEventEditor::isPointOverCaptionSeparator(const PointF &position)
		{
			RectF r;
			float caption_width{ CalculateCaptionWidth() };
			r.Left = m_sBorderWidth.Left + caption_width;
			r.Top = m_sBorderWidth.Top;
			r.Right = r.Left + m_fCaptionSeparatorWidth;
			r.Bottom = getHeight() - m_sBorderWidth.Bottom;
			return r.is_valid() && !r.is_zero() && position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom;
		}

		void CEventEditor::Update()
		{
			if (m_bUpdateRequired)
			{
				UpdateEventList();
				UpdateScroll();
				m_bUpdateRequired = false;
			}
		}

		void CEventEditor::UpdateEventList()
		{
			// Build list of package events required to be in visible events
			std::vector<IEvent*> events;
			if (m_aEventLists.size() > 0)
			{
				for (int i = 0; i < m_aEventLists[0]->getCount(); i++)
					events.push_back(m_aEventLists[0]->getEvent(i));
				if (m_aEventLists.size() > 1)
				{
					auto pos{ events.begin() };
					while (pos != events.end())
					{
						bool allowed{ true };
						for (int i = 1; i < (int)m_aEventLists.size(); i++)
						{
							bool found{ false };
							for (int j = 0; j < m_aEventLists[i]->getCount(); j++)
							{
								IEvent *p{ m_aEventLists[i]->getEvent(j) };
								if (CompareEvents(p, *pos))
								{
									found = true;
									break;
								}
							}
							if (!found)
							{
								allowed = false;
								break;
							}
						}
						if (!allowed)
							pos = events.erase(pos);
						else
							pos++;
					}
				}
			}
			// Update list of visible events
			IEvent *focused_event{ m_iFocusedEventIndex >= 0 ? m_aEvents[m_iFocusedEventIndex] : nullptr };
			auto pos{ m_aEvents.begin() };
			while (pos != m_aEvents.end())
			{
				auto p{ std::find(events.begin(), events.end(), *pos) };
				if (p == events.end())
					pos = m_aEvents.erase(pos);
				else
				{
					events.erase(p);
					pos++;
				}
			}
			for (auto pos = events.begin(); pos != events.end(); pos++)
				m_aEvents.push_back(*pos);
			std::sort(m_aEvents.begin(), m_aEvents.end(), [](IEvent *a, IEvent *b) { return a->getName() < b->getName(); });
			if (focused_event)
			{
				for (auto pos = m_aEvents.begin(); pos != m_aEvents.end(); pos++)
					if (*pos == focused_event)
					{
						m_iFocusedEventIndex = int(pos - m_aEvents.begin());
						focused_event = nullptr;
						break;
					}
				if (focused_event)
					FreeHandler();
			}
		}

		void CEventEditor::UpdateScroll()
		{
			m_fRowHeight = 2 * m_fCaptionPadding;
			if (getForm() && getForm()->getRenderer())
			{
				IPlatformFont *pf{ getFont()->getPlatformFont(getForm()->getRenderer()) };
				if (pf)
					m_fRowHeight += pf->getStringSize(L"Wy", 0).Y;
			}
			getScroll()->setSize(PointF{ getScroll()->getSize().X, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom });
			getScroll()->setPosition(PointF{ getWidth() - m_sBorderWidth.Right - getScroll()->getWidth(), m_sBorderWidth.Top });
			getScroll()->setDeltaMedium(m_fRowHeight * 3);
			float required_height{ m_fRowHeight * (float)m_aEvents.size() };
			if (ntl::IsGreater<float>(required_height, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom))
			{
				getScroll()->setEnabled(true);
				getScroll()->setMax(required_height - getHeight() + m_sBorderWidth.Top + m_sBorderWidth.Bottom);
				float area{ getScroll()->getSize().Y - 2 * (getScroll()->getSize().X - 1) };
				if (ntl::IsGreater<float>(area, 0))
				{
					getScroll()->setScrollerSize(getScroll()->getSize().Y / required_height * area);
					getScroll()->setDeltaLarge(getScroll()->getSize().Y / required_height * getScroll()->getMax());
				}
				else
				{
					getScroll()->setScrollerSize(1);
					getScroll()->setDeltaLarge(1);
				}
			}
			else
			{
				getScroll()->setEnabled(false);
				getScroll()->setScroll(0);
			}
		}

		float CEventEditor::CalculateCaptionWidth()
		{
			return m_fCaptionWidth * ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - getScroll()->getSize().X);
		}

		float CEventEditor::CalculateHandlerWidth()
		{
			return ntl::Max<float>(0, (1 - m_fCaptionWidth) * ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - getScroll()->getSize().X - m_fCaptionSeparatorWidth));
		}

		float CEventEditor::CalculateHandlerX()
		{
			return m_sBorderWidth.Left + CalculateCaptionWidth() + m_fCaptionSeparatorWidth;
		}

		float CEventEditor::CalculateHandlerAndSetOpenDirectionY()
		{
			float result{ m_sBorderWidth.Top };
			if (getScroll()->isEnabled())
				result -= getScroll()->getScroll();
			result += (float)m_iFocusedEventIndex * m_fRowHeight;
			m_cDropDown.setOpenDirection((result > getHeight() - 200) ? CBuiltInDropDown::OpenDirection::Up : CBuiltInDropDown::OpenDirection::Down);
			return result;
		}

		CEventEditor::EventState CEventEditor::getEventState(const int index)
		{
			if (index == m_iFocusedEventIndex)
				return EventState::Focused;
			if (m_eHoveredElement == Element::Event && index == m_iHoveredEventIndex)
				return EventState::Hovered;
			return EventState::Normal;
		}

		CEventEditor::Element CEventEditor::getElement(const PointF &position, int &event_index, PointF &event_position)
		{
			// Caption separator
			if (ntl::IsGreater<float>(m_fCaptionSeparatorWidth, 0))
			{
				RectF r;
				float caption_width{ CalculateCaptionWidth() };
				r.Left = m_sBorderWidth.Left + caption_width;
				r.Top = m_sBorderWidth.Top;
				r.Right = r.Left + m_fCaptionSeparatorWidth;
				r.Bottom = getHeight() - m_sBorderWidth.Bottom;
				if (r.is_valid() && !r.is_zero() && position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return Element::CaptionSeparator;
			}
			// Scroll
			if (position.X >= getWidth() - m_sBorderWidth.Right - getScroll()->getSize().X && position.X < getWidth() - m_sBorderWidth.Right && position.Y >= m_sBorderWidth.Top && position.Y < getHeight() - m_sBorderWidth.Bottom)
				return Element::Scroll;
			// Property
			if (position.X >= m_sBorderWidth.Left && position.X < getWidth() - m_sBorderWidth.Right - getScroll()->getSize().X && position.Y >= m_sBorderWidth.Top && position.Y < getHeight() - m_sBorderWidth.Bottom)
			{
				float x{ m_sBorderWidth.Left + CalculateCaptionWidth() + m_fCaptionSeparatorWidth }, y{ m_sBorderWidth.Top };
				if (getScroll()->isEnabled())
					y -= getScroll()->getScroll();
				for (auto pos = m_aEvents.begin(); pos != m_aEvents.end(); pos++)
				{
					if (position.Y >= y && position.Y < y + m_fRowHeight)
					{
						event_position.X = x;
						event_position.Y = y;
						event_index = int(pos - m_aEvents.begin());
						return Element::Event;
					}
					y += m_fRowHeight;
				}
			}
			return Element::None;
		}

		bool CEventEditor::UpdateHoveredElement(const PointF &position)
		{
			int event_index;
			PointF event_position;
			Element new_element{ getElement(position, event_index, event_position) };
			if (new_element != m_eHoveredElement || (new_element == Element::Event && event_index != m_iHoveredEventIndex))
			{
				switch (m_eHoveredElement)
				{
				case Element::Scroll:
					getScroll()->NotifyOnMouseLeave();
					break;
				case Element::Event:
					if (m_pHandler && m_iHoveredEventIndex != m_iFocusedEventIndex)
						m_pHandler->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_eHoveredElement = new_element;
				m_iHoveredEventIndex = event_index;
				switch (m_eHoveredElement)
				{
				case Element::Scroll:
					getScroll()->NotifyOnMouseHover(PointF{ position.X - getWidth() - m_sBorderWidth.Left - getScroll()->getSize().X, position.Y - m_sBorderWidth.Top });
					break;
				case Element::Event:
					if (m_pHandler && m_iHoveredEventIndex == m_iFocusedEventIndex)
						m_pHandler->NotifyOnMouseHover(PointF{ position.X - event_position.X, position.Y - event_position.Y });
					break;
				default:
					break;
				}
				return true;
			}
			return false;
		}

		void CEventEditor::FreeHandler()
		{
			if (m_pHandler)
			{
				if (isActive())
					getForm()->setActiveControl(nullptr);
				m_pHandler->setFocused(false);
				m_pHandler = nullptr;
				m_iFocusedEventIndex = -1;
			}
		}

		PointF CEventEditor::FormToHandler(const PointF &position)
		{
			PointF p{ FormToLocal(position) };
			float x{ CalculateHandlerX() };
			float y{ m_sBorderWidth.Top - (getScroll()->isEnabled() ? getScroll()->getScroll() : 0) };
			for (auto pos = m_aEvents.begin(); pos != m_aEvents.end(); pos++)
			{
				if (pos - m_aEvents.begin() == m_iFocusedEventIndex)
					return PointF{ p.X - x, p.Y - y };
				y += m_fRowHeight;
			}
			return PointF{ 0, 0 };
		}

		bool CEventEditor::CompareEvents(IEvent *a, IEvent *b)
		{
			return a->getName() == b->getName() && a->getSignature() == b->getSignature();
		}

		void CEventEditor::UpdateFormStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L"BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L"BorderColor", m_sBorderColor);
			style->getOption(m_sClassName + L"BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L"BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L"CaptionWidth", m_fCaptionWidth);
			for (int i = 0; i <= (int)EventState::Focused; i++)
			{
				String name;
				switch ((EventState)i)
				{
				case EventState::Normal:
					name = L"Normal";
					break;
				case EventState::Hovered:
					name = L"Hovered";
					break;
				default:
					name = L"Focused";
				}
				style->getOption(m_sClassName + L"CaptionColor[" + name + L"]", m_aCaptionColor[i]);
				style->getOption(m_sClassName + L"CaptionBorderWidth[" + name + L"]", m_aCaptionBorderWidth[i]);
				style->getOption(m_sClassName + L"CaptionBorderColor[" + name + L"]", m_aCaptionBorderColor[i]);
				style->getOption(m_sClassName + L"CaptionBackgroundColor[" + name + L"]", m_aCaptionBackgroundColor[i]);
				style->getOption(m_sClassName + L"CaptionBackgroundGradient[" + name + L"]", m_aCaptionBackgroundGradient[i]);
			}
			style->getOption(m_sClassName + L"CaptionSeparatorWidth", m_fCaptionSeparatorWidth);
			style->getOption(m_sClassName + L"CaptionSeparatorColor", m_sCaptionSeparatorColor);
			style->getOption(m_sClassName + L"CaptionSeparatorGradient", m_cCaptionSeparatorGradient);

			m_cDropDown.UpdateFromStyle(style, m_cDropDown.ClassName);
			getScroll()->UpdateFromStyle(style, getScroll()->ClassName);
			m_bIgnoreGradient = false;
			m_bUpdateRequired = true;
		}
	#pragma endregion

	#pragma region Property change notification
		void CEventEditor::NotifyOnEventChange(IEvent *event)
		{
			// Update other list events if multiple event lists added
			if (OnEventChange)
				OnEventChange(this, event, m_aEventLists[0], m_aEventLists[0]->getParent());
			if (m_aEventLists.size() > 1)
				for (int i = 0; i < (int)m_aEventLists.size(); i++)
					for (int j = 0; j < m_aEventLists[i]->getCount(); j++)
						if (CompareEvents(m_aEventLists[i]->getEvent(j), event))
						{
							if (m_aEventLists[i]->getEvent(j)->setValue(event->getValue()))
								if (OnEventChange)
									OnEventChange(this, m_aEventLists[i]->getEvent(j), m_aEventLists[i], m_aEventLists[i]->getParent());
							break;
						}
			// Repaint
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}
	#pragma endregion

	#pragma region Paint
		void CEventEditor::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			RectF all_rect{ 0, 0, getWidth(), getHeight() };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				Update();
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				DrawSimpleBackground(renderer, all_rect, m_sBorderWidth, RectF{ 0, 0, 0, 0 }, m_sBorderColor, m_sBackgroundColor, m_cBackgroundGradient);
				RenderControl(renderer);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CEventEditor::RenderControl(IRenderer *renderer)
		{
			float x{ m_sBorderWidth.Left };

			// Render caption separator
			float width_caption{ CalculateCaptionWidth() }, width_value{ CalculateHandlerWidth() }, x_caption{ x }, x_value{ x + width_caption + m_fCaptionSeparatorWidth };
			x += width_caption;
			if (ntl::IsGreater<float>(m_fCaptionSeparatorWidth, 0))
			{
				if (m_cCaptionSeparatorGradient.getPointCount() > 1)
					renderer->DrawGradient(RectF{ x, m_sBorderWidth.Top, x + m_fCaptionSeparatorWidth, getHeight() - m_sBorderWidth.Bottom }, m_cCaptionSeparatorGradient);
				else if (m_sCaptionSeparatorColor.A > 0)
					renderer->DrawRectangle(RectF{ x, m_sBorderWidth.Top, x + m_fCaptionSeparatorWidth, getHeight() - m_sBorderWidth.Bottom }, m_sCaptionSeparatorColor);
				x += m_fCaptionSeparatorWidth;
			}

			// Items
			IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
			float line_height{ pf->getStringSize(L"Wy", 0).Y };
			Block b{ RectF{ 0, 0, getWidth(), getHeight() }, m_sBorderWidth, RectF{ 0, 0, 0, 0 }, PointLocation::Inside };
			IBaseTexture *old{ renderer->ActiveTarget };
			ITexture *clip_caption{ ntl::IsGreater<float>(width_caption, 0) ? renderer->CreateTexture(ntl::Round<int>(width_caption), ntl::Round<int>(m_fRowHeight), 1, TextureFormat::RGBA, true) : nullptr };
			RectF clip_caption_rect{ 0, 0, clip_caption ? clip_caption->Widthf : 0, clip_caption ? clip_caption->Heightf : 0 };
			ITexture *clip_value{ ntl::IsGreater<float>(width_value, 0) ? renderer->CreateTexture(ntl::Round<int>(width_value), ntl::Round<int>(m_fRowHeight), 1, TextureFormat::RGBA, true) : nullptr };
			RectF clip_value_rect{ 0, 0, clip_value ? clip_value->Widthf : 0, clip_value ? clip_value->Heightf : 0 };
			float y{ m_sBorderWidth.Top };
			if (getScroll()->isEnabled())
				y -= getScroll()->getScroll();
			for (auto pos = m_aEvents.begin(); pos != m_aEvents.end(); pos++)
			{
				// Caption
				if (clip_caption)
				{
					EventState state{ getEventState(int(pos - m_aEvents.begin())) };
					Color color{ m_aCaptionColor[(int)state].A > 0 ? m_aCaptionColor[(int)state] : getFont()->Color };
					if (color.A > 0 && y + m_fRowHeight >= m_sBorderWidth.Top && y < getHeight() - m_sBorderWidth.Bottom)
					{
						renderer
							->ActivateTarget(clip_caption)
							->Clear(Color{ 0, 0, 0, 0 });

						DrawSimpleBackground(renderer, clip_caption_rect, RectF{ m_aCaptionBorderWidth[(int)state], m_aCaptionBorderWidth[(int)state], m_aCaptionBorderWidth[(int)state],
							m_aCaptionBorderWidth[(int)state] }, RectF{ 0, 0, 0, 0 }, BorderColor{ m_aCaptionBorderColor[(int)state], m_aCaptionBorderColor[(int)state], m_aCaptionBorderColor[(int)state],
							m_aCaptionBorderColor[(int)state] }, m_aCaptionBackgroundColor[(int)state], m_aCaptionBackgroundGradient[(int)state]);

						CStoreBlock s_block{ renderer };
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_fCaptionPadding, (m_fRowHeight - line_height) * 0.5f, 0))
							->DrawText((*pos)->getName(), pf, getFont()->Distance, color)
							->ActivateTarget(old)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x_caption + clip_caption_rect.Left, y + clip_caption_rect.Top, 0))
							->ActivateBlock(getScroll()->isEnabled() ? &b : nullptr)
							->DrawImage(clip_caption, 1);
					}
				}

				// Value
				if (clip_value)
				{
					if (!isFocused() || int(pos - m_aEvents.begin()) != m_iFocusedEventIndex)
					{
						if (getFont()->Color.A > 0 && y + m_fRowHeight >= m_sBorderWidth.Top && y < getHeight() - m_sBorderWidth.Bottom)
						{
							String event_string{ (*pos)->getValue() };
							if (!event_string.empty())
							{
								CStoreBlock s_block{ renderer };
								CStorePrimitiveMatrix s_matrix{ renderer };
								renderer
									->ActivateTarget(clip_value)
									->Clear(Color{ 0, 0, 0, 0 })
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_fCaptionPadding, (m_fRowHeight - line_height) * 0.5f, 0))
									->DrawText(event_string, pf, getFont()->Distance, getFont()->Color)
									->ActivateTarget(old)
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x_value + clip_value_rect.Left, y + clip_value_rect.Top, 0))
									->ActivateBlock(getScroll()->isEnabled() ? &b : nullptr)
									->DrawImage(clip_value, 1);
							}
						}
					}
					else if (int(pos - m_aEvents.begin()) == m_iFocusedEventIndex && y + m_fRowHeight >= m_sBorderWidth.Top && y < getHeight() - m_sBorderWidth.Bottom)
					{
						renderer
							->ActivateTarget(clip_value)
							->Clear(Color{ 0, 0, 0, 0 });
						m_pHandler->Render(false, Identity, nullptr);
						CStoreBlock s_block{ renderer };
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivateTarget(old)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x_value + clip_value_rect.Left, y + clip_value_rect.Top, 0))
							->ActivateBlock(getScroll()->isEnabled() ? &b : nullptr)
							->DrawImage(clip_value, 1);
					}
				}
				y += m_fRowHeight;
			}
			if (clip_caption)
				clip_caption->Release();
			if (clip_value)
				clip_value->Release();

			// Scroll
			getScroll()->setSize(PointF{ getScroll()->getSize().X, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom });
			getScroll()->Render(false, ntl::Mat4Translate<float>(getWidth() - m_sBorderWidth.Left - getScroll()->getSize().X, m_sBorderWidth.Top, 0), nullptr);
		}

		void CEventEditor::RenderHandler() // Called at second render pass
		{
			Update();
			if (isFocused() && m_pHandler && m_fHandlerY + m_fRowHeight >= m_sBorderWidth.Top && m_fHandlerY < getHeight() - m_sBorderWidth.Bottom)
				m_pHandler->Render(true, getTransformMatrix() * ntl::Mat4Translate<float>(CalculateHandlerX(), m_fHandlerY, 0), nullptr);
		}
	#pragma endregion
	}
}