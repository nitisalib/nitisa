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
		CTrackBar::CGradientListener::CGradientListener(CTrackBar *control) :
			m_pControl{ control }
		{

		}

		void CTrackBar::CGradientListener::NotifyOnChange()
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
		CTrackBar::CTrackBar() :
			CControl(L"TrackBar", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_iMin{ 0 },
			m_iMax{ 100 },
			m_iValue{ 50 },
			m_eTrackerStyle{ TrackerStyle::Down },
			m_aBackPadding{
				RectF{ 9, 6, 9, 24 },
				RectF{ 9, 24, 9, 6 },
				RectF{ 9, 15, 9, 15 } },
			m_aBackMargin{ 5, 5, 3 },
			m_aTickSize{
				PointF{ 1, 3 },
				PointF{ 1, 3 },
				PointF{ 1, 3 } },
			m_aBigTickSize{
				PointF{ 1, 4 },
				PointF{ 1, 4 },
				PointF{ 1, 4 } },
			m_aTrackerPadding{
				PointF{ 7, 23 },
				PointF{ 23, 7 },
				PointF{ 12, 12 } },
			m_aTrackerWidth{ 9, 9, 9 },
			m_iTickInterval{ 10 },
			m_iBigTickInterval{ 10 },
			m_aBorderWidth{
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
				RectF{ 0, 0, 0, 0 } },
			m_aBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aShadowRadius{ 1, 1, 1, 1, 1, 1, 1 },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
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
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aBackBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aBackBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aBackBorderColor{
				BorderColor{ Color{ 176, 176, 176, 255 }, Color{ 176, 176, 176, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 } },
				BorderColor{ Color{ 176, 176, 176, 255 }, Color{ 176, 176, 176, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 } },
				BorderColor{ Color{ 176, 176, 176, 255 }, Color{ 176, 176, 176, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 } },
				BorderColor{ Color{ 176, 176, 176, 255 }, Color{ 176, 176, 176, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 } },
				BorderColor{ Color{ 176, 176, 176, 255 }, Color{ 176, 176, 176, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 } },
				BorderColor{ Color{ 176, 176, 176, 255 }, Color{ 176, 176, 176, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 } },
				BorderColor{ Color{ 176, 176, 176, 255 }, Color{ 176, 176, 176, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 } } },
			m_aBackBackgroundColor{
				Color{ 231, 234, 234, 255 },
				Color{ 231, 234, 234, 255 },
				Color{ 231, 234, 234, 255 },
				Color{ 231, 234, 234, 255 },
				Color{ 231, 234, 234, 255 },
				Color{ 231, 234, 234, 255 },
				Color{ 231, 234, 234, 255 } },
			m_aBackBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aTrackerBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aTrackerBorderRadius{
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 } },
			m_aTrackerBorderColor{
				BorderColor{ Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 } },
				BorderColor{ Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 } },
				BorderColor{ Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 } },
				BorderColor{ Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 } },
				BorderColor{ Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 } },
				BorderColor{ Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 } },
				BorderColor{ Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 } } },
			m_aTrackerBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 240, 240, 240, 255 } },
			m_aTrackerBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aTickColor{
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 } },
			m_aBigTickColor{
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 },
				Color{ 196, 196, 196, 255 } },
			m_aOutlineColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 0 } },
			m_aOutlineMask{
				0b00000000000000000000000000000000,
				0b00000000000000000000000000000000,
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100,
				0b00000000000000000000000000000000 },
			m_bIgnoreGradient{ true },
			m_pCanvas{ nullptr },
			m_eHoveredElement{ Element::None }
		{
			OnChange = nullptr;
			setService(new CTrackBarService(this), true);
			setSize(PointF{ 155, 45 });

			m_aTrackerBackgroundGradient[(int)State::Normal].setPoints(Color1DArray{
				Color1D{ 0.000f, Color{ 242, 242, 242, 255 } },
				Color1D{ 0.499f, Color{ 235, 235, 235, 255 } },
				Color1D{ 0.500f, Color{ 219, 219, 219, 255 } },
				Color1D{ 1.000f, Color{ 208, 208, 208, 255 } } });
			m_aTrackerBackgroundGradient[(int)State::Hovered].setPoints(Color1DArray{
				Color1D{ 0.000f, Color{ 234, 246, 253, 255 } },
				Color1D{ 0.499f, Color{ 217, 240, 252, 255 } },
				Color1D{ 0.500f, Color{ 190, 230, 253, 255 } },
				Color1D{ 1.000f, Color{ 167, 217, 245, 255 } } });
			m_aTrackerBackgroundGradient[(int)State::Focused].setPoints(Color1DArray{
				Color1D{ 0.000f, Color{ 242, 242, 242, 255 } },
				Color1D{ 0.499f, Color{ 235, 235, 235, 255 } },
				Color1D{ 0.500f, Color{ 219, 219, 219, 255 } },
				Color1D{ 1.000f, Color{ 208, 208, 208, 255 } } });
			m_aTrackerBackgroundGradient[(int)State::FocusedHovered].setPoints(Color1DArray{
				Color1D{ 0.000f, Color{ 234, 246, 253, 255 } },
				Color1D{ 0.499f, Color{ 217, 240, 252, 255 } },
				Color1D{ 0.500f, Color{ 190, 230, 253, 255 } },
				Color1D{ 1.000f, Color{ 167, 217, 245, 255 } } });
			m_aTrackerBackgroundGradient[(int)State::Active].setPoints(Color1DArray{
				Color1D{ 0.000f, Color{ 229, 244, 252, 255 } },
				Color1D{ 0.499f, Color{ 196, 229, 246, 255 } },
				Color1D{ 0.500f, Color{ 152, 209, 239, 255 } },
				Color1D{ 1.000f, Color{ 109, 182, 221, 255 } } });
			m_aTrackerBackgroundGradient[(int)State::ActiveHovered].setPoints(Color1DArray{
				Color1D{ 0.000f, Color{ 229, 244, 252, 255 } },
				Color1D{ 0.499f, Color{ 196, 229, 246, 255 } },
				Color1D{ 0.500f, Color{ 152, 209, 239, 255 } },
				Color1D{ 1.000f, Color{ 109, 182, 221, 255 } } });
			m_bIgnoreGradient = false;
		}

		CTrackBar::CTrackBar(IForm *parent) :CTrackBar()
		{
			setForm(parent);
		}

		CTrackBar::CTrackBar(IControl *parent) : CTrackBar()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CTrackBar::getRenderRect()
		{
			RectF result{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)State::Normal], m_aShadowShift[(int)State::Normal], m_aShadowRadius[(int)State::Normal]) };
			for (int i = (int)State::Normal + 1; i <= (int)State::Disabled; i++)
				result += AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
			return result;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CTrackBar::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (int i = 0; i <= (int)TrackerStyle::Both; i++)
				{
					m_aBackPadding[i] *= s;
					m_aBackMargin[i] *= avg;
					m_aTickSize[i] *= s;
					m_aBigTickSize[i] *= s;
					m_aTrackerPadding[i] *= s;
					m_aTrackerWidth[i] *= s.X;
				}
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aBorderWidth[i] *= s;
					m_aBorderRadius[i] *= avg;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
					m_aBackBorderWidth[i] *= s;
					m_aBackBorderRadius[i] *= avg;
					m_aTrackerBorderWidth[i] *= s;
					m_aTrackerBorderRadius[i] *= avg;
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
		void CTrackBar::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region ITrackBar getters
		int CTrackBar::getMin()
		{
			return m_iMin;
		}

		int CTrackBar::getMax()
		{
			return m_iMax;
		}

		int CTrackBar::getValue()
		{
			return m_iValue;
		}
	#pragma endregion

	#pragma region ITrackBar setters
		bool CTrackBar::setMin(const int value)
		{
			if (value != m_iMin)
			{
				m_iMin = value;
				if (m_iMax <= m_iMin)
					m_iMax = m_iMin + 1;
				m_iValue = ntl::Clamp<int>(m_iValue, m_iMin, m_iMax);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackBar::setMax(const int value)
		{
			if (value != m_iMax)
			{
				m_iMax = value;
				if (m_iMin >= m_iMax)
					m_iMin = m_iMax - 1;
				m_iValue = ntl::Clamp<int>(m_iValue, m_iMin, m_iMax);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return true;
		}

		bool CTrackBar::setValue(const int value)
		{
			int v{ ntl::Clamp<int>(value, m_iMin, m_iMax) };
			if (v != m_iValue)
			{
				m_iValue = v;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CTrackBar::State CTrackBar::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isCaptureMouse())
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

		CTrackBar::TrackerStyle CTrackBar::getTrackerStyle() const
		{
			return m_eTrackerStyle;
		}

		RectF CTrackBar::getBackPadding(const TrackerStyle style) const
		{
			return m_aBackPadding[(int)style];
		}

		float CTrackBar::getBackMargin(const TrackerStyle style) const
		{
			return m_aBackMargin[(int)style];
		}

		PointF CTrackBar::getTickSize(const TrackerStyle style) const
		{
			return m_aTickSize[(int)style];
		}

		PointF CTrackBar::getBigTickSize(const TrackerStyle style) const
		{
			return m_aBigTickSize[(int)style];
		}

		PointF CTrackBar::getTrackerPadding(const TrackerStyle style) const
		{
			return m_aTrackerPadding[(int)style];
		}

		float CTrackBar::getTrackerWidth(const TrackerStyle style) const
		{
			return m_aTrackerWidth[(int)style];
		}

		int CTrackBar::getTickInterval() const
		{
			return m_iTickInterval;
		}

		int CTrackBar::getBigTickInterval() const
		{
			return m_iBigTickInterval;
		}

		RectF CTrackBar::getBorderWidth(const State state) const
		{
			return m_aBorderWidth[(int)state];
		}

		RectF CTrackBar::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CTrackBar::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CTrackBar::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CTrackBar::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		int CTrackBar::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CTrackBar::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CTrackBar::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		RectF CTrackBar::getBackBorderWidth(const State state) const
		{
			return m_aBackBorderWidth[(int)state];
		}

		RectF CTrackBar::getBackBorderRadius(const State state) const
		{
			return m_aBackBorderRadius[(int)state];
		}

		BorderColor CTrackBar::getBackBorderColor(const State state) const
		{
			return m_aBackBorderColor[(int)state];
		}

		Color CTrackBar::getBackBackgroundColor(const State state) const
		{
			return m_aBackBackgroundColor[(int)state];
		}

		Gradient *CTrackBar::getBackBackgroundGradient(const State state)
		{
			return &m_aBackBackgroundGradient[(int)state];
		}

		RectF CTrackBar::getTrackerBorderWidth(const State state) const
		{
			return m_aTrackerBorderWidth[(int)state];
		}

		RectF CTrackBar::getTrackerBorderRadius(const State state) const
		{
			return m_aTrackerBorderRadius[(int)state];
		}

		BorderColor CTrackBar::getTrackerBorderColor(const State state) const
		{
			return m_aTrackerBorderColor[(int)state];
		}

		Color CTrackBar::getTrackerBackgroundColor(const State state) const
		{
			return m_aTrackerBackgroundColor[(int)state];
		}

		Gradient *CTrackBar::getTrackerBackgroundGradient(const State state)
		{
			return &m_aTrackerBackgroundGradient[(int)state];
		}

		Color CTrackBar::getTickColor(const State state) const
		{
			return m_aTickColor[(int)state];
		}

		Color CTrackBar::getBigTickColor(const State state) const
		{
			return m_aBigTickColor[(int)state];
		}

		Color CTrackBar::getOutlineColor(const State state) const
		{
			return m_aOutlineColor[(int)state];
		}

		unsigned int CTrackBar::getOutlineMask(const State state) const
		{
			return m_aOutlineMask[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CTrackBar::setTrackerStyle(const TrackerStyle value)
		{
			if (value != m_eTrackerStyle)
			{
				m_eTrackerStyle = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackBar::setBackPadding(const TrackerStyle style, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBackPadding[(int)style]))
			{
				m_aBackPadding[(int)style] = value;
				if (style == m_eTrackerStyle)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setBackMargin(const TrackerStyle style, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aBackMargin[(int)style]))
			{
				m_aBackMargin[(int)style] = value;
				if (style == m_eTrackerStyle)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setTickSize(const TrackerStyle style, const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_aTickSize[(int)style]))
			{
				m_aTickSize[(int)style] = value;
				if (style == m_eTrackerStyle)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setBigTickSize(const TrackerStyle style, const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_aBigTickSize[(int)style]))
			{
				m_aBigTickSize[(int)style] = value;
				if (style == m_eTrackerStyle)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setTrackerPadding(const TrackerStyle style, const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_aTrackerPadding[(int)style]))
			{
				m_aTrackerPadding[(int)style] = value;
				if (style == m_eTrackerStyle)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setTrackerWidth(const TrackerStyle style, const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aTrackerWidth[(int)style]))
			{
				m_aTrackerWidth[(int)style] = value;
				if (style == m_eTrackerStyle)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setTickInterval(const int value)
		{
			if (value >= 0 && value != m_iTickInterval)
			{
				m_iTickInterval = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackBar::setBigTickInterval(const int value)
		{
			if (value >= 0 && value != m_iBigTickInterval)
			{
				m_iBigTickInterval = value;
				if (m_iTickInterval > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderWidth[(int)state]))
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

		bool CTrackBar::setBorderRadius(const State state, const RectF &value)
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

		bool CTrackBar::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (m_aBorderWidth[(int)state].has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (m_aBackgroundGradient[(int)state].getPointCount() < 2 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (state == s && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				m_aShadowRadius[(int)state] = value;
				if (state == s && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackBar::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (state == s && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				m_aShadowShift[(int)state] = value;
				if (state == s && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackBar::setShadowColor(const State state, const Color &value)
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

		bool CTrackBar::setBackBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBackBorderWidth[(int)state]))
			{
				m_aBackBorderWidth[(int)state] = value;
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

		bool CTrackBar::setBackBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBackBorderRadius[(int)state]))
			{
				m_aBackBorderRadius[(int)state] = value;
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

		bool CTrackBar::setBackBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBackBorderColor[(int)state])
			{
				m_aBackBorderColor[(int)state] = value;
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

		bool CTrackBar::setBackBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackBackgroundColor[(int)state])
			{
				m_aBackBackgroundColor[(int)state] = value;
				if (m_aBackBackgroundGradient[(int)state].getPointCount() < 2 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setTrackerBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aTrackerBorderWidth[(int)state]))
			{
				m_aTrackerBorderWidth[(int)state] = value;
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

		bool CTrackBar::setTrackerBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aTrackerBorderRadius[(int)state]))
			{
				m_aTrackerBorderRadius[(int)state] = value;
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

		bool CTrackBar::setTrackerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aTrackerBorderColor[(int)state])
			{
				m_aTrackerBorderColor[(int)state] = value;
				if (m_aTrackerBorderWidth[(int)state].has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setTrackerBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aTrackerBackgroundColor[(int)state])
			{
				m_aTrackerBackgroundColor[(int)state] = value;
				if (m_aTrackerBackgroundGradient[(int)state].getPointCount() < 2 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setTickColor(const State state, const Color &value)
		{
			if (value != m_aTickColor[(int)state])
			{
				m_aTickColor[(int)state] = value;
				if (m_iTickInterval > 0 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setBigTickColor(const State state, const Color &value)
		{
			if (value != m_aBigTickColor[(int)state])
			{
				m_aBigTickColor[(int)state] = value;
				if (m_iTickInterval > 0 && m_iBigTickInterval > 0 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackBar::setOutlineColor(const State state, const Color &value)
		{
			if (value != m_aOutlineColor[(int)state])
			{
				m_aOutlineColor[(int)state] = value;
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

		bool CTrackBar::setOutlineMask(const State state, const unsigned int value)
		{
			if (value != m_aOutlineMask[(int)state])
			{
				m_aOutlineMask[(int)state] = value;
				if (m_aOutlineColor[(int)state].A > 0 && state == getState())
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
		void CTrackBar::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			for (int i = 0; i <= (int)TrackerStyle::Both; i++)
			{
				String state;
				switch ((TrackerStyle)i)
				{
				case TrackerStyle::Down:
					state = L"Down";
					break;
				case TrackerStyle::Up:
					state = L"Up";
					break;
				default:
					state = L"Both";
				}
				style->getOption(m_sClassName + L".BackPadding[" + state + L"]", m_aBackPadding[i]);
				style->getOption(m_sClassName + L".BackMargin[" + state + L"]", m_aBackMargin[i]);
				style->getOption(m_sClassName + L".TickSize[" + state + L"]", m_aTickSize[i]);
				style->getOption(m_sClassName + L".BigTickSize[" + state + L"]", m_aBigTickSize[i]);
				style->getOption(m_sClassName + L".TrackerPadding[" + state + L"]", m_aTrackerPadding[i]);
				style->getOption(m_sClassName + L".TrackerWidth[" + state + L"]", m_aTrackerWidth[i]);
			}
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
				style->getOption(m_sClassName + L".BorderWidth[" + state + L"]", m_aBorderWidth[i]);
				style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]);
				style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".BackBorderWidth[" + state + L"]", m_aBackBorderWidth[i]);
				style->getOption(m_sClassName + L".BackBorderRadius[" + state + L"]", m_aBackBorderRadius[i]);
				style->getOption(m_sClassName + L".BackBorderColor[" + state + L"]", m_aBackBorderColor[i]);
				style->getOption(m_sClassName + L".BackBackgroundColor[" + state + L"]", m_aBackBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackBackgroundGradient[" + state + L"]", m_aBackBackgroundGradient[i]);
				style->getOption(m_sClassName + L".TrackerBorderWidth[" + state + L"]", m_aTrackerBorderWidth[i]);
				style->getOption(m_sClassName + L".TrackerBorderRadius[" + state + L"]", m_aTrackerBorderRadius[i]);
				style->getOption(m_sClassName + L".TrackerBorderColor[" + state + L"]", m_aTrackerBorderColor[i]);
				style->getOption(m_sClassName + L".TrackerBackgroundColor[" + state + L"]", m_aTrackerBackgroundColor[i]);
				style->getOption(m_sClassName + L".TrackerBackgroundGradient[" + state + L"]", m_aTrackerBackgroundGradient[i]);
				style->getOption(m_sClassName + L".TickColor[" + state + L"]", m_aTickColor[i]);
				style->getOption(m_sClassName + L".BigTickColor[" + state + L"]", m_aBigTickColor[i]);
				style->getOption(m_sClassName + L".OutlineColor[" + state + L"]", m_aOutlineColor[i]);
				style->getOption(m_sClassName + L".OutlineMask[" + state + L"]", m_aOutlineMask[i]);
			}
			m_bIgnoreGradient = false;
		}

		CTrackBar::State CTrackBar::getTrackerState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isCaptureMouse())
			{
				if (m_eHoveredElement == Element::Tracker)
					return State::ActiveHovered;
				return State::Active;
			}
			if (isFocused())
			{
				if (m_eHoveredElement == Element::Tracker)
					return State::FocusedHovered;
				return State::Focused;
			}
			if (m_eHoveredElement == Element::Tracker)
				return State::Hovered;
			return State::Normal;
		}

		RectF CTrackBar::getTrackerRect()
		{
			RectF back{ getBackRect() };
			PointF size{ m_aTrackerWidth[(int)m_eTrackerStyle], getHeight() - m_aTrackerPadding[(int)m_eTrackerStyle].X - m_aTrackerPadding[(int)m_eTrackerStyle].Y };
			float x{ back.Left + float(m_iValue - m_iMin) * (back.width() - 1) / float(m_iMax - m_iMin) - size.X * 0.5f };
			return RectF{ x, m_aTrackerPadding[(int)m_eTrackerStyle].X, x + m_aTrackerWidth[(int)m_eTrackerStyle], getHeight() - m_aTrackerPadding[(int)m_eTrackerStyle].Y };
		}

		RectF CTrackBar::getBackRect()
		{
			return RectF{ m_aBackPadding[(int)m_eTrackerStyle].Left, m_aBackPadding[(int)m_eTrackerStyle].Top, getWidth() - m_aBackPadding[(int)m_eTrackerStyle].Right, getHeight() - m_aBackPadding[(int)m_eTrackerStyle].Bottom };
		}

		bool CTrackBar::UpdateHoveredElement(const PointF &position)
		{
			Element el{ Element::None };
			if (isEnabled(true))
			{
				RectF client{ getClientRect() };
				if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
				{
					RectF r{ getTrackerRect() };
					if (r.is_valid() && !r.is_zero() && position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
						el = Element::Tracker;
					else
					{
						r = getBackRect();
						if (r.is_valid() && !r.is_zero() && position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
							el = Element::Back;
					}
				}
			}
			if (el != m_eHoveredElement)
			{
				m_eHoveredElement = el;
				return true;
			}
			return false;
		}

		int CTrackBar::ClientToValue(const PointF &position)
		{
			RectF r{ getBackRect() };
			if (!r.is_valid() || r.is_zero())
				return m_iMin;
			if (position.X <= r.Left)
				return m_iMin;
			if (position.X >= r.Right)
				return m_iMax;
			return ntl::Round<int>((float)m_iMin + float(m_iMax - m_iMin) * (position.X - r.Left) / r.width());
		}
	#pragma endregion

	#pragma region Paint
		void CTrackBar::Render()
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
				DrawBlockShadow(renderer, rect, m_aBorderRadius[(int)state], m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawSimpleBackground(renderer, rect, m_aBorderWidth[(int)state], m_aBorderRadius[(int)state], m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
				if (m_aBackBorderRadius[(int)state].has_positive() || m_aBorderWidth[(int)state].has_positive())
				{
					Block b{ rect, m_aBorderWidth[(int)state], m_aBorderRadius[(int)state], PointLocation::Inside };
					ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(rect.width()), ntl::Round<int>(rect.height()), 1, TextureFormat::RGBA, true) };
					if (clip)
					{
						renderer
							->ActivateTarget(clip)
							->Clear(Color{ 0, 0, 0, 0 });
						RectF r{ 0, 0, rect.width(), rect.height() };
						RenderBack(renderer, r, state);
						RenderTicks(renderer, r, state);
						RenderTracker(renderer, r, getTrackerState());
						RenderOutline(renderer, r, state);
						CStoreBlock s_block{ renderer };
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivateTarget(m_pCanvas)
							->ActivateBlock(&b)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(rect.Left, rect.Top, 0))
							->DrawImage(clip, 1);
						clip->Release();
					}
				}
				else
				{
					RenderBack(renderer, rect, state);
					RenderTicks(renderer, rect, state);
					RenderTracker(renderer, rect, getTrackerState());
					RenderOutline(renderer, rect, state);
				}
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CTrackBar::RenderBack(IRenderer *renderer, const RectF &rect, const State state)
		{
			RectF r{
				rect.Left + m_aBackPadding[(int)m_eTrackerStyle].Left,
				rect.Top + m_aBackPadding[(int)m_eTrackerStyle].Top,
				rect.Right - m_aBackPadding[(int)m_eTrackerStyle].Right,
				rect.Bottom - m_aBackPadding[(int)m_eTrackerStyle].Bottom };
			if (r.is_valid() && !r.is_zero())
			{
				if (m_aBackBorderWidth[(int)state].has_positive() || m_aBackBorderRadius[(int)state].has_positive())
				{
					Block b{ r, m_aBackBorderWidth[(int)state], m_aBackBorderRadius[(int)state], PointLocation::Inside };
					BlockColors colors{
						m_aBackBorderColor[(int)state].Left,
						m_aBackBorderColor[(int)state].Top,
						m_aBackBorderColor[(int)state].Right,
						m_aBackBorderColor[(int)state].Bottom,
						m_aBackBackgroundGradient[(int)state].getPointCount() >= 2 ? Color{ 0, 0, 0, 0 } : m_aBackBackgroundColor[(int)state],
						Color{ 0, 0, 0, 0 }
					};
					if (m_aBackBackgroundGradient[(int)state].getPointCount() >= 2)
					{
						CStoreBlock s_block{ renderer };
						renderer
							->ActivateBlock(&b)
							->DrawGradient(r, m_aBackBackgroundGradient[(int)state]);
					}
					renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
				}
				else
				{
					if (m_aBackBackgroundGradient[(int)state].getPointCount() >= 2)
						renderer->DrawGradient(r, m_aBackBackgroundGradient[(int)state]);
					else if (m_aBackBackgroundColor[(int)state].A > 0)
						renderer->DrawRectangle(r, m_aBackBackgroundColor[(int)state]);
				}
			}
		}

		void CTrackBar::RenderTicks(IRenderer *renderer, const RectF &rect, const State state)
		{
			if (m_iTickInterval > 0)
			{
				RectF back{
					rect.Left + m_aBackPadding[(int)m_eTrackerStyle].Left,
					rect.Top + m_aBackPadding[(int)m_eTrackerStyle].Top,
					rect.Right - m_aBackPadding[(int)m_eTrackerStyle].Right,
					rect.Bottom - m_aBackPadding[(int)m_eTrackerStyle].Bottom };
				if (back.is_valid() && !back.is_zero())
				{
					PointF small1{ back.Top - m_aBackMargin[(int)m_eTrackerStyle] - m_aTickSize[(int)m_eTrackerStyle].Y, back.Top - m_aBackMargin[(int)m_eTrackerStyle] };
					PointF small2{ back.Bottom + m_aBackMargin[(int)m_eTrackerStyle], back.Bottom + m_aBackMargin[(int)m_eTrackerStyle] + m_aTickSize[(int)m_eTrackerStyle].Y };
					PointF big1{ back.Top - m_aBackMargin[(int)m_eTrackerStyle] - m_aBigTickSize[(int)m_eTrackerStyle].Y, back.Top - m_aBackMargin[(int)m_eTrackerStyle] };
					PointF big2{ back.Bottom + m_aBackMargin[(int)m_eTrackerStyle], back.Bottom + m_aBackMargin[(int)m_eTrackerStyle] + m_aBigTickSize[(int)m_eTrackerStyle].Y };
					int tick{ m_iMin }, index{ 0 };
					float x, t;
					while (tick <= m_iMax)
					{
						x = back.Left + float(tick - m_iMin) * (back.width() - 1) / float(m_iMax - m_iMin);
						if (m_iBigTickInterval > 0 && index % m_iBigTickInterval == 0)
						{
							if (ntl::IsGreater<float>(m_aBigTickSize[(int)m_eTrackerStyle].X, 0) && ntl::IsGreater<float>(m_aBigTickSize[(int)m_eTrackerStyle].Y, 0) && m_aBigTickColor[(int)state].A > 0)
							{
								t = std::round(x - m_aBigTickSize[(int)m_eTrackerStyle].X * 0.5f);
								if (m_eTrackerStyle != TrackerStyle::Down)
									renderer->DrawRectangle(RectF{ t, big1.X, t + m_aBigTickSize[(int)m_eTrackerStyle].X, big1.Y }, m_aBigTickColor[(int)state]);
								if (m_eTrackerStyle != TrackerStyle::Up)
									renderer->DrawRectangle(RectF{ t, big2.X, t + m_aBigTickSize[(int)m_eTrackerStyle].X, big2.Y }, m_aBigTickColor[(int)state]);
							}
						}
						else
						{
							if (ntl::IsGreater<float>(m_aTickSize[(int)m_eTrackerStyle].X, 0) && ntl::IsGreater<float>(m_aTickSize[(int)m_eTrackerStyle].Y, 0) && m_aTickColor[(int)state].A > 0)
							{
								t = std::round(x - m_aTickSize[(int)m_eTrackerStyle].X * 0.5f);
								if (m_eTrackerStyle != TrackerStyle::Down)
									renderer->DrawRectangle(RectF{ t, small1.X, t + m_aTickSize[(int)m_eTrackerStyle].X, small1.Y }, m_aTickColor[(int)state]);
								if (m_eTrackerStyle != TrackerStyle::Up)
									renderer->DrawRectangle(RectF{ t, small2.X, t + m_aTickSize[(int)m_eTrackerStyle].X, small2.Y }, m_aTickColor[(int)state]);
							}
						}
						tick += m_iTickInterval;
						index++;
					}
				}
			}
		}

		void CTrackBar::RenderTracker(IRenderer *renderer, const RectF &rect, const State state)
		{
			PointF size{ m_aTrackerWidth[(int)m_eTrackerStyle], rect.height() - m_aTrackerPadding[(int)m_eTrackerStyle].X - m_aTrackerPadding[(int)m_eTrackerStyle].Y };
			if (ntl::IsGreater<float>(size.X, 0) && ntl::IsGreater<float>(size.Y, 0))
			{
				RectF back{
					rect.Left + m_aBackPadding[(int)m_eTrackerStyle].Left,
					rect.Top + m_aBackPadding[(int)m_eTrackerStyle].Top,
					rect.Right - m_aBackPadding[(int)m_eTrackerStyle].Right,
					rect.Bottom - m_aBackPadding[(int)m_eTrackerStyle].Bottom };
				if (back.is_valid() && !back.is_zero())
				{
					float x{ back.Left + float(m_iValue - m_iMin) * (back.width() - 1) / float(m_iMax - m_iMin) - size.X * 0.5f };
					RectF r{ x, rect.Top + m_aTrackerPadding[(int)m_eTrackerStyle].X, x + m_aTrackerWidth[(int)m_eTrackerStyle], rect.Bottom - m_aTrackerPadding[(int)m_eTrackerStyle].Y };
					if (r.is_valid() && !r.is_zero())
					{
						switch (m_eTrackerStyle)
						{
						case TrackerStyle::Down:
							RenderTrackerDown(renderer, r, state);
							break;
						case TrackerStyle::Up:
							RenderTrackerUp(renderer, r, state);
							break;
						case TrackerStyle::Both:
							RenderTrackerBoth(renderer, r, state);
							break;
						}
					}
				}
			}
		}

		void CTrackBar::RenderTrackerDown(IRenderer *renderer, const RectF &rect, const State state)
		{
			PointF size{ std::round(rect.width()), std::round(rect.height()) };
			if (ntl::IsPositive<float>(size.X) && ntl::IsPositive<float>(size.Y))
			{
				IBaseTexture *old{ renderer->ActiveTarget };
				ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(size.X), ntl::Round<int>(size.Y), 1, TextureFormat::RGBA, true) };
				if (clip)
				{
					renderer
						->ActivateTarget(clip)
						->Clear(Color{ 0, 0, 0, 0 });
					RectF r{ 0, 0, size.X, size.Y }, r1{ 0, 0, size.X, std::round(size.Y - size.X * 0.5f) }, r2{ 0, r1.Bottom, size.X, size.Y };
					if (r1.is_valid() && !r1.is_zero())
					{
						if (ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Left, 0) || ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Top, 0) || ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Right, 0) ||
							ntl::IsGreater<float>(m_aTrackerBorderRadius[(int)state].Left, 0) || ntl::IsGreater<float>(m_aTrackerBorderRadius[(int)state].Top, 0))
						{
							Block b{ r1, RectF{ 1, 1, 1, 0 }, RectF{ m_aTrackerBorderRadius[(int)state].Left, m_aTrackerBorderRadius[(int)state].Top, 0, 0 }, PointLocation::Inside };
							BlockColors colors{
								m_aTrackerBorderColor[(int)state].Left,
								m_aTrackerBorderColor[(int)state].Top,
								m_aTrackerBorderColor[(int)state].Right,
								Color{ 0, 0, 0, 0 },
								m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2 ? Color{ 0, 0, 0, 0 } : m_aTrackerBackgroundColor[(int)state],
								Color{ 0, 0, 0, 0 }
							};
							if (m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2)
							{
								CStoreBlock s_block{ renderer };
								renderer
									->ActivateBlock(&b)
									->DrawGradient(r, m_aTrackerBackgroundGradient[(int)state]);
							}
							if (m_aTrackerBorderWidth[(int)state].has_positive())
								renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
						}
						else
						{
							if (m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2)
							{
								Block b{ r1, RectF{ 0, 0, 0, 0 }, RectF{ 0, 0, 0, 0 }, PointLocation::Inside };
								CStoreBlock s_block{ renderer };
								renderer
									->ActivateBlock(&b)
									->DrawGradient(r, m_aTrackerBackgroundGradient[(int)state]);
							}
							else if (m_aTrackerBackgroundColor[(int)state].A > 0)
								renderer->DrawRectangle(r1, m_aTrackerBackgroundColor[(int)state]);
						}
					}
					if (r2.is_valid() && !r2.is_zero())
					{
						Color c1, c2;
						if (m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2)
						{
							c1 = m_aTrackerBackgroundGradient[(int)state].getColor((r1.Bottom - r1.Top) / rect.height());
							c2 = m_aTrackerBackgroundGradient[(int)state].getColor(1);
						}
						else
						{
							c1 = m_aTrackerBackgroundColor[(int)state];
							c2 = m_aTrackerBackgroundColor[(int)state];
						}
						float mid{ size.X * 0.5f };
						renderer->DrawTriangle(PointF{ r2.Left, r2.Top }, PointF{ r2.Right, r2.Top }, PointF{ mid, r2.Bottom }, c1, c1, c2);
						if (ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Left, 0) || ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Top, 0) || ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Right, 0))
						{
							renderer->DrawLine(PointF{ r2.Left, r2.Top - 1 }, PointF{ mid, r2.Bottom }, m_aTrackerBorderColor[(int)state].Left);
							renderer->DrawLine(PointF{ r2.Right, r2.Top - 1 }, PointF{ mid - 1, r2.Bottom }, m_aTrackerBorderColor[(int)state].Right);
						}
					}
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateTarget(old)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(rect.Left), std::round(rect.Top), 0))
						->DrawImage(clip, 1);
					clip->Release();
				}
			}
		}

		void CTrackBar::RenderTrackerUp(IRenderer *renderer, const RectF &rect, const State state)
		{
			PointF size{ std::round(rect.width()), std::round(rect.height()) };
			if (ntl::IsPositive<float>(size.X) && ntl::IsPositive<float>(size.Y))
			{
				IBaseTexture *old{ renderer->ActiveTarget };
				ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(size.X), ntl::Round<int>(size.Y), 1, TextureFormat::RGBA, true) };
				if (clip)
				{
					renderer
						->ActivateTarget(clip)
						->Clear(Color{ 0, 0, 0, 0 });
					RectF r{ 0, 0, size.X, size.Y }, r1{ 0, 0, size.X, std::round(size.X * 0.5f) }, r2{ 0, r1.Bottom, size.X, size.Y };
					if (r1.is_valid() && !r1.is_zero())
					{
						Color c1, c2;
						if (m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2)
						{
							c1 = m_aTrackerBackgroundGradient[(int)state].getColor(0);
							c2 = m_aTrackerBackgroundGradient[(int)state].getColor((r1.Bottom - r1.Top) / rect.height());
						}
						else
						{
							c1 = m_aTrackerBackgroundColor[(int)state];
							c2 = m_aTrackerBackgroundColor[(int)state];
						}
						float mid{ size.X * 0.5f };
						renderer->DrawTriangle(PointF{ r1.Left, r1.Bottom }, PointF{ mid, r1.Top }, PointF{ r1.Right, r1.Bottom }, c1, c2, c2);
						if (ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Left, 0) || ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Right, 0) || ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Bottom, 0))
						{
							renderer->DrawLine(PointF{ mid, r1.Top }, PointF{ r1.Left, r1.Bottom }, m_aTrackerBorderColor[(int)state].Left);
							renderer->DrawLine(PointF{ mid - 1, r1.Top }, PointF{ r1.Right, r1.Bottom }, m_aTrackerBorderColor[(int)state].Right);
						}
					}
					if (r2.is_valid() && !r2.is_zero())
					{
						if (ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Left, 0) || ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Right, 0) || ntl::IsGreater<float>(m_aTrackerBorderWidth[(int)state].Bottom, 0) ||
							ntl::IsGreater<float>(m_aTrackerBorderRadius[(int)state].Right, 0) || ntl::IsGreater<float>(m_aTrackerBorderRadius[(int)state].Bottom, 0))
						{
							Block b{ r2, RectF{ 1, 0, 1, 1 }, RectF{ 0, 0, m_aTrackerBorderRadius[(int)state].Right, m_aTrackerBorderRadius[(int)state].Bottom }, PointLocation::Inside };
							BlockColors colors{
								m_aTrackerBorderColor[(int)state].Left,
								Color{ 0, 0, 0, 0 },
								m_aTrackerBorderColor[(int)state].Right,
								m_aTrackerBorderColor[(int)state].Bottom,
								m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2 ? Color{ 0, 0, 0, 0 } : m_aTrackerBackgroundColor[(int)state],
								Color{ 0, 0, 0, 0 }
							};
							if (m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2)
							{
								CStoreBlock s_block{ renderer };
								renderer
									->ActivateBlock(&b)
									->DrawGradient(r, m_aTrackerBackgroundGradient[(int)state]);
							}
							if (m_aTrackerBorderWidth[(int)state].has_positive())
								renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
						}
						else
						{
							if (m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2)
							{
								Block b{ r2, RectF{ 0, 0, 0, 0 }, RectF{ 0, 0, 0, 0 }, PointLocation::Inside };
								CStoreBlock s_block{ renderer };
								renderer
									->ActivateBlock(&b)
									->DrawGradient(r, m_aTrackerBackgroundGradient[(int)state]);
							}
							else if (m_aTrackerBackgroundColor[(int)state].A > 0)
								renderer->DrawRectangle(r2, m_aTrackerBackgroundColor[(int)state]);
						}
					}
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateTarget(old)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(rect.Left), std::round(rect.Top), 0))
						->DrawImage(clip, 1);
					clip->Release();
				}
			}
		}

		void CTrackBar::RenderTrackerBoth(IRenderer *renderer, const RectF &rect, const State state)
		{
			RectF r{ 0, 0, std::round(rect.width()), std::round(rect.height()) };
			if (r.is_valid() && !r.is_zero())
			{
				IBaseTexture *old{ renderer->ActiveTarget };
				ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(r.Right), ntl::Round<int>(r.Bottom), 1, TextureFormat::RGBA, true) };
				if (clip)
				{
					renderer
						->ActivateTarget(clip)
						->Clear(Color{ 0, 0, 0, 0 });
					if (m_aTrackerBorderWidth[(int)state].has_positive() || m_aTrackerBorderRadius[(int)state].has_positive())
					{
						Block b{ r, m_aTrackerBorderWidth[(int)state], m_aTrackerBorderRadius[(int)state], PointLocation::Inside };
						BlockColors colors{
							m_aTrackerBorderColor[(int)state].Left,
							m_aTrackerBorderColor[(int)state].Top,
							m_aTrackerBorderColor[(int)state].Right,
							m_aTrackerBorderColor[(int)state].Bottom,
							m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2 ? Color{ 0, 0, 0, 0 } : m_aTrackerBackgroundColor[(int)state],
							Color{ 0, 0, 0, 0 }
						};
						if (m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2)
						{
							CStoreBlock s_block{ renderer };
							renderer
								->ActivateBlock(&b)
								->DrawGradient(r, m_aTrackerBackgroundGradient[(int)state]);
						}
						if (m_aTrackerBorderWidth[(int)state].has_positive())
							renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
					}
					else
					{
						if (m_aTrackerBackgroundGradient[(int)state].getPointCount() >= 2)
							renderer->DrawGradient(r, m_aTrackerBackgroundGradient[(int)state]);
						else if (m_aTrackerBackgroundColor[(int)state].A > 0)
							renderer->DrawRectangle(r, m_aTrackerBackgroundColor[(int)state]);
					}
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateTarget(old)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(rect.Left), std::round(rect.Top), 0))
						->DrawImage(clip, 1);
					clip->Release();
				}
			}
		}

		void CTrackBar::RenderOutline(IRenderer *renderer, const RectF &rect, const State state)
		{
			if (m_aOutlineColor[(int)state].A > 0 && m_aOutlineMask[(int)state] != 0)
			{
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ m_aOutlineMask[(int)state], 0, true, false })
					->DrawLines({
						PointF{ rect.Left, rect.Top },
						PointF{ rect.Right, rect.Top },
						PointF{ rect.Right, rect.Bottom - 1 },
						PointF{ 1, rect.Bottom - 1 },
						PointF{ 1, 1 } },
						m_aOutlineColor[(int)state],
						false);
			}
		}
	#pragma endregion
	}
}