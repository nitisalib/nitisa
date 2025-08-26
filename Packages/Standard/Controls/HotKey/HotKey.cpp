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
		CHotKey::CGradientListener::CGradientListener(CHotKey *control) :
			m_pControl{ control }
		{

		}

		void CHotKey::CGradientListener::NotifyOnChange()
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
		CHotKey::CHotKey() :
			CControl(L"HotKey", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_sHotkey{ Key::Unknown, false, false, false, false },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sPadding{ 2, 2, 2, 2 },
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
				Color{ 255, 255, 255, 255 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aShadowRadius{ 1, 1, 1, 1, 1 },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aTextColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aTextShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aTextShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aTextShadowRadius{ 1, 1, 1, 1, 1 },
			m_bIgnoreGradient{ false },
			m_pCanvas{ nullptr }
		{
			setService(new CHotKeyService(this), true);
			setSize(PointF{ 120, 20 });
		}

		CHotKey::CHotKey(IControl *parent) :CHotKey()
		{
			setParent(parent);
		}

		CHotKey::CHotKey(IForm *parent) : CHotKey()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		RectF CHotKey::getClientRect()
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

		RectF CHotKey::getRenderRect()
		{
			RectF result{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)State::Normal], m_aShadowShift[(int)State::Normal], m_aShadowRadius[(int)State::Normal]) };
			for (int i = 1; i <= (int)State::Disabled; i++)
				result += AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
			return result;
		}

		bool CHotKey::isWantTabs()
		{
			return true;
		}

		Hotkey CHotKey::getHotKey()
		{
			return m_sHotkey;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CHotKey::setWantTabs(const bool value)
		{
			return false;
		}

		bool CHotKey::setHotKey(const Hotkey &value)
		{
			if (value.Key != m_sHotkey.Key || value.Ctrl != m_sHotkey.Ctrl || value.Alt != m_sHotkey.Alt || value.Shift != m_sHotkey.Shift)
			{
				m_sHotkey = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHotKey::setDPI(const Point &value)
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
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
					m_aTextShadowShift[i] *= s;
					m_aTextShadowRadius[i] = ntl::Round<int>((float)m_aTextShadowRadius[i] * avg);
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CHotKey::State CHotKey::getState()
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

		RectF CHotKey::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CHotKey::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		RectF CHotKey::getPadding() const
		{
			return m_sPadding;
		}

		BorderColor CHotKey::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CHotKey::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CHotKey::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		int CHotKey::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CHotKey::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CHotKey::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		Color CHotKey::getTextColor(const State state) const
		{
			return m_aTextColor[(int)state];
		}

		Color CHotKey::getTextShadowColor(const State state) const
		{
			return m_aTextShadowColor[(int)state];
		}

		PointF CHotKey::getTextShadowShift(const State state) const
		{
			return m_aTextShadowShift[(int)state];
		}

		int CHotKey::getTextShadowRadius(const State state) const
		{
			return m_aTextShadowRadius[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CHotKey::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHotKey::setBorderRadius(const RectF &value)
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

		bool CHotKey::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				if (!m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHotKey::setBorderColor(const State state, const BorderColor &value)
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

		bool CHotKey::setLeftBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CHotKey::setTopBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CHotKey::setRightBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CHotKey::setBottomBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CHotKey::setBackgroundColor(const State state, const Color &value)
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

		bool CHotKey::setShadowRadius(const State state, const int value)
		{
			if (value > 0 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (state == getState() && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
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

		bool CHotKey::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (state == getState() && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
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

		bool CHotKey::setShadowColor(const State state, const Color &value)
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

		bool CHotKey::setTextColor(const State state, const Color &value)
		{
			if (value != m_aTextColor[(int)state])
			{
				m_aTextColor[(int)state] = value;
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

		bool CHotKey::setTextShadowColor(const State state, const Color &value)
		{
			if (value != m_aTextShadowColor[(int)state])
			{
				m_aTextShadowColor[(int)state] = value;
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

		bool CHotKey::setTextShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aTextShadowShift[(int)state]))
			{
				m_aTextShadowShift[(int)state] = value;
				if (state == getState() && m_aTextShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CHotKey::setTextShadowRadius(const State state, const int value)
		{
			if (value > 0 && value != m_aTextShadowRadius[(int)state])
			{
				m_aTextShadowRadius[(int)state] = value;
				if (state == getState() && m_aTextShadowColor[(int)state].A > 0)
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
		void CHotKey::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CHotKey::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
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
				style->getOption(m_sClassName + L".ShadowRadius[" + name + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + name + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + name + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".TextColor[" + name + L"]", m_aTextColor[i]);
				style->getOption(m_sClassName + L".TextShadowColor[" + name + L"]", m_aTextShadowColor[i]);
				style->getOption(m_sClassName + L".TextShadowShift[" + name + L"]", m_aTextShadowShift[i]);
				style->getOption(m_sClassName + L".TextShadowRadius[" + name + L"]", m_aTextShadowRadius[i]);
			}
			m_bIgnoreGradient = false;
		}
	#pragma endregion

	#pragma region Paint
		void CHotKey::Render()
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
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
				if (m_sHotkey.Key != Key::Unknown)
				{
					IFont *font{ getFont() };
					IPlatformFont *pf{ font->getPlatformFont(renderer) };
					Color shadow_color{ m_aTextShadowColor[(int)state].A > 0 ? m_aTextShadowColor[(int)state] : font->ShadowColor };
					RectF client{ getClientRect() };
					String text{ CTranslate::Hotkey(m_sHotkey) };
					float height{ pf->getStringSize(text, font->Distance).Y };
					float y{ m_sBorderWidth.Top + m_sPadding.Top + (client.height() - height) / 2 };
					PointF pos{ std::round(m_sBorderWidth.Left + m_sPadding.Left + disp.X), std::round(y + disp.Y) };
					if (shadow_color.A > 0)
						DrawTextShadow(renderer, pf, font->Distance, Identity, client + disp, pos, text, shadow_color, m_aTextShadowShift[(int)state], m_aTextShadowRadius[(int)state]);
					Block b{ rect, AddElements(m_sBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
					Color color{ m_aTextColor[(int)state].A > 0 ? m_aTextColor[(int)state] : font->Color };
					if (color.A > 0)
					{
						CStoreBlock s_block{ renderer };
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivateBlock(&b)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(pos.X, pos.Y, 0))
							->DrawText(text, pf, font->Distance, color);
					}
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}
	#pragma endregion
	}
}