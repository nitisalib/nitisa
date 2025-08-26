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
		CListItemColor::CGradientListener::CGradientListener(CListItemColor *control) :
			m_pControl{ control }
		{

		}

		void CListItemColor::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient && m_pControl->QueryService()->getOwner())
				m_pControl->QueryService()->getOwner()->NotifyOnRepaintRequired(m_pControl);
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CListItemColor::CListItemColor() :
			CListItem(L"ListItemColor", false),
			m_cGradientListener{ this },
			m_pService{ nullptr },
			m_sColor{ 0, 0, 0, 0 },
			m_eAlign{ TextAlign::Left },
			m_sPadding{ 4, 2, 4, 2 },
			m_bTextAtRight{ true },
			m_aColorBorderWidth{
				RectF{ 0, 0, 0, 0 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 0, 0, 0, 0 } },
			m_aColorBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aColorPadding{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aCaptionColor{
				Color{ 0, 0, 0, 0 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 109, 109, 109, 255 } },
			m_aCaptionShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aCaptionShadowRadius{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			m_aCaptionShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 255, 200 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 0, 0 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aBorderWidth{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
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
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aColorBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_bIgnoreGradient{ false },
			OnClick{ nullptr }
		{
			
		}

		CListItemColor::CListItemColor(const Color &color, const String &caption) : CListItemColor()
		{
			m_sCaption = caption;
			m_sColor = color;
			m_aColorBorderColor[(int)State::Normal] = m_aColorBorderColor[(int)State::Selected] = m_aColorBorderColor[(int)State::SelectedHovered] = m_aColorBorderColor[(int)State::ActiveSelected] =
				m_aColorBorderColor[(int)State::ActiveSelectedHovered] = m_aColorBorderColor[(int)State::Disabled] = BorderColor{ color, color, color, color };
		}

		CListItemColor::~CListItemColor()
		{
			if (m_pService)
				m_pService->Release();
		}
	#pragma endregion

	#pragma region Getters
		IListItemService *CListItemColor::QueryService()
		{
			if (!m_pService)
				m_pService = new CListItemColorService(this);
			return m_pService;
		}

		CListItemColor::State CListItemColor::getState()
		{
			if (!isEnabled())
				return State::Disabled;
			if (isActive())
			{
				if (isSelected())
				{
					if (isHovered())
						return State::ActiveSelectedHovered;
					return State::ActiveSelected;
				}
				if (isHovered())
					return State::ActiveHovered;
				return State::Active;
			}
			if (isSelected())
			{
				if (isHovered())
					return State::SelectedHovered;
				return State::Selected;
			}
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		String CListItemColor::getCaption()
		{
			return m_sCaption;
		}

		Color CListItemColor::getColor()
		{
			return m_sColor;
		}

		TextAlign CListItemColor::getAlign()
		{
			return m_eAlign;
		}

		RectF CListItemColor::getPadding() const
		{
			return m_sPadding;
		}

		Color CListItemColor::getCaptionColor(const State state) const
		{
			return m_aCaptionColor[(int)state];
		}

		Color CListItemColor::getCaptionShadowColor(const State state) const
		{
			return m_aCaptionShadowColor[(int)state];
		}

		int CListItemColor::getCaptionShadowRadius(const State state) const
		{
			return m_aCaptionShadowRadius[(int)state];
		}

		PointF CListItemColor::getCaptionShadowShift(const State state) const
		{
			return m_aCaptionShadowShift[(int)state];
		}

		Color CListItemColor::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CListItemColor::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		RectF CListItemColor::getBorderWidth(const State state) const
		{
			return m_aBorderWidth[(int)state];
		}

		RectF CListItemColor::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CListItemColor::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CListItemColor::getLeftBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CListItemColor::getTopBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CListItemColor::getRightBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CListItemColor::getBottomBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		bool CListItemColor::isTextAtRight() const
		{
			return m_bTextAtRight;
		}

		RectF CListItemColor::getColorBorderWidth(const State state) const
		{
			return m_aColorBorderWidth[(int)state];
		}

		RectF CListItemColor::getColorBorderRadius(const State state) const
		{
			return m_aColorBorderRadius[(int)state];
		}

		RectF CListItemColor::getColorPadding(const State state) const
		{
			return m_aColorPadding[(int)state];
		}

		BorderColor CListItemColor::getColorBorderColor(const State state) const
		{
			return m_aColorBorderColor[(int)state];
		}

		Color CListItemColor::getColorLeftBorderColor(const State state) const
		{
			return m_aColorBorderColor[(int)state].Left;
		}

		Color CListItemColor::getColorTopBorderColor(const State state) const
		{
			return m_aColorBorderColor[(int)state].Top;
		}

		Color CListItemColor::getColorRightBorderColor(const State state) const
		{
			return m_aColorBorderColor[(int)state].Right;
		}

		Color CListItemColor::getColorBottomBorderColor(const State state) const
		{
			return m_aColorBorderColor[(int)state].Bottom;
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemColor::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setColor(const Color &value)
		{
			if (value != m_sColor)
			{
				m_sColor = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setAlign(const TextAlign value)
		{
			if (value != m_eAlign)
			{
				m_eAlign = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setCaptionColor(const State state, const Color &value)
		{
			if (value != m_aCaptionColor[(int)state])
			{
				m_aCaptionColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setCaptionShadowColor(const State state, const Color &value)
		{
			if (value != m_aCaptionShadowColor[(int)state])
			{
				m_aCaptionShadowColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setCaptionShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aCaptionShadowRadius[(int)state])
			{
				m_aCaptionShadowRadius[(int)state] = value;
				if (isVisible() && getState() == state && m_aCaptionShadowColor[(int)state].A > 0 && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setCaptionShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aCaptionShadowShift[(int)state]))
			{
				m_aCaptionShadowShift[(int)state] = value;
				if (isVisible() && getState() == state && m_aCaptionShadowColor[(int)state].A > 0 && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderWidth[(int)state]))
			{
				m_aBorderWidth[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderRadius[(int)state]))
			{
				m_aBorderRadius[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setLeftBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemColor::setTopBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemColor::setRightBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemColor::setBottomBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CListItemColor::setTextAtRight(const bool value)
		{
			if (value != m_bTextAtRight)
			{
				m_bTextAtRight = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setColorBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aColorBorderWidth[(int)state]))
			{
				m_aColorBorderWidth[(int)state] = value;
				if (isVisible() && QueryService()->getOwner() && getState() == state)
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setColorBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aColorBorderRadius[(int)state]))
			{
				m_aColorBorderRadius[(int)state] = value;
				if (isVisible() && QueryService()->getOwner() && getState() == state)
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setColorPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aColorPadding[(int)state]))
			{
				m_aColorPadding[(int)state] = value;
				if (isVisible() && QueryService()->getOwner() && getState() == state)
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setColorBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aColorBorderColor[(int)state])
			{
				m_aColorBorderColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemColor::setColorLeftBorderColor(const State state, const Color &value)
		{
			return setColorBorderColor(state, BorderColor{ value, m_aColorBorderColor[(int)state].Top, m_aColorBorderColor[(int)state].Right, m_aColorBorderColor[(int)state].Bottom });
		}

		bool CListItemColor::setColorTopBorderColor(const State state, const Color &value)
		{
			return setColorBorderColor(state, BorderColor{ m_aColorBorderColor[(int)state].Left, value, m_aColorBorderColor[(int)state].Right, m_aColorBorderColor[(int)state].Bottom });
		}

		bool CListItemColor::setColorRightBorderColor(const State state, const Color &value)
		{
			return setColorBorderColor(state, BorderColor{ m_aColorBorderColor[(int)state].Left, m_aColorBorderColor[(int)state].Top, value, m_aColorBorderColor[(int)state].Bottom });
		}

		bool CListItemColor::setColorBottomBorderColor(const State state, const Color &value)
		{
			return setColorBorderColor(state, BorderColor{ m_aColorBorderColor[(int)state].Left, m_aColorBorderColor[(int)state].Top, m_aColorBorderColor[(int)state].Right, value });
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemColor::UpdateFromStyle(IStyle *style)
		{
			bool changed{ false };
			m_bIgnoreGradient = true;
			changed = style->getOption(m_sClassName + L".Padding", m_sPadding) || changed;
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Hovered:
					state = L"Hovered";
					break;
				case State::Selected:
					state = L"Selected";
					break;
				case State::SelectedHovered:
					state = L"SelectedHovered";
					break;
				case State::Active:
					state = L"Active";
					break;
				case State::ActiveHovered:
					state = L"ActiveHovered";
					break;
				case State::ActiveSelected:
					state = L"ActiveSelected";
					break;
				case State::ActiveSelectedHovered:
					state = L"ActiveSelectedHovered";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				changed = style->getOption(m_sClassName + L".CaptionColor[" + state + L"]", m_aCaptionColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".CaptionShadowColor[" + state + L"]", m_aCaptionShadowColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".CaptionShadowRadius[" + state + L"]", m_aCaptionShadowRadius[i]) || changed;
				changed = style->getOption(m_sClassName + L".CaptionShadowShift[" + state + L"]", m_aCaptionShadowShift[i]) || changed;
				changed = style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderWidth[" + state + L"]", m_aBorderWidth[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".ColorBorderWidth[" + state + L"]", m_aColorBorderWidth[i]) || changed;
				changed = style->getOption(m_sClassName + L".ColorBorderRadius[" + state + L"]", m_aColorBorderRadius[i]) || changed;
			}
			m_bIgnoreGradient = false;
			if (changed && QueryService()->getOwner())
				QueryService()->getOwner()->NotifyOnSizeChange(this);
		}

		PointF CListItemColor::CalculateTextPosition()
		{
			IListItemOwner *owner{ QueryService()->getOwner() };
			if (owner && owner->getRenderer() && owner->getFont(this) && owner->getFont(this)->getPlatformFont(owner->getRenderer()))
			{
				IPlatformFont *pf{ owner->getFont(this)->getPlatformFont(owner->getRenderer()) };
				String caption{ Application->Translate->t(TranslateCategoryColors, m_sCaption) };
				PointF size{ pf->getStringSize(caption, owner->getFont(this)->Distance) };
				if (caption.empty())
					size.Y = pf->getStringSize(L"Wy", 0).Y;
				if (m_bTextAtRight)
					return PointF{ getSize().Y + m_sPadding.Left, std::round((getSize().Y + m_sPadding.Top - m_sPadding.Bottom - size.Y) * 0.5f) };
				return PointF{ getSize().X - getSize().Y - m_sPadding.Right - size.X, std::round((getSize().Y + m_sPadding.Top - m_sPadding.Bottom - size.Y) * 0.5f) };
			}
			return PointF{ 0, 0 };
		}

		IListItem *CListItemColor::Clone()
		{
			CListItemColor *result{ new CListItemColor(m_sColor, m_sCaption) };
			Copy(result);
			return result;
		}

		bool CListItemColor::Copy(IListItem *dest)
		{
			CListItemColor *d{ cast<CListItemColor*>(dest) };
			if (d)
			{
				d->m_eAlign = m_eAlign;
				d->m_sPadding = m_sPadding;
				d->m_bTextAtRight = m_bTextAtRight;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					d->m_aColorBorderWidth[i] = m_aColorBorderWidth[i];
					d->m_aColorBorderRadius[i] = m_aColorBorderRadius[i];
					d->m_aColorPadding[i] = m_aColorPadding[i];
					d->m_aCaptionColor[i] = m_aCaptionColor[i];
					d->m_aCaptionShadowColor[i] = m_aCaptionShadowColor[i];
					d->m_aCaptionShadowRadius[i] = m_aCaptionShadowRadius[i];
					d->m_aCaptionShadowShift[i] = m_aCaptionShadowShift[i];
					d->m_aBackgroundColor[i] = m_aBackgroundColor[i];
					d->m_aBackgroundGradient[i] = m_aBackgroundGradient[i];
					d->m_aBorderWidth[i] = m_aBorderWidth[i];
					d->m_aBorderRadius[i] = m_aBorderRadius[i];
					d->m_aBorderColor[i] = m_aBorderColor[i];
					d->m_aColorBorderColor[i] = m_aColorBorderColor[i];
				}
				return CListItem::Copy(dest);
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CListItemColor::Render(const Mat4f &matrix, const Block *block, ITexture **clip)
		{
			IRenderer *renderer{ QueryService()->getOwner()->getRenderer() };
			IFont *font{ QueryService()->getOwner()->getFont(this) };
			IPlatformFont *pf{ font->getPlatformFont(renderer) };
			ITexture *clip_internal;
			if (clip)
			{
				if (*clip)
					(*clip)->setSize(ntl::Round<int>(getSize().X), ntl::Round<int>(getSize().Y));
				else
					*clip = renderer->CreateTexture(ntl::Round<int>(getSize().X), ntl::Round<int>(getSize().Y), 1, TextureFormat::RGBA, true);
				clip_internal = *clip;
			}
			else
				clip_internal = renderer->CreateTexture(ntl::Round<int>(getSize().X), ntl::Round<int>(getSize().Y), 1, TextureFormat::RGBA, true);
			if (clip_internal)
			{
				State state{ getState() };
				RectF rect_clip{ clip_internal->Rectf };
				Color text_color{ m_aCaptionColor[(int)state].A > 0 ? m_aCaptionColor[(int)state] : font->Color };
				Color shadow_color{ m_aCaptionShadowColor[(int)state] };
				int shadow_radius{ m_aCaptionShadowRadius[(int)state] };
				PointF shadow_shift{ m_aCaptionShadowShift[(int)state] };
				PointF text_position{ CalculateTextPosition() };
				IBaseTexture *old{ renderer->ActiveTarget };
				renderer
					->ActivateTarget(clip_internal)
					->Clear(Color{ 0, 0, 0, 0 });
				DrawSimpleBackground(
					renderer,
					rect_clip,
					m_aBorderWidth[(int)state],
					m_aBorderRadius[(int)state],
					m_aBorderColor[(int)state],
					m_aBackgroundColor[(int)state],
					m_aBackgroundGradient[(int)state]);
				RenderParts(state, rect_clip, renderer, font, pf, text_position, text_color, shadow_color, shadow_radius, shadow_shift);
				CStoreBlock s_block{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateTarget(old)
					->ActivateBlock(block)
					->ActivatePrimitiveMatrix(matrix)
					->DrawImage(clip_internal, 1);
				if (!clip)
					clip_internal->Release();
			}
		}

		void CListItemColor::RenderParts(const State state, const RectF &rect_clip, IRenderer *renderer, IFont *font, IPlatformFont *pf,
			const PointF &text_position, const Color &text_color, const Color &shadow_color, const int shadow_radius, const PointF &shadow_shift)
		{
			String caption{ Application->Translate->t(TranslateCategoryColors, m_sCaption) };
			DrawTextShadow(renderer, pf, font->Distance, Identity, rect_clip, text_position, caption, shadow_color, shadow_shift, shadow_radius);
			// Render color box
			RectF color_rect{ m_aColorPadding[(int)state].Left, m_aColorPadding[(int)state].Top, getSize().Y - m_aColorPadding[(int)state].Right, getSize().Y - m_aColorPadding[(int)state].Bottom };
			if (color_rect.is_valid() && !color_rect.is_zero())
			{
				if (m_aColorBorderWidth[(int)state].has_positive() || m_aColorBorderRadius[(int)state].has_positive())
				{
					BlockColors colors{
						m_aColorBorderColor[(int)state].Left,
						m_aColorBorderColor[(int)state].Top,
						m_aColorBorderColor[(int)state].Right,
						m_aColorBorderColor[(int)state].Bottom,
						m_sColor,
						Color{ 0, 0, 0, 0 }
					};
					renderer->DrawBlock(color_rect, m_aColorBorderWidth[(int)state], m_aColorBorderRadius[(int)state], colors);
				}
				else
					renderer->DrawRectangle(color_rect, m_sColor);
			}
			// Render caption
			if (!caption.empty())
			{
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(text_position.X, text_position.Y, 0))
					->DrawText(caption, pf, font->Distance, text_color);
			}
		}
	#pragma endregion
	}
}