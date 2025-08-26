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
		const float CCustomTreeView::ItemHeightAuto{ -1 };
		const float CCustomTreeView::ItemHeightText{ 0 };

	#pragma region CGradientListener
		CCustomTreeView::CGradientListener::CGradientListener(CCustomTreeView *control) :
			m_pControl{ control }
		{

		}

		void CCustomTreeView::CGradientListener::NotifyOnChange()
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
		CCustomTreeView::CCustomTreeView(const String &class_name) :
			CControl(class_name, true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sPadding{ 1, 1, 1, 1 },
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
			m_aCornerColor{
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 } },
			m_fItemHeight{ -1 },
			m_sFolderSize{ 9, 9 },
			m_sFolderLinesColor{ 200, 200, 200, 255 },
			m_aFolderBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aFolderBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aFolderBorderColor{
				BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
				BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } } },
			m_aFolderBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aFolderBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aFolderSignSize{
				PointF{ 5, 1 },
				PointF{ 5, 1 } },
			m_aFolderSignColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 } },
			m_bMultiselect{ true },
			m_bMovable{ true },
			m_eHScrollVisibility{ ScrollVisibility::Auto },
			m_eVScrollVisibility{ ScrollVisibility::Auto },
			m_fScrollInterval{ 0.3f },
			m_fScrollDelta{ 10 },
			m_pCanvas{ nullptr },
			m_pVScroll{ nullptr },
			m_pHScroll{ nullptr },
			m_pListItemOwner{ nullptr },
			m_cScrollListener{ this },
			m_bHScrollVisible{ false },
			m_bVScrollVisible{ false },
			m_iLockUpdate{ 0 },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None },
			m_pHoveredItem{ nullptr },
			m_bIgnoreGradient{ false },
			m_bItemsSorted{ true },
			OnSelectItem{ nullptr },
			OnDeselectItem{ nullptr },
			OnMovingSelection{ nullptr },
			OnMoveSelection{ nullptr },
			OnActivateItem{ nullptr },
			OnDeactivateItem{ nullptr }
		{
			setService(new CCustomTreeViewService(this), true);
			m_cRootItem.QueryService()->setOwner(QueryListItemOwner());
			setSize(PointF{ 121, 97 });
		}

		CCustomTreeView::~CCustomTreeView()
		{
			if (m_pListItemOwner)
				m_pListItemOwner->Release();
		}
	#pragma endregion

	#pragma region Interface getters
		IListItem *CCustomTreeView::getRootItem()
		{
			return &m_cRootItem;
		}

		RectF CCustomTreeView::getClientRect()
		{
			RectF result{
				m_sBorderWidth.Left + m_sPadding.Left,
				m_sBorderWidth.Top + m_sPadding.Top,
				getWidth() - m_sBorderWidth.Right - m_sPadding.Right - (m_bVScrollVisible ? getVScroll()->getWidth() : 0),
				getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom - (m_bHScrollVisible ? getHScroll()->getHeight() : 0)
			};
			result.validate();
			return result;
		}

		RectF CCustomTreeView::getRenderRect()
		{
			State state{ getState() };
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}

		IListItemOwner *CCustomTreeView::QueryListItemOwner()
		{
			if (!m_pListItemOwner)
				m_pListItemOwner = new CCustomTreeViewListItemOwner(this);
			return m_pListItemOwner;
		}
	#pragma endregion

	#pragma region Getters
		IListItem *CCustomTreeView::getActiveItem()
		{
			return FindActiveItem(&m_cRootItem);
		}

		CCustomTreeView::State CCustomTreeView::getState()
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

		RectF CCustomTreeView::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CCustomTreeView::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		RectF CCustomTreeView::getPadding() const
		{
			return m_sPadding;
		}

		BorderColor CCustomTreeView::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CCustomTreeView::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CCustomTreeView::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CCustomTreeView::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CCustomTreeView::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CCustomTreeView::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		Color CCustomTreeView::getCornerColor(const State state) const
		{
			return m_aCornerColor[(int)state];
		}

		float CCustomTreeView::getItemHeight() const
		{
			return m_fItemHeight;
		}

		PointF CCustomTreeView::getFolderSize() const
		{
			return m_sFolderSize;
		}

		Color CCustomTreeView::getFolderLinesColor() const
		{
			return m_sFolderLinesColor;
		}

		RectF CCustomTreeView::getFolderBorderWidth(const FolderState state) const
		{
			return m_aFolderBorderWidth[(int)state];
		}

		RectF CCustomTreeView::getFolderBorderRadius(const FolderState state) const
		{
			return m_aFolderBorderRadius[(int)state];
		}

		BorderColor CCustomTreeView::getFolderBorderColor(const FolderState state) const
		{
			return m_aFolderBorderColor[(int)state];
		}

		Color CCustomTreeView::getFolderBackgroundColor(const FolderState state) const
		{
			return m_aFolderBackgroundColor[(int)state];
		}

		Gradient *CCustomTreeView::getFolderBackgroundGradient(const FolderState state)
		{
			return &m_aFolderBackgroundGradient[(int)state];
		}

		PointF CCustomTreeView::getFolderSignSize(const FolderState state) const
		{
			return m_aFolderSignSize[(int)state];
		}

		Color CCustomTreeView::getFolderSignColor(const FolderState state) const
		{
			return m_aFolderSignColor[(int)state];
		}

		bool CCustomTreeView::isMultiselect() const
		{
			return m_bMultiselect;
		}

		bool CCustomTreeView::isMovable() const
		{
			return m_bMovable;
		}

		ScrollVisibility CCustomTreeView::getHScrollVisibility() const
		{
			return m_eHScrollVisibility;
		}

		ScrollVisibility CCustomTreeView::getVScrollVisibility() const
		{
			return m_eVScrollVisibility;
		}

		float CCustomTreeView::getScrollInterval() const
		{
			return m_fScrollInterval;
		}

		float CCustomTreeView::getScrollDelta() const
		{
			return m_fScrollDelta;
		}

		bool CCustomTreeView::isFolded(IListItem *item)
		{
			SortItems();
			int index{ FindItemIndex(item) };
			if (index >= 0)
				return m_aItems[index].Folded;
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CCustomTreeView::setDPI(const Point &value)
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
				m_fItemHeight *= s.Y;
				m_sFolderSize *= s;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowShift[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
				}
				for (int i = 0; i <= (int)FolderState::Hovered; i++)
				{
					m_aFolderBorderWidth[i] *= s;
					m_aFolderBorderRadius[i] *= avg;
					m_aFolderSignSize[i] *= s;
				}
				SetListItemDPI(&m_cRootItem);
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				LockUpdate();
				m_sBorderWidth = value;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setBorderRadius(const RectF &value)
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

		bool CCustomTreeView::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				LockUpdate();
				m_sPadding = value;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
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

		bool CCustomTreeView::setLeftBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CCustomTreeView::setTopBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CCustomTreeView::setRightBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CCustomTreeView::setBottomBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CCustomTreeView::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
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

		bool CCustomTreeView::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (s == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowColor[(int)state] = value;
				if (s == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (s == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (s == state && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setShadowRadius(const State state, const int value)
		{
			if (value > 0 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (s == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (s == state && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setCornerColor(const State state, const Color &value)
		{
			if (value != m_aCornerColor[(int)state])
			{
				m_aCornerColor[(int)state] = value;
				if (getState() == state && m_bHScrollVisible && m_bVScrollVisible)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setItemHeight(const float value)
		{
			if (ntl::IsLess<float>(value, 0) && ntl::IsLess<float>(m_fItemHeight, 0))
				return false;
			if (ntl::IsNotEqual<float>(value, m_fItemHeight))
			{
				LockUpdate();
				if (ntl::IsLess<float>(value, 0))
					m_fItemHeight = -1;
				else
					m_fItemHeight = value;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setFolderSize(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sFolderSize))
			{
				m_sFolderSize = value;
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setFolderLinesColor(const Color &value)
		{
			if (value != m_sFolderLinesColor)
			{
				m_sFolderLinesColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setFolderBorderWidth(const FolderState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aFolderBorderWidth[(int)state]))
			{
				m_aFolderBorderWidth[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setFolderBorderRadius(const FolderState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aFolderBorderRadius[(int)state]))
			{
				m_aFolderBorderRadius[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setFolderBorderColor(const FolderState state, const BorderColor &value)
		{
			if (value != m_aFolderBorderColor[(int)state])
			{
				m_aFolderBorderColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setFolderBackgroundColor(const FolderState state, const Color &value)
		{
			if (value != m_aFolderBackgroundColor[(int)state])
			{
				m_aFolderBackgroundColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setFolderSignSize(const FolderState state, const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_aFolderSignSize[(int)state]))
			{
				m_aFolderSignSize[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setFolderSignColor(const FolderState state, const Color &value)
		{
			if (value != m_aFolderSignColor[(int)state])
			{
				m_aFolderSignColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setMultiselect(const bool value)
		{
			if (value != m_bMultiselect)
			{
				CLockRepaint lock{ this };
				m_bMultiselect = value;
				if (!m_bMultiselect)
					DeselectAllExceptFirst();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setMovable(const bool value)
		{
			if (value != m_bMovable)
			{
				m_bMovable = value;
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setHScrollVisibility(const ScrollVisibility value)
		{
			if (value != m_eHScrollVisibility)
			{
				LockUpdate();
				m_eHScrollVisibility = value;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setVScrollVisibility(const ScrollVisibility value)
		{
			if (value != m_eVScrollVisibility)
			{
				LockUpdate();
				m_eVScrollVisibility = value;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setScrollInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
			{
				m_fScrollInterval = value;
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setScrollDelta(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollDelta))
			{
				m_fScrollDelta = value;
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setFolded(IListItem *item, const bool value)
		{
			SortItems();
			int index{ FindItemIndex(item) };
			if (index >= 0 && m_aItems[index].Folded != value)
			{
				m_aItems[index].Folded = value;
				LockUpdate();
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomTreeView::setBorderColor(const BorderColor &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setBorderColor((State)i, value) || result;
			return result;
		}

		bool CCustomTreeView::setLeftBorderColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setLeftBorderColor((State)i, value) || result;
			return result;
		}

		bool CCustomTreeView::setTopBorderColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setTopBorderColor((State)i, value) || result;
			return result;
		}

		bool CCustomTreeView::setRightBorderColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setRightBorderColor((State)i, value) || result;
			return result;
		}

		bool CCustomTreeView::setBottomBorderColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setBottomBorderColor((State)i, value) || result;
			return result;
		}

		bool CCustomTreeView::setBackgroundColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setBackgroundColor((State)i, value) || result;
			return result;
		}

		bool CCustomTreeView::setShadowColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setShadowColor((State)i, value) || result;
			return result;
		}

		bool CCustomTreeView::setShadowShift(const PointF &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setShadowShift((State)i, value) || result;
			return result;
		}

		bool CCustomTreeView::setShadowRadius(const int value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setShadowRadius((State)i, value) || result;
			return result;
		}

		bool CCustomTreeView::setCornerColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setCornerColor((State)i, value) || result;
			return result;
		}
	#pragma endregion

	#pragma region Helpers
		void CCustomTreeView::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getVScroll()->Refresh();
			getHScroll()->Refresh();
			CControl::Refresh(refresh_children);
		}

		void CCustomTreeView::UpdateFromStyle(IStyle *style)
		{
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String name;
				switch ((State)i)
				{
				case State::Hovered:
					name = L"Hovered";
					break;
				case State::Focused:
					name = L"Focused";
					break;
				case State::FocusedHovered:
					name = L"FocusedHovered";
					break;
				case State::Disabled:
					name = L"Disabled";
					break;
				default:
					name = L"Normal";
				}
				style->getOption(m_sClassName + L".BorderColor[" + name + L"]", m_aBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + name + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + name + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + name + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + name + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + name + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".CornerColor[" + name + L"]", m_aCornerColor[i]);
			}
			style->getOption(m_sClassName + L".ItemHeight", m_fItemHeight);
			style->getOption(m_sClassName + L".FolderSize", m_sFolderSize);
			style->getOption(m_sClassName + L".FolderLinesColor", m_sFolderLinesColor);
			for (int i = 0; i <= (int)FolderState::Hovered; i++)
			{
				String name;
				switch ((FolderState)i)
				{
				case FolderState::Hovered:
					name = L"Hovered";
					break;
				default:
					name = L"Normal";
				}
				style->getOption(m_sClassName + L".FolderBorderWidth[" + name + L"]", m_aFolderBorderWidth[i]);
				style->getOption(m_sClassName + L".FolderBorderRadius[" + name + L"]", m_aFolderBorderRadius[i]);
				style->getOption(m_sClassName + L".FolderBorderColor[" + name + L"]", m_aFolderBorderColor[i]);
				style->getOption(m_sClassName + L".FolderBackgroundColor[" + name + L"]", m_aFolderBackgroundColor[i]);
				style->getOption(m_sClassName + L".FolderBackgroundGradient[" + name + L"]", m_aFolderBackgroundGradient[i]);
				style->getOption(m_sClassName + L".FolderSignSize[" + name + L"]", m_aFolderSignSize[i]);
				style->getOption(m_sClassName + L".FolderSignColor[" + name + L"]", m_aFolderSignColor[i]);
			}
			style->getOption(m_sClassName + L".ScrollInterval", m_fScrollInterval);
			style->getOption(m_sClassName + L".ScrollDelta", m_fScrollDelta);
			QueryListItemOwner()->setIgnoreSizeChange(true);
			QueryListItemOwner()->setIgnoreRepaintRequired(true);
			UpdateItemFromStyle(&m_cRootItem);
			QueryListItemOwner()->setIgnoreSizeChange(false);
			QueryListItemOwner()->setIgnoreRepaintRequired(false);
			Update();
			UpdateHoveredElement();
		}

		IBuiltInScroll *CCustomTreeView::getVScroll()
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

		IBuiltInScroll *CCustomTreeView::getHScroll()
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

		void CCustomTreeView::LockUpdate()
		{
			m_iLockUpdate++;
		}

		void CCustomTreeView::UnlockUpdate()
		{
			if (--m_iLockUpdate <= 0)
			{
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
		}

		void CCustomTreeView::EnumItems(IListItem *item, void *param, FItemCallback callback, void(*enumerator)(void *param, IListItem *item, FItemCallback callback))
		{
			for (int i = 0; i < item->getItemCount(); i++)
			{
				enumerator(param, item->getItem(i), callback);
				EnumItems(item->getItem(i), param, callback, enumerator);
			}
		}

		void CCustomTreeView::EnumSelectedItems(void *param, FItemCallback callback)
		{
			if (callback)
				EnumItems(&m_cRootItem, param, callback, [](void *param, IListItem *item, FItemCallback callback) {
					if (item->isVisible() && item->isSelected())
						callback(param, item);
				});
		}

		void CCustomTreeView::SortItems()
		{
			if (!m_bItemsSorted)
			{
				std::sort(m_aItems.begin(), m_aItems.end(), [](const ITEM &a, const ITEM &b) {return a.Item < b.Item; });
				m_bItemsSorted = true;
			}
		}

		int CCustomTreeView::FindItemIndex(IListItem *item) // Assume m_aItems is sorted
		{
			ITEM s{ item };
			auto pos{ std::lower_bound(m_aItems.begin(), m_aItems.end(), s, [](const ITEM &a, const ITEM &b) {return a.Item < b.Item; }) };
			if (pos == m_aItems.end() || pos->Item != item)
				return -1;
			return int(pos - m_aItems.begin());
		}

		void CCustomTreeView::CalculateRequiredSize(IListItem *parent, PointF &required_size, const float line_height, const int level)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->QueryService()->getRequiredSize() };
					float height{ ntl::IsGreater<float>(m_fItemHeight, 0) ? m_fItemHeight : (ntl::IsEqual<float>(m_fItemHeight, 0) ? line_height : size.Y) };
					required_size.Y += height;
					required_size.X = ntl::Max<float>(required_size.X, size.X + height * (float)level);
					parent->getItem(i)->QueryService()->setSize(PointF{ size.X, height });
					if (parent->getItem(i)->getItemCount() > 0)
					{
						int index{ FindItemIndex(parent->getItem(i)) };
						if (index >= 0 && !m_aItems[index].Folded)
							CalculateRequiredSize(parent->getItem(i), required_size, line_height, level + 1);
					}
				}
		}

		void CCustomTreeView::Update()
		{
			if (getForm() && getForm()->getRenderer() && getFont() && getFont()->getPlatformFont(getForm()->getRenderer()))
			{
				// Client area
				RectF client{
					m_sBorderWidth.Left + m_sPadding.Left,
					m_sBorderWidth.Top + m_sPadding.Top,
					getWidth() - m_sBorderWidth.Right - m_sPadding.Right,
					getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom };
				if (m_eVScrollVisibility == ScrollVisibility::Visible)
					client.Right -= getVScroll()->getWidth();
				if (m_eHScrollVisibility == ScrollVisibility::Visible)
					client.Bottom -= getHScroll()->getHeight();
				if (client.is_valid() && !client.is_zero())
				{
					SortItems();
					// Calculate required size
					float line_height{ getFont()->getPlatformFont(getForm()->getRenderer())->getStringSize(L"Wy", getFont()->Distance).Y };
					PointF required_size{ 0, 0 };
					CalculateRequiredSize(&m_cRootItem, required_size, line_height, 1);
					// Update scrolls
					if (ntl::IsGreater<float>(required_size.X, client.width()))
					{
						getHScroll()->setEnabled(isEnabled(false));
						switch (m_eHScrollVisibility)
						{
						case ScrollVisibility::None:
							m_bHScrollVisible = false;
							getHScroll()->setMax(required_size.X - client.width());
							break;
						default:
							m_bHScrollVisible = true;
							getHScroll()->setMax(required_size.X - client.width());
						}
					}
					else
					{
						getHScroll()->setScroll(0);
						getHScroll()->setEnabled(false);
						m_bHScrollVisible = m_eHScrollVisibility == ScrollVisibility::Visible;
					}
					if (ntl::IsGreater<float>(required_size.Y, client.height()))
					{
						getVScroll()->setEnabled(isEnabled(false));
						switch (m_eVScrollVisibility)
						{
						case ScrollVisibility::None:
							m_bVScrollVisible = false;
							getVScroll()->setMax(required_size.Y - client.height());
							break;
						default:
							m_bVScrollVisible = true;
							getVScroll()->setMax(required_size.Y - client.height());
						}
					}
					else
					{
						getVScroll()->setScroll(0);
						getVScroll()->setEnabled(false);
						m_bVScrollVisible = m_eVScrollVisibility == ScrollVisibility::Visible;
					}
					if (m_bHScrollVisible)
					{
						getHScroll()->setPosition(PointF{ m_sBorderWidth.Left, getHeight() - m_sBorderWidth.Bottom - getHScroll()->getHeight() });
						getHScroll()->setSize(PointF{ getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - (m_bVScrollVisible ? getVScroll()->getWidth() : 0), getHScroll()->getHeight() });
					}
					if (m_bVScrollVisible)
					{
						getVScroll()->setPosition(PointF{ getWidth() - m_sBorderWidth.Right - getVScroll()->getWidth(), m_sBorderWidth.Top });
						getVScroll()->setSize(PointF{ getVScroll()->getWidth(), getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - (m_bHScrollVisible ? getHScroll()->getHeight() : 0) });
					}
				}
			}
		}

		bool CCustomTreeView::UpdateHoveredElement()
		{
			if (getForm())
				return UpdateHoveredElement(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return false;
		}

		void CCustomTreeView::UpdateHoveredItem(IListItem *parent, const PointF &position, PointF &current, Element &element, IListItem **hovered, const float line_height)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (element != Element::None)
					return;
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->getSize() };
					if (position.X >= current.X && position.X < current.X + size.Y + size.X && position.Y >= current.Y && position.Y < current.Y + size.Y)
					{
						if (ntl::IsGreater<float>(m_sFolderSize.X, 0) && ntl::IsGreater<float>(m_sFolderSize.Y, 0))
						{
							RectF folder{ current.X + (size.Y - m_sFolderSize.X) / 2, current.Y + (size.Y - m_sFolderSize.Y) / 2 };
							folder.Right = folder.Left + m_sFolderSize.X;
							folder.Bottom = folder.Top + m_sFolderSize.Y;
							if (position.X >= folder.Left && position.X < folder.Right && position.Y >= folder.Top && position.Y < folder.Bottom)
							{
								element = Element::Folder;
								*hovered = parent->getItem(i);
								return;
							}
						}
						if (position.X >= current.X + size.Y)
						{
							element = Element::Item;
							*hovered = parent->getItem(i);
							return;
						}
					}
					current.Y += size.Y;
					if (parent->getItem(i)->getItemCount() > 0 && !m_aItems[FindItemIndex(parent->getItem(i))].Folded)
					{
						current.X += size.Y;
						UpdateHoveredItem(parent->getItem(i), position, current, element, hovered, line_height);
						current.X -= size.Y;
					}
				}
				if (current.Y >= getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom)
					break;
			}
		}

		bool CCustomTreeView::UpdateHoveredElement(const PointF &position)
		{
			if (m_eDownElement == Element::None)
			{
				Element new_element{ Element::None };
				IListItem *hovered{ nullptr };
				if (isEnabled(false))
				{
					RectF client{ m_sBorderWidth.Left, m_sBorderWidth.Top, getWidth() - m_sBorderWidth.Right, getHeight() - m_sBorderWidth.Bottom };
					if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
					{
						// VScroll
						if (m_bVScrollVisible)
						{
							if (position.X >= getVScroll()->getLeft() && position.X < getVScroll()->getLeft() + getVScroll()->getWidth() && position.Y >= getVScroll()->getTop() && position.Y < getVScroll()->getTop() + getVScroll()->getHeight())
								new_element = Element::VScroll;
							else
								client.Right -= getVScroll()->getWidth();
						}
						// HScroll
						if (new_element == Element::None && m_bHScrollVisible)
						{
							if (position.X >= getHScroll()->getLeft() && position.X < getHScroll()->getLeft() + getHScroll()->getWidth() && position.Y >= getHScroll()->getTop() && position.Y < getHScroll()->getTop() + getHScroll()->getHeight())
								new_element = Element::HScroll;
							else
								client.Bottom -= getHScroll()->getHeight();
						}
						// Items and folders
						if (new_element == Element::None)
						{
							PointF current{
								m_sBorderWidth.Left + m_sPadding.Left - (getHScroll()->isEnabled() ? getHScroll()->getScroll() : 0),
								m_sBorderWidth.Top + m_sPadding.Top - (getVScroll()->isEnabled() ? getVScroll()->getScroll() : 0)
							};
							client.Left += m_sPadding.Left;
							client.Top += m_sPadding.Top;
							client.Right -= m_sPadding.Right;
							client.Bottom -= m_sPadding.Bottom;
							if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
								UpdateHoveredItem(&m_cRootItem, position, current, new_element, &hovered, getFont()->getPlatformFont(getForm()->getRenderer())->getStringSize(L"Wy", getFont()->Distance).Y);
						}
					}
				}
				if (new_element != m_eHoveredElement || hovered != m_pHoveredItem)
				{
					switch (m_eHoveredElement)
					{
					case Element::VScroll:
						getVScroll()->NotifyOnMouseLeave();
						break;
					case Element::HScroll:
						getHScroll()->NotifyOnMouseLeave();
						break;
					case Element::Item:
						if (m_pHoveredItem) // The method could be called after deleting item, so prev hovered item might not exist anymore
							m_pHoveredItem->QueryService()->setHovered(false);
						break;
					default:
						break;
					}
					m_eHoveredElement = new_element;
					m_pHoveredItem = hovered;
					switch (m_eHoveredElement)
					{
					case Element::VScroll:
						getVScroll()->NotifyOnMouseHover(PointF{ position.X - getVScroll()->getPosition().X, position.Y - getVScroll()->getPosition().Y });
						break;
					case Element::HScroll:
						getHScroll()->NotifyOnMouseHover(PointF{ position.X - getHScroll()->getPosition().X, position.Y - getHScroll()->getPosition().Y });
						break;
					case Element::Item:
						m_pHoveredItem->QueryService()->setHovered(true);
						break;
					default:
						break;
					}
					return true;
				}
			}
			return false;
		}

		void CCustomTreeView::DeselectAllExceptFirst(IListItem *parent, bool &first)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent->getItem(i)->isSelected())
				{
					if (first)
						first = false;
					else
						parent->getItem(i)->setSelected(false);
				}
				DeselectAllExceptFirst(parent->getItem(i), first);
			}
		}

		void CCustomTreeView::DeselectAllExceptFirst()
		{
			QueryListItemOwner()->setIgnoreDeselect(true);
			bool first{ true };
			DeselectAllExceptFirst(&m_cRootItem, first);
			QueryListItemOwner()->setIgnoreDeselect(true);
		}

		bool CCustomTreeView::DeselectAllExceptItem(IListItem *parent, IListItem *exclude)
		{
			bool result{ false };
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent->getItem(i) != exclude && parent->getItem(i)->isSelected())
				{
					parent->getItem(i)->setSelected(false);
					result = true;
				}
				result = DeselectAllExceptItem(parent->getItem(i), exclude) || result;
			}
			return result;
		}

		void CCustomTreeView::DeactivateAllExceptItem(IListItem *parent, IListItem *exclude)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent->getItem(i) != exclude && parent->getItem(i)->isActive())
					parent->getItem(i)->setActive(false);
				DeactivateAllExceptItem(parent->getItem(i), exclude);
			}
		}

		bool CCustomTreeView::DeselectAllExceptParent(IListItem *parent, IListItem *exclude)
		{
			bool result{ false };
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent != exclude && parent->getItem(i)->isSelected())
					result = parent->getItem(i)->setSelected(false) || result;
				result = DeselectAllExceptParent(parent->getItem(i), exclude) || result;
			}
			return result;
		}

		bool CCustomTreeView::DeselectAllExceptParent(IListItem *exclude)
		{
			return DeselectAllExceptParent(&m_cRootItem, exclude);
		}

		void CCustomTreeView::UpdateItemFromStyle(IListItem *parent)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				parent->getItem(i)->QueryService()->UpdateFromStyle();
				UpdateItemFromStyle(parent->getItem(i));
			}
		}

		bool CCustomTreeView::ScrollToActiveItem(IListItem *parent, PointF &current, bool &changed)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->getSize() };
					if (parent->getItem(i)->isActive())
					{
						RectF client{ getClientRect() };
						if (getHScroll()->isEnabled())
						{
							if (current.X + size.Y + size.X >= client.Right)
							{
								if (getHScroll()->setScroll(getHScroll()->getScroll() + current.X + size.Y + size.X - client.Right))
									changed = true;
							}
							else if (current.X < client.Left)
							{
								if (getHScroll()->setScroll(getHScroll()->getScroll() - client.Left + current.X))
									changed = true;
							}
						}
						if (getVScroll()->isEnabled())
						{
							if (current.Y + size.Y >= client.Bottom)
							{
								if (getVScroll()->setScroll(getVScroll()->getScroll() + current.Y + size.Y - client.Bottom))
									changed = true;
							}
							else if (current.Y < client.Top)
							{
								if (getVScroll()->setScroll(getVScroll()->getScroll() - client.Top + current.Y))
									changed = true;
							}
						}
						return true;
					}
					current.Y += size.Y;
					if (!m_aItems[FindItemIndex(parent->getItem(i))].Folded)
					{
						current.X += size.X;
						if (ScrollToActiveItem(parent->getItem(i), current, changed))
							return true;
						current.X -= size.X;
					}
				}
			return false;
		}

		bool CCustomTreeView::ScrollToActiveItem()
		{
			if (getHScroll()->isEnabled() || getVScroll()->isEnabled())
			{
				PointF current{ m_sBorderWidth.Left + m_sPadding.Left - getHScroll()->getScroll(), m_sBorderWidth.Top + m_sPadding.Top - getVScroll()->getScroll() };
				bool changed{ false };
				if (ScrollToActiveItem(&m_cRootItem, current, changed))
					if (changed)
					{
						if (m_pCanvas)
							m_pCanvas->setValid(false);
						Repaint(false);
						return true;
					}
			}
			return false;
		}

		bool CCustomTreeView::FoldAll()
		{
			bool result{ false };
			for (auto &pos : m_aItems)
				if (!pos.Folded)
				{
					pos.Folded = true;
					result = true;
				}
			if (result)
			{
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CCustomTreeView::UnfoldAll()
		{
			bool result{ false };
			for (auto &pos : m_aItems)
				if (pos.Folded)
				{
					pos.Folded = false;
					result = true;
				}
			if (result)
			{
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CCustomTreeView::Fold(IListItem *item)
		{
			for (auto &pos : m_aItems)
				if (pos.Item == item)
				{
					if (!pos.Folded)
					{
						pos.Folded = true;
						Update();
						UpdateHoveredElement();
						if (m_pCanvas)
							m_pCanvas->setValid(false);
						Repaint(false);
						return true;
					}
					break;
				}
			return false;
		}

		bool CCustomTreeView::Unfold(IListItem *item)
		{
			for (auto &pos : m_aItems)
				if (pos.Item == item)
				{
					if (pos.Folded)
					{
						pos.Folded = false;
						Update();
						UpdateHoveredElement();
						if (m_pCanvas)
							m_pCanvas->setValid(false);
						Repaint(false);
						return true;
					}
					break;
				}
			return false;
		}

		IListItem *CCustomTreeView::FindActiveItem(IListItem *parent)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent->getItem(i)->isActive())
					return parent->getItem(i);
				IListItem *a{ FindActiveItem(parent->getItem(i)) };
				if (a)
					return a;
			}
			return nullptr;
		}

		void CCustomTreeView::SetListItemDPI(IListItem *parent)
		{
			parent->QueryService()->setDPI(getDPI());
			for (int i = 0; i < parent->getItemCount(); i++)
				SetListItemDPI(parent->getItem(i));
		}
	#pragma endregion

	#pragma region Paint
		void CCustomTreeView::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				SortItems();
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
				RenderItems(renderer, disp, state);
				RenderScrolls(renderer, disp);
				RenderCorner(renderer, disp, state);
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CCustomTreeView::RenderItems(IRenderer *renderer, const PointF &disp, const State state)
		{
			RectF client{ getClientRect() };
			if (!client.is_zero() && m_cRootItem.getItemCount() > 0)
			{
				PointF current{ std::round(-getHScroll()->getScroll()), std::round(-getVScroll()->getScroll()) };
				ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(client.width()), ntl::Round<int>(client.height()), 1, TextureFormat::RGBA, true) };
				if (clip)
				{
					renderer
						->ActivateTarget(clip)
						->Clear(Color{ 0, 0, 0, 0 });
					ITexture *folder_normal_folded{ nullptr }, *folder_hovered_folded{ nullptr }, *folder_normal{ nullptr }, *folder_hovered{ nullptr }, *clip_items{ nullptr };
					RenderItems(
						&m_cRootItem,
						renderer,
						current,
						getFont()->getPlatformFont(renderer)->getStringSize(L"Wy", getFont()->Distance).Y,
						client.height(),
						&folder_normal_folded,
						&folder_hovered_folded,
						&folder_normal,
						&folder_hovered,
						&clip_items);
					if (folder_normal_folded)
						folder_normal_folded->Release();
					if (folder_hovered_folded)
						folder_hovered_folded->Release();
					if (folder_normal)
						folder_normal->Release();
					if (folder_hovered)
						folder_hovered->Release();
					if (clip_items)
						clip_items->Release();
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateTarget(m_pCanvas)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(disp.X + client.Left, disp.Y + client.Top, 0));
					if (ntl::IsGreater<float>(m_sBorderRadius.Left, ntl::Min<float>(m_sBorderWidth.Left + m_sPadding.Left, m_sBorderWidth.Top + m_sPadding.Top)) ||
						ntl::IsGreater<float>(m_sBorderRadius.Top, ntl::Min<float>(m_sBorderWidth.Top + m_sPadding.Top, m_sBorderWidth.Right + m_sPadding.Right)) ||
						ntl::IsGreater<float>(m_sBorderRadius.Right, ntl::Min<float>(m_sBorderWidth.Right + m_sPadding.Right, m_sBorderWidth.Bottom + m_sPadding.Bottom)) ||
						ntl::IsGreater<float>(m_sBorderRadius.Bottom, ntl::Min<float>(m_sBorderWidth.Bottom + m_sPadding.Bottom, m_sBorderWidth.Left + m_sPadding.Left)))
					{
						Block b{
							RectF{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() },
							RectF{
								m_sBorderWidth.Left + m_sPadding.Left,
								m_sBorderWidth.Top + m_sPadding.Top,
								m_sBorderWidth.Right + m_sPadding.Right + (m_bVScrollVisible ? getVScroll()->getWidth() : 0),
								m_sBorderWidth.Bottom + m_sPadding.Bottom + (m_bHScrollVisible ? getHScroll()->getHeight() : 0),
							},
							m_sBorderRadius,
							PointLocation::Inside
						};
						CStoreBlock s_block{ renderer };
						renderer
							->ActivateBlock(&b)
							->DrawImage(clip, 1);
					}
					else
						renderer->DrawImage(clip, 1);
					clip->Release();
				}
			}
		}

		void CCustomTreeView::RenderItems(IListItem *parent, IRenderer *renderer, PointF &current, const float line_height, const float client_height, ITexture **folder_normal_folded,
			ITexture **folder_hovered_folded, ITexture **folder_normal, ITexture **folder_hovered, ITexture **clip_items)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->getSize() };
					bool folded{ m_aItems[FindItemIndex(parent->getItem(i))].Folded };
					if (current.Y >= -size.Y)
					{
						// Folder
						if (parent->getItem(i)->getItemCount() > 0)
						{
							ITexture *folder{ RenderFolder(renderer, parent->getItem(i), folder_normal_folded, folder_hovered_folded, folder_normal, folder_hovered, folded) };
							if (folder)
							{
								{
									CStorePrimitiveMatrix s_matrix{ renderer };
									renderer
										->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(current.X + (size.Y - folder->Widthf) / 2, current.Y + (size.Y - folder->Heightf) / 2, 0))
										->DrawImage(folder, 1);
								}
								if (!folded && m_sFolderLinesColor.A > 0)
								{
									renderer->DrawLines({
										PointF{current.X + size.Y / 2, current.Y + size.Y},
										PointF{current.X + size.Y / 2, current.Y + size.Y + size.Y / 2},
										PointF{current.X + size.Y, current.Y + size.Y + size.Y / 2} },
										m_sFolderLinesColor,
										false);
								}
							}
						}
						// Item
						parent->getItem(i)->QueryService()->Render(ntl::Mat4Translate<float>(current.X + size.Y, current.Y, 0), nullptr, false, clip_items);
					}
					current.Y += size.Y;
					if (parent->getItem(i)->getItemCount() > 0 && !folded)
					{
						current.X += size.Y;
						RenderItems(parent->getItem(i), renderer, current, line_height, client_height, folder_normal_folded, folder_hovered_folded, folder_normal, folder_hovered, clip_items);
						current.X -= size.Y;
					}
				}
				if (current.Y >= client_height)
					break;
			}
		}

		ITexture *CCustomTreeView::RenderFolder(IRenderer *renderer, IListItem *item, ITexture **folder_normal_folded, ITexture **folder_hovered_folded, ITexture **folder_normal,
			ITexture **folder_hovered, const bool folded)
		{
			if (ntl::IsGreater<float>(m_sFolderSize.X, 0) && ntl::IsGreater<float>(m_sFolderSize.Y, 0))
			{
				FolderState state{ (m_eHoveredElement == Element::Folder && item == m_pHoveredItem) ? FolderState::Hovered : FolderState::Normal };
				ITexture **folder{ (m_eHoveredElement == Element::Folder && item == m_pHoveredItem) ? (folded ? folder_hovered_folded : folder_hovered): (folded ? folder_normal_folded : folder_normal) };
				if (!*folder)
				{
					*folder = renderer->CreateTexture(ntl::Round<int>(m_sFolderSize.X), ntl::Round<int>(m_sFolderSize.Y), 1, TextureFormat::RGBA, true);
					if (*folder)
					{
						CStoreTarget s_target{ renderer };
						renderer
							->ActivateTarget(*folder)
							->Clear(Color{ 0, 0, 0, 0 });
						DrawSimpleBackground(
							renderer,
							RectF{ 0, 0, m_sFolderSize.X, m_sFolderSize.Y },
							m_aFolderBorderWidth[(int)state],
							m_aFolderBorderRadius[(int)state],
							m_aFolderBorderColor[(int)state],
							m_aFolderBackgroundColor[(int)state],
							m_aFolderBackgroundGradient[(int)state]);
						if (ntl::IsGreater<float>(m_aFolderSignSize[(int)state].X, 0) && ntl::IsGreater<float>(m_aFolderSignSize[(int)state].Y, 0))
						{
							// Horizontal line
							PointF p{ (m_sFolderSize.X - m_aFolderSignSize[(int)state].X) / 2, (m_sFolderSize.Y - m_aFolderSignSize[(int)state].Y) / 2 };
							renderer->DrawRectangle(RectF{ p.X, p.Y, p.X + m_aFolderSignSize[(int)state].X, p.Y + m_aFolderSignSize[(int)state].Y }, m_aFolderSignColor[(int)state]);
							if (folded)
							{
								// Vertical line
								p = PointF{ (m_sFolderSize.X - m_aFolderSignSize[(int)state].Y) / 2, (m_sFolderSize.Y - m_aFolderSignSize[(int)state].X) / 2 };
								renderer->DrawRectangle(RectF{ p.X, p.Y, p.X + m_aFolderSignSize[(int)state].Y, p.Y + m_aFolderSignSize[(int)state].X }, m_aFolderSignColor[(int)state]);
							}
						}
					}
				}
				return *folder;
			}
			return nullptr;
		}

		void CCustomTreeView::RenderScrolls(IRenderer *renderer, const PointF &disp)
		{
			Block b{ RectF{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() }, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
			if (m_bHScrollVisible)
				getHScroll()->Render(false, ntl::Mat4Translate<float>(m_sBorderWidth.Left + disp.X, getHeight() - m_sBorderWidth.Bottom - getHScroll()->getSize().Y + disp.Y, 0), &b);
			if (m_bVScrollVisible)
				getVScroll()->Render(false, ntl::Mat4Translate<float>(getWidth() - m_sBorderWidth.Right - getVScroll()->getSize().X + disp.X, m_sBorderWidth.Top + disp.Y, 0), &b);
		}

		void CCustomTreeView::RenderCorner(IRenderer *renderer, const PointF &disp, const State state)
		{
			if (m_bVScrollVisible && m_bHScrollVisible && m_aCornerColor[(int)state].A > 0)
			{
				Block b{ RectF{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() }, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
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