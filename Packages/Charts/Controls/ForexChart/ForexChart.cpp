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
	namespace charts
	{
	#pragma region CGradientListener
		CForexChart::CGradientListener::CGradientListener(CForexChart *control) :
			m_pControl{ control }
		{

		}

		void CForexChart::CGradientListener::NotifyOnChange()
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
		CForexChart::CForexChart() :
			CControl(L"ForexChart", true, true, false, false, false, false),
			m_cGradientListener{ this },
			m_pData{ nullptr },
			m_sAutoGrid{ true, true },
			m_sDefaultGridStep{ 150, 50 },
			m_sShowAxes{ true, true },
			m_sShowGrid{ true, true },
			m_sBackgroundColor{ 0, 0, 0, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_sXAxisColor{ 128, 128, 128, 255 },
			m_sYAxisColor{ 128, 128, 128, 255 },
			m_sXGridColor{ 64, 64, 64, 255 },
			m_sYGridColor{ 64, 64, 64, 255 },
			m_sGridStep{ 150, 50 },
			m_sLabelPadding{ 48, 16 },
			m_sShowLabels{ true, true },
			m_bXLabelsAtTop{ false },
			m_bYLabelsAtRight{ true },
			m_sLabelSigns{ 0, 5 },
			m_sXLabelsColor{ 255, 255, 255, 255 },
			m_sYLabelsColor{ 255, 255, 255, 255 },
			m_sAutoGridStep{ 10, 10 },
			m_sXRange{ -169, 169 },
			m_sYRange{ -97, 97 },
			m_sAutoRange{ true, true },
			m_sAutoXRange{ 0, 0 },
			m_sAutoYRange{ 0, 0 },
			m_fBarWidth{ 9 },
			m_sNormalPositiveBarBorderColor{ 0, 255, 0, 255 },
			m_sActivePositiveBarBorderColor{ 0, 255, 0, 128 },
			m_sNormalNegativeBarBorderColor{ 0, 255, 0, 255 },
			m_sActiveNegativeBarBorderColor{ 0, 255, 0, 128 },
			m_sNormalPositiveBarBackgroundColor{ 0, 0, 0, 0 },
			m_sActivePositiveBarBackgroundColor{ 0, 0, 0, 0 },
			m_sNormalNegativeBarBackgroundColor{ 255, 255, 255, 255 },
			m_sActiveNegativeBarBackgroundColor{ 255, 255, 255, 128 },
			m_bCandlestick{ true },
			m_pCanvas{ nullptr },
			m_iHoveredPoint{ -1 },
			m_bIgnoreGradient{ false }
		{
			OnHoverPoint = nullptr;
			OnLeavePoint = nullptr;

			setService(new CForexChartService(this), true);
			setSize(PointF{ 370, 210 });
		}

		CForexChart::CForexChart(IForm *parent) :CForexChart()
		{
			setForm(parent);
		}

		CForexChart::CForexChart(IControl *parent) : CForexChart()
		{
			setParent(parent);
		}

		CForexChart::~CForexChart()
		{
			if (m_pData)
				m_pData->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CForexChart::getClientRect()
		{
			RectF result{
				(m_sShowLabels.Y && !m_bYLabelsAtRight) ? m_sLabelPadding.X : 0,
				(m_sShowLabels.X && m_bXLabelsAtTop) ? m_sLabelPadding.Y : 0,
				getWidth() - ((m_sShowLabels.Y && m_bYLabelsAtRight) ? m_sLabelPadding.X : 0),
				getHeight() - ((m_sShowLabels.X && !m_bXLabelsAtTop) ? m_sLabelPadding.Y : 0)
			};
			result.validate();
			return result;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CForexChart::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_sLabelPadding *= s;
				m_fBarWidth *= s.X;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CForexChart::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region IForexChart getters
		PointD CForexChart::getXRange()
		{
			return m_sXRange;
		}

		PointD CForexChart::getYRange()
		{
			return m_sYRange;
		}

		PointB CForexChart::getAutoRange()
		{
			return m_sAutoRange;
		}

		IForexChart::IForexChartData *CForexChart::getData()
		{
			if (!m_pData)
				m_pData = new CForexChartData();
			return m_pData;
		}
	#pragma endregion

	#pragma region IForexChart setters
		bool CForexChart::setXRange(const PointD &value)
		{
			if (ntl::IsGreater<double>(value.Y, value.X) && IsNotEqual(value, m_sXRange))
			{
				m_sXRange = value;
				m_sAutoRange.X = false;
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CForexChart::setYRange(const PointD &value)
		{
			if (ntl::IsGreater<double>(value.Y, value.X) && IsNotEqual(value, m_sYRange))
			{
				m_sYRange = value;
				m_sAutoRange.Y = false;
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CForexChart::setAutoRange(const PointB &value)
		{
			if (value != m_sAutoRange)
			{
				m_sAutoRange = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CForexChart::setData(IForexChartData *value, const bool release_old)
		{
			if (value != m_pData)
			{
				if (m_pData && release_old)
					m_pData->Release();
				m_pData = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IForexChart methods
		void CForexChart::Update()
		{
			UpdateAutoRanges();
			UpdateHoveredPoint();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}
	#pragma endregion

	#pragma region Getters
		PointB CForexChart::getShowAxes() const
		{
			return m_sShowAxes;
		}

		PointB CForexChart::getShowGrid() const
		{
			return m_sShowGrid;
		}

		Color CForexChart::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CForexChart::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		Color CForexChart::getXAxisColor() const
		{
			return m_sXAxisColor;
		}

		Color CForexChart::getYAxisColor() const
		{
			return m_sYAxisColor;
		}

		Color CForexChart::getXGridColor() const
		{
			return m_sXGridColor;
		}

		Color CForexChart::getYGridColor() const
		{
			return m_sYGridColor;
		}

		PointD CForexChart::getGridStep() const
		{
			return m_sGridStep;
		}

		PointF CForexChart::getLabelPadding() const
		{
			return m_sLabelPadding;
		}

		PointB CForexChart::getShowLabels() const
		{
			return m_sShowLabels;
		}

		bool CForexChart::isXLabelsAtTop() const
		{
			return m_bXLabelsAtTop;
		}

		bool CForexChart::isYLabelsAtRight() const
		{
			return m_bYLabelsAtRight;
		}

		Point CForexChart::getLabelSigns() const
		{
			return m_sLabelSigns;
		}

		Color CForexChart::getXLabelsColor() const
		{
			return m_sXLabelsColor;
		}

		Color CForexChart::getYLabelsColor() const
		{
			return m_sYLabelsColor;
		}

		PointB CForexChart::getAutoGrid()
		{
			return m_sAutoGrid;
		}

		PointD CForexChart::getDefaultGridStep()
		{
			return m_sDefaultGridStep;
		}

		float CForexChart::getBarWidth() const
		{
			return m_fBarWidth;
		}

		Color CForexChart::getNormalPositiveBarBorderColor() const
		{
			return m_sNormalPositiveBarBorderColor;
		}

		Color CForexChart::getActivePositiveBarBorderColor() const
		{
			return m_sActivePositiveBarBorderColor;
		}

		Color CForexChart::getNormalNegativeBarBorderColor() const
		{
			return m_sNormalNegativeBarBorderColor;
		}

		Color CForexChart::getActiveNegativeBarBorderColor() const
		{
			return m_sActiveNegativeBarBorderColor;
		}

		Color CForexChart::getNormalPositiveBarBackgroundColor() const
		{
			return m_sNormalPositiveBarBackgroundColor;
		}

		Color CForexChart::getActivePositiveBarBackgroundColor() const
		{
			return m_sActivePositiveBarBackgroundColor;
		}

		Color CForexChart::getNormalNegativeBarBackgroundColor() const
		{
			return m_sNormalNegativeBarBackgroundColor;
		}

		Color CForexChart::getActiveNegativeBarBackgroundColor() const
		{
			return m_sActiveNegativeBarBackgroundColor;
		}

		bool CForexChart::isCandleStick() const
		{
			return m_bCandlestick;
		}
	#pragma endregion

	#pragma region Setters
		bool CForexChart::setShowAxes(const PointB &value)
		{
			if (value != m_sShowAxes)
			{
				m_sShowAxes = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CForexChart::setShowGrid(const PointB &value)
		{
			if (value != m_sShowGrid)
			{
				m_sShowGrid = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CForexChart::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_cBackgroundGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setXAxisColor(const Color &value)
		{
			if (value != m_sXAxisColor)
			{
				m_sXAxisColor = value;
				if (m_sShowAxes.X)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setYAxisColor(const Color &value)
		{
			if (value != m_sYAxisColor)
			{
				m_sYAxisColor = value;
				if (m_sShowAxes.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setXGridColor(const Color &value)
		{
			if (value != m_sXGridColor)
			{
				m_sXGridColor = value;
				if (m_sShowGrid.X)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setYGridColor(const Color &value)
		{
			if (value != m_sYGridColor)
			{
				m_sYGridColor = value;
				if (m_sShowGrid.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setGridStep(const PointD &value)
		{
			if (ntl::IsGreater<double>(value.X, 0) && ntl::IsGreater<double>(value.Y, 0) && IsNotEqual(value, m_sGridStep))
			{
				m_sGridStep = value;
				m_sAutoGrid = PointB{ false, false };
				if (m_sShowGrid.X || m_sShowGrid.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setLabelPadding(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sLabelPadding))
			{
				m_sLabelPadding = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CForexChart::setShowLabels(const PointB &value)
		{
			if (value != m_sShowLabels)
			{
				m_sShowLabels = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CForexChart::setXLabelsAtTop(const bool value)
		{
			if (value != m_bXLabelsAtTop)
			{
				m_bXLabelsAtTop = value;
				if (m_sShowLabels.X)
				{
					UpdateHoveredPoint();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setYLabelsAtRight(const bool value)
		{
			if (value != m_bYLabelsAtRight)
			{
				m_bYLabelsAtRight = value;
				if (m_sShowLabels.Y)
				{
					UpdateHoveredPoint();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setLabelSigns(const Point &value)
		{
			if (value.X >= 0 && value.X <= 9 && value.Y >= 0 && value.Y <= 9 && value != m_sLabelSigns)
			{
				m_sLabelSigns = value;
				if (m_sShowLabels.X || m_sShowLabels.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setXLabelsColor(const Color &value)
		{
			if (value != m_sXLabelsColor)
			{
				m_sXLabelsColor = value;
				if (m_sShowLabels.X)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setYLabelsColor(const Color &value)
		{
			if (value != m_sYLabelsColor)
			{
				m_sYLabelsColor = value;
				if (m_sShowLabels.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setAutoGrid(const PointB &value)
		{
			if (value != m_sAutoGrid)
			{
				m_sAutoGrid = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CForexChart::setDefaultGridStep(const PointD &value)
		{
			if (ntl::IsGreater<double>(value.X, 0) && ntl::IsGreater<double>(value.Y, 0) && IsNotEqual(value, m_sDefaultGridStep))
			{
				m_sDefaultGridStep = value;
				if (m_sAutoGrid.X || m_sAutoGrid.Y)
				{
					UpdateAutoRanges();
					UpdateHoveredPoint();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setBarWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fBarWidth))
			{
				m_fBarWidth = value;
				if (m_pData && m_pData->getCount() > 0)
				{
					UpdateHoveredPoint();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setNormalPositiveBarBorderColor(const Color &value)
		{
			if (value != m_sNormalPositiveBarBorderColor)
			{
				m_sNormalPositiveBarBorderColor = value;
				if (m_pData && m_pData->getCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setActivePositiveBarBorderColor(const Color &value)
		{
			if (value != m_sActivePositiveBarBorderColor)
			{
				m_sActivePositiveBarBorderColor = value;
				if (m_pData && m_pData->getCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setNormalNegativeBarBorderColor(const Color &value)
		{
			if (value != m_sNormalNegativeBarBorderColor)
			{
				m_sNormalNegativeBarBorderColor = value;
				if (m_pData && m_pData->getCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setActiveNegativeBarBorderColor(const Color &value)
		{
			if (value != m_sActiveNegativeBarBorderColor)
			{
				m_sActiveNegativeBarBorderColor = value;
				if (m_pData && m_pData->getCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setNormalPositiveBarBackgroundColor(const Color &value)
		{
			if (value != m_sNormalPositiveBarBackgroundColor)
			{
				m_sNormalPositiveBarBackgroundColor = value;
				if (m_pData && m_pData->getCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setActivePositiveBarBackgroundColor(const Color &value)
		{
			if (value != m_sActivePositiveBarBackgroundColor)
			{
				m_sActivePositiveBarBackgroundColor = value;
				if (m_pData && m_pData->getCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setNormalNegativeBarBackgroundColor(const Color &value)
		{
			if (value != m_sNormalNegativeBarBackgroundColor)
			{
				m_sNormalNegativeBarBackgroundColor = value;
				if (m_pData && m_pData->getCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setActiveNegativeBarBackgroundColor(const Color &value)
		{
			if (value != m_sActiveNegativeBarBackgroundColor)
			{
				m_sActiveNegativeBarBackgroundColor = value;
				if (m_pData && m_pData->getCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CForexChart::setCandlestick(const bool value)
		{
			if (value != m_bCandlestick)
			{
				m_bCandlestick = value;
				if (m_pData && m_pData->getCount() > 0)
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
		void CForexChart::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".XAxisColor", m_sXAxisColor);
			style->getOption(m_sClassName + L".YAxisColor", m_sYAxisColor);
			style->getOption(m_sClassName + L".XGridColor", m_sXGridColor);
			style->getOption(m_sClassName + L".YGridColor", m_sYGridColor);
			style->getOption(m_sClassName + L".LabelPadding", m_sLabelPadding);
			style->getOption(m_sClassName + L".XLabelsColor", m_sXLabelsColor);
			style->getOption(m_sClassName + L".YLabelsColor", m_sYLabelsColor);
			style->getOption(m_sClassName + L".BarWidth", m_fBarWidth);
			style->getOption(m_sClassName + L".NormalPositiveBarBorderColor", m_sNormalPositiveBarBorderColor);
			style->getOption(m_sClassName + L".ActivePositiveBarBorderColor", m_sActivePositiveBarBorderColor);
			style->getOption(m_sClassName + L".NormalNegativeBarBorderColor", m_sNormalNegativeBarBorderColor);
			style->getOption(m_sClassName + L".ActiveNegativeBarBorderColor", m_sActiveNegativeBarBorderColor);
			style->getOption(m_sClassName + L".NormalPositiveBarBackgroundColor", m_sNormalPositiveBarBackgroundColor);
			style->getOption(m_sClassName + L".ActivePositiveBarBackgroundColor", m_sActivePositiveBarBackgroundColor);
			style->getOption(m_sClassName + L".NormalNegativeBarBackgroundColor", m_sNormalNegativeBarBackgroundColor);
			style->getOption(m_sClassName + L".ActiveNegativeBarBackgroundColor", m_sActiveNegativeBarBackgroundColor);
			m_bIgnoreGradient = false;
		}

		bool CForexChart::UpdateHoveredPoint()
		{
			if (getForm())
				return UpdateHoveredPoint((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition()));
			if (m_iHoveredPoint >= 0)
			{
				m_iHoveredPoint = -1;
				if (OnLeavePoint)
					OnLeavePoint(this);
				return true;
			}
			return false;
		}

		bool CForexChart::UpdateHoveredPoint(const PointF &position)
		{
			int hovered_point{ -1 };
			if (m_pData && isEnabled(true))
			{
				RectF client{ getClientRect() };
				if (!client.is_zero())
				{
					PointF p{ FormToLocal(position) };
					if (p.X >= client.Left && p.X < client.Right && p.Y >= client.Top && p.Y < client.Bottom)
					{
						p.X -= client.Left;
						p.Y -= client.Top;
						PointF view_size{ client.width(), client.height() };
						double x, ymin, ymax;
						PointD xrange{ m_sAutoRange.X ? m_sAutoXRange : m_sXRange }, yrange{ m_sAutoRange.Y ? m_sAutoYRange : m_sYRange };
						CDateTime dt;
						for (int i = 0; i < m_pData->getCount(); i++)
						{
							dt = m_pData->getDateTime(i);
							x = DataXToViewD(double((long long)dt), xrange, (double)view_size.X);
							if ((double)p.X >= x - double(m_fBarWidth * 0.5f) && (double)p.X < x + double(m_fBarWidth * 0.5f))
							{
								ymin = DataYToViewD((double)m_pData->getMin(i), yrange, (double)view_size.Y);
								if ((double)p.Y < ymin)
								{
									ymax = DataYToViewD((double)m_pData->getMax(i), yrange, (double)view_size.Y);
									if ((double)p.Y >= ymax)
									{
										hovered_point = i;
										break;
									}
								}
							}
						}
					}
				}
			}
			if (hovered_point != m_iHoveredPoint)
			{
				m_iHoveredPoint = hovered_point;
				if (m_iHoveredPoint >= 0)
				{
					if (OnHoverPoint)
						OnHoverPoint(this, m_iHoveredPoint);
				}
				else
				{
					if (OnLeavePoint)
						OnLeavePoint(this);
				}
				return true;
			}
			return false;
		}

		void CForexChart::UpdateAutoRanges()
		{
			RectF client{ getClientRect() };
			if (m_sAutoRange.X || m_sAutoRange.Y)
			{
				double xmin{ 0 }, ymin{ 0 }, xmax, ymax;
				int count{ 0 };
				m_iMinTime = (long long)CDateTime{};
				if (m_pData)
				{
					CDateTime tmp;
					long long t, tmin, tmax;
					for (int i = 0; i < m_pData->getCount(); i++)
					{
						tmp = m_pData->getDateTime(i);
						t = (long long)tmp;
						if (count > 0)
						{
							m_iMinTime = ntl::Min<long long>(m_iMinTime, t);
							tmin = ntl::Min<long long>(tmin, t);
							ymin = ntl::Min<double>(ymin, (double)m_pData->getMin(i));
							tmax = ntl::Max<long long>(tmax, t);
							ymax = ntl::Max<double>(ymax, (double)m_pData->getMax(i));
							count++;
						}
						else
						{
							m_iMinTime = tmin = tmax = t;
							ymin = (double)m_pData->getMin(i);
							ymax = (double)m_pData->getMax(i);
							count = 1;
						}
					}
					if (count > 0)
					{
						tmin -= m_iMinTime;
						tmax -= m_iMinTime;
						xmin = (double)tmin;
						xmax = (double)tmax;
					}
				}
				if (count == 0)
				{
					xmin = double(-client.width() * 0.5f);
					ymin = double(-client.height() * 0.5f);
					xmax = double(client.width() * 0.5f);
					ymax = double(client.height() * 0.5f);
				}
				else if (count == 1)
				{
					xmin -= double(client.width() * 0.5f);
					xmax += double(client.width() * 0.5f);
				}
				// Ranges are extended by 5% to leave some space at the borders. It is applied only if there is data
				if (m_sAutoRange.X)
					m_sAutoXRange = PointD{ xmin - ((count > 1) ? ((xmax - xmin) * 0.05) : 0), xmax + ((count > 1) ? ((xmax - xmin) * 0.05) : 0) };
				if (m_sAutoRange.Y)
					m_sAutoYRange = PointD{ ymin - ((count > 1) ? ((ymax - ymin) * 0.05) : 0), ymax + ((count > 1) ? ((ymax - ymin) * 0.05) : 0) };
			}
			if (m_sAutoGrid.X)
			{
				PointD xrange{ m_sAutoRange.X ? m_sAutoXRange : m_sXRange };
				if (ntl::IsGreater<double>(xrange.Y, xrange.X))
				{
					double step{ m_sDefaultGridStep.X }, w{ (double)client.width() }, zero{ DataXToViewD(0, xrange, w) }, p{ ntl::Abs<double>(DataXToViewD(step, xrange, w) - zero) };
					if (p < m_sDefaultGridStep.X)
					{
						while (p < m_sDefaultGridStep.X)
						{
							step *= 2;
							p = ntl::Abs<double>(DataXToViewD(step, xrange, w) - zero);
						}
					}
					else if (p > m_sDefaultGridStep.X)
					{
						while (p > m_sDefaultGridStep.X)
						{
							step *= 0.5;
							p = ntl::Abs<double>(DataXToViewD(step, xrange, w) - zero);
						}
					}
					m_sAutoGridStep.X = step;
				}
			}
			if (m_sAutoGrid.Y)
			{
				PointD yrange{ m_sAutoRange.Y ? m_sAutoYRange : m_sYRange };
				if (ntl::IsGreater<double>(yrange.Y, yrange.X))
				{
					double step{ m_sDefaultGridStep.Y }, h{ client.height() }, zero{ DataYToViewD(0, yrange, h) }, p{ ntl::Abs<double>(DataYToViewD(step, yrange, h) - zero) };
					if (p < m_sDefaultGridStep.Y)
					{
						while (p < m_sDefaultGridStep.Y)
						{
							step *= 2;
							p = ntl::Abs<double>(DataYToViewD(step, yrange, h) - zero);
						}
					}
					else if (p > m_sDefaultGridStep.Y)
					{
						while (p > m_sDefaultGridStep.Y)
						{
							step *= 0.5;
							p = ntl::Abs<double>(DataYToViewD(step, yrange, h) - zero);
						}
					}
					m_sAutoGridStep.Y = step;
				}
			}
		}

		String CForexChart::XToTime(const long long x)
		{
			CDateTime dt{ x };
			String day{ ToString(dt.getDay()) };
			String month{ CTranslate::Month(months::ShortNames[dt.getMonth()]) };
			String year{ ToString(dt.getYear()) };
			String hour{ (dt.getHour() < 10) ? (L"0" + ToString(dt.getHour())) : ToString(dt.getHour()) };
			String minute{ (dt.getMinute() < 10) ? (L"0" + ToString(dt.getMinute())) : ToString(dt.getMinute()) };
			return day + L", " + month + L" " + year + L" " + hour + L":" + minute;
		}

		double CForexChart::DataXToViewD(const double x, const PointD &xrange, const double view_width)
		{
			return (x - xrange.X) * view_width / (xrange.Y - xrange.X);
		}

		double CForexChart::DataYToViewD(const double y, const PointD &yrange, const double view_height)
		{
			return view_height - (y - yrange.X) * view_height / (yrange.Y - yrange.X);
		}
	#pragma endregion

	#pragma region Paint
		void CForexChart::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			RectF rect{ 0, 0, getWidth(), getHeight() };
			if (PrepareCanvas(renderer, &m_pCanvas, rect))
			{
				CStoreTarget s_target{ renderer };
				renderer->ActivateTarget(m_pCanvas);
				renderer->Clear(Color{ 0, 0, 0, 0 });

				RectF client{ getClientRect() };
				IFont *font{ getFont() };
				IPlatformFont *pf{ font ? font->getPlatformFont(renderer) : nullptr };
				RenderBackground(renderer, rect);
				if (!client.is_zero())
				{
					PointD xrange{ m_sAutoRange.X ? m_sAutoXRange : m_sXRange }, yrange{ m_sAutoRange.Y ? m_sAutoYRange : m_sYRange };
					PointD grid_step{ m_sAutoGrid.X ? m_sAutoGridStep.X : m_sGridStep.X, m_sAutoGrid.Y ? m_sAutoGridStep.Y : m_sGridStep.Y };
					RenderAxesAndGrid(renderer, client, xrange, yrange, grid_step);
					if (font && pf)
						RenderLabels(renderer, client, font, pf, xrange, yrange, grid_step);
					RenderDataSet(renderer, client, xrange, yrange);
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CForexChart::RenderBackground(IRenderer *renderer, const RectF &rect)
		{
			if (m_cBackgroundGradient.getPointCount() >= 2)
				renderer->DrawGradient(rect, m_cBackgroundGradient);
			else if (m_sBackgroundColor.A > 0)
				renderer->DrawRectangle(rect, m_sBackgroundColor);
		}

		void CForexChart::RenderAxesAndGrid(IRenderer *renderer, const RectF &client, const PointD &xrange, const PointD &yrange, const PointD &grid_step)
		{
			double client_w{ (double)client.width() }, client_h{ (double)client.height() };
			double client_l{ (double)client.Left }, client_t{ (double)client.Top }, client_r{ (double)client.Right }, client_b{ (double)client.Bottom };
			if (m_sShowGrid.X && m_sXGridColor.A > 0)
			{
				double x1{ double((long long)(xrange.X / grid_step.X)) * grid_step.X }, x2{ double((long long)(xrange.Y / grid_step.X)) * grid_step.X };
				while (x1 <= x2)
				{
					double x{ client_l + (x1 - xrange.X) * client_w / (xrange.Y - xrange.X) };
					if (x >= client_l && x < client_r && (ntl::IsNotEqual<double>(x1, 0) || !m_sShowAxes.X))
						renderer->DrawLine(PointF{ (float)x, client.Top }, PointF{ (float)x, client.Bottom }, m_sXGridColor);
					x1 += grid_step.X;
				}
			}
			if (m_sShowGrid.Y && m_sYGridColor.A > 0)
			{
				double y1{ double((long long)(yrange.X / grid_step.Y)) * grid_step.Y }, y2{ double((long long)(yrange.Y / grid_step.Y)) * grid_step.Y };
				while (y1 <= y2)
				{
					double y{ client_b - (y1 - yrange.X) * client_h / (yrange.Y - yrange.X) };
					if (y >= client_t && y < client_b && (ntl::IsNotEqual<double>(y1, 0) || !m_sShowAxes.Y))
						renderer->DrawLine(PointF{ client.Left, (float)y }, PointF{ client.Right, (float)y }, m_sYGridColor);
					y1 += grid_step.Y;
				}
			}
			if (m_sShowAxes.X && yrange.X <= 0 && yrange.Y >= 0 && m_sXAxisColor.A > 0)
			{
				double y{ client_b + yrange.X * client_h / (yrange.Y - yrange.X) };
				renderer->DrawLine(PointF{ client.Left, (float)y }, PointF{ client.Right, (float)y }, m_sXAxisColor);
			}
			if (m_sShowAxes.Y && xrange.X <= 0 && xrange.Y >= 0 && m_sYAxisColor.A > 0)
			{
				double x{ client_l - xrange.X * client_w / (xrange.Y - xrange.X) };
				renderer->DrawLine(PointF{ (float)x, client.Top }, PointF{ (float)x, client.Bottom }, m_sYAxisColor);
			}
		}

		void CForexChart::RenderLabels(IRenderer *renderer, const RectF &client, IFont *font, IPlatformFont *pf, const PointD &xrange, const PointD &yrange, const PointD &grid_step)
		{
			CStorePrimitiveMatrix s_matrix{ renderer };
			String label;
			PointF size;
			Color color;
			double client_l{ (double)client.Left }, client_b{ (double)client.Bottom };
			double client_w{ (double)client.width() }, client_h{ (double)client.height() };
			if (m_sShowLabels.X)
			{
				color = m_sXLabelsColor.A > 0 ? m_sXLabelsColor : font->Color;
				if (color.A > 0)
				{
					double x1{ double((long long)(xrange.X / grid_step.X)) * grid_step.X }, x2{ double((long long)(xrange.Y / grid_step.X)) * grid_step.X };
					while (x1 <= x2)
					{
						double x{ client_l + (x1 - xrange.X) * client_w / (xrange.Y - xrange.X) };
						if (x >= client_l)
						{
							label = XToTime(ntl::Round<long long>(x1) + m_iMinTime);
							if (m_pData)
								label = m_pData->getXLabel(x1 + (double)m_iMinTime, label);
							if (!label.empty())
							{
								size = pf->getStringSize(label, font->Distance);
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>((float)std::round(x - (double)size.X * 0.5), std::round(m_bXLabelsAtTop ? (m_sLabelPadding.Y - size.Y) : client.Bottom), 0))
									->DrawText(label, pf, font->Distance, color);
							}
						}
						x1 += grid_step.X;
					}
				}
			}
			if (m_sShowLabels.Y)
			{
				color = m_sYLabelsColor.A > 0 ? m_sYLabelsColor : font->Color;
				if (color.A > 0)
				{
					double y1{ double((long long)(yrange.X / grid_step.Y)) * grid_step.Y }, y2{ double((long long)(yrange.Y / grid_step.Y)) * grid_step.Y };
					while (y1 <= y2)
					{
						double y{ client_b - (y1 - yrange.X) * client_h / (yrange.Y - yrange.X) };
						if (y < client_b)
						{
							label = ToFixed(y1, m_sLabelSigns.Y);
							if (m_pData)
								label = m_pData->getYLabel(y1, label);
							if (!label.empty())
							{
								size = pf->getStringSize(label, font->Distance);
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(m_bYLabelsAtRight ? client.Right : (m_sLabelPadding.X - size.X)), (float)std::round(y - (double)size.Y * 0.5), 0))
									->DrawText(label, pf, font->Distance, color);
							}
						}
						y1 += grid_step.Y;
					}
				}
			}
		}

		void CForexChart::RenderDataSet(IRenderer *renderer, const RectF &client, const PointD &xrange, const PointD &yrange)
		{
			if (m_pData && m_pData->getCount() > 0)
			{
				ITexture *target{ renderer->CreateTexture(ntl::Round<int>(client.width()), ntl::Round<int>(client.height()), 1, TextureFormat::RGBA, true) };
				if (target)
				{
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateTarget(target)
						->Clear(Color{ 0, 0, 0, 0 });
					RenderData(renderer, target, m_pData, xrange, yrange);
					renderer
						->ActivateTarget(m_pCanvas)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(client.Left, client.Top, 0))
						->DrawImage(target, 1);
					target->Release();
				}
			}
		}

		void CForexChart::RenderData(IRenderer *renderer, ITexture *target, IForexChartData *data, const PointD &xrange, const PointD &yrange)
		{
			PointD view_size{ (double)target->Width, (double)target->Height };
			double x, open, close, min, max, ix, iy;
			Color border;
			CDateTime dt;
			if (m_bCandlestick)
			{
				Color background;
				RectF rect;
				BlockColors colors{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
				for (int i = 0; i < data->getCount(); i++)
				{
					dt = data->getDateTime(i);
					x = DataXToViewD(double((long long)dt - m_iMinTime), xrange, view_size.X);
					open = DataYToViewD((double)data->getOpen(i), yrange, view_size.Y);
					close = DataYToViewD((double)data->getClose(i), yrange, view_size.Y);
					min = DataYToViewD((double)data->getMin(i), yrange, view_size.Y);
					max = DataYToViewD((double)data->getMax(i), yrange, view_size.Y);
					if (i == m_iHoveredPoint)
					{
						if (close >= open)
						{
							border = m_sActivePositiveBarBorderColor;
							background = m_sActivePositiveBarBackgroundColor;
						}
						else
						{
							border = m_sActiveNegativeBarBorderColor;
							background = m_sActiveNegativeBarBackgroundColor;
						}
					}
					else
					{
						if (close >= open)
						{
							border = m_sNormalPositiveBarBorderColor;
							background = m_sNormalPositiveBarBackgroundColor;
						}
						else
						{
							border = m_sNormalNegativeBarBorderColor;
							background = m_sNormalNegativeBarBackgroundColor;
						}
					}
					if (border.A > 0 || background.A > 0)
					{
						rect.Left = (float)x - m_fBarWidth * 0.5f;
						rect.Right = rect.Left + m_fBarWidth;
						rect.Top = (float)ntl::Min<double>(open, close);
						rect.Bottom = (float)ntl::Max<double>(open, close);
						if (ntl::IsEqual<float>(rect.Bottom, rect.Top))
							rect.Bottom++;
						colors[0] = colors[1] = colors[2] = colors[3] = border;
						colors[4] = background;
						renderer->DrawBlock(rect, RectF{ 1, 1, 1, 1 }, RectF{ 0, 0, 0, 0 }, colors);
						if (border.A > 0)
						{
							iy = max;
							ix = x;
							if (iy < rect.Top)
								renderer->DrawLine(PointF{ (float)ix, (float)iy }, PointF{ (float)ix, rect.Top }, border);
							iy = min;
							if (iy > rect.Bottom)
								renderer->DrawLine(PointF{ (float)ix, rect.Bottom }, PointF{ (float)ix, (float)iy }, border);
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < data->getCount(); i++)
				{
					dt = data->getDateTime(i);
					x = DataXToViewD(double((long long)dt - m_iMinTime), xrange, view_size.X);
					open = DataYToViewD((double)data->getOpen(i), yrange, view_size.Y);
					close = DataYToViewD((double)data->getClose(i), yrange, view_size.Y);
					min = DataYToViewD((double)data->getMin(i), yrange, view_size.Y);
					max = DataYToViewD((double)data->getMax(i), yrange, view_size.Y);
					if (i == m_iHoveredPoint)
					{
						if (close >= open)
							border = m_sActivePositiveBarBorderColor;
						else
							border = m_sActiveNegativeBarBorderColor;
					}
					else
					{
						if (close >= open)
							border = m_sNormalPositiveBarBorderColor;
						else
							border = m_sNormalNegativeBarBorderColor;
					}
					if (border.A > 0)
					{
						renderer->DrawLine(PointF{ (float)x, (float)max }, PointF{ (float)x, (float)min }, border);
						renderer->DrawLine(PointF{ (float)x - (m_fBarWidth - 1) / 2, (float)open }, PointF{ (float)x - 1, (float)open }, border);
						renderer->DrawLine(PointF{ (float)x, (float)close }, PointF{ (float)x + (m_fBarWidth - 1) / 2 - 1, (float)close }, border);
					}
				}
			}
		}
	#pragma endregion
	}
}