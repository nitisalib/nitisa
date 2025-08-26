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
	#pragma region CTimerListener
		CMultiButton::CTimerListener::CTimerListener(CMultiButton *control) :
			m_pControl{ control }
		{

		}

		void CMultiButton::CTimerListener::NotifyOnTimer(const PlatformHandle id)
		{
			m_pControl->getForm()->DeleteTimer(m_pControl->m_hTimer);
			m_pControl->m_hTimer = nullptr;
			m_pControl->m_bHasExtra = true;
			m_pControl->UpdateHoveredButtonIndex();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_pCanvasExtra)
				m_pControl->m_pCanvasExtra->setValid(false);
			m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region CGradientListener
		CMultiButton::CGradientListener::CGradientListener(CMultiButton *control) :
			m_pControl{ control }
		{

		}

		void CMultiButton::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bHasExtra && m_pControl->m_pCanvasExtra)
					m_pControl->m_pCanvasExtra->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CMultiButton::CMultiButton():
			CControl(L"MultiButton", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_bHasExtra{ false },
			m_fDelay{ 0.5f },
			m_iActiveButtonIndex{ 0 },
			m_pImageList{ nullptr },
			m_eOpenDirection{ OpenDirection::Bottom },
			m_aOutlineMask{
				OutlineMask,
				OutlineMask,
				OutlineMask,
				OutlineMask,
				OutlineMask,
				OutlineMask,
				OutlineMask,
				OutlineMask,
				OutlineMask,
				OutlineMask,
				OutlineMask,
				OutlineMask,
				OutlineMask
			},
			m_aOutlineColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 60, 127, 177, 255 },
				Color{ 60, 127, 177, 255 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 60, 127, 177, 255 },
				Color{ 60, 127, 177, 255 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 }
			},
			m_aOpenerSize{
				4,
				4,
				4,
				4,
				4,
				4,
				4,
				4,
				4,
				4,
				4,
				4,
				4 },
			m_aOpenerColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 127, 127, 127, 255 } },
			m_aBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aOuterBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aOuterBorderColor{
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } } },
			m_aInnerBorderWidth{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aInnerBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aBackgroundColor{
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 60, 127, 177, 255 },
				Color{ 60, 127, 177, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 200, 200, 200, 255 },
				Color{ 240, 240, 240, 255 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aPadding{
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 } },
			m_aImageSize{
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain,
				ImageSize::Contain },
			m_aCaptionHorizontalAlign{
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center },
			m_aCaptionVerticalAlign{
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle },
			m_aCaptionColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 } },
			m_aShadowRadius{
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1 },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 } },
			m_cOwner{ this },
			m_pCanvas{ nullptr },
			m_pCanvasExtra{ nullptr },
			m_bIgnoreGradient{ false },
			m_hTimer{ nullptr },
			m_bEnterDown{ false },
			m_iHoveredButtonIndex{ -2 },
			m_cTimerListener{ this }
		{
			setService(new CMultiButtonService(this), true);
			setSize(PointF{ 32, 32 });
		}

		CMultiButton::CMultiButton(IControl *parent) :CMultiButton()
		{
			setParent(parent);
		}

		CMultiButton::CMultiButton(IForm *parent) : CMultiButton()
		{
			setForm(parent);
		}

		void CMultiButton::BeforeRelease()
		{
			DeleteButtons();
			CControl::BeforeRelease();
		}
	#pragma endregion

	#pragma region IControl getters
		IControl *CMultiButton::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CMultiButton::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CMultiButton::getControl(const PointF &position)
		{
			if (isVisible(false))
			{
				Mat4f m{ ntl::Inversed<float>(getTransformMatrix()) };
				Vec4f v{ m * Vec4f{ position.X, position.Y, 0, 1 } };
				if (v.X >= 0 && v.X < getWidth() && v.Y >= 0 && v.Y < getHeight())
					return this;
				if (m_bHasExtra && CalculateExtraRect().is_inside(PointF{ v.X, v.Y }))
					return this;
			}
			return nullptr;
		}

		RectF CMultiButton::getRenderRect()
		{
			State st{ CalculateState() };
			RectF result{ AddShadow(getRect(), m_aShadowColor[(int)st], m_aShadowShift[(int)st], m_aShadowRadius[(int)st]) };
			if (m_bHasExtra)
				result += CalculateExtraRect();
			return result;
		}

		bool CMultiButton::hasExtra()
		{
			return m_bHasExtra;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CMultiButton::setAlign(const Align value)
		{
			return false;
		}

		bool CMultiButton::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aOpenerSize[i] *= avg;
					m_aBorderRadius[i] *= s;
					m_aOuterBorderWidth[i] *= s;
					m_aInnerBorderWidth[i] *= s;
					m_aPadding[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
				}
				UpdateHoveredButtonIndex();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IComponentItemList getters
		int CMultiButton::getItemCount()
		{
			return (int)m_aButtons.size();
		}

		IListItem *CMultiButton::getItem(const int index)
		{
			if (index >= 0 && index < (int)m_aButtons.size())
				return m_aButtons[index];
			return nullptr;
		}

		int CMultiButton::getItemIndex(IListItem *item)
		{
			for (int i = 0; i < (int)m_aButtons.size(); i++)
				if (m_aButtons[i] == item)
					return i;
			return -1;
		}

		bool CMultiButton::isAcceptItem(IListItem *item)
		{
			return cast<IListItemMultiButton*>(item) != nullptr;
		}
	#pragma endregion

	#pragma region IComponentItemList items
		bool CMultiButton::AddItem(IListItem *item)
		{
			return AddButton(cast<IListItemMultiButton*>(item));
		}

		bool CMultiButton::InsertItem(IListItem *item, const int before)
		{
			return InsertButton(cast<IListItemMultiButton*>(item), before);
		}

		bool CMultiButton::DeleteItem(const int index)
		{
			return DeleteButton(index);
		}

		bool CMultiButton::DeleteItem(IListItem *item)
		{
			return DeleteButton(cast<IListItemMultiButton*>(item));
		}

		bool CMultiButton::DeleteItems()
		{
			return DeleteButtons();
		}
	#pragma endregion

	#pragma region IComponentItemList methods
		IListItemOwner *CMultiButton::QueryListItemOwner()
		{
			return &m_cOwner;
		}
	#pragma endregion

	#pragma region IButtonList getters
		float CMultiButton::getDelay()
		{
			return m_fDelay;
		}

		int CMultiButton::getButtonCount()
		{
			return (int)m_aButtons.size();
		}

		IListItemMultiButton *CMultiButton::getButton(const int index)
		{
			if (index >= 0 && index < (int)m_aButtons.size())
				return cast<IListItemMultiButton*>(m_aButtons[index]);
			return nullptr;
		}

		int CMultiButton::getButtonIndex(IListItemMultiButton *item)
		{
			for (int i = 0; i < (int)m_aButtons.size(); i++)
				if (m_aButtons[i] == item)
					return i;
			return -1;
		}

		int CMultiButton::getActiveButtonIndex()
		{
			return m_iActiveButtonIndex;
		}

		IListItemMultiButton *CMultiButton::getActiveButton()
		{
			if (m_iActiveButtonIndex >= 0 && m_iActiveButtonIndex < (int)m_aButtons.size())
				return cast<IListItemMultiButton*>(m_aButtons[m_iActiveButtonIndex]);
			return nullptr;
		}
	#pragma endregion

	#pragma region IButtonList setters
		bool CMultiButton::setDelay(const float value, const float tolerance)
		{
			if (ntl::IsGreater<float>(value, 0, tolerance) && ntl::IsNotEqual<float>(value, m_fDelay, tolerance))
			{
				m_fDelay = value;
				return true;
			}
			return false;
		}

		bool CMultiButton::setActiveButtonIndex(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iActiveButtonIndex)
			{
				m_iActiveButtonIndex = v;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setActiveButton(IListItemMultiButton *value)
		{
			return setActiveButtonIndex(getButtonIndex(value));
		}
	#pragma endregion

	#pragma region IButtonList buttons
		bool CMultiButton::AddButton(IListItemMultiButton *item)
		{
			if (!m_bHasExtra && item && !item->getParent() && !in<IListItem*>(item, m_aButtons))
			{
				m_aButtons.push_back(item);
				item->QueryService()->setOwner(&m_cOwner);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		IListItemMultiButton *CMultiButton::AddButton(const String &caption)
		{
			if (!m_bHasExtra)
			{
				IListItemMultiButton *result{ new CListItemMultiButton(caption) };
				m_aButtons.push_back(result);
				result->QueryService()->setOwner(&m_cOwner);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return result;
			}
			return nullptr;
		}

		bool CMultiButton::InsertButton(IListItemMultiButton *item, const int before)
		{
			if (before >= (int)m_aButtons.size())
				return AddButton(item);
			if (!m_bHasExtra && item && !item->getParent() && !in<IListItem*>(item, m_aButtons))
			{
				if (before < 0)
					m_aButtons.insert(m_aButtons.begin(), item);
				else
					m_aButtons.insert(m_aButtons.begin() + before, item);
				item->QueryService()->setOwner(&m_cOwner);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		IListItemMultiButton *CMultiButton::InsertButton(const String &caption, const int before)
		{
			if (before >= (int)m_aButtons.size())
				return AddButton(caption);
			if (!m_bHasExtra)
			{
				IListItemMultiButton *result{ new CListItemMultiButton(caption) };
				if (before < 0)
					m_aButtons.insert(m_aButtons.begin(), result);
				else
					m_aButtons.insert(m_aButtons.begin() + before, result);
				result->QueryService()->setOwner(&m_cOwner);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return result;
			}
			return nullptr;
		}

		bool CMultiButton::DeleteButton(const int index)
		{
			if (!m_bHasExtra && index >= 0 && index < (int)m_aButtons.size())
			{
				m_aButtons[index]->Release();
				m_aButtons.erase(m_aButtons.begin() + index);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::DeleteButton(IListItemMultiButton *item)
		{
			return DeleteButton(getButtonIndex(item));
		}

		bool CMultiButton::DeleteButtons()
		{
			if (!m_bHasExtra && m_aButtons.size() > 0)
			{
				for (auto btn : m_aButtons)
					btn->Release();
				m_aButtons.clear();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		IImageList *CMultiButton::getImageList()
		{
			return m_pImageList;
		}

		CMultiButton::OpenDirection CMultiButton::getOpenDirection() const
		{
			return m_eOpenDirection;
		}

		unsigned int CMultiButton::getOutlineMask(const State state) const
		{
			return m_aOutlineMask[(int)state];
		}

		Color CMultiButton::getOutlineColor(const State state) const
		{
			return m_aOutlineColor[(int)state];
		}

		float CMultiButton::getOpenerSize(const State state) const
		{
			return m_aOpenerSize[(int)state];
		}

		Color CMultiButton::getOpenerColor(const State state) const
		{
			return m_aOpenerColor[(int)state];
		}

		RectF CMultiButton::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		RectF CMultiButton::getOuterBorderWidth(const State state) const
		{
			return m_aOuterBorderWidth[(int)state];
		}

		BorderColor CMultiButton::getOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state];
		}

		RectF CMultiButton::getInnerBorderWidth(const State state) const
		{
			return m_aInnerBorderWidth[(int)state];
		}

		BorderColor CMultiButton::getInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state];
		}

		Color CMultiButton::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CMultiButton::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		RectF CMultiButton::getPadding(const State state) const
		{
			return m_aPadding[(int)state];
		}

		CMultiButton::ImageSize CMultiButton::getImageSize(const State state) const
		{
			return m_aImageSize[(int)state];
		}

		TextAlign CMultiButton::getCaptionHorizontalAlign(const State state) const
		{
			return m_aCaptionHorizontalAlign[(int)state];
		}

		VerticalAlign CMultiButton::getCaptionVerticalAlign(const State state) const
		{
			return m_aCaptionVerticalAlign[(int)state];
		}

		Color CMultiButton::getCaptionColor(const State state) const
		{
			return m_aCaptionColor[(int)state];
		}

		int CMultiButton::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CMultiButton::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CMultiButton::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CMultiButton::setImageList(IImageList *value)
		{
			if (value != m_pImageList)
			{
				m_pImageList = value;
				if (m_aButtons.size() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_bHasExtra && m_pCanvasExtra)
						m_pCanvasExtra->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setOpenDirection(const OpenDirection value)
		{
			if (!m_bHasExtra && value != m_eOpenDirection)
			{
				m_eOpenDirection = value;
				if (m_aButtons.size() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setOutlineMask(const State state, const unsigned int value)
		{
			if (value != m_aOutlineMask[(int)state])
			{
				m_aOutlineMask[(int)state] = value;
				if (state == CalculateState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setOutlineColor(const State state, const Color &value)
		{
			if (value != m_aOutlineColor[(int)state])
			{
				m_aOutlineColor[(int)state] = value;
				if (state == CalculateState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setOpenerSize(const State state, const float value, const float tolerance)
		{
			if (ntl::IsPositive<float>(value, tolerance) && ntl::IsNotEqual<float>(value, m_aOpenerSize[(int)state], tolerance))
			{
				m_aOpenerSize[(int)state] = value;
				if (m_aButtons.size() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setOpenerColor(const State state, const Color &value)
		{
			if (value != m_aOpenerColor[(int)state])
			{
				m_aOpenerColor[(int)state] = value;
				if (m_aButtons.size() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setBorderRadius(const State state, const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_aBorderRadius[(int)state], tolerance))
			{
				m_aBorderRadius[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setOuterBorderWidth(const State state, const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_aOuterBorderWidth[(int)state], tolerance))
			{
				m_aOuterBorderWidth[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aOuterBorderColor[(int)state])
			{
				m_aOuterBorderColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setInnerBorderWidth(const State state, const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_aInnerBorderWidth[(int)state], tolerance))
			{
				m_aInnerBorderWidth[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aInnerBorderColor[(int)state])
			{
				m_aInnerBorderColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setPadding(const State state, const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_aPadding[(int)state], tolerance))
			{
				m_aPadding[(int)state] = value;
				if (m_aButtons.size() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_bHasExtra && m_pCanvasExtra)
						m_pCanvasExtra->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setImageSize(const State state, const ImageSize value)
		{
			if (value != m_aImageSize[(int)state])
			{
				m_aImageSize[(int)state] = value;
				if (m_aButtons.size() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_bHasExtra && m_pCanvasExtra)
						m_pCanvasExtra->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setCaptionHorizontalAlign(const State state, const TextAlign value)
		{
			if (value != m_aCaptionHorizontalAlign[(int)state])
			{
				m_aCaptionHorizontalAlign[(int)state] = value;
				if (m_aButtons.size() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_bHasExtra && m_pCanvasExtra)
						m_pCanvasExtra->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setCaptionVerticalAlign(const State state, const VerticalAlign value)
		{
			if (value != m_aCaptionVerticalAlign[(int)state])
			{
				m_aCaptionVerticalAlign[(int)state] = value;
				if (m_aButtons.size() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_bHasExtra && m_pCanvasExtra)
						m_pCanvasExtra->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setCaptionColor(const State state, const Color &value)
		{
			if (value != m_aCaptionColor[(int)state])
			{
				m_aCaptionColor[(int)state] = value;
				if (m_aButtons.size() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_bHasExtra && m_pCanvasExtra)
						m_pCanvasExtra->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMultiButton::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setShadowShift(const State state, const PointF &value, const float tolerance)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state], tolerance))
			{
				CLockRepaint lock{ this };
				Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				CLockRepaint lock{ this };
				Repaint(false);
				m_aShadowColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setOutlineMask(const unsigned int value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aOutlineMask[i])
				{
					m_aOutlineMask[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setOutlineColor(const Color &value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aOutlineColor[i])
				{
					m_aOutlineColor[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setOpenerSize(const float value, const float tolerance)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (ntl::IsPositive<float>(value, tolerance) && ntl::IsNotEqual<float>(value, m_aOpenerSize[i], tolerance))
				{
					m_aOpenerSize[i] = value;
					changed = true;
				}
			if (changed && m_aButtons.size() > 0)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setOpenerColor(const Color &value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aOpenerColor[i])
				{
					m_aOpenerColor[i] = value;
					changed = true;
				}
			if (changed && m_aButtons.size() > 0)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setBorderRadius(const RectF &value, const float tolerance)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (!value.has_negative(tolerance) && IsNotEqual(value, m_aBorderRadius[i], tolerance))
				{
					m_aBorderRadius[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setOuterBorderWidth(const RectF &value, const float tolerance)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (!value.has_negative(tolerance) && IsNotEqual(value, m_aOuterBorderWidth[i], tolerance))
				{
					m_aOuterBorderWidth[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setOuterBorderColor(const BorderColor &value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aOuterBorderColor[i])
				{
					m_aOuterBorderColor[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setInnerBorderWidth(const RectF &value, const float tolerance)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (!value.has_negative(tolerance) && IsNotEqual(value, m_aInnerBorderWidth[i], tolerance))
				{
					m_aInnerBorderWidth[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setInnerBorderColor(const BorderColor &value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aInnerBorderColor[i])
				{
					m_aInnerBorderColor[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setBackgroundColor(const Color &value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aBackgroundColor[i])
				{
					m_aBackgroundColor[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setPadding(const RectF &value, const float tolerance)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (!value.has_negative(tolerance) && IsNotEqual(value, m_aPadding[i], tolerance))
				{
					m_aPadding[i] = value;
					changed = true;
				}
			if (changed && m_aButtons.size() > 0)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setImageSize(const ImageSize value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aImageSize[i])
				{
					m_aImageSize[i] = value;
					changed = true;
				}
			if (changed && m_aButtons.size() > 0)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setCaptionHorizontalAlign(const TextAlign value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aCaptionHorizontalAlign[i])
				{
					m_aCaptionHorizontalAlign[i] = value;
					changed = true;
				}
			if (changed && m_aButtons.size() > 0)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setCaptionVerticalAlign(const VerticalAlign value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aCaptionVerticalAlign[i])
				{
					m_aCaptionVerticalAlign[i] = value;
					changed = true;
				}
			if (changed && m_aButtons.size() > 0)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setCaptionColor(const Color &value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aCaptionColor[i])
				{
					m_aCaptionColor[i] = value;
					changed = true;
				}
			if (changed && m_aButtons.size() > 0)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bHasExtra && m_pCanvasExtra)
					m_pCanvasExtra->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setShadowRadius(const int value)
		{
			bool changed{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value >= 1 && value != m_aShadowRadius[i])
				{
					Repaint(false);
					m_aShadowRadius[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setShadowShift(const PointF &value, const float tolerance)
		{
			bool changed{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (IsNotEqual(value, m_aShadowShift[i], tolerance))
				{
					Repaint(false);
					m_aShadowShift[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMultiButton::setShadowColor(const Color &value)
		{
			bool changed{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aShadowColor[i])
				{
					Repaint(false);
					m_aShadowColor[i] = value;
					changed = true;
				}
			if (changed)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CMultiButton::SortItems()
		{

		}

		void CMultiButton::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
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
				case State::Down:
					state = L"Down";
					break;
				case State::DownHovered:
					state = L"DownHovered";
					break;
				case State::DownFocused:
					state = L"DownFocused";
					break;
				case State::DownFocusedHovered:
					state = L"DownFocusedHovered";
					break;
				case State::Active:
					state = L"Active";
					break;
				case State::ActiveHovered:
					state = L"ActiveHovered";
					break;
				case State::Inactive:
					state = L"Inactive";
					break;
				case State::InactiveHovered:
					state = L"InactiveHovered";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".OutlineMask[" + state + L"]", m_aOutlineMask[i]);
				style->getOption(m_sClassName + L".OutlineColor[" + state + L"]", m_aOutlineColor[i]);
				style->getOption(m_sClassName + L".OpenerSize[" + state + L"]", m_aOpenerSize[i]);
				style->getOption(m_sClassName + L".OpenerColor[" + state + L"]", m_aOpenerColor[i]);
				style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]);
				style->getOption(m_sClassName + L".OuterBorderWidth[" + state + L"]", m_aOuterBorderWidth[i]);
				style->getOption(m_sClassName + L".OuterBorderColor[" + state + L"]", m_aOuterBorderColor[i]);
				style->getOption(m_sClassName + L".InnerBorderWidth[" + state + L"]", m_aInnerBorderWidth[i]);
				style->getOption(m_sClassName + L".InnerBorderColor[" + state + L"]", m_aInnerBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".Padding[" + state + L"]", m_aPadding[i]);
				style->getOption(m_sClassName + L".CaptionColor[" + state + L"]", m_aCaptionColor[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
			}
			m_bIgnoreGradient = false;
		}

		bool CMultiButton::UpdateHoveredButtonIndex()
		{
			if (getForm())
				return UpdateHoveredButtonIndex(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			if (m_iActiveButtonIndex != -2)
			{
				m_iActiveButtonIndex = -2;
				return true;
			}
			return false;
		}

		bool CMultiButton::UpdateHoveredButtonIndex(const PointF &p)
		{
			int index{ -2 };
			if (m_bHasExtra)
			{
				for (int i = 0; i < (int)m_aButtons.size(); i++)
					if (CalculateButtonRect(i).is_inside(p))
					{
						index = i;
						break;
					}
			}
			else if (getRect().is_inside(p))
				index = -1;
			if (index != m_iHoveredButtonIndex)
			{
				m_iHoveredButtonIndex = index;
				return true;
			}
			return false;
		}

		RectF CMultiButton::CalculateExtraRect()
		{
			switch (m_eOpenDirection)
			{
			case OpenDirection::Left:
				return RectF{ -getWidth() * (float)m_aButtons.size(), 0, 0, getHeight() };
			case OpenDirection::Top:
				return RectF{ 0, -getHeight() * (float)m_aButtons.size(), getWidth(), 0 };
			case OpenDirection::Right:
				return RectF{ getWidth(), 0, getWidth() * float(m_aButtons.size() + 1), getHeight() };
			default:
				return RectF{ 0, getHeight(), getWidth(), getHeight() * float(m_aButtons.size() + 1) };
			}
		}

		RectF CMultiButton::CalculateButtonRect(const int index)
		{
			switch (m_eOpenDirection)
			{
			case OpenDirection::Left:
				return RectF{ -getWidth() * float(index + 1), 0, -getWidth() * (float)index, getHeight() };
			case OpenDirection::Top:
				return RectF{ 0, -getHeight() * float(index + 1), getWidth(), -getHeight() * (float)index };
			case OpenDirection::Right:
				return RectF{ getWidth() * float(index + 1), 0, getWidth() * float(index + 2), getHeight() };
			default:
				return RectF{ 0, getHeight() * float(index + 1), getWidth(), getHeight() * float(index + 2) };
			}
		}

		CMultiButton::State CMultiButton::CalculateState()
		{
			if (m_iActiveButtonIndex < 0 || m_iActiveButtonIndex >= (int)m_aButtons.size() || !isEnabled(false))
				return State::Disabled;
			if (!Application->Editor) // As state is calculated on the fly we should consider the control can be under the Form Builder where all states except Normal and Disabled are not being used
			{
				PointF p{ FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				if (m_hTimer || m_bHasExtra || m_bEnterDown)
				{
					if (getRect().is_inside(p))
					{
						if (isFocused())
							return State::DownFocusedHovered;
						return State::DownHovered;
					}
					if (isFocused())
						return State::DownFocused;
					return State::Down;
				}
				if (getRect().is_inside(p))
				{
					if (isFocused())
						return State::FocusedHovered;
					return State::Hovered;
				}
				if (isFocused())
					return State::Focused;
			}
			return State::Normal;
		}

		CMultiButton::State CMultiButton::CalculateState(const int index)
		{
			PointF p{ FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())) };
			RectF r{ CalculateButtonRect(index) };
			if (r.is_inside(p))
			{
				if (index == m_iActiveButtonIndex)
					return State::ActiveHovered;
				return State::InactiveHovered;
			}
			if (index == m_iActiveButtonIndex)
				return State::Active;
			return State::Inactive;
		}

		int CMultiButton::CalculateButtonImageIndex(IListItemMultiButton *button, const State state)
		{
			CListItemMultiButton *btn{ cast<CListItemMultiButton*>(button) };
			if (btn)
			{
				switch (state)
				{
				case State::Hovered:
					return btn->getImageIndexHovered();
				case State::Focused:
					return btn->getImageIndexFocused();
				case State::FocusedHovered:
					return btn->getImageIndexFocusedHovered();
				case State::Down:
					return btn->getImageIndexDown();
				case State::DownHovered:
					return btn->getImageIndexDownHovered();
				case State::DownFocused:
					return btn->getImageIndexDownFocused();
				case State::DownFocusedHovered:
					return btn->getImageIndexDownFocusedHovered();
				case State::Active:
					return btn->getImageIndexActive();
				case State::ActiveHovered:
					return btn->getImageIndexActiveHovered();
				case State::Inactive:
					return btn->getImageIndexInactive();
				case State::InactiveHovered:
					return btn->getImageIndexInactiveHovered();
				case State::Disabled:
					return btn->getImageIndexDisabled();
				default:
					break;
				}
			}
			return button->getImageIndex();
		}
	#pragma endregion

	#pragma region Render
		void CMultiButton::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			State state{ CalculateState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
				DrawBlockShadow(
					renderer,
					rect,
					m_aBorderRadius[(int)state],
					m_aShadowColor[(int)state],
					m_aShadowShift[(int)state],
					m_aShadowRadius[(int)state]);
				if (rect.has_area())
				{
					if (m_iActiveButtonIndex >= 0 && m_iActiveButtonIndex < (int)m_aButtons.size())
						RenderButton(renderer, rect, state, cast<IListItemMultiButton*>(m_aButtons[m_iActiveButtonIndex]));
					else
						RenderButton(renderer, rect, state, nullptr);
					RectF r{
						rect.Left + m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left,
						rect.Top + m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top,
						rect.Right - m_aOuterBorderWidth[(int)state].Right - m_aInnerBorderWidth[(int)state].Right,
						rect.Bottom - m_aOuterBorderWidth[(int)state].Bottom - m_aInnerBorderWidth[(int)state].Bottom
					};
					if (r.has_area())
					{
						RenderOpener(renderer, r, state);
						RenderOutline(renderer, r, state);
					}
				}
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CMultiButton::RenderOutline(IRenderer *renderer, const RectF &rect, const State state)
		{
			if (m_aOutlineMask[(int)state] != 0 && m_aOutlineColor[(int)state].A > 0)
			{
				RectF r{
					rect.Left + m_aPadding[(int)state].Left,
					rect.Top + m_aPadding[(int)state].Top,
					rect.Right - m_aPadding[(int)state].Right,
					rect.Bottom - m_aPadding[(int)state].Bottom
				};
				if (r.has_area())
				{
					CStoreBitmask s_bitmask{ renderer };
					renderer
						->ActivateBitmask(Bitmask{ m_aOutlineMask[(int)state], 0, true, false })
						->DrawLines({
							PointF{ r.Left, r.Top },
							PointF{ r.Right, r.Top },
							PointF{ r.Right, r.Bottom - 1 },
							PointF{ r.Left + 1, r.Bottom - 1 },
							PointF{ r.Left + 1, r.Top + 1 } },
							m_aOutlineColor[(int)state],
							false);
				}
			}
		}

		void CMultiButton::RenderOpener(IRenderer *renderer, const RectF &rect, const State state)
		{
			if (m_aButtons.size() > 0 && m_aOpenerColor[(int)state].A > 0 && ntl::IsGreater<float>(m_aOpenerSize[(int)state], 0))
			{
				if (rect.height() >= m_aOpenerSize[(int)state] && rect.width() >= m_aOpenerSize[(int)state])
				{
					switch (m_eOpenDirection)
					{
					case OpenDirection::Left:
						renderer->DrawTriangle(
							PointF{ rect.Left, rect.Bottom - m_aOpenerSize[(int)state] - 1 },
							PointF{ rect.Left + m_aOpenerSize[(int)state] + 1, rect.Bottom },
							PointF{ rect.Left, rect.Bottom },
							m_aOpenerColor[(int)state]);
						break;
					case OpenDirection::Top:
						renderer->DrawTriangle(
							PointF{ rect.Left, rect.Top },
							PointF{ rect.Left + m_aOpenerSize[(int)state] + 1, rect.Top },
							PointF{ rect.Left, rect.Top + m_aOpenerSize[(int)state] + 1 },
							m_aOpenerColor[(int)state]);
						break;
					case OpenDirection::Right:
						renderer->DrawTriangle(
							PointF{ rect.Right - m_aOpenerSize[(int)state], rect.Top },
							PointF{ rect.Right, rect.Top },
							PointF{ rect.Right, rect.Top + m_aOpenerSize[(int)state] },
							m_aOpenerColor[(int)state]);
						break;
					default:
						renderer->DrawTriangle(
							PointF{ rect.Right, rect.Bottom - m_aOpenerSize[(int)state] },
							PointF{ rect.Right, rect.Bottom },
							PointF{ rect.Right - m_aOpenerSize[(int)state], rect.Bottom },
							m_aOpenerColor[(int)state]);
						break;
					}
				}
			}
		}

		void CMultiButton::RenderButton(IRenderer *renderer, const RectF &rect, const State state, IListItemMultiButton *button)
		{
			DrawDoubleBackground(
				renderer,
				rect,
				m_aOuterBorderWidth[(int)state],
				m_aInnerBorderWidth[(int)state],
				m_aBorderRadius[(int)state],
				m_aOuterBorderColor[(int)state],
				m_aInnerBorderColor[(int)state],
				m_aBackgroundColor[(int)state],
				m_aBackgroundGradient[(int)state]);
			if (button)
			{
				RectF client{
					rect.Left + m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left + m_aPadding[(int)state].Left,
					rect.Top + m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top + m_aPadding[(int)state].Top,
					rect.Right - m_aOuterBorderWidth[(int)state].Right - m_aInnerBorderWidth[(int)state].Right - m_aPadding[(int)state].Right,
					rect.Bottom - m_aOuterBorderWidth[(int)state].Bottom - m_aInnerBorderWidth[(int)state].Bottom - m_aPadding[(int)state].Bottom
				};
				if (client.has_area())
				{
					// Image
					if (m_pImageList)
					{
						ITexture *image{ m_pImageList->getTexture(CalculateButtonImageIndex(button, state)) };
						if (image)
						{
							PointF scale;
							Mat4f t, s;
							switch (m_aImageSize[(int)state])
							{
							case ImageSize::Cover:
								scale.X = ntl::Max<float>(client.width() / image->Widthf, client.height() / image->Heightf);
								ntl::Scale<float>(s, scale.X, scale.X, 1);
								ntl::Translate<float>(t, (client.Left + client.Right - image->Widthf * scale.X) * 0.5f, (client.Top + client.Bottom - image->Heightf * scale.X) * 0.5f, 0);
								break;
							case ImageSize::Contain:
								scale.X = ntl::Min<float>(client.width() / image->Widthf, client.height() / image->Heightf);
								ntl::Scale<float>(s, scale.X, scale.X, 1);
								ntl::Translate<float>(t, (client.Left + client.Right - image->Widthf * scale.X) * 0.5f, (client.Top + client.Bottom - image->Heightf * scale.X) * 0.5f, 0);
								break;
							case ImageSize::Stretch:
								scale = PointF{ client.width() / image->Widthf, client.height() / image->Heightf };
								ntl::Scale<float>(s, scale.X, scale.Y, 1);
								ntl::Translate<float>(t, (client.Left + client.Right - image->Widthf * scale.X) * 0.5f, (client.Top + client.Bottom - image->Heightf * scale.Y) * 0.5f, 0);
								break;
							default: // Original
								ntl::Translate<float>(t, (client.Left + client.Right - image->Widthf) * 0.5f, (client.Top + client.Bottom - image->Heightf) * 0.5f, 0);
								ntl::Identity<float>(s);
								break;
							}
							CStorePrimitiveMatrix s_matrix{ renderer };
							Block b{ client, RectF{ 0, 0, 0, 0 }, m_aBorderRadius[(int)state], PointLocation::Inside };
							CStoreBlock s_block{ renderer };
							renderer
								->ActivateBlock(&b)
								->ActivatePrimitiveMatrix(t * s)
								->DrawImage(image, 1);
						}
					}
					// Caption
					if (!button->getCaption().empty() && m_aCaptionColor[(int)state].A > 0)
					{
						IFont *f{ getFont() };
						IPlatformFont *pf{ f->getPlatformFont(renderer) };
						PointF size{ pf->getStringSize(button->getCaption(), f->Distance) }, pos;
						switch (m_aCaptionHorizontalAlign[(int)state])
						{
						case TextAlign::Center:
							pos.X = (client.Left + client.Right - size.X) * 0.5f;
							break;
						case TextAlign::Right:
							pos.X = client.Right - size.X;
							break;
						default: // Left
							pos.X = client.Left;
							break;
						}
						switch (m_aCaptionVerticalAlign[(int)state])
						{
						case VerticalAlign::Middle:
							pos.Y = (client.Top + client.Bottom - size.Y) * 0.5f;
							break;
						case VerticalAlign::Bottom:
							pos.Y = client.Bottom - size.Y;
							break;
						default: // Top
							pos.Y = client.Top;
							break;
						}
						CStorePrimitiveMatrix s_matrix{ renderer };
						Block b{ client, RectF{ 0, 0, 0, 0 }, m_aBorderRadius[(int)state], PointLocation::Inside };
						CStoreBlock s_block{ renderer };
						renderer
							->ActivateBlock(&b)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X), std::round(pos.Y), 0))
							->DrawText(button->getCaption(), pf, f->Distance, m_aCaptionColor[(int)state]);
					}
				}
			}
		}

		void CMultiButton::RenderExtra()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			RectF rect{ CalculateExtraRect() };
			if (PrepareCanvas(renderer, &m_pCanvasExtra, rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvasExtra)
					->Clear(Color{ 0, 0, 0, 0 });
				for (int i = 0; i < (int)m_aButtons.size(); i++)
					RenderButton(renderer, CalculateButtonRect(i) - rect.LeftTop, CalculateState(i), cast<IListItemMultiButton*>(m_aButtons[i]));
				m_pCanvasExtra->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix() * ntl::Mat4Translate<float>(rect.Left, rect.Top, 0), m_pCanvasExtra, PointF{ 0, 0 });
		}
	#pragma endregion
	}
}