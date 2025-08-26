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
	#pragma region CGradientListener
		CIconButton::CGradientListener::CGradientListener(CIconButton *control) :
			m_pControl{ control }
		{

		}

		void CIconButton::CGradientListener::NotifyOnChange()
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
		CIconButton::CIconButton() :
			CControl(L"IconButton", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_aOuterBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aInnerBorderWidth{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aOuterBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
				BorderColor{ Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aInnerBorderColor{
				BorderColor{ Color{ 243, 243, 243, 255 }, Color{ 243, 243, 243, 255 }, Color{ 243, 243, 243, 255 }, Color{ 243, 243, 243, 255 } },
				BorderColor{ Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 } },
				BorderColor{ Color{ 59, 214, 253, 255 }, Color{ 59, 214, 253, 255 }, Color{ 59, 214, 253, 255 }, Color{ 59, 214, 253, 255 } },
				BorderColor{ Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 } } },
			m_aBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
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
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowRadius{ 1, 1, 1, 1, 1, 1, 1 },
			m_aPadding{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aImageList{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
			m_aIconIndex{ -1, -1, -1, -1, -1, -1, -1 },
			m_aOutlineMask{
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100 },
			m_aOutlineColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 0, 0 } },
			m_eIconSize{ IconSize::Original },
			m_bOutlineInEditor{ true },
			m_pCanvas{ nullptr },
			m_bKeyDown{ false },
			m_bMouseDown{ false },
			m_bIgnoreGradient{ false },
			OnClick{ nullptr }
		{
			setService(new CIconButtonService(this), true);
			setSize(PointF{ 24, 24 });
		}

		CIconButton::CIconButton(IControl *parent) :CIconButton()
		{
			setParent(parent);
		}

		CIconButton::CIconButton(IForm *parent) : CIconButton()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CIconButton::getClientRect()
		{
			RectF result{ 0, 0, getWidth(), getHeight() };
			State state{ getState() };
			result.Left += m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left + m_aPadding[(int)state].Left;
			result.Top += m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top + m_aPadding[(int)state].Top;
			result.Right -= m_aOuterBorderWidth[(int)state].Right + m_aInnerBorderWidth[(int)state].Right + m_aPadding[(int)state].Right;
			result.Bottom -= m_aOuterBorderWidth[(int)state].Bottom + m_aInnerBorderWidth[(int)state].Bottom + m_aPadding[(int)state].Bottom;
			result.validate();
			return result;
		}

		RectF CIconButton::getRenderRect()
		{
			RectF result{ getRenderRect(State::Normal) };
			for (int i = (int)State::Normal + 1; i <= (int)State::Disabled; i++)
				result += getRenderRect((State)i);
			return result;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CIconButton::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aOuterBorderWidth[i] *= s;
					m_aInnerBorderWidth[i] *= s;
					m_aBorderRadius[i] *= avg;
					m_aShadowShift[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aPadding[i] *= s;
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CIconButton::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region IIconButton methods
		void CIconButton::Click()
		{
			if (OnClick)
				OnClick(this);
		}
	#pragma endregion

	#pragma region Getters
		CIconButton::State CIconButton::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_bKeyDown || m_bMouseDown)
			{
				if (isHovered())
					return State::ActiveHovered;
				return State::Active;
			}
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

		RectF CIconButton::getOuterBorderWidth(const State state) const
		{
			return m_aOuterBorderWidth[(int)state];
		}

		RectF CIconButton::getInnerBorderWidth(const State state) const
		{
			return m_aInnerBorderWidth[(int)state];
		}

		RectF CIconButton::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CIconButton::getOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state];
		}

		BorderColor CIconButton::getInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state];
		}

		Color CIconButton::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CIconButton::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CIconButton::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CIconButton::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CIconButton::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		RectF CIconButton::getPadding(const State state) const
		{
			return m_aPadding[(int)state];
		}

		IImageList *CIconButton::getImageList(const State state) const
		{
			return m_aImageList[(int)state];
		}

		int CIconButton::getIconIndex(const State state) const
		{
			return m_aIconIndex[(int)state];
		}

		unsigned int CIconButton::getOutlineMask(const State state) const
		{
			return m_aOutlineMask[(int)state];
		}

		Color CIconButton::getOutlineColor(const State state) const
		{
			return m_aOutlineColor[(int)state];
		}

		CIconButton::IconSize CIconButton::getIconSize() const
		{
			return m_eIconSize;
		}

		bool CIconButton::isOutlineInEditor() const
		{
			return m_bOutlineInEditor;
		}
	#pragma endregion

	#pragma region Setters
		bool CIconButton::setOuterBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aOuterBorderWidth[(int)state]))
			{
				m_aOuterBorderWidth[(int)state] = value;
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

		bool CIconButton::setInnerBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aInnerBorderWidth[(int)state]))
			{
				m_aInnerBorderWidth[(int)state] = value;
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

		bool CIconButton::setBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderRadius[(int)state]))
			{
				m_aBorderRadius[(int)state] = value;
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

		bool CIconButton::setOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aOuterBorderColor[(int)state])
			{
				m_aOuterBorderColor[(int)state] = value;
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

		bool CIconButton::setInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aInnerBorderColor[(int)state])
			{
				m_aInnerBorderColor[(int)state] = value;
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

		bool CIconButton::setBackgroundColor(const State state, const Color &value)
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

		bool CIconButton::setShadowColor(const State state, const Color &value)
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

		bool CIconButton::setShadowShift(const State state, const PointF &value)
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

		bool CIconButton::setShadowRadius(const State state, const int value)
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

		bool CIconButton::setPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aPadding[(int)state]))
			{
				m_aPadding[(int)state] = value;
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

		bool CIconButton::setImageList(const State state, IImageList *value)
		{
			if (value != m_aImageList[(int)state])
			{
				m_aImageList[(int)state] = value;
				if (getState() == state && m_aIconIndex[(int)state] >= 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CIconButton::setIconIndex(const State state, const int value)
		{
			if (value != m_aIconIndex[(int)state])
			{
				m_aIconIndex[(int)state] = value;
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

		bool CIconButton::setOutlineMask(const State state, const unsigned int value)
		{
			if (m_aOutlineMask[(int)state] != value)
			{
				m_aOutlineMask[(int)state] = value;
				if (m_aOutlineColor[(int)state].A > 0 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CIconButton::setOutlineColor(const State state, const Color &value)
		{
			if (value != m_aOutlineColor[(int)state])
			{
				m_aOutlineColor[(int)state] = value;
				if (m_aOutlineMask[(int)state] != 0 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CIconButton::setIconSize(const IconSize value)
		{
			if (value != m_eIconSize)
			{
				m_eIconSize = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CIconButton::setOutlineInEditor(const bool value)
		{
			if (value != m_bOutlineInEditor)
			{
				m_bOutlineInEditor = value;
				if (Application->Editor)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CIconButton::setOuterBorderWidth(const RectF &value)
		{
			bool result{ false };
			if (!value.has_negative())
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (IsNotEqual(value, m_aOuterBorderWidth[i]))
					{
						m_aOuterBorderWidth[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setInnerBorderWidth(const RectF &value)
		{
			bool result{ false };
			if (!value.has_negative())
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (IsNotEqual(value, m_aInnerBorderWidth[i]))
					{
						m_aInnerBorderWidth[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setBorderRadius(const RectF &value)
		{
			bool result{ false };
			if (!value.has_negative())
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (IsNotEqual(value, m_aBorderRadius[i]))
					{
						m_aBorderRadius[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setOuterBorderColor(const BorderColor &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aOuterBorderColor[i])
				{
					m_aOuterBorderColor[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setInnerBorderColor(const BorderColor &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aInnerBorderColor[i])
				{
					m_aInnerBorderColor[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setBackgroundColor(const Color &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aBackgroundColor[i])
				{
					m_aBackgroundColor[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setShadowColor(const Color &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aShadowColor[i])
				{
					m_aShadowColor[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setShadowShift(const PointF &value)
		{
			CLockRepaint lock{ this };
			Repaint(false);
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (IsNotEqual(value, m_aShadowShift[i]))
				{
					m_aShadowShift[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setShadowRadius(const int value)
		{
			CLockRepaint lock{ this };
			Repaint(false);
			bool result{ false };
			if (value >= 1)
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (value != m_aShadowRadius[i])
					{
						m_aShadowRadius[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setPadding(const RectF &value)
		{
			bool result{ false };
			if (!value.has_negative())
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (IsNotEqual(value, m_aPadding[i]))
					{
						m_aPadding[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setImageList(IImageList *value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aImageList[i])
				{
					m_aImageList[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CIconButton::setIconIndex(const int value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aIconIndex[i])
				{
					m_aIconIndex[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}
	#pragma endregion

	#pragma region Helpers
		void CIconButton::UpdateFromStyle(IStyle *style)
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
				case State::Active:
					state = L"Active";
					break;
				case State::ActiveHovered:
					state = L"ActiveHovered";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".OuterBorderWidth[" + state + L"]", m_aOuterBorderWidth[i]);
				style->getOption(m_sClassName + L".InnerBorderWidth[" + state + L"]", m_aInnerBorderWidth[i]);
				style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]);
				style->getOption(m_sClassName + L".OuterBorderColor[" + state + L"]", m_aOuterBorderColor[i]);
				style->getOption(m_sClassName + L".InnerBorderColor[" + state + L"]", m_aInnerBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".Padding[" + state + L"]", m_aPadding[i]);
				style->getOption(m_sClassName + L".OutlineColor[" + state + L"]", m_aOutlineColor[i]);
			}
			m_bIgnoreGradient = false;
		}

		RectF CIconButton::getRenderRect(const State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}
	#pragma endregion

	#pragma region Render
		void CIconButton::Render()
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

				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };

				if (m_bOutlineInEditor && Application->Editor)
				{
					CStoreBitmask s_bitmask{ renderer };
					renderer
						->ActivateBitmask(Bitmask{ OutlineMask, 0, true, false })
						->DrawLines({
							PointF{ rect.Left, rect.Top },
							PointF{ rect.Right, rect.Top },
							PointF{ rect.Right, rect.Bottom - 1 },
							PointF{ rect.Left + 1, rect.Bottom - 1 },
							PointF{ rect.Left + 1, rect.Top } },
							Color{ 0, 0, 0, 255 },
							false);
				}
				DrawBlockShadow(
					renderer,
					rect,
					m_aBorderRadius[(int)state],
					m_aShadowColor[(int)state],
					m_aShadowShift[(int)state],
					m_aShadowRadius[(int)state]);
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
				RenderOutline(renderer, rect, state);
				RenderContent(state, renderer, rect);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CIconButton::RenderOutline(IRenderer *renderer, const RectF &rect, const State state)
		{
			if (m_aOutlineMask[(int)state] != 0 && m_aOutlineColor[(int)state].A > 0)
			{
				RectF r{ rect };
				r.Left += ntl::Max<float>(m_aBorderRadius[(int)state].Bottom, m_aBorderRadius[(int)state].Left, m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left);
				r.Top += ntl::Max<float>(m_aBorderRadius[(int)state].Left, m_aBorderRadius[(int)state].Top, m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top);
				r.Right -= ntl::Max<float>(m_aBorderRadius[(int)state].Top, m_aBorderRadius[(int)state].Right, m_aOuterBorderWidth[(int)state].Right + m_aInnerBorderWidth[(int)state].Right);
				r.Bottom -= ntl::Max<float>(m_aBorderRadius[(int)state].Right, m_aBorderRadius[(int)state].Bottom, m_aOuterBorderWidth[(int)state].Bottom + m_aInnerBorderWidth[(int)state].Bottom);
				if (r.is_valid() && !r.is_zero())
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

		void CIconButton::RenderContent(const State state, IRenderer *renderer, const RectF &rect)
		{
			ITexture *icon{ (m_aImageList[(int)state] && m_aIconIndex[(int)state] >= 0) ? m_aImageList[(int)state]->getTexture(m_aIconIndex[(int)state]) : nullptr };
			if (icon)
			{
				RectF client{ rect };
				client.Left += m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left + m_aPadding[(int)state].Left;
				client.Top += m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top + m_aPadding[(int)state].Top;
				client.Right -= m_aOuterBorderWidth[(int)state].Right + m_aInnerBorderWidth[(int)state].Right + m_aPadding[(int)state].Right;
				client.Bottom -= m_aOuterBorderWidth[(int)state].Bottom + m_aInnerBorderWidth[(int)state].Bottom + m_aPadding[(int)state].Bottom;
				client.validate();
				if (!client.is_zero())
				{
					switch (m_eIconSize)
					{
					case IconSize::Contain:
						RenderContain(renderer, state, client, icon);
						break;
					case IconSize::Cover:
						RenderCover(renderer, state, client, rect, icon);
						break;
					case IconSize::Stretch:
						RenderStretch(renderer, state, client, icon);
						break;
					default:
						RenderOriginal(renderer, state, rect, client, icon);
					}
				}
			}
		}

		void CIconButton::RenderOriginal(IRenderer *renderer, const State state, const RectF &rect, const RectF &client, ITexture *icon)
		{
			RectF borders{ AddElements(m_aOuterBorderWidth[(int)state], m_aInnerBorderWidth[(int)state], m_aPadding[(int)state]) };
			Block b{ rect, borders, m_aBorderRadius[(int)state], PointLocation::Inside };
			PointF pos{ std::round((client.Left + client.Right - icon->Widthf) * 0.5f), std::round((client.Top + client.Bottom - icon->Heightf) * 0.5f) };
			CStoreBlock s_block{ renderer };
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivateBlock(&b)
				->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(pos.X, pos.Y, 0))
				->DrawImage(icon, 1);
		}

		void CIconButton::RenderContain(IRenderer *renderer, const State state, const RectF &client, ITexture *icon)
		{
			float client_size{ ntl::Min<float>(client.width(), client.height()) }, icon_size{ ntl::Max<float>(icon->Widthf, icon->Heightf) }, scale{ client_size / icon_size };
			PointF pos{ std::round((client.Left + client.Right - client_size) * 0.5f), std::round((client.Top + client.Bottom - client_size) * 0.5f) };
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(pos.X, pos.Y, 0) * ntl::Mat4Scale<float>(scale, scale, 1))
				->DrawImage(icon, 1);
		}

		void CIconButton::RenderCover(IRenderer *renderer, const State state, const RectF &rect, const RectF &client, ITexture *icon)
		{
			float client_size{ ntl::Max<float>(client.width(), client.height()) }, icon_size{ ntl::Min<float>(icon->Widthf, icon->Heightf) }, scale{ client_size / icon_size };
			PointF pos{ std::round((client.Left + client.Right - client_size) * 0.5f), std::round((client.Top + client.Bottom - client_size) * 0.5f) };
			RectF borders{ AddElements(m_aOuterBorderWidth[(int)state], m_aInnerBorderWidth[(int)state], m_aPadding[(int)state]) };
			Block b{ rect, borders, m_aBorderRadius[(int)state], PointLocation::Inside };
			CStoreBlock s_block{ renderer };
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivateBlock(&b)
				->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(pos.X, pos.Y, 0) * ntl::Mat4Scale<float>(scale, scale, 1))
				->DrawImage(icon, 1);
		}

		void CIconButton::RenderStretch(IRenderer *renderer, const State state, const RectF &client, ITexture *icon)
		{
			PointF scale{ client.width() / icon->Widthf, client.height() / icon->Heightf };
			PointF pos{ std::round(client.Left), std::round(client.Top) };
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(pos.X, pos.Y, 0) * ntl::Mat4Scale<float>(scale.X, scale.Y, 1))
				->DrawImage(icon, 1);
		}
	#pragma endregion
	}
}