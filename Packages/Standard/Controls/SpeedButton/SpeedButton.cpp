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
		CSpeedButton::CGradientListener::CGradientListener(CSpeedButton *control) :
			m_pControl{ control }
		{

		}

		void CSpeedButton::CGradientListener::NotifyOnChange()
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
		CSpeedButton::CSpeedButton() :
			CControl(L"SpeedButton", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_iGroupIndex{ 0 },
			m_bDown{ false },
			m_aPadding{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aOuterBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aInnerBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aBorderRadius{
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 } },
			m_aOuterBorderColor{
				BorderColor{ Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 173, 178, 181, 255 }, Color{ 173, 178, 181, 255 }, Color{ 173, 178, 181, 255 }, Color{ 173, 178, 181, 255 } } },
			m_aInnerBorderColor{
				BorderColor{ Color{ 243, 243, 243, 255 }, Color{ 243, 243, 243, 255 }, Color{ 243, 243, 243, 255 }, Color{ 243, 243, 243, 255 } },
				BorderColor{ Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 59, 214, 253, 255 }, Color{ 59, 214, 253, 255 }, Color{ 59, 214, 253, 255 }, Color{ 59, 214, 253, 255 } },
				BorderColor{ Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 } } },
			m_aBackgroundColor{
				Color{ 246, 246, 246, 255 },
				Color{ 238, 248, 254, 255 },
				Color{ 158, 187, 204, 255 },
				Color{ 158, 187, 204, 255 },
				Color{ 246, 246, 246, 255 },
				Color{ 238, 248, 254, 255 },
				Color{ 158, 187, 204, 255 },
				Color{ 158, 187, 204, 255 },
				Color{ 252, 252, 252, 255 } },
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
			m_aImageList{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
			m_aIconIndex{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
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
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowRadius{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			m_pCanvas{ nullptr },
			m_bIgnoreGradient{ true },
			OnDown{ nullptr },
			OnUp{ nullptr }
		{
			OnDown = nullptr;
			OnUp = nullptr;
			setService(new CSpeedButtonService(this), true);
			setSize(PointF{ 32, 32 });

			m_aBackgroundGradient[(int)State::Normal].setPointCount(4);
			m_aBackgroundGradient[(int)State::Normal].setPoint(0, 0.000f, Color{ 242, 242, 242, 255 });
			m_aBackgroundGradient[(int)State::Normal].setPoint(1, 0.499f, Color{ 235, 235, 235, 255 });
			m_aBackgroundGradient[(int)State::Normal].setPoint(2, 0.500f, Color{ 221, 221, 221, 255 });
			m_aBackgroundGradient[(int)State::Normal].setPoint(3, 1.000f, Color{ 207, 207, 207, 255 });

			m_aBackgroundGradient[(int)State::Hovered].setPointCount(4);
			m_aBackgroundGradient[(int)State::Hovered].setPoint(0, 0.000f, Color{ 234, 246, 253, 255 });
			m_aBackgroundGradient[(int)State::Hovered].setPoint(1, 0.499f, Color{ 217, 240, 252, 255 });
			m_aBackgroundGradient[(int)State::Hovered].setPoint(2, 0.500f, Color{ 190, 230, 253, 255 });
			m_aBackgroundGradient[(int)State::Hovered].setPoint(3, 1.000f, Color{ 167, 217, 245, 255 });

			m_aBackgroundGradient[(int)State::Down].setPointCount(4);
			m_aBackgroundGradient[(int)State::Down].setPoint(0, 0.000f, Color{ 229, 244, 252, 255 });
			m_aBackgroundGradient[(int)State::Down].setPoint(1, 0.499f, Color{ 196, 229, 246, 255 });
			m_aBackgroundGradient[(int)State::Down].setPoint(2, 0.500f, Color{ 152, 209, 239, 255 });
			m_aBackgroundGradient[(int)State::Down].setPoint(3, 1.000f, Color{ 109, 182, 221, 255 });

			m_aBackgroundGradient[(int)State::DownHovered].setPointCount(4);
			m_aBackgroundGradient[(int)State::DownHovered].setPoint(0, 0.000f, Color{ 229, 244, 252, 255 });
			m_aBackgroundGradient[(int)State::DownHovered].setPoint(1, 0.499f, Color{ 196, 229, 246, 255 });
			m_aBackgroundGradient[(int)State::DownHovered].setPoint(2, 0.500f, Color{ 152, 209, 239, 255 });
			m_aBackgroundGradient[(int)State::DownHovered].setPoint(3, 1.000f, Color{ 109, 182, 221, 255 });

			m_aBackgroundGradient[(int)State::Focused].setPointCount(4);
			m_aBackgroundGradient[(int)State::Focused].setPoint(0, 0.000f, Color{ 238, 244, 247, 255 });
			m_aBackgroundGradient[(int)State::Focused].setPoint(1, 0.499f, Color{ 232, 239, 244, 255 });
			m_aBackgroundGradient[(int)State::Focused].setPoint(2, 0.500f, Color{ 211, 227, 236, 255 });
			m_aBackgroundGradient[(int)State::Focused].setPoint(3, 1.000f, Color{ 195, 216, 228, 255 });

			m_aBackgroundGradient[(int)State::FocusedHovered].setPointCount(4);
			m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(0, 0.000f, Color{ 234, 246, 253, 255 });
			m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(1, 0.499f, Color{ 217, 240, 252, 255 });
			m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(2, 0.500f, Color{ 190, 230, 253, 255 });
			m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(3, 1.000f, Color{ 167, 217, 245, 255 });

			m_aBackgroundGradient[(int)State::FocusedDown].setPointCount(4);
			m_aBackgroundGradient[(int)State::FocusedDown].setPoint(0, 0.000f, Color{ 229, 244, 252, 255 });
			m_aBackgroundGradient[(int)State::FocusedDown].setPoint(1, 0.499f, Color{ 196, 229, 246, 255 });
			m_aBackgroundGradient[(int)State::FocusedDown].setPoint(2, 0.500f, Color{ 152, 209, 239, 255 });
			m_aBackgroundGradient[(int)State::FocusedDown].setPoint(3, 1.000f, Color{ 109, 182, 221, 255 });

			m_aBackgroundGradient[(int)State::FocusedDownHovered].setPointCount(4);
			m_aBackgroundGradient[(int)State::FocusedDownHovered].setPoint(0, 0.000f, Color{ 229, 244, 252, 255 });
			m_aBackgroundGradient[(int)State::FocusedDownHovered].setPoint(1, 0.499f, Color{ 196, 229, 246, 255 });
			m_aBackgroundGradient[(int)State::FocusedDownHovered].setPoint(2, 0.500f, Color{ 152, 209, 239, 255 });
			m_aBackgroundGradient[(int)State::FocusedDownHovered].setPoint(3, 1.000f, Color{ 109, 182, 221, 255 });

			m_bIgnoreGradient = false;
		}

		CSpeedButton::CSpeedButton(IForm *parent) :CSpeedButton()
		{
			setForm(parent);
		}

		CSpeedButton::CSpeedButton(IControl *parent) : CSpeedButton()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		RectF CSpeedButton::getRenderRect()
		{
			RectF result{ getRect() };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = AddShadow(result, m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
			return result;
		}

		bool CSpeedButton::isFocusByMouse()
		{
			return false;
		}

		int CSpeedButton::getGroupIndex()
		{
			return m_iGroupIndex;
		}

		bool CSpeedButton::isDown()
		{
			return m_bDown;
		}
	#pragma endregion

	#pragma region Getters
		CSpeedButton::State CSpeedButton::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isFocused())
			{
				if (m_bDown)
				{
					if (isHovered())
						return State::FocusedDownHovered;
					return State::FocusedDown;
				}
				if (isHovered())
					return State::FocusedHovered;
				return State::Focused;
			}
			if (m_bDown)
			{
				if (isHovered())
					return State::DownHovered;
				return State::Down;
			}
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		RectF CSpeedButton::getPadding(const State state) const
		{
			return m_aPadding[(int)state];
		}

		RectF CSpeedButton::getOuterBorderWidth(const State state) const
		{
			return m_aOuterBorderWidth[(int)state];
		}

		RectF CSpeedButton::getInnerBorderWidth(const State state) const
		{
			return m_aInnerBorderWidth[(int)state];
		}

		RectF CSpeedButton::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CSpeedButton::getOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state];
		}

		Color CSpeedButton::getLeftOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Left;
		}

		Color CSpeedButton::getTopOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Top;
		}

		Color CSpeedButton::getRightOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Right;
		}

		Color CSpeedButton::getBottomOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Bottom;
		}

		BorderColor CSpeedButton::getInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state];
		}

		Color CSpeedButton::getLeftInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Left;
		}

		Color CSpeedButton::getTopInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Top;
		}

		Color CSpeedButton::getRightInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Right;
		}

		Color CSpeedButton::getBottomInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Bottom;
		}

		Color CSpeedButton::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CSpeedButton::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		IImageList *CSpeedButton::getImageList(const State state)
		{
			return m_aImageList[(int)state];
		}

		int CSpeedButton::getIconIndex(const State state) const
		{
			return m_aIconIndex[(int)state];
		}

		Color CSpeedButton::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CSpeedButton::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CSpeedButton::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSpeedButton::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aPadding[i] *= s;
					m_aOuterBorderWidth[i] *= s;
					m_aInnerBorderWidth[i] *= s;
					m_aBorderRadius[i] *= avg;
					m_aShadowShift[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSpeedButton::setGroupIndex(const int value)
		{
			if (value < 0 && m_iGroupIndex < 0)
				return false;
			if (value != m_iGroupIndex)
			{
				m_iGroupIndex = value < 0 ? -1 : value;
				if (m_bDown && m_iGroupIndex >= 0 && DownExists())
				{
					m_bDown = false;
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setDown(const bool value)
		{
			if (value != m_bDown)
			{
				CLockRepaint lock{ this };
				m_bDown = value;
				if (m_bDown && m_iGroupIndex >= 0)
					ReleaseDown();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CSpeedButton::setPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aPadding[(int)state]))
			{
				m_aPadding[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setOuterBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aOuterBorderWidth[(int)state]))
			{
				m_aOuterBorderWidth[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setInnerBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aInnerBorderWidth[(int)state]))
			{
				m_aInnerBorderWidth[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderRadius[(int)state]))
			{
				m_aBorderRadius[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aOuterBorderColor[(int)state])
			{
				m_aOuterBorderColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setLeftOuterBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ value, m_aOuterBorderColor[(int)state].Top, m_aOuterBorderColor[(int)state].Right, m_aOuterBorderColor[(int)state].Bottom });
		}

		bool CSpeedButton::setTopOuterBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ m_aOuterBorderColor[(int)state].Left, value, m_aOuterBorderColor[(int)state].Right, m_aOuterBorderColor[(int)state].Bottom });
		}

		bool CSpeedButton::setRightOuterBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ m_aOuterBorderColor[(int)state].Left, m_aOuterBorderColor[(int)state].Top, value, m_aOuterBorderColor[(int)state].Bottom });
		}

		bool CSpeedButton::setBottomOuterBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ m_aOuterBorderColor[(int)state].Left, m_aOuterBorderColor[(int)state].Top, m_aOuterBorderColor[(int)state].Right, value });
		}

		bool CSpeedButton::setInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aInnerBorderColor[(int)state])
			{
				m_aInnerBorderColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setLeftInnerBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ value, m_aInnerBorderColor[(int)state].Top, m_aInnerBorderColor[(int)state].Right, m_aInnerBorderColor[(int)state].Bottom });
		}

		bool CSpeedButton::setTopInnerBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ m_aInnerBorderColor[(int)state].Left, value, m_aInnerBorderColor[(int)state].Right, m_aInnerBorderColor[(int)state].Bottom });
		}

		bool CSpeedButton::setRightInnerBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ m_aInnerBorderColor[(int)state].Left, m_aInnerBorderColor[(int)state].Top, value, m_aInnerBorderColor[(int)state].Bottom });
		}

		bool CSpeedButton::setBottomInnerBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ m_aInnerBorderColor[(int)state].Left, m_aInnerBorderColor[(int)state].Top, m_aInnerBorderColor[(int)state].Right, value });
		}

		bool CSpeedButton::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setImageList(const State state, IImageList *value)
		{
			if (value != m_aImageList[(int)state])
			{
				m_aImageList[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setImageList(IImageList *value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aImageList[i])
				{
					m_aImageList[i] = value;
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

		bool CSpeedButton::setIconIndex(const State state, const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_aIconIndex[(int)state])
			{
				m_aIconIndex[(int)state] = v;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setIconIndex(const int value)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aIconIndex[i])
				{
					m_aIconIndex[i] = value;
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

		bool CSpeedButton::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				m_aShadowColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				m_aShadowShift[(int)state] = value;
				if (state == getState() && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSpeedButton::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				m_aShadowRadius[(int)state] = value;
				if (state == getState() && m_aShadowColor[(int)state].A > 0)
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
		void CSpeedButton::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		bool CSpeedButton::DownExists()
		{
			if (getParent())
			{
				for (int i = 0; i < getParent()->getControlCount(); i++)
					if (getParent()->getControl(i) != this)
					{
						ISpeedButton *btn{ cast<ISpeedButton*>(getParent()->getControl(i)) };
						if (btn && btn->getGroupIndex() == m_iGroupIndex && btn->isDown())
							return true;
					}
			}
			else if (getForm())
				for (int i = 0; i < getForm()->getControlCount(); i++)
					if (getForm()->getControl(i) != this)
					{
						ISpeedButton *btn{ cast<ISpeedButton*>(getForm()->getControl(i)) };
						if (btn && btn->getGroupIndex() == m_iGroupIndex && btn->isDown())
							return true;
					}
			return false;
		}

		void CSpeedButton::ReleaseDown()
		{
			if (getParent())
			{
				for (int i = 0; i < getParent()->getControlCount(); i++)
					if (getParent()->getControl(i) != this)
					{
						ISpeedButton *btn{ cast<ISpeedButton*>(getParent()->getControl(i)) };
						if (btn && btn->getGroupIndex() == m_iGroupIndex && btn->isDown())
						{
							btn->setDown(false);
							CSpeedButton *b{ cast<CSpeedButton*>(btn) };
							if (b && b->OnUp)
								b->OnUp(b);
						}
					}
			}
			else if (getForm())
				for (int i = 0; i < getForm()->getControlCount(); i++)
					if (getForm()->getControl(i) != this)
					{
						ISpeedButton *btn{ cast<ISpeedButton*>(getForm()->getControl(i)) };
						if (btn && btn->getGroupIndex() == m_iGroupIndex && btn->isDown())
						{
							btn->setDown(false);
							CSpeedButton *b{ cast<CSpeedButton*>(btn) };
							if (b && b->OnUp)
								b->OnUp(b);
						}
					}
		}

		void CSpeedButton::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String name;
				switch ((State)i)
				{
				case State::Normal:
					name = L"Normal";
					break;
				case State::Hovered:
					name = L"Hovered";
					break;
				case State::Down:
					name = L"Down";
					break;
				case State::DownHovered:
					name = L"DownHovered";
					break;
				case State::Focused:
					name = L"Focused";
					break;
				case State::FocusedHovered:
					name = L"FocusedHovered";
					break;
				case State::FocusedDown:
					name = L"FocusedDown";
					break;
				case State::FocusedDownHovered:
					name = L"FocusedDownHovered";
				default:
					name = L"Disabled";
				}
				style->getOption(m_sClassName + L".Padding[" + name + L"]", m_aPadding[i]);
				style->getOption(m_sClassName + L".OuterBorderWidth[" + name + L"]", m_aOuterBorderWidth[i]);
				style->getOption(m_sClassName + L".InnerBorderWidth[" + name + L"]", m_aInnerBorderWidth[i]);
				style->getOption(m_sClassName + L".BorderRadius[" + name + L"]", m_aBorderRadius[i]);
				style->getOption(m_sClassName + L".OuterBorderColor[" + name + L"]", m_aOuterBorderColor[i]);
				style->getOption(m_sClassName + L".InnerBorderColor[" + name + L"]", m_aInnerBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + name + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + name + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + name + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + name + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + name + L"]", m_aShadowRadius[i]);
			}
			m_bIgnoreGradient = false;
		}
	#pragma endregion

	#pragma region Paint
		void CSpeedButton::Render()
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

				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() }, icon_part;
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

				rect.Left += m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left + m_aPadding[(int)state].Left;
				rect.Top += m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top + m_aPadding[(int)state].Top;
				rect.Right -= m_aOuterBorderWidth[(int)state].Right + m_aInnerBorderWidth[(int)state].Right + m_aPadding[(int)state].Right;
				rect.Bottom -= m_aOuterBorderWidth[(int)state].Bottom + m_aInnerBorderWidth[(int)state].Bottom + m_aPadding[(int)state].Bottom;
				if (rect.is_valid() && !rect.is_zero())
				{
					ITexture *icon{ (m_aImageList[(int)state] && m_aIconIndex[(int)state] >= 0) ? m_aImageList[(int)state]->getTexture(m_aIconIndex[(int)state]) : nullptr };
					if (icon)
					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						icon_part = RectF{ 0, 0, icon->Widthf, icon->Heightf };
						Mat4f s, t;
						ntl::Scale<float>(s, rect.width() / icon_part.width(), rect.height() / icon_part.height(), 1);
						ntl::Translate<float>(t, rect.Left, rect.Top, 0);
						renderer->ActivatePrimitiveMatrix(t * s);
						if (ntl::IsGreater<float>(m_aBorderRadius[(int)state].Left, ntl::Min<float>(m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left + m_aPadding[(int)state].Left, m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top + m_aPadding[(int)state].Top)) ||
							ntl::IsGreater<float>(m_aBorderRadius[(int)state].Top, ntl::Min<float>(m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top + m_aPadding[(int)state].Top, m_aOuterBorderWidth[(int)state].Right + m_aInnerBorderWidth[(int)state].Right + m_aPadding[(int)state].Right)) ||
							ntl::IsGreater<float>(m_aBorderRadius[(int)state].Right, ntl::Min<float>(m_aOuterBorderWidth[(int)state].Right + m_aInnerBorderWidth[(int)state].Right + m_aPadding[(int)state].Right, m_aOuterBorderWidth[(int)state].Bottom + m_aInnerBorderWidth[(int)state].Bottom + m_aPadding[(int)state].Bottom)) ||
							ntl::IsGreater<float>(m_aBorderRadius[(int)state].Bottom, ntl::Min<float>(m_aOuterBorderWidth[(int)state].Bottom + m_aInnerBorderWidth[(int)state].Bottom + m_aPadding[(int)state].Bottom, m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left + m_aPadding[(int)state].Left)))
						{
							Block b{ rect, AddElements(m_aOuterBorderWidth[(int)state], m_aInnerBorderWidth[(int)state]), m_aBorderRadius[(int)state], PointLocation::Inside };
							CStoreBlock s_block{ renderer };
							renderer
								->ActivateBlock(&b)
								->DrawImage(icon, 1, icon_part);
						}
						else
							renderer->DrawImage(icon, 1, icon_part);
					}
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}
	#pragma endregion
	}
}