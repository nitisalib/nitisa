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
		CToolBar::CGradientListener::CGradientListener(CToolBar *control) :
			m_pControl{ control }
		{

		}

		void CToolBar::CGradientListener::NotifyOnChange()
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
		CToolBar::CToolBar() :
			CControl(L"ToolBar", true, true, true, false, false, false),
			m_cGradientListener{ this },
			m_eAlignTo{ AlignTo::Left },
			m_fDistance{ 2 },
			m_sPadding{ 2, 2, 2, 2 },
			m_sBorderWidth{ 0, 1, 0, 1 },
			m_sBorderColor{ Color{ 0, 0, 0, 0 }, Color{ 255, 255, 255, 255 }, Color{ 0, 0, 0, 0 }, Color{ 255, 255, 255, 255 } },
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_fScrollerSize{ 10 },
			m_fScrollerArrowSize{ 0.6f },
			m_aScrollerBorderWidth{
				RectF{ 0, 0, 0, 0 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 0, 0, 0, 0 } },
			m_aScrollerBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aScrollerBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aScrollerBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aScrollerArrowColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 100, 255 },
				Color{ 0, 0, 200, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 127, 127, 127, 255 } },
			m_fScrollInterval{ ScrollInterval },
			m_fScrollDeltaTimer{ 10 },
			m_fScrollDeltaWheel{ 10 },
			m_bUseMask{ true },
			m_bIgnoreGradient{ false },
			m_pCanvas{ nullptr },
			m_pMask{ nullptr },
			m_fScroll{ 0 },
			m_fScrollMax{ 0 },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None }
		{
			setService(new CToolBarService(this), true);
			setSize(PointF{ 185, 38 });
		}

		CToolBar::CToolBar(IForm *parent) : CToolBar()
		{
			setForm(parent);
		}

		CToolBar::CToolBar(IControl *parent) : CToolBar()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		IControl *CToolBar::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CToolBar::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CToolBar::getControl(const PointF &position) // Check if position is over scrollers first
		{
			IControl *result{ CControl::getControl(position) };
			if (result && result != this)
			{
				Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f{ position.X, position.Y, 0, 1 } };
				RectF client{ getClientRect() };
				if (v.X < client.Left || v.X >= client.Right || v.Y < client.Top || v.Y >= client.Bottom)
					result = this;
			}
			return result;
		}

		RectF CToolBar::getClientRect()
		{
			RectF result{
				m_sBorderWidth.Left + m_sPadding.Left,
				m_sBorderWidth.Top + m_sPadding.Top,
				getWidth() - m_sBorderWidth.Right - m_sPadding.Right,
				getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom };
			if (ntl::IsGreater<float>(m_fScrollMax, 0))
			{
				result.Left += m_fScrollerSize;
				result.Right -= m_fScrollerSize;
			}
			result.validate();
			return result;
		}

		IToolBar::AlignTo CToolBar::getAlignTo()
		{
			return m_eAlignTo;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CToolBar::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_fDistance *= s.X;
				m_sPadding *= s;
				m_sBorderWidth *= s;
				m_fScrollerSize *= s.X;
				for (int i = 0; i <= (int)ScrollerState::Disabled; i++)
					m_aScrollerBorderWidth[i] *= s;
				m_fScrollDeltaTimer *= avg;
				m_fScrollDeltaWheel *= avg;
				QueryService()->AlignControls();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CToolBar::setAlignTo(const AlignTo value)
		{
			if (value != m_eAlignTo)
			{
				CLockRepaint lock{ this };
				m_eAlignTo = value;
				QueryService()->AlignControls();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		float CToolBar::getDistance() const
		{
			return m_fDistance;
		}

		RectF CToolBar::getPadding() const
		{
			return m_sPadding;
		}

		RectF CToolBar::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		BorderColor CToolBar::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CToolBar::getLeftBorderColor() const
		{
			return m_sBorderColor.Left;
		}

		Color CToolBar::getTopBorderColor() const
		{
			return m_sBorderColor.Top;
		}

		Color CToolBar::getRightBorderColor() const
		{
			return m_sBorderColor.Right;
		}

		Color CToolBar::getBottomBorderColor() const
		{
			return m_sBorderColor.Bottom;
		}

		Color CToolBar::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CToolBar::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		float CToolBar::getScrollerSize() const
		{
			return m_fScrollerSize;
		}

		float CToolBar::getScrollerArrowSize() const
		{
			return m_fScrollerArrowSize;
		}

		RectF CToolBar::getScrollerBorderWidth(const ScrollerState state) const
		{
			return m_aScrollerBorderWidth[(int)state];
		}

		BorderColor CToolBar::getScrollerBorderColor(const ScrollerState state) const
		{
			return m_aScrollerBorderColor[(int)state];
		}

		Color CToolBar::getScrollerLeftBorderColor(const ScrollerState state) const
		{
			return m_aScrollerBorderColor[(int)state].Left;
		}

		Color CToolBar::getScrollerTopBorderColor(const ScrollerState state) const
		{
			return m_aScrollerBorderColor[(int)state].Top;
		}

		Color CToolBar::getScrollerRightBorderColor(const ScrollerState state) const
		{
			return m_aScrollerBorderColor[(int)state].Right;
		}

		Color CToolBar::getScrollerBottomBorderColor(const ScrollerState state) const
		{
			return m_aScrollerBorderColor[(int)state].Bottom;
		}

		Color CToolBar::getScrollerBackgroundColor(const ScrollerState state) const
		{
			return m_aScrollerBackgroundColor[(int)state];
		}

		Gradient *CToolBar::getScrollerBackgroundGradient(const ScrollerState state)
		{
			return &m_aScrollerBackgroundGradient[(int)state];
		}

		Color CToolBar::getScrollerArrowColor(const ScrollerState state) const
		{
			return m_aScrollerArrowColor[(int)state];
		}

		float CToolBar::getScrollInterval() const
		{
			return m_fScrollInterval;
		}

		float CToolBar::getScrollDeltaTimer() const
		{
			return m_fScrollDeltaTimer;
		}

		float CToolBar::getScrollDeltaWheel() const
		{
			return m_fScrollDeltaWheel;
		}

		bool CToolBar::isUseMask() const
		{
			return m_bUseMask;
		}

		bool CToolBar::isAcceptBubbledEvents()
		{
			return true;
		}
	#pragma endregion

	#pragma region Setters
		bool CToolBar::setDistance(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDistance))
			{
				CLockRepaint lock{ this };
				m_fDistance = value;
				QueryService()->AlignControls();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CToolBar::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				CLockRepaint lock{ this };
				m_sPadding = value;
				QueryService()->AlignControls();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CToolBar::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sBorderWidth = value;
				QueryService()->AlignControls();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CToolBar::setBorderColor(const BorderColor &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
				if (m_sBorderWidth.has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CToolBar::setLeftBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ value, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CToolBar::setTopBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, value, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CToolBar::setRightBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, value, m_sBorderColor.Bottom });
		}

		bool CToolBar::setBottomBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, value });
		}

		bool CToolBar::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CToolBar::setScrollerSize(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollerSize))
			{
				m_fScrollerSize = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					CLockRepaint lock{ this };
					QueryService()->AlignControls();
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CToolBar::setScrollerArrowSize(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsLessOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fScrollerArrowSize))
			{
				m_fScrollerArrowSize = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CToolBar::setScrollerBorderWidth(const ScrollerState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aScrollerBorderWidth[(int)state]))
			{
				m_aScrollerBorderWidth[(int)state] = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CToolBar::setScrollerBorderColor(const ScrollerState state, const BorderColor &value)
		{
			if (value != m_aScrollerBorderColor[(int)state])
			{
				m_aScrollerBorderColor[(int)state] = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CToolBar::setScrollerLeftBorderColor(const ScrollerState state, const Color &value)
		{
			return setScrollerBorderColor(state, BorderColor{ value, m_aScrollerBorderColor[(int)state].Top, m_aScrollerBorderColor[(int)state].Right, m_aScrollerBorderColor[(int)state].Bottom });
		}

		bool CToolBar::setScrollerTopBorderColor(const ScrollerState state, const Color &value)
		{
			return setScrollerBorderColor(state, BorderColor{ m_aScrollerBorderColor[(int)state].Left, value, m_aScrollerBorderColor[(int)state].Right, m_aScrollerBorderColor[(int)state].Bottom });
		}

		bool CToolBar::setScrollerRightBorderColor(const ScrollerState state, const Color &value)
		{
			return setScrollerBorderColor(state, BorderColor{ m_aScrollerBorderColor[(int)state].Left, m_aScrollerBorderColor[(int)state].Top, value, m_aScrollerBorderColor[(int)state].Bottom });
		}

		bool CToolBar::setScrollerBottomBorderColor(const ScrollerState state, const Color &value)
		{
			return setScrollerBorderColor(state, BorderColor{ m_aScrollerBorderColor[(int)state].Left, m_aScrollerBorderColor[(int)state].Top, m_aScrollerBorderColor[(int)state].Right, value });
		}

		bool CToolBar::setScrollerBackgroundColor(const ScrollerState state, const Color &value)
		{
			if (value != m_aScrollerBackgroundColor[(int)state])
			{
				m_aScrollerBackgroundColor[(int)state] = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CToolBar::setScrollerArrowColor(const ScrollerState state, const Color &value)
		{
			if (value != m_aScrollerArrowColor[(int)state])
			{
				m_aScrollerArrowColor[(int)state] = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CToolBar::setScrollInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
			{
				m_fScrollInterval = value;
				return true;
			}
			return false;
		}

		bool CToolBar::setScrollDeltaTimer(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollDeltaTimer))
			{
				m_fScrollDeltaTimer = value;
				return true;
			}
			return false;
		}

		bool CToolBar::setScrollDeltaWheel(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollDeltaWheel))
			{
				m_fScrollDeltaWheel = value;
				return true;
			}
			return false;
		}

		bool CToolBar::setUseMask(const bool value)
		{
			if (value != m_bUseMask)
			{
				m_bUseMask = value;
				Repaint(true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CToolBar::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			CControl::Refresh(refresh_children);
		}

		CToolBar::ScrollerState CToolBar::getLeftScrollerState()
		{
			if ((m_eAlignTo == AlignTo::Left && ntl::IsLessOrEqual<float>(m_fScroll, 0)) || (m_eAlignTo == AlignTo::Right && ntl::IsGreaterOrEqual<float>(m_fScroll, m_fScrollMax)))
				return ScrollerState::Disabled;
			if (m_eDownElement == Element::LeftScroller)
			{
				if (m_eHoveredElement == Element::LeftScroller)
					return ScrollerState::ActiveHovered;
				return ScrollerState::Active;
			}
			if (m_eHoveredElement == Element::LeftScroller)
				return ScrollerState::Hovered;
			return ScrollerState::Normal;
		}

		CToolBar::ScrollerState CToolBar::getRightScrollerState()
		{
			if ((m_eAlignTo == AlignTo::Right && ntl::IsLessOrEqual<float>(m_fScroll, 0)) || (m_eAlignTo == AlignTo::Left && ntl::IsGreaterOrEqual<float>(m_fScroll, m_fScrollMax)))
				return ScrollerState::Disabled;
			if (m_eDownElement == Element::RightScroller)
			{
				if (m_eHoveredElement == Element::RightScroller)
					return ScrollerState::ActiveHovered;
				return ScrollerState::Active;
			}
			if (m_eHoveredElement == Element::RightScroller)
				return ScrollerState::Hovered;
			return ScrollerState::Normal;
		}

		RectF CToolBar::getLeftScrollerRect()
		{
			return RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, m_sBorderWidth.Left + m_fScrollerSize, getHeight() - m_sBorderWidth.Bottom };
		}

		RectF CToolBar::getRightScrollerRect()
		{
			return RectF{ getWidth() - m_sBorderWidth.Right - m_fScrollerSize, m_sBorderWidth.Top, getWidth() - m_sBorderWidth.Right, getHeight() - m_sBorderWidth.Bottom };
		}

		bool CToolBar::UpdateHoveredElement(const PointF &position)
		{
			Element new_element{ Element::None };
			if (ntl::IsGreater<float>(m_fScrollMax, 0) && position.Y >= 0 && position.Y < getHeight())
			{
				if (position.X >= 0 && position.X < m_sBorderWidth.Left + m_fScrollerSize)
					new_element = Element::LeftScroller;
				else if (position.X >= getWidth() - m_sBorderWidth.Right - m_fScrollerSize && position.X < getWidth())
					new_element = Element::RightScroller;
			}
			if (new_element != m_eHoveredElement)
			{
				m_eHoveredElement = new_element;
				return true;
			}
			return false;
		}

		void CToolBar::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".Distance", m_fDistance);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderColor", m_sBorderColor);
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".ScrollerSize", m_fScrollerSize);
			style->getOption(m_sClassName + L".ScrollerArrowSize", m_fScrollerArrowSize);
			for (int i = 0; i <= (int)ScrollerState::Disabled; i++)
			{
				String name;
				switch ((ScrollerState)i)
				{
				case ScrollerState::Normal:
					name = L"Normal";
					break;
				case ScrollerState::Hovered:
					name = L"Hovered";
					break;
				case ScrollerState::Active:
					name = L"Active";
					break;
				case ScrollerState::ActiveHovered:
					name = L"ActiveHovered";
					break;
				default:
					name = L"Disabled";
				}
				style->getOption(m_sClassName + L".ScrollerBorderWidth[" + name + L"]", m_aScrollerBorderWidth[i]);
				style->getOption(m_sClassName + L".ScrollerBorderColor[" + name + L"]", m_aScrollerBorderColor[i]);
				style->getOption(m_sClassName + L".ScrollerBackgroundColor[" + name + L"]", m_aScrollerBackgroundColor[i]);
				style->getOption(m_sClassName + L".ScrollerBackgroundGradient[" + name + L"]", m_aScrollerBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ScrollerArrowColor[" + name + L"]", m_aScrollerArrowColor[i]);
			}
			m_bIgnoreGradient = false;
			QueryService()->AlignControls();
		}
	#pragma endregion

	#pragma region Paint
		void CToolBar::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				DrawSimpleBackground(renderer, getRect(), m_sBorderWidth, RectF{ 0, 0, 0, 0 }, m_sBorderColor, m_sBackgroundColor, m_cBackgroundGradient);
				RenderScroller(renderer);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, matrix, m_pCanvas, PointF{ 0, 0 });
		}

		void CToolBar::RenderScroller(IRenderer *renderer)
		{
			if (ntl::IsGreater<float>(m_fScrollMax, 0) && getWidth() >= m_sBorderWidth.Left + m_sBorderWidth.Right + 2 * m_fScrollerSize && getHeight() >= m_sBorderWidth.Top + m_sBorderWidth.Bottom)
			{
				// Left scroller
				ScrollerState state{ getLeftScrollerState() };
				RectF rect{ getLeftScrollerRect() };
				DrawSimpleBackground(
					renderer,
					rect,
					m_aScrollerBorderWidth[(int)state],
					RectF{ 0, 0, 0, 0 },
					m_aScrollerBorderColor[(int)state],
					m_aScrollerBackgroundColor[(int)state],
					m_aScrollerBackgroundGradient[(int)state]);
				if (ntl::IsGreater<float>(m_fScrollerArrowSize, 0))
				{
					float w{ m_fScrollerSize * m_fScrollerArrowSize * 0.5f };
					PointF m{ (rect.Left + rect.Right) * 0.5f, (rect.Top + rect.Bottom) * 0.5f };
					renderer->DrawTriangle(PointF{ m.X - w, m.Y }, PointF{ m.X + w, m.Y - 2 * w }, PointF{ m.X + w, m.Y + 2 * w }, m_aScrollerArrowColor[(int)state]);
				}
				// Right scroller
				state = getRightScrollerState();
				rect = getRightScrollerRect();
				DrawSimpleBackground(
					renderer,
					rect,
					m_aScrollerBorderWidth[(int)state],
					RectF{ 0, 0, 0, 0 },
					m_aScrollerBorderColor[(int)state],
					m_aScrollerBackgroundColor[(int)state],
					m_aScrollerBackgroundGradient[(int)state]);
				if (ntl::IsGreater<float>(m_fScrollerArrowSize, 0))
				{
					float w{ m_fScrollerSize * m_fScrollerArrowSize * 0.5f };
					PointF m{ (rect.Left + rect.Right) * 0.5f, (rect.Top + rect.Bottom) * 0.5f };
					// Added 1 to be same size as left arrow
					renderer->DrawTriangle(PointF{ m.X + w, m.Y }, PointF{ m.X - w, m.Y + 2 * w + 1 }, PointF{ m.X - w, m.Y - 2 * w - 1 }, m_aScrollerArrowColor[(int)state]);
				}
			}
		}

		void CToolBar::RenderMask(IRenderer *renderer)
		{
			if (PrepareCanvas(renderer, &m_pMask, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMask)
					->Clear(Color{ 0, 0, 0, 0 })
					->DrawRectangle(getClientRect(), Color{ 0, 0, 0, 255 });
				m_pMask->setValid(true);
			}
		}
	#pragma endregion
	}
}