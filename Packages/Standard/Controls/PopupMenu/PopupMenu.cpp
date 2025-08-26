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
		CPopupMenu::CGradientListener::CGradientListener(CPopupMenu *control) :
			m_pControl{ control }
		{

		}

		void CPopupMenu::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
				m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CPopupMenu::CPopupMenu() :
			CControl(L"PopupMenu", true, false, false, true, false, false),
			m_cGradientListener{ this },
			m_pImageListEnabled{ nullptr },
			m_pImageListDisabled{ nullptr },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sBorderColor{ Color{ 152, 152, 152, 255 }, Color{ 152, 152, 152, 255 }, Color{ 152, 152, 152, 255 }, Color{ 152, 152, 152, 255 } },
			m_sPadding{ 2, 2, 2, 2 },
			m_sBackgroundColor{ 241, 241, 241, 255 },
			m_sShadowColor{ 152, 152, 152, 200 },
			m_iShadowRadius{ 3 },
			m_sShadowShift{ 2, 2 },
			m_sSubmenuShift{ -5, -1 },
			m_bIgnoreHotkeys{ true },
			m_fHotkeyMaxInterval{ 1.0 },
			m_fScrollHeight{ 6 },
			m_sScrollArrowColorNormal{ 0, 0, 0, 255 },
			m_sScrollArrowColorHovered{ 64, 64, 64, 255 },
			m_sScrollArrowColorDisabled{ 127, 127, 127, 255 },
			m_fScrollInterval{ ScrollInterval },
			m_fDeltaScrollTimer{ 2 },
			m_fDeltaScrollWheel{ 10 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_pListItemOwner{ nullptr },
			m_pTransform{ nullptr },
			m_hScrollTimer{ 0 },
			m_bIgnoreVisible{ true },
			m_pHoveredItem{ nullptr },
			m_bHoverTopScroller{ false },
			m_bHoverBottomScroller{ false },
			m_pDownItem{ nullptr },
			m_cRootItem{ L"Root", true },
			m_bIgnoreGradient{ false },
			OnSelectItem{ nullptr },
			OnDeselectItem{ nullptr },
			OnActivateItem{ nullptr },
			OnDeactivateItem{ nullptr },
			OnDeleteItem{ nullptr },
			OnDeleteItems{ nullptr }
		{
			setService(new CPopupMenuService(this), true);
			m_pTransform = new CPopupMenuTransform(nullptr);
			CControl::setTransform(m_pTransform);
			m_sLastHotkey = std::chrono::steady_clock::now();
			setOwner(&m_cRootItem);
			m_aItems.push_back(ITEM{ &m_cRootItem, true, 0, 0, PointF{ 0, 0 }, PointF{ 0, 0 } });
			setVisibleInternal(false);
		}

		CPopupMenu::CPopupMenu(IForm *parent) :CPopupMenu()
		{
			setForm(parent);
		}

		CPopupMenu::~CPopupMenu()
		{
			if (m_pListItemOwner)
				m_pListItemOwner->Release();
		}
	#pragma endregion

	#pragma region CControl getters
		IControl *CPopupMenu::getControl(const PointF &position)
		{
			if (isCaptureMouse() && TestPosition(&m_cRootItem, position))
				return this;
			return CControl::getControl(position);
		}

		RectF CPopupMenu::getClientRect()
		{
			return CControl::getClientRect();
		}

		RectF CPopupMenu::getRenderRect()
		{
			RectF result{ 0, 0, 0, 0 };
			CalculateRenderRect(&m_cRootItem, result);
			result.Left -= m_aItems[0].Position.X;
			result.Top -= m_aItems[0].Position.Y;
			result.Right -= m_aItems[0].Position.X;
			result.Bottom -= m_aItems[0].Position.Y;
			return result;
		}

		Mat4f CPopupMenu::getTransformMatrix()
		{
			return getTransform()->getMatrix();
		}

		bool CPopupMenu::hasExtra()
		{
			return true;
		}

		IListItemOwner *CPopupMenu::QueryListItemOwner()
		{
			if (!m_pListItemOwner)
				m_pListItemOwner = new CPopupMenuListItemOwner(this);
			return m_pListItemOwner;
		}
	#pragma endregion

	#pragma region Getters
		IListItem *CPopupMenu::getRootItem()
		{
			return &m_cRootItem;
		}

		int CPopupMenu::getItemCount(const bool total)
		{
			return m_cRootItem.getItemCount(total);
		}

		IListItem *CPopupMenu::getItem(const int index)
		{
			return m_cRootItem.getItem(index);
		}

		IListItem *CPopupMenu::getItem(const String &name)
		{
			return m_cRootItem.getItem(name);
		}

		IListItem *CPopupMenu::getItem(const PointF &position)
		{
			bool t, b;
			IListItem *result{ getItem(&m_cRootItem, position, t, b) };
			if (t || b)
				result = nullptr;
			return result;
		}

		IImageList *CPopupMenu::getImageListEnabled()
		{
			return m_pImageListEnabled;
		}

		IImageList *CPopupMenu::getImageListDisabled()
		{
			return m_pImageListDisabled;
		}

		RectF CPopupMenu::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CPopupMenu::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		BorderColor CPopupMenu::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CPopupMenu::getLeftBorderColor() const
		{
			return m_sBorderColor.Left;
		}

		Color CPopupMenu::getTopBorderColor() const
		{
			return m_sBorderColor.Top;
		}

		Color CPopupMenu::getRightBorderColor() const
		{
			return m_sBorderColor.Right;
		}

		Color CPopupMenu::getBottomBorderColor() const
		{
			return m_sBorderColor.Bottom;
		}

		RectF CPopupMenu::getPadding() const
		{
			return m_sPadding;
		}

		Color CPopupMenu::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Color CPopupMenu::getShadowColor() const
		{
			return m_sShadowColor;
		}

		int CPopupMenu::getShadowRadius() const
		{
			return m_iShadowRadius;
		}

		PointF CPopupMenu::getShadowShift() const
		{
			return m_sShadowShift;
		}

		float CPopupMenu::getScroll() const
		{
			return m_aItems[0].Scroll;
		}

		float CPopupMenu::getScrollMax() const
		{
			return m_aItems[0].ScrollMax;
		}

		float CPopupMenu::getSubmenuScroll(IListItem *parent)
		{
			int parent_index{ FindItemIndex(parent) };
			if (parent_index >= 0)
				return m_aItems[parent_index].Scroll;
			return 0;
		}

		float CPopupMenu::getSubmenuScrollMax(IListItem *parent)
		{
			int parent_index{ FindItemIndex(parent) };
			if (parent_index >= 0)
				return m_aItems[parent_index].ScrollMax;
			return 0;
		}

		PointF CPopupMenu::getSubmenuShift() const
		{
			return m_sSubmenuShift;
		}

		bool CPopupMenu::getIgnoreHotkeys() const
		{
			return m_bIgnoreHotkeys;
		}

		float CPopupMenu::getHotkeyMaxInterval() const
		{
			return m_fHotkeyMaxInterval;
		}

		float CPopupMenu::getScrollHeight() const
		{
			return m_fScrollHeight;
		}

		Color CPopupMenu::getScrollArrowColorNormal() const
		{
			return m_sScrollArrowColorNormal;
		}

		Color CPopupMenu::getScrollArrowColorHovered() const
		{
			return m_sScrollArrowColorHovered;
		}

		Color CPopupMenu::getScrollArrowColorDisabled() const
		{
			return m_sScrollArrowColorDisabled;
		}

		float CPopupMenu::getScrollInterval() const
		{
			return m_fScrollInterval;
		}

		float CPopupMenu::getDeltaScrollTimer() const
		{
			return m_fDeltaScrollTimer;
		}

		float CPopupMenu::getDeltaScrollWheel() const
		{
			return m_fDeltaScrollWheel;
		}

		Gradient *CPopupMenu::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}
	#pragma endregion

	#pragma region CControl setters
		bool CPopupMenu::setAlign(const Align value)
		{
			return false;
		}

		bool CPopupMenu::setConstraints(const RectF &value)
		{
			return CControl::setConstraints(RectF{ 0, ntl::Max<float>(value.Bottom, m_sBorderWidth.Top + m_sBorderWidth.Bottom + ntl::Max<float>(m_sPadding.Top + m_sPadding.Bottom, 2 * m_fScrollHeight) + 1), 0, 0 });
		}

		bool CPopupMenu::setSize(const PointF &value)
		{
			return false;
		}

		bool CPopupMenu::setVisible(const bool value)
		{
			if (!m_bIgnoreVisible)
				return CControl::setVisible(value);
			return false;
		}

		bool CPopupMenu::setEnabled(const bool value)
		{
			return false;
		}

		bool CPopupMenu::setTransform(ITransform *value)
		{
			return false;
		}

		bool CPopupMenu::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sPadding *= s;
				m_iShadowRadius = ntl::Round<int>((float)m_iShadowRadius * avg);
				m_sShadowShift *= s;
				m_sSubmenuShift *= s;
				m_fScrollHeight *= s.Y;
				m_fDeltaScrollTimer *= s.Y;
				m_fDeltaScrollWheel *= s.Y;
				SetListItemDPI(&m_cRootItem);
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CPopupMenu::setImageListEnabled(IImageList *value)
		{
			if (value != m_pImageListEnabled)
			{
				CLockRepaint lock{ this };
				m_pImageListEnabled = value;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setImageListDisabled(IImageList *value)
		{
			if (value != m_pImageListDisabled)
			{
				CLockRepaint lock{ this };
				m_pImageListDisabled = value;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sBorderWidth = value;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderRadius))
			{
				m_sBorderRadius = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setBorderColor(const BorderColor &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setLeftBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ value, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CPopupMenu::setTopBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, value, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CPopupMenu::setRightBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, value, m_sBorderColor.Bottom });
		}

		bool CPopupMenu::setBottomBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, value });
		}

		bool CPopupMenu::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				CLockRepaint lock{ this };
				m_sPadding = value;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setShadowColor(const Color &value)
		{
			if (value != m_sShadowColor)
			{
				m_sShadowColor = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setShadowRadius(const int value)
		{
			if (value >= 1 && value != m_iShadowRadius)
			{
				CLockRepaint lock{ this };
				if (m_sShadowColor.A > 0)
					Repaint(false);
				m_iShadowRadius = value;
				if (m_sShadowColor.A > 0)
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setShadowShift(const PointF &value)
		{
			if (IsNotEqual(value, m_sShadowShift))
			{
				CLockRepaint lock{ this };
				if (m_sShadowColor.A > 0)
					Repaint(false);
				m_sShadowShift = value;
				if (m_sShadowColor.A > 0)
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setScroll(const float value)
		{
			float v{ value };
			if (v < 0)
				v = 0;
			else if (v > m_aItems[0].ScrollMax)
				v = m_aItems[0].ScrollMax;
			if (ntl::IsNotEqual<float>(v, m_aItems[0].Scroll))
			{
				m_aItems[0].Scroll = v;
				Repaint(getAbsoluteRenderRect(0), false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setSubmenuScroll(IListItem *parent, const float value)
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

		bool CPopupMenu::setSubmenuShift(const PointF &value)
		{
			if (IsNotEqual(value, m_sShadowShift))
			{
				m_sShadowShift = value;
				UpdateSubmenuPosition(&m_cRootItem);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setIgnoreHotkeys(const bool value)
		{
			if (value != m_bIgnoreHotkeys)
			{
				m_bIgnoreHotkeys = value;
				m_aLastHotkeys.clear();
				return true;
			}
			return false;
		}

		bool CPopupMenu::setHotkeyMaxInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fHotkeyMaxInterval))
			{
				m_fHotkeyMaxInterval = value;
				return true;
			}
			return false;
		}

		bool CPopupMenu::setScrollHeight(const float value)
		{
			float v{ value };
			if (v < MIN_SCROLL_HEIGHT)
				v = MIN_SCROLL_HEIGHT;
			if (ntl::IsNotEqual<float>(v, m_fScrollHeight))
			{
				CLockRepaint lock{ this };
				m_fScrollHeight = v;
				UpdateSubmenu(&m_cRootItem, true);
				UpdateSubmenuPosition(&m_cRootItem);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setScrollArrowColorNormal(const Color &value)
		{
			if (value != m_sScrollArrowColorNormal)
			{
				m_sScrollArrowColorNormal = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setScrollArrowColorHovered(const Color &value)
		{
			if (value != m_sScrollArrowColorHovered)
			{
				m_sScrollArrowColorHovered = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setScrollArrowColorDisabled(const Color &value)
		{
			if (value != m_sScrollArrowColorDisabled)
			{
				m_sScrollArrowColorDisabled = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::setScrollInterval(const float value)
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

		bool CPopupMenu::setDeltaScrollTimer(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDeltaScrollTimer))
			{
				m_fDeltaScrollTimer = value;
				return true;
			}
			return false;
		}

		bool CPopupMenu::setDeltaScrollWheel(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDeltaScrollWheel))
			{
				m_fDeltaScrollWheel = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Items
		bool CPopupMenu::Add(IListItem *item)
		{
			return m_cRootItem.AddItem(item);
		}

		bool CPopupMenu::Insert(IListItem *item, const int before)
		{
			return m_cRootItem.InsertItem(item, before);
		}

		bool CPopupMenu::Delete(const int index)
		{
			return m_cRootItem.DeleteItem(index);
		}

		bool CPopupMenu::Clear()
		{
			return m_cRootItem.DeleteItems();
		}
	#pragma endregion

	#pragma region Helpers
		void CPopupMenu::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".BorderColor", m_sBorderColor);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".ShadowColor", m_sShadowColor);
			style->getOption(m_sClassName + L".ShadowRadius", m_iShadowRadius);
			style->getOption(m_sClassName + L".ShadowShift", m_sShadowShift);
			style->getOption(m_sClassName + L".SubmenuShift", m_sSubmenuShift);
			style->getOption(m_sClassName + L".ScrollHeight", m_fScrollHeight);
			style->getOption(m_sClassName + L".ScrollArriwColorNormal", m_sScrollArrowColorNormal);
			style->getOption(m_sClassName + L".ScrollArriwColorHovered", m_sScrollArrowColorHovered);
			style->getOption(m_sClassName + L".ScrollArriwColorDisabled", m_sScrollArrowColorDisabled);
			style->getOption(m_sClassName + L".ScrollInterval", m_fScrollInterval);
			style->getOption(m_sClassName + L".DeltaScrollTimer", m_fDeltaScrollTimer);
			style->getOption(m_sClassName + L".DeltaScrollWheel", m_fDeltaScrollWheel);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			UpdateItemFromStyle(&m_cRootItem);
			m_bIgnoreGradient = false;
		}

		void CPopupMenu::UpdateItemFromStyle(IListItem *item)
		{
			item->QueryService()->UpdateFromStyle();
			for (int i = 0; i < item->getItemCount(); i++)
				UpdateItemFromStyle(item->getItem(i));
		}

		int CPopupMenu::FindItemIndex(IListItem *item)
		{
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if (pos->Item == item)
					return int(pos - m_aItems.begin());
			return -1;
		}

		PointF CPopupMenu::CalculateRequiredSize(IListItem *parent)
		{
			// Build list of items to be processed
			std::vector<IListItem*> items;
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
					items.push_back(parent->getItem(i));
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

		void CPopupMenu::UpdateSubmenu(IListItem *parent, const bool recursive)
		{
			bool repainted{ false };
			PointF required_size{ CalculateRequiredSize(parent) };
			float new_height;
			if (ntl::IsGreater<float>(getMaxHeight(), 0) && ntl::IsGreater<float>(required_size.Y + m_sBorderWidth.Top + m_sBorderWidth.Bottom + m_sPadding.Top + m_sPadding.Bottom, getMaxHeight()))
				new_height = ntl::Max<float>(0, getMaxHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - 2 * m_fScrollHeight);
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
					Repaint(getAbsoluteRenderRect(parent_index), false);
				}
			}
			float y{ m_sBorderWidth.Top + (ntl::IsGreater<float>(m_aItems[parent_index].ScrollMax, 0) ? m_fScrollHeight : m_sPadding.Top) };
			bool changed{ false };
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->QueryService()->getRequiredSize() };
					PointF new_size{ required_size.X, size.Y };
					PointF new_pos{ m_sBorderWidth.Left + m_sPadding.Left, y };
					if (IsNotEqual(parent->getItem(i)->getSize(), new_size) || IsNotEqual(parent->getItem(i)->getPosition(), new_pos))
					{
						parent->getItem(i)->QueryService()->setSize(new_size);
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
				required_size.X + m_sBorderWidth.Left + m_sBorderWidth.Right + m_sPadding.Left + m_sPadding.Right,
				new_height + m_sBorderWidth.Top + m_sBorderWidth.Bottom + (ntl::IsGreater<float>(m_aItems[parent_index].ScrollMax, 0) ? (2 * m_fScrollHeight) : (m_sPadding.Top + m_sPadding.Bottom)) };
			if (IsNotEqual(m_aItems[parent_index].Size, new_size))
			{
				if (!repainted && parent_index > 0)
				{
					Repaint(getAbsoluteRenderRect(parent_index), false);
					repainted = true;
				}
				m_aItems[parent_index].Size = new_size;
			}
			if (parent_index == 0 && IsNotEqual(getSize(), new_size))
				setSizeInternal(new_size);
			if (recursive)
				for (int i = 0; i < parent->getItemCount(); i++)
				{
					int index{ FindItemIndex(parent->getItem(i)) };
					if (m_aItems[index].Opended)
						UpdateSubmenu(parent->getItem(i), true);
				}
		}

		void CPopupMenu::UpdateSubmenuPosition(IListItem *parent)
		{
			if (!getForm() || !isVisible(false))
				return;
			int parent_index{ FindItemIndex(parent) };
			RectF client{ (RectF)getForm()->getClientRect() };
			PointF pos;
			if (parent->getParent())
			{
				int parent2_index{ FindItemIndex(parent->getParent()) };
				pos = PointF{
					m_aItems[parent2_index].Position.X + m_aItems[parent2_index].Size.X + m_sSubmenuShift.X,
					m_aItems[parent2_index].Position.Y + parent->getPosition().Y - m_aItems[parent2_index].Scroll + m_sSubmenuShift.Y };
				if (ntl::IsGreaterOrEqual<float>(pos.X + m_aItems[parent_index].Size.X, client.Right))
					pos.X = ntl::Max<float>(client.Left, m_aItems[parent2_index].Position.X - m_sShadowShift.X);
				if (ntl::IsGreaterOrEqual<float>(pos.Y + m_aItems[parent_index].Size.Y, client.Bottom))
					pos.Y = ntl::Max<float>(client.Top, pos.Y - m_aItems[parent_index].Size.Y);
			}
			else
			{
				pos = PointF{ getTransform()->getTx(), getTransform()->getTy() };
				if (ntl::IsGreaterOrEqual<float>(pos.X + m_aItems[parent_index].Size.X, client.Right))
					pos.X = ntl::Max<float>(client.Left, getTransform()->getTx() - m_sShadowShift.X);
				if (ntl::IsGreaterOrEqual<float>(pos.Y + m_aItems[parent_index].Size.Y, client.Bottom))
					pos.Y = ntl::Max<float>(client.Top, pos.Y - m_aItems[parent_index].Size.Y);
			}
			if (IsNotEqual(pos, m_aItems[parent_index].Position))
			{
				if (parent_index > 0)
					Repaint(getAbsoluteRenderRect(parent_index), false);
				m_aItems[parent_index].Position = pos;
				if (parent_index == 0)
					getTransform()->Translate(pos.X, pos.Y, 0.0);
				else
					Repaint(getAbsoluteRenderRect(parent_index), false);
			}
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				int index{ FindItemIndex(parent->getItem(i)) };
				if (m_aItems[index].Opended)
					UpdateSubmenuPosition(parent->getItem(i));
			}
		}

		void CPopupMenu::CalculateRenderRect(IListItem *parent, RectF &rect)
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
				{
					int index{ FindItemIndex(parent->getItem(i)) };
					if (m_aItems[index].Opended)
						CalculateRenderRect(parent->getItem(i), rect);
				}
			}
		}

		IListItem *CPopupMenu::getItem(IListItem *parent, const PointF &position, bool &top_scroller, bool &bottom_scroller)
		{
			top_scroller = bottom_scroller = false;
			if (!isVisible(false))
				return nullptr;
			int parent_index{ FindItemIndex(parent) };
			if (m_aItems[parent_index].ScrollMax > 0)
			{
				if (position.X >= m_aItems[parent_index].Position.X + m_sBorderWidth.Left &&
					position.X < m_aItems[parent_index].Position.X + m_aItems[parent_index].Size.X - m_sBorderWidth.Right &&
					position.Y >= m_aItems[parent_index].Position.Y + m_sBorderWidth.Top &&
					position.Y < m_aItems[parent_index].Position.Y + m_sBorderWidth.Top + m_fScrollHeight)
				{
					top_scroller = true;
					return parent;
				}
				if (position.X >= m_aItems[parent_index].Position.X + m_sBorderWidth.Left &&
					position.X < m_aItems[parent_index].Position.X + m_aItems[parent_index].Size.X - m_sBorderWidth.Right &&
					position.Y >= m_aItems[parent_index].Position.Y + m_aItems[parent_index].Size.Y - m_sBorderWidth.Bottom - m_fScrollHeight &&
					position.Y < m_aItems[parent_index].Position.Y + m_aItems[parent_index].Size.Y - m_sBorderWidth.Bottom)
				{
					bottom_scroller = true;
					return parent;
				}
			}
			RectF client{ getClientRect(parent) };
			bool in_client{
				position.X >= m_aItems[parent_index].Position.X + client.Left && position.X < m_aItems[parent_index].Position.X + client.Right &&
				position.Y >= m_aItems[parent_index].Position.Y + client.Top && position.Y < m_aItems[parent_index].Position.Y + client.Bottom };
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					int index{ FindItemIndex(parent->getItem(i)) };
					if (m_aItems[index].Opended)
					{
						IListItem *item{ getItem(parent->getItem(i), position, top_scroller, bottom_scroller) };
						if (item)
							return item;
					}
					if (in_client &&
						position.X - m_aItems[parent_index].Position.X >= parent->getItem(i)->getPosition().X &&
						position.X - m_aItems[parent_index].Position.X < parent->getItem(i)->getPosition().X + parent->getItem(i)->getSize().X &&
						position.Y - m_aItems[parent_index].Position.Y + m_aItems[parent_index].Scroll >= parent->getItem(i)->getPosition().Y &&
						position.Y - m_aItems[parent_index].Position.Y + m_aItems[parent_index].Scroll < parent->getItem(i)->getPosition().Y + parent->getItem(i)->getSize().Y)
						return parent->getItem(i);
				}
			return nullptr;
		}

		void CPopupMenu::setSizeInternal(const PointF &value)
		{
			CControl::setSize(value);
		}

		bool CPopupMenu::setVisibleInternal(const bool value)
		{
			m_bIgnoreVisible = false;
			bool result{ setVisible(value) };
			m_bIgnoreVisible = true;
			return result;
		}

		void CPopupMenu::setOwner(IListItem *item)
		{
			item->QueryService()->setOwner(QueryListItemOwner());
			for (int i = 0; i < item->getItemCount(); i++)
				setOwner(item->getItem(i));
		}

		RectF CPopupMenu::getClientRect(IListItem *parent)
		{
			int parent_index{ FindItemIndex(parent) };
			RectF result{
				m_sBorderWidth.Left + m_sPadding.Left,
				m_sBorderWidth.Top,
				m_aItems[parent_index].Size.X - m_sBorderWidth.Right - m_sPadding.Right,
				m_aItems[parent_index].Size.Y - m_sBorderWidth.Bottom };
			if (ntl::IsGreater<float>(m_aItems[parent_index].ScrollMax, 0))
			{
				result.Top += m_fScrollHeight;
				result.Bottom -= m_fScrollHeight;
			}
			else
			{
				result.Top += m_sPadding.Top;
				result.Bottom -= m_sPadding.Bottom;
			}
			result.validate();
			return result;
		}

		void CPopupMenu::MouseDownCancel()
		{
			if (m_pDownItem)
			{
				m_pDownItem->QueryService()->NotifyOnMouseDownCancel();
				m_pDownItem = nullptr;
			}
		}

		bool CPopupMenu::TestPosition(IListItem *parent, const PointF &position)
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

		RectF CPopupMenu::getAbsoluteRenderRect(IListItem *parent)
		{
			return getAbsoluteRenderRect(FindItemIndex(parent));
		}

		RectF CPopupMenu::getAbsoluteRenderRect(const int parent_index)
		{
			return AddShadow(RectF{
				m_aItems[parent_index].Position.X,
				m_aItems[parent_index].Position.Y,
				m_aItems[parent_index].Position.X + m_aItems[parent_index].Size.X,
				m_aItems[parent_index].Position.Y + m_aItems[parent_index].Size.Y },
				m_sShadowColor, m_sShadowShift, m_iShadowRadius);
		}

		void CPopupMenu::SetListItemDPI(IListItem *parent)
		{
			parent->QueryService()->setDPI(getDPI());
			for (int i = 0; i < parent->getItemCount(); i++)
				SetListItemDPI(parent->getItem(i));
		}

		bool CPopupMenu::Show(const PointF &position)
		{
			if (getForm())
			{
				CLockRepaint lock{ this };
				if (!isVisible(false))
					setVisibleInternal(true);
				getTransform()->Translate(position.X, position.Y, 0);
				UpdateSubmenuPosition(&m_cRootItem);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPopupMenu::Hide()
		{
			return setVisibleInternal(false);
		}
	#pragma endregion

	#pragma region Paint
		void CPopupMenu::Render()
		{
			ITexture *clip{ nullptr };
			Render(&m_cRootItem, getForm()->getRenderer(), &clip);
			if (clip)
				clip->Release();
		}

		void CPopupMenu::Render(IListItem *parent, IRenderer *renderer, ITexture **clip)
		{
			int parent_index{ FindItemIndex(parent) };
			PointF disp{ DispOnCanvas(m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, m_aItems[parent_index].Size.X, m_aItems[parent_index].Size.Y }, m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			IBaseTexture *old{ renderer->ActiveTarget };
			ITexture *canvas{ renderer->CreateTexture(ntl::Round<int>(all_rect.width()), ntl::Round<int>(all_rect.height()), 1, TextureFormat::RGBA, true) };
			if (canvas)
			{
				renderer
					->ActivateTarget(canvas)
					->Clear(Color{ 0, 0, 0, 0 });
				DrawBlockShadow(renderer, RectF{ 0, 0, m_aItems[parent_index].Size.X, m_aItems[parent_index].Size.Y }, m_sBorderRadius, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
				RenderBlock(m_aItems[parent_index].Size, renderer, disp);
				// Activate mask if required
				Block b{
					RectF{ disp.X, disp.Y, m_aItems[parent_index].Size.X + disp.X, m_aItems[parent_index].Size.Y + disp.Y },
					RectF{ m_sBorderWidth.Left + m_sPadding.Left, m_sBorderWidth.Top + m_sPadding.Top, m_sBorderWidth.Right + m_sPadding.Right, m_sBorderWidth.Bottom + m_sPadding.Bottom },
					m_sBorderRadius, PointLocation::Inside };
				// Draw items
				for (int i = 0; i < parent->getItemCount(); i++)
					if (parent->getItem(i)->isVisible())
					{
						float y{ parent->getItem(i)->getPosition().Y - m_aItems[parent_index].Scroll };
						if (y + parent->getItem(i)->getSize().Y >= 0 && y < m_aItems[parent_index].Size.Y)
							parent->getItem(i)->QueryService()->Render(ntl::Mat4Translate<float>(std::round(parent->getItem(i)->getPosition().X + disp.X), std::round(y + disp.Y), 0), nullptr, true, clip);
					}
				RenderScrollers(m_aItems[parent_index].Size, m_aItems[parent_index].Scroll, m_aItems[parent_index].ScrollMax, parent, b, renderer, disp);
				renderer->ActivateTarget(old);

				DrawCanvas(renderer, ntl::Mat4Translate<float>(m_aItems[parent_index].Position.X, m_aItems[parent_index].Position.Y, 0), canvas, disp);
				canvas->Release();
			}
			// Draw submenu
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible() && m_aItems[FindItemIndex(parent->getItem(i))].Opended)
					Render(parent->getItem(i), renderer, clip);
		}

		void CPopupMenu::RenderBlock(const PointF &size, IRenderer *renderer, const PointF &disp)
		{
			BlockColors colors{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom, m_sBackgroundColor, Color{ 0, 0, 0, 0 } };
			Block b{ RectF{ disp.X, disp.Y, size.X + disp.X, size.Y + disp.Y }, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
			renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
			if (m_cBackgroundGradient.getPointCount() > 0)
			{
				CStoreBlock s_block{ renderer };
				renderer
					->ActivateBlock(&b)
					->DrawGradient(b.Rect, m_cBackgroundGradient);
			}
		}

		void CPopupMenu::RenderScrollers(const PointF &size, const float scroll, const float scroll_max, IListItem *parent, const Block &block, IRenderer *renderer, const PointF &disp)
		{
			if (ntl::IsGreater<float>(scroll_max, 0))
			{
				CStoreBlock s_block{ renderer };
				renderer->ActivateBlock(&block);
				// Top
				RectF rect{ m_sBorderWidth.Left + disp.X, m_sBorderWidth.Top + disp.Y, size.X - m_sBorderWidth.Right + disp.X, m_sBorderWidth.Top + m_fScrollHeight + disp.Y };
				renderer->DrawRectangle(rect, m_sBackgroundColor);

				Color color{ ntl::IsEqual<float>(scroll, 0) ? m_sScrollArrowColorDisabled : ((m_bHoverTopScroller && m_pHoveredItem == parent) ? m_sScrollArrowColorHovered : m_sScrollArrowColorNormal) };
				if (color.A > 0)
				{
					float h{ rect.height() - 2 }, x{ (rect.Right + rect.Left) * 0.5f };
					renderer->DrawTriangle(PointF{ x - h, rect.Bottom - 1 }, PointF{ x, rect.Top + 1 }, PointF{ x + h, rect.Bottom - 1 }, color);
				}
				// Bottom
				rect.Top = size.Y - m_sBorderWidth.Bottom - m_fScrollHeight + disp.X;
				rect.Bottom = size.Y - m_sBorderWidth.Bottom + disp.Y;
				renderer->DrawRectangle(rect, m_sBackgroundColor);

				color = ntl::IsEqual<float>(scroll, scroll_max) ? m_sScrollArrowColorDisabled : ((m_bHoverBottomScroller && m_pHoveredItem == parent) ? m_sScrollArrowColorHovered : m_sScrollArrowColorNormal);
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