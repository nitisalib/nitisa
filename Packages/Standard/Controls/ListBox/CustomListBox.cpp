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
	namespace standard
	{
	#pragma region CGradientListener
		CCustomListBox::CGradientListener::CGradientListener(CCustomListBox *control) :
			m_pControl{ control }
		{

		}

		void CCustomListBox::CGradientListener::NotifyOnChange()
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
		CCustomListBox::CCustomListBox(const String &class_name, const bool accept_form, const bool accept_control, const bool tab_stop) :
			CControlItemList(class_name, accept_form, accept_control, false, true, false, tab_stop),
			m_cGradientListener{ this },
			m_bSortable{ false },
			m_iActiveIndex{ -1 },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sPadding{ 1, 1, 1, 1 },
			m_fSearchResetInterval{ 2 },
			m_eHorizontalScrollBar{ ScrollVisibility::Auto },
			m_eVerticalScrollBar{ ScrollVisibility::Auto },
			m_iColumns{ 1 },
			m_bMultiselect{ true },
			m_fScrollInterval{ 0.3f },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowRadius{ 1, 1, 1, 1, 1 },
			m_aBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } } },
			m_aBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 244, 244, 244, 255 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aCornerColor{
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 } },
			m_pHScroll{ nullptr },
			m_pVScroll{ nullptr },
			m_bIgnoreGradient{ false },
			m_pListItemOwner{ nullptr },
			m_eHoveredElement{ CCustomListBoxService::Element::None },
			m_eDownElement{ CCustomListBoxService::Element::None },
			m_bSorted{ true },
			m_sLastSearch{ std::chrono::steady_clock::now() },
			m_sGrid{ 0, 0 },
			m_sItemSize{ 0, 0 },
			m_bHScroll{ false },
			m_bVScroll{ false },
			m_iDownIndex{ -1 },
			m_pDownItem{ nullptr },
			m_iLockUpdate{ 0 },
			m_bUpdateRequired{ false },
			m_pCanvas{ nullptr },
			m_cScrollListener{ this },
			OnActivate{ nullptr },
			OnSelect{ nullptr },
			OnDeselect{ nullptr }
		{
			setService(new CCustomListBoxService(this), true);
			setSize(PointF{ 121, 97 });
		}

		CCustomListBox::~CCustomListBox()
		{
			if (m_pHScroll)
				m_pHScroll->Release();
			if (m_pVScroll)
				m_pVScroll->Release();
			if (m_pListItemOwner)
				m_pListItemOwner->Release();
		}

		void CCustomListBox::BeforeRelease()
		{
			DeleteItems();
			CControlItemList::BeforeRelease();
		}
	#pragma endregion

	#pragma region CControl getters
		RectF CCustomListBox::getClientRect()
		{
			RectF result{
				m_sBorderWidth.Left + m_sPadding.Left,
				m_sBorderWidth.Top + m_sPadding.Top,
				getWidth() - m_sBorderWidth.Right - m_sPadding.Right,
				getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom
			};
			result.validate();
			return result;
		}

		RectF CCustomListBox::getRenderRect()
		{
			RectF result{ getRenderRect(State::Normal) };
			for (int i = 1; i <= (int)State::Disabled; i++)
				result += getRenderRect((State)i);
			return result;
		}

		IListItemOwner *CCustomListBox::QueryListItemOwner()
		{
			if (!m_pListItemOwner)
				m_pListItemOwner = new CCustomListBoxListItemOwner(this);
			return m_pListItemOwner;
		}
	#pragma endregion

	#pragma region Getters
		CCustomListBox::State CCustomListBox::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isFocused())
			{
				if (isHovered())
					return State::FocusedHovered;
				return State::Focused;
			}
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		bool CCustomListBox::isSortable() const
		{
			return m_bSortable;
		}

		int CCustomListBox::getActiveIndex()
		{
			return m_iActiveIndex;
		}

		RectF CCustomListBox::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CCustomListBox::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		RectF CCustomListBox::getPadding() const
		{
			return m_sPadding;
		}

		float CCustomListBox::getSearchResetInterval() const
		{
			return m_fSearchResetInterval;
		}

		ScrollVisibility CCustomListBox::getHorizontalScrollBar() const
		{
			return m_eHorizontalScrollBar;
		}

		ScrollVisibility CCustomListBox::getVerticalScrollBar() const
		{
			return m_eVerticalScrollBar;
		}

		int CCustomListBox::getColumns() const
		{
			return m_iColumns;
		}

		bool CCustomListBox::isMultiselect() const
		{
			return m_bMultiselect;
		}

		float CCustomListBox::getScrollInterval() const
		{
			return m_fScrollInterval;
		}

		Color CCustomListBox::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CCustomListBox::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CCustomListBox::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		BorderColor CCustomListBox::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CCustomListBox::getLeftBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CCustomListBox::getTopBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CCustomListBox::getRightBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CCustomListBox::getBottomBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		Color CCustomListBox::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CCustomListBox::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CCustomListBox::getCornerColor(const State state) const
		{
			return m_aCornerColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CCustomListBox::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				getHScroll()->setDPI(value);
				getVScroll()->setDPI(value);
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sPadding *= s;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowShift[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
				}
				for (int i = 0; i < getItemCount(); i++)
					getItem(i)->QueryService()->setDPI(value);
				Update();
				return true;
			}
			return false;
		}

		bool CCustomListBox::setHScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pHScroll)
			{
				value->setListener(&m_cScrollListener);
				value->NotifyOnFreeResources();
				if (value->isVertical())
				{
					CScroll *scroll{ cast<CScroll*>(value) };
					if (scroll)
						scroll->SwitchDirection(true);
					else
						value->setVertical(false);
				}
				value->setMin(0);
				if (m_pHScroll)
					m_pHScroll->Release();
				m_pHScroll = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomListBox::setVScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pVScroll)
			{
				value->setListener(&m_cScrollListener);
				value->NotifyOnFreeResources();
				if (!value->isVertical())
				{
					CScroll *scroll{ cast<CScroll*>(value) };
					if (scroll)
						scroll->SwitchDirection(true);
					else
						value->setVertical(true);
				}
				value->setMin(0);
				if (m_pVScroll)
					m_pVScroll->Release();
				m_pVScroll = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomListBox::setSortable(const bool value)
		{
			if (value != m_bSortable)
			{
				m_bSortable = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomListBox::setActiveIndex(const int value)
		{
			if (value < 0 && m_iActiveIndex < 0)
				return false;
			if (value < (int)m_aItems.size() && value != m_iActiveIndex)
			{
				CLockRepaint lock{ this };
				SortItems();
				if (m_iActiveIndex >= 0)
					m_aItems[m_iActiveIndex]->setActive(false);
				m_iActiveIndex = value >= 0 ? value : -1;
				if (m_iActiveIndex >= 0)
					m_aItems[m_iActiveIndex]->setActive(true);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomListBox::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomListBox::setBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderRadius))
			{
				m_sBorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomListBox::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomListBox::setSearchResetInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fSearchResetInterval))
			{
				m_fSearchResetInterval = value;
				return true;
			}
			return false;
		}

		bool CCustomListBox::setHorizontalScrollBar(const ScrollVisibility value)
		{
			if (value != m_eHorizontalScrollBar)
			{
				m_eHorizontalScrollBar = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomListBox::setVerticalScrollBar(const ScrollVisibility value)
		{
			if (value != m_eVerticalScrollBar)
			{
				m_eVerticalScrollBar = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomListBox::setColumns(const int value)
		{
			if (value >= 1 && value != m_iColumns)
			{
				m_iColumns = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomListBox::setMultiselect(const bool value)
		{
			if (value != m_bMultiselect)
			{
				m_bMultiselect = value;
				if (!m_bMultiselect)
				{
					CLockRepaint lock{ this };
					int found{ 0 };
					QueryListItemOwner()->setIgnoreSelect(true);
					for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
						if ((*pos)->isSelected() && found++ >= 1)
							(*pos)->setSelected(false);
					QueryListItemOwner()->setIgnoreSelect(false);
					if (found > 1)
					{
						if (m_pCanvas)
							m_pCanvas->setValid(false);
						Repaint(false);
					}
				}
				return true;
			}
			return false;
		}

		bool CCustomListBox::setScrollInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
			{
				m_fScrollInterval = value;
				if (getForm())
				{
					CCustomListBoxService *service{ cast<CCustomListBoxService*>(QueryService()) };
					if (service->m_hTimer)
						getForm()->ResetTimer(service->m_hTimer, m_fScrollInterval);
				}
				return true;
			}
			return false;
		}

		bool CCustomListBox::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				m_aShadowColor[(int)state] = value;
				if (getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomListBox::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomListBox::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomListBox::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomListBox::setLeftBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CCustomListBox::setTopBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CCustomListBox::setRightBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CCustomListBox::setBottomBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CCustomListBox::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (getState() == state && m_aBackgroundGradient[(int)state].getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomListBox::setCornerColor(const State state, const Color &value)
		{
			if (value != m_aCornerColor[(int)state])
			{
				m_aCornerColor[(int)state] = value;
				if (getState() == state)
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

	#pragma region Items
		bool CCustomListBox::InsertItem(IListItem *item, const int before)
		{
			CLockRepaint lock{ this };
			if (CControlItemList::InsertItem(item, before))
			{
				item->QueryService()->setOwner(QueryListItemOwner());
				item->QueryService()->setDPI(getDPI());
				m_bSorted = false;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomListBox::DeleteItem(const int index)
		{
			CLockRepaint lock{ this };
			SortItems();
			if (m_pDownItem && m_pDownItem == m_aItems[index])
				m_pDownItem = nullptr;
			if (CControlItemList::DeleteItem(index))
			{
				if (index < m_iActiveIndex)
					m_iActiveIndex--;
				else if (index == m_iActiveIndex)
					m_iActiveIndex = -1;
				m_iDownIndex = -1;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomListBox::DeleteItem(IListItem *item)
		{
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if (*pos == item)
					return DeleteItem(int(pos - m_aItems.begin()));
			return false;
		}

		bool CCustomListBox::DeleteItems()
		{
			if (CControlItemList::DeleteItems())
			{
				m_iActiveIndex = -1;
				m_iDownIndex = -1;
				m_pDownItem = nullptr;
				m_bSorted = true;
				Update();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CCustomListBox::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getVScroll()->Refresh();
			getHScroll()->Refresh();
			CControl::Refresh(refresh_children);
		}

		IBuiltInScroll *CCustomListBox::getHScroll()
		{
			if (!m_pHScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				scroll->setListener(&m_cScrollListener);
				m_pHScroll = scroll;
				if (scroll->isVertical())
					scroll->SwitchDirection(true);
			}
			return m_pHScroll;
		}

		IBuiltInScroll *CCustomListBox::getVScroll()
		{
			if (!m_pVScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				scroll->setListener(&m_cScrollListener);
				m_pVScroll = scroll;
				if (!scroll->isVertical())
					scroll->SwitchDirection(true);
			}
			return m_pVScroll;
		}

		RectF CCustomListBox::getRenderRect(const State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}

		IListItem *CCustomListBox::getItemAtPoint(const PointF &position)
		{
			if (m_aItems.size() > 0)
			{
				RectF client{ getRealClientRect() };
				if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
				{
					Point p{ getGridCell(client, position) };
					if (p.X >= 0 && p.X < m_sGrid.X && p.Y >= 0 && p.Y < m_sGrid.Y)
					{
						int index{ p.Y * m_sGrid.X + p.X };
						if (index >= 0 && index < (int)m_aItems.size())
						{
							SortItems();
							return m_aItems[index];
						}
					}
				}
			}
			return nullptr;
		}

		Point CCustomListBox::getGridCell(const PointF &position)
		{
			if (m_aItems.size() > 0)
				return getGridCell(getRealClientRect(), position);
			return Point{ 0, 0 };
		}

		Point CCustomListBox::getGridCell(const RectF &client, const PointF &position)
		{
			if (m_aItems.size() > 0)
			{
				PointF p{ position.X - client.Left + (getHScroll()->isEnabled() ? getHScroll()->getScroll() : 0), position.Y - client.Top + (getVScroll()->isEnabled() ? getVScroll()->getScroll() : 0) };
				return Point{ int(p.X / m_sItemSize.X), int(p.Y / m_sItemSize.Y) };
			}
			return Point{ 0, 0 };
		}

		RectF CCustomListBox::getRealClientRect()
		{
			RectF client{ getClientRect() };
			if (m_bVScroll)
				client.Right -= getVScroll()->getSize().X;
			if (m_bHScroll)
				client.Bottom -= getHScroll()->getSize().Y;
			client.validate();
			return client;
		}

		Point CCustomListBox::IndexToGrid(const int value)
		{
			return Point{ value % m_iColumns, int(value / m_iColumns) };
		}

		int CCustomListBox::GridToIndex(const Point &value)
		{
			return value.Y * m_iColumns + value.X;
		}

		bool CCustomListBox::ScrollToActiveItem()
		{
			if (m_iActiveIndex >= 0)
				return ScrollToItem(m_iActiveIndex);
			return false;
		}

		bool CCustomListBox::ScrollToItem(const int index)
		{
			bool result{ false };
			RectF client{ getRealClientRect() };
			if (!client.is_empty())
			{
				// Item coords in control coordinates
				PointF pos1{ m_aItems[index]->getPosition() }, pos{ pos1 };
				if (getVScroll()->isEnabled())
					pos.Y -= getVScroll()->getScroll();
				if (getHScroll()->isEnabled())
					pos.X -= getHScroll()->getScroll();
				// HScroll
				if (getHScroll()->isEnabled())
				{
					if (pos.X + m_sItemSize.X > client.Right)
					{
						result = getHScroll()->setScroll(getHScroll()->getScroll() + pos.X + m_sItemSize.X - client.Right) || result;
						pos.X = pos1.X - getHScroll()->getScroll();
					}
					if (pos.X < client.Left)
						result = getHScroll()->setScroll(getHScroll()->getScroll() - client.Left + pos.X) || result;
				}
				// VScroll
				if (getVScroll()->isEnabled())
				{
					if (pos.Y < client.Top)
						result = getVScroll()->setScroll(getVScroll()->getScroll() - client.Top + pos.Y) || result;
					else if (pos.Y + m_sItemSize.Y > client.Bottom)
						result = getVScroll()->setScroll(getVScroll()->getScroll() + pos.Y + m_sItemSize.Y - client.Bottom) || result;
				}
			}
			return result;
		}

		void CCustomListBox::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Hovered:
					state = L"Hovered";
					break;
				case State::Focused:
					state = L"Focused";
					break;
				case State::FocusedHovered:
					state = L"FocusedHovered";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".CornerColor[" + state + L"]", m_aCornerColor[i]);
			}
			getHScroll()->UpdateFromStyle(style, m_sClassName + L".Scroll");
			getVScroll()->UpdateFromStyle(style, m_sClassName + L".Scroll");
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				(*pos)->QueryService()->UpdateFromStyle();
			UpdateList();
			UpdateHoveredItem();
			m_bIgnoreGradient = false;
		}

		void CCustomListBox::UpdateList()
		{
			// Item sizes
			m_sItemSize = PointF{ 0, 0 };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			{
				PointF size{ (*pos)->QueryService()->getRequiredSize() };
				m_sItemSize.X = ntl::Max<float>(m_sItemSize.X, size.X);
				m_sItemSize.Y = ntl::Max<float>(m_sItemSize.Y, size.Y);
			}
			// Grid
			if (m_aItems.size() > 0)
			{
				m_sGrid.X = ntl::Min<int>((int)m_aItems.size(), m_iColumns);
				m_sGrid.Y = (int)m_aItems.size() / m_iColumns;
				if ((int)m_aItems.size() % m_iColumns > 0)
					m_sGrid.Y++;
			}
			else
				m_sGrid = Point{ 0, 0 };
			// HScroll visibility
			RectF client{ getClientRect() };
			PointF grid_size{ (float)m_sGrid.X * m_sItemSize.X, (float)m_sGrid.Y * m_sItemSize.Y };
			switch (m_eHorizontalScrollBar)
			{
			case ScrollVisibility::None:
				m_bHScroll = false; // HScroll is never visible
				break;
			case ScrollVisibility::Visible:
				m_bHScroll = true; // HScroll is always visible
				break;
			default:
				if (ntl::IsGreater<float>(grid_size.X, client.width())) // Items width is greater then client area max width
					m_bHScroll = true;
				else if (ntl::IsLessOrEqual<float>(grid_size.X, client.width() - getVScroll()->getSize().X)) // Items width is less than client area min width
					m_bHScroll = false;
				else // HScroll visibility depends on VScroll visibility
					switch (m_eVerticalScrollBar)
					{
					case ScrollVisibility::None:
						m_bHScroll = false; // VScroll is invisible, so HScroll is invisible too
						break;
					case ScrollVisibility::Visible:
						m_bHScroll = true; // VScroll is visible, so HScroll is visible too
						break;
					default:
						m_bHScroll = ntl::IsGreater<float>(grid_size.Y, client.height()); // HScroll is visible only if items height is greater than client area max height
					}
			}
			// VScroll visibility
			switch (m_eVerticalScrollBar)
			{
			case ScrollVisibility::None:
				m_bVScroll = false; // VScroll is never visible
				break;
			case ScrollVisibility::Visible:
				m_bVScroll = true; // VScroll is always visible
				break;
			default:
				if (ntl::IsGreater<float>(grid_size.Y, client.height())) // Items height is greater than client area max height
					m_bVScroll = true;
				else if (ntl::IsLessOrEqual<float>(grid_size.Y, client.height() - getHScroll()->getSize().Y)) // Items height is less than client area min height
					m_bVScroll = false;
				else // Items height is somewhere between min and max client area height, so VScroll is visible only if HScroll is visible
					m_bVScroll = m_bHScroll;
			}
			// New client rect(without scrolls)
			RectF new_client{ client };
			if (m_bHScroll)
				new_client.Bottom -= getHScroll()->getSize().Y;
			if (m_bVScroll)
				new_client.Right -= getVScroll()->getSize().X;
			new_client.validate();
			// Scroll's params
			getHScroll()->setEnabled(ntl::IsGreater<float>(grid_size.X, new_client.width()));
			getVScroll()->setEnabled(ntl::IsGreater<float>(grid_size.Y, new_client.height()));
			if (getHScroll()->isEnabled())
				getHScroll()->setMax(grid_size.X - new_client.width());
			if (getVScroll()->isEnabled())
				getVScroll()->setMax(grid_size.Y - new_client.height());
			if (m_bHScroll)
				getHScroll()->setSize(PointF{ getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - (m_bVScroll ? getVScroll()->getSize().X : 0), getHScroll()->getSize().Y });
			if (m_bVScroll)
				getVScroll()->setSize(PointF{ getVScroll()->getSize().X, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - (m_bHScroll ? getHScroll()->getSize().Y : 0) });
			// Adjust enabled state depending on control enabled state
			if (!isEnabled(false))
			{
				getHScroll()->setEnabled(false);
				getVScroll()->setEnabled(false);
			}
			// Adjust item width
			if (ntl::IsGreater<float>(new_client.width() / (float)m_iColumns, m_sItemSize.X))
				m_sItemSize.X = new_client.width() / (float)m_iColumns;
			// Set item sizes
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				(*pos)->QueryService()->setSize(m_sItemSize);
			// Set item positions
			int index{ 0 };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++, index++)
				(*pos)->QueryService()->setPosition(
					PointF{ m_sBorderWidth.Left + m_sPadding.Left + float(index % m_iColumns) * m_sItemSize.X, m_sBorderWidth.Top + m_sPadding.Top + float(index / m_iColumns) * m_sItemSize.Y });
		}

		bool CCustomListBox::UpdateHoveredItem()
		{
			if (getForm())
				return UpdateHoveredItem(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return false;
		}

		bool CCustomListBox::UpdateHoveredItem(const PointF &position)
		{
			SortItems();
			IListItem *hovered{ getItemAtPoint(position) };
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

		void CCustomListBox::SortItems()
		{
			if (m_bSortable && !m_bSorted && getCompareItems() && m_aItems.size() > 1)
			{
				IListItem *active{ m_iActiveIndex >= 0 ? m_aItems[m_iActiveIndex] : nullptr };
				std::sort(m_aItems.begin(), m_aItems.end(), getCompareItems());
				if (active)
					m_iActiveIndex = int(std::find(m_aItems.begin(), m_aItems.end(), active) - m_aItems.begin());
				m_bSorted = true;
			}
		}

		void CCustomListBox::Update()
		{
			if (m_iLockUpdate == 0)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			else
				m_bUpdateRequired = true;
		}

		CCustomListBox::FCompare CCustomListBox::getCompareItems()
		{
			return nullptr;
		}

		int CCustomListBox::Search(const String &search)
		{
			return -1;
		}

		void CCustomListBox::LockUpdate()
		{
			m_iLockUpdate++;
		}

		void CCustomListBox::UnlockUpdate()
		{
			if (m_iLockUpdate > 0)
				if (--m_iLockUpdate == 0 && m_bUpdateRequired)
				{
					UpdateList();
					UpdateHoveredItem();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
		}
	#pragma endregion

	#pragma region Paint
		void CCustomListBox::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				SortItems();
				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
				RenderItems(renderer, disp, rect);
				RenderScrolls(renderer, rect, disp);
				RenderCorner(renderer, state, rect, disp);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CCustomListBox::RenderItems(IRenderer *renderer, const PointF &disp, const RectF &rect)
		{
			if (m_aItems.size() > 0)
			{
				PointF p;
				RectF client{ getRealClientRect() };
				client += disp;
				RectF client_in_grid{ 0, 0, client.width(), client.height() };
				if (getHScroll()->isEnabled())
				{
					client_in_grid.Left += getHScroll()->getScroll();
					client_in_grid.Right += getHScroll()->getScroll();
				}
				if (getVScroll()->isEnabled())
				{
					client_in_grid.Top += getVScroll()->getScroll();
					client_in_grid.Bottom += getVScroll()->getScroll();
				}
				int
					x1{ ntl::Min<int>(m_sGrid.X - 1, ntl::Max<int>(0, int(client_in_grid.Left / m_sItemSize.X))) },
					x2{ ntl::Min<int>(m_sGrid.X - 1, ntl::Max<int>(0, int(client_in_grid.Right / m_sItemSize.X))) },
					y1{ ntl::Min<int>(m_sGrid.Y - 1, ntl::Max<int>(0, int(client_in_grid.Top / m_sItemSize.Y))) },
					y2{ ntl::Min<int>(m_sGrid.Y - 1, ntl::Max<int>(0, int(client_in_grid.Bottom / m_sItemSize.Y))) };
				Block b{ rect, RectF{ client.Left - rect.Left, client.Top - rect.Top, rect.Right - client.Right, rect.Bottom - client.Bottom }, m_sBorderRadius, PointLocation::Inside };
				ITexture *clip{ nullptr };
				for (int y = y1; y <= y2; y++)
					for (int x = x1; x <= x2; x++)
					{
						int index{ y * m_iColumns + x };
						if (index < (int)m_aItems.size())
						{
							p.X = m_aItems[index]->getPosition().X - (getHScroll()->isEnabled() ? getHScroll()->getScroll() : 0);
							p.Y = m_aItems[index]->getPosition().Y - (getVScroll()->isEnabled() ? getVScroll()->getScroll() : 0);
							m_aItems[index]->QueryService()->Render(ntl::Mat4Translate<float>(std::round(p.X + disp.X), std::round(p.Y + disp.Y), 0), &b, false, &clip);
						}
					}
				if (clip)
					clip->Release();
			}
		}

		void CCustomListBox::RenderScrolls(IRenderer *renderer, const RectF &rect, const PointF &disp)
		{
			Block b{ rect, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
			if (m_bHScroll)
				getHScroll()->Render(false, ntl::Mat4Translate<float>(m_sBorderWidth.Left + disp.X, getHeight() - m_sBorderWidth.Bottom - getHScroll()->getSize().Y + disp.Y, 0), &b);
			if (m_bVScroll)
				getVScroll()->Render(false, ntl::Mat4Translate<float>(getWidth() - m_sBorderWidth.Right - getVScroll()->getSize().X + disp.X, m_sBorderWidth.Top + disp.Y, 0), &b);
		}

		void CCustomListBox::RenderCorner(IRenderer *renderer, const State state, const RectF &rect, const PointF &disp)
		{
			if (m_bVScroll && m_bHScroll && m_aCornerColor[(int)state].A > 0)
			{
				Block b{ rect, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
				RectF r{
					getWidth() - m_sBorderWidth.Right - getVScroll()->getSize().X + disp.X,
					getHeight() - m_sBorderWidth.Bottom - getHScroll()->getSize().Y + disp.Y,
					getWidth() - m_sBorderWidth.Right + disp.X,
					getHeight() - m_sBorderWidth.Bottom + disp.Y };
				CStoreBlock s_block{ renderer };
				renderer
					->ActivateBlock(&b)
					->DrawRectangle(r, m_aCornerColor[(int)state]);
			}
		}
	#pragma endregion
	}
}