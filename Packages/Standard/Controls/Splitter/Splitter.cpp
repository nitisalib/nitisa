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
		CSplitter::CGradientListener::CGradientListener(CSplitter *control) :
			m_pControl{ control }
		{

		}

		void CSplitter::CGradientListener::NotifyOnChange()
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
		CSplitter::CSplitter() :
			CControl(L"Splitter", true, true, false, false, false, false),
			m_cGradientListener{ this },
			m_fDotWidth{ 1 },
			m_iDotCount{ 3 },
			m_aBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 100 },
				Color{ 0, 0, 0, 0 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener},
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aDotColor{
				Color{ 127, 127, 127, 255 },
				Color{ 127, 127, 127, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 127, 127, 127, 255 } },
			m_bIgnoreGradient{ false },
			m_pCanvas{ nullptr },
			m_bActive{ false }
		{
			setService(new CSplitterService(this), true);
			setAlign(Align::Top);
			setHeight(5);
			setCursor(CursorType::SizeNorthSouth);
		}

		CSplitter::CSplitter(IControl *parent) :CSplitter()
		{
			setParent(parent);
		}

		CSplitter::CSplitter(IForm *parent) : CSplitter()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSplitter::setAlign(const Align value)
		{
			if (value == Align::Top || value == Align::Bottom || value == Align::Left || value == Align::Right)
			{
				CLockRepaint lock{ this };
				float t{ (getAlign() == Align::Left || getAlign() == Align::Right) ? getWidth() : getHeight() };
				if (CControl::setAlign(value))
				{
					switch (getAlign())
					{
					case Align::Top:
					case Align::Bottom:
						setHeight(t);
						setCursor(CursorType::SizeNorthSouth);
						break;
					default:
						setWidth(t);
						setCursor(CursorType::SizeWestEast);
					}
					return true;
				}
			}
			return false;
		}

		bool CSplitter::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_fDotWidth *= (s.X + s.Y) * 0.5f;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CSplitter::State CSplitter::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_bActive)
				return State::Active;
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		float CSplitter::getDotWidth() const
		{
			return m_fDotWidth;
		}

		int CSplitter::getDotCount() const
		{
			return m_iDotCount;
		}

		Color CSplitter::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CSplitter::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CSplitter::getDotColor(const State state) const
		{
			return m_aDotColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CSplitter::setDotWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDotWidth))
			{
				m_fDotWidth = value;
				if (m_iDotCount > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSplitter::setDotCount(const int value)
		{
			if (value >= 0 && value != m_iDotCount)
			{
				m_iDotCount = value;
				if (ntl::IsGreater<float>(m_fDotWidth, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CSplitter::setBackgroundColor(const State state, const Color &value)
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

		bool CSplitter::setDotColor(const State state, const Color &value)
		{
			if (value != m_aDotColor[(int)state])
			{
				m_aDotColor[(int)state] = value;
				if (ntl::IsGreater<float>(m_fDotWidth, 0) && m_iDotCount > 0 && getState() == state)
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
		void CSplitter::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CSplitter::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".DotWidth", m_fDotWidth);
			style->getOption(m_sClassName + L".DotCount", m_iDotCount);
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String name;
				switch ((State)i)
				{
				case State::Hovered:
					name = L"Hovered";
					break;
				case State::Active:
					name = L"Active";
					break;
				case State::Disabled:
					name = L"Disabled";
					break;
				default:
					name = L"Normal";
				}
				style->getOption(m_sClassName + L".BackgroundColor[" + name + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + name + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".DotColor[" + name + L"]", m_aDotColor[i]);
			}
			m_bIgnoreGradient = false;
		}
	#pragma endregion

	#pragma region Paint
		void CSplitter::Render()
		{
			State state{ getState() };
			if ((m_iDotCount > 0 && ntl::IsGreater<float>(m_fDotWidth, 0)) || m_aBackgroundColor[(int)state].A > 0 || m_aBackgroundGradient[(int)state].getPointCount() > 1)
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
				{
					CStoreTarget s_target{ renderer };
					renderer
						->ActivateTarget(m_pCanvas)
						->Clear(Color{ 0, 0, 0, 0 });
					if (m_aBackgroundGradient[(int)state].getPointCount() > 1)
						renderer->DrawGradient(RectF{ 0, 0, getWidth(), getHeight() }, m_aBackgroundGradient[(int)state]);
					else if (m_aBackgroundColor[(int)state].A > 0)
						renderer->DrawRectangle(RectF{ 0, 0, getWidth(), getHeight() }, m_aBackgroundColor[(int)state]);
					if (m_iDotCount > 0 && ntl::IsGreater<float>(m_fDotWidth, 0) && m_aDotColor[(int)state].A > 0)
					{

						float w{ m_fDotWidth * float(2 * m_iDotCount - 1) };
						if (getAlign() == Align::Top || getAlign() == Align::Bottom)
						{
							float x{ (getWidth() - w) / 2 }, y{ (getHeight() - m_fDotWidth) / 2 };
							for (int i = 0; i < m_iDotCount; i++)
							{
								renderer->DrawRectangle(RectF{ x, y, x + m_fDotWidth, y + m_fDotWidth }, m_aDotColor[(int)state]);
								x += m_fDotWidth * 2;
							}
						}
						else
						{
							float y{ (getHeight() - w) / 2 }, x{ (getWidth() - m_fDotWidth) / 2 };
							for (int i = 0; i < m_iDotCount; i++)
							{
								renderer->DrawRectangle(RectF{ x, y, x + m_fDotWidth, y + m_fDotWidth }, m_aDotColor[(int)state]);
								y += m_fDotWidth * 2;
							}
						}
					}
					m_pCanvas->setValid(true);
				}
				DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
			}
		}
	#pragma endregion
	}
}