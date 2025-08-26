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
		CProgressBar::CGradientListener::CGradientListener(CProgressBar *control) :
			m_pControl{ control }
		{

		}

		void CProgressBar::CGradientListener::NotifyOnChange()
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
		CProgressBar::CProgressBar() :
			CControl(L"ProgressBar", true, true, false, false, false, false),
			m_cGradientListener{ this },
			m_fMin{ 0 },
			m_fMax{ 100 },
			m_fProgress{ 0 },
			m_eCaptionHorizontalAlign{ TextAlign::Center },
			m_eCaptionVerticalAlign{ VerticalAlign::Middle },
			m_bSmooth{ false },
			m_fBarSize{ 8 },
			m_fBarInterval{ 0 },
			m_sShadowColor{ 0, 0, 0, 0 },
			m_sShadowShift{ 0, 0 },
			m_iShadowRadius{ 1 },
			m_sOuterBorderWidth{ 1, 1, 1, 1 },
			m_sInnerBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 2, 2, 2, 2 },
			m_sOuterBorderColor{ Color{ 120, 120, 120, 255 }, Color{ 120, 120, 120, 255 }, Color{ 120, 120, 120, 255 }, Color{ 120, 120, 120, 255 } },
			m_sInnerBorderColor{ Color{ 210, 210, 210, 255 }, Color{ 210, 210, 210, 255 }, Color{ 210, 210, 210, 255 }, Color{ 210, 210, 210, 255 } },
			m_sBackgroundColor{ 255, 255, 255, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_sForegroundColor{ 1, 2, 129, 255 },
			m_cForegroundGradient{ &m_cGradientListener },
			m_sBarBorderWidth{ 1, 1, 1, 1 },
			m_sBarBorderRadius{ 0, 0, 0, 0 },
			m_sBarBorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_sBarColor{ 1, 2, 129, 255 },
			m_cBarGradient{ &m_cGradientListener },
			m_sCaptionPadding{ 4, 0, 4, 0 },
			m_eFillDirection{ FillDirection::LeftToRight },
			m_bIgnoreGradient{ true },
			m_pCanvas{ nullptr }
		{
			setService(new CProgressBarService(this), true);
			setSize(PointF{ 150, 17 });
			m_cBarGradient.setPointCount(3);
			m_cBarGradient.setPointColor(0, Color{ 171, 237, 172, 255 });
			m_cBarGradient.setPointColor(1, Color{ 46, 211, 49, 255 });
			m_cBarGradient.setPointColor(2, Color{ 142, 231, 144, 255 });
			m_bIgnoreGradient = false;
		}

		CProgressBar::CProgressBar(IForm *parent) :CProgressBar()
		{
			setForm(parent);
		}

		CProgressBar::CProgressBar(IControl *parent) : CProgressBar()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		RectF CProgressBar::getClientRect()
		{
			RectF result{
				m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left, m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top,
				getWidth() - m_sOuterBorderWidth.Right - m_sInnerBorderWidth.Right, getHeight() - m_sOuterBorderWidth.Bottom - m_sInnerBorderWidth.Bottom
			};
			result.validate();
			return result;
		}

		RectF CProgressBar::getRenderRect()
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
		}

		float CProgressBar::getMin()
		{
			return m_fMin;
		}

		float CProgressBar::getMax()
		{
			return m_fMax;
		}

		float CProgressBar::getProgress()
		{
			return m_fProgress;
		}
	#pragma endregion

	#pragma region Getters
		const String &CProgressBar::getCaption() const
		{
			return m_sCaption;
		}

		TextAlign CProgressBar::getCaptionHorizontalAlign() const
		{
			return m_eCaptionHorizontalAlign;
		}

		VerticalAlign CProgressBar::getCaptionVerticalAlign() const
		{
			return m_eCaptionVerticalAlign;
		}

		bool CProgressBar::isSmooth() const
		{
			return m_bSmooth;
		}

		float CProgressBar::getBarSize() const
		{
			return m_fBarSize;
		}

		float CProgressBar::getBarInterval() const
		{
			return m_fBarInterval;
		}

		Color CProgressBar::getShadowColor() const
		{
			return m_sShadowColor;
		}

		PointF CProgressBar::getShadowShift() const
		{
			return m_sShadowShift;
		}

		int CProgressBar::getShadowRadius() const
		{
			return m_iShadowRadius;
		}

		RectF CProgressBar::getOuterBorderWidth() const
		{
			return m_sOuterBorderWidth;
		}

		RectF CProgressBar::getInnerBorderWidth() const
		{
			return m_sInnerBorderWidth;
		}

		RectF CProgressBar::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		BorderColor CProgressBar::getOuterBorderColor() const
		{
			return m_sOuterBorderColor;
		}

		Color CProgressBar::getLeftOuterBorderColor() const
		{
			return m_sOuterBorderColor.Left;
		}

		Color CProgressBar::getTopOuterBorderColor() const
		{
			return m_sOuterBorderColor.Top;
		}

		Color CProgressBar::getRightOuterBorderColor() const
		{
			return m_sOuterBorderColor.Right;
		}

		Color CProgressBar::getBottomOuterBorderColor() const
		{
			return m_sOuterBorderColor.Bottom;
		}

		BorderColor CProgressBar::getInnerBorderColor() const
		{
			return m_sInnerBorderColor;
		}

		Color CProgressBar::getLeftInnerBorderColor() const
		{
			return m_sInnerBorderColor.Left;
		}

		Color CProgressBar::getTopInnerBorderColor() const
		{
			return m_sInnerBorderColor.Right;
		}

		Color CProgressBar::getRightInnerBorderColor() const
		{
			return m_sInnerBorderColor.Right;
		}

		Color CProgressBar::getBottomInnerBorderColor() const
		{
			return m_sInnerBorderColor.Bottom;
		}

		Color CProgressBar::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CProgressBar::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		Color CProgressBar::getForegroundColor() const
		{
			return m_sForegroundColor;
		}

		Gradient *CProgressBar::getForegroundGradient()
		{
			return &m_cForegroundGradient;
		}

		RectF CProgressBar::getBarBorderWidth() const
		{
			return m_sBarBorderWidth;
		}

		RectF CProgressBar::getBarBorderRadius() const
		{
			return m_sBarBorderRadius;
		}

		BorderColor CProgressBar::getBarBorderColor() const
		{
			return m_sBarBorderColor;
		}

		Color CProgressBar::getBarLeftBorderColor() const
		{
			return m_sBarBorderColor.Left;
		}

		Color CProgressBar::getBarTopBorderColor() const
		{
			return m_sBarBorderColor.Top;
		}

		Color CProgressBar::getBarRightBorderColor() const
		{
			return m_sBarBorderColor.Right;
		}

		Color CProgressBar::getBarBottomBorderColor() const
		{
			return m_sBarBorderColor.Bottom;
		}

		Color CProgressBar::getBarColor() const
		{
			return m_sBarColor;
		}

		Gradient *CProgressBar::getBarGradient()
		{
			return &m_cBarGradient;
		}

		RectF CProgressBar::getCaptionPadding() const
		{
			return m_sCaptionPadding;
		}

		CProgressBar::FillDirection CProgressBar::getFillDirection() const
		{
			return m_eFillDirection;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CProgressBar::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_fBarSize *= avg;
				m_fBarInterval *= avg;
				m_sShadowShift *= s;
				m_iShadowRadius = ntl::Round<int>((float)m_iShadowRadius * avg);
				m_sOuterBorderWidth *= s;
				m_sInnerBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sBarBorderWidth *= s;
				m_sBarBorderRadius *= avg;
				m_sCaptionPadding *= s;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CProgressBar::setMin(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMin))
			{
				m_fMin = value;
				if (ntl::IsLessOrEqual<float>(m_fMax, m_fMin))
					m_fMax = m_fMin + 1;
				m_fProgress = ntl::Clamp<float>(m_fProgress, m_fMin, m_fMax);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CProgressBar::setMax(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMax))
			{
				m_fMax = value;
				if (ntl::IsGreaterOrEqual<float>(m_fMin, m_fMax))
					m_fMin = m_fMax - 1;
				m_fProgress = ntl::Clamp<float>(m_fProgress, m_fMin, m_fMax);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CProgressBar::setProgress(const float value)
		{
			float v{ ntl::Clamp<float>(value, m_fMin, m_fMax) };
			if (ntl::IsNotEqual<float>(v, m_fProgress))
			{
				m_fProgress = v;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CProgressBar::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CProgressBar::setCaptionHorizontalAlign(const TextAlign value)
		{
			if (value != m_eCaptionHorizontalAlign)
			{
				m_eCaptionHorizontalAlign = value;
				if (!m_sCaption.empty())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setCaptionVerticalAlign(const VerticalAlign value)
		{
			if (value != m_eCaptionVerticalAlign)
			{
				m_eCaptionVerticalAlign = value;
				if (!m_sCaption.empty())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setSmooth(const bool value)
		{
			if (value != m_bSmooth)
			{
				m_bSmooth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CProgressBar::setBarSize(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fBarSize))
			{
				m_fBarSize = value;
				if (!m_bSmooth)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setBarInterval(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fBarInterval))
			{
				m_fBarInterval = value;
				if (!m_bSmooth)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setShadowColor(const Color &value)
		{
			if (value != m_sShadowColor)
			{
				m_sShadowColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CProgressBar::setShadowShift(const PointF &value)
		{
			if (IsNotEqual(value, m_sShadowShift))
			{
				CLockRepaint lock{ this };
				if (m_sShadowColor.A > 0)
					Repaint(false);
				m_sShadowShift = value;
				if (m_sShadowColor.A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setShadowRadius(const int value)
		{
			if (value >= 1 && value != m_iShadowRadius)
			{
				CLockRepaint lock{ this };
				if (m_sShadowColor.A > 0)
					Repaint(false);
				m_iShadowRadius = value;
				if (m_sShadowColor.A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setOuterBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sOuterBorderWidth))
			{
				m_sOuterBorderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CProgressBar::setInnerBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sInnerBorderWidth))
			{
				m_sInnerBorderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CProgressBar::setBorderRadius(const RectF &value)
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

		bool CProgressBar::setOuterBorderColor(const BorderColor &value)
		{
			if (value != m_sOuterBorderColor)
			{
				m_sOuterBorderColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CProgressBar::setLeftOuterBorderColor(const Color &value)
		{
			return setOuterBorderColor(BorderColor{ value, m_sOuterBorderColor.Top, m_sOuterBorderColor.Right, m_sOuterBorderColor.Bottom });
		}

		bool CProgressBar::setTopOuterBorderColor(const Color &value)
		{
			return setOuterBorderColor(BorderColor{ m_sOuterBorderColor.Left, value, m_sOuterBorderColor.Right, m_sOuterBorderColor.Bottom });
		}

		bool CProgressBar::setRightOuterBorderColor(const Color &value)
		{
			return setOuterBorderColor(BorderColor{ m_sOuterBorderColor.Left, m_sOuterBorderColor.Top, value, m_sOuterBorderColor.Bottom });
		}

		bool CProgressBar::setBottomOuterBorderColor(const Color &value)
		{
			return setOuterBorderColor(BorderColor{ m_sOuterBorderColor.Left, m_sOuterBorderColor.Top, m_sOuterBorderColor.Right, value });
		}

		bool CProgressBar::setInnerBorderColor(const BorderColor &value)
		{
			if (value != m_sInnerBorderColor)
			{
				m_sInnerBorderColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CProgressBar::setLeftInnerBorderColor(const Color &value)
		{
			return setInnerBorderColor(BorderColor{ value, m_sInnerBorderColor.Top, m_sInnerBorderColor.Right, m_sInnerBorderColor.Bottom });
		}

		bool CProgressBar::setTopInnerBorderColor(const Color &value)
		{
			return setInnerBorderColor(BorderColor{ m_sInnerBorderColor.Left, value, m_sInnerBorderColor.Right, m_sInnerBorderColor.Bottom });
		}

		bool CProgressBar::setRightInnerBorderColor(const Color &value)
		{
			return setInnerBorderColor(BorderColor{ m_sInnerBorderColor.Left, m_sInnerBorderColor.Top, value, m_sInnerBorderColor.Bottom });
		}

		bool CProgressBar::setBottomInnerBorderColor(const Color &value)
		{
			return setInnerBorderColor(BorderColor{ m_sInnerBorderColor.Left, m_sInnerBorderColor.Top, m_sInnerBorderColor.Right, value });
		}

		bool CProgressBar::setBackgroundColor(const Color &value)
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

		bool CProgressBar::setForegroundColor(const Color &value)
		{
			if (value != m_sForegroundColor)
			{
				m_sForegroundColor = value;
				if (m_bSmooth)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setBarBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBarBorderWidth))
			{
				m_sBarBorderWidth = value;
				if (!m_bSmooth)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setBarBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBarBorderRadius))
			{
				m_sBarBorderRadius = value;
				if (!m_bSmooth)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setBarBorderColor(const BorderColor &value)
		{
			if (value != m_sBarBorderColor)
			{
				m_sBarBorderColor = value;
				if (!m_bSmooth)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setBarLeftBorderColor(const Color &value)
		{
			return setBarBorderColor(BorderColor{ value, m_sBarBorderColor.Top, m_sBarBorderColor.Right, m_sBarBorderColor.Bottom });
		}

		bool CProgressBar::setBarTopBorderColor(const Color &value)
		{
			return setBarBorderColor(BorderColor{ m_sBarBorderColor.Left, value, m_sBarBorderColor.Right, m_sBarBorderColor.Bottom });
		}

		bool CProgressBar::setBarRightBorderColor(const Color &value)
		{
			return setBarBorderColor(BorderColor{ m_sBarBorderColor.Left, m_sBarBorderColor.Top, value, m_sBarBorderColor.Bottom });
		}

		bool CProgressBar::setBarBottomBorderColor(const Color &value)
		{
			return setBarBorderColor(BorderColor{ m_sBarBorderColor.Left, m_sBarBorderColor.Top, m_sBarBorderColor.Right, value });
		}

		bool CProgressBar::setBarColor(const Color &value)
		{
			if (value != m_sBarColor)
			{
				m_sBarColor = value;
				if (!m_bSmooth)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setCaptionPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sCaptionPadding))
			{
				m_sCaptionPadding = value;
				if (!m_sCaption.empty())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CProgressBar::setFillDirection(const FillDirection value)
		{
			if (value != m_eFillDirection)
			{
				m_eFillDirection = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CProgressBar::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CProgressBar::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".Smooth", m_bSmooth);
			style->getOption(m_sClassName + L".BarSize", m_fBarSize);
			style->getOption(m_sClassName + L".BarInterval", m_fBarInterval);
			style->getOption(m_sClassName + L".ShadowColor", m_sShadowColor);
			style->getOption(m_sClassName + L".ShadowShift", m_sShadowShift);
			style->getOption(m_sClassName + L".ShadowRadius", m_iShadowRadius);
			style->getOption(m_sClassName + L".OuterBorderWidth", m_sOuterBorderWidth);
			style->getOption(m_sClassName + L".InnerBorderWidth", m_sInnerBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".OuterBorderColor", m_sOuterBorderColor);
			style->getOption(m_sClassName + L".InnerBorderColor", m_sInnerBorderColor);
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".ForegroungColor", m_sForegroundColor);
			style->getOption(m_sClassName + L".ForegroundGradient", m_cForegroundGradient);
			style->getOption(m_sClassName + L".BarBorderWidth", m_sBarBorderWidth);
			style->getOption(m_sClassName + L".BarBorderRadius", m_sBarBorderRadius);
			style->getOption(m_sClassName + L".BarBorderColor", m_sBarBorderColor);
			style->getOption(m_sClassName + L".BarColor", m_sBarColor);
			style->getOption(m_sClassName + L".BarGradient", m_cBarGradient);
			m_bIgnoreGradient = false;
		}

		PointF CProgressBar::CalculateCaptionPosition(IPlatformFont *pf)
		{
			if (!m_sCaption.empty())
			{
				RectF client{ getClientRect() };
				client.Left += m_sCaptionPadding.Left;
				client.Top += m_sCaptionPadding.Top;
				client.Right -= m_sCaptionPadding.Right;
				client.Bottom -= m_sCaptionPadding.Bottom;
				client.validate();
				PointF size{ pf->getStringSize(m_sCaption, getFont()->Distance) };
				PointF result;
				switch (m_eCaptionHorizontalAlign)
				{
				case TextAlign::Center:
					result.X = (client.Right + client.Left - size.X) * 0.5f;
					break;
				case TextAlign::Right:
					result.X = client.Right - size.X;
					break;
				default:
					result.X = client.Left;
				}
				switch (m_eCaptionVerticalAlign)
				{
				case VerticalAlign::Middle:
					result.Y = (client.Bottom + client.Top - size.Y) * 0.5f;
					break;
				case VerticalAlign::Bottom:
					result.Y = client.Bottom - size.Y;
					break;
				default:
					result.Y = client.Top;
				}
				return result;
			}
			return PointF{ 0, 0 };
		}
	#pragma endregion

	#pragma region Paint
		void CProgressBar::Render()
		{
			IRenderer * renderer{ getForm()->getRenderer() };
			PointF disp{ DispOnCanvas(m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() }, client{ getClientRect() };
				client += disp;
				IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
				PointF caption_position{ CalculateCaptionPosition(pf) };
				caption_position += disp;
				caption_position.X = std::round(caption_position.X);
				caption_position.Y = std::round(caption_position.Y);
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
				DrawDoubleBackground(renderer, rect, m_sOuterBorderWidth, m_sInnerBorderWidth, m_sBorderRadius, m_sOuterBorderColor, m_sInnerBorderColor, m_sBackgroundColor, m_cBackgroundGradient);
				Block b{ rect, AddElements(m_sOuterBorderWidth, m_sInnerBorderWidth), m_sBorderRadius, PointLocation::Inside };
				RenderForeground(renderer, rect, &b, client);
				DrawTextShadow(renderer, pf, getFont()->Distance, Identity, client, caption_position, m_sCaption, getFont()->ShadowColor, getFont()->ShadowShift, getFont()->ShadowRadius);
				RenderCaption(renderer, rect, pf, caption_position, &b);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CProgressBar::RenderCaption(IRenderer *renderer, const RectF &rect, IPlatformFont *pf, const PointF &caption_position, const Block *block)
		{
			if (!m_sCaption.empty() && getFont()->Color.A > 0)
			{
				CStoreBlock s_block{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBlock(block)
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(caption_position.X, caption_position.Y, 0))
					->DrawText(m_sCaption, pf, getFont()->Distance, getFont()->Color);
			}
		}

		void CProgressBar::RenderForeground(IRenderer *renderer, const RectF &rect, const Block *block, const RectF &client)
		{
			float size;
			switch (m_eFillDirection)
			{
			case FillDirection::TopToBottom:
			case FillDirection::BottomToTop:
				size = client.height() * (m_fProgress - m_fMin) / (m_fMax - m_fMin);
				break;
			default:
				size = client.width() * (m_fProgress - m_fMin) / (m_fMax - m_fMin);
			}
			if (m_bSmooth)
			{
				CStoreBlock s_block{ renderer };
				renderer->ActivateBlock(block);
				RectF rect{ client };
				switch (m_eFillDirection)
				{
				case FillDirection::RightToLeft:
					rect.Left = client.Right - size;
					break;
				case FillDirection::TopToBottom:
					rect.Bottom = client.Top + size;
					break;
				case FillDirection::BottomToTop:
					rect.Top = client.Bottom - size;
					break;
				default:
					rect.Right = client.Left + size;
				}
				if (m_cForegroundGradient.getPointCount() >= 2)
					renderer->DrawGradient(rect, m_cForegroundGradient);
				else
					renderer->DrawRectangle(rect, m_sForegroundColor);
			}
			else
			{
				int bar_count{ ntl::Round<int>(size / (m_fBarSize + m_fBarInterval)) };
				RectF rect;
				for (int i = 0; i < bar_count; i++)
				{
					switch (m_eFillDirection)
					{
					case FillDirection::RightToLeft:
						rect = RectF{ client.Right - (float)i * (m_fBarSize + m_fBarInterval) - m_fBarSize, client.Top, client.Right - (float)i * (m_fBarSize + m_fBarInterval), client.Bottom };
						break;
					case FillDirection::TopToBottom:
						rect = RectF{ client.Left, client.Top + (float)i * (m_fBarSize + m_fBarInterval), client.Right, client.Top + (float)i * (m_fBarSize + m_fBarInterval) + m_fBarSize };
						break;
					case FillDirection::BottomToTop:
						rect = RectF{ client.Left, client.Bottom - (float)i * (m_fBarSize + m_fBarInterval) - m_fBarSize, client.Right, client.Bottom - (float)i * (m_fBarSize + m_fBarInterval) };
						break;
					default:
						rect = RectF{ client.Left + (float)i * (m_fBarSize + m_fBarInterval), client.Top, client.Left + (float)i * (m_fBarSize + m_fBarInterval) + m_fBarSize, client.Bottom };
					}
					DrawSimpleBackground(renderer, rect, m_sBarBorderWidth, m_sBarBorderRadius, m_sBarBorderColor, m_sBarColor, m_cBarGradient);
				}
			}
		}
	#pragma endregion
	}
}