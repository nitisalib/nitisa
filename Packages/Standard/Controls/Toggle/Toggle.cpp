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
	#pragma region Constructor & destructor
		CToggle::CToggle():
			CControl(L"Toggle", true, true, false, false, false, false),
			m_bOn{ true },
			m_aBackgroundBorderWidth{ 0, 0, 0 },
			m_aBackgroundBorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_aBackgroundColor{ Color{ 76, 202, 97, 255 }, Color{ 222, 222, 222, 255 }, Color{ 222, 222, 222, 255 } },
			m_aBorderWidth{ 2, 2, 2 },
			m_aBorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_aColor{ Color{ 247, 247, 247, 255 }, Color{ 247, 247, 247, 255 }, Color{ 230, 230, 230, 255 } },
			m_aShadowRadius{ 1, 1, 1 },
			m_aShadowColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_aShadowShift{ PointF{ 0, 0 }, PointF{ 0, 0 }, PointF{ 0, 0 } },
			m_pCanvas{ nullptr },
			OnToggle{ nullptr }
		{
			setService(new CToggleService(this), true);
			setSize(PointF{ 40, 20 });
		}

		CToggle::CToggle(IControl *parent) :CToggle()
		{
			setParent(parent);
		}

		CToggle::CToggle(IForm *parent) :CToggle()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CToggle::getRenderRect()
		{
			RectF result{ AddShadow(getRect(), m_aShadowColor[0], m_aShadowShift[0], m_aShadowRadius[0]) };
			for (int i = 1; i <= (int)State::Disabled; i++)
				result += AddShadow(getRect(), m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
			return result;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CToggle::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aBackgroundBorderWidth[i] *= avg;
					m_aBorderWidth[i] *= avg;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
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
		void CToggle::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region IToggle getters
		bool CToggle::isOn()
		{
			return m_bOn;
		}
	#pragma endregion

	#pragma region IToggle setters
		bool CToggle::setOn(const bool value)
		{
			if (value != m_bOn)
			{
				CLockRepaint lock{ this };
				Repaint(false);
				m_bOn = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IToggle methods
		void CToggle::Toggle()
		{
			CLockRepaint lock{ this };
			Repaint(false);
			m_bOn = !m_bOn;
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}
	#pragma endregion

	#pragma region Getters
		float CToggle::getBackgroundBorderWidth(const State state)
		{
			return m_aBackgroundBorderWidth[(int)state];
		}

		Color CToggle::getBackgroundBorderColor(const State state)
		{
			return m_aBackgroundBorderColor[(int)state];
		}

		Color CToggle::getBackgroundColor(const State state)
		{
			return m_aBackgroundColor[(int)state];
		}

		float CToggle::getBorderWidth(const State state)
		{
			return m_aBorderWidth[(int)state];
		}

		Color CToggle::getBorderColor(const State state)
		{
			return m_aBorderColor[(int)state];
		}

		Color CToggle::getColor(const State state)
		{
			return m_aColor[(int)state];
		}

		int CToggle::getShadowRadius(const State state)
		{
			return m_aShadowRadius[(int)state];
		}

		Color CToggle::getShadowColor(const State state)
		{
			return m_aShadowColor[(int)state];
		}

		PointF CToggle::getShadowShift(const State state)
		{
			return m_aShadowShift[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CToggle::setBackgroundBorderWidth(const State state, const float value)
		{
			if (ntl::IsPositive<float>(value) && ntl::IsNotEqual<float>(value, m_aBackgroundBorderWidth[(int)state]))
			{
				m_aBackgroundBorderWidth[(int)state] = value;
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

		bool CToggle::setBackgroundBorderColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundBorderColor[(int)state])
			{
				m_aBackgroundBorderColor[(int)state] = value;
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

		bool CToggle::setBackgroundColor(const State state, const Color &value)
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

		bool CToggle::setBorderWidth(const State state, const float value)
		{
			if (ntl::IsPositive<float>(value) && ntl::IsNotEqual<float>(value, m_aBorderWidth[(int)state]))
			{
				m_aBorderWidth[(int)state] = value;
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

		bool CToggle::setBorderColor(const State state, const Color &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
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

		bool CToggle::setColor(const State state, const Color &value)
		{
			if (value != m_aColor[(int)state])
			{
				m_aColor[(int)state] = value;
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

		bool CToggle::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				State current{ getState() };
				if (state == current && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (state == current && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CToggle::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				CLockRepaint lock{ this };
				State current{ getState() };
				if (state == current)
					Repaint(false);
				m_aShadowColor[(int)state] = value;
				if (state == current)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CToggle::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				State current{ getState() };
				if (state == current && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (state == current && m_aShadowColor[(int)state].A > 0)
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
		void CToggle::UpdateFromStyle(IStyle *style)
		{
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Off:
					state = L"Off";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"On";
				}
				style->getOption(m_sClassName + L".BackgroundBorderWidth[" + state + L"]", m_aBackgroundBorderWidth[i]);
				style->getOption(m_sClassName + L".BackgroundBorderColor[" + state + L"]", m_aBackgroundBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BorderWidth[" + state + L"]", m_aBorderWidth[i]);
				style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]);
				style->getOption(m_sClassName + L".Color[" + state + L"]", m_aColor[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
			}
		}

		CToggle::State CToggle::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_bOn)
				return State::On;
			return State::Off;
		}
	#pragma endregion

	#pragma region Render
		void CToggle::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(getRect(), m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				Gradient g;
				if (rect.width() >= rect.height())
				{
					// Horizontal
					float bg_radius{ rect.height() * 0.5f };
					float bg_border{ std::floor(ntl::Min<float>(m_aBackgroundBorderWidth[(int)state], rect.height() * 0.5f)) };
					DrawBlockShadow(
						renderer,
						rect,
						RectF{ bg_radius, bg_radius, bg_radius, bg_radius },
						m_aShadowColor[(int)state],
						m_aShadowShift[(int)state],
						m_aShadowRadius[(int)state]);
					DrawSimpleBackground(
						renderer,
						rect,
						RectF{ bg_border, bg_border, bg_border, bg_border },
						RectF{ bg_radius, bg_radius, bg_radius, bg_radius },
						BorderColor{ m_aBackgroundBorderColor[(int)state], m_aBackgroundBorderColor[(int)state], m_aBackgroundBorderColor[(int)state], m_aBackgroundBorderColor[(int)state] },
						m_aBackgroundColor[(int)state],
						g);
					float radius{ rect.height() * 0.5f - bg_border };
					if (radius >= 2 + m_aBorderWidth[(int)state])
					{
						RectF r;
						if (m_bOn)
							r = RectF{ getWidth() - bg_border - 2 * radius, bg_border, getWidth() - bg_border, getHeight() - bg_border } + rect.LeftTop;
						else
							r = RectF{ bg_border, bg_border, bg_border + radius * 2, getHeight() - bg_border } + rect.LeftTop;
						DrawSimpleBackground(
							renderer,
							r,
							RectF{ m_aBorderWidth[(int)state], m_aBorderWidth[(int)state], m_aBorderWidth[(int)state], m_aBorderWidth[(int)state] },
							RectF{ radius, radius, radius, radius },
							BorderColor{ m_aBorderColor[(int)state], m_aBorderColor[(int)state], m_aBorderColor[(int)state], m_aBorderColor[(int)state] },
							m_aColor[(int)state],
							g);
					}
				}
				else
				{
					// Vertical
					float bg_radius{ rect.width() * 0.5f };
					float bg_border{ std::floor(ntl::Min<float>(m_aBackgroundBorderWidth[(int)state], rect.width() * 0.5f)) };
					DrawBlockShadow(
						renderer,
						rect,
						RectF{ bg_radius, bg_radius, bg_radius, bg_radius },
						m_aShadowColor[(int)state],
						m_aShadowShift[(int)state],
						m_aShadowRadius[(int)state]);
					DrawSimpleBackground(
						renderer,
						rect,
						RectF{ bg_border, bg_border, bg_border, bg_border },
						RectF{ bg_radius, bg_radius, bg_radius, bg_radius },
						BorderColor{ m_aBackgroundBorderColor[(int)state], m_aBackgroundBorderColor[(int)state], m_aBackgroundBorderColor[(int)state], m_aBackgroundBorderColor[(int)state] },
						m_aBackgroundColor[(int)state],
						g);
					float radius{ rect.width() * 0.5f - bg_border };
					if (radius >= 2 + m_aBorderWidth[(int)state])
					{
						RectF r;
						if (m_bOn)
							r = RectF{  bg_border, bg_border, getWidth() - bg_border, bg_border + radius * 2 } + rect.LeftTop;
						else
							r = RectF{ bg_border, getHeight() - bg_border - 2 * radius, getWidth() - bg_border, getHeight() - bg_border } + rect.LeftTop;
						DrawSimpleBackground(
							renderer,
							r,
							RectF{ m_aBorderWidth[(int)state], m_aBorderWidth[(int)state], m_aBorderWidth[(int)state], m_aBorderWidth[(int)state] },
							RectF{ radius, radius, radius, radius },
							BorderColor{ m_aBorderColor[(int)state], m_aBorderColor[(int)state], m_aBorderColor[(int)state], m_aBorderColor[(int)state] },
							m_aColor[(int)state],
							g);
					}
				}
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}
	#pragma endregion
	}
}