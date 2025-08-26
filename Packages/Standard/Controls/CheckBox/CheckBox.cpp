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
	#pragma region Constructor & destructor
		CCheckBox::CCheckBox() :
			CControl(L"CheckBox", true, true, false, true, false, true),
			m_eContentHorizontalAlign{ TextAlign::Left },
			m_eContentVerticalAlign{ VerticalAlign::Middle },
			m_bIconOnRight{ false },
			m_bAutoSize{ true },
			m_fIconPadding{ 4 },
			m_eChecked{ CheckedState::Unchecked },
			m_aColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 64, 64, 255, 255 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 133, 135, 139, 255 } },
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
			m_pCanvas{ nullptr },
			m_bMouseDown{ false },
			m_bCaptionChanged{ false },
			OnChange{ nullptr }
		{
			setService(new CCheckBoxService(this), true);
		}

		CCheckBox::CCheckBox(IControl *parent) :CCheckBox()
		{
			setParent(parent);
		}

		CCheckBox::CCheckBox(IForm *parent) : CCheckBox()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region IControl methods
		void CCheckBox::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region CControl getters
		RectF CCheckBox::getRenderRect()
		{
			RectF result{ getRenderRect(State::Normal) };
			for (int i = (int)State::Normal + 1; i <= (int)State::Disabled; i++)
				result += getRenderRect((State)i);
			return result;
		}
	#pragma endregion

	#pragma region ICheckBox getters
		ICheckBox::CheckedState CCheckBox::getChecked()
		{
			return m_eChecked;
		}
	#pragma endregion

	#pragma region Getters
		CCheckBox::State CCheckBox::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_bMouseDown)
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

		String CCheckBox::getCaption()
		{
			return m_sCaption;
		}

		TextAlign CCheckBox::getContentHorizontalAlign() const
		{
			return m_eContentHorizontalAlign;
		}

		VerticalAlign CCheckBox::getContentVerticalAlign() const
		{
			return m_eContentVerticalAlign;
		}

		bool CCheckBox::isIconOnRight() const
		{
			return m_bIconOnRight;
		}

		bool CCheckBox::isAutoSize() const
		{
			return m_bAutoSize;
		}

		float CCheckBox::getIconPadding() const
		{
			return m_fIconPadding;
		}

		Color CCheckBox::getColor(const State state) const
		{
			return m_aColor[(int)state];
		}

		Color CCheckBox::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CCheckBox::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CCheckBox::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}
	#pragma endregion

	#pragma region CControl setters
		bool CCheckBox::setAlign(const Align value)
		{
			m_bAutoSize = false;
			return CControl::setAlign(value);
		}

		bool CCheckBox::setConstraints(const RectF &value)
		{
			m_bAutoSize = false;
			return CControl::setConstraints(value);
		}

		bool CCheckBox::setSize(const PointF &value)
		{
			m_bAutoSize = false;
			return CControl::setSize(value);
		}

		bool CCheckBox::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_fIconPadding *= s.X;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowShift[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
				}
				UpdateAutoSize();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ICheckBox setters
		bool CCheckBox::setChecked(const CheckedState value)
		{
			if (value != m_eChecked)
			{
				m_eChecked = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CCheckBox::setCaption(const String &value)
		{
			m_bCaptionChanged = true;
			if (value != m_sCaption)
			{
				CLockRepaint lock{ this };
				m_sCaption = value;
				UpdateAutoSize();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCheckBox::setContentHorizontalAlign(const TextAlign value)
		{
			if (value != m_eContentHorizontalAlign)
			{
				m_eContentHorizontalAlign = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCheckBox::setContentVerticalAlign(const VerticalAlign value)
		{
			if (value != m_eContentVerticalAlign)
			{
				m_eContentVerticalAlign = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCheckBox::setIconOnRight(const bool value)
		{
			if (value != m_bIconOnRight)
			{
				m_bIconOnRight = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCheckBox::setAutoSize(const bool value)
		{
			if (value != m_bAutoSize)
			{
				m_bAutoSize = value;
				if (m_bAutoSize)
				{
					CLockRepaint lock{ this };
					CControl::setAlign(Align::None);
					UpdateAutoSize();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCheckBox::setIconPadding(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fIconPadding))
			{
				CLockRepaint lock{ this };
				m_fIconPadding = value;
				UpdateAutoSize();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCheckBox::setColor(const State state, const Color &value)
		{
			if (value != m_aColor[(int)state])
			{
				m_aColor[(int)state] = value;
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

		bool CCheckBox::setShadowColor(const State state, const Color &value)
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

		bool CCheckBox::setShadowShift(const State state, const PointF &value)
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

		bool CCheckBox::setShadowRadius(const State state, const int value)
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
	#pragma endregion

	#pragma region Helpers
		ITexture *CCheckBox::FindIcon(const State state, RectF &part)
		{
			String name{ m_sClassName };
			switch (m_eChecked)
			{
			case ICheckBox::CheckedState::Grayed:
				name += L".Grayed";
				break;
			case ICheckBox::CheckedState::Checked:
				name += L".Checked";
				break;
			default:
				name += L".Unchecked";
			}
			switch (state)
			{
			case State::Hovered:
				name += L".Hovered";
				break;
			case State::Focused:
				name += L".Focused";
				break;
			case State::FocusedHovered:
				name += L".Focused.Hovered";
				break;
			case State::Active:
				name += L".Active";
				break;
			case State::ActiveHovered:
				name += L".Active.Hovered";
				break;
			case State::Disabled:
				name += L".Disabled";
				break;
			default:
				break;
			}
			IStyle *style{ getStyle() };
			if (style)
			{
				IStyleSkin *skin{ style->getSkin(name) };
				if (skin)
				{
					part = skin->Rect;
					return getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			if (style != Application->Styles->getStyle(0) && (style = Application->Styles->getStyle(0)))
			{
				IStyleSkin *skin{ style->getSkin(name) };
				if (skin)
				{
					part = skin->Rect;
					return getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			return nullptr;
		}

		void CCheckBox::UpdateAutoSize()
		{
			if (m_bAutoSize && getForm() && getForm()->getRenderer() && getFont()->getPlatformFont(getForm()->getRenderer()))
			{
				PointF required_size{ 0, 0 };
				if (!m_sCaption.empty())
					required_size = getFont()->getPlatformFont(getForm()->getRenderer())->getStringSize(m_sCaption, getFont()->Distance);
				RectF part;
				ITexture *icon{ FindIcon(State::Normal, part) };
				if (icon)
				{
					if (!m_sCaption.empty())
						required_size.X += m_fIconPadding;
					required_size.X += part.width();
					required_size.Y = ntl::Max<float>(required_size.Y, part.height());
				}
				CControl::setSize(required_size);
			}
		}

		void CCheckBox::UpdateFromStyle(IStyle *style)
		{
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
				style->getOption(m_sClassName + L".Color[" + state + L"]", m_aColor[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
			}
		}

		RectF CCheckBox::getRenderRect(const State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}
	#pragma endregion

	#pragma region Paint to canvas
		void CCheckBox::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				State state{ getState() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				IFont *font{ getFont() };
				IPlatformFont *pf{ font->getPlatformFont(renderer) };
				RectF icon_part;
				ITexture *icon{ FindIcon(state, icon_part) };
				if (!m_sCaption.empty())
				{
					PointF pos{ 0, 0 }, text_size{ pf->getStringSize(m_sCaption, font->Distance) };
					float width{ text_size.X + (icon ? (m_fIconPadding + icon_part.width()) : 0) }, height{ ntl::Max<float>(text_size.Y, icon ? icon_part.height() : 0) };
					switch (m_eContentHorizontalAlign)
					{
					case TextAlign::Center:
						pos.X = (getWidth() - width) * 0.5f;
						break;
					case TextAlign::Right:
						pos.X = getWidth() - width;
						break;
					default:
						break;
					}
					if (icon && !m_bIconOnRight)
						pos.X += m_fIconPadding + icon_part.width();
					switch (m_eContentVerticalAlign)
					{
					case VerticalAlign::Middle:
						pos.Y = (getHeight() - height) * 0.5f;
						break;
					case VerticalAlign::Bottom:
						pos.Y = getHeight() - height;
						break;
					default:
						break;
					}
					if (icon)
						pos.Y += (height - text_size.Y) * 0.5f;
					pos.X = std::round(pos.X);
					pos.Y = std::round(pos.Y);
					DrawTextShadow(
						renderer,
						pf,
						font->Distance,
						Identity,
						RectF{ 0, 0, getWidth(), getHeight() },
						pos,
						m_sCaption,
						m_aShadowColor[(int)state],
						m_aShadowShift[(int)state],
						m_aShadowRadius[(int)state]);
					Color color{ m_aColor[(int)state].A > 0 ? m_aColor[(int)state] : getFont()->Color };
					if (color.A > 0)
					{
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(pos.X, pos.Y, 0))
							->DrawText(m_sCaption, pf, font->Distance, color);
					}
				}
				if (icon)
				{
					PointF pos{ 0, 0 }, text_size{ m_sCaption.empty() ? PointF{ 0, 0 } : pf->getStringSize(m_sCaption, font->Distance) };
					float width{ icon_part.width() + (m_sCaption.empty() ? 0 : (m_fIconPadding + text_size.X)) }, height{ ntl::Max<float>(text_size.Y, icon_part.height()) };
					switch (m_eContentHorizontalAlign)
					{
					case TextAlign::Center:
						pos.X = (getWidth() - width) * 0.5f;
						break;
					case TextAlign::Right:
						pos.X = getWidth() - width;
						break;
					default:
						break;
					}
					if (!m_sCaption.empty() && m_bIconOnRight)
						pos.X = pos.X + width - icon_part.width();
					switch (m_eContentVerticalAlign)
					{
					case VerticalAlign::Middle:
						pos.Y = (getHeight() - height) * 0.5f;
						break;
					case VerticalAlign::Bottom:
						pos.Y = getHeight() - height;
						break;
					default:
						break;
					}
					if (!m_sCaption.empty())
						pos.Y += (height - icon_part.height()) * 0.5f;
					renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X), std::round(pos.Y), 0))
						->DrawImage(icon, 1, icon_part);
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}
	#pragma endregion
	}
}