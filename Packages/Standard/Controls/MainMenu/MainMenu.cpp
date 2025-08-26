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
		const int MIN_SCROLL_HEIGHT{ 3 };

	#pragma region CGradientListener
		CMainMenu::CGradientListener::CGradientListener(CMainMenu *control) :
			m_pControl{ control }
		{

		}

		void CMainMenu::CGradientListener::NotifyOnChange()
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
		CMainMenu::CMainMenu() :
			CControl(L"MainMenu", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_pImageListEnabled{ nullptr },
			m_pImageListDisabled{ nullptr },
			m_sSubmenuBorderWidth{ 1, 1, 1, 1 },
			m_sSubmenuBorderRadius{ 0, 0, 0, 0 },
			m_sSubmenuBorderColor{ Color{ 152, 152, 152, 255 }, Color{ 152, 152, 152, 255 }, Color{ 152, 152, 152, 255 }, Color{ 152, 152, 152, 255 } },
			m_sSubmenuPadding{ 2, 2, 2, 2 },
			m_sSubmenuBackgroundColor{ 241, 241, 241, 255 },
			m_sSubmenuShadowColor{ 152, 152, 152, 200 },
			m_iSubmenuShadowRadius{ 3 },
			m_sSubmenuShadowShift{ 2, 2 },
			m_sSubmenuShift{ -5, -1 },
			m_fHotkeyMaxInterval{ 1.0 },
			m_fSubmenuScrollHeight{ 6 },
			m_sSubmenuScrollArrowColorNormal{ 0, 0, 0, 255 },
			m_sSubmenuScrollArrowColorHovered{ 64, 64, 64, 255 },
			m_sSubmenuScrollArrowColorDisabled{ 127, 127, 127, 255 },
			m_fScrollInterval{ ScrollInterval },
			m_fSubmenuDeltaScrollTimer{ 2 },
			m_fSubmenuDeltaScrollWheel{ 10 },
			m_fSubmenuMaxHeight{ 0 },
			m_cSubmenuBackgroundGradient{ &m_cGradientListener },
			m_sBorderWidth{ 0, 0, 0, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sPadding{ 4, 4, 4, 4 },
			m_aBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 182, 188, 204, 255 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 182, 188, 254, 255 } } },
			m_aBackgroundColor{
				Color{ 241, 241, 241, 255 },
				Color{ 241, 241, 241, 255 } },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aShadowRadius{ 1, 1 },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_fScrollWidth{ 8 },
			m_sScrollArrowColorNormal{ 0, 0, 0, 255 },
			m_sScrollArrowColorHovered{ 64, 64, 64, 255 },
			m_sScrollArrowColorDisabled{ 127, 127, 127, 255 },
			m_sRootSubmenuShift{ 0, -1 },
			m_pListItemOwner{ nullptr },
			m_pTransform{ nullptr },
			m_hScrollTimer{ 0 },
			m_pHoveredItem{ nullptr },
			m_bHoverStartScroller{ false },
			m_bHoverEndScroller{ false },
			m_pDownItem{ nullptr },
			m_cRootItem{ L"Root", true },
			m_bIgnoreGradient{ true },
			m_pCanvas{ nullptr },
			OnSelectItem{ nullptr },
			OnDeselectItem{ nullptr },
			OnActivateItem{ nullptr },
			OnDeactivateItem{ nullptr },
			OnDeleteItem{ nullptr },
			OnDeleteItems{ nullptr }
		{
			setService(new CMainMenuService(this), true);
			m_pTransform = new CMainMenuTransform(nullptr);
			CControl::setTransform(m_pTransform);
			m_sLastHotkey = std::chrono::steady_clock::now();
			setOwner(&m_cRootItem);
			m_aItems.push_back({ &m_cRootItem, true, 0, 0, PointF{ 0, 0 }, PointF{ 0, 0 }, false });
			m_aBackgroundGradient[(int)State::Normal].setPointCount(3);
			m_aBackgroundGradient[(int)State::Normal].setPointColor(0, Color{ 254, 254, 255, 255 });
			m_aBackgroundGradient[(int)State::Normal].setPointColor(1, Color{ 212, 219, 237, 255 });
			m_aBackgroundGradient[(int)State::Normal].setPointColor(2, Color{ 225, 230, 246, 255 });
			m_aBackgroundGradient[(int)State::Active].setPointCount(3);
			m_aBackgroundGradient[(int)State::Active].setPointColor(0, Color{ 254, 254, 255, 255 });
			m_aBackgroundGradient[(int)State::Active].setPointColor(1, Color{ 212, 219, 237, 255 });
			m_aBackgroundGradient[(int)State::Active].setPointColor(2, Color{ 225, 230, 246, 255 });
			m_bIgnoreGradient = false;
			setSize(PointF{ 105, 28 });
			CControl::setAlign(Align::Top);
		}

		CMainMenu::CMainMenu(IForm *parent) :CMainMenu()
		{
			setForm(parent);
		}

		CMainMenu::CMainMenu(IControl *parent) : CMainMenu()
		{
			setParent(parent);
		}

		CMainMenu::~CMainMenu()
		{
			if (m_pListItemOwner)
				m_pListItemOwner->Release();
		}
	#pragma endregion

	#pragma region CControl getters
		IControl *CMainMenu::getControl(const PointF &position)
		{
			if (isCaptureMouse() && TestPosition(&m_cRootItem, position))
				return this;
			return CControl::getControl(position);
		}

		RectF CMainMenu::getRenderRect()
		{
			RectF result{ 0, 0, 0, 0 };
			CalculateRenderRect(&m_cRootItem, result);
			result.Left -= m_aItems[0].Position.X;
			result.Top -= m_aItems[0].Position.Y;
			result.Right -= m_aItems[0].Position.X;
			result.Bottom -= m_aItems[0].Position.Y;
			return result;
		}

		bool CMainMenu::hasExtra()
		{
			for (int i = 0; i < m_cRootItem.getItemCount(); i++)
				if (m_cRootItem.getItem(i)->isVisible() && m_aItems[FindItemIndex(m_cRootItem.getItem(i))].Opended)
					return true;
			return false;
		}

		IListItemOwner *CMainMenu::QueryListItemOwner()
		{
			if (!m_pListItemOwner)
				m_pListItemOwner = new CMainMenuListItemOwner(this);
			return m_pListItemOwner;
		}
	#pragma endregion

	#pragma region Getters
		CMainMenu::State CMainMenu::getState()
		{
			return isFocused() ? State::Active : State::Normal;
		}

		IListItem *CMainMenu::getRootItem()
		{
			return &m_cRootItem;
		}

		int CMainMenu::getItemCount(const bool total)
		{
			return m_cRootItem.getItemCount(total);
		}

		IListItem *CMainMenu::getItem(const int index)
		{
			return m_cRootItem.getItem(index);
		}

		IListItem *CMainMenu::getItem(const String &name)
		{
			return m_cRootItem.getItem(name);
		}

		IListItem *CMainMenu::getItem(const PointF &position)
		{
			bool t, b;
			IListItem *result{ getItem(&m_cRootItem, t, b, position) };
			if (t || b)
				return nullptr;
			return result;
		}

		IImageList *CMainMenu::getImageListEnabled()
		{
			return m_pImageListEnabled;
		}

		IImageList *CMainMenu::getImageListDisabled()
		{
			return m_pImageListDisabled;
		}

		RectF CMainMenu::getSubmenuBorderWidth() const
		{
			return m_sSubmenuBorderWidth;
		}

		RectF CMainMenu::getSubmenuBorderRadius() const
		{
			return m_sSubmenuBorderRadius;
		}

		BorderColor CMainMenu::getSubmenuBorderColor() const
		{
			return m_sSubmenuBorderColor;
		}

		Color CMainMenu::getSubmenuLeftBorderColor() const
		{
			return m_sSubmenuBorderColor.Left;
		}

		Color CMainMenu::getSubmenuTopBorderColor() const
		{
			return m_sSubmenuBorderColor.Top;
		}

		Color CMainMenu::getSubmenuRightBorderColor() const
		{
			return m_sSubmenuBorderColor.Right;
		}

		Color CMainMenu::getSubmenuBottomBorderColor() const
		{
			return m_sSubmenuBorderColor.Bottom;
		}

		RectF CMainMenu::getSubmenuPadding() const
		{
			return m_sSubmenuPadding;
		}

		Color CMainMenu::getSubmenuBackgroundColor() const
		{
			return m_sSubmenuBackgroundColor;
		}

		Color CMainMenu::getSubmenuShadowColor() const
		{
			return m_sSubmenuShadowColor;
		}

		int CMainMenu::getSubmenuShadowRadius() const
		{
			return m_iSubmenuShadowRadius;
		}

		PointF CMainMenu::getSubmenuShadowShift() const
		{
			return m_sSubmenuShadowShift;
		}

		float CMainMenu::getScroll() const
		{
			return m_aItems[0].Scroll;
		}

		float CMainMenu::getScrollMax() const
		{
			return m_aItems[0].ScrollMax;
		}

		float CMainMenu::getSubmenuScroll(IListItem *parent)
		{
			int parent_index{ FindItemIndex(parent) };
			if (parent_index >= 0)
				return m_aItems[parent_index].Scroll;
			return 0;
		}

		float CMainMenu::getSubmenuScrollMax(IListItem *parent)
		{
			int parent_index{ FindItemIndex(parent) };
			if (parent_index >= 0)
				return m_aItems[parent_index].ScrollMax;
			return 0;
		}

		PointF CMainMenu::getSubmenuShift() const
		{
			return m_sSubmenuShift;
		}

		float CMainMenu::getHotkeyMaxInterval() const
		{
			return m_fHotkeyMaxInterval;
		}

		float CMainMenu::getSubmenuScrollHeight() const
		{
			return m_fSubmenuScrollHeight;
		}

		Color CMainMenu::getSubmenuScrollArrowColorNormal() const
		{
			return m_sSubmenuScrollArrowColorNormal;
		}

		Color CMainMenu::getSubmenuScrollArrowColorHovered() const
		{
			return m_sSubmenuScrollArrowColorHovered;
		}

		Color CMainMenu::getSubmenuScrollArrowColorDisabled() const
		{
			return m_sSubmenuScrollArrowColorDisabled;
		}

		float CMainMenu::getScrollInterval() const
		{
			return m_fScrollInterval;
		}

		float CMainMenu::getSubmenuDeltaScrollTimer() const
		{
			return m_fSubmenuDeltaScrollTimer;
		}

		float CMainMenu::getSubmenuDeltaScrollWheel() const
		{
			return m_fSubmenuDeltaScrollWheel;
		}

		float CMainMenu::getSubmenuMaxHeight() const
		{
			return m_fSubmenuMaxHeight;
		}

		RectF CMainMenu::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CMainMenu::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		BorderColor CMainMenu::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CMainMenu::getLeftBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CMainMenu::getTopBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CMainMenu::getRightBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CMainMenu::getBottomBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		RectF CMainMenu::getPadding() const
		{
			return m_sPadding;
		}

		Color CMainMenu::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Color CMainMenu::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		int CMainMenu::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CMainMenu::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Gradient *CMainMenu::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Gradient *CMainMenu::getSubmenuBackgroundGradient()
		{
			return &m_cSubmenuBackgroundGradient;
		}

		float CMainMenu::getScrollWidth() const
		{
			return m_fScrollWidth;
		}

		Color CMainMenu::getScrollArrowColorNormal() const
		{
			return m_sScrollArrowColorNormal;
		}

		Color CMainMenu::getScrollArrowColorHovered() const
		{
			return m_sScrollArrowColorHovered;
		}

		Color CMainMenu::getScrollArrowColorDisabled() const
		{
			return m_sScrollArrowColorDisabled;
		}

		bool CMainMenu::isItemRightAligned(const int index)
		{
			int i{ FindItemIndex(m_cRootItem.getItem(index)) };
			if (i >= 0)
				return m_aItems[i].RightAligned;
			return false;
		}

		bool CMainMenu::isItemRightAligned(IListItem *item)
		{
			for (int i = 0; i < m_cRootItem.getItemCount(); i++)
				if (m_cRootItem.getItem(i) == item)
					return isItemRightAligned(i);
			return false;
		}

		PointF CMainMenu::getRootSubmenuShift() const
		{
			return m_sRootSubmenuShift;
		}
	#pragma endregion

	#pragma region CControl setters
		bool CMainMenu::setAlign(const Align value)
		{
			if (value == Align::Top || value == Align::None)
				return CControl::setAlign(value);
			return false;
		}

		bool CMainMenu::setConstraints(const RectF &value)
		{
			return false;
		}

		bool CMainMenu::setEnabled(const bool value)
		{
			return false;
		}

		bool CMainMenu::setTransform(ITransform *value)
		{
			return false;
		}

		bool CMainMenu::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sSubmenuBorderWidth *= s;
				m_sSubmenuBorderRadius *= avg;
				m_sSubmenuPadding *= s;
				m_iSubmenuShadowRadius = ntl::Round<int>((float)m_iSubmenuShadowRadius * avg);
				m_sSubmenuShift *= s;
				m_fSubmenuScrollHeight *= s.Y;
				m_fSubmenuDeltaScrollTimer *= s.Y;
				m_fSubmenuDeltaScrollWheel *= s.Y;
				m_fSubmenuMaxHeight *= s.Y;
				m_sBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sPadding *= s;
				for (int i = 0; i <= (int)State::Active; i++)
				{
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
				}
				m_fScrollWidth *= s.X;
				m_sRootSubmenuShift *= s;
				SetListItemDPI(&m_cRootItem);
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CMainMenu::setImageListEnabled(IImageList *value)
		{
			if (value != m_pImageListEnabled)
			{
				CLockRepaint lock{ this };
				m_pImageListEnabled = value;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				return true;
			}
			return false;
		}

		bool CMainMenu::setImageListDisabled(IImageList *value)
		{
			if (value != m_pImageListDisabled)
			{
				CLockRepaint lock{ this };
				m_pImageListDisabled = value;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sSubmenuBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sSubmenuBorderWidth = value;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sSubmenuBorderRadius))
			{
				m_sSubmenuBorderRadius = value;
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuBorderColor(const BorderColor &value)
		{
			if (value != m_sSubmenuBorderColor)
			{
				m_sSubmenuBorderColor = value;
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuLeftBorderColor(const Color &value)
		{
			return setSubmenuBorderColor(BorderColor{ value, m_sSubmenuBorderColor.Top, m_sSubmenuBorderColor.Right, m_sSubmenuBorderColor.Bottom });
		}

		bool CMainMenu::setSubmenuTopBorderColor(const Color &value)
		{
			return setSubmenuBorderColor(BorderColor{ m_sSubmenuBorderColor.Left, value, m_sSubmenuBorderColor.Right, m_sSubmenuBorderColor.Bottom });
		}

		bool CMainMenu::setSubmenuRightBorderColor(const Color &value)
		{
			return setSubmenuBorderColor(BorderColor{ m_sSubmenuBorderColor.Left, m_sSubmenuBorderColor.Top, value, m_sSubmenuBorderColor.Bottom });
		}

		bool CMainMenu::setSubmenuBottomBorderColor(const Color &value)
		{
			return setSubmenuBorderColor(BorderColor{ m_sSubmenuBorderColor.Left, m_sSubmenuBorderColor.Top, m_sSubmenuBorderColor.Right, value });
		}

		bool CMainMenu::setSubmenuPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sSubmenuPadding))
			{
				CLockRepaint lock{ this };
				m_sSubmenuPadding = value;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuBackgroundColor(const Color &value)
		{
			if (value != m_sSubmenuBackgroundColor)
			{
				m_sSubmenuBackgroundColor = value;
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuShadowColor(const Color &value)
		{
			if (value != m_sSubmenuShadowColor)
			{
				m_sSubmenuShadowColor = value;
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuShadowRadius(const int value)
		{
			if (value >= 1 && value != m_iSubmenuShadowRadius)
			{
				CLockRepaint lock{ this };
				RepaintSubmenus(0);
				m_iSubmenuShadowRadius = value;
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuShadowShift(const PointF &value)
		{
			if (IsNotEqual(value, m_sSubmenuShadowShift))
			{
				CLockRepaint lock{ this };
				RepaintSubmenus(0);
				m_sSubmenuShadowShift = value;
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setScroll(const float value)
		{
			float v{ value };
			if (v < 0)
				v = 0;
			else if (v > m_aItems[0].ScrollMax)
				v = m_aItems[0].ScrollMax;
			if (ntl::IsNotEqual<float>(v, m_aItems[0].Scroll))
			{
				m_aItems[0].Scroll = v;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getAbsoluteRenderRect(0), false);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuScroll(IListItem *parent, const float value)
		{
			int parent_index{ FindItemIndex(parent) };
			if (parent_index >= 0)
			{
				float v{ value };
				if (v < 0)
					v = 0;
				else if (v > m_aItems[parent_index].ScrollMax)
					v = m_aItems[parent_index].ScrollMax;
				if (ntl::IsNotEqual<float>(v, m_aItems[parent_index].Scroll))
				{
					m_aItems[parent_index].Scroll = v;
					Repaint(getAbsoluteRenderRect(parent_index), false);
					return true;
				}
				return false;
			}
			return setScroll(value);
		}

		bool CMainMenu::setSubmenuShift(const PointF &value)
		{
			if (IsNotEqual(value, m_sSubmenuShift))
			{
				CLockRepaint lock{ this };
				m_sSubmenuShift = value;
				UpdateSubmenuPosition(&m_cRootItem);
				return true;
			}
			return false;
		}

		bool CMainMenu::setHotkeyMaxInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fHotkeyMaxInterval))
			{
				m_fHotkeyMaxInterval = value;
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuScrollHeight(const float value)
		{
			float v{ value };
			if (v < MIN_SCROLL_HEIGHT)
				v = MIN_SCROLL_HEIGHT;
			if (ntl::IsNotEqual<float>(v, m_fSubmenuScrollHeight))
			{
				CLockRepaint lock{ this };
				m_fSubmenuScrollHeight = v;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuScrollArrowColorNormal(const Color &value)
		{
			if (value != m_sSubmenuScrollArrowColorNormal)
			{
				m_sSubmenuScrollArrowColorNormal = value;
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuScrollArrowColorHovered(const Color &value)
		{
			if (value != m_sSubmenuScrollArrowColorHovered)
			{
				m_sSubmenuScrollArrowColorHovered = value;
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuScrollArrowColorDisabled(const Color &value)
		{
			if (value != m_sSubmenuScrollArrowColorDisabled)
			{
				m_sSubmenuScrollArrowColorDisabled = value;
				RepaintSubmenus(0);
				return true;
			}
			return false;
		}

		bool CMainMenu::setScrollInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
			{
				m_fScrollInterval = value;
				if (m_hScrollTimer)
					getForm()->ResetTimer(m_hScrollTimer, m_fScrollInterval);
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuDeltaScrollTimer(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fSubmenuDeltaScrollTimer))
			{
				m_fSubmenuDeltaScrollTimer = value;
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuDeltaScrollWheel(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fSubmenuDeltaScrollWheel))
			{
				m_fSubmenuDeltaScrollWheel = value;
				return true;
			}
			return false;
		}

		bool CMainMenu::setSubmenuMaxHeight(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fSubmenuMaxHeight))
			{
				CLockRepaint lock{ this };
				m_fSubmenuMaxHeight = value;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				return true;
			}
			return false;
		}

		bool CMainMenu::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sBorderWidth = value;
				UpdateSubmenu(&m_cRootItem, false);
				UpdateSubmenuPosition(&m_cRootItem);
				return true;
			}
			return false;
		}

		bool CMainMenu::setBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderRadius))
			{
				m_sBorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getAbsoluteRenderRect(0), false);
				return true;
			}
			return false;
		}

		bool CMainMenu::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getAbsoluteRenderRect(0), false);
				}
				return true;
			}
			return false;
		}

		bool CMainMenu::setLeftBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CMainMenu::setTopBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CMainMenu::setRightBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CMainMenu::setBottomBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CMainMenu::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				CLockRepaint lock{ this };
				m_sPadding = value;
				UpdateSubmenu(&m_cRootItem, false);
				UpdateSubmenuPosition(&m_cRootItem);
				return true;
			}
			return false;
		}

		bool CMainMenu::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getAbsoluteRenderRect(0), false);
				}
				return true;
			}
			return false;
		}

		bool CMainMenu::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				m_aShadowColor[(int)state] = value;
				if (getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getAbsoluteRenderRect(0), false);
				}
				return true;
			}
			return false;
		}

		bool CMainMenu::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
					Repaint(getAbsoluteRenderRect(0), false);
				m_aShadowRadius[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getAbsoluteRenderRect(0), false);
				}
				return true;
			}
			return false;
		}

		bool CMainMenu::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
					Repaint(getAbsoluteRenderRect(0), false);
				m_aShadowShift[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getAbsoluteRenderRect(0), false);
				}
				return true;
			}
			return false;
		}

		bool CMainMenu::setScrollWidth(const float value)
		{
			float v{ value };
			if (v < MIN_SCROLL_HEIGHT)
				v = MIN_SCROLL_HEIGHT;
			if (ntl::IsNotEqual<float>(v, m_fScrollWidth))
			{
				CLockRepaint lock{ this };
				m_fScrollWidth = v;
				UpdateSubmenu(&m_cRootItem, false);
				UpdateSubmenuPosition(&m_cRootItem);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getAbsoluteRenderRect(0), false);
				return true;
			}
			return false;
		}

		bool CMainMenu::setScrollArrowColorNormal(const Color &value)
		{
			if (value != m_sScrollArrowColorNormal)
			{
				m_sScrollArrowColorNormal = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getAbsoluteRenderRect(0), false);
				return true;
			}
			return false;
		}

		bool CMainMenu::setScrollArrowColorHovered(const Color &value)
		{
			if (value != m_sScrollArrowColorHovered)
			{
				m_sScrollArrowColorHovered = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getAbsoluteRenderRect(0), false);
				return true;
			}
			return false;
		}

		bool CMainMenu::setScrollArrowColorDisabled(const Color &value)
		{
			if (value != m_sScrollArrowColorDisabled)
			{
				m_sScrollArrowColorDisabled = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getAbsoluteRenderRect(0), false);
				return true;
			}
			return false;
		}

		bool CMainMenu::setItemRightAligned(const int index, const bool value)
		{
			int i{ FindItemIndex(m_cRootItem.getItem(index)) };
			if (i >= 0 && value != m_aItems[i].RightAligned)
			{
				CLockRepaint lock{ this };
				m_aItems[i].RightAligned = value;
				UpdateSubmenu(m_aItems[i].Item->getParent(), true);
				UpdateSubmenuPosition(m_aItems[i].Item->getParent());
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getAbsoluteRenderRect(0), false);
				return true;
			}
			return false;
		}

		bool CMainMenu::setItemRightAligned(IListItem *item, const bool value)
		{
			for (int i = 0; i < m_cRootItem.getItemCount(); i++)
				if (m_cRootItem.getItem(i) == item)
					return setItemRightAligned(i, value);
			return false;
		}

		bool CMainMenu::setRootSubmenuShift(const PointF &value)
		{
			if (IsNotEqual(value, m_sRootSubmenuShift))
			{
				CLockRepaint lock{ this };
				m_sRootSubmenuShift = value;
				UpdateSubmenuPosition(&m_cRootItem);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Items
		bool CMainMenu::Add(IListItem *item)
		{
			return Add(item, false);
		}

		bool CMainMenu::Insert(IListItem *item, const int before)
		{
			return Insert(item, before, false);
		}

		bool CMainMenu::Delete(const int index)
		{
			return m_cRootItem.DeleteItem(index);
		}

		bool CMainMenu::Clear()
		{
			return m_cRootItem.DeleteItems();
		}

		bool CMainMenu::Add(IListItem *item, const bool right_aligned)
		{
			CLockRepaint lock{ this };
			if (m_cRootItem.AddItem(item))
			{
				if (right_aligned)
				{
					m_aItems[FindItemIndex(item)].RightAligned = true;
					UpdateSubmenu(&m_cRootItem, false);
					UpdateSubmenuPosition(&m_cRootItem);
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getAbsoluteRenderRect(0), false);
				}
				return true;
			}
			return false;
		}

		bool CMainMenu::Insert(IListItem *item, const int before, const bool right_aligned)
		{
			CLockRepaint lock{ this };
			if (m_cRootItem.InsertItem(item, before))
			{
				if (right_aligned)
				{
					m_aItems[FindItemIndex(item)].RightAligned = true;
					UpdateSubmenu(&m_cRootItem, false);
					UpdateSubmenuPosition(&m_cRootItem);
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getAbsoluteRenderRect(0), false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CMainMenu::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CMainMenu::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".SubmenuBorderWidth", m_sSubmenuBorderWidth);
			style->getOption(m_sClassName + L".SubmenuBorderRadius", m_sSubmenuBorderRadius);
			style->getOption(m_sClassName + L".SubmenuBorderColor", m_sSubmenuBorderColor);
			style->getOption(m_sClassName + L".SubmenuPadding", m_sSubmenuPadding);
			style->getOption(m_sClassName + L".SubmenuBackgroundColor", m_sSubmenuBackgroundColor);
			style->getOption(m_sClassName + L".SubmenuShadowColor", m_sSubmenuShadowColor);
			style->getOption(m_sClassName + L".SubmenuShadowRadius", m_iSubmenuShadowRadius);
			style->getOption(m_sClassName + L".SubmenuShadowShift", m_sSubmenuShadowShift);
			style->getOption(m_sClassName + L".SubmenuShift", m_sSubmenuShift);
			style->getOption(m_sClassName + L".SubmenuScrollHeight", m_fSubmenuScrollHeight);
			style->getOption(m_sClassName + L".SubmenuScrollArriwColorNormal", m_sSubmenuScrollArrowColorNormal);
			style->getOption(m_sClassName + L".SubmenuScrollArriwColorHovered", m_sSubmenuScrollArrowColorHovered);
			style->getOption(m_sClassName + L".SubmenuScrollArriwColorDisabled", m_sSubmenuScrollArrowColorDisabled);
			style->getOption(m_sClassName + L".ScrollInterval", m_fScrollInterval);
			style->getOption(m_sClassName + L".SubmenuDeltaScrollTimer", m_fSubmenuDeltaScrollTimer);
			style->getOption(m_sClassName + L".SubmenuDeltaScrollWheel", m_fSubmenuDeltaScrollWheel);
			style->getOption(m_sClassName + L".SubmenuBackgroundGradient", m_cSubmenuBackgroundGradient);
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".BorderColor[Normal]", m_aBorderColor[(int)State::Normal]);
			style->getOption(m_sClassName + L".BorderColor[Active]", m_aBorderColor[(int)State::Active]);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".BackgroundColor[Normal]", m_aBackgroundColor[(int)State::Normal]);
			style->getOption(m_sClassName + L".BackgroundColor[Active]", m_aBackgroundColor[(int)State::Active]);
			style->getOption(m_sClassName + L".ShadowColor[Normal]", m_aShadowColor[(int)State::Normal]);
			style->getOption(m_sClassName + L".ShadowColor[Active]", m_aShadowColor[(int)State::Active]);
			style->getOption(m_sClassName + L".ShadowRadius[Normal]", m_aShadowRadius[(int)State::Normal]);
			style->getOption(m_sClassName + L".ShadowRadius[Active]", m_aShadowRadius[(int)State::Active]);
			style->getOption(m_sClassName + L".ShadowShift[Normal]", m_aShadowShift[(int)State::Normal]);
			style->getOption(m_sClassName + L".ShadowShift[Active]", m_aShadowShift[(int)State::Active]);
			style->getOption(m_sClassName + L".BackgroundGradient[Normal]", m_aBackgroundGradient[(int)State::Normal]);
			style->getOption(m_sClassName + L".BackgroundGradient[Active]", m_aBackgroundGradient[(int)State::Active]);
			style->getOption(m_sClassName + L".ScrollWidth", m_fScrollWidth);
			style->getOption(m_sClassName + L".ScrollArriwColorNormal", m_sScrollArrowColorNormal);
			style->getOption(m_sClassName + L".ScrollArriwColorHovered", m_sScrollArrowColorHovered);
			style->getOption(m_sClassName + L".ScrollArriwColorDisabled", m_sScrollArrowColorDisabled);
			m_bIgnoreGradient = false;
			UpdateItemFromStyle(&m_cRootItem);
		}

		void CMainMenu::UpdateItemFromStyle(IListItem *item)
		{
			item->QueryService()->UpdateFromStyle();
			for (int i = 0; i < item->getItemCount(); i++)
				UpdateItemFromStyle(item->getItem(i));
		}

		int CMainMenu::FindItemIndex(IListItem *item) const
		{
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if (pos->Item == item)
					return int(pos - m_aItems.begin());
			return -1;
		}

		PointF CMainMenu::CalculateRequiredSize(IListItem *parent)
		{
			// Build list of items to be processed
			std::vector<IListItem*> items;
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
					items.push_back(parent->getItem(i));
			if (parent == &m_cRootItem)
			{
				// Calculate required size
				PointF result{ 0, getHeight() };
				for (auto pos = items.begin(); pos != items.end(); pos++)
					result.X += (*pos)->QueryService()->getRequiredSize().X;
				return result;
			}
			// Find parts sizes of IListItemMenu items
			float icon_width{ 0 }, arrow_width{ 0 }, hotkey_width{ 0 };
			if (getForm() && getForm()->getRenderer() && getFont()->getPlatformFont(getForm()->getRenderer()))
				icon_width = arrow_width = getFont()->getPlatformFont(getForm()->getRenderer())->getStringSize(L"Wy", 0).Y;
			for (auto pos = items.begin(); pos != items.end(); pos++)
			{
				IListItemMenuService *service{ cast<IListItemMenuService*>((*pos)->QueryService()) };
				if (service)
				{
					icon_width = ntl::Max<float>(icon_width, service->getIconWidth());
					arrow_width = ntl::Max<float>(arrow_width, service->getArrowWidth());
					hotkey_width = ntl::Max<float>(hotkey_width, service->getHotkeyWidth());
				}
				float y{ (*pos)->QueryService()->getRequiredSize().Y };
				icon_width = ntl::Max<float>(icon_width, y);
				arrow_width = ntl::Max<float>(arrow_width, y);
			}
			// Calculate required size
			PointF result{ 0, 0 };
			for (auto pos = items.begin(); pos != items.end(); pos++)
			{
				IListItemMenuService *service{ cast<IListItemMenuService*>((*pos)->QueryService()) };
				if (service)
				{
					service->setIconWidth(icon_width);
					service->setHotkeyWidth(hotkey_width);
					service->setArrowWidth(arrow_width);
				}
				PointF size{ (*pos)->QueryService()->getRequiredSize() };
				result.X = ntl::Max<float>(result.X, size.X);
				result.Y += size.Y;
			}
			return result;
		}

		void CMainMenu::UpdateSubmenu(IListItem *parent, const bool recursive)
		{
			bool repainted{ false };
			PointF required_size{ CalculateRequiredSize(parent) };
			if (parent == &m_cRootItem)
			{
				float new_width;
				if (ntl::IsGreater<float>(required_size.X + m_sBorderWidth.Left + m_sBorderWidth.Right + m_sPadding.Left + m_sPadding.Right, getWidth()))
					new_width = ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - 2 * m_fScrollWidth);
				else
					new_width = required_size.X;
				if (ntl::IsLess<float>(new_width, required_size.X))
				{
					m_aItems[0].ScrollMax = required_size.X - new_width;
					float new_scroll{ ntl::Min<float>(m_aItems[0].Scroll, m_aItems[0].ScrollMax) };
					if (ntl::IsNotEqual<float>(m_aItems[0].Scroll, new_scroll))
					{
						m_aItems[0].Scroll = new_scroll;
						if (!repainted)
						{
							if (m_pCanvas)
								m_pCanvas->setValid(false);
							Repaint(getAbsoluteRenderRect(0), false);
							repainted = true;
						}
					}
				}
				else
				{
					m_aItems[0].ScrollMax = 0;
					if (ntl::IsNotEqual<float>(m_aItems[0].Scroll, 0))
					{
						m_aItems[0].Scroll = 0;
						if (!repainted)
						{
							if (m_pCanvas)
								m_pCanvas->setValid(false);
							Repaint(getAbsoluteRenderRect(0), false);
							repainted = true;
						}
					}
				}
				float x_left{ m_sBorderWidth.Left + (m_aItems[0].ScrollMax > 0 ? m_fScrollWidth : m_sPadding.Left) };
				float x_right{ getWidth() - m_sBorderWidth.Right - (ntl::IsGreater<float>(m_aItems[0].ScrollMax, 0) ? m_fScrollWidth : m_sPadding.Right) };
				bool changed{ false };
				for (int i = 0; i < m_cRootItem.getItemCount(); i++)
					if (m_cRootItem.getItem(i)->isVisible())
					{
						PointF size{ m_cRootItem.getItem(i)->QueryService()->getRequiredSize() };
						PointF new_size{ size.X, ntl::Max<float>(0, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - m_sPadding.Top - m_sPadding.Bottom) };
						int index{ FindItemIndex(m_cRootItem.getItem(i)) };
						PointF new_pos{ (m_aItems[index].RightAligned && ntl::IsEqual<float>(m_aItems[0].ScrollMax, 0)) ? (x_right - size.X) : x_left, m_sBorderWidth.Top + m_sPadding.Top };
						if (IsNotEqual(m_cRootItem.getItem(i)->getSize(), new_size))
						{
							m_cRootItem.getItem(i)->QueryService()->setSize(new_size);
							changed = true;
						}
						if (IsNotEqual(m_cRootItem.getItem(i)->getPosition(), new_pos))
						{
							m_cRootItem.getItem(i)->QueryService()->setPosition(new_pos);
							changed = true;
						}
						if (m_aItems[index].RightAligned && ntl::IsEqual<float>(m_aItems[0].ScrollMax, 0))
							x_right -= size.X;
						else
							x_left += size.X;
					}
				if (changed && !repainted)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getAbsoluteRenderRect(0), false);
					repainted = true;
				}
				PointF new_size{ getWidth(), required_size.Y + m_sBorderWidth.Top + m_sBorderWidth.Bottom + m_sPadding.Top + m_sPadding.Bottom };
				if (IsNotEqual(m_aItems[0].Size, new_size))
				{
					m_aItems[0].Size = new_size;
					CControl::setConstraints(RectF{ 0, m_sBorderWidth.Top + m_sBorderWidth.Bottom + m_sPadding.Top + m_sPadding.Bottom, 0, 0 });
				}
			}
			else
			{
				float new_height;
				if (ntl::IsGreater<float>(m_fSubmenuMaxHeight, 0) &&
					ntl::IsGreater<float>(required_size.Y + m_sSubmenuBorderWidth.Top + m_sSubmenuBorderWidth.Bottom + m_sSubmenuPadding.Top + m_sSubmenuPadding.Bottom, m_fSubmenuMaxHeight))
					new_height = ntl::Max<float>(0, m_fSubmenuMaxHeight - m_sSubmenuBorderWidth.Top - m_sSubmenuBorderWidth.Bottom - 2 * m_fSubmenuScrollHeight);
				else
					new_height = required_size.Y;
				int parent_index{ FindItemIndex(parent) };
				if (ntl::IsLess<float>(new_height, required_size.Y))
				{
					m_aItems[parent_index].ScrollMax = required_size.Y - new_height;
					float new_scroll{ ntl::Min<float>(m_aItems[parent_index].Scroll, m_aItems[parent_index].ScrollMax) };
					if (ntl::IsNotEqual<float>(m_aItems[parent_index].Scroll, new_scroll))
					{
						m_aItems[parent_index].Scroll = new_scroll;
						if (!repainted)
						{
							Repaint(getAbsoluteRenderRect(parent_index), false);
							repainted = true;
						}
					}
				}
				else
				{
					m_aItems[parent_index].ScrollMax = 0;
					if (ntl::IsNotEqual<float>(m_aItems[parent_index].Scroll, 0))
					{
						m_aItems[parent_index].Scroll = 0;
						if (!repainted)
						{
							Repaint(getAbsoluteRenderRect(parent_index), false);
							repainted = true;
						}
					}
				}
				float y{ m_sSubmenuBorderWidth.Top + (ntl::IsGreater<float>(m_aItems[parent_index].ScrollMax, 0) ? m_fSubmenuScrollHeight : m_sSubmenuPadding.Top) };
				bool changed{ false };
				for (int i = 0; i < parent->getItemCount(); i++)
					if (parent->getItem(i)->isVisible())
					{
						PointF size{ parent->getItem(i)->QueryService()->getRequiredSize() };
						PointF new_size{ required_size.X, size.Y };
						PointF new_pos{ m_sSubmenuBorderWidth.Left + m_sSubmenuPadding.Left, y };
						if (IsNotEqual(parent->getItem(i)->getSize(), new_size))
						{
							parent->getItem(i)->QueryService()->setSize(new_size);
							changed = true;
						}
						if (IsNotEqual(parent->getItem(i)->getPosition(), new_pos))
						{
							parent->getItem(i)->QueryService()->setPosition(new_pos);
							changed = true;
						}
						y += size.Y;
					}
				if (changed && !repainted)
				{
					Repaint(getAbsoluteRenderRect(parent_index), false);
					repainted = true;
				}
				PointF new_size{
					required_size.X + m_sSubmenuBorderWidth.Left + m_sSubmenuBorderWidth.Right + m_sSubmenuPadding.Left + m_sSubmenuPadding.Right,
					new_height + m_sSubmenuBorderWidth.Top + m_sSubmenuBorderWidth.Bottom + (ntl::IsGreater<float>(m_aItems[parent_index].ScrollMax, 0) ?
					(2 * m_fSubmenuScrollHeight) : (m_sSubmenuPadding.Top + m_sSubmenuPadding.Bottom)) };
				if (IsNotEqual(m_aItems[parent_index].Size, new_size))
				{
					if (!repainted)
					{
						Repaint(getAbsoluteRenderRect(parent_index), false);
						repainted = true;
					}
					m_aItems[parent_index].Size = new_size;
					Repaint(getAbsoluteRenderRect(parent_index), false);
				}
			}
			if (recursive)
				for (int i = 0; i < parent->getItemCount(); i++)
				{
					int index{ FindItemIndex(parent->getItem(i)) };
					if (m_aItems[index].Opended)
						UpdateSubmenu(parent->getItem(i), true);
				}
		}

		void CMainMenu::UpdateSubmenuPosition(IListItem *parent)
		{
			if (!getForm() || !isVisible(false))
				return;
			if (parent != &m_cRootItem)
			{
				int parent_index{ FindItemIndex(parent) };
				RectF client{ (RectF)getForm()->getClientRect() };
				PointF pos;
				if (parent->getParent() == &m_cRootItem)
				{
					pos = PointF{
						parent->getPosition().X - m_aItems[0].Scroll + m_sRootSubmenuShift.X,
						parent->getPosition().Y + parent->getSize().Y + m_sRootSubmenuShift.Y
					};
					if (pos.X + m_aItems[parent_index].Size.X + getTransform()->getTx() > client.Right)
						pos.X = ntl::Clamp<float>(getTransform()->getTx() + parent->getPosition().X + parent->getSize().X - m_aItems[0].Scroll - m_aItems[parent_index].Size.X, client.Left, client.Right - m_aItems[parent_index].Size.X);
					if (pos.X < client.Left)
						pos.X = client.Left;
				}
				else
				{
					int parent2_index{ FindItemIndex(parent->getParent()) };
					pos = PointF{
						m_aItems[parent2_index].Position.X + m_aItems[parent2_index].Size.X + m_sSubmenuShift.X,
						m_aItems[parent2_index].Position.Y + parent->getPosition().Y - m_aItems[parent2_index].Scroll + m_sSubmenuShift.Y };
					if (pos.X + m_aItems[parent_index].Size.X >= client.Right)
						pos.X = ntl::Max<float>(client.Left, m_aItems[parent2_index].Position.X - m_sSubmenuShadowShift.X);
					if (pos.Y + m_aItems[parent_index].Size.Y >= client.Bottom)
						pos.Y = ntl::Max<float>(client.Top, pos.Y - m_aItems[parent_index].Size.Y);
				}
				if (IsNotEqual(pos, m_aItems[parent_index].Position))
				{
					Repaint(getAbsoluteRenderRect(parent_index), false);
					m_aItems[parent_index].Position = pos;
					Repaint(getAbsoluteRenderRect(parent_index), false);
				}
			}
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				int index{ FindItemIndex(parent->getItem(i)) };
				if (m_aItems[index].Opended)
					UpdateSubmenuPosition(parent->getItem(i));
			}
		}

		void CMainMenu::CalculateRenderRect(IListItem *parent, RectF &rect)
		{
			if (!isVisible(false))
				return;
			int parent_index{ FindItemIndex(parent) };
			if (m_aItems[parent_index].Opended)
			{
				if (parent == &m_cRootItem)
					rect = getAbsoluteRenderRect(parent_index);
				else
					rect += getAbsoluteRenderRect(parent_index);
				for (int i = 0; i < parent->getItemCount(); i++)
					CalculateRenderRect(parent->getItem(i), rect);
			}
		}

		IListItem *CMainMenu::getItem(IListItem *parent, bool &start_scroller, bool &end_scroller, const PointF &position)
		{
			start_scroller = end_scroller = false;
			if (!isVisible(false))
				return nullptr;
			int parent_index{ FindItemIndex(parent) };
			if (parent == &m_cRootItem)
			{
				if (ntl::IsGreater<float>(m_aItems[0].ScrollMax, 0))
				{
					if (position.X >= m_aItems[0].Position.X + m_sBorderWidth.Left &&
						position.X < m_aItems[0].Position.X + m_sBorderWidth.Left + m_fScrollWidth &&
						position.Y >= m_aItems[0].Position.Y + m_sBorderWidth.Top &&
						position.Y < m_aItems[0].Position.Y + m_aItems[0].Size.Y - m_sBorderWidth.Bottom)
					{
						start_scroller = true;
						return parent;
					}
					if (position.X >= m_aItems[0].Position.X + m_aItems[0].Size.X - m_sBorderWidth.Right - m_fScrollWidth &&
						position.X < m_aItems[0].Position.X + m_aItems[0].Size.X - m_sBorderWidth.Right &&
						position.Y >= m_aItems[0].Position.Y + m_sBorderWidth.Top &&
						position.Y < m_aItems[0].Position.Y + m_aItems[0].Size.Y - m_sBorderWidth.Bottom)
					{
						end_scroller = true;
						return parent;
					}
				}
			}
			else if (ntl::IsGreater<float>(m_aItems[parent_index].ScrollMax, 0))
			{
				if (position.X >= m_aItems[parent_index].Position.X + m_sSubmenuBorderWidth.Left &&
					position.X < m_aItems[parent_index].Position.X + m_aItems[parent_index].Size.X - m_sSubmenuBorderWidth.Right &&
					position.Y >= m_aItems[parent_index].Position.Y + m_sSubmenuBorderWidth.Top &&
					position.Y < m_aItems[parent_index].Position.Y + m_sSubmenuBorderWidth.Top + m_fSubmenuScrollHeight)
				{
					start_scroller = true;
					return parent;
				}
				if (position.X >= m_aItems[parent_index].Position.X + m_sSubmenuBorderWidth.Left &&
					position.X < m_aItems[parent_index].Position.X + m_aItems[parent_index].Size.X - m_sSubmenuBorderWidth.Right &&
					position.Y >= m_aItems[parent_index].Position.Y + m_aItems[parent_index].Size.Y - m_sSubmenuBorderWidth.Bottom - m_fSubmenuScrollHeight &&
					position.Y < m_aItems[parent_index].Position.Y + m_aItems[parent_index].Size.Y - m_sSubmenuBorderWidth.Bottom)
				{
					end_scroller = true;
					return parent;
				}
			}
			RectF client{ GetClientRect(parent) };
			bool in_client{
				position.X >= m_aItems[parent_index].Position.X + client.Left && position.X < m_aItems[parent_index].Position.X + client.Right &&
				position.Y >= m_aItems[parent_index].Position.Y + client.Top && position.Y < m_aItems[parent_index].Position.Y + client.Bottom };
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					int index{ FindItemIndex(parent->getItem(i)) };
					if (m_aItems[index].Opended)
					{
						IListItem *item{ getItem(parent->getItem(i), start_scroller, end_scroller, position) };
						if (item)
							return item;
					}
					if (parent == &m_cRootItem)
					{
						if (in_client &&
							position.X - m_aItems[parent_index].Position.X + m_aItems[parent_index].Scroll >= parent->getItem(i)->getPosition().X &&
							position.X - m_aItems[parent_index].Position.X + m_aItems[parent_index].Scroll < parent->getItem(i)->getPosition().X + parent->getItem(i)->getSize().X &&
							position.Y - m_aItems[parent_index].Position.Y >= parent->getItem(i)->getPosition().Y &&
							position.Y - m_aItems[parent_index].Position.Y < parent->getItem(i)->getPosition().Y + parent->getItem(i)->getSize().Y)
							return parent->getItem(i);
					}
					else
					{
						if (in_client &&
							position.X - m_aItems[parent_index].Position.X >= parent->getItem(i)->getPosition().X &&
							position.X - m_aItems[parent_index].Position.X < parent->getItem(i)->getPosition().X + parent->getItem(i)->getSize().X &&
							position.Y - m_aItems[parent_index].Position.Y + m_aItems[parent_index].Scroll >= parent->getItem(i)->getPosition().Y &&
							position.Y - m_aItems[parent_index].Position.Y + m_aItems[parent_index].Scroll < parent->getItem(i)->getPosition().Y + parent->getItem(i)->getSize().Y)
							return parent->getItem(i);
					}
				}
			return nullptr;
		}

		void CMainMenu::setOwner(IListItem *item)
		{
			item->QueryService()->setOwner(QueryListItemOwner());
			for (int i = 0; i < item->getItemCount(); i++)
				setOwner(item->getItem(i));
		}

		RectF CMainMenu::GetClientRect(IListItem *parent)
		{
			if (parent == &m_cRootItem)
			{
				RectF result{
					m_sBorderWidth.Left,
					m_sBorderWidth.Top + m_sPadding.Top,
					m_aItems[0].Size.X - m_sBorderWidth.Right,
					m_aItems[0].Size.Y - m_sBorderWidth.Bottom - m_sPadding.Bottom };
				if (ntl::IsGreater<float>(m_aItems[0].ScrollMax, 0))
				{
					result.Left += m_fScrollWidth;
					result.Right -= m_fScrollWidth;
				}
				else
				{
					result.Left += m_sPadding.Left;
					result.Right -= m_sPadding.Right;
				}
				result.validate();
				return result;
			}
			int parent_index{ FindItemIndex(parent) };
			RectF result{
				m_sSubmenuBorderWidth.Left + m_sSubmenuPadding.Left,
				m_sSubmenuBorderWidth.Top,
				m_aItems[parent_index].Size.X - m_sSubmenuBorderWidth.Right - m_sSubmenuPadding.Right,
				m_aItems[parent_index].Size.Y - m_sSubmenuBorderWidth.Bottom };
			if (ntl::IsGreater<float>(m_aItems[parent_index].ScrollMax, 0))
			{
				result.Top += m_fSubmenuScrollHeight;
				result.Bottom -= m_fSubmenuScrollHeight;
			}
			else
			{
				result.Top += m_sSubmenuPadding.Top;
				result.Bottom -= m_sSubmenuPadding.Bottom;
			}
			result.validate();
			return result;
		}

		void CMainMenu::MouseDownCancel()
		{
			if (m_pDownItem)
			{
				m_pDownItem->QueryService()->NotifyOnMouseDownCancel();
				m_pDownItem = nullptr;
			}
		}

		bool CMainMenu::TestPosition(IListItem *parent, const PointF &position)
		{
			int parent_index{ FindItemIndex(parent) };
			if (position.X >= m_aItems[parent_index].Position.X && position.X < m_aItems[parent_index].Position.X + m_aItems[parent_index].Size.X &&
				position.Y >= m_aItems[parent_index].Position.Y && position.Y < m_aItems[parent_index].Position.Y + m_aItems[parent_index].Size.Y)
				return true;
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					int index{ FindItemIndex(parent->getItem(i)) };
					if (m_aItems[index].Opended && TestPosition(parent->getItem(i), position))
						return true;
				}
			return false;
		}

		RectF CMainMenu::getAbsoluteRenderRect(IListItem *parent)
		{
			return getAbsoluteRenderRect(FindItemIndex(parent));
		}

		RectF CMainMenu::getAbsoluteRenderRect(const int parent_index)
		{
			RectF result{
				m_aItems[parent_index].Position.X,
				m_aItems[parent_index].Position.Y,
				m_aItems[parent_index].Position.X + m_aItems[parent_index].Size.X,
				m_aItems[parent_index].Position.Y + m_aItems[parent_index].Size.Y };
			if (parent_index == 0)
			{
				RectF clean{ result };
				for (int i = 0; i <= (int)State::Active; i++)
					result += AddShadow(clean, m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
				result.Left += getTransform()->getTx();
				result.Top += getTransform()->getTy();
				result.Right += getTransform()->getTx();
				result.Bottom += getTransform()->getTy();
			}
			else
				result = AddShadow(result, m_sSubmenuShadowColor, m_sSubmenuShadowShift, m_iSubmenuShadowRadius);
			return result;
		}

		void CMainMenu::SetListItemDPI(IListItem *parent)
		{
			parent->QueryService()->setDPI(getDPI());
			for (int i = 0; i < parent->getItemCount(); i++)
				SetListItemDPI(parent->getItem(i));
		}

		void CMainMenu::RepaintSubmenus(const int parent_index)
		{
			if (parent_index > 0)
				Repaint(getAbsoluteRenderRect(parent_index), false);
			for (int i = 0; i < m_aItems[parent_index].Item->getItemCount(); i++)
				if (m_aItems[parent_index].Item->getItem(i)->isVisible())
				{
					int index{ FindItemIndex(m_aItems[parent_index].Item->getItem(i)) };
					if (m_aItems[index].Opended)
						RepaintSubmenus(index);
				}
		}
	#pragma endregion

	#pragma region Paint
		void CMainMenu::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			//matrix.Translate(m_aItems[0].Position.X, m_aItems[0].Position.Y, 0);
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			ITexture *clip{ nullptr };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, RectF{ 0, 0, m_aItems[0].Size.X, m_aItems[0].Size.Y }, m_sBorderRadius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
				// Activate mask if required
				Block b{ rect, AddElements(m_sBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
				// Draw items
				for (int i = 0; i < m_cRootItem.getItemCount(); i++)
					if (m_cRootItem.getItem(i)->isVisible())
					{
						float x{ m_cRootItem.getItem(i)->getPosition().X - m_aItems[0].Scroll };
						if (x + m_cRootItem.getItem(i)->getSize().X >= 0 && x < getWidth())
							m_cRootItem.getItem(i)->QueryService()->Render(ntl::Mat4Translate<float>(std::round(x + disp.X), std::round(m_cRootItem.getItem(i)->getPosition().Y + disp.Y), 0), &b, false, &clip);
					}
				b.Border = RectF{ 0, 0, 0, 0 };
				RenderMenuScrolls(getSize(), m_aItems[0].Scroll, m_aItems[0].ScrollMax, b, renderer, state, disp);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
			// Draw submenu
			for (int i = 0; i < m_cRootItem.getItemCount(); i++)
				if (m_cRootItem.getItem(i)->isVisible() && m_aItems[FindItemIndex(m_cRootItem.getItem(i))].Opended)
					RenderSubmenu(m_cRootItem.getItem(i), renderer, &clip);
			if (clip)
				clip->Release();
		}

		void CMainMenu::RenderMenuScrolls(const PointF &size, const float scroll, const float scroll_max, const Block &block, IRenderer *renderer, const State state, const PointF &disp)
		{
			if (ntl::IsGreater<float>(scroll_max, 0))
			{
				CStoreBlock s_block{ renderer };
				renderer->ActivateBlock(&block);
				// Left
				RectF rect{ m_sBorderWidth.Left + disp.X, m_sBorderWidth.Top + disp.Y, m_sBorderWidth.Left + m_fScrollWidth + disp.X, size.Y - m_sBorderWidth.Bottom + disp.Y };
				renderer->DrawRectangle(rect, m_aBackgroundColor[(int)state]);

				Color color{ ntl::IsEqual<float>(scroll, 0) ? m_sScrollArrowColorDisabled : ((m_bHoverStartScroller && m_pHoveredItem == &m_cRootItem) ? m_sScrollArrowColorHovered : m_sScrollArrowColorNormal) };
				if (color.A > 0)
				{
					float w{ rect.width() - 2 }, y{ (rect.Bottom + rect.Top) * 0.5f };
					renderer->DrawTriangle(PointF{ rect.Left + 1, y }, PointF{ rect.Right - 1, y - w }, PointF{ rect.Right - 1, y + w }, color);
				}
				// Right
				rect.Left = size.X - m_sBorderWidth.Right - m_fScrollWidth;
				rect.Right = size.X - m_sBorderWidth.Right;
				renderer->DrawRectangle(rect, m_aBackgroundColor[(int)state]);

				color = ntl::IsEqual<float>(scroll, scroll_max) ? m_sScrollArrowColorDisabled : ((m_bHoverEndScroller && m_pHoveredItem == &m_cRootItem) ? m_sScrollArrowColorHovered : m_sScrollArrowColorNormal);
				if (color.A > 0)
				{
					float w{ rect.width() - 2 }, y{ (rect.Bottom + rect.Top) * 0.5f };
					renderer->DrawTriangle(PointF{ rect.Left + 1, y - w }, PointF{ rect.Right - 1, y }, PointF{ rect.Left + 1, y + w }, color);
				}
			}
		}

		void CMainMenu::RenderSubmenu(IListItem *parent, IRenderer *renderer, ITexture **clip)
		{
			int parent_index{ FindItemIndex(parent) };
			PointF disp{ DispOnCanvas(m_sSubmenuShadowColor, m_sSubmenuShadowShift, m_iSubmenuShadowRadius) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, m_aItems[parent_index].Size.X, m_aItems[parent_index].Size.Y }, m_sSubmenuShadowColor, m_sSubmenuShadowShift, m_iSubmenuShadowRadius) };
			IBaseTexture *old{ renderer->ActiveTarget };
			ITexture *canvas{ renderer->CreateTexture(ntl::Round<int>(all_rect.width()), ntl::Round<int>(all_rect.height()), 1, TextureFormat::RGBA, true) };
			if (canvas)
			{
				renderer
					->ActivateTarget(canvas)
					->Clear(Color{ 0, 0, 0, 0 });
				DrawBlockShadow(
					renderer,
					RectF{ 0, 0, m_aItems[parent_index].Size.X, m_aItems[parent_index].Size.Y },
					m_sSubmenuBorderRadius,
					m_sSubmenuShadowColor,
					m_sSubmenuShadowShift,
					m_iSubmenuShadowRadius);
				RenderBlock(
					m_aItems[parent_index].Size,
					m_sSubmenuBorderColor,
					m_sSubmenuBackgroundColor,
					m_sSubmenuBorderWidth,
					m_sSubmenuBorderRadius,
					m_cSubmenuBackgroundGradient,
					renderer,
					disp);
				// Activate mask if required
				Block b{
					RectF{ disp.X, disp.Y, disp.X + m_aItems[parent_index].Size.X, disp.Y + m_aItems[parent_index].Size.Y },
					RectF{
						m_sSubmenuBorderWidth.Left + m_sSubmenuPadding.Left,
						m_sSubmenuBorderWidth.Top + m_sSubmenuPadding.Top,
						m_sSubmenuBorderWidth.Right + m_sSubmenuPadding.Right,
						m_sSubmenuBorderWidth.Bottom + m_sSubmenuPadding.Bottom
					},
					m_sSubmenuBorderRadius, PointLocation::Inside };
				// Draw items
				for (int i = 0; i < parent->getItemCount(); i++)
					if (parent->getItem(i)->isVisible())
					{
						float y{ parent->getItem(i)->getPosition().Y - m_aItems[parent_index].Scroll };
						if (y + parent->getItem(i)->getSize().Y >= 0 && y < m_aItems[parent_index].Size.Y)
							parent->getItem(i)->QueryService()->Render(ntl::Mat4Translate<float>(std::round(parent->getItem(i)->getPosition().X + disp.X), std::round(y + disp.Y), 0), &b, true, clip);
					}
				RenderSubmenuScrolls(m_aItems[parent_index].Size, m_aItems[parent_index].Scroll, m_aItems[parent_index].ScrollMax, parent, b, renderer, disp);
				renderer->ActivateTarget(old);

				DrawCanvas(renderer, ntl::Mat4Translate<float>(m_aItems[parent_index].Position.X, m_aItems[parent_index].Position.Y, 0) * getTransformMatrix(), canvas, disp);
				canvas->Release();
			}
			// Draw submenu
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible() && m_aItems[FindItemIndex(parent->getItem(i))].Opended)
					RenderSubmenu(parent->getItem(i), renderer, clip);
		}

		void CMainMenu::RenderBlock(const PointF &size, const BorderColor &border_colors, const Color &background_color, const RectF &border_width, const RectF &border_radius, Gradient &gradient,
			IRenderer *renderer, const PointF &disp)
		{
			BlockColors colors{ border_colors.Left, border_colors.Top, border_colors.Right, border_colors.Bottom, background_color, Color{ 0, 0, 0, 0 } };
			Block b{ RectF{ disp.X, disp.Y, size.X + disp.X, size.Y + disp.Y }, border_width, border_radius, PointLocation::Inside };
			renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
			if (gradient.getPointCount() > 0)
			{
				CStoreBlock s_block{ renderer };
				renderer
					->ActivateBlock(&b)
					->DrawGradient(b.Rect, gradient);
			}
		}

		void CMainMenu::RenderSubmenuScrolls(const PointF &size, const float scroll, const float scroll_max, IListItem *parent, const Block &block, IRenderer *renderer, const PointF &disp)
		{
			if (ntl::IsGreater<float>(scroll_max, 0))
			{
				CStoreBlock s_block{ renderer };
				renderer->ActivateBlock(&block);
				// Top
				RectF rect{
					m_sSubmenuBorderWidth.Left + disp.X,
					m_sSubmenuBorderWidth.Top + disp.Y,
					size.X - m_sSubmenuBorderWidth.Right + disp.X,
					m_sSubmenuBorderWidth.Top + m_fSubmenuScrollHeight + disp.Y };
				renderer->DrawRectangle(rect, m_sSubmenuBackgroundColor);

				Color color{ ntl::IsEqual<float>(scroll, 0) ? m_sSubmenuScrollArrowColorDisabled : ((m_bHoverStartScroller && m_pHoveredItem == parent) ? m_sSubmenuScrollArrowColorHovered : m_sSubmenuScrollArrowColorNormal) };
				if (color.A > 0)
				{
					float h{ rect.height() - 2 }, x{ (rect.Right + rect.Left) * 0.5f };
					renderer->DrawTriangle(PointF{ x - h, rect.Bottom - 1 }, PointF{ x, rect.Top + 1 }, PointF{ x + h, rect.Bottom - 1 }, color);
				}
				// Bottom
				rect.Top = size.Y - m_sSubmenuBorderWidth.Bottom - m_fSubmenuScrollHeight + disp.Y;
				rect.Bottom = size.Y - m_sSubmenuBorderWidth.Bottom + disp.Y;
				renderer->DrawRectangle(rect, m_sSubmenuBackgroundColor);

				color = ntl::IsEqual<float>(scroll, scroll_max) ? m_sSubmenuScrollArrowColorDisabled : ((m_bHoverEndScroller && m_pHoveredItem == parent) ? m_sSubmenuScrollArrowColorHovered : m_sSubmenuScrollArrowColorNormal);
				if (color.A > 0)
				{
					float h{ rect.height() - 2 }, x{ (rect.Right + rect.Left) * 0.5f };
					renderer->DrawTriangle(PointF{ x + h, rect.Top + 1 }, PointF{ x, rect.Bottom - 1 }, PointF{ x - h, rect.Top + 1 }, color);
				}
			}
		}
	#pragma endregion
	}
}