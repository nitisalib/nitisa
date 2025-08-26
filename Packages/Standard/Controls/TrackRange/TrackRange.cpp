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
		CTrackRange::CGradientListener::CGradientListener(CTrackRange *control) :
			m_pControl{ control }
		{

		}

		void CTrackRange::CGradientListener::NotifyOnChange()
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
		CTrackRange::CTrackRange() :
			CControl(L"TrackRange", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_iMin{ 0 },
			m_iMax{ 100 },
			m_sValue{ 33, 66 },
			m_sTrackerEnabled{ true, true },
			m_sTrackerVisible{ true, true },
			m_sBackPadding{ 5, 12, 5, 12 },
			m_fBackMargin{ 5 },
			m_sTickSize{ 2, 3 },
			m_sBigTickSize{ 2, 6 },
			m_sTrackerPadding{ 7, 7 },
			m_fTrackerWidth{ 10 },
			m_bTopTicksVisible{ true },
			m_bBottomTicksVisible{ true },
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
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aBackBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aBackBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aBackBackgroundColor{
				Color{ 170, 173, 170, 255 },
				Color{ 170, 173, 170, 255 },
				Color{ 170, 173, 170, 255 },
				Color{ 170, 173, 170, 255 },
				Color{ 170, 173, 170, 255 },
				Color{ 170, 173, 170, 255 },
				Color{ 170, 173, 170, 255 } },
			m_aBackBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aBackSelectionBackgroundColor{
				Color{ 114, 209, 255, 255 },
				Color{ 114, 209, 255, 255 },
				Color{ 114, 209, 255, 255 },
				Color{ 114, 209, 255, 255 },
				Color{ 114, 209, 255, 255 },
				Color{ 114, 209, 255, 255 },
				Color{ 114, 209, 255, 255 } },
			m_aBackSelectionBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aTrackerBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aTrackerOuterBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aTrackerInnerBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aTrackerOuterBorderColor{
				BorderColor{ Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 } },
				BorderColor{ Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 } },
				BorderColor{ Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 } },
				BorderColor{ Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 } },
				BorderColor{ Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 } },
				BorderColor{ Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 } },
				BorderColor{ Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 }, Color{ 255, 252, 252, 255 } } },
			m_aTrackerInnerBorderColor{
				BorderColor{ Color{ 170, 173, 170, 255 }, Color{ 170, 173, 170, 255 }, Color{ 170, 173, 170, 255 }, Color{ 170, 173, 170, 255 } },
				BorderColor{ Color{  87, 148, 191, 255 }, Color{  87, 148, 191, 255 }, Color{  87, 148, 191, 255 }, Color{  87, 148, 191, 255 } },
				BorderColor{ Color{ 170, 173, 170, 255 }, Color{ 170, 173, 170, 255 }, Color{ 170, 173, 170, 255 }, Color{ 170, 173, 170, 255 } },
				BorderColor{ Color{  87, 148, 191, 255 }, Color{  87, 148, 191, 255 }, Color{  87, 148, 191, 255 }, Color{  87, 148, 191, 255 } },
				BorderColor{ Color{  61, 123, 173, 255 }, Color{  61, 123, 173, 255 }, Color{  61, 123, 173, 255 }, Color{  61, 123, 173, 255 } },
				BorderColor{ Color{  61, 123, 173, 255 }, Color{  61, 123, 173, 255 }, Color{  61, 123, 173, 255 }, Color{  61, 123, 173, 255 } },
				BorderColor{ Color{ 220, 220, 220, 255 }, Color{ 220, 220, 220, 255 }, Color{ 220, 220, 220, 255 }, Color{ 220, 220, 220, 255 } } },
			m_aTrackerBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 } },
			m_aTrackerBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aTickColor{
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 } },
			m_aBigTickColor{
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 },
				Color{ 210, 214, 210, 255 } },
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
			m_bIgnoreGradient{ false },
			m_pCanvas{ nullptr },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None }
		{
			OnChange = nullptr;
			setService(new CTrackRangeService(this), true);
			setSize(PointF{ 155, 30 });
		}

		CTrackRange::CTrackRange(IForm *parent) :CTrackRange()
		{
			setForm(parent);
		}

		CTrackRange::CTrackRange(IControl *parent) : CTrackRange()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CTrackRange::getRenderRect()
		{
			RectF result{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)State::Normal], m_aShadowShift[(int)State::Normal], m_aShadowRadius[(int)State::Normal]) };
			for (int i = (int)State::Normal + 1; i <= (int)State::Disabled; i++)
				result += AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
			return result;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CTrackRange::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBackPadding *= s;
				m_fBackMargin *= avg;
				m_sTickSize *= s;
				m_sBigTickSize *= s;
				m_sTrackerPadding *= s;
				m_fTrackerWidth *= s.X;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aBorderWidth[i] *= s;
					m_aBorderRadius[i] *= avg;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
					m_aBackBorderWidth[i] *= s;
					m_aBackBorderRadius[i] *= avg;
					m_aTrackerBorderRadius[i] *= avg;
					m_aTrackerOuterBorderWidth[i] *= s;
					m_aTrackerInnerBorderWidth[i] *= s;
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
		void CTrackRange::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region ITrackBar getters
		int CTrackRange::getMin()
		{
			return m_iMin;
		}

		int CTrackRange::getMax()
		{
			return m_iMax;
		}

		Point CTrackRange::getValue()
		{
			return m_sValue;
		}

		PointB CTrackRange::getTrackerEnabled()
		{
			return m_sTrackerEnabled;
		}

		PointB CTrackRange::getTrackerVisible()
		{
			return m_sTrackerVisible;
		}
	#pragma endregion

	#pragma region ITrackBar setters
		bool CTrackRange::setMin(const int value)
		{
			if (value != m_iMin)
			{
				m_iMin = value;
				if (m_iMax <= m_iMin)
					m_iMax = m_iMin + 1;
				m_sValue.X = ntl::Clamp<int>(m_sValue.X, m_iMin, m_iMax);
				m_sValue.Y = ntl::Clamp<int>(m_sValue.Y, m_iMin, m_iMax);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackRange::setMax(const int value)
		{
			if (value != m_iMax)
			{
				m_iMax = value;
				if (m_iMin >= m_iMax)
					m_iMin = m_iMax - 1;
				m_sValue.X = ntl::Clamp<int>(m_sValue.X, m_iMin, m_iMax);
				m_sValue.Y = ntl::Clamp<int>(m_sValue.Y, m_iMin, m_iMax);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return true;
		}

		bool CTrackRange::setValue(const Point &value)
		{
			Point v{ ntl::Clamp<int>(value.X, m_iMin, m_iMax), ntl::Clamp<int>(value.Y, m_iMin, m_iMax) };
			v.Y = ntl::Max<int>(v.X, v.Y);
			if (v != m_sValue)
			{
				m_sValue = v;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackRange::setTrackerEnabled(const PointB &value)
		{
			if (value != m_sTrackerEnabled)
			{
				m_sTrackerEnabled = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackRange::setTrackerVisible(const PointB &value)
		{
			if (value != m_sTrackerVisible)
			{
				m_sTrackerVisible = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackRange::setValue1(const int value)
		{
			int v{ ntl::Clamp<int>(value, m_iMin, m_iMax) };
			if (v != m_sValue.X)
			{
				m_sValue.X = v;
				m_sValue.Y = ntl::Max<int>(m_sValue.X, m_sValue.Y);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackRange::setValue2(const int value)
		{
			int v{ ntl::Clamp<int>(value, m_iMin, m_iMax) };
			if (v != m_sValue.Y)
			{
				m_sValue.Y = v;
				m_sValue.X = ntl::Min<int>(m_sValue.X, m_sValue.Y);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CTrackRange::State CTrackRange::getState()
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

		RectF CTrackRange::getBackPadding() const
		{
			return m_sBackPadding;
		}

		float CTrackRange::getBackMargin() const
		{
			return m_fBackMargin;
		}

		PointF CTrackRange::getTickSize() const
		{
			return m_sTickSize;
		}

		PointF CTrackRange::getBigTickSize() const
		{
			return m_sBigTickSize;
		}

		PointF CTrackRange::getTrackerPadding() const
		{
			return m_sTrackerPadding;
		}

		float CTrackRange::getTrackerWidth() const
		{
			return m_fTrackerWidth;
		}

		bool CTrackRange::isTopTicksVisible() const
		{
			return m_bTopTicksVisible;
		}

		bool CTrackRange::isBottomTicksVisible() const
		{
			return m_bBottomTicksVisible;
		}

		int CTrackRange::getTickInterval() const
		{
			return m_iTickInterval;
		}

		int CTrackRange::getBigTickInterval() const
		{
			return m_iBigTickInterval;
		}

		RectF CTrackRange::getBorderWidth(const State state) const
		{
			return m_aBorderWidth[(int)state];
		}

		RectF CTrackRange::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CTrackRange::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CTrackRange::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CTrackRange::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		int CTrackRange::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CTrackRange::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CTrackRange::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		RectF CTrackRange::getBackBorderWidth(const State state) const
		{
			return m_aBackBorderWidth[(int)state];
		}

		RectF CTrackRange::getBackBorderRadius(const State state) const
		{
			return m_aBackBorderRadius[(int)state];
		}

		BorderColor CTrackRange::getBackBorderColor(const State state) const
		{
			return m_aBackBorderColor[(int)state];
		}

		Color CTrackRange::getBackBackgroundColor(const State state) const
		{
			return m_aBackBackgroundColor[(int)state];
		}

		Gradient *CTrackRange::getBackBackgroundGradient(const State state)
		{
			return &m_aBackBackgroundGradient[(int)state];
		}

		Color CTrackRange::getBackSelectionBackgroundColor(const State state) const
		{
			return m_aBackSelectionBackgroundColor[(int)state];
		}

		Gradient *CTrackRange::getBackSelectionBackgroundGradient(const State state)
		{
			return &m_aBackSelectionBackgroundGradient[(int)state];
		}

		RectF CTrackRange::getTrackerBorderRadius(const State state) const
		{
			return m_aTrackerBorderRadius[(int)state];
		}

		RectF CTrackRange::getTrackerOuterBorderWidth(const State state) const
		{
			return m_aTrackerOuterBorderWidth[(int)state];
		}

		RectF CTrackRange::getTrackerInnerBorderWidth(const State state) const
		{
			return m_aTrackerInnerBorderWidth[(int)state];
		}

		BorderColor CTrackRange::getTrackerOuterBorderColor(const State state) const
		{
			return m_aTrackerOuterBorderColor[(int)state];
		}

		BorderColor CTrackRange::getTrackerInnerBorderColor(const State state) const
		{
			return m_aTrackerInnerBorderColor[(int)state];
		}

		Color CTrackRange::getTrackerBackgroundColor(const State state) const
		{
			return m_aTrackerBackgroundColor[(int)state];
		}

		Gradient *CTrackRange::getTrackerBackgroundGradient(const State state)
		{
			return &m_aTrackerBackgroundGradient[(int)state];
		}

		Color CTrackRange::getTickColor(const State state) const
		{
			return m_aTickColor[(int)state];
		}

		Color CTrackRange::getBigTickColor(const State state) const
		{
			return m_aBigTickColor[(int)state];
		}

		Color CTrackRange::getOutlineColor(const State state) const
		{
			return m_aOutlineColor[(int)state];
		}

		unsigned int CTrackRange::getOutlineMask(const State state) const
		{
			return m_aOutlineMask[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CTrackRange::setBackPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBackPadding))
			{
				m_sBackPadding = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTrackRange::setBackMargin(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fBackMargin))
			{
				m_fBackMargin = value;
				if (m_bTopTicksVisible || m_bBottomTicksVisible)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTickSize(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sTickSize))
			{
				m_sTickSize = value;
				if (m_bTopTicksVisible || m_bBottomTicksVisible)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setBigTickSize(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sBigTickSize))
			{
				m_sBigTickSize = value;
				if ((m_bTopTicksVisible || m_bBottomTicksVisible) && m_iTickInterval > 0 && m_iBigTickInterval > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTrackerPadding(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sTrackerPadding))
			{
				m_sTrackerPadding = value;
				if (m_sTrackerVisible.X || m_sTrackerVisible.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTrackerWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fTrackerWidth))
			{
				m_fTrackerWidth = value;
				if (m_sTrackerVisible.X || m_sTrackerVisible.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTopTicksVisible(const bool value)
		{
			if (value != m_bTopTicksVisible)
			{
				m_bTopTicksVisible = value;
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

		bool CTrackRange::setBottomTicksVisible(const bool value)
		{
			if (value != m_bBottomTicksVisible)
			{
				m_bBottomTicksVisible = value;
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

		bool CTrackRange::setTickInterval(const int value)
		{
			if (value >= 0 && value != m_iTickInterval)
			{
				m_iTickInterval = value;
				if (m_bTopTicksVisible || m_bBottomTicksVisible)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setBigTickInterval(const int value)
		{
			if (value >= 0 && value != m_iBigTickInterval)
			{
				m_iBigTickInterval = value;
				if (m_iTickInterval > 0 && (m_bTopTicksVisible || m_bBottomTicksVisible) && m_iBigTickInterval > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setBorderWidth(const State state, const RectF &value)
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

		bool CTrackRange::setBorderRadius(const State state, const RectF &value)
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

		bool CTrackRange::setBorderColor(const State state, const BorderColor &value)
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

		bool CTrackRange::setBackgroundColor(const State state, const Color &value)
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

		bool CTrackRange::setShadowRadius(const State state, const int value)
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

		bool CTrackRange::setShadowShift(const State state, const PointF &value)
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

		bool CTrackRange::setShadowColor(const State state, const Color &value)
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

		bool CTrackRange::setBackBorderWidth(const State state, const RectF &value)
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

		bool CTrackRange::setBackBorderRadius(const State state, const RectF &value)
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

		bool CTrackRange::setBackBorderColor(const State state, const BorderColor &value)
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

		bool CTrackRange::setBackBackgroundColor(const State state, const Color &value)
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

		bool CTrackRange::setBackSelectionBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackSelectionBackgroundColor[(int)state])
			{
				m_aBackSelectionBackgroundColor[(int)state] = value;
				if (m_aBackSelectionBackgroundGradient[(int)state].getPointCount() < 2 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTrackerBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aTrackerBorderRadius[(int)state]))
			{
				m_aTrackerBorderRadius[(int)state] = value;
				if ((m_sTrackerVisible.X || m_sTrackerVisible.Y) && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTrackerOuterBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aTrackerOuterBorderWidth[(int)state]))
			{
				m_aTrackerOuterBorderWidth[(int)state] = value;
				if ((m_sTrackerVisible.X || m_sTrackerVisible.Y) && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTrackerInnerBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aTrackerInnerBorderWidth[(int)state]))
			{
				m_aTrackerInnerBorderWidth[(int)state] = value;
				if ((m_sTrackerVisible.X || m_sTrackerVisible.Y) && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTrackerOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aTrackerOuterBorderColor[(int)state])
			{
				m_aTrackerOuterBorderColor[(int)state] = value;
				if ((m_sTrackerVisible.X || m_sTrackerVisible.Y) && m_aTrackerOuterBorderWidth[(int)state].has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTrackerInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aTrackerInnerBorderColor[(int)state])
			{
				m_aTrackerInnerBorderColor[(int)state] = value;
				if ((m_sTrackerVisible.X || m_sTrackerVisible.Y) && m_aTrackerInnerBorderWidth[(int)state].has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTrackerBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aTrackerBackgroundColor[(int)state])
			{
				m_aTrackerBackgroundColor[(int)state] = value;
				if ((m_sTrackerVisible.X || m_sTrackerVisible.Y) && m_aTrackerBackgroundGradient[(int)state].getPointCount() < 2 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setTickColor(const State state, const Color &value)
		{
			if (value != m_aTickColor[(int)state])
			{
				m_aTickColor[(int)state] = value;
				if (m_iTickInterval > 0 && (m_bTopTicksVisible || m_bBottomTicksVisible) && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setBigTickColor(const State state, const Color &value)
		{
			if (value != m_aBigTickColor[(int)state])
			{
				m_aBigTickColor[(int)state] = value;
				if (m_iTickInterval > 0 && m_iBigTickInterval > 0 && (m_bTopTicksVisible || m_bBottomTicksVisible) && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTrackRange::setOutlineColor(const State state, const Color &value)
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

		bool CTrackRange::setOutlineMask(const State state, const unsigned int value)
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
		void CTrackRange::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BackPadding", m_sBackPadding);
			style->getOption(m_sClassName + L".BackMargin", m_fBackMargin);
			style->getOption(m_sClassName + L".TickSize", m_sTickSize);
			style->getOption(m_sClassName + L".BigTickSize", m_sBigTickSize);
			style->getOption(m_sClassName + L".TrackerPadding", m_sTrackerPadding);
			style->getOption(m_sClassName + L".TrackerWidth", m_fTrackerWidth);
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
				style->getOption(m_sClassName + L".BackSelectionBackgroundColor[" + state + L"]", m_aBackSelectionBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackSelectionBackgroundGradient[" + state + L"]", m_aBackSelectionBackgroundGradient[i]);
				style->getOption(m_sClassName + L".TrackerBorderRadius[" + state + L"]", m_aTrackerBorderRadius[i]);
				style->getOption(m_sClassName + L".TrackerOuterBorderWidth[" + state + L"]", m_aTrackerOuterBorderWidth[i]);
				style->getOption(m_sClassName + L".TrackerInnerBorderWidth[" + state + L"]", m_aTrackerInnerBorderWidth[i]);
				style->getOption(m_sClassName + L".TrackerOuterBorderColor[" + state + L"]", m_aTrackerOuterBorderColor[i]);
				style->getOption(m_sClassName + L".TrackerInnerBorderColor[" + state + L"]", m_aTrackerInnerBorderColor[i]);
				style->getOption(m_sClassName + L".TrackerBackgroundColor[" + state + L"]", m_aTrackerBackgroundColor[i]);
				style->getOption(m_sClassName + L".TrackerBackgroundGradient[" + state + L"]", m_aTrackerBackgroundGradient[i]);
				style->getOption(m_sClassName + L".TickColor[" + state + L"]", m_aTickColor[i]);
				style->getOption(m_sClassName + L".BigTickColor[" + state + L"]", m_aBigTickColor[i]);
				style->getOption(m_sClassName + L".OutlineColor[" + state + L"]", m_aOutlineColor[i]);
				style->getOption(m_sClassName + L".OutlineMask[" + state + L"]", m_aOutlineMask[i]);
			}
			m_bIgnoreGradient = false;
		}

		CTrackRange::State CTrackRange::getTracker1State()
		{
			if (!m_sTrackerEnabled.X || !isEnabled(false))
				return State::Disabled;
			if (m_eDownElement == Element::Tracker1)
			{
				if (m_eHoveredElement == Element::Tracker1)
					return State::ActiveHovered;
				return State::Active;
			}
			if (isFocused())
			{
				if (m_eHoveredElement == Element::Tracker1)
					return State::FocusedHovered;
				return State::Focused;
			}
			if (m_eHoveredElement == Element::Tracker1)
				return State::Hovered;
			return State::Normal;
		}

		CTrackRange::State CTrackRange::getTracker2State()
		{
			if (!m_sTrackerEnabled.Y || !isEnabled(false))
				return State::Disabled;
			if (m_eDownElement == Element::Tracker2)
			{
				if (m_eHoveredElement == Element::Tracker2)
					return State::ActiveHovered;
				return State::Active;
			}
			if (isFocused())
			{
				if (m_eHoveredElement == Element::Tracker2)
					return State::FocusedHovered;
				return State::Focused;
			}
			if (m_eHoveredElement == Element::Tracker2)
				return State::Hovered;
			return State::Normal;
		}

		RectF CTrackRange::getTracker1Rect()
		{
			RectF back{ getBackRect() };
			PointF size{ m_fTrackerWidth, getHeight() - m_sTrackerPadding.X - m_sTrackerPadding.Y };
			float x{ back.Left + float(m_sValue.X - m_iMin) * (back.width() - 1) / float(m_iMax - m_iMin) - size.X * 0.5f };
			return RectF{ x, m_sTrackerPadding.X, x + m_fTrackerWidth, getHeight() - m_sTrackerPadding.Y };
		}

		RectF CTrackRange::getTracker2Rect()
		{
			RectF back{ getBackRect() };
			PointF size{ m_fTrackerWidth, getHeight() - m_sTrackerPadding.X - m_sTrackerPadding.Y };
			float x{ back.Left + float(m_sValue.Y - m_iMin) * (back.width() - 1) / float(m_iMax - m_iMin) - size.X * 0.5f };
			return RectF{ x, m_sTrackerPadding.X, x + m_fTrackerWidth, getHeight() - m_sTrackerPadding.Y };
		}

		RectF CTrackRange::getBackRect()
		{
			return RectF{ m_sBackPadding.Left, m_sBackPadding.Top, getWidth() - m_sBackPadding.Right, getHeight() - m_sBackPadding.Bottom };
		}

		bool CTrackRange::UpdateHoveredElement(const PointF &position)
		{
			Element el{ Element::None };
			if (isEnabled(true))
			{
				RectF client{ getClientRect() };
				if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
				{
					if (m_sTrackerVisible.X)
					{
						RectF r{ getTracker1Rect() };
						if (r.is_valid() && !r.is_zero() && position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
							el = Element::Tracker1;
					}
					if (el == Element::None && m_sTrackerVisible.Y)
					{
						RectF r{ getTracker2Rect() };
						if (r.is_valid() && !r.is_zero() && position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
							el = Element::Tracker2;
					}
					if (el == Element::None)
					{
						RectF r{ getBackRect() };
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

		int CTrackRange::ClientToValue(const PointF &position)
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
		void CTrackRange::Render()
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
						RenderTrackers(renderer, r);
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
					RenderTrackers(renderer, rect);
					RenderOutline(renderer, rect, state);
				}
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CTrackRange::RenderBack(IRenderer *renderer, const RectF &rect, const State state)
		{
			RectF back{
				rect.Left + m_sBackPadding.Left,
				rect.Top + m_sBackPadding.Top,
				rect.Right - m_sBackPadding.Right,
				rect.Bottom - m_sBackPadding.Bottom };
			PointF s{
				float(m_sValue.X - m_iMin) * (back.width() - m_aBackBorderWidth[(int)state].Left - m_aBackBorderWidth[(int)state].Right) / float(m_iMax - m_iMin),
				float(m_sValue.Y - m_iMin) * (back.width() - m_aBackBorderWidth[(int)state].Left - m_aBackBorderWidth[(int)state].Right) / float(m_iMax - m_iMin) };
			RectF r1{ back.Left, back.Top, ntl::Min<float>(back.Right, back.Left + ntl::Min<float>(s.X, s.Y) + m_aBackBorderWidth[(int)state].Left), back.Bottom };
			RectF r2{ r1.Right, back.Top, back.Left + ntl::Min<float>(back.Right, ntl::Max<float>(s.X, s.Y) + m_aBackBorderWidth[(int)state].Left), back.Bottom };
			RectF r3{ r2.Right, back.Top, back.Right, back.Bottom };
			if (r2.is_zero()) // No selection
			{
				if (back.is_valid() && !back.is_zero())
				{
					if (m_aBackBorderWidth[(int)state].has_positive() || m_aBackBorderRadius[(int)state].has_positive())
					{
						Block b{ back, m_aBackBorderWidth[(int)state], m_aBackBorderRadius[(int)state], PointLocation::Inside };
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
								->DrawGradient(back, m_aBackBackgroundGradient[(int)state]);
						}
						renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
					}
					else
					{
						if (m_aBackBackgroundGradient[(int)state].getPointCount() >= 2)
							renderer->DrawGradient(back, m_aBackBackgroundGradient[(int)state]);
						else if (m_aBackBackgroundColor[(int)state].A > 0)
							renderer->DrawRectangle(back, m_aBackBackgroundColor[(int)state]);
					}
				}
			}
			else
			{
				if (r1.is_valid() && !r1.is_zero())
				{
					Block b{ r1, RectF{ m_aBackBorderWidth[(int)state].Left, m_aBackBorderWidth[(int)state].Top, 0, m_aBackBorderWidth[(int)state].Bottom }, RectF{ m_aBackBorderRadius[(int)state].Left,
						0, 0, m_aBackBorderRadius[(int)state].Bottom }, PointLocation::Inside };
					if (m_aBackBorderWidth[(int)state].has_positive() || m_aBackBorderRadius[(int)state].has_positive())
					{
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
								->DrawGradient(back, m_aBackBackgroundGradient[(int)state]);
						}
						renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
					}
					else
					{
						if (m_aBackBackgroundGradient[(int)state].getPointCount() >= 2)
						{
							CStoreBlock s_block{ renderer };
							renderer
								->ActivateBlock(&b)
								->DrawGradient(back, m_aBackBackgroundGradient[(int)state]);
						}
						else if (m_aBackBackgroundColor[(int)state].A > 0)
							renderer->DrawRectangle(r1, m_aBackBackgroundColor[(int)state]);
					}
				}
				if (m_aBackBorderWidth[(int)state].has_positive() || m_aBackBorderRadius[(int)state].has_positive())
				{
					Block b{ r2, RectF{ 0, m_aBackBorderWidth[(int)state].Top, 0, m_aBackBorderWidth[(int)state].Bottom }, RectF{ 0, 0, 0, 0 }, PointLocation::Inside };
					BlockColors colors{
						Color{ 0, 0, 0, 0 },
						m_aBackBorderColor[(int)state].Top,
						Color{ 0, 0, 0, 0 },
						m_aBackBorderColor[(int)state].Bottom,
						m_aBackSelectionBackgroundGradient[(int)state].getPointCount() >= 2 ? Color{ 0, 0, 0, 0 } : m_aBackSelectionBackgroundColor[(int)state],
						Color{ 0, 0, 0, 0 }
					};
					if (m_aBackSelectionBackgroundGradient[(int)state].getPointCount() >= 2)
					{
						CStoreBlock s_block{ renderer };
						renderer
							->ActivateBlock(&b)
							->DrawGradient(r2, m_aBackSelectionBackgroundGradient[(int)state]);
					}
					renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
				}
				else
				{
					if (m_aBackSelectionBackgroundGradient[(int)state].getPointCount() >= 2)
						renderer->DrawGradient(r2, m_aBackSelectionBackgroundGradient[(int)state]);
					else if (m_aBackSelectionBackgroundColor[(int)state].A > 0)
						renderer->DrawRectangle(r2, m_aBackSelectionBackgroundColor[(int)state]);
				}
				if (r3.is_valid() && !r3.is_zero())
				{
					Block b{ r3, RectF{ 0, m_aBackBorderWidth[(int)state].Top, m_aBackBorderWidth[(int)state].Right, m_aBackBorderWidth[(int)state].Bottom }, RectF{ 0, 
						m_aBackBorderRadius[(int)state].Top, m_aBackBorderRadius[(int)state].Right, 0 }, PointLocation::Inside };
					if (m_aBackBorderWidth[(int)state].has_positive() || m_aBackBorderRadius[(int)state].has_positive())
					{
						BlockColors colors{
							Color{ 0, 0, 0, 0 },
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
								->DrawGradient(back, m_aBackBackgroundGradient[(int)state]);
						}
						renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
					}
					else
					{
						if (m_aBackBackgroundGradient[(int)state].getPointCount() >= 2)
						{
							CStoreBlock s_block{ renderer };
							renderer
								->ActivateBlock(&b)
								->DrawGradient(back, m_aBackBackgroundGradient[(int)state]);
						}
						else if (m_aBackBackgroundColor[(int)state].A > 0)
							renderer->DrawRectangle(r3, m_aBackBackgroundColor[(int)state]);
					}
				}
			}
		}

		void CTrackRange::RenderTicks(IRenderer *renderer, const RectF &rect, const State state)
		{
			if (m_iTickInterval > 0 && (m_bTopTicksVisible || m_bBottomTicksVisible))
			{
				RectF back{
					rect.Left + m_sBackPadding.Left,
					rect.Top + m_sBackPadding.Top,
					rect.Right - m_sBackPadding.Right,
					rect.Bottom - m_sBackPadding.Bottom };
				if (back.is_valid() && !back.is_zero())
				{
					PointF small1{ back.Top - m_fBackMargin - m_sTickSize.Y, back.Top - m_fBackMargin };
					PointF small2{ back.Bottom + m_fBackMargin, back.Bottom + m_fBackMargin + m_sTickSize.Y };
					PointF big1{ back.Top - m_fBackMargin - m_sBigTickSize.Y, back.Top - m_fBackMargin };
					PointF big2{ back.Bottom + m_fBackMargin, back.Bottom + m_fBackMargin + m_sBigTickSize.Y };
					int tick{ m_iMin }, index{ 0 };
					float x, t;
					while (tick <= m_iMax)
					{
						x = back.Left + float(tick - m_iMin) * (back.width() - 1) / float(m_iMax - m_iMin);
						if (m_iBigTickInterval > 0 && index % m_iBigTickInterval == 0)
						{
							if (ntl::IsGreater<float>(m_sBigTickSize.X, 0) && ntl::IsGreater<float>(m_sBigTickSize.Y, 0) && m_aBigTickColor[(int)state].A > 0)
							{
								t = x - m_sBigTickSize.X * 0.5f;
								if (m_bTopTicksVisible)
									renderer->DrawRectangle(RectF{ t, big1.X, t + m_sBigTickSize.X, big1.Y }, m_aBigTickColor[(int)state]);
								if (m_bBottomTicksVisible)
									renderer->DrawRectangle(RectF{ t, big2.X, t + m_sBigTickSize.X, big2.Y }, m_aBigTickColor[(int)state]);
							}
						}
						else
						{
							if (ntl::IsGreater<float>(m_sTickSize.X, 0) && ntl::IsGreater<float>(m_sTickSize.Y, 0) && m_aTickColor[(int)state].A > 0)
							{
								t = x - m_sTickSize.X * 0.5f;
								if (m_bTopTicksVisible)
									renderer->DrawRectangle(RectF{ t, small1.X, t + m_sTickSize.X, small1.Y }, m_aTickColor[(int)state]);
								if (m_bBottomTicksVisible)
									renderer->DrawRectangle(RectF{ t, small2.X, t + m_sTickSize.X, small2.Y }, m_aTickColor[(int)state]);
							}
						}
						tick += m_iTickInterval;
						index++;
					}
				}
			}
		}

		void CTrackRange::RenderTrackers(IRenderer *renderer, const RectF &rect)
		{
			if (m_sTrackerVisible.X || m_sTrackerVisible.Y)
			{
				PointF size{ m_fTrackerWidth, rect.height() - m_sTrackerPadding.X - m_sTrackerPadding.Y };
				if (ntl::IsGreater<float>(size.X, 0) && ntl::IsGreater<float>(size.Y, 0))
				{
					RectF back{
						rect.Left + m_sBackPadding.Left,
						rect.Top + m_sBackPadding.Top,
						rect.Right - m_sBackPadding.Right,
						rect.Bottom - m_sBackPadding.Bottom };
					if (back.is_valid() && !back.is_zero())
					{
						if (m_sTrackerVisible.X)
						{
							float x{ std::round(back.Left + float(m_sValue.X - m_iMin) * (back.width() - 1) / float(m_iMax - m_iMin) - size.X * 0.5f) };
							RectF r{ x, rect.Top + m_sTrackerPadding.X, x + m_fTrackerWidth, rect.Bottom - m_sTrackerPadding.Y };
							if (r.is_valid() && !r.is_zero())
								RenderTracker(renderer, r, getTracker1State());
						}
						if (m_sTrackerVisible.Y)
						{
							float x{ std::round(back.Left + float(m_sValue.Y - m_iMin) * (back.width() - 1) / float(m_iMax - m_iMin) - size.X * 0.5f) };
							RectF r{ x, rect.Top + m_sTrackerPadding.X, x + m_fTrackerWidth, rect.Bottom - m_sTrackerPadding.Y };
							if (r.is_valid() && !r.is_zero())
								RenderTracker(renderer, r, getTracker2State());
						}
					}
				}
			}
		}

		void CTrackRange::RenderTracker(IRenderer *renderer, const RectF &rect, const State state)
		{
			if (m_aTrackerOuterBorderWidth[(int)state].has_positive() || m_aTrackerInnerBorderWidth[(int)state].has_positive() || m_aTrackerBorderRadius[(int)state].has_positive())
			{
				DrawDoubleBackground(
					renderer,
					rect,
					m_aTrackerOuterBorderWidth[(int)state],
					m_aTrackerInnerBorderWidth[(int)state],
					m_aTrackerBorderRadius[(int)state],
					m_aTrackerOuterBorderColor[(int)state],
					m_aTrackerInnerBorderColor[(int)state],
					m_aTrackerBackgroundColor[(int)state],
					m_aTrackerBackgroundGradient[(int)state]);
			}
		}

		void CTrackRange::RenderOutline(IRenderer *renderer, const RectF &rect, const State state)
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