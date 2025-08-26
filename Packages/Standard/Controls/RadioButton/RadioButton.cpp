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
		CRadioButton::CRadioButton() :
			CControl(L"RadioButton", true, true, false, true, false, true),
			m_eContentHorizontalAlign{ TextAlign::Left },
			m_eContentVerticalAlign{ VerticalAlign::Middle },
			m_bIconOnRight{ false },
			m_bAutoSize{ true },
			m_fIconPadding{ 4 },
			m_iGroupIndex{ 0 },
			m_bChecked{ false },
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
			m_bMouseDown{ false },
			m_pCanvas{ nullptr },
			m_bCaptionChanged{ false },
			OnChange{ nullptr }
		{
			setService(new CRadioButtonService(this), true);
		}

		CRadioButton::CRadioButton(IControl *parent) :CRadioButton()
		{
			setParent(parent);
		}

		CRadioButton::CRadioButton(IForm *parent) : CRadioButton()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region CControl getters
		RectF CRadioButton::getRenderRect()
		{
			RectF result{ getRenderRect(State::Normal) };
			for (int i = (int)State::Normal + 1; i <= (int)State::Disabled; i++)
				result += getRenderRect((State)i);
			return result;
		}
	#pragma endregion

	#pragma region IRadioButton getters
		int CRadioButton::getGroupIndex()
		{
			return m_iGroupIndex;
		}

		bool CRadioButton::isChecked()
		{
			return m_bChecked;
		}
	#pragma endregion

	#pragma region Getters
		CRadioButton::State CRadioButton::getState()
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

		String CRadioButton::getCaption()
		{
			return m_sCaption;
		}

		TextAlign CRadioButton::getContentHorizontalAlign() const
		{
			return m_eContentHorizontalAlign;
		}

		VerticalAlign CRadioButton::getContentVerticalAlign() const
		{
			return m_eContentVerticalAlign;
		}

		bool CRadioButton::isIconOnRight() const
		{
			return m_bIconOnRight;
		}

		bool CRadioButton::isAutoSize() const
		{
			return m_bAutoSize;
		}

		float CRadioButton::getIconPadding() const
		{
			return m_fIconPadding;
		}

		Color CRadioButton::getColor(const State state) const
		{
			return m_aColor[(int)state];
		}

		Color CRadioButton::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CRadioButton::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CRadioButton::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}
	#pragma endregion

	#pragma region CControl setters
		bool CRadioButton::setAlign(const Align value)
		{
			m_bAutoSize = false;
			return CControl::setAlign(value);
		}

		bool CRadioButton::setConstraints(const RectF &value)
		{
			m_bAutoSize = false;
			return CControl::setConstraints(value);
		}

		bool CRadioButton::setSize(const PointF &value)
		{
			m_bAutoSize = false;
			return CControl::setSize(value);
		}

		bool CRadioButton::setDPI(const Point &value)
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

	#pragma region IRadioButton setters
		bool CRadioButton::setGroupIndex(const int value)
		{
			if (value < 0 && m_iGroupIndex < 0)
				return false;
			if (value != m_iGroupIndex)
			{
				m_iGroupIndex = value < 0 ? -1 : value;
				if (m_iGroupIndex >= 0 && m_bChecked && HaveCheckedOnParent())
					m_bChecked = false;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CRadioButton::setChecked(const bool value)
		{
			if (value != m_bChecked)
			{
				CLockRepaint lock{ this };
				m_bChecked = value;
				if (m_bChecked && m_iGroupIndex >= 0)
					UncheckAllOnParent();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CRadioButton::setCaption(const String &value)
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

		bool CRadioButton::setContentHorizontalAlign(const TextAlign value)
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

		bool CRadioButton::setContentVerticalAlign(const VerticalAlign value)
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

		bool CRadioButton::setIconOnRight(const bool value)
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

		bool CRadioButton::setAutoSize(const bool value)
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

		bool CRadioButton::setIconPadding(const float value)
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

		bool CRadioButton::setColor(const State state, const Color &value)
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

		bool CRadioButton::setShadowColor(const State state, const Color &value)
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

		bool CRadioButton::setShadowShift(const State state, const PointF &value)
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

		bool CRadioButton::setShadowRadius(const State state, const int value)
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
		void CRadioButton::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		bool CRadioButton::HaveCheckedOnParent()
		{
			if (getParent())
			{
				for (int i = 0; i < getParent()->getControlCount(); i++)
					if (getParent()->getControl(i) != this)
					{
						IRadioButton *control{ cast<IRadioButton*>(getParent()->getControl(i)) };
						if (control && control->getGroupIndex() == m_iGroupIndex)
							return true;
					}
			}
			else if (getForm())
				for (int i = 0; i < getForm()->getControlCount(); i++)
					if (getForm()->getControl(i) != this)
					{
						IRadioButton *control{ cast<IRadioButton*>(getForm()->getControl(i)) };
						if (control && control->getGroupIndex() == m_iGroupIndex)
							return true;
					}
			return false;
		}

		void CRadioButton::UncheckAllOnParent()
		{
			if (getParent())
			{
				for (int i = 0; i < getParent()->getControlCount(); i++)
					if (getParent()->getControl(i) != this)
					{
						IRadioButton *control{ cast<IRadioButton*>(getParent()->getControl(i)) };
						if (control && control->getGroupIndex() == m_iGroupIndex)
							control->setChecked(false);
					}
			}
			else if (getForm())
				for (int i = 0; i < getForm()->getControlCount(); i++)
					if (getForm()->getControl(i) != this)
					{
						IRadioButton *control{ cast<IRadioButton*>(getForm()->getControl(i)) };
						if (control && control->getGroupIndex() == m_iGroupIndex)
							control->setChecked(false);
					}
		}

		ITexture *CRadioButton::FindIcon(const State state, RectF &part)
		{
			String name{ m_sClassName + (m_bChecked ? L".Checked" : L".Unchecked") };
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

		void CRadioButton::UpdateAutoSize()
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

		void CRadioButton::UpdateFromStyle(IStyle *style)
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

		RectF CRadioButton::getRenderRect(const State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}
	#pragma endregion

	#pragma region Paint
		void CRadioButton::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			RectF all_rect{ 0, 0, getWidth(), getHeight() };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
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
					DrawTextShadow(renderer, pf, font->Distance, Identity, all_rect, pos, m_sCaption, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
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