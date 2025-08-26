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
	namespace ide
	{
	#pragma region Constructor & destructor
		CViewH2H2::CViewH2H2() :
			CControl(L"ViewH2H2", true, true, true, false, false, false),
			m_bResizable{ true },
			m_fSeparatorV{ 0.5f },
			m_fSeparatorH1{ 0.3333f },
			m_fSeparatorH2{ 0.6667f },
			m_eActiveView{ View::None },
			m_fBorderWidth{ 2 },
			m_fSeparatorWidth{ 4 },
			m_aBorderColor{
				Color{ 0, 0, 0, 0 },
				Color{ 224, 214, 130 , 100 }
			},
			m_aSeparatorColor{
				Color{ 90, 90, 90, 255 },
				Color{ 61, 123, 173, 255 }
			},
			m_eDownElement{ Element::None },
			m_bAligningControls{ false }
		{
			setService(new CViewH2H2Service(this), true);
			setSize(PointF{ 640, 480 });
		}

		CViewH2H2::CViewH2H2(IForm *parent) :
			CViewH2H2()
		{
			setForm(parent);
		}

		CViewH2H2::CViewH2H2(IControl *parent) :
			CViewH2H2()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		CursorType CViewH2H2::getCursor()
		{
			if (getForm() && isEnabled(true) && m_bResizable)
			{
				PointF p{ FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				if (CalculateSeparatorVRect().is_inside(p))
					return CursorType::SizeNorthSouth;
				if (CalculateSeparatorH1Rect().is_inside(p))
					return CursorType::SizeWestEast;
				if (CalculateSeparatorH2Rect().is_inside(p))
					return CursorType::SizeWestEast;
			}
			return CControl::getCursor();
		}
	#pragma endregion

	#pragma region IViewControl methods
		bool CViewH2H2::ActivateView(const int index)
		{
			if (index < 0)
				return setActiveView(View::None);
			if (index == 0)
				return setActiveView(View::LeftTop);
			if (index == 1)
				return setActiveView(View::RightTop);
			if (index == 2)
				return setActiveView(View::LeftBottom);
			if (index == 3)
				return setActiveView(View::RightBottom);
			return false;
		}
	#pragma endregion

	#pragma region IViewH2H2 getters
		bool CViewH2H2::isResizable()
		{
			return m_bResizable;
		}

		float CViewH2H2::getSeparatorV()
		{
			return m_fSeparatorV;
		}

		float CViewH2H2::getSeparatorH1()
		{
			return m_fSeparatorH1;
		}

		float CViewH2H2::getSeparatorH2()
		{
			return m_fSeparatorH2;
		}
	#pragma endregion

	#pragma region IViewH2H2 setters
		bool CViewH2H2::setResizable(const bool value)
		{
			if (value != m_bResizable)
			{
				m_bResizable = value;
				return true;
			}
			return false;
		}

		bool CViewH2H2::setSeparatorV(const float value)
		{
			float v{ ntl::Clamp<float>(value, 0, 1) };
			if (ntl::IsNotEqual<float>(v, m_fSeparatorV, 0.0001f))
			{
				m_fSeparatorV = v;
				AlignControls();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CViewH2H2::setSeparatorH1(const float value)
		{
			float v{ ntl::Clamp<float>(value, 0, 1) };
			if (ntl::IsNotEqual<float>(v, m_fSeparatorH1, 0.0001f))
			{
				m_fSeparatorH1 = v;
				AlignControls();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CViewH2H2::setSeparatorH2(const float value)
		{
			float v{ ntl::Clamp<float>(value, 0, 1) };
			if (ntl::IsNotEqual<float>(v, m_fSeparatorH2, 0.0001f))
			{
				m_fSeparatorH2 = v;
				AlignControls();
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CViewH2H2::View CViewH2H2::getActiveView()
		{
			return m_eActiveView;
		}

		float CViewH2H2::getBorderWidth()
		{
			return m_fBorderWidth;
		}

		float CViewH2H2::getSeparatorWidth()
		{
			return m_fSeparatorWidth;
		}

		Color CViewH2H2::getBorderColor(const State state)
		{
			return m_aBorderColor[(int)state];
		}

		Color CViewH2H2::getSeparatorColor(const State state)
		{
			return m_aSeparatorColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CViewH2H2::setActiveView(const View value)
		{
			if (value != m_eActiveView)
			{
				m_eActiveView = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CViewH2H2::setBorderWidth(const float value)
		{
			float v{ ntl::Clamp<float>(value, 0, 16) };
			if (ntl::IsNotEqual<float>(v, m_fBorderWidth))
			{
				m_fBorderWidth = v;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CViewH2H2::setSeparatorWidth(const float value)
		{
			float v{ ntl::Clamp<float>(value, 0, 16) };
			if (ntl::IsNotEqual<float>(v, m_fSeparatorWidth))
			{
				m_fSeparatorWidth = v;
				AlignControls();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CViewH2H2::setBorderColor(const State state, const Color &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (state == State::Normal || m_eActiveView != View::None)
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CViewH2H2::setSeparatorColor(const State state, const Color &value)
		{
			if (value != m_aSeparatorColor[(int)state])
			{
				m_aSeparatorColor[(int)state] = value;
				if (state == State::Normal || m_eDownElement != Element::None)
					Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CViewH2H2::UpdateFromStyle(IStyle *style)
		{
			style->getOption(m_sClassName + L".BorderWidth", m_fBorderWidth);
			style->getOption(m_sClassName + L".SeparatorWidth", m_fSeparatorWidth);
			style->getOption(m_sClassName + L".BorderColor[Normal]", m_aBorderColor[(int)State::Normal]);
			style->getOption(m_sClassName + L".BorderColor[Active]", m_aBorderColor[(int)State::Active]);
			style->getOption(m_sClassName + L".SeparatorColor[Normal]", m_aSeparatorColor[(int)State::Normal]);
			style->getOption(m_sClassName + L".SeparatorColor[Active]", m_aSeparatorColor[(int)State::Active]);
			AlignControls();
		}

		void CViewH2H2::AlignControls()
		{
			if (!m_bAligningControls)
			{
				m_bAligningControls = true;
				RectF rect;
				IControl *control;
				if ((control = getControl(0)))
				{
					rect = CalculateLeftTopClientRect();
					control->setVisible(true);
					control->getTransform()->QueryService()->Transform(rect.Left, rect.Top, 0, 1, 1, 1, 0, 0, 0);
					if (IsNotEqual(PointF{ rect.width(), rect.height() }, control->getSize()))
					{
						control->QueryService()->setSize(PointF{ rect.width(), rect.height() });
						control->QueryService()->AlignControls();
						CNotifier::Resize(control);
					}
				}
				if ((control = getControl(1)))
				{
					rect = CalculateRightTopClientRect();
					control->setVisible(true);
					control->getTransform()->QueryService()->Transform(rect.Left, rect.Top, 0, 1, 1, 1, 0, 0, 0);
					if (IsNotEqual(PointF{ rect.width(), rect.height() }, control->getSize()))
					{
						control->QueryService()->setSize(PointF{ rect.width(), rect.height() });
						control->QueryService()->AlignControls();
						CNotifier::Resize(control);
					}
				}
				if ((control = getControl(2)))
				{
					rect = CalculateLeftBottomClientRect();
					control->setVisible(true);
					control->getTransform()->QueryService()->Transform(rect.Left, rect.Top, 0, 1, 1, 1, 0, 0, 0);
					if (IsNotEqual(PointF{ rect.width(), rect.height() }, control->getSize()))
					{
						control->QueryService()->setSize(PointF{ rect.width(), rect.height() });
						control->QueryService()->AlignControls();
						CNotifier::Resize(control);
					}
				}
				if ((control = getControl(3)))
				{
					rect = CalculateRightBottomClientRect();
					control->setVisible(true);
					control->getTransform()->QueryService()->Transform(rect.Left, rect.Top, 0, 1, 1, 1, 0, 0, 0);
					if (IsNotEqual(PointF{ rect.width(), rect.height() }, control->getSize()))
					{
						control->QueryService()->setSize(PointF{ rect.width(), rect.height() });
						control->QueryService()->AlignControls();
						CNotifier::Resize(control);
					}
				}
				m_bAligningControls = false;
			}
		}

		RectF CViewH2H2::CalculateSeparatorVRect()
		{
			if (ntl::IsZero<float>(m_fSeparatorWidth) || getHeight() <= m_fSeparatorWidth || ntl::IsZero<float>(getWidth()))
				return RectF{ 0, 0, 0, 0 };
			RectF result{ 0, std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f), getWidth(), 0 };
			result.Bottom = result.Top + m_fSeparatorWidth;
			return result;
		}

		RectF CViewH2H2::CalculateSeparatorH1Rect()
		{
			if (ntl::IsZero<float>(m_fSeparatorWidth) || getWidth() <= m_fSeparatorWidth || ntl::IsZero<float>(getHeight()))
				return RectF{ 0, 0, 0, 0 };
			RectF result{ std::round(getWidth() * m_fSeparatorH1 - m_fSeparatorWidth * 0.5f), 0, 0, std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f) };
			result.Right = result.Left + m_fSeparatorWidth;
			return result;
		}

		RectF CViewH2H2::CalculateSeparatorH2Rect()
		{
			if (ntl::IsZero<float>(m_fSeparatorWidth) || getWidth() <= m_fSeparatorWidth || ntl::IsZero<float>(getHeight()))
				return RectF{ 0, 0, 0, 0 };
			RectF result{ std::round(getWidth() * m_fSeparatorH2 - m_fSeparatorWidth * 0.5f), std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f) + m_fSeparatorWidth, 0, getHeight() };
			result.Right = result.Left + m_fSeparatorWidth;
			return result;
		}

		RectF CViewH2H2::CalculateLeftTopViewRect()
		{
			if (ntl::IsZero<float>(m_fBorderWidth) || ntl::IsZero<float>(getWidth()) || ntl::IsZero<float>(getHeight()))
				return RectF{ 0, 0, 0, 0 };
			RectF result{ 0, 0, std::round(getWidth() * m_fSeparatorH1 - m_fSeparatorWidth * 0.5f), std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f) };
			if (result.height() <= m_fBorderWidth * 2 || result.width() <= m_fBorderWidth * 2)
				return RectF{ 0, 0, 0, 0 };
			return result;
		}

		RectF CViewH2H2::CalculateRightTopViewRect()
		{
			if (ntl::IsZero<float>(m_fBorderWidth) || ntl::IsZero<float>(getWidth()) || ntl::IsZero<float>(getHeight()))
				return RectF{ 0, 0, 0, 0 };
			RectF result{ std::round(getWidth() * m_fSeparatorH1 - m_fSeparatorWidth * 0.5f) + m_fSeparatorWidth, 0, getWidth(), std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f) };
			if (result.height() <= m_fBorderWidth * 2 || result.width() <= m_fBorderWidth * 2)
				return RectF{ 0, 0, 0, 0 };
			return result;
		}

		RectF CViewH2H2::CalculateLeftBottomViewRect()
		{
			if (ntl::IsZero<float>(m_fBorderWidth) || ntl::IsZero<float>(getWidth()) || ntl::IsZero<float>(getHeight()))
				return RectF{ 0, 0, 0, 0 };
			RectF result{ 0, std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f) + m_fSeparatorWidth, std::round(getWidth() * m_fSeparatorH2 - m_fSeparatorWidth * 0.5f), getHeight() };
			if (result.height() <= m_fBorderWidth * 2 || result.width() <= m_fBorderWidth * 2)
				return RectF{ 0, 0, 0, 0 };
			return result;
		}

		RectF CViewH2H2::CalculateRightBottomViewRect()
		{
			if (ntl::IsZero<float>(m_fBorderWidth) || ntl::IsZero<float>(getWidth()) || ntl::IsZero<float>(getHeight()))
				return RectF{ 0, 0, 0, 0 };
			RectF result{ std::round(getWidth() * m_fSeparatorH2 - m_fSeparatorWidth * 0.5f) + m_fSeparatorWidth, std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f) + m_fSeparatorWidth, getWidth(), getHeight() };
			if (result.height() <= m_fBorderWidth * 2 || result.width() <= m_fBorderWidth * 2)
				return RectF{ 0, 0, 0, 0 };
			return result;
		}

		RectF CViewH2H2::CalculateLeftTopClientRect()
		{
			RectF result{ 0, 0, std::round(getWidth() * m_fSeparatorH1 - m_fSeparatorWidth * 0.5f), std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f) };
			result.validate();
			return result;
		}

		RectF CViewH2H2::CalculateRightTopClientRect()
		{
			RectF result{ std::round(getWidth() * m_fSeparatorH1 - m_fSeparatorWidth * 0.5f) + m_fSeparatorWidth, 0, getWidth(), std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f) };
			result.validate();
			return result;
		}

		RectF CViewH2H2::CalculateLeftBottomClientRect()
		{
			RectF result{ 0, std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f) + m_fSeparatorWidth, std::round(getWidth() * m_fSeparatorH2 - m_fSeparatorWidth * 0.5f), getHeight() };
			result.validate();
			return result;
		}

		RectF CViewH2H2::CalculateRightBottomClientRect()
		{
			RectF result{ std::round(getWidth() * m_fSeparatorH2 - m_fSeparatorWidth * 0.5f) + m_fSeparatorWidth, std::round(getHeight() * m_fSeparatorV - m_fSeparatorWidth * 0.5f) + m_fSeparatorWidth, getWidth(), getHeight() };
			result.validate();
			return result;
		}
	#pragma endregion

	#pragma region Render
		void CViewH2H2::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer->ActivatePrimitiveMatrix(getTransformMatrix());
			// SeparatorV
			RectF rect{ CalculateSeparatorVRect() * getRect() };
			if (!rect.is_zero())
			{
				if (m_eDownElement == Element::SeparatorV)
				{
					if (m_aSeparatorColor[(int)State::Active].A > 0)
						renderer->DrawRectangle(rect, m_aSeparatorColor[(int)State::Active]);
				}
				else
				{
					if (m_aSeparatorColor[(int)State::Normal].A > 0)
						renderer->DrawRectangle(rect, m_aSeparatorColor[(int)State::Normal]);
				}
			}
			// SeparatorH1
			rect = CalculateSeparatorH1Rect() * getRect();
			if (!rect.is_zero())
			{
				if (m_eDownElement == Element::SeparatorH1)
				{
					if (m_aSeparatorColor[(int)State::Active].A > 0)
						renderer->DrawRectangle(rect, m_aSeparatorColor[(int)State::Active]);
				}
				else
				{
					if (m_aSeparatorColor[(int)State::Normal].A > 0)
						renderer->DrawRectangle(rect, m_aSeparatorColor[(int)State::Normal]);
				}
			}
			// SeparatorH2
			rect = CalculateSeparatorH2Rect() * getRect();
			if (!rect.is_zero())
			{
				if (m_eDownElement == Element::SeparatorH2)
				{
					if (m_aSeparatorColor[(int)State::Active].A > 0)
						renderer->DrawRectangle(rect, m_aSeparatorColor[(int)State::Active]);
				}
				else
				{
					if (m_aSeparatorColor[(int)State::Normal].A > 0)
						renderer->DrawRectangle(rect, m_aSeparatorColor[(int)State::Normal]);
				}
			}
			// LeftTop view
			rect = CalculateLeftTopViewRect();
			if (!rect.is_zero())
			{
				if (m_eActiveView == View::LeftTop)
				{
					if (m_aBorderColor[(int)State::Active].A > 0)
					{
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top + m_fBorderWidth, rect.Left + m_fBorderWidth, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top, rect.Right, rect.Top + m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Right - m_fBorderWidth, rect.Top + m_fBorderWidth, rect.Right, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Bottom - m_fBorderWidth, rect.Right, rect.Bottom }, m_aBorderColor[(int)State::Active]);
					}
				}
				else
				{
					if (m_aBorderColor[(int)State::Normal].A > 0)
					{
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top + m_fBorderWidth, rect.Left + m_fBorderWidth, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top, rect.Right, rect.Top + m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Right - m_fBorderWidth, rect.Top + m_fBorderWidth, rect.Right, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Bottom - m_fBorderWidth, rect.Right, rect.Bottom }, m_aBorderColor[(int)State::Normal]);
					}
				}
			}
			// RightTop view
			rect = CalculateRightTopViewRect();
			if (!rect.is_zero())
			{
				if (m_eActiveView == View::RightTop)
				{
					if (m_aBorderColor[(int)State::Active].A > 0)
					{
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top + m_fBorderWidth, rect.Left + m_fBorderWidth, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top, rect.Right, rect.Top + m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Right - m_fBorderWidth, rect.Top + m_fBorderWidth, rect.Right, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Bottom - m_fBorderWidth, rect.Right, rect.Bottom }, m_aBorderColor[(int)State::Active]);
					}
				}
				else
				{
					if (m_aBorderColor[(int)State::Normal].A > 0)
					{
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top + m_fBorderWidth, rect.Left + m_fBorderWidth, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top, rect.Right, rect.Top + m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Right - m_fBorderWidth, rect.Top + m_fBorderWidth, rect.Right, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Bottom - m_fBorderWidth, rect.Right, rect.Bottom }, m_aBorderColor[(int)State::Normal]);
					}
				}
			}
			// LeftBottom view
			rect = CalculateLeftBottomViewRect();
			if (!rect.is_zero())
			{
				if (m_eActiveView == View::LeftBottom)
				{
					if (m_aBorderColor[(int)State::Active].A > 0)
					{
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top + m_fBorderWidth, rect.Left + m_fBorderWidth, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top, rect.Right, rect.Top + m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Right - m_fBorderWidth, rect.Top + m_fBorderWidth, rect.Right, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Bottom - m_fBorderWidth, rect.Right, rect.Bottom }, m_aBorderColor[(int)State::Active]);
					}
				}
				else
				{
					if (m_aBorderColor[(int)State::Normal].A > 0)
					{
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top + m_fBorderWidth, rect.Left + m_fBorderWidth, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top, rect.Right, rect.Top + m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Right - m_fBorderWidth, rect.Top + m_fBorderWidth, rect.Right, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Bottom - m_fBorderWidth, rect.Right, rect.Bottom }, m_aBorderColor[(int)State::Normal]);
					}
				}
			}
			// RightBottom view
			rect = CalculateRightBottomViewRect();
			if (!rect.is_zero())
			{
				if (m_eActiveView == View::RightBottom)
				{
					if (m_aBorderColor[(int)State::Active].A > 0)
					{
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top + m_fBorderWidth, rect.Left + m_fBorderWidth, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top, rect.Right, rect.Top + m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Right - m_fBorderWidth, rect.Top + m_fBorderWidth, rect.Right, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Active]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Bottom - m_fBorderWidth, rect.Right, rect.Bottom }, m_aBorderColor[(int)State::Active]);
					}
				}
				else
				{
					if (m_aBorderColor[(int)State::Normal].A > 0)
					{
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top + m_fBorderWidth, rect.Left + m_fBorderWidth, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Top, rect.Right, rect.Top + m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Right - m_fBorderWidth, rect.Top + m_fBorderWidth, rect.Right, rect.Bottom - m_fBorderWidth }, m_aBorderColor[(int)State::Normal]);
						renderer->DrawRectangle(RectF{ rect.Left, rect.Bottom - m_fBorderWidth, rect.Right, rect.Bottom }, m_aBorderColor[(int)State::Normal]);
					}
				}
			}
			// Outline
			if (Application->Editor)
			{
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ OutlineMask, 0, true, false })
					->DrawLines({ PointF{ 0, 1 }, PointF{ getWidth(), 1 }, PointF{ getWidth(), getHeight() }, PointF{ 1, getHeight() }, PointF{ 1, 1 } }, Color{ 0, 0, 0, 255 }, false);
			}
		}
	#pragma endregion
	}
}