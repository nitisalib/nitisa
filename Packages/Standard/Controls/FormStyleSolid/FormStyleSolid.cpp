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
		CFormStyleSolid::CFormStyleSolid():
			CControl(L"FormStyleSolid", true, false, false, false, false, false),
			m_bShowCaption{ true },
			m_fCaptionHeight{ 22 },
			m_sCaptionPadding{ 0, 0 },
			m_sBorderWidth{ 8, 30, 8, 8 },
			m_sBorderColor{ Color{ 214, 219, 233, 255 }, Color{ 214, 219, 233, 255 }, Color{ 214, 219, 233, 255 }, Color{ 214, 219, 233, 255 } },
			m_sCaptionBackgroundColor{ 214, 219, 233, 255 },
			m_eCaptionAlign{ TextAlign::Left },
			m_sBtnMinimize{
				true, // Visible
				true, // Enabled
				{ // Border widths
					RectF{ 1, 0, 1, 1 },
					RectF{ 1, 0, 1, 1 },
					RectF{ 1, 0, 1, 1 },
					RectF{ 1, 0, 1, 1 }
				},
				{ // Border radii
					RectF{ 0, 0, 0, 0 },
					RectF{ 0, 0, 0, 0 },
					RectF{ 0, 0, 0, 0 },
					RectF{ 0, 0, 0, 0 }
				},
				{ // Border colors
					BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
					BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
					BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
					BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } }
				},
				{ // Background colors
					Color{ 0, 0, 0, 0 },
					Color{ 255, 252, 244, 255 },
					Color{ 255, 232, 166, 255 },
					Color{ 0, 0, 0, 0 }
				}
			},
			m_sBtnRestore{
				true, // Visible
				true, // Enabled
				{ // Border widths
					RectF{ 1, 0, 1, 1 },
					RectF{ 1, 0, 1, 1 },
					RectF{ 1, 0, 1, 1 },
					RectF{ 1, 0, 1, 1 }
				},
				{ // Border radii
					RectF{ 0, 0, 0, 0 },
					RectF{ 0, 0, 0, 0 },
					RectF{ 0, 0, 0, 0 },
					RectF{ 0, 0, 0, 0 }
				},
				{ // Border colors
					BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
					BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
					BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
					BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } }
				},
				{ // Background colors
					Color{ 0, 0, 0, 0 },
					Color{ 255, 252, 244, 255 },
					Color{ 255, 232, 166, 255 },
					Color{ 0, 0, 0, 0 }
				}
			},
			m_sBtnClose{
				true, // Visible
				true, // Enabled
				{ // Border widths
					RectF{ 1, 0, 1, 1 },
					RectF{ 1, 0, 1, 1 },
					RectF{ 1, 0, 1, 1 },
					RectF{ 1, 0, 1, 1 }
				},
				{ // Border radii
					RectF{ 0, 0, 0, 0 },
					RectF{ 0, 0, 0, 0 },
					RectF{ 0, 0, 0, 0 },
					RectF{ 0, 0, 0, 0 }
				},
				{ // Border colors
					BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
					BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
					BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
					BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } }
				},
				{ // Background colors
					Color{ 0, 0, 0, 0 },
					Color{ 255, 252, 244, 255 },
					Color{ 255, 232, 166, 255 },
					Color{ 0, 0, 0, 0 }
				}
			},
			m_pCanvasHeader{ nullptr },
			m_eHovered{ Element::None },
			m_eDown{ Element::None }
		{
			setService(new CFormStyleSolidService(this), true);
		}

		CFormStyleSolid::CFormStyleSolid(IForm *parent) :CFormStyleSolid()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		IControl *CFormStyleSolid::getControl(const int index)
		{
			return nullptr;
		}

		IControl *CFormStyleSolid::getControl(const String &name)
		{
			return nullptr;
		}

		IControl *CFormStyleSolid::getControl(const PointF &position)
		{
			if (getForm() && !Application->Editor)
			{
				Rect client{ getForm()->getClientRect() };
				if (position.X >= (float)client.Left && position.X < (float)client.Right && position.Y >= (float)client.Top && position.Y < (float)client.Bottom &&
					(position.X < (float)client.Left + m_sBorderWidth.Left || position.X >= (float)client.Right - m_sBorderWidth.Right ||
						position.Y < (float)client.Top + m_sBorderWidth.Top + m_fCaptionHeight || position.Y >= (float)client.Bottom - m_sBorderWidth.Bottom))
					return this;
			}
			return nullptr;
		}

		RectF CFormStyleSolid::getRect()
		{
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CFormStyleSolid::getClientRect()
		{
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CFormStyleSolid::getRenderRect()
		{
			if (getForm())
				return (RectF)getForm()->getClientRect();
			return RectF{ 0, 0, 0, 0 };
		}

		CursorType CFormStyleSolid::getCursor()
		{
			Element el{ m_eDown == Element::None ? m_eHovered : m_eDown };
			switch (el)
			{
			case Element::LeftBorder:
			case Element::RightBorder:
				return CursorType::SizeWestEast;
			case Element::TopBorder:
			case Element::BottomBorder:
				return CursorType::SizeNorthSouth;
			case Element::LeftTopCorner:
			case Element::RightBottomCorner:
				return CursorType::SizeNorthwestSoutheast;
			case Element::RightTopCorner:
			case Element::LeftBottomCorner:
				return CursorType::SizeNortheastSouthwest;
			//case Element::Header:
			//	return CursorType::SizeAll;
			default:
				return CursorType::Arrow;
			}
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormStyleSolid::setAlign(const Align value)
		{
			return false;
		}

		bool CFormStyleSolid::setConstraints(const RectF &value)
		{
			return false;
		}

		bool CFormStyleSolid::setSize(const PointF &value)
		{
			return false;
		}

		bool CFormStyleSolid::setHintText(const String &value)
		{
			return false;
		}

		bool CFormStyleSolid::setVisible(const bool value)
		{
			return false;
		}

		bool CFormStyleSolid::setEnabled(const bool value)
		{
			return false;
		}

		bool CFormStyleSolid::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_fCaptionHeight *= s.Y;
				m_sBorderWidth *= s;
				for (int i = 0; i <= (int)ButtonState::Disabled; i++)
				{
					m_sBtnMinimize.BorderWidth[i] *= s;
					m_sBtnRestore.BorderWidth[i] *= s;
					m_sBtnClose.BorderWidth[i] *= s;
				}
				if (getForm())
					getForm()->setBorderWidth(m_sBorderWidth);
				if (m_pCanvasHeader)
					m_pCanvasHeader->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormStyleSolid::Refresh(const bool refresh_children)
		{
			if (m_pCanvasHeader)
				m_pCanvasHeader->setValid(false);
			CControl::Refresh(refresh_children);
		}
	#pragma endregion

	#pragma region Getters
		bool CFormStyleSolid::isShowCaption() const
		{
			return m_bShowCaption;
		}

		RectF CFormStyleSolid::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		float CFormStyleSolid::getCaptionHeight() const
		{
			return m_fCaptionHeight;
		}

		PointF CFormStyleSolid::getCaptionPadding() const
		{
			return m_sCaptionPadding;
		}

		BorderColor CFormStyleSolid::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CFormStyleSolid::getCaptionBackgroundColor() const
		{
			return m_sCaptionBackgroundColor;
		}

		TextAlign CFormStyleSolid::getCaptionAlign() const
		{
			return m_eCaptionAlign;
		}

		bool CFormStyleSolid::isBtnMinimizeVisible() const
		{
			return m_sBtnMinimize.Visible;
		}

		bool CFormStyleSolid::isBtnMinimizeEnabled() const
		{
			return m_sBtnMinimize.Enabled;
		}

		RectF CFormStyleSolid::getBtnMinimizeBorderWidth(const ButtonState state) const
		{
			return m_sBtnMinimize.BorderWidth[(int)state];
		}

		RectF CFormStyleSolid::getBtnMinimizeBorderRadius(const ButtonState state) const
		{
			return m_sBtnMinimize.BorderRadius[(int)state];
		}

		BorderColor CFormStyleSolid::getBtnMinimizeBorderColor(const ButtonState state) const
		{
			return m_sBtnMinimize.BorderColor[(int)state];
		}

		Color CFormStyleSolid::getBtnMinimizeBackgroundColor(const ButtonState state) const
		{
			return m_sBtnMinimize.BackgroundColor[(int)state];
		}

		bool CFormStyleSolid::isBtnRestoreVisible() const
		{
			return m_sBtnRestore.Visible;
		}

		bool CFormStyleSolid::isBtnRestoreEnabled() const
		{
			return m_sBtnRestore.Enabled;
		}

		RectF CFormStyleSolid::getBtnRestoreBorderWidth(const ButtonState state) const
		{
			return m_sBtnRestore.BorderWidth[(int)state];
		}

		RectF CFormStyleSolid::getBtnRestoreBorderRadius(const ButtonState state) const
		{
			return m_sBtnRestore.BorderRadius[(int)state];
		}

		BorderColor CFormStyleSolid::getBtnRestoreBorderColor(const ButtonState state) const
		{
			return m_sBtnRestore.BorderColor[(int)state];
		}

		Color CFormStyleSolid::getBtnRestoreBackgroundColor(const ButtonState state) const
		{
			return m_sBtnRestore.BackgroundColor[(int)state];
		}

		bool CFormStyleSolid::isBtnCloseVisible() const
		{
			return m_sBtnClose.Visible;
		}

		bool CFormStyleSolid::isBtnCloseEnabled() const
		{
			return m_sBtnClose.Enabled;
		}

		RectF CFormStyleSolid::getBtnCloseBorderWidth(const ButtonState state) const
		{
			return m_sBtnClose.BorderWidth[(int)state];
		}

		RectF CFormStyleSolid::getBtnCloseBorderRadius(const ButtonState state) const
		{
			return m_sBtnClose.BorderRadius[(int)state];
		}

		BorderColor CFormStyleSolid::getBtnCloseBorderColor(const ButtonState state) const
		{
			return m_sBtnClose.BorderColor[(int)state];
		}

		Color CFormStyleSolid::getBtnCloseBackgroundColor(const ButtonState state) const
		{
			return m_sBtnClose.BackgroundColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CFormStyleSolid::setShowCaption(const bool value)
		{
			if (value != m_bShowCaption)
			{
				m_bShowCaption = value;
				if (m_pCanvasHeader)
					m_pCanvasHeader->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setCaptionHeight(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCaptionHeight))
			{
				m_fCaptionHeight = value;
				if (m_pCanvasHeader)
					m_pCanvasHeader->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setCaptionPadding(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sCaptionPadding))
			{
				m_sCaptionPadding = value;
				if (m_bShowCaption)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sBorderWidth = value;
				if (getForm())
					getForm()->setBorderWidth(m_sBorderWidth);
				if (m_pCanvasHeader)
					m_pCanvasHeader->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBorderColor(const BorderColor &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
				if (m_pCanvasHeader)
					m_pCanvasHeader->setValid(false);
				if (m_sBorderWidth.has_positive())
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setCaptionBackgroundColor(const Color &value)
		{
			if (value != m_sCaptionBackgroundColor)
			{
				m_sCaptionBackgroundColor = value;
				if (m_pCanvasHeader)
					m_pCanvasHeader->setValid(false);
				if (m_sBorderWidth.has_positive())
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setCaptionAlign(const TextAlign value)
		{
			if (value != m_eCaptionAlign)
			{
				m_eCaptionAlign = value;
				if (m_bShowCaption)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					if (m_sBorderWidth.has_positive())
						Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnMinimizeVisible(const bool value)
		{
			if (value != m_sBtnMinimize.Visible)
			{
				m_sBtnMinimize.Visible = value;
				if (m_pCanvasHeader)
					m_pCanvasHeader->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnMinimizeEnabled(const bool value)
		{
			if (value != m_sBtnMinimize.Enabled)
			{
				m_sBtnMinimize.Enabled = value;
				if (m_sBtnMinimize.Visible)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnMinimizeBorderWidth(const ButtonState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnMinimize.BorderWidth[(int)state]))
			{
				m_sBtnMinimize.BorderWidth[(int)state] = value;
				if (m_sBtnMinimize.Visible && getBtnMinimizeState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnMinimizeBorderRadius(const ButtonState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnMinimize.BorderRadius[(int)state]))
			{
				m_sBtnMinimize.BorderRadius[(int)state] = value;
				if (m_sBtnMinimize.Visible && getBtnMinimizeState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnMinimizeBorderColor(const ButtonState state, const BorderColor &value)
		{
			if (value != m_sBtnMinimize.BorderColor[(int)state])
			{
				m_sBtnMinimize.BorderColor[(int)state] = value;
				if (m_sBtnMinimize.Visible && getBtnMinimizeState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnMinimizeBackgroundColor(const ButtonState state, const Color &value)
		{
			if (value != m_sBtnMinimize.BackgroundColor[(int)state])
			{
				m_sBtnMinimize.BackgroundColor[(int)state] = value;
				if (m_sBtnMinimize.Visible && getBtnMinimizeState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnRestoreVisible(const bool value)
		{
			if (value != m_sBtnRestore.Visible)
			{
				m_sBtnRestore.Visible = value;
				if (m_pCanvasHeader)
					m_pCanvasHeader->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnRestoreEnabled(const bool value)
		{
			if (value != m_sBtnRestore.Enabled)
			{
				m_sBtnRestore.Enabled = value;
				if (m_sBtnRestore.Visible)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnRestoreBorderWidth(const ButtonState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnRestore.BorderWidth[(int)state]))
			{
				m_sBtnRestore.BorderWidth[(int)state] = value;
				if (m_sBtnRestore.Visible && getBtnRestoreState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnRestoreBorderRadius(const ButtonState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnRestore.BorderRadius[(int)state]))
			{
				m_sBtnRestore.BorderRadius[(int)state] = value;
				if (m_sBtnRestore.Visible && getBtnRestoreState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnRestoreBorderColor(const ButtonState state, const BorderColor &value)
		{
			if (value != m_sBtnRestore.BorderColor[(int)state])
			{
				m_sBtnRestore.BorderColor[(int)state] = value;
				if (m_sBtnRestore.Visible && getBtnRestoreState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnRestoreBackgroundColor(const ButtonState state, const Color &value)
		{
			if (value != m_sBtnRestore.BackgroundColor[(int)state])
			{
				m_sBtnRestore.BackgroundColor[(int)state] = value;
				if (m_sBtnRestore.Visible && getBtnRestoreState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnCloseVisible(const bool value)
		{
			if (value != m_sBtnClose.Visible)
			{
				m_sBtnClose.Visible = value;
				if (m_pCanvasHeader)
					m_pCanvasHeader->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnCloseEnabled(const bool value)
		{
			if (value != m_sBtnClose.Enabled)
			{
				m_sBtnClose.Enabled = value;
				if (m_sBtnClose.Visible)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnCloseBorderWidth(const ButtonState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnClose.BorderWidth[(int)state]))
			{
				m_sBtnClose.BorderWidth[(int)state] = value;
				if (m_sBtnClose.Visible && getBtnCloseState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnCloseBorderRadius(const ButtonState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnClose.BorderRadius[(int)state]))
			{
				m_sBtnClose.BorderRadius[(int)state] = value;
				if (m_sBtnClose.Visible && getBtnCloseState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnCloseBorderColor(const ButtonState state, const BorderColor &value)
		{
			if (value != m_sBtnClose.BorderColor[(int)state])
			{
				m_sBtnClose.BorderColor[(int)state] = value;
				if (m_sBtnClose.Visible && getBtnCloseState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::setBtnCloseBackgroundColor(const ButtonState state, const Color &value)
		{
			if (value != m_sBtnClose.BackgroundColor[(int)state])
			{
				m_sBtnClose.BackgroundColor[(int)state] = value;
				if (m_sBtnClose.Visible && getBtnCloseState() == state)
				{
					if (m_pCanvasHeader)
						m_pCanvasHeader->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CFormStyleSolid::UpdateFromStyle(IStyle *style)
		{
			style->getOption(m_sClassName + L".BorderColor", m_sBorderColor);
			for (int i = 0; i <= (int)ButtonState::Disabled; i++)
			{
				String state;
				switch ((ButtonState)i)
				{
				case ButtonState::Hovered:
					state = L"Hovered";
					break;
				case ButtonState::Active:
					state = L"Active";
					break;
				case ButtonState::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".BtnMinimize.BorderWidth[" + state + L"]", m_sBtnMinimize.BorderWidth[i]);
				style->getOption(m_sClassName + L".BtnMinimize.BorderRadius[" + state + L"]", m_sBtnMinimize.BorderRadius[i]);
				style->getOption(m_sClassName + L".BtnMinimize.BorderColor[" + state + L"]", m_sBtnMinimize.BorderColor[i]);
				style->getOption(m_sClassName + L".BtnMinimize.BackgroundColor[" + state + L"]", m_sBtnMinimize.BackgroundColor[i]);
				style->getOption(m_sClassName + L".BtnRestore.BorderWidth[" + state + L"]", m_sBtnRestore.BorderWidth[i]);
				style->getOption(m_sClassName + L".BtnRestore.BorderRadius[" + state + L"]", m_sBtnRestore.BorderRadius[i]);
				style->getOption(m_sClassName + L".BtnRestore.BorderColor[" + state + L"]", m_sBtnRestore.BorderColor[i]);
				style->getOption(m_sClassName + L".BtnRestore.BackgroundColor[" + state + L"]", m_sBtnRestore.BackgroundColor[i]);
				style->getOption(m_sClassName + L".BtnClose.BorderWidth[" + state + L"]", m_sBtnClose.BorderWidth[i]);
				style->getOption(m_sClassName + L".BtnClose.BorderRadius[" + state + L"]", m_sBtnClose.BorderRadius[i]);
				style->getOption(m_sClassName + L".BtnClose.BorderColor[" + state + L"]", m_sBtnClose.BorderColor[i]);
				style->getOption(m_sClassName + L".BtnClose.BackgroundColor[" + state + L"]", m_sBtnClose.BackgroundColor[i]);
			}
		}

		CFormStyleSolid::ButtonState CFormStyleSolid::getBtnMinimizeState()
		{
			if (!m_sBtnMinimize.Enabled)
				return ButtonState::Disabled;
			if (m_eDown == Element::BtnMinimize)
				return ButtonState::Active;
			if (m_eHovered == Element::BtnMinimize)
				return ButtonState::Hovered;
			return ButtonState::Normal;
		}

		CFormStyleSolid::ButtonState CFormStyleSolid::getBtnRestoreState()
		{
			if (!m_sBtnRestore.Enabled)
				return ButtonState::Disabled;
			if (m_eDown == Element::BtnRestore)
				return ButtonState::Active;
			if (m_eHovered == Element::BtnRestore)
				return ButtonState::Hovered;
			return ButtonState::Normal;
		}

		CFormStyleSolid::ButtonState CFormStyleSolid::getBtnCloseState()
		{
			if (!m_sBtnClose.Enabled)
				return ButtonState::Disabled;
			if (m_eDown == Element::BtnClose)
				return ButtonState::Active;
			if (m_eHovered == Element::BtnClose)
				return ButtonState::Hovered;
			return ButtonState::Normal;
		}

		CFormStyleSolid::Element CFormStyleSolid::getElement(const PointF &pos)
		{
			Rect client{ getForm()->getClientRect() };
			float h{ m_sBorderWidth.Top + m_fCaptionHeight };
			if (pos.X < (float)client.Left || pos.X >= (float)client.Right || pos.Y < (float)client.Top || pos.Y >= (float)client.Bottom ||
				(pos.X >= (float)client.Left + m_sBorderWidth.Left && pos.X < (float)client.Right - m_sBorderWidth.Right && pos.Y >= (float)client.Top + h && pos.Y < (float)client.Bottom - m_sBorderWidth.Bottom))
				return Element::None;
			if (pos.X < (float)client.Left + m_sBorderWidth.Left && pos.Y < (float)client.Top + h)
				return Element::LeftTopCorner;
			if (pos.X >= (float)client.Right - m_sBorderWidth.Right && pos.Y < (float)client.Top + h)
				return Element::RightTopCorner;
			if (pos.X < (float)client.Left + m_sBorderWidth.Left && pos.Y >= (float)client.Bottom - m_sBorderWidth.Bottom)
				return Element::LeftBottomCorner;
			if (pos.X >= (float)client.Right - m_sBorderWidth.Right && pos.Y >= (float)client.Bottom - m_sBorderWidth.Bottom)
				return Element::RightBottomCorner;
			if (pos.X < (float)client.Left + m_sBorderWidth.Left)
				return Element::LeftBorder;
			if (pos.X >= (float)client.Right - m_sBorderWidth.Right)
				return Element::RightBorder;
			if (pos.Y >= (float)client.Bottom - m_sBorderWidth.Bottom)
				return Element::BottomBorder;
			if (m_sBtnClose.Visible && pos.Y < (float)client.Top + h && pos.X >= (float)client.Right - h - m_sBorderWidth.Right && pos.X < (float)client.Right - m_sBorderWidth.Right)
				return Element::BtnClose;
			if (m_sBtnRestore.Visible && pos.Y < (float)client.Top + h)
			{
				float x{ (float)client.Right - h - m_sBorderWidth.Right };
				if (m_sBtnClose.Visible)
					x -= h;
				if (pos.X >= x && pos.X < x + h)
					return Element::BtnRestore;
			}
			if (m_sBtnMinimize.Visible && pos.Y < (float)client.Top + h)
			{
				float x{ (float)client.Right - h - m_sBorderWidth.Right };
				if (m_sBtnClose.Visible)
					x -= h;
				if (m_sBtnRestore.Visible)
					x -= h;
				if (pos.X >= x && pos.X < x + h)
					return Element::BtnMinimize;
			}
			if (pos.Y < (float)client.Top + m_sBorderWidth.Top)
				return Element::TopBorder;
			return Element::Header;
		}

		bool CFormStyleSolid::UpdateHoveredElement(const PointF &position)
		{
			Element el{ getElement(position) };
			if (el != m_eHovered)
			{
				m_eHovered = el;
				return true;
			}
			return false;
		}

		bool CFormStyleSolid::DownAllowed()
		{
			switch (m_eHovered)
			{
			case Element::LeftBorder:
			case Element::TopBorder:
			case Element::RightBorder:
			case Element::BottomBorder:
			case Element::LeftTopCorner:
			case Element::RightTopCorner:
			case Element::LeftBottomCorner:
			case Element::RightBottomCorner:
			case Element::Header:
				return true;
			case Element::BtnMinimize:
				return m_sBtnMinimize.Enabled;
			case Element::BtnRestore:
				return m_sBtnRestore.Enabled;
			case Element::BtnClose:
				return m_sBtnClose.Enabled;
			default:
				return false;
			}
		}

		ITexture *CFormStyleSolid::FindIcon(IRenderer *renderer, const String &name, RectF &part)
		{
			IStyle *style{ getStyle() };
			if (style)
			{
				IStyleSkin *skin{ style->getSkin(name) };
				if (skin)
				{
					part = skin->Rect;
					return renderer->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			if (style != Application->Styles->getStyle(0) && (style = Application->Styles->getStyle(0)))
			{
				IStyleSkin *skin{ style->getSkin(name) };
				if (skin)
				{
					part = skin->Rect;
					return renderer->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			return nullptr;
		}
	#pragma endregion

	#pragma region Paint
		void CFormStyleSolid::Render()
		{
			Rect client{ getForm()->getClientRect() };
			if (!client.is_empty())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				if (PrepareCanvas(renderer, &m_pCanvasHeader, (float)client.width(), m_sBorderWidth.Top + m_fCaptionHeight))
				{
					CStoreTarget s_target{ renderer };
					renderer
						->ActivateTarget(m_pCanvasHeader)
						->Clear(Color{ 0, 0, 0, 0 });

					float x{ (float)client.Right - m_sBorderWidth.Right - m_sBorderWidth.Top - m_fCaptionHeight };
					RenderCaption(renderer);
					RenderBtn(renderer, m_sBtnClose, getBtnCloseState(), L"BtnClose", x);
					RenderBtn(renderer, m_sBtnRestore, getBtnRestoreState(), getForm()->getState() == WindowState::Maximized ? L"BtnRestore" : L"BtnMaximize", x);
					RenderBtn(renderer, m_sBtnMinimize, getBtnMinimizeState(), L"BtnMinimize", x);
					
					m_pCanvasHeader->setValid(true);
				}

				if (m_sBorderWidth.has_positive() || ntl::IsGreater<float>(m_fCaptionHeight, 0))
				{
					renderer->DrawBlock(
						(RectF)client,
						RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, m_sBorderWidth.Right, m_sBorderWidth.Bottom },
						RectF{ 0, 0, 0, 0 },
						BlockColors{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } });
				}
				if (m_pCanvasHeader)
					renderer->DrawImage(m_pCanvasHeader, 1);
			}
		}

		void CFormStyleSolid::RenderCaption(IRenderer *renderer)
		{
			if (m_sCaptionBackgroundColor.A > 0 && ntl::IsGreater<float>(m_fCaptionHeight, 0))
				renderer->DrawRectangle(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, (float)getForm()->getClientWidth() - m_sBorderWidth.Right, m_sBorderWidth.Top + m_fCaptionHeight }, m_sCaptionBackgroundColor);
			if (m_bShowCaption && getFont() && getFont()->Color.A > 0)
			{
				String caption{ getForm()->getCaption() };
				if (!caption.empty())
				{
					IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
					if (pf)
					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						PointF size{ pf->getStringSize(caption, getFont()->Distance) };
						float x;
						switch (m_eCaptionAlign)
						{
						case TextAlign::Center:
							x = (float)getForm()->getClientRect().Right - m_sBorderWidth.Right - m_sCaptionPadding.Y;
							if (m_sBtnClose.Visible)
								x -= m_sBorderWidth.Top + m_fCaptionHeight;
							if (m_sBtnRestore.Visible)
								x -= m_sBorderWidth.Top + m_fCaptionHeight;
							if (m_sBtnMinimize.Visible)
								x -= m_sBorderWidth.Top + m_fCaptionHeight;
							x = std::round((x + m_sBorderWidth.Left + m_sCaptionPadding.X - size.X) * 0.5f);
							break;
						case TextAlign::Right:
							x = (float)getForm()->getClientRect().Right - m_sBorderWidth.Right;
							if (m_sBtnClose.Visible)
								x -= m_sBorderWidth.Top + m_fCaptionHeight;
							if (m_sBtnRestore.Visible)
								x -= m_sBorderWidth.Top + m_fCaptionHeight;
							if (m_sBtnMinimize.Visible)
								x -= m_sBorderWidth.Top + m_fCaptionHeight;
							x = std::round(x - size.X - m_sCaptionPadding.Y);
							break;
						default:
							x = std::round(m_sBorderWidth.Left + m_sCaptionPadding.X);
							break;
						}
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x, std::round(m_sBorderWidth.Top + (m_fCaptionHeight - size.Y) / 2), 0))
							->DrawText(caption, pf, getFont()->Distance, getFont()->Color);
					}
				}
			}
		}

		void CFormStyleSolid::RenderBtn(IRenderer *renderer, const BUTTON &btn, const ButtonState state, const String &name, float &x)
		{
			if (btn.Visible)
			{
				float h{ m_sBorderWidth.Top + m_fCaptionHeight };
				// Background
				if (btn.BorderWidth[(int)state].has_positive())
				{
					renderer->DrawBlock(
						RectF{ x, 0, x + h, h },
						btn.BorderWidth[(int)state],
						btn.BorderRadius[(int)state],
						BlockColors{
							btn.BorderColor[(int)state].Left,
							btn.BorderColor[(int)state].Top,
							btn.BorderColor[(int)state].Right,
							btn.BorderColor[(int)state].Bottom,
							btn.BackgroundColor[(int)state], Color{ 0, 0, 0, 0 } });
				}
				else if (btn.BackgroundColor[(int)state].A > 0)
					renderer->DrawRectangle(RectF{ x, 0, x + h, x + h }, btn.BackgroundColor[(int)state]);
				// Icon
				RectF part;
				ITexture *icon{ FindIcon(renderer, m_sClassName + L"." + name + (state == ButtonState::Disabled ? L"[Disabled]" : L"[Normal]"), part) };
				if (icon)
				{
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x + (h - part.width()) / 2, (h - part.height()) / 2, 0))
						->DrawImage(icon, 1, part);
				}
				x -= h;
			}
		}
	#pragma endregion
	}
}